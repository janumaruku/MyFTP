/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** ClientSession
*/

#include "ClientSession.hpp"

#include <cctype>
#include <iostream>

#include "constants.hpp"
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

std::string ClientSession::getCurrentDirectory() const noexcept
{
    const std::string pwd = fs::relative(_currentDirectory, _rootDirectory);

    if (pwd == ".")
        return "/";
    return "/" + pwd;
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
} // ftp
