#include "shell_ui/functional_menu.hh"

#include <vector>
#include <string>
#include <functional>

#include "shell_ui/scene.hh"
#include "ncurses_helper/windows.hh"
#include "ncurses_helper/ncurses_menu_object.hh"

using terminal_user_interface::ncurses_helper::win_size_t;
using terminal_user_interface::ncurses_helper::win_coord_t;

namespace terminal_user_interface {
    namespace shell_ui {
        FunctionalMenu::FunctionalMenu(const std::vector<std::function<void(Scene&)>>& functions,
                const std::vector<std::string>& options,
                win_size_t height, win_size_t width,
                win_coord_t start_y, win_coord_t start_x)
            : NCursesMenuObject(options, height, width, start_y, start_x),
              functions_(functions) {
        }

        void FunctionalMenu::execute_selected_option(Scene& current_scene) const {
            functions_[get_selected_option()](current_scene);
        }
    }  // namespace shell_ui
}  // namespace terminal_user_interface

