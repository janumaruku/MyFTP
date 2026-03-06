/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** IoContext
*/

#include "IoContext.hpp"

#include <iostream>

namespace ftp {
void IOContext::registerNotifier(const int &fileDescriptor,
    const OnFileDescriptorReady &notifier)
{
    _pollFds.push_back({
        .fd      = fileDescriptor,
        .events  = POLLIN,
        .revents = 0,
    });
    _notifiers[fileDescriptor] = notifier;
}

void IOContext::run()
{
    std::clog << "Start main loop 1" << std::endl;
    while (true) {
        if (poll(_pollFds.data(), _pollFds.size(), 10) == -1)
            throw std::system_error(std::make_error_code(std::errc::timed_out));

        for (const auto &pollFd: _pollFds) {
            if (pollFd.revents & POLLIN) {
                _notifiers[pollFd.fd]();
            }
        }
    }
}
} // ftp
