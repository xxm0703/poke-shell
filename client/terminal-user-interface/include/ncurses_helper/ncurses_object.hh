#ifndef TERMINAL_USER_INTERFACE__NCURSES_HELPER__NCURSES_OBJECT_HH
#define TERMINAL_USER_INTERFACE__NCURSES_HELPER__NCURSES_OBJECT_HH

#include <ncurses.h>
#include "ncurses_helper/windows.hh"

namespace terminal_user_interface {
    namespace ncurses_helper {
        class NCursesObject {
        public:
            explicit NCursesObject(win_size_t, win_size_t, 
                    win_coord_t = 0, win_coord_t = 0);
            virtual ~NCursesObject() noexcept;
            virtual void mvwprint(win_coord_t = 0, win_coord_t = 0) = 0;
            NCursesObject& refresh_window() noexcept;
            NCursesObject& clear_window() noexcept;
            NCursesObject& move_window(win_coord_t, win_coord_t);
            NCursesObject& center_window(WINDOW * = stdscr, bool = true, bool = true);
            NCursesObject& move_y(win_coord_t);
            NCursesObject& offset_y(win_coord_t);
            NCursesObject& center_y(WINDOW * = stdscr);
            NCursesObject& anchor_y(WINDOW * = stdscr);
            NCursesObject& move_x(win_coord_t);
            NCursesObject& offset_x(win_coord_t);
            NCursesObject& center_x(WINDOW * = stdscr);
            NCursesObject& anchor_x(WINDOW * = stdscr);
            WINDOW *get_win() const noexcept;
        private:
            WINDOW *win_;
        };  // class NCursesObject
    }  // namespace ncurses_helper
}  // namespace terminal_user_interface

#endif

