/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** IoContext
*/

#include "IoContext.hpp"

#include <algorithm>
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

void IOContext::unregisterNotifier(const int &socketFd)
{
    const auto pollFd = std::ranges::find_if(_pollFds,
        [&socketFd](const pollfd &fd) {
            return fd.fd == socketFd;
        });

    if (pollFd != _pollFds.end())
        _pollFds.erase(pollFd);

    const auto notifier = _notifiers.find(socketFd);
    if (notifier != _notifiers.end()) {
        _notifiers.erase(notifier);
    }
}
} // ftp
