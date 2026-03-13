/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** ClientSession
*/

#include "ClientSession.hpp"

#include <cctype>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unistd.h>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>

#include "constants.hpp"
#include "StringUtils.hpp"
#include "FtpException/include/AccessDenied.hpp"
#include "FtpException/include/NoSuchFileOrDirectory.hpp"
#include "FtpException/include/NotADirectory.hpp"
#include "FtpException/include/PermissionDenied.hpp"

namespace ftp {
ClientSession::ClientSession(
    const std::shared_ptr<network::ConnectedSocket> &socket,
    FtpProtocol &protocol, const std::string &rootDirectory): _socket{socket},
    _protocol{protocol}, _rootDirectory{fs::canonical(rootDirectory)},
    _currentDirectory{fs::canonical(rootDirectory)}
{
    _buffer.resize(1024);
}

void ClientSession::start()
{
    doRead();
}

void ClientSession::doRead()
{
    _socket->asyncReadSome(network::Buffer{_buffer},
        [this](const std::error_code &errCode, const std::size_t &readBytes) {
            if (errCode) {
                std::cerr << "Something went wrong while reading from socket: ";
                std::cerr << utils::RED << errCode.message() << utils::RESET <<
                    std::endl;
                return;
            }
            if (readBytes == 0) {
                _logger.start(ULogLevel::INFO) << "Connection lost" <<
                    utils::END;
                return;
            }

            handleReadData(readBytes);
        });
}

void ClientSession::send(const std::string &message) const
{
    _socket->syncWrite(network::Buffer{message}, [](auto, auto) {});
}

utils::Logger ClientSession::warnLog() noexcept
{
    return _logger.start(ULogLevel::WARNING);
}

void ClientSession::setUser() noexcept
{
    _isUserSet = true;
}

void ClientSession::setPassword() noexcept
{
    _isPasswordSet = true;
}

bool ClientSession::isLoggedIn() const noexcept
{
    return _isUserSet && _isPasswordSet;
}

void ClientSession::closeConnection() const
{
    _socket->close();
}

bool ClientSession::isUserSet() const noexcept
{
    return _isUserSet;
}

void ClientSession::changeDirectory(const std::string &directory)
{
    try {
        const fs::path resolvedRoot = fs::weakly_canonical(_rootDirectory);

        fs::path candidate;
        if (!directory.empty() && directory[0] == '/') {
            const fs::path ftpPath = fs::path{directory}.relative_path();
            candidate              = resolvedRoot / ftpPath;
        } else {
            candidate = _currentDirectory / fs::path{directory};
        }

        const fs::path resolvedTarget = fs::weakly_canonical(candidate);

        auto rootIt   = resolvedRoot.begin();
        auto targetIt = resolvedTarget.begin();

        for (; rootIt != resolvedRoot.end() && targetIt != resolvedTarget.end();
               ++rootIt, ++targetIt) {
            if (*rootIt != *targetIt)
                throw error::PermissionDenied{};
        }
        if (rootIt != resolvedRoot.end())
            throw error::PermissionDenied{};

        if (!fs::exists(resolvedTarget))
            throw error::NoSuchFileOrDirectory{};
        if (!fs::is_directory(resolvedTarget))
            throw error::NotADirectory{};

        _currentDirectory = resolvedTarget;
    } catch (const fs::filesystem_error &err) {
        if (err.code() == std::errc::no_such_file_or_directory)
            throw error::NoSuchFileOrDirectory{};
        if (err.code() == std::errc::permission_denied)
            throw error::PermissionDenied{};
        throw error::AccessDenied{};
    }
}

void ClientSession::changeDirectory()
{
    changeDirectory("..");
}

std::string ClientSession::getCurrentDirectory() const noexcept
{
    const std::string pwd = fs::relative(_currentDirectory, _rootDirectory);

    if (pwd == ".")
        return "/";
    return "/" + pwd;
}

void ClientSession::setPortRemoteEndpoint(const std::string &host)
{
    const auto tokens = utils::StringUtils::split(host, ',');
    if (tokens.size() != 6)
        throw std::invalid_argument{""};

    for (std::size_t i = 0; i < 6; ++i) {
        const auto temp = std::stoi(tokens.at(i));
        if (temp < 0 || temp > 255)
            throw std::invalid_argument{""};
    }

    const auto ipAddress = tokens.at(0) + "." + tokens.at(1) + "." + tokens.
        at(2) + "." + tokens.at(3);
    const short port = (std::stoi(tokens.at(4)) * 256) +
        std::stoi(tokens.at(5));
    try {
        _portRemoteEndpoint = network::Endpoint{port, ipAddress};
        _mode               = Mode::ACTIVE;
        _logger.start(ULogLevel::ERROR) << "Connecting to: "
            << _portRemoteEndpoint.getHostname() << ":"
            << _portRemoteEndpoint.getPort() << utils::END;
    } catch (const std::exception &) {
        throw;
    }
}

bool ClientSession::isModeSet() const noexcept
{
    return _mode != Mode::NONE;
}

void ClientSession::listDirectory(const std::vector<std::string> &dirs)
{
    std::vector<std::string> args;
    for (std::size_t i = 1; i < dirs.size(); ++i) {
        if (dirs.at(i)[0] == '/')
            args.push_back(fs::weakly_canonical(
                _rootDirectory / fs::path{dirs.at(i)}.relative_path()));
        else
            args.push_back(
                fs::weakly_canonical(
                    _currentDirectory / fs::path{dirs.at(i)}));
        if (args.back().starts_with(".."))
            throw error::PermissionDenied{};
    }

    if (_mode == Mode::ACTIVE) {
        this->send("150 File status okay; about to open data connection.\r\n");
        auto socket = network::ConnectedSocket{_socket->getIOContext()};
        try {
            socket.connect(_portRemoteEndpoint);
            _logger.start(ULogLevel::ERROR) << "Start transfer ..." <<
                utils::END;
            if (!runLsOnDataSocket(socket.getFd(), args))
                return;
            this->send("226 Closing data connection.\r\n");
            socket.close();
            _logger.start(ULogLevel::ERROR) << "End transfer ..." << utils::END;
        } catch (const std::exception &) {
            send("425 Can't open data connection.\r\n");
        }
    }

    resetMode();
}

bool ClientSession::runLsOnDataSocket(const int dataFd,
    const std::vector<std::string> &dirs) const
{
    const pid_t pid = fork();
    if (pid == -1) {
        send("451 Requested action aborted.\r\n");
        return false;
    }

    if (pid == 0) {
        if (dup2(dataFd, STDOUT_FILENO) == -1)
            _exit(1);
        if (dup2(dataFd, STDERR_FILENO) == -1)
            _exit(1);

        close(dataFd);

        std::vector<char *> argv;
        argv.push_back(const_cast<char *>("ls"));
        argv.push_back(const_cast<char *>("-l"));

        for (const std::string &dir: dirs)
            argv.push_back(const_cast<char *>(dir.c_str()));

        argv.push_back(nullptr);

        execv("/bin/ls", argv.data());
        _exit(1);
    }

    auto status = 0;
    // close(dataFd);

    if (waitpid(pid, &status, 0) == -1)
        return false;

    return WIFEXITED(status) && WEXITSTATUS(status) == 0;
}

void ClientSession::handleReadData(const size_t &bytes)
{
    _processedData.append(_buffer.begin(), _buffer.begin() + bytes);

    const std::size_t endLine = _processedData.find("\r\n");

    if (endLine == std::string::npos) {
        doRead();
    } else {
        const std::string command = _processedData.substr(0, endLine);
        _logger.start(ULogLevel::INFO) << "Received: " << command <<
            utils::END;

        _protocol.handleCommand(*this, command);

        _processedData.erase(0, endLine + 2);
        doRead();
    }
}

void ClientSession::resetMode() noexcept
{
    _mode = Mode::NONE;
}
} // ftp
