/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** PwdCommand
*/

#ifndef MYFTP_PWDCOMMAND_HPP
#define MYFTP_PWDCOMMAND_HPP

#include <memory>

#include "IFtpCommand.hpp"

namespace ftp {
class PwdCommand: public IFtpCommand {
public:
    PwdCommand() = default;

    ~PwdCommand() override = default;

    bool operator()(ClientSession &client,
        const std::vector<std::string> &command) override;

    bool execute(ClientSession &client,
        const std::vector<std::string> &command) override;

    static std::unique_ptr<IFtpCommand> create();
};
} // ftp

#endif //MYFTP_PWDCOMMAND_HPP