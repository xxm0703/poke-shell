#ifndef TERMINAL_USER_INTERFACE__SHELL_UI__MAIN_MENU_SCENE_HH
#define TERMINAL_USER_INTERFACE__SHELL_UI__MAIN_MENU_SCENE_HH

#include "shell_ui/scene_with_input.hh"

namespace terminal_user_interface {
    namespace shell_ui {
        class MainMenuScene final: public SceneWithInput {
        public:
            void init() final;
            void update() final;
            void destroy() final;
            void read_input() const final;
        };  // class MainMenuScene
    }  // namespace shell_ui
}  // namespace terminal_user_interface
#endif

