#include "__test/test_helper.hh"

#include <cstdio>
#include <stdexcept>
#include <string>
#include <sstream>
#include <stdexcept>

#include <ncurses.h>
#include "ncurses_helper/ncurses_exception.hh"

#define _NULL_NAME "NULL"

using terminal_user_interface::ncurses_helper::ncurses_errno_t;
using terminal_user_interface::ncurses_helper::NCursesException;

namespace terminal_user_interface {
    namespace __test {
        namespace ncurses_helper {
            namespace {
                std::FILE *termout;
                SCREEN *termscr;
            }  // anonymous namespace

            void ncurses_setup() {
                if ((termout = fopen("./tmp/streams/termout", "w")) == nullptr) {
                    perror("fopen");
                    throw std::runtime_error("could not create terminal output stream");
                }
                if ((termscr = newterm(NULL, termout, stdin)) == nullptr)
                    throw NCursesException("newterm", nullptr);
                set_term(termscr);

                // setup colors
                if (!has_colors()) {
                    throw std::runtime_error("terminal does not support colors");
                } else {
                    int rc;

                    rc = start_color();
                    if (rc == ERR) throw NCursesException("start_color", rc);
                }
                refresh();
            }

            void ncurses_teardown() {
                int rc;

                delscreen(termscr);
                rc = fclose(termout);
                if (rc == EOF) {
                    perror("fclose");
                    throw std::runtime_error("couldn't close terminal output stream");
                }
            }

            std::string ncurses_error_msg(const char *func_name, 
                    ncurses_errno_t rc) noexcept {
                std::ostringstream msg;
                msg << "ncurses function '" << func_name 
                    << "' returned error code " << rc;
                return msg.str();
            }

            std::string ncurses_error_msg(const std::string& func_name, 
                    ncurses_errno_t rc) noexcept {
                return ncurses_error_msg(func_name.c_str(), rc);
            }

            std::string ncurses_error_msg(const char *func_name, void *null_ptr) {
                if (null_ptr != nullptr)  // arbitrary pointer has been passed
                    throw std::invalid_argument("parsed pointer is not null");

                std::ostringstream msg;
                msg << "ncurses function '" << func_name 
                    << "' returned error code " << _NULL_NAME;
                return msg.str();
            }

            std::string ncurses_error_msg(const std::string& func_name, void *null_ptr) {
                return ncurses_error_msg(func_name.c_str(), null_ptr);
            }
        }  // namespace ncurses_helper
    }  // namespace __test
}  // namespace terminal_user_interface

#undef _NULL_NAME

