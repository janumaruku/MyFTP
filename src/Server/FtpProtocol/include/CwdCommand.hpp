/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** CwdCommand
*/

#ifndef MYFTP_CWDCOMMAND_HPP
#define MYFTP_CWDCOMMAND_HPP

#include <memory>

#include "IFtpCommand.hpp"

namespace ftp {
class CwdCommand: public IFtpCommand {
public:
    CwdCommand() = default;

    ~CwdCommand() override = default;

    bool operator()(ClientSession &client,
        const std::vector<std::string> &command) override;

    bool execute(ClientSession &client,
        const std::vector<std::string> &command) override;

    static std::unique_ptr<IFtpCommand> create();
};
} // ftp

#endif //MYFTP_CWDCOMMAND_HPP