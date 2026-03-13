/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** PasvCommand
*/

#ifndef MYFTP_PASVCOMMAND_HPP
#define MYFTP_PASVCOMMAND_HPP

#include <memory>

#include "IFtpCommand.hpp"

namespace ftp {
class PasvCommand: public IFtpCommand {
public:
    PasvCommand() = default;

    ~PasvCommand() override = default;

    bool operator()(ClientSession &client,
        const std::vector<std::string> &command) override;

    bool execute(ClientSession &client,
        const std::vector<std::string> &command) override;

    static std::unique_ptr<IFtpCommand> create();
};
} // ftp

#endif //MYFTP_PASVCOMMAND_HPP
