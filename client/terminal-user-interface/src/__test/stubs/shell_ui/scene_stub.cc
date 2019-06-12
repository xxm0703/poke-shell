#include "__test/stubs/shell_ui/scene_stub.hh"

#include <memory>
#include <string>

#include "ncurses_helper/ncurses_object.hh"

using terminal_user_interface::ncurses_helper::NCursesObject;

namespace terminal_user_interface {
    namespace __test {
        void SceneStub::init() {
            // do nothing
        }

        void SceneStub::update() {
            // do nothing
        }

        void SceneStub::destroy() {
            // do nothing
        }

        void SceneStub::_ex_add_scene_object(const std::string& name, 
                std::shared_ptr<NCursesObject> scene_object) {
            add_scene_object(name, scene_object);
        }
    }  // namespace __test
}  // namespace terminal_user_interface

