/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** ClientSession
*/

#ifndef MYFTP_CLIENT_SESSION_HPP
#define MYFTP_CLIENT_SESSION_HPP
#include <memory>

#include "ConnectedSocket.hpp"

namespace ftp {
class ClientSession {
public:
    explicit ClientSession(const std::shared_ptr<ConnectedSocket> &socket);

    void start();

    void doRead();

private:
    std::shared_ptr<ConnectedSocket> _socket;
    std::string _buffer;
    utils::Logger _logger{"CONNECTED-CLIENT", ULogLevel::INFO, true};
};
} // ftp

#endif //MYFTP_CLIENT_SESSION_HPP
