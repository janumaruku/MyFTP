/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** ClientSession
*/

#include "ClientSession.hpp"

#include <cctype>
#include <iostream>

#include "constants.hpp"

namespace ftp {
ClientSession::ClientSession(
    const std::shared_ptr<network::ConnectedSocket> &socket):
    _socket{socket}
{
    _buffer.resize(1024);
}

void ClientSession::start()
{
    doRead();
}

void ClientSession::doRead()
{
    _socket->asyncReadSome(network::Buffer{_buffer},
        [this](const std::error_code &errCode, const std::size_t &readBytes) {
            if (errCode) {
                std::cerr << "Something went wrong while reading from socket: ";
                std::cerr << utils::RED << errCode.message() << utils::RESET <<
                    std::endl;
                return;
            }
            if (readBytes == 0) {
                _logger.start(ULogLevel::INFO) << "Connection lost" << LOG_END;
                return;
            }

            std::clog << "Received bytes: " << readBytes << std::endl;
            std::string message{_buffer.data(), readBytes};

            if (message.back() == '\n')
                message.pop_back();
            if (message.back() == '\r')
                message.pop_back();

            std::cout << "Received text: [" << message << "]" << std::endl;

            _socket->syncWrite(network::Buffer{std::string{"Hello world\r\n"}},
                [](auto, auto) {});
            doRead();
        });
}
} // ftp
