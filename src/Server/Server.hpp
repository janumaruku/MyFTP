/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Server
*/

#ifndef MYFTP_SERVER_HPP
#define MYFTP_SERVER_HPP

#include "Acceptor.hpp"
#include "IoContext.hpp"
#include "Options.hpp"

namespace ftp {

class Server {
public:
    // Server() = default;

    explicit Server(const std::string &port);

    void start();

    static void help() noexcept;

private:
    IOContext _ioContext{};
    Acceptor _acceptor;
};

} // namespace ftp

#endif // MYFTP_SERVER_HPP
