/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** StringUtils
*/

#ifndef NANOTEKSPICE_STRINGUTILS_HPP
#define NANOTEKSPICE_STRINGUTILS_HPP

#include <string>
#include <vector>

namespace utils {
class StringUtils {
public:
    static std::string cleanString(const std::string &str) noexcept;

    static std::vector<std::string> split(const std::string &str) noexcept;

    static std::vector<std::string> split(const std::string &str,
        const char &delim);

    static std::string spaces(std::size_t size) noexcept;

    static std::string fillChars(std::size_t size, char character) noexcept;

    static std::size_t beginSpacesCount(const std::string &str);

    static short stos(const std::string &str);

    static std::string toLower(const std::string &value);
};
} // utils

#endif //NANOTEKSPICE_STRINGUTILS_HPP
