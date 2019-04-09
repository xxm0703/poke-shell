#ifndef __TERMINAL_USER_INTERFACE__TEST__TEST_HELPER_HH 
#define __TERMINAL_USER_INTERFACE__TEST__TEST_HELPER_HH 

#include <string>
#include <vector>

#include "ncurses_helper/ncurses_exception.hh"

namespace terminal_user_interface {
    namespace __test {
        namespace ncurses_helper {
            void ncurses_setup();
            void ncurses_teardown();
            std::string ncurses_error_msg(const char *, 
                    terminal_user_interface::ncurses_helper::ncurses_errno_t) noexcept;
            std::string ncurses_error_msg(const std::string&, 
                    terminal_user_interface::ncurses_helper::ncurses_errno_t) noexcept;
            std::string ncurses_error_msg(const char *, void *);
            std::string ncurses_error_msg(const std::string&, void *);
        }  // namespace ncurses_helper

        const std::string& get_longest_string(const std::vector<std::string>&) noexcept;
    }  // namespace __test
}  // namespace terminal_user_interface

#endif

