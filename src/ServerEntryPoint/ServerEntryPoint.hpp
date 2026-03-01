/*
** EPITECH PROJECT, 2026
** MyFTP
** File description:
** ServerEntryPoint
*/

#ifndef MYFTP_SERVERENTRYPOINT_HPP
#define MYFTP_SERVERENTRYPOINT_HPP
#include "../Server/Server.hpp"

namespace ftp {

class ServerEntryPoint {
public:
    explicit ServerEntryPoint(const int &argc, char *argv[]);

private:
    Server _server;
};

} // namespace ftp

#endif // MYFTP_SERVERENTRYPOINT_HPP
