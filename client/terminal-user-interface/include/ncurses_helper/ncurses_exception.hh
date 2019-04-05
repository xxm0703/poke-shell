#ifndef TERMINAL_USER_INTERFACE__NCURSES_HELPER__NCURSES_EXCEPTION_HH
#define TERMINAL_USER_INTERFACE__NCURSES_HELPER__NCURSES_EXCEPTION_HH

#include <exception>
#include <string>

namespace terminal_user_interface {
    namespace ncurses_helper {
        class NCursesException: public std::exception {
        public:
            explicit NCursesException(const char *, int) noexcept;
            explicit NCursesException(const char *, void *);
            explicit NCursesException(const std::string&, int) noexcept;
            explicit NCursesException(const std::string&, void *);
            const char *what() const noexcept override;
            bool has_null_rc() const noexcept;
            const std::string& get_func_name() const noexcept;
            int get_rc() const;
        private:
            const std::string func_name_;
            struct {
                bool is_null;
                int code;
            } rc_;
            const std::string error_message_;
            std::string build_message() const noexcept;
        };  // class NCursesException    
    }  // namespace ncurses_helper
}  // namespace terminal_user_interface

#endif

