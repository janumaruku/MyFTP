/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** IoContext
*/

#ifndef MYFTP_IOCONTEXT_HPP
#define MYFTP_IOCONTEXT_HPP

#include <functional>
#include <poll.h>
#include <unordered_map>
#include <vector>

#include "ConnectedSocket.hpp"

namespace network {
class IOContext {
public:
    using OnFileDescriptorReady = std::function<void()>;

    IOContext() = default;

    void registerNotifier(const int &fileDescriptor,
        const OnFileDescriptorReady &notifier);

    void run();

    void unregisterNotifier(const int &socketFd);

private:
    std::vector<pollfd> _pollFds;
    std::unordered_map<int, OnFileDescriptorReady> _notifiers;
};
} // ftp

#endif //MYFTP_IOCONTEXT_HPP
