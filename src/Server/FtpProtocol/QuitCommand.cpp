/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** QuitCommand
*/

#include "QuitCommand.hpp"

#include "ClientSession.hpp"

namespace ftp {
bool QuitCommand::operator()(ClientSession &client,
    const std::vector<std::string> &command)
{
    if (command.size() != 1) {
        client.send(ftpMessage(FtpMessageCode::SYNTAX_ERROR));
        return false;
    }

    client.send(ftpMessage(FtpMessageCode::CLOSING_CONNECTION));
    client.closeConnection();
    return true;
}

bool QuitCommand::execute(ClientSession &client,
    const std::vector<std::string> &command)
{
    return (*this)(client, command);
}

std::unique_ptr<IFtpCommand> QuitCommand::create()
{
    return std::make_unique<QuitCommand>();
}
} // ftp