#include "shell_ui/vertical_menu.hh"

#include <algorithm>
#include <string>
#include <vector>

#include <ncurses.h>
#include "std_helper/string.hh"
#include "ncurses_helper/windows.hh"
#include "ncurses_helper/ncurses_menu_object.hh"

using terminal_user_interface::ncurses_helper::win_size_t;
using terminal_user_interface::ncurses_helper::win_coord_t;
using terminal_user_interface::ncurses_helper::cur_coord_t;
using terminal_user_interface::ncurses_helper::menu_option_t;
using terminal_user_interface::ncurses_helper::get_window_height;
using terminal_user_interface::ncurses_helper::get_window_width;

namespace terminal_user_interface {
    namespace shell_ui {
        VerticalMenu::VerticalMenu(
                const std::vector<std::function<void(Scene&)>>& functions,
                const std::vector<std::string>& options,
                win_size_t height, win_size_t width,
                win_coord_t start_y, win_coord_t start_x)
            : FunctionalMenu(functions, options, 
                    calc_height(height, options), calc_width(width, options),
                    start_y, start_x) {
        }

        void VerticalMenu::mvwprint(cur_coord_t y, cur_coord_t x) {
            if (y) {}  // avoid compiler warning
            if (x) {}  // avoid compiler warning

            WINDOW *win = get_win();
            const auto& options = get_options();
            size_t current_option_index = 0;
            menu_option_t selected_option = get_selected_option();
            
            for (register win_size_t row = 0; 
                    row < static_cast<win_size_t>(options.size()); 
                    ++row) {
                wmove(win, row, 0);

                const std::string& current_option = options[row];
                win_size_t nempty_spaces = get_window_width(win) - current_option.length();
                std::string padded_option = std_helper::rpad_string(
                        std_helper::lpad_string(current_option,
                            nempty_spaces / 2),
                        nempty_spaces / 2 + current_option.length() % 2);

                // highlight selected option
                if (row == selected_option) wattron(win, A_REVERSE);
                wprintw(win, "%s", padded_option.c_str());
                wattroff(win, A_REVERSE);
                ++current_option_index;  // move on to the next string
            }
            refresh_window();
        }

        win_size_t VerticalMenu::calc_height(win_size_t height, 
                const std::vector<std::string>& options) const {
            win_size_t min_res = options.size();

            return std::max(min_res, height);
        }

        win_size_t VerticalMenu::calc_width(win_size_t width,
                const std::vector<std::string>& options) const {
            win_size_t min_res = std_helper::get_longest_string(options).length();
            win_size_t result = std::max(min_res, width);

            result += result % 2;  // even out the width
            return result;
        }
    }  // namespace shell_ui
}  // namespace terminal_user_interface

