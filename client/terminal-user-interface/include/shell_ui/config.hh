#ifndef TERMINAL_USER_INTERFACE__SHELL_UI__CONFIG_HH
#define TERMINAL_USER_INTERFACE__SHELL_UI__CONFIG_HH

namespace terminal_user_interface {
    namespace shell_ui {
        namespace config {
            extern bool colored;  // globally indicate whether terminal supports colors
            extern bool quit;  // globally indicate whether to quit the program

            void setup_colors();
        }  // namespace config
    }  // namespace shell_ui
}  // namespace terminal_user_interface

#endif

