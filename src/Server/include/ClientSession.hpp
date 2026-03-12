/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** ClientSession
*/

#ifndef MYFTP_CLIENT_SESSION_HPP
#define MYFTP_CLIENT_SESSION_HPP

#include <filesystem>
#include <memory>

#include "ConnectedSocket.hpp"
#include "FtpProtocol.hpp"

namespace fs = std::filesystem;

namespace ftp {
class ClientSession {
public:
    using FtpCommandFactory = designPattern::FactoryTemplate<IFtpCommand,
        std::string>;

    explicit ClientSession(
        const std::shared_ptr<network::ConnectedSocket> &socket,
        FtpProtocol &protocol, const std::string &rootDirectory);

    void start();

    void doRead();

    void send(const std::string &message) const;

    utils::Logger warnLog() noexcept;

    void setUser() noexcept;

    void setPassword() noexcept;

    [[nodiscard]] bool isLoggedIn() const noexcept;

    void closeConnection() const;

    [[nodiscard]] bool isUserSet() const noexcept;

    bool changeDirectory(const std::string &directory);

    [[nodiscard]] std::string getCurrentDirectory() const noexcept;

private:
    std::shared_ptr<network::ConnectedSocket> _socket;
    FtpProtocol &_protocol;
    fs::path _rootDirectory;
    fs::path _currentDirectory;
    std::string _buffer;
    std::string _processedData;
    utils::Logger _logger{"CONNECTED-CLIENT", ULogLevel::INFO, true};
    bool _isUserSet     = false;
    bool _isPasswordSet = false;

    void handleReadData(const size_t &bytes);
};
} // ftp

#endif //MYFTP_CLIENT_SESSION_HPP
