#include "ncurses_helper/windows.hh"

#include <ncurses.h>
#include "ncurses_helper/exceptions/ncurses_exception.hh"

namespace terminal_user_interface {
    namespace ncurses_helper {
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

        win_coord_t get_window_begy(WINDOW *win) {
            win_coord_t result = getbegy(win);

            if (result == ERR) throw NCursesException("getbegy", ERR);
            return result;
        }

        win_coord_t get_window_begx(WINDOW *win) {
            win_coord_t result = getbegx(win);

            if (result == ERR) throw NCursesException("getbegx", ERR);
            return result;
        }
    }  // namespace ncurses_helper
}  // namespace terminal_user_interface

