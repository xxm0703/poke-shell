#ifndef TERMINAL_USER_INTERFACE__POKER_API__AUTHENTICATION_HH
#define TERMINAL_USER_INTERFACE__POKER_API__AUTHENTICATION_HH

#include <string>

#include "lib/nlohmann/json/json.hpp"

namespace terminal_user_interface {
    namespace poker_api {
        using url_t = std::string;
        using username_t = std::string;
        using display_name_t = std::string;
        using password_t = std::string;

        nlohmann::json register_user(url_t, username_t, display_name_t, 
                password_t, password_t) noexcept;
    }  // namespace poker_api
}  // namespace terminal_user_interface

#endif

