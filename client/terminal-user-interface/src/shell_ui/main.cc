#include <ncurses.h>

#include "shell_ui/title.hh"

using namespace terminal_user_interface;
using namespace terminal_user_interface::shell_ui;

bool colored;  // globally indicate whether terminal supports colors

static void setup_colors(void);

int main(void) {
    initscr();  // initialize main ncurses window
    setup_colors();
    
    WINDOW *title_win = newwin(120, 120, 0, 0);
    mvprintw_title(title_win, 0, 0);
    refresh();

    getch();
    endwin();  // destroy main ncurses window
    return 0;
}

static void setup_colors(void) {
    if (has_colors()) {  // terminal supports colors
        colored = true;
        start_color();
        if (can_change_color())
            init_color(COLOR_BLACK, 0, 0, 0);

        init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    } else {  // terminal does not support colors
        colored = false;
    }
}

