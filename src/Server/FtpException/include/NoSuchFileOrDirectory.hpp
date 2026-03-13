/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** NoSuchFileOrDirectory
*/

#ifndef MYFTP_NOSUCHFILEORDIRECTORY_HPP
#define MYFTP_NOSUCHFILEORDIRECTORY_HPP
#include "FtpCommandException.hpp"

namespace ftp {
namespace error {
class NoSuchFileOrDirectory: public FtpCommandException {
public:
    NoSuchFileOrDirectory();
};
} // error
} // ftp

#endif //MYFTP_NOSUCHFILEORDIRECTORY_HPP