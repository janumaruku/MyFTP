/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** FtpProtocol
*/

#include "FtpProtocol.hpp"

#include "ClientSession.hpp"
#include "QuitCommand.hpp"
#include "StringUtils.hpp"
#include "UserCommand.hpp"

namespace ftp {
FtpProtocol::FtpProtocol()
{
    _ftpCommandFactory.registerCreator<UserCommand>("user");
    _ftpCommandFactory.registerCreator<QuitCommand>("quit");
}

void FtpProtocol::handleCommand(ClientSession &client,
    const std::string &command)
{
    const std::vector<std::string> splitCommand =
        utils::StringUtils::split(command);

    try {
        const auto cmd = _ftpCommandFactory.create(
            utils::StringUtils::toLower(splitCommand[0]));

        (*cmd)(client, splitCommand);
    } catch (std::exception &e) {
        client.warnLog() << e.what() << utils::END;
        client.send(IFtpCommand::ftpMessage(FtpMessageCode::COMMAND_NOT_FOUND));
    }
}
} // ftp
