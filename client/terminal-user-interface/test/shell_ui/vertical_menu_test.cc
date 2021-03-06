#include "catch2/catch.hpp"
#include "__test/test_helper.hh"
#include "shell_ui/vertical_menu.hh"

#include <algorithm>
#include <vector>
#include <string>
#include <functional>

#include "shell_ui/scene.hh"
#include "ncurses_helper/windows.hh"
#include "std_helper/string.hh"

using namespace terminal_user_interface;
using namespace terminal_user_interface::shell_ui;
using terminal_user_interface::ncurses_helper::win_size_t;
using terminal_user_interface::ncurses_helper::win_coord_t;
using terminal_user_interface::ncurses_helper::cur_coord_t;
using terminal_user_interface::ncurses_helper::get_window_height;
using terminal_user_interface::ncurses_helper::get_window_width;
using terminal_user_interface::ncurses_helper::get_window_begy;
using terminal_user_interface::ncurses_helper::get_window_begx;

TEST_CASE("Display a vertical multiple-choice menu", "[shell_ui::VerticalMenu]") {
    SECTION("setup") {
        __test::ncurses_setup();
    }

    WINDOW *win;
    std::vector<std::function<void(Scene&)>> functions;
    std::vector<std::string> options{"Start", "Exit", "Credits", "Show"};
    std::string longest_option = std_helper::get_longest_string(options);

    SECTION("can construct object") {
        SECTION("with default arguments") {
            VerticalMenu menu(functions, options);
            win = menu.get_win();
            REQUIRE(get_window_begy(win) == 0);
            REQUIRE(get_window_begx(win) == 0);
        }
        
        SECTION("fulfills the minimum width and height requirements") {
            win_size_t height = GENERATE(-21, 0, 2, 7);
            win_size_t width = GENERATE(-5, 0, 5, 12);

            VerticalMenu menu(functions, options, height, width);
            win = menu.get_win();
            REQUIRE(get_window_height(win) >= options.size());
            REQUIRE(get_window_width(win) >= longest_option.length());
        }

        SECTION("always evens out the width") {
            win_size_t width = GENERATE(0, 9, 12);
            win_size_t expected_width = std::max(width, 
                    static_cast<win_size_t>(longest_option.length()));
            expected_width += expected_width % 2;

            VerticalMenu menu(functions, options, 0, width);
            win = menu.get_win();
            REQUIRE(get_window_width(win) % 2 == 0);
            REQUIRE(get_window_width(win) == expected_width);
        }
    }

    SECTION("can print a vertical menu on the screen") {
        SECTION("with default menu sizes") {
            VerticalMenu menu(functions, options);
            win = menu.get_win();
            menu.mvwprint();
            REQUIRE(getcury(win) == options.size() - 1);
            REQUIRE(getcurx(win) == longest_option.length());
        }

        SECTION("with custom menu sizes") {
            win_size_t height = GENERATE(5, 7);
            win_size_t width = GENERATE(8, 12);
            REQUIRE(height > options.size());
            REQUIRE(width > longest_option.length());

            VerticalMenu menu(functions, options, height, width);
            win = menu.get_win();
            menu.mvwprint();
            REQUIRE(getcury(win) == options.size());
            REQUIRE(getcurx(win) == 0);
        }
    }

    SECTION("teardown") {
        __test::ncurses_teardown();
    }
}

