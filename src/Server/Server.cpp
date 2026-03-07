/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Server
*/

#include "Server.hpp"

#include <iostream>
#include <ostream>

#include "IoContext.hpp"
#include "StringUtils.hpp"

namespace ftp {
Server::Server(const std::string &port):
    _acceptor{_ioContext, Endpoint{utils::StringUtils::stos(port)}}
{}

void Server::start()
{
    doAccept();
    _ioContext.run();
}

void Server::help() noexcept
{
    std::cout << "\tHelper message ..." << std::endl;
}

void Server::doAccept()
{
    _acceptor.asyncAccept(
        [this](std::error_code, std::shared_ptr<ConnectedSocket> socket) {
            socket->syncWrite(std::string{"Hello world\n"},
                [](const std::error_code &, const std::size_t &) {});
            _logger.start(ULogLevel::INFO) << "New connection received from "
                << socket->remoteEndpoint().getHostname() << utils::Logger::END;
            _clientSessions.emplace_back(socket);
            _clientSessions.back().start();
            start();
        });
}
} // namespace ftp
