/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** NotADirectory
*/

#include "include/NotADirectory.hpp"

namespace ftp {
error::NotADirectory::NotADirectory()
{
    _message = "550 Not a directory.";
}
} // ftp