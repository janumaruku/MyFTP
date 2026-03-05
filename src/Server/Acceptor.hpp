/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Acceptor
*/

#ifndef MYFTP_ACCEPTOR_HPP
#define MYFTP_ACCEPTOR_HPP
#include "Endpoint.hpp"
#include "Socket.hpp"

namespace ftp {
class Acceptor {
public:
    explicit Acceptor(Endpoint &&endpoint);

    int getSocketFd() const noexcept;

private:
    Endpoint _endpoint;
    Socket _socket;
};
} // ftp

#endif //MYFTP_ACCEPTOR_HPP
