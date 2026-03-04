/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** HelpOptionHandler
*/

#include "HelpOptionHandler.hpp"

#include "OptionException.hpp"
#include "Server.hpp"

namespace ftp {
bool HelpOptionHandler::operator()(
    const std::vector<std::string> &args, std::vector<std::string> &tempArgs)
{
    if (args[0] != "-h" || args[0] == "--help")
        return false;

    if (args.size() != 1)
        throw error::OptionException(args[0], "bad formated help option");

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
