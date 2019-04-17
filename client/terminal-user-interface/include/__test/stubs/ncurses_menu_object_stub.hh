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

        inline NCursesMenuObjectStub::NCursesMenuObjectStub(const std::vector<std::string>& options,
                ncurses_helper::win_size_t height, ncurses_helper::win_size_t width, 
                ncurses_helper::win_coord_t start_y, ncurses_helper::win_coord_t start_x)
            : ncurses_helper::NCursesMenuObject(options, 
                    calc_height(height, options), calc_width(width, options), 
                    start_y, start_x) {
        }

        inline void NCursesMenuObjectStub::mvwprint(ncurses_helper::win_coord_t y,
                ncurses_helper::win_coord_t x) {
            if (y) {}  // do nothing
            if (x) {}  // do nothing
        }

        inline ncurses_helper::win_size_t NCursesMenuObjectStub::calc_height(
                ncurses_helper::win_size_t height, 
                const std::vector<std::string>& options) const noexcept {
            if (options.empty()) {}  // do nothing
            return height;
        }

        inline ncurses_helper::win_size_t NCursesMenuObjectStub::calc_width(
                ncurses_helper::win_size_t width,
                const std::vector<std::string>& options) const noexcept {
            if (options.empty()) {}  // do nothing
            return width;
        }
    }  // namespace __test
}  // namespace terminal_user_interface

#endif

