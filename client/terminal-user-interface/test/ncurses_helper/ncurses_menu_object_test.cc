#include "catch2/catch.hpp"
#include "__test/test_helper.hh"
#include "__test/stubs/ncurses_menu_object_stub.hh"
#include "ncurses_helper/ncurses_menu_object.hh"

#include <vector>
#include <string>
#include <stdexcept>

using namespace terminal_user_interface;
using namespace terminal_user_interface::ncurses_helper;
using terminal_user_interface::__test::NCursesMenuObjectStub;

TEST_CASE("NCursesMenuObject extends NCursesObject, providing a selectable menu as its content", "[ncurses_helper::NCursesMenuObject]") {
    SECTION("setup") {
        __test::ncurses_setup();
    }

    std::vector<std::string> options{"Start", "Exit", "Credits"};

    SECTION("can construct object") {
        WINDOW *stub_win;

        SECTION("with default arguments") {
            NCursesMenuObjectStub stub(options);
            stub_win = stub.get_win();

            REQUIRE(get_window_begy(stub_win) == 0);
            REQUIRE(get_window_begx(stub_win) == 0);
        }

        SECTION("with custom sizes") {
            win_size_t height = 5;
            win_size_t width = 10;

            NCursesMenuObjectStub stub(options, height, width);
            stub_win = stub.get_win();
            REQUIRE(get_window_height(stub_win) == height);
            REQUIRE(get_window_width(stub_win) == width);
        }
        
        SECTION("with custom coordinates") {
            win_coord_t start_y = 3;
            win_coord_t start_x = 2;

            NCursesMenuObjectStub stub(options, 0, 0, start_y, start_x);
            stub_win = stub.get_win();
            REQUIRE(get_window_begy(stub_win) == start_y);
            REQUIRE(get_window_begx(stub_win) == start_x);
        }

        SECTION("can get selected option") {
            menu_option_t selected_option = GENERATE(0, 1, 2);

            NCursesMenuObjectStub stub(options);
            stub.select_option(selected_option);
            REQUIRE(stub.get_selected_option() == selected_option);
        }

        SECTION("can retrieve all options") {
            NCursesMenuObjectStub stub(options);
            const std::vector<std::string>& retrieved_options = stub.get_options();
            for (register size_t i = 0; i < options.size(); ++i)
                REQUIRE(options[i] == retrieved_options[i]);
        }
    }

    SECTION("can select options from the menu") {
        NCursesMenuObjectStub stub(options);

        SECTION("by default is deselected") {
            REQUIRE(stub.is_selected() == false);
            REQUIRE(stub.get_selected_option() == NCursesMenuObjectStub::no_option_index);
        }

        SECTION("with valid arguments") {
            menu_option_t option_to_select = GENERATE(0, 1, 2);
                
            stub.select_option(option_to_select);
            REQUIRE(stub.is_selected() == true);
            REQUIRE(stub.get_selected_option() == option_to_select);
        }

        SECTION("throws error with invalid arguments") {
            menu_option_t option_to_select = GENERATE(-1, 3);

            REQUIRE_THROWS_AS(stub.select_option(option_to_select), std::invalid_argument);
        }

        SECTION("and then deselect all options") {
            menu_option_t selected_option = 1;

            stub.select_option(selected_option);
            REQUIRE(stub.is_selected() == true);
            stub.deselect();
            REQUIRE(stub.is_selected() == false);
            REQUIRE(stub.get_selected_option() == NCursesMenuObjectStub::no_option_index);
        }
    }

    SECTION("teardown") {
        __test::ncurses_teardown();
    }
}
