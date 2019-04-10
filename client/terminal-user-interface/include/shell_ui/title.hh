#ifndef TERMINAL_USER_INTERFACE__SHELL_UI__TITLE_HH
#define TERMINAL_USER_INTERFACE__SHELL_UI__TITLE_HH

#include <string>

#include "ncurses_helper/ncurses_object.hh"

namespace terminal_user_interface {
    namespace shell_ui {
        class Title: public ncurses_helper::NCursesObject {
        public:
            static constexpr ncurses_helper::win_size_t nrows = 6;
            static constexpr ncurses_helper::win_size_t row_len = 80;
            static constexpr char letter_color_pair_name[] = "title_letter";
            explicit Title(ncurses_helper::win_coord_t = 0, 
                    ncurses_helper::win_coord_t = 0);
            void mvwprint(ncurses_helper::cur_coord_t = 0, 
                    ncurses_helper::cur_coord_t = 0) final;
        };  // class Title
    }  // namespace shell_ui
}  // namespace terminal_user_interface

#endif

