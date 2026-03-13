/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** CwdCommand
*/

#include "CwdCommand.hpp"

#include "ClientSession.hpp"
#include "../FtpException/include/NoSuchFileOrDirectory.hpp"

namespace ftp {
bool CwdCommand::operator()(ClientSession &client,
    const std::vector<std::string> &command)
{
    if (command.size() != 2) {
        client.send(ftpMessage(FtpMessageCode::SYNTAX_ERROR));
        return false;
    }

    if (!client.isLoggedIn()) {
        client.send(ftpMessage(FtpMessageCode::NOT_LOGGED_IN));
        return false;
    }

    try {
        client.changeDirectory(command[1]);
        client.send(ftpMessage(FtpMessageCode::DIRECTORY_OK));
    } catch (const error::FtpCommandException &error) {
        client.send(error.what());
    }
    return true;
}

bool CwdCommand::execute(ClientSession &client,
    const std::vector<std::string> &command)
{
    return (*this)(client, command);
}

std::unique_ptr<IFtpCommand> CwdCommand::create()
{
    return std::make_unique<CwdCommand>();
}
} // ftp