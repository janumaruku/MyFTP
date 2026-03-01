/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Options
*/

#include "Options.hpp"

#include <ranges>

namespace utils {
Options::Options(char *argv[])
{
    for (std::size_t i = 0; argv[i] != nullptr; ++i)
        _args.emplace_back(argv[i]);
    _tempArgs = _args;
}

void Options::processArgs()
{
    for (auto &handler: _optionHandlerMap | std::views::values) {
        try {
            (*handler)(_args, _tempArgs);
        } catch (const std::exception &) {
            throw;
        }
    }

    _isProcessed = true;
}

std::string Options::getOption(const std::string &option)
{
    const auto itt = _optionHandlerMap.find(option);

    if (itt == _optionHandlerMap.end())
        throw std::logic_error("Unknown option \"" + option + "\"");

    return itt->second->getOption();
}
} // namespace utils
