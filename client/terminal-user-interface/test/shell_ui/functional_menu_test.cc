#include "catch2/catch.hpp"
#include "__test/test_helper.hh"
#include "__test/stubs/ncurses_object_stub.hh"
#include "__test/stubs/scene_stub.hh"
#include "__test/stubs/functional_menu_stub.hh"
#include "shell_ui/functional_menu.hh"

#include <string>
#include <memory>
#include <vector>
#include <functional>

#include "shell_ui/scene.hh"
#include "ncurses_helper/ncurses_object.hh"
#include "ncurses_helper/windows.hh"

using namespace terminal_user_interface;
using namespace terminal_user_interface::shell_ui;
using terminal_user_interface::__test::NCursesObjectStub;
using terminal_user_interface::__test::SceneStub;
using terminal_user_interface::__test::FunctionalMenuStub;
using terminal_user_interface::ncurses_helper::NCursesObject;
using terminal_user_interface::ncurses_helper::win_coord_t;
using terminal_user_interface::ncurses_helper::get_window_begy;
using terminal_user_interface::ncurses_helper::get_window_begx;

TEST_CASE("Execute various functionality depending on a menu's selected choice", "[shell_ui::FunctionalMenu]") {
    SECTION("setup") {
        __test::ncurses_setup();
    }

    SceneStub scene;
    std::string example_object_name{"example_object"};
    auto example_object = std::make_shared<NCursesObjectStub>(5, 5);
    scene._ex_add_scene_object(example_object_name, example_object);

    win_coord_t move_coord = 8;
    std::vector<std::function<void(Scene&)>> functions;
    functions.push_back([example_object_name, move_coord](Scene& current_scene) {
                auto example_object_ptr = current_scene.get_scene_object(example_object_name);

                example_object_ptr->move_y(move_coord);
            });
    functions.push_back([example_object_name, move_coord](Scene& current_scene) {
                auto example_object_ptr = current_scene.get_scene_object(example_object_name);

                example_object_ptr->move_x(move_coord);
            });
    std::vector<std::string> options{"Move Y", "Move X"};
    FunctionalMenuStub functional_menu(functions, options);


    SECTION("can change the state of the scene") {
        // Move the example ncurses object in the Y direction
        functional_menu.select_option(0);
        REQUIRE(functional_menu.get_selected_option() == 0);
        REQUIRE(get_window_begy(example_object->get_win()) != move_coord);
        functional_menu.execute_selected_option(scene);
        REQUIRE(get_window_begy(example_object->get_win()) == move_coord);

        // Move the example ncurses object in the X direction
        functional_menu.select_option(1);
        REQUIRE(functional_menu.get_selected_option() == 1);
        REQUIRE(get_window_begx(example_object->get_win()) != move_coord);
        functional_menu.execute_selected_option(scene);
        REQUIRE(get_window_begx(example_object->get_win()) == move_coord);
    }

    SECTION("teardown") {
        __test::ncurses_teardown();
    }
}
