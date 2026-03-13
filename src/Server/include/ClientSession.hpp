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
    enum class Mode: uint8_t {
        NONE,
        ACTIVE,
        PASSIVE,
    };

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

    void changeDirectory(const std::string &directory);

    void changeDirectory();

    [[nodiscard]] std::string getCurrentDirectory() const noexcept;

    void setPortRemoteEndpoint(const std::string &host);

    bool isModeSet() const noexcept;

    // void startDTP();

    void listDirectory(const std::vector<std::string> &dirs);

    bool runLsOnDataSocket(int dataFd, const std::vector<std::string> &dirs) const;

private:
    std::shared_ptr<network::ConnectedSocket> _socket;
    // network::IOContext &_ioContext;
    FtpProtocol &_protocol;
    fs::path _rootDirectory;
    fs::path _currentDirectory;
    std::string _buffer;
    std::string _processedData;
    utils::Logger _logger{"CONNECTED-CLIENT", ULogLevel::INFO, true};
    bool _isUserSet     = false;
    bool _isPasswordSet = false;
    Mode _mode = Mode::NONE;
    network::Endpoint _portRemoteEndpoint;

    void handleReadData(const size_t &bytes);

    void resetMode() noexcept;
};
} // ftp

#endif //MYFTP_CLIENT_SESSION_HPP
