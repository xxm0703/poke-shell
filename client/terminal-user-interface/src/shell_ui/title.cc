#include "shell_ui/title.hh"

#include <string>

#include <ncurses.h>
#include "shell_ui/config.hh"
#include "ncurses_helper/colors.hh"
#include "ncurses_helper/windows.hh"

using terminal_user_interface::ncurses_helper::color_pair_t;
using terminal_user_interface::ncurses_helper::win_size_t;
using terminal_user_interface::ncurses_helper::win_coord_t;
using terminal_user_interface::ncurses_helper::cur_coord_t;

namespace terminal_user_interface {
    namespace shell_ui {
        namespace {
            constexpr char title[Title::nrows][Title::row_len+1] = {
                ".------..------..------..------..------..------..------..------..------..------.",
                "|P.--. ||O.--. ||K.--. ||E.--. ||-.--. ||S.--. ||H.--. ||E.--. ||L.--. ||L.--. |",
                "| :/\\: || :/\\: || :/\\: || (\\/) || (\\/) || :/\\: || :/\\: || (\\/) || :/\\: || :/\\: |",
                "| (__) || :\\/: || :\\/: || :\\/: || :\\/: || :\\/: || (__) || :\\/: || (__) || (__) |",
                "| '--'P|| '--'O|| '--'K|| '--'E|| '--'-|| '--'S|| '--'H|| '--'E|| '--'L|| '--'L|",
                "`------'`------'`------'`------'`------'`------'`------'`------'`------'`------'"
            };
            constexpr win_size_t card_len = 8;
            constexpr cur_coord_t upper_letter_index = 1;
            constexpr cur_coord_t lower_letter_index = 6;
        }  // unnamed namespace
        constexpr win_size_t Title::nrows;
        constexpr win_size_t Title::row_len;
        constexpr char Title::letter_color_pair_name[];

        Title::Title(win_coord_t start_y, win_coord_t start_x)
            : NCursesObject(nrows, row_len, start_y, start_x) {
        }

        void Title::mvwprint(cur_coord_t y, cur_coord_t x) {
            if (y) {}  // avoid compiler warnings
            if (x) {}  // avoid compiler warnings

            int ch;
            WINDOW *win = get_win();
            color_pair_t color_pair = config::colored ? ncurses_helper::get_color_pair(
                        letter_color_pair_name) : 0;

            for (register win_size_t row = 0; row < nrows; ++row) {
                wmove(win, row, 0);
                for (register win_size_t col = 0; col < row_len; ++col) {
                    ch = title[row][col];
                    if (config::colored && ((row == 1 || row == nrows - 2)
                            && (col % card_len == upper_letter_index 
                                || col % card_len == lower_letter_index))) {
                        ch |= A_BOLD;  // bold title letter
                        wattron(win, color_pair);  // use color pair for title letter
                    }
                    waddch(win, ch);
                    wattroff(win, color_pair);
                }
            }
            refresh_window();
        }
    }  // namespace shell_ui
}  // namespace terminal_user_interface

