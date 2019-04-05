#include "ncurses_helper/colors.hh"

#include <ncurses.h>
#include <string>
#include <unordered_map>

namespace terminal_user_interface {
    namespace ncurses_helper {
        namespace colors {
            namespace {
                short current_id = 1;
                std::unordered_map<std::string, short> color_pairs;
            }  // private namespace

            int get_color_pair(const std::string& name) {
                return COLOR_PAIR(color_pairs[name]);
            }

            int add_color_pair(const std::string& name, short fg_color, short bg_color) {
                color_pairs.insert(std::make_pair(name, current_id));
                return init_pair(current_id++, fg_color, bg_color);
            }
        }  // namespace colors
    }  // namespace ncurses_helper
}  // namespace terminal_user_interface

