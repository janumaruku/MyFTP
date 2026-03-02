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

#include "HelpOptionHandler.hpp"

namespace ftp {
Server::Server(const int &argc, char *argv[]): _options{argv}
{
    // if (argc == 1) {
    //     std::clog << "From thrown exception" << std::endl;
    //     help();
    //     throw std::logic_error("");
    // }
    //
    // _options.registerOptionHandler<HelpOptionHandler>("-h");
    //
    // _options.processArgs();
    //
    // if (_options.hasOption("-h"))
    //     _options.getOption("-h");

}

void Server::help() noexcept
{
    std::cout << "\tHelper message ..." << std::endl;
}
} // namespace ftp
