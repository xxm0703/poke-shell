#ifndef TERMINAL_USER_INTERFACE__SHELL_UI__SCENE_WITH_INPUT_HH
#define TERMINAL_USER_INTERFACE__SHELL_UI__SCENE_WITH_INPUT_HH

#include <memory>
#include <thread>

#include "shell_ui/scene.hh"

namespace terminal_user_interface {
    namespace shell_ui {
        class SceneWithInput: public Scene {
        public:
            virtual void init() override;
            virtual void destroy() override;
            virtual void read_input() const = 0;
        private:
            std::unique_ptr<std::thread> input_thread_;
        };  // class SceneWithInput 
    }  // namespace shell_ui
}  // namespace terminal_user_interface

#endif

