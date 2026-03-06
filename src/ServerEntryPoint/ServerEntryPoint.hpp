/*
** EPITECH PROJECT, 2026
** MyFTP
** File description:
** ServerEntryPoint
*/

#ifndef MYFTP_SERVERENTRYPOINT_HPP
#define MYFTP_SERVERENTRYPOINT_HPP

#include "Server.hpp"

namespace ftp {

class ServerEntryPoint {
public:
    explicit ServerEntryPoint(const int &argc, char *argv[]);

    bool run();

private:
    std::string _port;
    std::string _address;
    // Server _server;
    utils::Options _options;
    std::vector<std::string> _args;
};

} // namespace ftp

#endif // MYFTP_SERVERENTRYPOINT_HPP
