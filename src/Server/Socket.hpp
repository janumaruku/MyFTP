/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Socket
*/

#ifndef MYFTP_SOCKET_HPP
#define MYFTP_SOCKET_HPP
#include "Endpoint.hpp"
// #include "IoContext.hpp"

namespace ftp {
class IOContext;

class Socket {
public:
    Socket() = default;

    explicit Socket(IOContext ioContext);

    [[nodiscard]] int getFd() const noexcept;

    void connect(Endpoint &&endpoint);

    const Endpoint &remoteEndpoint() const noexcept;

private:
    int _socketFd;
    Endpoint _endpoint;
};
} // ftp

#endif //MYFTP_SOCKET_HPP
