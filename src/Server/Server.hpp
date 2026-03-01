/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Server
*/

#ifndef MYFTP_SERVER_HPP
#define MYFTP_SERVER_HPP
#include "../Utils/IOptionHandler.hpp"
#include "../Utils/Options.hpp"

namespace ftp {

class Server {
public:
    explicit Server(const int &argc, char *argv[]);

    // Server() = default;

private:
    utils::Options _options;
    static void help() noexcept;
};

} // namespace ftp

#endif // MYFTP_SERVER_HPP
