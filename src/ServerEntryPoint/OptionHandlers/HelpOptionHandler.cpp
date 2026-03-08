/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** HelpOptionHandler
*/

#include "HelpOptionHandler.hpp"

#include <iomanip>
#include <iostream>

#include "OptionException.hpp"

namespace ftp {
bool HelpOptionHandler::operator()(
    const std::vector<std::string> &args, std::vector<std::string> &tempArgs)
{
    if (args[0] != "-h" || args[0] == "--help")
        return false;

    if (args.size() != 1)
        throw utils::OptionException(args[0], "bad formated help option");

    tempArgs.erase(tempArgs.begin());
    _hasOption = true;

    return true;
}

std::string HelpOptionHandler::getOption() const noexcept
{
    help();

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

void HelpOptionHandler::help() noexcept
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
} // namespace ftp
