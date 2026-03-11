/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** UserCommand
*/

#ifndef MYFTP_USERCOMMAND_HPP
#define MYFTP_USERCOMMAND_HPP
#include <memory>

#include "IFtpCommand.hpp"

namespace ftp {
class UserCommand: public IFtpCommand {
public:
    UserCommand() = default;

    ~UserCommand() override = default;

    bool operator()(const ClientSession &client,
        const std::vector<std::string> &command) override;

    bool execute(const ClientSession &client,
        const std::vector<std::string> &command) override;

    static std::unique_ptr<IFtpCommand> create();
};
} // ftp

#endif //MYFTP_USERCOMMAND_HPP
