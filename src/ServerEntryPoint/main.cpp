/*
** EPITECH PROJECT, 2026
** MyFTP
** File description:
** main
*/

#include <exception>
#include <iostream>

#include "ServerEntryPoint.hpp"

int main(const int argc, char *argv[])
{
    // try {
        ftp::ServerEntryPoint server{argc, argv};

        if (!server.run())
            return 84;
    // } catch (const std::exception &err) {
    //     std::cerr << err.what() << std::endl;
    //     return 84;
    // }

    return 0;
}
