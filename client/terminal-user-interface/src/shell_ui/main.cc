#include <ncurses.h>
#include <string>

#include "shell_ui/title.hh"
#include "ncurses_helper/colors.hh"

using namespace terminal_user_interface;
using namespace terminal_user_interface::shell_ui;

bool colored;  // globally indicate whether terminal supports colors

static void setup_colors(void);

int main(void) {
    initscr();  // initialize main ncurses window
    setup_colors();
    refresh();
    
    Title title;
    title.center_window().offset_y(-10);
    title.clear_window();
    title.mvwprint();

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

        ncurses_helper::colors::add_color_pair(Title::letter_color_pair_name, 
                COLOR_YELLOW, COLOR_BLACK);
    } else {  // terminal does not support colors
        colored = false;
    }
}

