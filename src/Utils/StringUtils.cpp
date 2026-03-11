/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** StringUtils
*/

#include "StringUtils.hpp"

#include <iostream>
#include <limits>
#include <sstream>

namespace utils {
std::string StringUtils::cleanString(const std::string &str) noexcept
{
    std::stringstream stream{str};
    std::string word;
    std::string remaining;

    stream >> word;

    std::getline(stream, remaining);

    if (remaining.back() == '\r')
        remaining.pop_back();

    return word + remaining;
}

std::vector<std::string> StringUtils::split(const std::string &str) noexcept
{
    std::vector<std::string> result;
    std::stringstream stream{str};
    std::string word;

    while (stream >> word)
        result.push_back(word);

    return result;
}

std::vector<std::string> StringUtils::split(const std::string &str,
    const char &delim)
{
    std::vector<std::string> result;
    std::stringstream stream{str};
    std::string word;

    while (std::getline(stream, word, delim)) {
        if (word.at(0) == '#')
            break;
        result.push_back(word);
    }
    return result;
}

std::string StringUtils::spaces(const std::size_t size) noexcept
{
    std::string result;

    for (std::size_t i = 0; i < size; ++i)
        result += " ";

    return result;
}

std::string StringUtils::fillChars(const std::size_t size,
    const char character) noexcept
{
    std::string result;

    for (std::size_t i = 0; i < size; ++i)
        result += character;

    return result;
}

std::size_t StringUtils::beginSpacesCount(const std::string &str)
{
    std::size_t count = 0;

    while (str[count] == ' ' && count < str.size() - 1)
        ++count;

    return count;
}

short StringUtils::stos(const std::string &str)
{
    const int num = std::stoi(str);

    if (num > std::numeric_limits<short>::max() || num < std::numeric_limits<
        short>::min())
        throw std::out_of_range(str + " is out of range of short");

    return static_cast<short>(num);
}

std::string StringUtils::toLower(const std::string &value)
{
    std::string result;

    for (const char &character : value)
        result += std::tolower(character);

    return result;
}
} // utils
