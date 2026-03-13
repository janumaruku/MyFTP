/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** FtpProtocol
*/

#include "FtpProtocol.hpp"

#include <iomanip>

#include "CdupCommand.hpp"
#include "ClientSession.hpp"
#include "CwdCommand.hpp"
#include "ListCommand.hpp"
#include "PassCommand.hpp"
#include "PasvCommand.hpp"
#include "PortCommand.hpp"
#include "PwdCommand.hpp"
#include "QuitCommand.hpp"
#include "RetrCommand.hpp"
#include "StringUtils.hpp"
#include "UserCommand.hpp"

namespace ftp {
FtpProtocol::FtpProtocol()
{
    _ftpCommandFactory.registerCreator<UserCommand>("user");
    _ftpCommandFactory.registerCreator<QuitCommand>("quit");
    _ftpCommandFactory.registerCreator<PassCommand>("pass");
    _ftpCommandFactory.registerCreator<PwdCommand>("pwd");
    _ftpCommandFactory.registerCreator<CwdCommand>("cwd");
    _ftpCommandFactory.registerCreator<CdupCommand>("cdup");
    _ftpCommandFactory.registerCreator<PortCommand>("port");
    _ftpCommandFactory.registerCreator<PasvCommand>("pasv");
    _ftpCommandFactory.registerCreator<ListCommand>("list");
    _ftpCommandFactory.registerCreator<RetrCommand>("retr");
}

void FtpProtocol::handleCommand(ClientSession &client,
    const std::string &command)
{
    const std::vector<std::string> splitCommand =
        utils::StringUtils::split(command);
    if (splitCommand.empty()) {
        client.send(IFtpCommand::ftpMessage(FtpMessageCode::COMMAND_NOT_FOUND));
        return;
    }
    if ("help" == utils::StringUtils::toLower(splitCommand.at(0))) {
        helpMessage(client, splitCommand);
        return;
    }

    try {
        const auto cmd = _ftpCommandFactory.create(
            utils::StringUtils::toLower(splitCommand[0]));

        (*cmd)(client, splitCommand);
    } catch (std::exception &e) {
        client.warnLog() << e.what() << utils::END;
        client.send(IFtpCommand::ftpMessage(FtpMessageCode::COMMAND_NOT_FOUND));
    }
}

void FtpProtocol::helpMessage(const ClientSession &client,
    const std::vector<std::string> &command)
{
    if (command.size() > 1) {
        client.send(IFtpCommand::ftpMessage(FtpMessageCode::SYNTAX_ERROR));
        return;
    }

    std::stringstream message;
    message << "214-Available commands:" << std::endl;
    for (const auto &[cmd, help]: helpMessagesMap()) {
        message << "  " << std::setw(35) << std::left << cmd << ": " << help <<
            std::endl;
    }
    message << "214 Help OK.\r\n";

    client.send(message.str());
}

std::unordered_map<std::string, std::string> FtpProtocol::helpMessagesMap()
{
    static const std::unordered_map<std::string, std::string> helps = {
        {
            "HELP",
            "List available commands.",
        },
        {
            "QUIT",
            "Disconnection."
        },
        {
            "USER <SP> <username> <CRLF>",
            "Specify user for authentication."
        },
        {
            "PASS <SP> <password>",
            "Specify password for authentication."
        },
        {
            "PASV",
            "Enter passive mode."
        },
        {
            "PORT <h1,h2,h3,h4,p1,p2>",
            "Set active mode data endpoint."
        },
        {
            "LIST [path]",
            "List files."
        },
        {
            "RETR <pathname>",
            "Download a file."
        }
    };

    return helps;
}
} // ftp
