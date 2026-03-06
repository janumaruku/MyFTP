/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** IoContext
*/

#ifndef MYFTP_IOCONTEXT_HPP
#define MYFTP_IOCONTEXT_HPP
#include <cstdint>
#include <functional>
#include <poll.h>
#include <system_error>
#include <unordered_map>
#include <vector>

#include "Acceptor.hpp"

namespace ftp {
class IOContext {
public:
    using OnFileDescriptorReady = std::function<void()>;
    using OnAcceptorFdReady     = void(Acceptor::*)();

    IOContext() = default;

    void registerNotifier(const int &fileDescriptor,
        const OnFileDescriptorReady &notifier);

    void run();

private:
    std::vector<pollfd> _pollFds;
    std::unordered_map<int, OnFileDescriptorReady> _notifiers;
};
} // ftp

#endif //MYFTP_IOCONTEXT_HPP
