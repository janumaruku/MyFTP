/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Acceptor
*/

#include "Acceptor.hpp"

#include <stdexcept>
#include <sys/socket.h>

namespace ftp {
Acceptor::Acceptor(Endpoint &&endpoint): _endpoint{std::move(endpoint)}
{
    const auto &address = endpoint.getAddress();
    if (bind(_socket.getFd(), reinterpret_cast<const sockaddr *>(&address),
        sizeof(address)) == -1)
        throw std::runtime_error{"bind() failed"};

    if (listen(_socket.getFd(), 1) == -1)
        throw std::runtime_error{"listen() failed"};
}
} // ftp
