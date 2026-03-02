/*
** EPITECH PROJECT, 2026
** MyFTP
** File description:
** ServerEntryPoint
*/

#include "ServerEntryPoint.hpp"

#include <exception>
#include <iostream>
#include <ostream>

#include "HelpOptionHandler.hpp"

namespace ftp {
ServerEntryPoint::ServerEntryPoint(const int &argc, char *argv[]):
    _server{argc, argv}, _options{argv}
{
    if (argc == 1) {
        std::clog << "From thrown exception" << std::endl;
        Server::help();
        throw std::logic_error("");
    }

    _options.registerOptionHandler<HelpOptionHandler>("-h");

    _options.processArgs();

    if (_options.hasOption("-h"))
        _options.getOption("-h");
}
} // namespace ftp
