/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Endpoint
*/

#ifndef MYFTP_ENDPOINT_HPP
#define MYFTP_ENDPOINT_HPP
#include <string>
#include <netinet/in.h>

namespace ftp {
class Endpoint {
public:
    explicit Endpoint(const short &port);

    explicit Endpoint(std::string hostName, const short &port);

    [[nodiscard]] short getPort() const noexcept;

    [[nodiscard]] std::string getIpAddress() const noexcept;

    sockaddr_in &getAddress() noexcept;

private:
    short _port;
    std::string _hostName;
    sockaddr_in _address{};
};
} // ftp

#endif //MYFTP_ENDPOINT_HPP