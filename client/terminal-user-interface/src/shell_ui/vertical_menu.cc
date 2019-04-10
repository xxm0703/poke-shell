#include "shell_ui/vertical_menu.hh"

#include <string>
#include <vector>

using terminal_user_interface::ncurses_helper::win_size_t;
using terminal_user_interface::ncurses_helper::win_coord_t;
using terminal_user_interface::ncurses_helper::cur_coord_t;

namespace terminal_user_interface {
    namespace shell_ui {
        VerticalMenu::VerticalMenu(const std::vector<std::string>& options,
                win_size_t height, win_size_t width,
                win_coord_t start_y, win_coord_t start_x)
            : NCursesMenuObject(options, 
                    calc_height(height, options), calc_width(width, options),
                    start_y, start_x) {
        }

        void VerticalMenu::mvwprint(cur_coord_t y, cur_coord_t x) {
            // TODO implement
        }

        win_size_t VerticalMenu::calc_height(win_size_t height, 
                const std::vector<std::string>& options) const {
            // TODO implement
            return 0;
        }

        win_size_t VerticalMenu::calc_width(win_size_t width,
                const std::vector<std::string>& options) const {
            // TODO implement
            return 0;
        }
    }  // namespace shell_ui
}  // namespace terminal_user_interface

