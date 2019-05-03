#include "catch2/catch.hpp"
#include "__test/test_helper.hh"
#include "shell_ui/factories/main_menu_factory.hh"

using namespace terminal_user_interface;
using namespace terminal_user_interface::shell_ui;

TEST_CASE("Generate main menu with various functionality", "[shell_ui::MainMenuFactory]") {
    SECTION("setup") {
        __test::ncurses_setup();
    }

    // TODO: add tests for MainMenuFactory

    SECTION("teardown") {
        __test::ncurses_teardown();
    }
}

