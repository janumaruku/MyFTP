/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Server
*/

#include "Server.hpp"

#include <iostream>
#include <ostream>

#include "StringUtils.hpp"

namespace ftp {
Server::Server(const std::string &port): _acceptor{
    Endpoint{utils::StringUtils::stos(port)}}
{}

void Server::help() noexcept
{
    std::cout << "\tHelper message ..." << std::endl;
}
} // namespace ftp
