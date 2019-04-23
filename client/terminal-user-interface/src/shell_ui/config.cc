#include "shell_ui/config.hh"

#include <ncurses.h>
#include "shell_ui/title.hh"
#include "ncurses_helper/colors.hh"

namespace terminal_user_interface {
    namespace shell_ui {
        namespace config {
            bool colored;  // globally indicate whether terminal supports colors
            bool quit = false;  // globally indicate whether to quit the program

            void setup_colors() {
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
        }  // namespace config
    }  // namespace shell_ui
}  // namespace terminal_user_interface

