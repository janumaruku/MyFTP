/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Server
*/

#ifndef MYFTP_SERVER_HPP
#define MYFTP_SERVER_HPP

#include "../../Network/include/Acceptor.hpp"
#include "ClientSession.hpp"
#include "../../Network/include/IoContext.hpp"
#include "../../Utils/include/Options.hpp"

namespace ftp {

class Server {
public:
    explicit Server(const std::string &port);

    void start();

    // static void help() noexcept;

private:
    IOContext _ioContext{};
    Acceptor _acceptor;
    std::vector<ClientSession> _clientSessions;
    utils::Logger _logger{"SERVER", ULogLevel::INFO, true};

    void doAccept();
};

} // namespace ftp

#endif // MYFTP_SERVER_HPP
