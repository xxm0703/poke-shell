#include "catch2/catch.hpp"
#include "__test/test_helper.hh"
#include "shell_ui/text.hh"

#include <string>
#include <vector>

#include "std_helper/string.hh"

using namespace terminal_user_interface;
using namespace terminal_user_interface::shell_ui;
using terminal_user_interface::ncurses_helper::get_window_height;
using terminal_user_interface::ncurses_helper::get_window_width;
using terminal_user_interface::ncurses_helper::get_window_begy;
using terminal_user_interface::ncurses_helper::get_window_begx;

bool colored = false;

TEST_CASE("Display a static text", "[shell_ui::Text]") {
    SECTION("setup") {
        __test::ncurses_setup();
    }

    WINDOW *win;

    SECTION("can construct object") {
        SECTION("with default arguments") {
            std::string text_str("Pesho");

            Text text(text_str);
            win = text.get_win();
            REQUIRE(get_window_begy(win) == 0);
            REQUIRE(get_window_begx(win) == 0);
        }

        SECTION("with custom coordinates") {
            std::string text_str("Pesho");

            Text text(text_str, 3, 12);
            win = text.get_win();
            REQUIRE(get_window_begy(win) == 3);
            REQUIRE(get_window_begx(win) == 12);
        }

        SECTION("with different text contents") {
            auto text_str = GENERATE(as<std::string>{}, "Text", "Hello\nWorld", "This\nis\nPesho");

            std::vector<std::string> str_lines = std_helper::split(text_str, "\n");
            std::string longest_string = std_helper::get_longest_string(str_lines);
            Text text(text_str);
            win = text.get_win();
            REQUIRE(get_window_height(win) == str_lines.size());
            REQUIRE(get_window_width(win) == longest_string.length());
        }

        SECTION("can retrieve text contents") {
            auto text_str = GENERATE(as<std::string>{}, "Text", "Hello\nWorld", "This\nis\nPesho");

            Text text(text_str);
            REQUIRE(text.get_text() == text_str);
        }

        SECTION("can set text contents") {
            std::string text_str = "Text";
            std::string replacement_str = "Hello World";

            Text text(text_str);
            REQUIRE(text.get_text() == text_str);
            text.set_text(replacement_str);
            REQUIRE(text.get_text() == replacement_str);
        }
    }

    SECTION("teardown") {
        __test::ncurses_teardown();
    }
}

