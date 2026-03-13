/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** PortCommand
*/

#include "PortCommand.hpp"

#include "ClientSession.hpp"

namespace ftp {
bool PortCommand::operator()(ClientSession &client,
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
        client.setPortRemoteEndpoint(command[1]);
    } catch (const std::exception &e) {
        client.send(ftpMessage(FtpMessageCode::SYNTAX_ERROR, e.what()));
        return false;
    }

    client.send(ftpMessage(FtpMessageCode::OK));
    return true;
}

bool PortCommand::execute(ClientSession &client,
    const std::vector<std::string> &command)
{
    return (*this)(client, command);
}

std::unique_ptr<IFtpCommand> PortCommand::create()
{
    return std::make_unique<PortCommand>();
}
} // ftp