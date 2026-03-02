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
    if (args.size() != 1)
        throw std::runtime_error("");

    tempArgs.erase(tempArgs.begin());
    return true;
}

std::string HelpOptionHandler::getOption() const noexcept
{
    Server::help();

    return "";
}

std::unique_ptr<utils::IOptionHandler> HelpOptionHandler::create()
{
    return std::make_unique<HelpOptionHandler>();
}
} // namespace ftp
