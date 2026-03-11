/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** FtpProtocol
*/

#ifndef MYFTP_FTPPROTOCOL_HPP
#define MYFTP_FTPPROTOCOL_HPP

// #include "ConnectedSocket.hpp"
#include "FactoryTemplate.hpp"
#include "IFtpCommand.hpp"

namespace ftp {
class FtpProtocol {
public:
    using FtpCommandFactory = designPattern::FactoryTemplate<IFtpCommand,
        std::string>;

    FtpProtocol();

    void handleCommand(ClientSession &client, const std::string &command);

private:
    FtpCommandFactory _ftpCommandFactory;
};
} // ftp

#endif //MYFTP_FTPPROTOCOL_HPP
