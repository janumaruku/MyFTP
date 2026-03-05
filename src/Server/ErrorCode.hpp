/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** ErrorCode
*/

#ifndef MYFTP_ERRORCODE_HPP
#define MYFTP_ERRORCODE_HPP

#include <type_traits>
#include <system_error>

enum class AcceptorErrorCode : int {
    CONNECTION_LIMIT_REACHED = 1,
};

template <> struct std::is_error_code_enum<AcceptorErrorCode>: true_type {
};

struct AcceptorErrorCodeCategory: std::error_category {
    const char *name() const noexcept override;

    std::string message(int ev) const override;

    std::error_condition
        default_error_condition(int ev) const noexcept override;
};

inline const AcceptorErrorCodeCategory &acceptor_category() noexcept
{
    static const AcceptorErrorCodeCategory category{};

    return category;
}

std::error_code make_error_code(AcceptorErrorCode errCode) noexcept;

#endif //MYFTP_ERRORCODE_HPP
