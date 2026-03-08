/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** HelpOptionHandler
*/

#ifndef MYFTP_HELPOPTIONHANDLER_HPP
#define MYFTP_HELPOPTIONHANDLER_HPP

#include <memory>
#include <unordered_map>

#include "IOptionHandler.hpp"

namespace ftp {
const std::unordered_map<std::string, std::string> ARGUMENTS = {
    {
        "PORT",
        "port number on which the server socket listens"
    },
    {
        "DIRECTORY",
        "path to the home directory for the Anonymous user"
    }
};

const std::unordered_map<std::string, std::string> OPTIONS = {
    {
        "-h",
        "help message"
    },
    {
        "-d path",
        "path to the home directory for the Anonymous user"
    },
    {
        "-p port",
        "port number on which the server socket listens"
    }
};

class HelpOptionHandler: public utils::IOptionHandler {
public:
    HelpOptionHandler() = default;

    ~HelpOptionHandler() override = default;

    bool operator()(const std::vector<std::string> &args,
        std::vector<std::string> &tempArgs) override;

    std::string getOption() const noexcept override;

    [[nodiscard]] bool hasOption() const noexcept override;

    static std::unique_ptr<IOptionHandler> create();

    static void help() noexcept;

private:
    bool _hasOption = false;
};

} // namespace ftp

#endif // MYFTP_HELPOPTIONHANDLER_HPP
