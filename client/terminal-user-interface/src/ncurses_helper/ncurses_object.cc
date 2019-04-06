#include "ncurses_helper/ncurses_object.hh"

#include <ncurses.h>
#include <stdexcept>

#include "ncurses_helper/windows.hh"
#include "ncurses_helper/ncurses_exception.hh"

namespace terminal_user_interface {
    namespace ncurses_helper {
        NCursesObject::NCursesObject(int height, int width, 
                int start_y, int start_x)
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

        NCursesObject& NCursesObject::move_window(int y, int x) {
            int rc;

            rc = mvwin(win_, y, x);
            if (rc == ERR) throw NCursesException("mvwin", rc);
            refresh_window();
            return *this;
        }

        NCursesObject& NCursesObject::center_window(WINDOW *ref_win, 
                bool should_center_y, bool should_center_x) {
            int y, x;
            int height = getmaxy(win_);
            int width = getmaxx(win_);
            int ref_height = getmaxy(ref_win);
            int ref_width = getmaxx(ref_win);

            if (ref_height < height || ref_width < width)
                throw std::logic_error("reference window dimensions are smaller than this window");

            int ref_start_y, ref_start_x;
            getbegyx(ref_win, ref_start_y, ref_start_x);
            y = should_center_y ? ref_start_y + ref_height / 2 - height / 2 : getbegy(win_);
            x = should_center_x ? ref_start_x + ref_width / 2 - width / 2 : getbegx(win_);
            move_window(y, x);
            return *this;
        }

        NCursesObject& NCursesObject::move_y(int y) {
            move_window(y, getbegx(win_));
            return *this;
        }

        NCursesObject& NCursesObject::offset_y(int y) {
            move_y(getbegy(win_) + y);
            return *this;
        }

        NCursesObject& NCursesObject::center_y(WINDOW *ref_win) {
            center_window(ref_win, true, false);
            return *this;
        }

        NCursesObject& NCursesObject::move_x(int x) {
            move_window(getbegy(win_), x);
            return *this;
        }

        NCursesObject& NCursesObject::offset_x(int x) {
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

