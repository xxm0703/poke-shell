#include "catch2/catch.hpp"
#include "__test/test_helper.hh"
#include "shell_ui/scene.hh"

#include <memory>
#include <string>
#include <stdexcept>

#include "__test/stubs/ncurses_helper/ncurses_object_stub.hh"
#include "__test/stubs/shell_ui/scene_stub.hh"

using namespace terminal_user_interface;
using namespace terminal_user_interface::shell_ui;
using terminal_user_interface::__test::NCursesObjectStub;
using terminal_user_interface::__test::SceneStub;

TEST_CASE("A Scene has multiple NCursesObjects, which are controlled with independent logic", "[shell-ui::Scene]") {
    SECTION("setup") {
        __test::ncurses_setup();
    }

    SECTION("Can add and retrieve scene objects") {
        std::string object1_name = "object1";
        std::string object2_name = "object2";
        auto object1 = std::make_shared<NCursesObjectStub>(10, 5);
        auto object2 = std::make_shared<NCursesObjectStub>(12, 7);
        SceneStub scene;

        SECTION("successfully add multiple objects") {
            REQUIRE_NOTHROW(scene._ex_add_scene_object(object1_name, object1));
            REQUIRE_NOTHROW(scene._ex_add_scene_object(object2_name, object2));
            REQUIRE(scene.get_scene_object(object1_name) == object1);
            REQUIRE(scene.get_scene_object(object2_name) == object2);
        }

        SECTION("fails if an object is added multiple times") {
            REQUIRE_NOTHROW(scene._ex_add_scene_object(object1_name, object1));
            REQUIRE(scene.get_scene_object(object1_name) == object1);
            REQUIRE_THROWS_AS(scene._ex_add_scene_object(object1_name, object1), 
                    std::runtime_error);
        }
    }

    SECTION("teardown") {
        __test::ncurses_teardown();
    }
}

