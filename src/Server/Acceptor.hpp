/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Acceptor
*/

#ifndef MYFTP_ACCEPTOR_HPP
#define MYFTP_ACCEPTOR_HPP
#include <functional>
#include <system_error>

#include "Endpoint.hpp"
#include "Socket.hpp"

namespace ftp {
class Acceptor {
public:
    using ConnectionHandler = std::function<void(std::error_code, Socket)>;

    explicit Acceptor(IOContext &ioContext, Endpoint &&endpoint);

    int getSocketFd() const noexcept;

    void asyncAccept(const ConnectionHandler &handler);

private:
    Endpoint _endpoint;
    Socket _socket;
    std::size_t _maxConnection   = SOMAXCONN;
    std::size_t _connectionCount = 0;
    ConnectionHandler _handlerFunction;
    bool _handler;
    // IOContext &_ioContext;

    void handleNewConnection();
};
} // ftp

#endif //MYFTP_ACCEPTOR_HPP
