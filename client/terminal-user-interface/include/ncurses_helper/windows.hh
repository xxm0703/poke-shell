#ifndef TERMINAL_USER_INTERFACE__NCURSES_HELPER__WINDOWS_HH
#define TERMINAL_USER_INTERFACE__NCURSES_HELPER__WINDOWS_HH

#include <ncurses.h>

namespace terminal_user_interface {
    namespace ncurses_helper {
        using win_coord_t = int;
        using win_size_t = int;
        using cur_coord_t = int;

        win_size_t get_window_height(WINDOW *);
        win_size_t get_window_width(WINDOW *);
        win_coord_t get_window_begy(WINDOW *);
        win_coord_t get_window_begx(WINDOW *);
    }  // namespace ncurses_helper
}  // namespace terminal_user_interface

#endif

