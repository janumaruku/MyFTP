/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Acceptor
*/

#include "include/Acceptor.hpp"

#include <stdexcept>
#include <sys/socket.h>

#include "ConnectedSocket.hpp"
#include "ErrorCode.hpp"
#include "IoContext.hpp"

namespace network {
Acceptor::Acceptor(IOContext &ioContext, Endpoint &&endpoint):
    _endpoint(std::move(endpoint)), _socket(ioContext),
    _ioContext{ioContext}
{
    const auto &address = _endpoint.getAddress();
    if (bind(_socket.getFd(), reinterpret_cast<const sockaddr *>(&address),
        sizeof(address)) == -1)
        throw std::runtime_error{"bind() failed"};
    _logger.start(ULogLevel::DEBUG) << "Acceptor bound to address"
        << utils::END;

    if (listen(_socket.getFd(), SOMAXCONN) == -1)
        throw std::runtime_error{"listen() failed"};
    _logger.start(ULogLevel::DEBUG) << "Listening on port " << _endpoint.
        getPort() << utils::END;

    _ioContext.registerNotifier(_socket.getFd(), [this]() {
        handleNewConnection();
    });
}

int Acceptor::getSocketFd() const noexcept
{
    return _socket.getFd();
}

void Acceptor::asyncAccept(const ConnectionHandler &handler)
{
    _handlerFunction.emplace(handler);
}

void Acceptor::handleNewConnection()
{
    if (_handlerFunction.empty())
        return;
    const ConnectionHandler handler = _handlerFunction.front();
    _handlerFunction.pop();

    const auto clientSocket = acceptClient();
    if (!clientSocket) {
        handler(getAcceptorErrorCode(errno), clientSocket);
        return;
    }

    _logger.start(ULogLevel::DEBUG) << "Incoming connection" <<
        " from " << clientSocket->remoteEndpoint().getHostname() << utils::END;

    handler(std::error_code{}, clientSocket);
}

FtpErrorCode Acceptor::getAcceptorErrorCode(const int &error)
{
    static const std::unordered_map<int, FtpErrorCode> acceptorErrorCodes = {
        {EAGAIN, FtpErrorCode::RETRY_ACCEPT},
        {EWOULDBLOCK, FtpErrorCode::RETRY_ACCEPT},
        {EBADF, FtpErrorCode::ACCEPT_BAD_FILE_DESCRIPTOR},
        {ECONNABORTED, FtpErrorCode::RETRY_ACCEPT},
        {EFAULT, FtpErrorCode::ACCEPT_BAD_ADDRESS},
        {EINTR, FtpErrorCode::RETRY_ACCEPT},
        {EINVAL, FtpErrorCode::ACCEPT_INVALID_STATE},
        {EMFILE, FtpErrorCode::ACCEPT_RESOURCE_EXHAUSTED},
        {ENFILE, FtpErrorCode::ACCEPT_RESOURCE_EXHAUSTED},
        {ENOBUFS, FtpErrorCode::ACCEPT_RESOURCE_EXHAUSTED},
        {ENOMEM, FtpErrorCode::ACCEPT_RESOURCE_EXHAUSTED},
        {ENOTSOCK, FtpErrorCode::ACCEPT_BAD_FILE_DESCRIPTOR},
        {EOPNOTSUPP, FtpErrorCode::ACCEPT_INVALID_STATE},
        {EPERM, FtpErrorCode::ACCEPT_PERMISSION_DENIED},
        {EPROTO, FtpErrorCode::ACCEPT_PROTOCOL_ERROR},
    };

    return acceptorErrorCodes.at(error);
}

std::shared_ptr<ConnectedSocket> Acceptor::acceptClient() const
{
    sockaddr_in address{};
    socklen_t size     = sizeof(address);
    const int clientFd = accept(_socket.getFd(),
        reinterpret_cast<sockaddr *>(&address), &size);

    if (clientFd == -1) {
        if (getAcceptorErrorCode(errno) == FtpErrorCode::RETRY_ACCEPT)
            return acceptClient();

        return nullptr;
    }

    return std::make_shared<ConnectedSocket>(_ioContext, clientFd,
        Endpoint{address});
}
} // ftp
