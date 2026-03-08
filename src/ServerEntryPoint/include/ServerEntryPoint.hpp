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

#include "Options.hpp"

namespace ftp {
constexpr auto DO_HELP      = 1;
constexpr auto BAD_OPTIONS  = 0;
constexpr auto GOOD_OPTIONS = 2;

class ServerEntryPoint {
public:
    explicit ServerEntryPoint(const int &argc, char *argv[]);

    bool run();

private:
    std::string _port;
    std::string _address;
    utils::Options _options;
    std::vector<std::string> _args;

    int processArgsByOption();

    static void errorHelp() noexcept;
};

} // namespace ftp

#endif // MYFTP_SERVERENTRYPOINT_HPP
