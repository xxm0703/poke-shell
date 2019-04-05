#ifndef TERMINAL_USER_INTERFACE__SHELL_UI__TITLE_HH
#define TERMINAL_USER_INTERFACE__SHELL_UI__TITLE_HH

#include <ncurses.h>
#include <string>

namespace terminal_user_interface {
    namespace shell_ui {
        namespace title {
            class Title {
                static const unsigned short nrows;
                static const unsigned short row_len;
                static const std::string letter_color_pair_name;
                WINDOW *win_;

                public:

                Title(int = 0, int = 0) noexcept;
                ~Title(void) noexcept;
                static unsigned short get_nrows(void) noexcept;
                static unsigned short get_row_len(void) noexcept;
                static std::string get_letter_color_pair_name(void) noexcept;
                void mvwprint(int = 0, int = 0) noexcept;
                Title& refresh_window(void) noexcept;
                Title& clear_window(void) noexcept;
                Title& move_window(int, int) noexcept;
                Title& center_window(WINDOW * = stdscr, bool = true, bool = true) noexcept;
                Title& move_y(int) noexcept;
                Title& offset_y(int) noexcept;
                Title& center_y(WINDOW * = stdscr) noexcept;
                Title& move_x(int) noexcept;
                Title& offset_x(int) noexcept;
                Title& center_x(WINDOW * = stdscr) noexcept;
                WINDOW *get_win(void) const noexcept;
            };
        }  // namespace title
    }  // namespace shell_ui
}  // namespace terminal_user_interface

#endif

