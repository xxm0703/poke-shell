#ifndef TERMINAL_USER_INTERFACE__NCURSES_HELPER__NCURSES_OBJECT_HH
#define TERMINAL_USER_INTERFACE__NCURSES_HELPER__NCURSES_OBJECT_HH

#include <ncurses.h>

namespace terminal_user_interface {
    namespace ncurses_helper {
        class NCursesObject {
        public:
            explicit NCursesObject(int, int, int = 0, int = 0);
            virtual ~NCursesObject() noexcept;
            virtual void mvwprint(int, int) = 0;
            NCursesObject& refresh_window() noexcept;
            NCursesObject& clear_window() noexcept;
            NCursesObject& move_window(int, int);
            NCursesObject& center_window(WINDOW * = stdscr, bool = true, bool = true);
            NCursesObject& move_y(int);
            NCursesObject& offset_y(int);
            NCursesObject& center_y(WINDOW * = stdscr);
            NCursesObject& move_x(int);
            NCursesObject& offset_x(int);
            NCursesObject& center_x(WINDOW * = stdscr);
            WINDOW *get_win() const noexcept;
        private:
            WINDOW *win_;
        };  // class NCursesObject
    }  // namespace ncurses_helper
}  // namespace terminal_user_interface

#endif

