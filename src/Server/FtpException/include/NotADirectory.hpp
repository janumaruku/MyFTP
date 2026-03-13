/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** NotADirectory
*/

#ifndef MYFTP_NOTADIRECTORY_HPP
#define MYFTP_NOTADIRECTORY_HPP
#include "FtpCommandException.hpp"

namespace ftp {
namespace error {
class NotADirectory: public FtpCommandException {
public:
    NotADirectory();
};
}
} // ftp

#endif //MYFTP_NOTADIRECTORY_HPP