/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Server
*/

#include "Server.hpp"

#include <iostream>
#include <ostream>

#include "IoContext.hpp"
#include "StringUtils.hpp"

namespace ftp {
Server::Server(const std::string &port): _acceptor{_ioContext,
    Endpoint{utils::StringUtils::stos(port)}}
{}

void Server::start()
{
    _acceptor.asyncAccept([](std::error_code, ConnectedSocket) {
        std::cout << "Server accepted" << std::endl;
    });
    _ioContext.run();
}

void Server::help() noexcept
{
    std::cout << "\tHelper message ..." << std::endl;
}
} // namespace ftp
