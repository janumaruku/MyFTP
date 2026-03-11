/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** IoContext
*/

#include "IoContext.hpp"

#include <system_error>

namespace network {
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
    while (true) {
        if (poll(_pollFds.data(), _pollFds.size(), 10) == -1)
            throw std::system_error(std::make_error_code(std::errc::timed_out));

        std::size_t itt = 0;
        while (itt < _pollFds.size()) {
            if (_pollFds[itt].revents & POLLIN) {
                _notifiers[_pollFds[itt].fd]();
            }

            ++itt;
        }
    }
}
} // ftp
