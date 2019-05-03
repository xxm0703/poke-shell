#ifndef __TERMINAL_USER_INTERFACE__TEST__NCURSES_MENU_OBJECT_STUB_HH
#define __TERMINAL_USER_INTERFACE__TEST__NCURSES_MENU_OBJECT_STUB_HH

#include "ncurses_helper/ncurses_menu_object.hh"

#include <string>
#include <vector>

#include "ncurses_helper/windows.hh"

namespace terminal_user_interface {
    namespace __test {
        class NCursesMenuObjectStub final: public ncurses_helper::NCursesMenuObject {
        public:
            explicit NCursesMenuObjectStub(const std::vector<std::string>&, 
                    ncurses_helper::win_size_t = 0, ncurses_helper::win_size_t = 0, 
                    ncurses_helper::win_coord_t = 0, ncurses_helper::win_coord_t = 0);
            void mvwprint(ncurses_helper::win_coord_t, ncurses_helper::win_coord_t) final;
        private:
            ncurses_helper::win_size_t calc_height(ncurses_helper::win_size_t, 
                    const std::vector<std::string>&) const noexcept final;
            ncurses_helper::win_size_t calc_width(ncurses_helper::win_size_t, 
                    const std::vector<std::string>&) const noexcept final;
        };  // class NCursesMenuObjectStub
    }  // namespace __test
}  // namespace terminal_user_interface

#endif

