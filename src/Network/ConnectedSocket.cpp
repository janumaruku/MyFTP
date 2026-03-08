/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** ConnectedSocket
*/

#include "ConnectedSocket.hpp"

#include <stdexcept>
#include <unistd.h>

#include "ErrorCode.hpp"
#include "IoContext.hpp"

namespace network {
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

void ConnectedSocket::syncWrite(const Buffer &buffer, Callback handler) const
{
    auto result = write(_socketFd, buffer.data(), buffer.size());

    if (result == -1)
        handler(FtpErrorCode::CS_WRITE_ERROR, 0);
    else
        handler(std::error_code{}, result);
}

void ConnectedSocket::asyncReadSome(const Buffer &outputBuffer,
    Callback handler)
{
    _handlers.push([this, &outputBuffer, handler]() {
        const ssize_t result = read(_socketFd, outputBuffer.data(),
            outputBuffer.size());

        if (result == -1)
            handler(FtpErrorCode::CS_READ_ERROR, 0);
        else {
            handler(std::error_code{}, result);
        }
    });
}

void ConnectedSocket::handleAsyncOperation()
{
    if (_dummy == 0)
        ++_dummy;
    if (_handlers.empty())
        return;

    const PendingOperation handler = _handlers.front();
    _handlers.pop();

    handler();
}
} // ftp
