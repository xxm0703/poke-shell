#include "shell_ui/title.hh"

#include <cstring>
#include <ncurses.h>

extern bool colored;

namespace terminal_user_interface {
    namespace shell_ui {
        namespace {
            const unsigned short int title_rows = 6;
            const unsigned short int title_row_len = 81;
            const char title[title_rows][title_row_len] = {
                ".------..------..------..------..------..------..------..------..------..------.",
                "|P.--. ||O.--. ||K.--. ||E.--. ||-.--. ||S.--. ||H.--. ||E.--. ||L.--. ||L.--. |",
                "| :/\\: || :/\\: || :/\\: || (\\/) || (\\/) || :/\\: || :/\\: || (\\/) || :/\\: || :/\\: |",
                "| (__) || :\\/: || :\\/: || :\\/: || :\\/: || :\\/: || (__) || :\\/: || (__) || (__) |",
                "| '--'P|| '--'O|| '--'K|| '--'E|| '--'-|| '--'S|| '--'H|| '--'E|| '--'L|| '--'L|",
                "`------'`------'`------'`------'`------'`------'`------'`------'`------'`------'"
            };
            const unsigned short int card_len = 8;
            const unsigned short int upper_letter_index = 1;
            const unsigned short int lower_letter_index = 6;
        }  // private namespace

        void mvprintw_title(WINDOW *win, int y, int x) { 
            int ch;
            short int color_pair_id;

            move(y, x);
            for (register unsigned short int i = 0; i < title_rows; ++i) {
                if (i == 1 || i == title_rows - 2) {
                    for (register unsigned short int j = 0; j < title_row_len - 1; ++j) {
                        ch = title[i][j];
                        if (colored && (j % card_len == upper_letter_index 
                                    || j % card_len == lower_letter_index)) {
                            ch |= A_BOLD;  // bold title letter
                            color_pair_id = 1;
                            // use color pair for title letter
                            attron(COLOR_PAIR(color_pair_id));
                            addch(ch);
                            attroff(COLOR_PAIR(color_pair_id));
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

