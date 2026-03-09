/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Server
*/

#include "Server.hpp"

#include "IoContext.hpp"
#include "StringUtils.hpp"

namespace ftp {
Server::Server(const std::string &port):
    _acceptor{_ioContext, network::Endpoint{utils::StringUtils::stos(port)}}
{
    _logger.start(ULogLevel::INFO) << "Listening on port " << port << " ..." <<
        utils::END;
}

void Server::start()
{
    doAccept();
    _ioContext.run();
}

void Server::doAccept()
{
    _acceptor.asyncAccept(
        [this](const std::error_code &errCode,
        const std::shared_ptr<network::ConnectedSocket>& socket) {
            if (errCode) {
                _logger.start(ULogLevel::WARNING) << errCode.message() <<
                    utils::END;
                doAccept();
            } else {
                socket->syncWrite(network::Buffer{std::string{"Hello world\r\n"}},
                    [](const std::error_code &, const std::size_t &) {});

                _logger.start(ULogLevel::INFO) << "New connection received from "
                    << socket->remoteEndpoint().getHostname() << utils::Logger::END;

                _clientSessions.emplace_back(socket);
                _clientSessions.back().start();

                doAccept();
            }
        });
}
} // namespace ftp
