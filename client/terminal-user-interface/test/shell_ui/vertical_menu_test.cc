#include "catch2/catch.hpp"
#include "__test/test_helper.hh"
#include "shell_ui/vertical_menu.hh"

#include "std_helper/string.hh"

using namespace terminal_user_interface;
using namespace terminal_user_interface::shell_ui;
using terminal_user_interface::ncurses_helper::win_size_t;
using terminal_user_interface::ncurses_helper::win_coord_t;
using terminal_user_interface::ncurses_helper::cur_coord_t;

bool colored = false;

TEST_CASE("Display a vertical multiple-choice menu", "[shell_ui::VerticalMenu]") {
    SECTION("setup") {
        __test::ncurses_helper::ncurses_setup();
    }

    WINDOW *win;
    std::vector<std::string> options{"Start", "Exit", "Credits"};
    const std::string& longest_option = std_helper::string::get_longest_string(options);

    SECTION("can construct object") {
        SECTION("with default arguments") {
            VerticalMenu menu(options);
            win = menu.get_win();
            REQUIRE(getbegy(win) == 0);
            REQUIRE(getbegx(win) == 0);
        }
        
        SECTION("fulfills the minimum width and height requirements") {
            win_size_t height = GENERATE(-21, 0, 2);
            win_size_t width = GENERATE(-5, 0, 5);

            VerticalMenu menu(options, height, width);
            win = menu.get_win();
            REQUIRE(getmaxy(win) == options.size());
            REQUIRE(getmaxx(win) == longest_option.length());
        }
    }

    SECTION("can print a vertical menu on the screen") {
        cur_coord_t y = GENERATE(0);
        cur_coord_t x = GENERATE(0);

        SECTION("with default menu sizes") {
            VerticalMenu menu(options);
            win = menu.get_win();
            menu.mvwprint(y, x);
            REQUIRE(getcury(win) == y + options.size());
            REQUIRE(getcurx(win) == x + longest_option.length());
        }

        SECTION("with custom menu sizes") {
            win_size_t height = GENERATE(4, 7);
            win_size_t width = GENERATE(8, 12);
            REQUIRE(height > options.size());
            REQUIRE(width > longest_option.length());

            VerticalMenu menu(options, height, width);
            win = menu.get_win();
            menu.mvwprint(y, x);
            REQUIRE(getcury(win) == y + height);
            REQUIRE(getcurx(win) == x + width);
        }
    }

    SECTION("teardown") {
        __test::ncurses_helper::ncurses_teardown();
    }
}

