#include "ncurses_helper/windows.hh"

#include <ncurses.h>

namespace terminal_user_interface {
    namespace ncurses_helper {
        namespace windows {
            unsigned int get_window_height(WINDOW *win) noexcept {
                return getmaxy(win) - getbegy(win);
            }

            unsigned int get_window_width(WINDOW *win) noexcept {
                return getmaxx(win) - getbegx(win);
            }
        }  // namespace windows
    }  // namespace ncurses_helper
}  // namespace terminal_user_interface

