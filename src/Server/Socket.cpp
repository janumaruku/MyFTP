/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Socket
*/

#include "Socket.hpp"

#include <stdexcept>
#include <sys/socket.h>

#include "IoContext.hpp"

namespace ftp {
Socket::Socket(IOContext /*ioContext*/): _socketFd{socket(AF_INET, SOCK_STREAM, 0)}
{
    if (_socketFd == -1)
        throw std::runtime_error("Socket creation failed");

    // ioContext.registerSocket(*this);
}

int Socket::getFd() const noexcept
{
    return _socketFd;
}

void Socket::connect(Endpoint &&endpoint)
{
    _endpoint = std::move(endpoint);
    _socketFd = _endpoint.getAcceptFd();
}

const Endpoint & Socket::remoteEndpoint() const noexcept
{
    return _endpoint;
}
} // ftp
