/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** HelpOptionHandler
*/

#include "HelpOptionHandler.hpp"

#include <stdexcept>

#include "Server.hpp"

namespace ftp {
bool HelpOptionHandler::operator()(
    const std::vector<std::string> &args, std::vector<std::string> &tempArgs)
{
    if (args.size() != 1 || args[0] != "-h" || args[0] == "--help")
        throw std::runtime_error("");

    tempArgs.erase(tempArgs.begin());
    _hasOption = true;

    return true;
}

std::string HelpOptionHandler::getOption() const noexcept
{
    Server::help();

    return "";
}
bool HelpOptionHandler::hasOption() const noexcept
{
    return _hasOption;
}

std::unique_ptr<utils::IOptionHandler> HelpOptionHandler::create()
{
    return std::make_unique<HelpOptionHandler>();
}
} // namespace ftp
