#include "shell_ui/title.hh"

#include <ncurses.h>
#include <string>

#include "ncurses_helper/colors.hh"

// both macros must be defined in order to initialize title string array
#define _NROWS 6
#define _ROW_LEN 80

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
            constexpr unsigned short card_len = 8;
            constexpr unsigned short upper_letter_index = 1;
            constexpr unsigned short lower_letter_index = 6;
        }  // unnamed namespace
        const std::string Title::letter_color_pair_name = "title_letter";

        Title::Title(int start_y, int start_x) noexcept 
            : NCursesObject(nrows, row_len, start_y, start_x) {
        }

        void Title::mvwprint(int y, int x) noexcept {
            int ch;
            int color_pair = ncurses_helper::colors::get_color_pair(letter_color_pair_name);
            WINDOW *win = get_win();

            for (register unsigned short i = 0; i < nrows; ++i) {
                wmove(win, y + i, x);
                if (i == 1 || i == nrows - 2) {
                    for (register unsigned short j = 0; j < row_len; ++j) {
                        ch = title[i][j];
                        if (colored && (j % card_len == upper_letter_index 
                                    || j % card_len == lower_letter_index)) {
                            ch |= A_BOLD;  // bold title letter
                            wattron(win, color_pair);  // use color pair for title letter
                            waddch(win, ch);
                            wattroff(win, color_pair);
                        } else {
                            waddch(win, ch);
                        }
                    }
                } else {
                    wprintw(win, title[i]);
                }
            }
            refresh_window();
        }
    }  // namespace shell_ui
}  // namespace terminal_user_interface

