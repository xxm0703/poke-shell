#ifndef TERMINAL_USER_INTERFACE__SHELL_UI__TITLE_HH
#define TERMINAL_USER_INTERFACE__SHELL_UI__TITLE_HH

#include <string>

#include "ncurses_helper/ncurses_object.hh"

namespace terminal_user_interface {
    namespace shell_ui {
        class Title : public ncurses_helper::NCursesObject {
        public:
            static constexpr unsigned short nrows = 6;
            static constexpr unsigned short row_len = 80;
            static const std::string letter_color_pair_name;
            explicit Title(int = 0, int = 0) noexcept;
            void mvwprint(int = 0, int = 0) noexcept final;
        };  // class Title
    }  // namespace shell_ui
}  // namespace terminal_user_interface

#endif

