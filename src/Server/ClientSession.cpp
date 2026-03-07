/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** ClientSession
*/

#include "ClientSession.hpp"

#include <cctype>
#include <iostream>

namespace ftp {
ClientSession::ClientSession(const std::shared_ptr<ConnectedSocket> &socket):
    _socket{socket}
{
    _buffer.reserve(1024);
    _logger.start(ULogLevel::ERROR) << "Buffer max size: " << _buffer.capacity()
        << LOG_END;
}

void ClientSession::start()
{
    doRead();
}

void ClientSession::doRead()
{
    _socket->asyncReadSome(_buffer,
        [this](const std::error_code &errCode, const std::size_t &readBytes) {
            if (errCode) {
                std::cerr << errCode.message() << std::endl;
                return;
            }
            if (readBytes == 0) {
                _logger.start(ULogLevel::INFO) << "Connection lost" << LOG_END;
                return;
            }

            std::clog << "Received bytes: " << readBytes << std::endl;
            if (!_buffer.empty() && _buffer.back() == '\n')
                _buffer.pop_back();
            if (!_buffer.empty() && _buffer.back() == '\r')
                _buffer.pop_back();

            std::cout << "Received text: [" << _buffer << "]" << std::endl;

            _socket->syncWrite(std::string{"Hello world\n"},
                [](auto, auto) {});
            doRead();
        });
}
} // ftp
