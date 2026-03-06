/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** ConnectedSocket
*/

#include "ConnectedSocket.hpp"

#include <stdexcept>

#include "IoContext.hpp"

namespace ftp {
ConnectedSocket::ConnectedSocket(IOContext &ioContext): _socketFd{
    socket(AF_INET, SOCK_STREAM, 0)}
{
    if (_socketFd == -1)
        throw std::runtime_error("Socket creation failed");
    _logger.start(ULogLevel::DEBUG) << "Connected socket created" << LOG_END;

    ioContext.registerNotifier(_socketFd, [this]() {
        handleAsyncOperation();
    });
}

ConnectedSocket::ConnectedSocket(IOContext &ioContext, const int &clientFd,
    Endpoint &&endpoint): _socketFd{clientFd}, _endpoint{std::move(endpoint)}
{
    _logger.start(ULogLevel::DEBUG) << "Connected socket created" << LOG_END;

    ioContext.registerNotifier(_socketFd, [this]() {
        handleAsyncOperation();
    });
}

int ConnectedSocket::getFd() const noexcept
{
    return _socketFd;
}

const Endpoint &ConnectedSocket::remoteEndpoint() const noexcept
{
    return _endpoint;
}

void ConnectedSocket::handleAsyncOperation()
{
    if (_handlers.empty())
        return;

    const Callback handler = _handlers.front();
    _handlers.pop();

    handler({}, 0);
}
} // ftp
