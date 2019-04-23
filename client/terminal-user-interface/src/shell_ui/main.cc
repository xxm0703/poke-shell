#include <chrono>
#include <thread>

#include <ncurses.h>
#include "shell_ui/config.hh"
#include "shell_ui/title.hh"
#include "shell_ui/scene.hh"
#include "shell_ui/scenes/main_menu_scene.hh"
#include "ncurses_helper/colors.hh"
#include "ncurses_helper/input.hh"

using namespace terminal_user_interface;
using namespace terminal_user_interface::shell_ui;

int main() {
    initscr();  // initialize main ncurses window
    cbreak();
    noecho();
    config::setup_colors();
    refresh();

    MainMenuScene menu;
    menu.init();

    while (!config::quit) {
        menu.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 6));
    }

    menu.destroy();
    endwin();  // destroy main ncurses window
    return 0;
}


