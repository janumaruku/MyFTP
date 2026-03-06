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

#include "ErrorCode.hpp"
#include "IoContext.hpp"

namespace ftp {
Acceptor::Acceptor(IOContext &ioContext, Endpoint &&endpoint):
    _endpoint(std::move(endpoint)), _socket(ioContext), _handler(false)
{
    const auto &address = _endpoint.getAddress();
    if (bind(_socket.getFd(), reinterpret_cast<const sockaddr *>(&address),
        sizeof(address)) == -1)
        throw std::runtime_error{"bind() failed"};

    if (listen(_socket.getFd(), SOMAXCONN) == -1)
        throw std::runtime_error{"listen() failed"};

    ioContext.registerNotifier(_socket.getFd(), [this]() {
        handleNewConnection();
    });
}

int Acceptor::getSocketFd() const noexcept
{
    return _socket.getFd();
}

void Acceptor::asyncAccept(const ConnectionHandler &handler)
{
    std::clog << "Handler registration" << std::endl;
    _handlerFunction = handler;
    _handler         = true;
    std::clog << this << std::endl;
}

void Acceptor::handleNewConnection()
{
    std::clog << "Handling new connection" << std::endl;
    if (!_handlerFunction)
        return;
    std::clog << "Connection handler" << std::endl;
    if (_connectionCount >= _maxConnection) {
        _handlerFunction(AcceptorErrorCode::CONNECTION_LIMIT_REACHED, Socket());
        return;
    }

    Socket clientSocket{};
    try {
        clientSocket.connect(Endpoint{_socket.getFd()});
    } catch (const std::exception &exp) {
        _logger.start(utils::Logger::Level::WARNING) <<
            exp.what() << utils::Logger::END;
    }
    _logger.start(utils::Logger::Level::WARNING) << "Incoming connection" <<
        " from " << clientSocket.remoteEndpoint().getHostname() <<
        utils::Logger::END;
    ++_connectionCount;

    _handlerFunction(std::error_code{}, clientSocket);
}
} // ftp
