/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Server
*/

#ifndef MYFTP_SERVER_HPP
#define MYFTP_SERVER_HPP

#include "Acceptor.hpp"
#include "ClientSession.hpp"
#include "FtpProtocol.hpp"
#include "IoContext.hpp"
#include "Options.hpp"

namespace ftp {

class Server {
public:
    explicit Server(const std::string &port);

    void start();

private:
    network::IOContext _ioContext{};
    network::Acceptor _acceptor;
    std::vector<ClientSession> _clientSessions;
    utils::Logger _logger{"SERVER", ULogLevel::INFO, true};
    FtpProtocol _protocol;

    void doAccept();
};

} // namespace ftp

#endif // MYFTP_SERVER_HPP
