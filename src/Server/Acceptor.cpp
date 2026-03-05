/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Acceptor
*/

#include "Acceptor.hpp"

#include <stdexcept>
#include <sys/socket.h>

#include "ErrorCode.hpp"
#include "IoContext.hpp"

namespace ftp {
Acceptor::Acceptor(const IOContext &ioContext, Endpoint &&endpoint): _endpoint{
    std::move(endpoint)}, _socket{ioContext} /*, _ioContext{ioContext}*/
{
    const auto &address = endpoint.getAddress();
    if (bind(_socket.getFd(), reinterpret_cast<const sockaddr *>(&address),
        sizeof(address)) == -1)
        throw std::runtime_error{"bind() failed"};

    if (listen(_socket.getFd(), SOMAXCONN) == -1)
        throw std::runtime_error{"listen() failed"};
}

int Acceptor::getSocketFd() const noexcept
{
    return _socket.getFd();
}

void Acceptor::asyncAccept(const ConnectionHandler &handler)
{
    _handler = handler;
}

void Acceptor::handleNewConnection() const
{
    if (!_handler)
        return;
    if (_connectionCount >= _maxConnection) {
        _handler(AcceptorErrorCode::CONNECTION_LIMIT_REACHED, Socket());
        return;
    }

    Socket socket{};
    socket.connect(Endpoint{_socket.getFd()});
    _handler(std::error_code{}, socket);
}
} // ftp
