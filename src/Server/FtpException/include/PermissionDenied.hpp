/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** PermissionDenied
*/

#ifndef MYFTP_PERMISSIONDENIED_HPP
#define MYFTP_PERMISSIONDENIED_HPP

#include "FtpCommandException.hpp"

namespace ftp {
namespace error {
class PermissionDenied: public FtpCommandException {
public:
    PermissionDenied();
};
}
} // ftp

#endif //MYFTP_PERMISSIONDENIED_HPP