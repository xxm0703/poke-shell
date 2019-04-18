#include "shell_ui/scenes/main_menu_scene.hh"

#include <memory>

#include "shell_ui/title.hh"
#include "shell_ui/text.hh"
#include "shell_ui/vertical_menu.hh"
#include "ncurses_helper/ncurses_object.hh"
#include "std_helper/string.hh"

using terminal_user_interface::ncurses_helper::NCursesObject;

namespace terminal_user_interface {
    namespace shell_ui {
        void MainMenuScene::init() {
            auto title_ptr = std::make_shared<Title>();
            add_scene_object("title", title_ptr);

            const std::vector<std::string> options{"Register", "Login", "Exit"};
            std::string longest_option = std_helper::get_longest_string(options);
            auto menu_ptr = std::make_shared<VerticalMenu>(options, 
                    0, longest_option.length() * 2);
            add_scene_object("menu", menu_ptr);

            auto copyright_ptr = std::make_shared<Text>("Copyright (C) 2019 Martin Jordanov");
            add_scene_object("copyright", copyright_ptr);
        }

        void MainMenuScene::update() {
            // Title& title = *std::static_pointer_cast<Title>(get_scene_object("title"));
            std::shared_ptr<NCursesObject> title = get_scene_object("title");
            title->clear_window();
            title->center_window().offset_y(-12);
            title->mvwprint();

            VerticalMenu& menu = *std::static_pointer_cast<VerticalMenu>(get_scene_object("menu"));
            menu.clear_window();
            menu.center_window().offset_y(4);
            menu.mvwprint();

            Text& copyright = *std::static_pointer_cast<Text>(get_scene_object("copyright"));
            // position copyright text at bottom center
            copyright.clear_window();
            copyright.center_x().anchor_y().offset_y(-1);
            copyright.mvwprint();
        }

        void MainMenuScene::destroy() {
            clear();
            refresh();
        }
    }  // namespace shell_ui
}  // namespace terminal_user_interface

