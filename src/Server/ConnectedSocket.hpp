/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** ConnectedSocket
*/

#ifndef MYFTP_CONNECTEDSOCKET_HPP
#define MYFTP_CONNECTEDSOCKET_HPP
#include "Endpoint.hpp"
#include "Logger.hpp"

namespace ftp {
class IOContext;

class ConnectedSocket {
public:
    explicit ConnectedSocket(IOContext &ioContext);

    explicit ConnectedSocket(IOContext &ioContext, const int &clientFd,
        Endpoint &&endpoint);

    [[nodiscard]] int getFd() const noexcept;

    // void connect(Endpoint &&endpoint);

    [[nodiscard]] const Endpoint &remoteEndpoint() const noexcept;

private:
    int _socketFd = -1;
    Endpoint _endpoint;
    utils::Logger _logger{"CONNECTED-SOCKET", ULogLevel::INFO, true};
};
} // ftp

#endif //MYFTP_CONNECTEDSOCKET_HPP
