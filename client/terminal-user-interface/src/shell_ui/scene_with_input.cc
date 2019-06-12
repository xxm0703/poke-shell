#include "shell_ui/scene_with_input.hh"

#include <memory>
#include <thread>

namespace terminal_user_interface {
    namespace shell_ui {
        void SceneWithInput::init() {
            input_thread_ = std::make_unique<std::thread>(&SceneWithInput::read_input, this);
        }

        void SceneWithInput::destroy() {
            input_thread_->join();
        }
    }  // namespace shell_ui
}  // namespace terminal_user_interface

