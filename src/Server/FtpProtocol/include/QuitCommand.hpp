/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** QuitCommand
*/

#ifndef MYFTP_QUITCOMMAND_HPP
#define MYFTP_QUITCOMMAND_HPP

#include <memory>

#include "IFtpCommand.hpp"

namespace ftp {
class QuitCommand: public IFtpCommand {
public:
    QuitCommand() = default;

    ~QuitCommand() override = default;

    bool operator()(const ClientSession &client,
        const std::vector<std::string> &command) override;

    bool execute(const ClientSession &client,
        const std::vector<std::string> &command) override;

    static std::unique_ptr<IFtpCommand> create();
};
} // ftp

#endif //MYFTP_QUITCOMMAND_HPP