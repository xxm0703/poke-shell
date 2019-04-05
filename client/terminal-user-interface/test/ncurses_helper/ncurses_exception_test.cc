#include "catch2/catch.hpp"

#include <sstream>

#include "ncurses_helper/ncurses_exception.hh"

using namespace terminal_user_interface;
using namespace terminal_user_interface::ncurses_helper;

TEST_CASE("NCursesException describes an exception that occurred with the ncurses library", "[NCursesException]") {
    SECTION("can construct object") {
        SECTION("with c-string") {
            char func_name[] = "move";
            int rc = -1;
            NCursesException ex(func_name, rc);

            REQUIRE(ex.get_func_name() == func_name);
            REQUIRE(ex.get_rc() == rc);
        }

        SECTION("with C++ std::string") {
            std::string func_name = "move";
            int rc = -244;
            NCursesException ex(func_name, rc);

            REQUIRE(ex.get_func_name() == func_name);
            REQUIRE(ex.get_rc() == rc);
        }

        SECTION("throws no exception") {
            auto func_name = GENERATE(as<std::string>{}, "getmaxyx", "");
            auto rc = GENERATE(-32, 0, 23);

            REQUIRE_NOTHROW(NCursesException(func_name, rc));
        }
    }

    SECTION("can get exception information") {
        std::string func_name = "wmove";
        int rc = -23;
        NCursesException ex(func_name, rc);

        SECTION("function name can be retrieved") {
            REQUIRE_NOTHROW(ex.get_func_name());
            REQUIRE(ex.get_func_name() == func_name);
        }

        SECTION("return code can be retrieved") {
            REQUIRE_NOTHROW(ex.get_rc());
            REQUIRE(ex.get_rc() == rc);
        }

        SECTION("formats proper error message") {
            std::ostringstream expected_result;

            expected_result << "ncurses function '" << func_name 
                << "' returned error code " << rc;
            REQUIRE_NOTHROW(ex.what());
            REQUIRE(ex.what() == expected_result.str());
        }
    }
}

