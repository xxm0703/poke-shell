#include "ncurses_helper/ncurses_exception.hh"

#include <memory>
#include <sstream>

namespace terminal_user_interface {
    namespace ncurses_helper {
        NCursesException::NCursesException(const char *func_name, int rc) noexcept
            : std::exception(),
              func_name_(func_name),
              rc_(rc),
              error_message_(build_message()) {
        }

        NCursesException::NCursesException(const std::string& func_name, int rc) noexcept
            : NCursesException(func_name.c_str(), rc) {
        }

        const char *NCursesException::what() const noexcept {
            return error_message_.c_str();
        }

        const std::string& NCursesException::get_func_name() noexcept {
            return func_name_;
        }

        int NCursesException::get_rc() noexcept {
            return rc_;
        }

        std::string NCursesException::build_message() const noexcept {
            std::ostringstream msg;

            msg << "ncurses function '" << func_name_ 
                << "' returned error code " << rc_;
            return msg.str();
        }
    }  // namespace ncurses_helper
}  // namespace terminal_user_interface

