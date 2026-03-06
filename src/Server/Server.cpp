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
    _acceptor.asyncAccept(
        [this](std::error_code, ConnectedSocket socket) {
            socket.syncWrite(std::string{"Hello world"},
                [](const std::error_code &, const std::size_t &) {});
            _logger.start(ULogLevel::INFO) << "New connection received from "
                << socket.remoteEndpoint().getHostname() << utils::Logger::END;
            start();
        });
    _ioContext.run();
}

void Server::help() noexcept
{
    std::cout << "\tHelper message ..." << std::endl;
}
} // namespace ftp
