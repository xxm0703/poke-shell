#include "ncurses_helper/windows.hh"

#include <ncurses.h>
#include "ncurses_helper/ncurses_exception.hh"

namespace terminal_user_interface {
    namespace ncurses_helper {
        namespace windows {
            win_size_t get_window_height(WINDOW *win) {
                win_size_t result = getmaxy(win);

                if (result == ERR) throw NCursesException("getmaxy", ERR);
                return result;
            }

            win_size_t get_window_width(WINDOW *win) {
                win_size_t result = getmaxx(win);

                if (result == ERR) throw NCursesException("getmaxx", ERR);
                return result;
            }
        }  // namespace windows
    }  // namespace ncurses_helper
}  // namespace terminal_user_interface

