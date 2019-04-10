#include "ncurses_helper/ncurses_exception.hh"

#include <sstream>
#include <exception>

#include <ncurses.h>

#define _NULL_MSG "NULL"

namespace terminal_user_interface {
    namespace ncurses_helper {
        NCursesException::NCursesException(const char *func_name, ncurses_errno_t rc) noexcept
            : std::exception(),
              func_name_(func_name),
              rc_({ false, rc }),
              error_message_(build_message()) {
            endwin();
        }

        NCursesException::NCursesException(const char *func_name, void *null_ptr)
            : std::exception(),
              func_name_(func_name),
              rc_({ true, 0 }),
              error_message_(build_message()) {
            if (null_ptr != nullptr)  // passed pointer is not null
                throw std::invalid_argument("parsed pointer is not null");
            endwin();
        }

        NCursesException::NCursesException(const std::string& func_name, ncurses_errno_t rc) noexcept
            : NCursesException(func_name.c_str(), rc) {
        }

        NCursesException::NCursesException(const std::string& func_name, void *null_ptr)
            : NCursesException(func_name.c_str(), null_ptr) {
        }

        const char *NCursesException::what() const noexcept {
            return error_message_.c_str();
        }

        bool NCursesException::has_null_rc() const noexcept {
            return rc_.is_null;
        }

        const std::string& NCursesException::get_func_name() const noexcept {
            return func_name_;
        }

        ncurses_errno_t NCursesException::get_rc() const {
            if (rc_.is_null)  // no error code to report
                throw std::logic_error("erroneous function did not return an \
                        error code (returned NULL)");
            return rc_.code;
        }

        std::string NCursesException::build_message() const noexcept {
            std::ostringstream msg;

            msg << "ncurses function '" << func_name_ 
                << "' returned error code ";
            msg << (!rc_.is_null ? std::to_string(rc_.code) : _NULL_MSG);
            return msg.str();
        }
    }  // namespace ncurses_helper
}  // namespace terminal_user_interface

#undef _NULL_MSG

