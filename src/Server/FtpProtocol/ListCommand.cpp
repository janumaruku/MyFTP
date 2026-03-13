/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** ListCommand
*/

#include "ListCommand.hpp"

#include "ClientSession.hpp"

namespace ftp {
bool ListCommand::operator()(ClientSession &client,
    const std::vector<std::string> &command)
{
    if (!client.isLoggedIn()) {
        client.send(ftpMessage(FtpMessageCode::NOT_LOGGED_IN));
        return true;
    }

    if (!client.isModeSet()) {
        client.send(ftpMessage(FtpMessageCode::CANT_ENTER_PASSIVE_MODE));
        return true;
    }

    client.listDirectory(command);
    return true;
}

bool ListCommand::execute(ClientSession &client,
    const std::vector<std::string> &command)
{
    return (*this)(client, command);
}

std::unique_ptr<IFtpCommand> ListCommand::create()
{
    return std::make_unique<ListCommand>();
}
} // ftp