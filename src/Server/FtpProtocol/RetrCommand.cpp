/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** RetrCommand
*/

#include "include/RetrCommand.hpp"

#include "ClientSession.hpp"

namespace ftp {
bool RetrCommand::operator()(ClientSession &client,
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

    if (!client.isModeSet()) {
        client.send(ftpMessage(FtpMessageCode::CANT_ENTER_PASSIVE_MODE));
        return false;
    }

    try {
        client.retrieveFile(command);
    } catch (const std::exception &e) {
        client.send(e.what());
        return false;
    }
    return true;
}

bool RetrCommand::execute(ClientSession &client,
    const std::vector<std::string> &command)
{
    return (*this)(client, command);
}

std::unique_ptr<IFtpCommand> RetrCommand::create()
{
    return std::make_unique<RetrCommand>();
}
} // ftp
