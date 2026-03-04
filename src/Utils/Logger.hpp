/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Logger
*/

#ifndef MYFTP_LOGGER_HPP
#define MYFTP_LOGGER_HPP

#include <cstdint>
#include <iostream>
#include <string>

namespace utils {
class Logger {
public:
    enum class Level: std::uint8_t {
        ERROR = 0,
        WARNING,
        INFO,
        DEBUG
    };

    struct EndLogger {};

    static const EndLogger END;

    explicit Logger(std::string context, const bool &isEnabled);

    explicit Logger(const Level &level, std::string context,
        const bool &isEnabled);

    template <typename T>
    Logger &operator<<(const T &value)
    {
        if (!_isEnabled)
            return *this;

        *_stream << value;

        return *this;
    }

    Logger &operator<<(const EndLogger &);

    Logger &start(const std::string &context);

    Logger &start(const Level &level, const std::string &context);

private:
    bool _isEnabled = true;
    std::string _context;
    Level _level;
    std::ostream *_stream = &std::cout;

    void setLevelColor() const;

    void chooseOutputStream();
};
} // utils

#endif //MYFTP_LOGGER_HPP
