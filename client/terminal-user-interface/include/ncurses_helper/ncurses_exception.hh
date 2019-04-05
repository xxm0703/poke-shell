#ifndef TERMINAL_USER_INTERFACE__NCURSES_HELPER__NCURSES_EXCEPTION_HH
#define TERMINAL_USER_INTERFACE__NCURSES_HELPER__NCURSES_EXCEPTION_HH

#include <exception>
#include <memory>
#include <string>

namespace terminal_user_interface {
    namespace ncurses_helper {
        class NCursesException: public std::exception {
        public:
            explicit NCursesException(const char *, int) noexcept;
            explicit NCursesException(const std::string&, int) noexcept;
            const char *what() const noexcept override;
            const std::string& get_func_name() noexcept;
            int get_rc() noexcept;
        private:
            const std::string func_name_;
            int rc_;
            const std::string error_message_;
            std::string build_message() const noexcept;
        };  // class NCursesException    
    }  // namespace ncurses_helper
}  // namespace terminal_user_interface

#endif

