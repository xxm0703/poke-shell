#include "__test/stubs/shell_ui/functional_menu_stub.hh"

#include <string>
#include <vector>
#include <functional>

#include "shell_ui/scene.hh"
#include "ncurses_helper/windows.hh"

using terminal_user_interface::ncurses_helper::win_size_t;
using terminal_user_interface::ncurses_helper::win_coord_t;
using terminal_user_interface::shell_ui::Scene;

namespace terminal_user_interface {
    namespace __test {
        FunctionalMenuStub::FunctionalMenuStub(
                const std::vector<std::function<void(Scene&)>>& functions,
                const std::vector<std::string>& options,
                win_size_t height, win_size_t width,
                win_coord_t start_y, win_coord_t start_x)
            : FunctionalMenu(functions, options, height, width, start_y, start_x) {
        }

        void FunctionalMenuStub::mvwprint(win_coord_t y, win_coord_t x) {
            if (y) {}  // do nothing
            if (x) {}  // do nothing
        }

        win_size_t FunctionalMenuStub::calc_height(win_size_t height, 
                const std::vector<std::string>& options) const noexcept {
            if (options.empty()) {}  // do nothing
            return height;
        }

        win_size_t FunctionalMenuStub::calc_width(win_size_t width,
                const std::vector<std::string>& options) const noexcept {
            if (options.empty()) {}  // do nothing
            return width;
        }
    }  // namespace __test
}  // namespace terminal_user_interface
