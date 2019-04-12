#include "catch2/catch.hpp"
#include "__test/test_helper.hh"
#include "ncurses_helper/colors.hh"

#include <string>
#include <stdexcept>

#include <ncurses.h>
#include "ncurses_helper/ncurses_exception.hh"

using namespace terminal_user_interface;
using namespace terminal_user_interface::ncurses_helper;

TEST_CASE("Present interface to map names (strings) to ncurses color pairs", "[ncurses]") {
    SECTION("setup") {
        __test::ncurses_helper::ncurses_setup();
    }

    SECTION("can successfully add a string-to-color-pair association and retrive \
            the newly added color pair by name") {
        const std::string name("black");
        color_t fg_color = COLOR_BLACK;
        color_t bg_color = COLOR_WHITE;

        REQUIRE_NOTHROW(add_color_pair(name, fg_color, bg_color));
        REQUIRE_NOTHROW(get_color_pair(name));
        REQUIRE(get_color_pair(name) != ERR);

        _flush_color_pair_map();
    }

    SECTION("throw error when invalid color numbers are parsed") {
        REQUIRE_THROWS_AS(add_color_pair("red", -1, 0), std::invalid_argument);
        REQUIRE_THROWS_AS(add_color_pair("black", 0, -1), std::invalid_argument);
    }

    SECTION("cannot retrieve a non-existent color pair entry") {
        REQUIRE_THROWS(get_color_pair("yellow"));
        REQUIRE_THROWS(get_color_pair("black"));
    }

    SECTION("teardown") {
        __test::ncurses_helper::ncurses_teardown();
    }
}

