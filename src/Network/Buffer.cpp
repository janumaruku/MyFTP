/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Buffer
*/

#include "Buffer.hpp"

namespace network {
Buffer::Buffer(const std::string &buffer): _data{
        const_cast<void *>(static_cast<const void *>(buffer.data()))},
    _size{buffer.size()}
{}

Buffer::Buffer(std::string &&buffer): _data{buffer.data()},
    _size{buffer.size()}
{}

Buffer::Buffer(char *buffer, const std::size_t &size): _data{buffer},
    _size{size}
{}

void *Buffer::data() const noexcept
{
    return _data;
}

std::size_t Buffer::size() const noexcept
{
    return _size;
}
} // ftp
