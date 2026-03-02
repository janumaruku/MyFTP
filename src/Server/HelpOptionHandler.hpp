/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** HelpOptionHandler
*/

#ifndef MYFTP_HELPOPTIONHANDLER_HPP
#define MYFTP_HELPOPTIONHANDLER_HPP
#include <memory>

#include "../Utils/IOptionHandler.hpp"

namespace ftp {

class HelpOptionHandler: public utils::IOptionHandler {
public:
    HelpOptionHandler() = default;

    ~HelpOptionHandler() override = default;

    bool operator()(const std::vector<std::string> &args,
        std::vector<std::string> &tempArgs) override;

    [[nodiscard]] std::string getOption() const noexcept override;

    static std::unique_ptr<IOptionHandler> create();
};

} // namespace ftp

#endif // MYFTP_HELPOPTIONHANDLER_HPP
