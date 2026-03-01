/*
** EPITECH PROJECT, 2026
** MyFTP
** File description:
** ServerEntryPoint
*/

#include "ServerEntryPoint.hpp"

#include <exception>
#include <iostream>
#include <ostream>

namespace ftp {
ServerEntryPoint::ServerEntryPoint(const int &argc, char *argv[]):
    _server{argc, argv}
{
    // try {
    //     _server = Server(argc, argv);
    // } catch (const std::exception &) {
    //     throw;
    // }
}
} // namespace ftp
