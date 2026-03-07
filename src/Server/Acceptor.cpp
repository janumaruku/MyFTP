/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Acceptor
*/

#include "Acceptor.hpp"

#include <iostream>
#include <stdexcept>
#include <sys/socket.h>

#include "ConnectedSocket.hpp"
#include "ErrorCode.hpp"
#include "IoContext.hpp"

namespace ftp {
Acceptor::Acceptor(IOContext &ioContext, Endpoint &&endpoint):
    _endpoint(std::move(endpoint)), _socket(ioContext),
    _ioContext{ioContext}
{
    const auto &address = _endpoint.getAddress();
    if (bind(_socket.getFd(), reinterpret_cast<const sockaddr *>(&address),
        sizeof(address)) == -1)
        throw std::runtime_error{"bind() failed"};
    _logger.start(ULogLevel::DEBUG) << "Acceptor bound to address"
        << LOG_END;

    if (listen(_socket.getFd(), SOMAXCONN) == -1)
        throw std::runtime_error{"listen() failed"};
    _logger.start(ULogLevel::DEBUG) << "Listening on port" << _endpoint.
        getPort() << LOG_END;

    _ioContext.registerNotifier(_socket.getFd(), [this]() {
        handleNewConnection();
    });
}

int Acceptor::getSocketFd() const noexcept
{
    return _socket.getFd();
}

void Acceptor::asyncAccept(const ConnectionHandler &handler)
{
    _handlerFunction.emplace(handler);
}

void Acceptor::handleNewConnection()
{
    if (_handlerFunction.empty())
        return;
    const ConnectionHandler handler = _handlerFunction.front();
    _handlerFunction.pop();
    if (_connectionCount >= _maxConnection) {
        handler(FtpErrorCode::CONNECTION_LIMIT_REACHED, nullptr);
        return;
    }

    try {
        const auto clientSocket = acceptClient();
        _logger.start(ULogLevel::DEBUG) << "Incoming connection" <<
            " from " << clientSocket->remoteEndpoint().getHostname() <<
            utils::Logger::END;
        ++_connectionCount;

        handler(std::error_code{}, clientSocket);
    } catch (const std::exception &exp) {
        _logger.start(ULogLevel::WARNING) <<
            exp.what() << utils::Logger::END;
    }
}

std::shared_ptr<ConnectedSocket> Acceptor::acceptClient() const
{
    sockaddr_in address{};
    socklen_t size     = sizeof(address);
    const int clientFd = accept(_socket.getFd(),
        reinterpret_cast<sockaddr *>(&address), &size);

    if (clientFd == -1)
        throw std::runtime_error("Error accepting connection");

    return std::make_shared<ConnectedSocket>(_ioContext, clientFd,
        Endpoint{address});
}
} // ftp
