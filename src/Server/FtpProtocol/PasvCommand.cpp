/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** PasvCommand
*/

#include "include/PasvCommand.hpp"

#include "ClientSession.hpp"

namespace ftp {
bool PasvCommand::operator()(ClientSession &client,
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
        client.setPassiveMode();
        client.send(client.getPassiveModeMessage());
    } catch (const std::exception &e) {
        client.send(e.what());
        return false;
    }
    return true;
}

bool PasvCommand::execute(ClientSession &client,
    const std::vector<std::string> &command)
{
    return (*this)(client, command);
}

std::unique_ptr<IFtpCommand> PasvCommand::create()
{
    return std::make_unique<PasvCommand>();
}
} // ftp
