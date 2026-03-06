/*
** EPITECH PROJECT, 2026
** MyFTP
** File description:
** ServerEntryPoint
*/

#include "ServerEntryPoint.hpp"

#include <iostream>
#include <ostream>

#include "DirectoryOptionHandler.hpp"
#include "HelpOptionHandler.hpp"
#include "OptionException.hpp"
#include "PortOptionHandler.hpp"

namespace ftp {
ServerEntryPoint::ServerEntryPoint(const int &argc, char *argv[]):
    /*_server{"0"},*/ _options{argv}
{
    if (argc == 1) {
        std::clog << "From thrown exception" << std::endl;
        Server::help();
        throw std::logic_error("");
    }

    for (std::size_t i = 1; argv[i] != nullptr; i++)
        _args.emplace_back(argv[i]);

    _options.registerOptionHandler<HelpOptionHandler>("-h");
    _options.registerOptionHandler<PortOptionHandler>("-p");
    _options.registerOptionHandler<DirectoryOptionHandler>("-d");
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

    if (_options.hasOptions()) {
        if (_options.hasOption("-h")) {
            _options.getOption("-h");
            return true;
        }
        if (!_options.hasOption("-d") || !_options.hasOption("-p")) {
            std::cerr << "Need port (-p) and address (-d)" << std::endl;
            return false;
        }
        _port    = _options.getOption("-p");
        _address = _options.getOption("-d");
    } else {
        if (_args.size() != 2) {
            std::cerr << "Need port and address" << std::endl;
            return false;
        }
        _port = _args[0];
    }

    Server server{_port};
    server.start();

    return true;
}
} // namespace ftp
