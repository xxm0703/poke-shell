#include "__test/stubs/ncurses_helper/ncurses_menu_object_stub.hh"

#include <vector>
#include <string>

#include "ncurses_helper/windows.hh"
#include "ncurses_helper/ncurses_menu_object.hh"

using terminal_user_interface::ncurses_helper::win_coord_t;
using terminal_user_interface::ncurses_helper::win_size_t;
using terminal_user_interface::ncurses_helper::NCursesMenuObject;

namespace terminal_user_interface {
    namespace __test {
        NCursesMenuObjectStub::NCursesMenuObjectStub(const std::vector<std::string>& options,
                win_size_t height, win_size_t width, 
                win_coord_t start_y, win_coord_t start_x)
            : NCursesMenuObject(options, 
                    calc_height(height, options), calc_width(width, options), 
                    start_y, start_x) {
        }

        void NCursesMenuObjectStub::mvwprint(win_coord_t y, win_coord_t x) {
            if (y) {}  // do nothing
            if (x) {}  // do nothing
        }

        win_size_t NCursesMenuObjectStub::calc_height(win_size_t height, 
                const std::vector<std::string>& options) const noexcept {
            if (options.empty()) {}  // do nothing
            return height;
        }

        win_size_t NCursesMenuObjectStub::calc_width(win_size_t width,
                const std::vector<std::string>& options) const noexcept {
            if (options.empty()) {}  // do nothing
            return width;
        }
    }  // namespace __test
}  // namespace terminal_user_interface

