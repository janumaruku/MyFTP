/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** ClientSession
*/

#include "ClientSession.hpp"

#include <cctype>
#include <cstring>
#include <fcntl.h>
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

void ClientSession::setPassiveMode()
{
    resetMode();

    _passiveFd = socket(AF_INET, SOCK_STREAM, 0);
    if (_passiveFd == -1)
        throw std::runtime_error("425 Can't open data connection.\r\n");

    constexpr auto enable = 1;
    setsockopt(_passiveFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));

    sockaddr_in addr{};
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port        = htons(0);

    if (bind(_passiveFd, reinterpret_cast<sockaddr *>(&addr),
        sizeof(addr)) == -1) {
        ::close(_passiveFd);
        _passiveFd = -1;
        throw std::runtime_error("425 Can't open data connection.\r\n");
    }

    if (listen(_passiveFd, 1) == -1) {
        ::close(_passiveFd);
        _passiveFd = -1;
        throw std::runtime_error("425 Can't open data connection.\r\n");
    }

    _mode = Mode::PASSIVE;
}

std::string ClientSession::getPassiveModeMessage() const
{
    sockaddr_in addr{};
    socklen_t len = sizeof(addr);

    if (_passiveFd == -1 ||
        getsockname(_passiveFd, reinterpret_cast<sockaddr *>(&addr), &len) == -
        1) {
        throw std::runtime_error("425 Can't open data connection.\r\n");
    }

    const std::string host = _socket->remoteEndpoint().getHostname() ==
        "127.0.0.1"
        ? "127.0.0.1"
        : "127,0,0,1";

    const uint16_t port = ntohs(addr.sin_port);
    const uint16_t p1   = port / 256;
    const uint16_t p2   = port % 256;

    std::string ip = _socket->remoteEndpoint().getHostname();
    for (char &c: ip) {
        if (c == '.')
            c = ',';
    }

    return "227 Entering Passive Mode (" + ip + "," +
        std::to_string(p1) + "," + std::to_string(p2) + ").\r\n";
}

bool ClientSession::isModeSet() const noexcept
{
    return _mode != Mode::NONE;
}

void ClientSession::listDirectory(const std::vector<std::string> &dirs)
{
    std::vector<std::string> args;
    for (std::size_t i = 1; i < dirs.size(); ++i)
        args.push_back(resolvePath(dirs.at(i)).string());

    const int dataFd = openDataConnection();
    send("150 File status okay; about to open data connection.\r\n");

    const bool success = runLsOnDataSocket(dataFd, args);
    ::close(dataFd);
    resetMode();

    if (!success)
        throw std::runtime_error("451 Requested action aborted.\r\n");

    send("226 Closing data connection.\r\n");
}

void ClientSession::retrieveFile(const std::vector<std::string> &command)
{
    const fs::path target = resolvePath(command.at(1));

    if (!fs::exists(target))
        throw error::NoSuchFileOrDirectory{};
    if (!fs::is_regular_file(target))
        throw error::NotADirectory{};

    const int fileFd = ::open(target.c_str(), O_RDONLY);
    if (fileFd == -1)
        throw std::runtime_error("451 Requested action aborted.\r\n");

    const int dataFd = openDataConnection();
    send("150 File status okay; about to open data connection.\r\n");

    char buffer[4096];
    ssize_t readBytes = 0;
    while ((readBytes = ::read(fileFd, buffer, sizeof(buffer))) > 0) {
        if (::write(dataFd, buffer, static_cast<std::size_t>(readBytes)) == -
            1) {
            ::close(fileFd);
            ::close(dataFd);
            resetMode();
            throw std::runtime_error(
                "426 Connection closed; transfer aborted.\r\n");
        }
    }

    ::close(fileFd);
    ::close(dataFd);
    resetMode();

    if (readBytes == -1)
        throw std::runtime_error("451 Requested action aborted.\r\n");

    send("226 Closing data connection.\r\n");
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
    if (_passiveFd != -1) {
        ::close(_passiveFd);
        _passiveFd = -1;
    }
    _mode = Mode::NONE;
}

int ClientSession::openDataConnection() const
{
    if (_mode == Mode::ACTIVE) {
        auto dataSocket = network::ConnectedSocket{_socket->getIOContext()};
        auto endpoint   = _portRemoteEndpoint;
        dataSocket.connect(endpoint);
        return dataSocket.getFd();
    }

    if (_mode == Mode::PASSIVE) {
        sockaddr_in addr{};
        socklen_t len      = sizeof(addr);
        const int clientFd = accept(_passiveFd,
            reinterpret_cast<sockaddr *>(&addr), &len);
        if (clientFd == -1)
            throw std::runtime_error("425 Can't open data connection.\r\n");
        return clientFd;
    }

    throw std::runtime_error("425 Can't open data connection.\r\n");
}

fs::path ClientSession::resolvePath(const std::string &path) const
{
    const fs::path resolvedRoot = fs::weakly_canonical(_rootDirectory);

    fs::path candidate;
    if (!path.empty() && path[0] == '/') {
        candidate = resolvedRoot / fs::path{path}.relative_path();
    } else {
        candidate = _currentDirectory / fs::path{path};
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

    return resolvedTarget;
}
} // ftp
