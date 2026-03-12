/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** PwdCommand
*/

#include "PwdCommand.hpp"

#include "ClientSession.hpp"

namespace ftp {
bool PwdCommand::operator()(ClientSession &client,
    const std::vector<std::string> &command)
{
    if (command.size() != 1) {
        client.send(ftpMessage(FtpMessageCode::SYNTAX_ERROR));
        return false;
    }

    if (!client.isLoggedIn()) {
        client.send(ftpMessage(FtpMessageCode::NOT_LOGGED_IN));
        return false;
    }

    client.send(ftpMessage(FtpMessageCode::DIRECTORY_OK,
        "\"" + client.getCurrentDirectory() + "\" is current directory."));
    return true;
}

bool PwdCommand::execute(ClientSession &client,
    const std::vector<std::string> &command)
{
    return (*this)(client, command);
}

std::unique_ptr<IFtpCommand> PwdCommand::create()
{
    return std::make_unique<PwdCommand>();
}
} // ftp
