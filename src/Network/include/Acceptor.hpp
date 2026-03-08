/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Acceptor
*/

#ifndef MYFTP_ACCEPTOR_HPP
#define MYFTP_ACCEPTOR_HPP

#include <functional>
#include <memory>
#include <queue>
#include <system_error>

#include "ConnectedSocket.hpp"
#include "Endpoint.hpp"
#include "ListeningSocket.hpp"
#include "Logger.hpp"

namespace ftp {
class Acceptor {
public:
    using ConnectionHandler = std::function<void(std::error_code,
        std::shared_ptr<ConnectedSocket>)>;

    explicit Acceptor(IOContext &ioContext, Endpoint &&endpoint);

    [[nodiscard]] int getSocketFd() const noexcept;

    void asyncAccept(const ConnectionHandler &handler);

private:
    Endpoint _endpoint;
    ListeningSocket _socket;
    std::size_t _maxConnection   = SOMAXCONN;
    std::size_t _connectionCount = 0;
    std::queue<ConnectionHandler> _handlerFunction;
    utils::Logger _logger{"ACCEPTOR", ULogLevel::INFO, true};
    IOContext &_ioContext;

    void handleNewConnection();

    [[nodiscard]] std::shared_ptr<ConnectedSocket> acceptClient() const;
};
} // ftp

#endif //MYFTP_ACCEPTOR_HPP
