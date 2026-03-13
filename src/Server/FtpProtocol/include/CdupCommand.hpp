/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** CdupCommand
*/

#ifndef MYFTP_CDUPCOMMAND_HPP
#define MYFTP_CDUPCOMMAND_HPP

#include <memory>

#include "IFtpCommand.hpp"

namespace ftp {
class CdupCommand: public IFtpCommand {
public:
    CdupCommand() = default;

    ~CdupCommand() override = default;

    bool operator()(ClientSession &client,
        const std::vector<std::string> &command) override;

    bool execute(ClientSession &client,
        const std::vector<std::string> &command) override;

    static std::unique_ptr<IFtpCommand> create();
};
} // ftp

#endif //MYFTP_CDUPCOMMAND_HPP