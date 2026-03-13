/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** NoSuchFileOrDirectory
*/

#include "NoSuchFileOrDirectory.hpp"

namespace ftp {
namespace error {
NoSuchFileOrDirectory::NoSuchFileOrDirectory()
{
    _message = "550 No such file or directory\r\n";
}
} // error
} // ftp