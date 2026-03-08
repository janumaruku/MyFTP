/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** ConnectedSocket
*/

#ifndef MYFTP_CONNECTEDSOCKET_HPP
#define MYFTP_CONNECTEDSOCKET_HPP

#include <functional>
#include <queue>
#include <unistd.h>

#include "Endpoint.hpp"
#include "ErrorCode.hpp"
#include "Logger.hpp"

namespace ftp {
template <typename Buffer>
concept ResizableBuffer = std::ranges::sized_range<Buffer> &&
    requires(Buffer buffer)
    {
        buffer.resize(0);
        buffer.data();
    };

class IOContext;
constexpr std::size_t MAX_BUFFER_SIZE = 1024;

class ConnectedSocket {
public:
    using Callback = std::function<void(const std::error_code &,
        const std::size_t &)>;
    using PendingOperation = std::function<void()>;

    explicit ConnectedSocket(IOContext &ioContext);

    explicit ConnectedSocket(IOContext &ioContext, const int &clientFd,
        Endpoint &&endpoint);

    [[nodiscard]] int getFd() const noexcept;

    [[nodiscard]] const Endpoint &remoteEndpoint() const noexcept;

    template <ResizableBuffer Buffer>
    void syncWrite(Buffer buffer, Callback handler)
    {
        auto result = write(_socketFd, buffer.data(), buffer.size());

        if (result == -1)
            handler(FtpErrorCode::CS_WRITE_ERROR, 0);
        else
            handler(std::error_code{}, result);
    }

    template <ResizableBuffer Buffer>
    void asyncReadSome(Buffer &outputBuffer, const Callback handler)
    {
        _handlers.push([this, &outputBuffer, handler]() {
            const ssize_t result = read(_socketFd, outputBuffer.data(),
                outputBuffer.size());

            if (result == -1)
                handler(FtpErrorCode::CS_READ_ERROR, 0);
            else {
                outputBuffer.resize(result);
                handler(std::error_code{}, result);
            }
        });
    }

private:
    // std::array<uint8_t, MAX_BUFFER_SIZE> _buffer;
    int _dummy    = 0;
    int _socketFd = -1;
    Endpoint _endpoint;
    std::queue<PendingOperation> _handlers;
    utils::Logger _logger{"CONNECTED-SOCKET", ULogLevel::INFO, true};

    void handleAsyncOperation();
};
} // ftp

#endif //MYFTP_CONNECTEDSOCKET_HPP
