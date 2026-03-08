/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** ErrorCode
*/

#include "ErrorCode.hpp"

const char *FtpErrorCodeCategory::name() const noexcept
{
    return "AcceptorError";
}

std::string FtpErrorCodeCategory::message(int errorValue) const
{
    switch (static_cast<FtpErrorCode>(errorValue)) {
    case FtpErrorCode::CONNECTION_LIMIT_REACHED:
        return "Connection limit reached";
    case FtpErrorCode::CS_WRITE_ERROR:
        return "Failed to write to client socket";
    default:
        return "Unknown error";
    }
}

std::error_condition FtpErrorCodeCategory::default_error_condition(
    const int errorValue) const noexcept
{
    return {errorValue, *this};
}

std::error_code make_error_code(FtpErrorCode errCode) noexcept
{
    return {static_cast<int>(errCode), ftpCategory()};
}
