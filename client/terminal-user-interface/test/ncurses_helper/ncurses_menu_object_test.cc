#include "catch2/catch.hpp"
#include "__test/test_helper.hh"
#include "ncurses_helper/ncurses_menu_object.hh"

#include <vector>
#include <string>
#include <stdexcept>

using namespace terminal_user_interface;
using namespace terminal_user_interface::ncurses_helper;
using terminal_user_interface::ncurses_helper::windows::win_coord_t;
using terminal_user_interface::ncurses_helper::windows::win_size_t;

namespace {
    class NCursesMenuObjectStub: public NCursesMenuObject<std::vector> {
    public:
        explicit NCursesMenuObjectStub(const std::vector<std::string>&, 
                win_size_t = 0, win_size_t = 0, win_coord_t = 0, win_coord_t = 0);
    };  // class NCursesMenuObjectStub

    inline NCursesMenuObjectStub::NCursesMenuObjectStub(const std::vector<std::string>& options,
            win_size_t height, win_size_t width, win_coord_t start_y, win_coord_t start_x)
        : NCursesMenuObject(options, height, width, start_y, start_x) {
    }
}  // anonymous namespace

TEST_CASE("NCursesMenuObject extends NCursesObject, providing a selectable menu as its content", "[NCursesMenuObject]") {
    SECTION("setup") {
        __test::ncurses_helper::ncurses_setup();
    }

    std::vector<std::string> options{"Start", "Exit", "Credits"};

    SECTION("can construct object") {
        const std::string& longest_option = __test::get_longest_string(options);
        WINDOW *stub_win;

        SECTION("with default arguments") {
            NCursesMenuObjectStub stub(options);
            stub_win = stub.get_win();

            REQUIRE(getmaxy(stub_win) == options.size());
            REQUIRE(getmaxx(stub_win) == longest_option.length());
        }

        SECTION("with custom sizes") {
            win_size_t height = 5;
            win_size_t width = 10;

            NCursesMenuObjectStub stub(options, height, width);
            stub_win = stub.get_win();
            REQUIRE(getmaxy(stub_win) == height);
            REQUIRE(getmaxx(stub_win) == width);
        }
        
        SECTION("fulfills the minimum width and height requirements") {
            win_size_t height = GENERATE(-21, 0, 2);
            win_size_t width = GENERATE(-5, 0, 5);

            NCursesMenuObjectStub stub(options, height, width);
            stub_win = stub.get_win();
            REQUIRE(getmaxy(stub_win) == options.size());
            REQUIRE(getmaxx(stub_win) == longest_option.length());
        }

        SECTION("with custom coordinates") {
            win_coord_t start_y = 3;
            win_coord_t start_x = 2;

            NCursesMenuObjectStub stub(options, start_y, start_x);
            stub_win = stub.get_win();
            REQUIRE(getbegy(stub_win) == start_y);
            REQUIRE(getbegx(stub_win) == start_x);
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
        __test::ncurses_helper::ncurses_teardown();
    }
}
