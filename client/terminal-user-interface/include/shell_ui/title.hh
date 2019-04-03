#ifndef TERMINAL_USER_INTERFACE__SHELL_UI__TITLE_HH
#define TERMINAL_USER_INTERFACE__SHELL_UI__TITLE_HH

#include <ncurses.h>

namespace terminal_user_interface {
    namespace shell_ui {
        void mvprintw_title(WINDOW *, int, int);
    }  // namespace shell_ui
}  // namespace terminal_user_interface

#endif

