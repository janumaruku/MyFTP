/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** IFtpCommand
*/

#ifndef MYFTP_IFTPCOMMAND_HPP
#define MYFTP_IFTPCOMMAND_HPP

#include "ConnectedSocket.hpp"

namespace ftp {
class ClientSession;

constexpr std::string USERNAME = "Anonymous";

enum class FtpMessageCode: uint16_t {
    SERVICE_READY_SOON             = 120,
    DATA_CONNECTION_ALREADY_OPENED = 125,
    OPENING_DATA_CONNECTION        = 150,
    OK                             = 200,
    HELP_MESSAGE                   = 214,
    SERVICE_READY                  = 220,
    CLOSING_CONNECTION             = 221,
    CLOSING_DATA_CONNECTION        = 226,
    ENTERING_PASSIVE_MODE          = 227,
    LOGGED_IN                      = 230,
    FILE_ACTION_OK                 = 250,
    DIRECTORY_OK                   = 257,
    NEED_PASSWORD                  = 331,
    NEED_ACCOUNT_TO_LOGIN          = 332,
    CANT_ENTER_PASSIVE_MODE        = 425,
    CONNECTION_CLOSE_ABORTED       = 426,
    ACTION_NOT_TAKEN               = 450,
    ABORTED_LOCAL_ERROR            = 451,
    COMMAND_NOT_FOUND              = 500,
    SYNTAX_ERROR                   = 501,
    COMMAND_NOT_IMPLEMENTED        = 502,
    BAD_SEQUENCE_CMD               = 503,
    NOT_LOGGED_IN                  = 530,
    DIRECTORY_NOT_OK               = 550
};

class IFtpCommand {
public:
    IFtpCommand() = default;

    virtual ~IFtpCommand() = default;

    virtual bool operator()(ClientSession &client,
        const std::vector<std::string> &command) = 0;

    virtual bool execute(ClientSession &client,
        const std::vector<std::string> &command) = 0;

    static std::string ftpMessage(const FtpMessageCode &code);
};
} // ftp

#endif //MYFTP_IFTPCOMMAND_HPP
