#ifndef __TERMINAL_USER_INTERFACE__TEST__NCURSES_OBJECT_STUB_HH
#define __TERMINAL_USER_INTERFACE__TEST__NCURSES_OBJECT_STUB_HH

#include "ncurses_helper/ncurses_object.hh"

#include "ncurses_helper/windows.hh"

namespace terminal_user_interface {
    namespace __test {
        class NCursesObjectStub final: public ncurses_helper::NCursesObject {
        public:
            explicit NCursesObjectStub(ncurses_helper::win_size_t, ncurses_helper::win_size_t, 
                    ncurses_helper::win_coord_t = 0, ncurses_helper::win_coord_t = 0);
            void mvwprint(ncurses_helper::win_coord_t = 0, 
                    ncurses_helper::win_coord_t = 0) noexcept final;
        };  // class NCursesObjectStub

        inline NCursesObjectStub::NCursesObjectStub(
                ncurses_helper::win_size_t height, ncurses_helper::win_size_t width, 
                ncurses_helper::win_coord_t start_y, ncurses_helper::win_coord_t start_x)
            : ncurses_helper::NCursesObject(height, width, start_y, start_x) {
        }

        inline void NCursesObjectStub::mvwprint(ncurses_helper::win_coord_t y, 
                ncurses_helper::win_coord_t x) noexcept {
            if (y) {}  // do nothing
            if (x) {}  // do nothing
        }
    }  // namespace __test
}  // namespace terminal_user_interface

#endif

