#include "shell_ui/text.hh"

#include <algorithm>
#include <vector>
#include <string>

#include "std_helper/string.hh"
#include "ncurses_helper/windows.hh"
#include "ncurses_helper/ncurses_object.hh"

using terminal_user_interface::ncurses_helper::win_coord_t;
using terminal_user_interface::ncurses_helper::win_size_t;
using terminal_user_interface::ncurses_helper::get_window_height;

namespace terminal_user_interface {
    namespace shell_ui {
        Text::Text(const std::string& text, win_coord_t start_y, win_coord_t start_x)
            : NCursesObject(calc_height(text), calc_width(text), start_y, start_x),
              text_(text) {
        }

        void Text::mvwprint(win_coord_t y, win_coord_t x) {
            if (y) {}  // avoid compiler warning
            if (x) {}  // avoid compiler warning

            WINDOW *win = get_win();
            std::vector<std::string> text_lines = std_helper::split(text_, "\n");
            
            for (register win_size_t row = 0; row < get_window_height(win); ++row) {
                wmove(win, row, 0);
                wprintw(win, "%s", text_lines[row].c_str());
            }
            refresh_window();
        }

        std::string Text::get_text() const noexcept {
            return text_;
        }

        win_size_t Text::calc_height(const std::string& text) noexcept {
            return std::count(text.begin(), text.end(), '\n') + 1;
        }

        win_size_t Text::calc_width(const std::string& text) noexcept {
            std::vector<std::string> text_lines = std_helper::split(text, "\n");
            std::string longest_line = std_helper::get_longest_string(text_lines);

            return longest_line.length();
        }
    }  // namespace shell_ui
}  // namespace terminal_user_interface

