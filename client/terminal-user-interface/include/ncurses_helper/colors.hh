#ifndef TERMINAL_USER_INTERFACE__NCURSES_HELPER__COLORS_HH
#define TERMINAL_USER_INTERFACE__NCURSES_HELPER__COLORS_HH

#include <string>

namespace terminal_user_interface {
    namespace ncurses_helper {
        using color_t = short;
        using color_pair_t = short;

        namespace colors {
            void add_color_pair(const std::string&, color_t, color_t);
            color_pair_t get_color_pair(const std::string&);
            void _flush_color_pair_map() noexcept;
        }  // namespace colors
    }  // namespace ncurses_helper
}  // namespace terminal_user_interface

#endif

