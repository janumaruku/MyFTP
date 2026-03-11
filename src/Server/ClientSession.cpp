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

namespace ftp {
ClientSession::ClientSession(
    const std::shared_ptr<network::ConnectedSocket> &socket,
    FtpProtocol &protocol): _socket{socket}, _protocol{protocol}
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
