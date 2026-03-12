/*
** EPITECH PROJECT, 2026
** MyFTP
** File description:
** ServerEntryPoint
*/

#include "Server.hpp"
#include "ServerEntryPoint.hpp"

#include <iomanip>
#include <iostream>
#include <ostream>

#include "constants.hpp"
#include "DirectoryOptionHandler.hpp"
#include "HelpOptionHandler.hpp"
#include "OptionException.hpp"
#include "PortOptionHandler.hpp"

namespace ftp {
ServerEntryPoint::ServerEntryPoint(const int &argc, char *argv[]):
    _options{&argv[1]}
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
        _port           = _args[0];
        _startDirectory = _args[1];
    }

    Server server{_port, _startDirectory};
    server.start();

    return true;
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

    _port           = _options.getOption("-p");
    _startDirectory = _options.getOption("-d");

    if (fs::is_directory(_startDirectory)) {
        std::cerr << _startDirectory << ": " << utils::RED <<
            "no such file or directory" << utils::RESET << std::endl;
        errorHelp();
        return BAD_OPTIONS;
    }

    return GOOD_OPTIONS;
}
} // namespace ftp
