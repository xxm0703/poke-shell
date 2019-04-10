#include "shell_ui/title.hh"

#include <string>

#include <ncurses.h>
#include "ncurses_helper/colors.hh"
#include "ncurses_helper/windows.hh"
#include "ncurses_helper/ncurses_exception.hh"

using terminal_user_interface::ncurses_helper::color_pair_t;
using terminal_user_interface::ncurses_helper::win_size_t;
using terminal_user_interface::ncurses_helper::win_coord_t;
using terminal_user_interface::ncurses_helper::cur_coord_t;
using terminal_user_interface::ncurses_helper::ncurses_errno_t;
using terminal_user_interface::ncurses_helper::NCursesException;

extern bool colored;

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
            : NCursesObject(nrows, row_len + 2, start_y, start_x) {
        }

        void Title::mvwprint(cur_coord_t y, cur_coord_t x) {
            ncurses_errno_t rc;
            int ch;
            WINDOW *win = get_win();
            color_pair_t color_pair = colored ? ncurses_helper::colors::get_color_pair(
                        letter_color_pair_name) : 0;

            for (register win_size_t i = 0; i < nrows; ++i) {
                if (wmove(win, y + i, x) == ERR) break;
                for (register win_size_t j = 0; j < row_len - x; ++j) {
                    ch = title[i][j];
                    if (colored && ((i == 1 || i == nrows - 2)
                            && (j % card_len == upper_letter_index 
                                || j % card_len == lower_letter_index))) {
                        ch |= A_BOLD;  // bold title letter
                        wattron(win, color_pair);  // use color pair for title letter
                    }
                    rc = waddch(win, ch);
                    if (rc == ERR) throw NCursesException("waddch", rc);
                    wattroff(win, color_pair);
                }
            }
            refresh_window();
        }
    }  // namespace shell_ui
}  // namespace terminal_user_interface

