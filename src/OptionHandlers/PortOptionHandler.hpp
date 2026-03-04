/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** PortOptionHandler
*/

#ifndef MYFTP_PORTOPTIONHANDLER_HPP
#define MYFTP_PORTOPTIONHANDLER_HPP
#include <memory>

#include "IOptionHandler.hpp"

namespace ftp {

class PortOptionHandler: public utils::IOptionHandler {
public:
    PortOptionHandler() = default;

    ~PortOptionHandler() override = default;

    bool operator()(const std::vector<std::string> &args,
        std::vector<std::string> &tempArgs) override;

    std::string getOption() const noexcept override;

    [[nodiscard]] bool hasOption() const noexcept override;

    static std::unique_ptr<IOptionHandler> create();

private:
    bool _hasOption = false;
    std::string _optionValue;
};

} // namespace ftp

#endif // MYFTP_PORTOPTIONHANDLER_HPP
