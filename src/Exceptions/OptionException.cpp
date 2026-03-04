/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** OptionException
*/

#include "OptionException.hpp"

#include "constants.hpp"
#include "IOptionHandler.hpp"

namespace ftp {
namespace error {
OptionException::OptionException(const std::string &option,
        const std::string &message)
{
    _message = option + ": " + utils::RED + message + utils::RESET;
}

const char *OptionException::what() const noexcept
{
    return _message.c_str();
}
} // namespace error
} // namespace ftp
