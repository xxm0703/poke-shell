#include "catch2/catch.hpp"
#include "__test/test_helper.hh"
#include "ncurses_helper/windows.hh"

#include <ncurses.h>
#include "ncurses_helper/ncurses_exception.hh"

using namespace terminal_user_interface;
using namespace terminal_user_interface::ncurses_helper;
using namespace terminal_user_interface::ncurses_helper::windows;

TEST_CASE("Provide helper functions for use with ncurses functions") {
    SECTION("setup") {
        __test::ncurses_helper::ncurses_setup();
    }

    SECTION("can retrieve the dimensions of an ncurses WINDOW") {
        SECTION("when an initialized ncurses WINDOW is provided") {
            int height = 10;
            int width = 9;
            int start_y = 2;
            int start_x = 5;
            WINDOW *win = newwin(height, width, start_y, start_x);

            SECTION("can get a window's height") {
                REQUIRE(get_window_height(win) == height);
            }

            SECTION("can get a window's width") {
                REQUIRE(get_window_width(win) == width);
            }

            delwin(win);
        }

        SECTION("throws error when a null pointer is parsed") {
            WINDOW *win = nullptr;

            REQUIRE_THROWS_AS(get_window_height(win), NCursesException);
            REQUIRE_THROWS_WITH(get_window_height(win), 
                    __test::ncurses_helper::ncurses_error_msg("getmaxy", ERR));
            REQUIRE_THROWS_AS(get_window_width(win), NCursesException);
            REQUIRE_THROWS_WITH(get_window_width(win), 
                    __test::ncurses_helper::ncurses_error_msg("getmaxx", ERR));
        }
    }

    SECTION("teardown") {
        __test::ncurses_helper::ncurses_teardown();
    }
}

