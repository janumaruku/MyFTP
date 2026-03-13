/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** PermissionDenied
*/

#include "include/PermissionDenied.hpp"

namespace ftp {
namespace error {
PermissionDenied::PermissionDenied()
{
    _message = "550 permission denied.\r\n";
}
}
} // ftp