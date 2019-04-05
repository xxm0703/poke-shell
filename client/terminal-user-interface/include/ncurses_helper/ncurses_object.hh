#ifndef TERMINAL_USER_INTERFACE__NCURSES_HELPER__NCURSES_OBJECT_HH
#define TERMINAL_USER_INTERFACE__NCURSES_HELPER__NCURSES_OBJECT_HH

#include <ncurses.h>

namespace terminal_user_interface {
    namespace ncurses_helper {
        class NCursesObject {
        public:
            explicit NCursesObject(int, int, int = 0, int = 0) noexcept;
            virtual ~NCursesObject() noexcept;
            virtual void mvwprint(int, int) = 0;
            NCursesObject& refresh_window() noexcept;
            NCursesObject& clear_window() noexcept;
            NCursesObject& move_window(int, int) noexcept;
            NCursesObject& center_window(WINDOW * = stdscr, bool = true, bool = true) noexcept;
            NCursesObject& move_y(int) noexcept; 
            NCursesObject& offset_y(int) noexcept;
            NCursesObject& center_y(WINDOW * = stdscr) noexcept;
            NCursesObject& move_x(int) noexcept;
            NCursesObject& offset_x(int) noexcept;
            NCursesObject& center_x(WINDOW * = stdscr) noexcept;
            WINDOW *get_win() const noexcept;
        private:
            WINDOW *win_;
        };  // class NCursesObject
    }  // namespace ncurses_helper
}  // namespace terminal_user_interface

#endif

