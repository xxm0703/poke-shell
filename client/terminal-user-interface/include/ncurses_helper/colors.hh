#ifndef TERMINAL_USER_INTERFACE__NCURSES_HELPER__COLORS_HH
#define TERMINAL_USER_INTERFACE__NCURSES_HELPER__COLORS_HH

#include <string>

namespace terminal_user_interface {
    namespace ncurses_helper {
        namespace colors {
            int add_color_pair(const std::string&, short, short);
            int get_color_pair(const std::string&);
        }  // namespace colors
    }  // namespace ncurses_helper
}  // namespace terminal_user_interface

#endif

