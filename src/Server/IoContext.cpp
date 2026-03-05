/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** IoContext
*/

#include "IoContext.hpp"

namespace ftp {
// void IOContext::registerAcceptor(const Acceptor &acceptor,
//     AcceptorHandler handler)
// {
//     const int fileDescriptor = acceptor.getSocketFd();
//
//     pollfd pollFd = {
//         .fd = fileDescriptor,
//         .events = POLLIN,
//         .revents = 0,
//     };
//
//     _acceptorFds.push_back(pollFd);
//     _acceptorHandlers[fileDescriptor] = handler;
// }
//
// void IOContext::registerSocket(const Socket &socket, SocketHandler handler)
// {
//     const int fileDescriptor = socket.getFd();
//
//     pollfd pollFd = {
//         .fd = fileDescriptor,
//         .events = POLLIN,
//         .revents = 0,
//     };
//
//     _socketFds.push_back(pollFd);
//     _socketHandlers[fileDescriptor] = handler;
// }

void IOContext::registerNotifier(const int &fileDescriptor,
    OnFileDescriptorRead notifier)
{
    _pollFds.push_back({
        .fd      = fileDescriptor,
        .events  = POLLIN,
        .revents = 0,
    });
    _notifiers[fileDescriptor] = notifier;
}
} // ftp
