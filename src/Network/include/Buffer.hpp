/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Buffer
*/

#ifndef MYFTP_BUFFER_HPP
#define MYFTP_BUFFER_HPP

#include <string>
#include <vector>

namespace network {
class Buffer {
public:
    explicit Buffer(const std::string &buffer);

    explicit Buffer(std::string &&buffer);

    explicit Buffer(char *buffer, const std::size_t &size);

    template <typename PodType>
    explicit Buffer(std::vector<PodType> &buffer): _data{buffer.data()},
        _size{buffer.capacity()}
    {}

    template <typename PodType>
    explicit Buffer(std::vector<PodType> &&buffer): _data{buffer.data()},
        _size{buffer.capacity()}
    {}

    template <typename PodType, std::size_t size>
    explicit Buffer(std::array<PodType, size> &buffer): _data{buffer.data()},
        _size{size}
    {}

    template <typename PodType, std::size_t size>
    explicit Buffer(std::array<PodType, size> &&buffer): _data{buffer.data()},
        _size{size}
    {}

    [[nodiscard]] void *data() const noexcept;

    [[nodiscard]] std::size_t size() const noexcept;

private:
    void *_data;
    std::size_t _size;
};
} // ftp

#endif //MYFTP_BUFFER_HPP
