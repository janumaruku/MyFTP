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
    explicit Server(const int &argc, char *argv[]);

    static void help() noexcept;

private:
    utils::Options _options;
};

} // namespace ftp

#endif // MYFTP_SERVER_HPP
