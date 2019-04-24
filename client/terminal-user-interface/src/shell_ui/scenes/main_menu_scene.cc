#include "shell_ui/scenes/main_menu_scene.hh"

#include <memory>

#include <ncurses.h>
#include "shell_ui/config.hh"
#include "shell_ui/title.hh"
#include "shell_ui/text.hh"
#include "shell_ui/vertical_menu.hh"
#include "ncurses_helper/ncurses_object.hh"
#include "ncurses_helper/ncurses_menu_object.hh"
#include "ncurses_helper/input.hh"
#include "std_helper/string.hh"

using terminal_user_interface::ncurses_helper::NCursesObject;
using terminal_user_interface::ncurses_helper::NCursesMenuObject;

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
            menu_ptr->select_option(0);

            auto copyright_ptr = std::make_shared<Text>("Copyright (C) 2019 Martin Jordanov");
            add_scene_object("copyright", copyright_ptr);

            SceneWithInput::init();
        }

        void MainMenuScene::update() {
            std::shared_ptr<NCursesObject> title = get_scene_object("title");
            title->clear_window();
            title->center_window().offset_y(-12);
            title->mvwprint();

            std::shared_ptr<NCursesObject> menu = get_scene_object("menu");
            menu->clear_window();
            menu->center_window().offset_y(4);
            menu->mvwprint();

            std::shared_ptr<NCursesObject> copyright = get_scene_object("copyright");
            // position copyright text at bottom center
            copyright->clear_window();
            copyright->center_x().anchor_y().offset_y(-1);
            copyright->mvwprint();
        }

        void MainMenuScene::destroy() {
            SceneWithInput::destroy();

            clear();
            refresh();
        }

        void MainMenuScene::read_input() const {
            auto menu = std::static_pointer_cast<NCursesMenuObject>(get_scene_object("menu"));

            while (!config::g_quit) {
                switch (getch()) {
                case 'q':
                    config::g_quit = true;  // quit the program
                    break;
                case 'w':
                    menu->select_previous_option();
                    break;
                case 's':
                    menu->select_next_option();
                    break;
                case ncurses_helper::ncurses_keycodes::key_enter:
                    // TODO: execute option code here
                    break;
                }
            }
        }
    }  // namespace shell_ui
}  // namespace terminal_user_interface

