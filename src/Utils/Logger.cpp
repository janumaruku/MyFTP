/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Logger
*/

#include "Logger.hpp"

#include <iostream>
#include <utility>

#include "constants.hpp"

namespace utils {
const auto Logger::END = EndLogger{};

Logger::Logger(std::string context, const bool &isEnabled): _isEnabled
    {isEnabled}, _context{std::move(context)}/*, _level{Level::INFO}*/
{}

Logger &Logger::operator<<(const EndLogger &)
{
    *_stream << RESET;
    *_stream << std::endl;

    return *this;
}

Logger &Logger::start(const Level &level, const std::string &context)
{
    if (!_isEnabled)
        return *this;

    chooseOutputStream(level);
    setLevelColor(level);

    if (!context.empty())
        *_stream << "[" << context << "] ";
    else
        *_stream << "[" << _context << "] ";

    return *this;
}

void Logger::setLevelColor(const Level &level) const
{
    switch (level) {
    case Level::INFO:
        *_stream << CYAN;
        break;
    case Level::DEBUG:
        *_stream << YELLOW;
        break;
    case Level::ERROR:
        *_stream << RED;
        break;
    case Level::WARNING:
        *_stream << MAGENTA;
        break;
    default:
        break;
    }
}

void Logger::chooseOutputStream(const Level &level)
{
    switch (level) {
    case Level::INFO:
        _stream = &std::cout;
        break;
    case Level::DEBUG:
        _stream = &std::clog;
        break;
    case Level::ERROR:
    case Level::WARNING:
        _stream = &std::cerr;
        break;
    default:
        break;
    }
}
} // utils
