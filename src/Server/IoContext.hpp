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
    using AcceptorHandler = std::function<void(std::error_code)>;
    using SocketHandler   = std::function<void(std::error_code,
        std::vector<uint8_t>, std::size_t)>;

    IOContext() = default;

    void registerAcceptor(const Acceptor &acceptor, AcceptorHandler handler);

    void registerSocket(const Socket &socket, SocketHandler handler);

private:
    std::vector<pollfd> _acceptorFds;
    std::vector<pollfd> _socketFds;
    std::unordered_map<int, AcceptorHandler> _acceptorHandlers;
    std::unordered_map<int, SocketHandler> _socketHandlers;
};
} // ftp

#endif //MYFTP_IOCONTEXT_HPP
