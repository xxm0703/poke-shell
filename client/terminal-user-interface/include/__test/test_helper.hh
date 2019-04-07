#ifndef __TERMINAL_USER_INTERFACE__TEST__TEST_HELPER_HH 
#define __TERMINAL_USER_INTERFACE__TEST__TEST_HELPER_HH 

#include <string>

namespace terminal_user_interface {
    namespace __test {
        namespace ncurses_helper {
            void ncurses_setup();
            void ncurses_teardown();
            std::string ncurses_error_msg(const char *, int) noexcept;
            std::string ncurses_error_msg(const std::string&, int) noexcept;
            std::string ncurses_error_msg(const char *, void *);
            std::string ncurses_error_msg(const std::string&, void *);
        }  // namespace ncurses_helper
    }  // namespace __test
}  // namespace terminal_user_interface

#endif

