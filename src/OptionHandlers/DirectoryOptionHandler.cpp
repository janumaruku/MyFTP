/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** AddressOptionHandler
*/

#include "DirectoryOptionHandler.hpp"

#include "OptionException.hpp"

namespace ftp {
bool DirectoryOptionHandler::operator()(const std::vector<std::string> &,
    std::vector<std::string> &tempArgs)
{
    if (tempArgs.empty())
        return false;

    for (auto itt = tempArgs.begin(); itt != tempArgs.end(); ++itt) {
        if (*itt != "-d" && *itt != "--dir")
            continue;

        try {
            if (itt + 1 == tempArgs.end())
                throw std::invalid_argument("");
        } catch (const std::exception &err) {
            throw error::OptionException("-a", "Need an address");
        }

        _address   = *(itt + 1);
        _hasOption = true;
        tempArgs.erase(itt, itt + 2);

        return true;
    }

    return false;
}

std::string DirectoryOptionHandler::getOption() const noexcept
{
    return _address;
}

bool DirectoryOptionHandler::hasOption() const noexcept
{
    return !_address.empty();
}

std::unique_ptr<utils::IOptionHandler> DirectoryOptionHandler::create()
{
    return std::make_unique<DirectoryOptionHandler>();
}
} // ftp
