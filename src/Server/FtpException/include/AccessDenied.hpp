/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** AccessDenied
*/

#ifndef MYFTP_ACCESSDENIED_HPP
#define MYFTP_ACCESSDENIED_HPP

#include "FtpCommandException.hpp"

namespace ftp {
namespace error {
class AccessDenied: public FtpCommandException {
public:
    AccessDenied();
};
} // error
} // ftp

#endif //MYFTP_ACCESSDENIED_HPP