#include "shell_ui/title.hh"

#include <cstring>
#include <ncurses.h>
#include <string>

#include "ncurses_helper/colors.hh"

// both macros must be defined in order to initialize title string array
#define _NROWS 6
#define _ROW_LEN 80

extern bool colored;

namespace terminal_user_interface {
    namespace shell_ui {
        namespace title {
            namespace {
                const char title[_NROWS][_ROW_LEN+1] = {
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
            }  // unnamed namespace

            const unsigned short Title::nrows = _NROWS;
            const unsigned short Title::row_len = _ROW_LEN;
            const std::string Title::letter_color_pair_name = "title_letter";

            Title::Title(int start_y, int start_x) noexcept 
                : win_(newwin(nrows, row_len, start_y, start_x)) {
            }

            Title::~Title(void) noexcept {
                delwin(win_);
            }

            unsigned short Title::get_nrows(void) noexcept {
                return nrows;
            }

            unsigned short Title::get_row_len(void) noexcept  {
                return row_len;
            }

            std::string Title::get_letter_color_pair_name(void) noexcept  {
                return letter_color_pair_name;
            }

            void Title::mvwprint(int y, int x) noexcept {
                int ch;
                int color_pair = ncurses_helper::colors::get_color_pair(letter_color_pair_name);

                for (register unsigned short i = 0; i < nrows; ++i) {
                    wmove(win_, y + i, x);
                    if (i == 1 || i == nrows - 2) {
                        for (register unsigned short j = 0; j < row_len; ++j) {
                            ch = title[i][j];
                            if (colored && (j % card_len == upper_letter_index 
                                        || j % card_len == lower_letter_index)) {
                                ch |= A_BOLD;  // bold title letter
                                wattron(win_, color_pair);  // use color pair for title letter
                                waddch(win_, ch);
                                wattroff(win_, color_pair);
                            } else {
                                waddch(win_, ch);
                            }
                        }
                    } else {
                        wprintw(win_, title[i]);
                    }
                }
                refresh_window();
            }

            Title& Title::refresh_window(void) noexcept {
                wrefresh(win_);
                return *this;
            }

            Title& Title::clear_window(void) noexcept {
                wclear(win_);
                refresh_window();
                return *this;
            }

            Title& Title::move_window(int y, int x) noexcept {
                mvwin(win_, y, x);
                refresh_window();
                return *this;
            }

            Title& Title::center_window(WINDOW *parent_win, bool should_center_y,
                    bool should_center_x) noexcept {
                int parent_height, parent_width;
                int y, x;

                getmaxyx(parent_win, parent_height, parent_width);
                y = should_center_y ? parent_height / 2 - nrows / 2 : getbegy(win_);
                x = should_center_x ? parent_width / 2 - row_len / 2 : getbegx(win_);
                move_window(y, x);
                return *this;
            }

            Title& Title::move_y(int y) noexcept {
                move_window(y, getbegx(win_));
                return *this; 
            }

            Title& Title::offset_y(int y) noexcept {
                move_y(getbegy(win_) + y);
                return *this;
            }

            Title& Title::center_y(WINDOW *parent_win) noexcept {
                center_window(parent_win, true, false);
                return *this;
            }

            Title& Title::move_x(int x) noexcept {
                move_window(getbegy(win_), x);
                return *this; 
            }

            Title& Title::offset_x(int x) noexcept {
                move_x(getcurx(win_) + x);
                return *this;
            }

            Title& Title::center_x(WINDOW *parent_win) noexcept {
                center_window(parent_win, false, true);
                return *this;
            }

            WINDOW *Title::get_win(void) const noexcept {
                return win_;
            }
        }  // namespace title
    }  // namespace shell_ui
}  // namespace terminal_user_interface

#undef _NROWS
#undef _ROW_LEN

