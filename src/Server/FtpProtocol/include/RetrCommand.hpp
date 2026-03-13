/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** RetrCommand
*/

#ifndef MYFTP_RETRCOMMAND_HPP
#define MYFTP_RETRCOMMAND_HPP

#include <memory>

#include "IFtpCommand.hpp"

namespace ftp {
class RetrCommand: public IFtpCommand {
public:
    RetrCommand() = default;

    ~RetrCommand() override = default;

    bool operator()(ClientSession &client,
        const std::vector<std::string> &command) override;

    bool execute(ClientSession &client,
        const std::vector<std::string> &command) override;

    static std::unique_ptr<IFtpCommand> create();
};
} // ftp

#endif //MYFTP_RETRCOMMAND_HPP
