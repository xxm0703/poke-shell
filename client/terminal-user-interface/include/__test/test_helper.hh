#ifndef __TERMINAL_USER_INTERFACE__TEST__TEST_HELPER_HH 
#define __TERMINAL_USER_INTERFACE__TEST__TEST_HELPER_HH 

#include <string>
#include <vector>

#include "ncurses_helper/exceptions/ncurses_exception.hh"

namespace terminal_user_interface {
    namespace __test {
        void ncurses_setup();
        void ncurses_teardown();
        std::string ncurses_error_msg(const char *, 
                terminal_user_interface::ncurses_helper::ncurses_errno_t) noexcept;
        std::string ncurses_error_msg(const std::string&, 
                terminal_user_interface::ncurses_helper::ncurses_errno_t) noexcept;
        std::string ncurses_error_msg(const char *, void *);
        std::string ncurses_error_msg(const std::string&, void *);
    }  // namespace __test
}  // namespace terminal_user_interface

#endif

