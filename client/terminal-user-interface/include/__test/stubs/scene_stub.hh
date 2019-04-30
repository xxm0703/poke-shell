#ifndef __TERMINAL_USER_INTERFACE__TEST__SCENE_STUB_HH
#define __TERMINAL_USER_INTERFACE__TEST__SCENE_STUB_HH

#include "shell_ui/scene.hh"

#include <memory>
#include <string>

#include "ncurses_helper/ncurses_object.hh"

namespace terminal_user_interface {
    namespace __test {
        class SceneStub final: public shell_ui::Scene {
        public:
            void init() final;
            void update() final;
            void destroy() final;
            void _ex_add_scene_object(const std::string&, 
                    std::shared_ptr<ncurses_helper::NCursesObject>);
        };  // class SceneStub


        inline void SceneStub::init() {
            // do nothing
        }

        inline void SceneStub::update() {
            // do nothing
        }

        inline void SceneStub::destroy() {
            // do nothing
        }

        inline void SceneStub::_ex_add_scene_object(const std::string& name, 
                std::shared_ptr<ncurses_helper::NCursesObject> scene_object) {
            add_scene_object(name, scene_object);
        }
    }  // namespace __test
}  // namespace terminal_user_interface

#endif
