/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** PortOptionHandler
*/

#include "PortOptionHandler.hpp"

namespace ftp {
bool PortOptionHandler::operator()(
    const std::vector<std::string> &args, std::vector<std::string> &tempArgs)
{
    if (tempArgs.empty())
        return false;

    for (auto itt = args.begin(); itt != args.end(); ++itt) {
        if (*itt == "-p" || *itt == "--port") {
            if (itt + 1 == args.end())
                throw std::invalid_argument("Port option requires an argument");
            _optionValue = *itt;
            _hasOption = true;
            tempArgs.erase(itt + 1);
            tempArgs.erase(itt);

            return true;
        }
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
