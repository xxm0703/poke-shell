#include <chrono>
#include <thread>

#include <ncurses.h>
#include "shell_ui/title.hh"
#include "shell_ui/scene.hh"
#include "shell_ui/scenes/main_menu_scene.hh"
#include "ncurses_helper/colors.hh"
#include "ncurses_helper/input.hh"

using namespace terminal_user_interface;
using namespace terminal_user_interface::shell_ui;

bool colored;  // globally indicate whether terminal supports colors
bool quit = false;  // globally indicate whether to quit the program

namespace {
    inline void setup_colors();
}  // anonymous namespace

int main() {
    initscr();  // initialize main ncurses window
    cbreak();
    noecho();
    setup_colors();
    refresh();

    MainMenuScene menu;
    menu.init();

    while (!quit) {
        menu.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 6));
    }

    menu.destroy();
    endwin();  // destroy main ncurses window
    return 0;
}

namespace {
    inline void setup_colors() {
        if (has_colors()) {  // terminal supports colors
            colored = true;
            start_color();
            if (can_change_color())
                init_color(COLOR_BLACK, 0, 0, 0);

            ncurses_helper::add_color_pair(Title::letter_color_pair_name, 
                    COLOR_YELLOW, COLOR_BLACK);
        } else {  // terminal does not support colors
            colored = false;
        }
    }
}  // anonymous namespace

