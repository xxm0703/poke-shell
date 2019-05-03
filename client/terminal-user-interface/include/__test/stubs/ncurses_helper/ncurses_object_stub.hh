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
    }  // namespace __test
}  // namespace terminal_user_interface

#endif

