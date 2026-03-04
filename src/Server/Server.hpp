/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Server
*/

#ifndef MYFTP_SERVER_HPP
#define MYFTP_SERVER_HPP

#include "Options.hpp"

namespace ftp {

class Server {
public:
    explicit Server(const std::string &port, const std::string &address);

    static void help() noexcept;

private:
};

} // namespace ftp

#endif // MYFTP_SERVER_HPP
