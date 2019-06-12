#ifndef TERMINAL_USER_INTERFACE__NCURSES_HELPER__INPUT_HH
#define TERMINAL_USER_INTERFACE__NCURSES_HELPER__INPUT_HH

#define PRINT_CHCODE_EXIT_CODE 1

namespace terminal_user_interface {
    namespace ncurses_helper {
        namespace ncurses_keycodes {
            constexpr int key_ctrl_d = 4;
            constexpr int key_enter = 10;
        }  // namespace ncurses_keycodes

        void print_ncurses_character_code();
    }  // namespace ncurses_helper
}  // namespace terminal_user_interface

#endif

