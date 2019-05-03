#ifndef TERMINAL_USER_INTERFACE__SHELL_UI__MAIN_MENU_FACTORY_HH
#define TERMINAL_USER_INTERFACE__SHELL_UI__MAIN_MENU_FACTORY_HH

#include <cstdio>  // FIXME
#include <memory>
#include <functional>
#include <vector>
#include <string>

#include <ncurses.h>  // FIXME
#include "shell_ui/config.hh"
#include "shell_ui/functional_menu.hh"
#include "shell_ui/scene.hh"
#include "std_helper/string.hh"

namespace terminal_user_interface {
    namespace shell_ui {
        template<typename GeneratedT>
        class MainMenuFactory final {
        public:
            static std::shared_ptr<FunctionalMenu> unauthenticated_menu() {
                const std::vector<std::string> options{"Register", "Login", "Exit"};
                std::string longest_option = std_helper::get_longest_string(options);
                std::vector<std::function<void(Scene&)>> functions;
                functions.push_back([](Scene& current_scene) {
                        endwin();
                        puts("register");
                        exit(0);
                        });
                functions.push_back([](Scene& current_scene) {
                        endwin();
                        puts("login");
                        exit(0);
                        });
                functions.push_back([](Scene& current_scene) {
                        config::g_quit = true;  // quit the program
                        });
                return std::make_shared<GeneratedT>(functions, options, 
                        0, longest_option.length() * 2);
            }
        };  // class MainMenuFactory
    }  // namespace shell_ui
}  // namespace terminal_user_interface

#endif

