/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** UserCommand
*/

#include "UserCommand.hpp"

#include <memory>

#include "ClientSession.hpp"

namespace ftp {
bool UserCommand::operator()(const ClientSession &client,
    const std::vector<std::string> &command)
{
    if (command.size() > 2) {
        client.send(ftpMessage(FtpMessageCode::SYNTAX_ERROR));
        return false;
    }
    if (command.size() == 1 || (command.size() == 2 && command.at(1) !=
        USERNAME)) {
        client.send(ftpMessage(FtpMessageCode::NOT_LOGGED_IN));
        return false;
    }

    if (client.isLoggedIn()) {
        client.send(ftpMessage(FtpMessageCode::LOGGED_IN));
        return true;
    }

    client.send(ftpMessage(FtpMessageCode::NEED_PASSWORD));
    return true;
}

bool UserCommand::execute(const ClientSession &client,
    const std::vector<std::string> &command)
{
    return (*this)(client, command);
}

std::unique_ptr<IFtpCommand> UserCommand::create()
{
    return std::make_unique<UserCommand>();
}
} // ftp
