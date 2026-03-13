/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** FtpException
*/

#ifndef MYFTP_FTPEXCEPTION_HPP
#define MYFTP_FTPEXCEPTION_HPP

#include <exception>
#include <string>

namespace ftp {
namespace error {
class FtpCommandException: public std::exception {
public:
    FtpCommandException() = default;

    [[nodiscard]] const char* what() const noexcept override;

protected:
    std::string _message;
};
} // error
} // ftp

#endif //MYFTP_FTPEXCEPTION_HPP