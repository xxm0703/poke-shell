#include "catch2/catch.hpp"
#include "__test/test_helper.hh"
#include "ncurses_helper/ncurses_exception.hh"

#include <stdexcept>

using namespace terminal_user_interface;
using namespace terminal_user_interface::ncurses_helper;

TEST_CASE("NCursesException describes an exception that occurred with the ncurses library", "[ncurses_helper::NCursesException]") {
    SECTION("can construct object") {
        ncurses_errno_t rc = -1;

        SECTION("with c-string argument for function name") {
            char func_name[] = "move";
            NCursesException ex(func_name, rc);

            REQUIRE(ex.get_func_name() == func_name);
            REQUIRE(ex.get_rc() == rc);
        }

        SECTION("with C++ std::string argument for function name") {
            std::string func_name = "move";
            NCursesException ex(func_name, rc);

            REQUIRE(ex.get_func_name() == func_name);
            REQUIRE(ex.get_rc() == rc);
        }
    }

    SECTION("can retrieve error information") {
        SECTION("can get function name") {
            std::string func_name = "wmove";
            NCursesException ex(func_name, 22);

            REQUIRE_NOTHROW(ex.get_func_name());
            REQUIRE(ex.get_func_name() == func_name);
        }
    }

    SECTION("erroneous function returned an error code") {
        SECTION("object construction causes no errors") {
            auto func_name = GENERATE(as<std::string>{}, "getmaxyx", "");
            ncurses_errno_t rc = GENERATE(-32, 0, 23);

            REQUIRE_NOTHROW(NCursesException(func_name, rc));
        }

        SECTION("can get exception information") {
            std::string func_name = "wmove";
            ncurses_errno_t rc = -23;
            NCursesException ex(func_name, rc);

            SECTION("return code should not be null") {
                REQUIRE_NOTHROW(ex.has_null_rc());
                REQUIRE(ex.has_null_rc() == false);
            }

            SECTION("return code can be retrieved") {
                REQUIRE_NOTHROW(ex.get_rc());
                REQUIRE(ex.get_rc() == rc);
            }

            SECTION("formats proper error message") {
                REQUIRE_NOTHROW(ex.what());
                REQUIRE(ex.what() == __test::ncurses_helper::ncurses_error_msg(func_name, rc));
            }
        }
    }

    SECTION("exception constructor is parsed a pointer to an arbitrary address") {
        SECTION("object construction causes error") {
            auto func_name = GENERATE(as<std::string>{}, "getmaxyx", "");
            ncurses_errno_t rc = GENERATE(-1, 0, 33);

            REQUIRE_THROWS_AS(NCursesException(func_name, &rc), std::invalid_argument);
        }

        SECTION("can get exception information") {
            std::string func_name = "wmove";
            NCursesException ex(func_name, nullptr);

            SECTION("return code should be null") {
                REQUIRE_NOTHROW(ex.has_null_rc());
                REQUIRE(ex.has_null_rc() == true);
            }

            SECTION("return code cannot be retrieved") {
                REQUIRE_THROWS_AS(ex.get_rc(), std::logic_error);
            }

            SECTION("formats proper error message") {
                REQUIRE_NOTHROW(ex.what());
                REQUIRE(ex.what() == __test::ncurses_helper::ncurses_error_msg(func_name, nullptr));
            }
        }
    }

    SECTION("erroneous function returned a NULL pointer") {
        SECTION("object construction causes no errors") {
            auto func_name = GENERATE(as<std::string>{}, "getmaxyx", "");

            REQUIRE_NOTHROW(NCursesException(func_name, nullptr));
        }
    }
}

