/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** IFtpCommand
*/

#include "include/IFtpCommand.hpp"

namespace ftp {
std::string IFtpCommand::ftpMessage(const FtpMessageCode &code)
{
    const static std::unordered_map<FtpMessageCode, std::string> ftpMessages = {
        {FtpMessageCode::SERVICE_READY_SOON, "Service ready soon."},
        {FtpMessageCode::DATA_CONNECTION_ALREADY_OPENED,
         "Data connection already open; transfer starting."},
        {FtpMessageCode::OPENING_DATA_CONNECTION,
         "File status okay; about to open data connection."},
        {FtpMessageCode::OK, "Command okay."},
        {FtpMessageCode::HELP_MESSAGE, "Help OK."},
        {FtpMessageCode::SERVICE_READY, "Service ready for new user."},
        {FtpMessageCode::CLOSING_CONNECTION,
         "Service closing control connection."},
        {FtpMessageCode::CLOSING_DATA_CONNECTION, "Closing data connection."},
        {FtpMessageCode::ENTERING_PASSIVE_MODE, "Entering Passive Mode "},
        {FtpMessageCode::LOGGED_IN, "User logged in, proceed."},
        {FtpMessageCode::FILE_ACTION_OK,
         "Requested file action okay, completed."},
        {FtpMessageCode::DIRECTORY_OK, "created."},
        {FtpMessageCode::NEED_PASSWORD, "User name okay, need password."},
        {FtpMessageCode::NEED_ACCOUNT_TO_LOGIN, "Need account for login."},
        {FtpMessageCode::CANT_ENTER_PASSIVE_MODE,
         "Can't open data connection."},
        {FtpMessageCode::CONNECTION_CLOSE_ABORTED,
         "Connection closed; transfer aborted."},
        {FtpMessageCode::ACTION_NOT_TAKEN, "Requested file action not taken."},
        {FtpMessageCode::ABORTED_LOCAL_ERROR, "Requested action aborted."},
        {FtpMessageCode::CANT_ENTER_PASSIVE_MODE,
         "Can't open data connection."},
        {FtpMessageCode::CANT_ENTER_PASSIVE_MODE,
         "Can't open data connection."},
        {FtpMessageCode::COMMAND_NOT_FOUND, "Unknown command."},
        {FtpMessageCode::NOT_LOGGED_IN, "Not Logged In."},
        {FtpMessageCode::SYNTAX_ERROR,
         "Syntax error in parameters or arguments."},
        {FtpMessageCode::COMMAND_NOT_IMPLEMENTED, "Command not implemented."},
        {FtpMessageCode::BAD_SEQUENCE_CMD, "Bad sequence of commands."},
        {FtpMessageCode::DIRECTORY_NOT_OK, "Failed to change directory."}
    };

    std::string message = std::to_string(static_cast<int>(code));
    message.append(" ").append(ftpMessages.at(code)).append("\r\n");

    return message;
}

std::string IFtpCommand::ftpMessage(const FtpMessageCode &code,
    const std::string &message)
{
    return std::string{std::to_string(static_cast<int>(code))} + " " + message +
        "\r\n";
}
} // ftp
