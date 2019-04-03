#ifndef TERMINAL_USER_INTERFACE__SHELL_UI__TITLE_HH
#define TERMINAL_USER_INTERFACE__SHELL_UI__TITLE_HH

#include <ncurses.h>

#define TITLE_LETTER_COLOR_PAIR_NAME "title_letter"

namespace terminal_user_interface {
    namespace shell_ui {
        void mvprintw_title(WINDOW *, int, int);
    }  // namespace shell_ui
}  // namespace terminal_user_interface

#endif

