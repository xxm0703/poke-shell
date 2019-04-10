#ifndef TERMINAL_USER_INTERFACE__SHELL_UI__VERTICAL_MENU_HH
#define TERMINAL_USER_INTERFACE__SHELL_UI__VERTICAL_MENU_HH

#include <string>
#include <vector>

#include "ncurses_helper/ncurses_menu_object.hh"
#include "ncurses_helper/windows.hh"

namespace terminal_user_interface {
    namespace shell_ui {
        class VerticalMenu: public ncurses_helper::NCursesMenuObject {
        public:
            explicit VerticalMenu(const std::vector<std::string>&,
                    ncurses_helper::win_size_t = 0, ncurses_helper::win_size_t = 0,
                    ncurses_helper::win_coord_t = 0, ncurses_helper::win_coord_t = 0);
            void mvwprint(ncurses_helper::cur_coord_t = 0, 
                    ncurses_helper::cur_coord_t = 0) override;
        protected:
            ncurses_helper::win_size_t calc_height(ncurses_helper::win_size_t,
                    const std::vector<std::string>&) const override;
            ncurses_helper::win_size_t calc_width(ncurses_helper::win_size_t,
                    const std::vector<std::string>&) const override;
        };  // class VerticalMenu
    }  // namespace shell_ui
}  // namespace terminal_user_interface

#endif

