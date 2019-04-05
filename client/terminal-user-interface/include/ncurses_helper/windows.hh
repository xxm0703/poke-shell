#ifndef TERMINAL_USER_INTERFACE__NCURSES_HELPER__WINDOWS_HH
#define TERMINAL_USER_INTERFACE__NCURSES_HELPER__WINDOWS_HH

#include <ncurses.h>

namespace terminal_user_interface {
    namespace ncurses_helper {
        namespace windows {
            unsigned int get_window_height(WINDOW *) noexcept;
            unsigned int get_window_width(WINDOW *) noexcept;
        }  // namespace windows
    }  // namespace ncurses_helper
}  // namespace terminal_user_interface

#endif

