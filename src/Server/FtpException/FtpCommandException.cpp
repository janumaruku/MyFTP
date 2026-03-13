/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** FtpException
*/

#include "include/FtpCommandException.hpp"

namespace ftp {
namespace error {
const char *FtpCommandException::what() const noexcept
{
    return _message.c_str();
}
} // error
} // ftp
