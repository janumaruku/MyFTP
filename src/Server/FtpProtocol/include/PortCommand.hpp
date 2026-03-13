/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** PortCommand
*/

#ifndef MYFTP_PORTCOMMAND_HPP
#define MYFTP_PORTCOMMAND_HPP

#include <memory>

#include "IFtpCommand.hpp"

namespace ftp {
class PortCommand: public IFtpCommand {
public:
    PortCommand() = default;

    ~PortCommand() override = default;

    bool operator()(ClientSession &client,
        const std::vector<std::string> &command) override;

    bool execute(ClientSession &client,
        const std::vector<std::string> &command) override;

    static std::unique_ptr<IFtpCommand> create();
};
} // ftp

#endif //MYFTP_PORTCOMMAND_HPP