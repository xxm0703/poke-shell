#include "catch2/catch.hpp"
#include "__test/test_helper.hh"
#include "shell_ui/title.hh"

#include "ncurses_helper/windows.hh"

using namespace terminal_user_interface;
using namespace terminal_user_interface::shell_ui;
using terminal_user_interface::ncurses_helper::win_size_t;
using terminal_user_interface::ncurses_helper::win_coord_t;
using terminal_user_interface::ncurses_helper::cur_coord_t;
using terminal_user_interface::ncurses_helper::get_window_height;
using terminal_user_interface::ncurses_helper::get_window_width;
using terminal_user_interface::ncurses_helper::get_window_begy;
using terminal_user_interface::ncurses_helper::get_window_begx;

TEST_CASE("Display the title of the game", "[shell_ui::Title]") {
    SECTION("setup") {
        __test::ncurses_setup();
    }

    WINDOW *win;

    SECTION("can construct title object") {
        SECTION("with default arguments") {
            Title title;
            win = title.get_win();
            REQUIRE(get_window_begy(win) == 0);
            REQUIRE(get_window_begx(win) == 0);
        }

        SECTION("with custom coordinates") {
            cur_coord_t start_y = 3;
            cur_coord_t start_x = 5;

            Title title(start_y, start_x);
            win = title.get_win();
            REQUIRE(get_window_begy(win) == start_y);
            REQUIRE(get_window_begx(win) == start_x);
        }

        SECTION("defaults dimensions of window to title sting dimensions") {
            cur_coord_t start_y = GENERATE(0, 2, 6);
            cur_coord_t start_x = GENERATE(0, 3, 10);

            Title title(start_y, start_x);
            win = title.get_win();
            REQUIRE(get_window_height(win) == Title::nrows);
            REQUIRE(get_window_width(win) == Title::row_len);
        }
    }

    SECTION("can print the title of the game on the screen") {
        Title title;
        win = title.get_win();

        title.mvwprint();
        REQUIRE(getcury(win) == Title::nrows - 1);
        REQUIRE(getcurx(win) == Title::row_len - 1);
    }

    SECTION("teardown") {
        __test::ncurses_teardown();
    }
}

