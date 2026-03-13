/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** ListCommand
*/

#ifndef MYFTP_LISTCOMMAND_HPP
#define MYFTP_LISTCOMMAND_HPP

#include <memory>

#include "IFtpCommand.hpp"

namespace ftp {
class ListCommand: public IFtpCommand {
public:
    ListCommand() = default;

    ~ListCommand() override = default;

    bool operator()(ClientSession &client,
        const std::vector<std::string> &command) override;

    bool execute(ClientSession &client,
        const std::vector<std::string> &command) override;

    static std::unique_ptr<IFtpCommand> create();
};
} // ftp

#endif //MYFTP_LISTCOMMAND_HPP