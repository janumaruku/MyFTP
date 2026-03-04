/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Socket
*/

#ifndef MYFTP_SOCKET_HPP
#define MYFTP_SOCKET_HPP

namespace ftp {
class Socket {
public:
    Socket();

    [[nodiscard]] int getFd() const noexcept;

private:
    int _socketFd;
};
} // ftp

#endif //MYFTP_SOCKET_HPP