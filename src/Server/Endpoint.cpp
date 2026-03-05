/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Endpoint
*/

#include "Endpoint.hpp"

#include <stdexcept>
#include <utility>
#include <arpa/inet.h>

namespace ftp {
Endpoint::Endpoint(const short &port): _port{port}
{
    _address.sin_family      = AF_INET;
    _address.sin_port        = htons(port);
    _address.sin_addr.s_addr = INADDR_ANY;
}

Endpoint::Endpoint(std::string hostName, const short &port): _port{port},
    _hostName{std::move(hostName)}
{
    _address.sin_family  = AF_INET;
    _address.sin_port    = htons(port);
    const int inetResult = inet_pton(AF_INET, _hostName.c_str(),
        &_address.sin_addr);

    if (inetResult == 0)
        throw std::runtime_error("Invalid network address");
    if (inetResult == -1)
        throw std::runtime_error("Invalid network address family");
}

short Endpoint::getPort() const noexcept
{
    return _port;
}

std::string Endpoint::getIpAddress() const noexcept
{
    return _hostName;
}

sockaddr_in & Endpoint::getAddress() noexcept
{
    return _address;
}
} // ftp
