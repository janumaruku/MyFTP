/*
** EPITECH PROJECT, 2026
** MyFTP
** File description:
** ServerEntryPoint
*/

#include "ServerEntryPoint.hpp"

#include <iostream>
#include <ostream>

#include "HelpOptionHandler.hpp"
#include "OptionException.hpp"
#include "PortOptionHandler.hpp"

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
    _options.registerOptionHandler<PortOptionHandler>("-p");
}
bool ServerEntryPoint::run()
{
    try {
        _options.processArgs();
    } catch (const error::OptionException &err) {
        std::cerr << err.what() << std::endl;
        Server::help();
        return false;
    }

    if (_options.hasOption("-h")) {
        _options.getOption("-h");
        return true;
    }

    if (_options.hasOption("-p")) {
        auto port = _options.getOption("-p");
    }

    return true;
}
} // namespace ftp
