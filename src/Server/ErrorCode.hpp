/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** ErrorCode
*/

#ifndef MYFTP_ERRORCODE_HPP
#define MYFTP_ERRORCODE_HPP

#include <cstdint>
#include <type_traits>
#include <system_error>

enum class FtpErrorCode : uint8_t {
    CONNECTION_LIMIT_REACHED = 1,
    CS_WRITE_ERROR,
    CS_READ_ERROR,
};

template <> struct std::is_error_code_enum<FtpErrorCode>: true_type {};

struct FtpErrorCodeCategory: std::error_category {
    [[nodiscard]] const char *name() const noexcept override;

    [[nodiscard]] std::string message(int errorValue) const override;

    std::error_condition
        default_error_condition(int errorValue) const noexcept override;
};

inline const FtpErrorCodeCategory &ftpCategory() noexcept
{
    static const FtpErrorCodeCategory category{};

    return category;
}

std::error_code make_error_code(FtpErrorCode errCode) noexcept;

#endif //MYFTP_ERRORCODE_HPP
