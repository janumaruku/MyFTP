/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** ErrorCode
*/

#include "ErrorCode.hpp"

const char * AcceptorErrorCodeCategory::name() const noexcept
{
    return "AcceptorError";
}

std::string AcceptorErrorCodeCategory::message(int ev) const
{
    switch (static_cast<AcceptorErrorCode>(ev)) {
    case AcceptorErrorCode::CONNECTION_LIMIT_REACHED:
        return "Connection limit reached";
    default:
        return "Unknown error";
    }
}

std::error_condition AcceptorErrorCodeCategory::default_error_condition(
    const int ev) const noexcept
{
    return std::error_condition(ev, *this);
}

std::error_code make_error_code(AcceptorErrorCode errCode) noexcept
{
    return {static_cast<int>(errCode), acceptor_category()};
}
