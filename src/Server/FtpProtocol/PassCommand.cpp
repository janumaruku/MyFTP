/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** PassCommand
*/

#include "PassCommand.hpp"

#include "ClientSession.hpp"

namespace ftp {
bool PassCommand::operator()(ClientSession &client,
    const std::vector<std::string> &command)
{
    if (command.size() > 2) {
        client.send(ftpMessage(FtpMessageCode::SYNTAX_ERROR));
        return false;
    }

    if (command.size() == 2) {
        client.send(ftpMessage(FtpMessageCode::NOT_LOGGED_IN));
        return false;
    }

    if (!client.isUserSet()) {
        client.send(ftpMessage(FtpMessageCode::BAD_SEQUENCE_CMD));
        return false;
    }

    client.setPassword();
    client.send(ftpMessage(FtpMessageCode::LOGGED_IN));
    return true;
}

bool PassCommand::execute(ClientSession &client,
    const std::vector<std::string> &command)
{
    return (*this)(client, command);
}

std::unique_ptr<IFtpCommand> PassCommand::create()
{
    return std::make_unique<PassCommand>();
}
} // ftp