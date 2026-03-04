/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** PortOptionHandler
*/

#include "PortOptionHandler.hpp"

#include "OptionException.hpp"

namespace ftp {
bool PortOptionHandler::operator()(
    const std::vector<std::string> &, std::vector<std::string> &tempArgs)
{
    if (tempArgs.empty())
        return false;

    for (auto itt = tempArgs.begin(); itt != tempArgs.end(); ++itt) {
        if (*itt != "-p" && *itt != "--port")
            continue;

        try {
            if (itt + 1 == tempArgs.end())
                throw std::invalid_argument("");
            std::stol(*(itt + 1));
        } catch (const std::exception &err) {
            throw error::OptionException("-p",
                "Need a port number (as an integer)");
        }

        _optionValue = *(itt + 1);
        _hasOption   = true;
        tempArgs.erase(itt, itt + 2);

        return true;
    }

    return false;
}

std::string PortOptionHandler::getOption() const noexcept
{
    return _optionValue;
}

bool PortOptionHandler::hasOption() const noexcept
{
    return _hasOption;
}

std::unique_ptr<utils::IOptionHandler> PortOptionHandler::create()
{
    return std::make_unique<PortOptionHandler>();
}
} // namespace ftp
