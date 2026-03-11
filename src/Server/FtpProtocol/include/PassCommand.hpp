/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** PassCommand
*/

#ifndef MYFTP_PASSCOMMAND_HPP
#define MYFTP_PASSCOMMAND_HPP

#include <memory>

#include "IFtpCommand.hpp"

namespace ftp {
class PassCommand: public IFtpCommand {
public:
    PassCommand() = default;

    ~PassCommand() override = default;

    bool operator()(ClientSession &client,
        const std::vector<std::string> &command) override;

    bool execute(ClientSession &client,
        const std::vector<std::string> &command) override;

    static std::unique_ptr<IFtpCommand> create();
};
} // ftp

#endif //MYFTP_PASSCOMMAND_HPP