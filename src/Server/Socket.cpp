/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Socket
*/

#include "Socket.hpp"

#include <stdexcept>
#include <sys/socket.h>

namespace ftp {
Socket::Socket(): _socketFd{socket(AF_INET, SOCK_STREAM, 0)}
{
    if (_socketFd == -1)
        throw std::runtime_error("Socket creation failed");
}

int Socket::getFd() const noexcept
{
    return _socketFd;
}
} // ftp
