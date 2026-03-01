/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Server
*/

#include "Server.hpp"

#include <iostream>
#include <ostream>
#include <stdexcept>

namespace ftp {
Server::Server(const int &argc, char *argv[]): _options{argv}
{
    if (argc == 1) {
        help();
        throw std::logic_error("");
    }
}

void Server::help() noexcept
{
    std::cout << "\tHelper message ..." << std::endl;
}
} // namespace ftp
