#include "ncurses_helper/ncurses_object.hh"

#include <ncurses.h>

#include "ncurses_helper/windows.hh"

namespace terminal_user_interface {
    namespace ncurses_helper {
        NCursesObject::NCursesObject(int height, int width, 
                int start_y, int start_x) noexcept
            : win_(newwin(height, width, start_y, start_x)) {
        }

        NCursesObject::~NCursesObject() noexcept {
            delwin(win_);
        }

        NCursesObject& NCursesObject::refresh_window() noexcept {
            wrefresh(win_);
            return *this;
        }

        NCursesObject& NCursesObject::clear_window() noexcept {
            wclear(win_);
            refresh_window();
            return *this;
        }

        NCursesObject& NCursesObject::move_window(int y, int x) noexcept {
            mvwin(win_, y, x);
            refresh_window();
            return *this;
        }

        NCursesObject& NCursesObject::center_window(WINDOW *ref_win, 
                bool should_center_y, bool should_center_x) noexcept {
            int y, x;
            int height = windows::get_window_height(win_);
            int width = windows::get_window_width(win_);
            int ref_height = windows::get_window_height(ref_win);
            int ref_width = windows::get_window_width(ref_win);

            y = should_center_y ? ref_height / 2 - height / 2 : getbegy(win_);
            x = should_center_x ? ref_width / 2 - width / 2 : getbegx(win_);
            move_window(y, x);
            return *this;
        }

        NCursesObject& NCursesObject::move_y(int y) noexcept {
            move_window(y, getbegx(win_));
            return *this;
        }

        NCursesObject& NCursesObject::offset_y(int y) noexcept {
            move_y(getbegy(win_) + y);
            return *this;
        }

        NCursesObject& NCursesObject::center_y(WINDOW *ref_win) noexcept {
            center_window(ref_win, true, false);
            return *this;
        }

        NCursesObject& NCursesObject::move_x(int x) noexcept {
            move_window(getbegy(win_), x);
            return *this;
        }

        NCursesObject& NCursesObject::offset_x(int x) noexcept {
            move_x(getbegx(win_) + x);
            return *this;
        }

        NCursesObject& NCursesObject::center_x(WINDOW *ref_win) noexcept {
            center_window(ref_win, false, true);
            return *this;
        }

        WINDOW *NCursesObject::get_win() const noexcept {
            return win_;
        }
    }  // namespace ncurses_helper
}  // namespace terminal_user_interface

