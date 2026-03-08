/*
** EPITECH PROJECT, 2026
** MyFTP
** File description:
** ServerEntryPoint
*/

#include "../Server/include/Server.hpp"
#include "include/ServerEntryPoint.hpp"

#include <iomanip>
#include <iostream>
#include <ostream>

#include "constants.hpp"
#include "DirectoryOptionHandler.hpp"
#include "HelpOptionHandler.hpp"
#include "PortOptionHandler.hpp"
#include "../Utils/include/OptionException.hpp"

namespace ftp {
ServerEntryPoint::ServerEntryPoint(const int &argc, char *argv[]):
    /*_server{"0"},*/ _options{&argv[1]}
{
    if (argc == 1) {
        std::cerr << utils::RED << argv[0] << ": needs port and path" <<
            utils::RESET << std::endl;
        errorHelp();
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
    std::vector<std::string> unprocessedArgs;
    try {
        unprocessedArgs = _options.processArgs();
    } catch (const utils::OptionException &err) {
        std::cerr << err.what() << std::endl;
        errorHelp();
        return false;
    }

    if (unprocessedArgs.empty()) {
        const int res = processArgsByOption();
        if (res == BAD_OPTIONS || res == DO_HELP)
            return res;
    } else {
        if (_args.size() != 2) {
            std::cerr << "Need port and address" << std::endl;
            errorHelp();
            return false;
        }
        _port = _args[0];
    }

    Server server{_port};
    server.start();

    return true;
}

void ServerEntryPoint::help() noexcept
{
    std::cout << "Usage:" << std::endl;
    std::cout << "  1. ./myftp [PORT] [DIRECTORY]" << std::endl;
    for (const auto &[arg, description]: ARGUMENTS) {
        std::cout << "    " << std::setw(15) << std::left << arg;
        std::cout << description << std::endl;
    }
    std::cout << "\n" << std::endl;

    std::cout << "  2. ./myftp [OPTIONS]" << std::endl;
    for (const auto &[option, description]: OPTIONS) {
        std::cout << "    " << std::setw(15) << std::left << option;
        std::cout << description << std::endl;
    }
}

void ServerEntryPoint::errorHelp() noexcept
{
    std::cerr << "Try ./myftp -h for more information." << std::endl;
}

int ServerEntryPoint::processArgsByOption()
{
    if (_options.hasOption("-h")) {
        _options.getOption("-h");
        return DO_HELP;
    }

    if (!_options.hasOption("-d") || !_options.hasOption("-p")) {
        std::cerr << "Need port (-p) and address (-d)" << std::endl;
        errorHelp();
        return BAD_OPTIONS;
    }

    _port    = _options.getOption("-p");
    _address = _options.getOption("-d");

    return GOOD_OPTIONS;
}
} // namespace ftp
