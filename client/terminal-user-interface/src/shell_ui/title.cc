#include "shell_ui/title.hh"

#include <cstring>
#include <ncurses.h>

#include "ncurses_helper/colors.hh"

extern bool colored;

namespace terminal_user_interface {
    namespace shell_ui {
        namespace {
            const unsigned short title_rows = 6;
            const unsigned short title_row_len = 81;
            const char title[title_rows][title_row_len] = {
                ".------..------..------..------..------..------..------..------..------..------.",
                "|P.--. ||O.--. ||K.--. ||E.--. ||-.--. ||S.--. ||H.--. ||E.--. ||L.--. ||L.--. |",
                "| :/\\: || :/\\: || :/\\: || (\\/) || (\\/) || :/\\: || :/\\: || (\\/) || :/\\: || :/\\: |",
                "| (__) || :\\/: || :\\/: || :\\/: || :\\/: || :\\/: || (__) || :\\/: || (__) || (__) |",
                "| '--'P|| '--'O|| '--'K|| '--'E|| '--'-|| '--'S|| '--'H|| '--'E|| '--'L|| '--'L|",
                "`------'`------'`------'`------'`------'`------'`------'`------'`------'`------'"
            };
            const unsigned short card_len = 8;
            const unsigned short upper_letter_index = 1;
            const unsigned short lower_letter_index = 6;
        }  // private namespace

        void mvprintw_title(WINDOW *win, int y, int x) { 
            int ch;
            int color_pair = ncurses_helper::get_color_pair(TITLE_LETTER_COLOR_PAIR_NAME);

            move(y, x);
            for (register unsigned short i = 0; i < title_rows; ++i) {
                if (i == 1 || i == title_rows - 2) {
                    for (register unsigned short j = 0; j < title_row_len - 1; ++j) {
                        ch = title[i][j];
                        if (colored && (j % card_len == upper_letter_index 
                                    || j % card_len == lower_letter_index)) {
                            ch |= A_BOLD;  // bold title letter
                            attron(color_pair);  // use color pair for title letter
                            addch(ch);
                            attroff(color_pair);
                        } else {
                            addch(ch);
                        }
                    }
                } else {
                    printw(title[i]);
                }
                addch('\n');
            }
        }
    }  // namespace shell_ui
}  // namespace terminal_user_interface

