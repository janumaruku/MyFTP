/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** AddressOptionHandler
*/

#ifndef MYFTP_ADDRESSOPTIONHANDLER_HPP
#define MYFTP_ADDRESSOPTIONHANDLER_HPP

#include <memory>

#include "IOptionHandler.hpp"

namespace ftp {
class AddressOptionHandler: public utils::IOptionHandler {
public:
    AddressOptionHandler() = default;

    ~AddressOptionHandler() override = default;

    bool operator()(const std::vector<std::string> &args,
        std::vector<std::string> &tempArgs) override;

    std::string getOption() const noexcept override;

    [[nodiscard]] bool hasOption() const noexcept override;

    static std::unique_ptr<IOptionHandler> create();

private:
    bool _hasOption = false;
    std::string _address;
};
} // ftp

#endif //MYFTP_ADDRESSOPTIONHANDLER_HPP
