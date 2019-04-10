#include "ncurses_helper/ncurses_object.hh"

#include <ncurses.h>
#include <stdexcept>

#include "ncurses_helper/ncurses_exception.hh"
#include "ncurses_helper/windows.hh"

using terminal_user_interface::ncurses_helper::win_size_t;
using terminal_user_interface::ncurses_helper::win_coord_t;

namespace terminal_user_interface {
    namespace ncurses_helper {
        NCursesObject::NCursesObject(win_size_t height, win_size_t width, 
                win_coord_t start_y, win_coord_t start_x)
            : win_(newwin(height, width, start_y, start_x)) {
            if (win_ == nullptr)  // window couldn't be created
                 throw NCursesException("newwin", nullptr);
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

        NCursesObject& NCursesObject::move_window(win_coord_t y, win_coord_t x) {
            ncurses_errno_t rc;

            rc = mvwin(win_, y, x);
            if (rc == ERR) throw NCursesException("mvwin", rc);
            refresh_window();
            return *this;
        }

        NCursesObject& NCursesObject::center_window(WINDOW *ref_win, 
                bool should_center_y, bool should_center_x) {
            win_coord_t y, x;
            win_size_t height = windows::get_window_height(win_);
            win_size_t width = windows::get_window_width(win_);
            win_size_t ref_height = windows::get_window_height(ref_win);
            win_size_t ref_width = windows::get_window_width(ref_win);

            if (ref_height < height || ref_width < width)
                throw std::logic_error("reference window dimensions are smaller than this window");

            win_coord_t ref_start_y, ref_start_x;
            getbegyx(ref_win, ref_start_y, ref_start_x);
            y = should_center_y ? ref_start_y + ref_height / 2 - height / 2 : getbegy(win_);
            x = should_center_x ? ref_start_x + ref_width / 2 - width / 2 : getbegx(win_);
            move_window(y, x);
            return *this;
        }

        NCursesObject& NCursesObject::move_y(win_coord_t y) {
            move_window(y, getbegx(win_));
            return *this;
        }

        NCursesObject& NCursesObject::offset_y(win_coord_t y) {
            move_y(getbegy(win_) + y);
            return *this;
        }

        NCursesObject& NCursesObject::center_y(WINDOW *ref_win) {
            center_window(ref_win, true, false);
            return *this;
        }

        NCursesObject& NCursesObject::move_x(win_coord_t x) {
            move_window(getbegy(win_), x);
            return *this;
        }

        NCursesObject& NCursesObject::offset_x(win_coord_t x) {
            move_x(getbegx(win_) + x);
            return *this;
        }

        NCursesObject& NCursesObject::center_x(WINDOW *ref_win) {
            center_window(ref_win, false, true);
            return *this;
        }

        WINDOW *NCursesObject::get_win() const noexcept {
            return win_;
        }
    }  // namespace ncurses_helper
}  // namespace terminal_user_interface

