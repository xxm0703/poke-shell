#ifndef TERMINAL_USER_INTERFACE__SHELL_UI__CONFIG_HH
#define TERMINAL_USER_INTERFACE__SHELL_UI__CONFIG_HH

namespace terminal_user_interface {
    namespace shell_ui {
        namespace config {
            extern bool g_colored;  // globally indicate whether terminal supports colors
            extern bool g_quit;  // globally indicate whether to quit the program
            extern int g_frame_rate;  // window refresh rate

            void setup_colors();
            int ms_get_frame_period(int);
        }  // namespace config
    }  // namespace shell_ui
}  // namespace terminal_user_interface

#endif

