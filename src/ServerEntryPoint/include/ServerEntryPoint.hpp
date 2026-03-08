/*
** EPITECH PROJECT, 2026
** MyFTP
** File description:
** ServerEntryPoint
*/

#ifndef MYFTP_SERVERENTRYPOINT_HPP
#define MYFTP_SERVERENTRYPOINT_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include "../../Utils/include/Options.hpp"

namespace ftp {
constexpr auto DO_HELP      = 1;
constexpr auto BAD_OPTIONS  = 0;
constexpr auto GOOD_OPTIONS = 2;

const std::unordered_map<std::string, std::string> ARGUMENTS = {
    {
        "PORT",
        "port number on which the server socket listens"
    },
    {
        "DIRECTORY",
        "path to the home directory for the Anonymous user"
    }
};

const std::unordered_map<std::string, std::string> OPTIONS = {
    {
        "-h",
        "help message"
    },
    {
        "-d path",
        "path to the home directory for the Anonymous user"
    },
    {
        "-p port",
        "port number on which the server socket listens"
    }
};

class ServerEntryPoint {
public:
    explicit ServerEntryPoint(const int &argc, char *argv[]);

    bool run();

    static void help() noexcept;

    static void errorHelp() noexcept;

private:
    std::string _port;
    std::string _address;
    utils::Options _options;
    std::vector<std::string> _args;

    int processArgsByOption();
};

} // namespace ftp

#endif // MYFTP_SERVERENTRYPOINT_HPP
