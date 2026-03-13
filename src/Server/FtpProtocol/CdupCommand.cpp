/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** CdupCommand
*/

#include "CdupCommand.hpp"

#include "ClientSession.hpp"
#include "FtpCommandException.hpp"

namespace ftp {
bool CdupCommand::operator()(ClientSession &client,
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

    try {
        client.changeDirectory();
        client.send(ftpMessage(FtpMessageCode::DIRECTORY_OK,
            "Directory changed successfully."));
    } catch (const error::FtpCommandException &error) {
        client.send(error.what());
    }
    return true;
}

bool CdupCommand::execute(ClientSession &client,
    const std::vector<std::string> &command)
{
    return (*this)(client, command);
}

std::unique_ptr<IFtpCommand> CdupCommand::create()
{
    return std::make_unique<CdupCommand>();
}
} // ftp
