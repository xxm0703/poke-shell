#include "__test/stubs/ncurses_helper/ncurses_object_stub.hh"

#include "ncurses_helper/windows.hh"
#include "ncurses_helper/ncurses_object.hh"

using terminal_user_interface::ncurses_helper::win_coord_t;
using terminal_user_interface::ncurses_helper::win_size_t;
using terminal_user_interface::ncurses_helper::NCursesObject;

namespace terminal_user_interface {
    namespace __test {
        NCursesObjectStub::NCursesObjectStub(
                win_size_t height, win_size_t width, 
                win_coord_t start_y, win_coord_t start_x)
            : NCursesObject(height, width, start_y, start_x) {
        }

        void NCursesObjectStub::mvwprint(win_coord_t y, win_coord_t x) noexcept {
            if (y) {}  // do nothing
            if (x) {}  // do nothing
        }
    }  // namespace __test
}  // namespace terminal_user_interface

