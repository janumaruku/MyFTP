/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** AccessDenied
*/

#include "AccessDenied.hpp"

namespace ftp {
namespace error {
AccessDenied::AccessDenied()
{
    _message = "550 Access Denied";
}
} // error
} // ftp