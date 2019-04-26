#ifndef TERMINAL_USER_INTERFACE__SHELL_UI__FUNCTIONAL_MENU_HH
#define TERMINAL_USER_INTERFACE__SHELL_UI__FUNCTIONAL_MENU_HH

#include <string>
#include <vector>
#include <functional>

#include "shell_ui/scene.hh"
#include "ncurses_helper/ncurses_menu_object.hh"
#include "ncurses_helper/windows.hh"

namespace terminal_user_interface {
    namespace shell_ui {
        class FunctionalMenu: public ncurses_helper::NCursesMenuObject {
        public:
            explicit FunctionalMenu(const std::vector<std::function<void(Scene&)>>&,
                    const std::vector<std::string>&,
                    ncurses_helper::win_size_t = 0, ncurses_helper::win_size_t = 0,
                    ncurses_helper::win_coord_t = 0, ncurses_helper::win_coord_t = 0);
            void execute_selected_option(Scene&) const;
        private:
            std::vector<std::function<void(Scene&)>> functions_;
        };  // class FunctionalMenu
    }  // namespace shell_ui
}  // namespace terminal_user_interface

#endif

