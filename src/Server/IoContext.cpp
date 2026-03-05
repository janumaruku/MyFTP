/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** IoContext
*/

#include "IoContext.hpp"

#include <iostream>

#include "constants.hpp"

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

void IOContext::registerNotifier(Acceptor &acceptor,
    const OnAcceptorFdReady &notifier)
{
    _acceptorPollFds.push_back({
        .fd      = acceptor.getSocketFd(),
        .events  = POLLIN,
        .revents = 0,
    });
    _acceptorNotifiers.emplace(acceptor.getSocketFd(),
        std::pair{&acceptor, notifier});
}

void IOContext::run()
{
    std::clog << "Start main loop 1" << std::endl;
    while (true) {
        if (poll(_acceptorPollFds.data(), _acceptorPollFds.size(), 10) == -1)
            throw std::system_error(std::make_error_code(std::errc::timed_out));

        for (const auto &pollFd: _acceptorPollFds) {
            if (pollFd.revents & POLLIN) {
                std::clog << utils::YELLOW << "Hello world" << utils::RESET <<
                    std::endl;
                auto &[acceptor, handler] = _acceptorNotifiers[pollFd.fd];
                (acceptor->*handler)();
            }
        }
    }
}
} // ftp
