#include "catch2/catch.hpp"
#include "__test/test_helper.hh"
#include "shell_ui/scene.hh"

#include <memory>
#include <string>
#include <stdexcept>

#include "ncurses_helper/ncurses_object.hh"

using namespace terminal_user_interface;
using namespace terminal_user_interface::shell_ui;
using terminal_user_interface::ncurses_helper::win_coord_t;
using terminal_user_interface::ncurses_helper::win_size_t;
using terminal_user_interface::ncurses_helper::NCursesObject;

bool colored = false;

namespace {
    class SceneStub final: Scene {
    public:
        void init() final;
        void update() final;
        void destroy() final;
        std::shared_ptr<NCursesObject> _ex_get_scene_object(
                const std::string&) const;
        void _ex_add_scene_object(const std::string&, 
                std::shared_ptr<NCursesObject>);
    };  // class SceneStub

    class NCursesObjectStub final: public NCursesObject {
    public:
        explicit NCursesObjectStub(win_size_t, win_size_t, 
                win_coord_t = 0, win_coord_t = 0);
        void mvwprint(win_coord_t = 0, win_coord_t = 0) noexcept final;
    };  // class NCursesObjectStub


    inline void SceneStub::init() {
        // do nothing
    }

    inline void SceneStub::update() {
        // do nothing
    }

    inline void SceneStub::destroy() {
        // do nothing
    }

    inline std::shared_ptr<NCursesObject> SceneStub::_ex_get_scene_object(
            const std::string& name) const {
        return get_scene_object(name);
    }

    inline void SceneStub::_ex_add_scene_object(const std::string& name, 
            std::shared_ptr<NCursesObject> scene_object) {
        add_scene_object(name, scene_object);
    }

    inline NCursesObjectStub::NCursesObjectStub(win_size_t height, win_size_t width, 
            win_coord_t start_y, win_coord_t start_x)
        : NCursesObject(height, width, start_y, start_x) {
    }

    inline void NCursesObjectStub::mvwprint(win_coord_t y, win_coord_t x) noexcept {
        if (y) {}  // do nothing
        if (x) {}  // do nothing
    }
}  // anonymous namespace

namespace {
}  // anonymous namespace

TEST_CASE("A Scene has multiple NCursesObjects, which are controlled with independent logic", "[shell-ui::Scene]") {
    SECTION("setup") {
        __test::ncurses_helper::ncurses_setup();
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
            REQUIRE(scene._ex_get_scene_object(object1_name) == object1);
            REQUIRE(scene._ex_get_scene_object(object2_name) == object2);
        }

        SECTION("fails if an object is added multiple times") {
            REQUIRE_NOTHROW(scene._ex_add_scene_object(object1_name, object1));
            REQUIRE(scene._ex_get_scene_object(object1_name) == object1);
            REQUIRE_THROWS_AS(scene._ex_add_scene_object(object1_name, object1), 
                    std::runtime_error);
        }
    }

    SECTION("teardown") {
        __test::ncurses_helper::ncurses_teardown();
    }
}

