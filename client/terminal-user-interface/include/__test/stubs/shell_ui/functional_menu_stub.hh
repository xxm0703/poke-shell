#ifndef __TERMINAL_USER_INTERFACE__TEST__FUNCITONAL_MENU_STUB_HH
#define __TERMINAL_USER_INTERFACE__TEST__FUNCITONAL_MENU_STUB_HH

#include "shell_ui/functional_menu.hh"

#include <string>
#include <vector>
#include <functional>

#include "shell_ui/scene.hh"
#include "ncurses_helper/windows.hh"

namespace terminal_user_interface {
    namespace __test {
        class FunctionalMenuStub: public shell_ui::FunctionalMenu {
        public:
            explicit FunctionalMenuStub(
                    const std::vector<std::function<void(shell_ui::Scene&)>>&,
                    const std::vector<std::string>&,
                    ncurses_helper::win_size_t = 0, ncurses_helper::win_size_t = 0,
                    ncurses_helper::win_coord_t = 0, ncurses_helper::win_coord_t = 0);
            void mvwprint(ncurses_helper::win_coord_t, ncurses_helper::win_coord_t) final;
        private:
            ncurses_helper::win_size_t calc_height(ncurses_helper::win_size_t, 
                    const std::vector<std::string>&) const noexcept final;
            ncurses_helper::win_size_t calc_width(ncurses_helper::win_size_t, 
                    const std::vector<std::string>&) const noexcept final;
        };  // class FunctionalMenuStub
    }  // namespace __test
}  // namespace terminal_user_interface

#endif

