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
#include "FtpProtocol.hpp"

namespace ftp {
class ClientSession {
public:
    using FtpCommandFactory = designPattern::FactoryTemplate<IFtpCommand,
        std::string>;

    explicit ClientSession(
        const std::shared_ptr<network::ConnectedSocket> &socket,
        FtpProtocol &protocol);

    void start();

    void doRead();

    void send(const std::string &message) const;

    utils::Logger warnLog() noexcept;

    void setUser() noexcept;

    void setPassword() noexcept;

    [[nodiscard]] bool isLoggedIn() const noexcept;

    void closeConnection() const;

private:
    std::shared_ptr<network::ConnectedSocket> _socket;
    std::string _buffer;
    std::string _processedData;
    utils::Logger _logger{"CONNECTED-CLIENT", ULogLevel::INFO, true};
    bool _isUserSet     = false;
    bool _isPasswordSet = false;
    FtpProtocol &_protocol;

    void handleReadData(const size_t &bytes);
};
} // ftp

#endif //MYFTP_CLIENT_SESSION_HPP
