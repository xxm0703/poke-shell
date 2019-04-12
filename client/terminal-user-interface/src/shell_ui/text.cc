#include "shell_ui/text.hh"

#include <string>

#include "ncurses_helper/windows.hh"
#include "ncurses_helper/ncurses_object.hh"

using terminal_user_interface::ncurses_helper::win_coord_t;
using terminal_user_interface::ncurses_helper::win_size_t;

namespace terminal_user_interface {
    namespace shell_ui {
        Text::Text(const std::string& text, win_coord_t start_y, win_coord_t start_x)
            : NCursesObject(calc_height(text), calc_width(text), start_y, start_x) {
        }

        void Text::mvwprint(win_coord_t y, win_coord_t x) {
            // TODO: implement
        }

        std::string Text::get_text() const noexcept {
            // TODO: implement
            return "";
        }

        win_size_t Text::calc_height(const std::string& text) noexcept {
            // TODO: implement
            return 0;
        }

        win_size_t Text::calc_width(const std::string& text) noexcept {
            // TODO: implement
            return 0;
        }
    }  // namespace shell_ui
}  // namespace terminal_user_interface

