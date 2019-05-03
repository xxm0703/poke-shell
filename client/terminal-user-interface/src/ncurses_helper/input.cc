#include "ncurses_helper/input.hh"

#include <stdio.h>

#include <ncurses.h>
#include "ncurses_helper/exceptions/ncurses_exception.hh"

namespace terminal_user_interface {
    namespace ncurses_helper {
        void print_ncurses_character_code() {
            int ch = getch();
            if (ch == ERR) throw NCursesException("getch", ERR);
            const char *chname = keyname(ch);
            if (chname == NULL) throw NCursesException("keyname", nullptr);

            endwin();
            printf("key name: %s\nkey code: %d\n", chname, ch);
            exit(PRINT_CHCODE_EXIT_CODE);
        }
    }  // namespace ncurses_helper
}  // namespace terminal_user_interface
