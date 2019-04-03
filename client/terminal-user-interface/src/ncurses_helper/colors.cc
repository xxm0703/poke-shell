#include "ncurses_helper/colors.hh"

#include <ncurses.h>
#include <string>
#include <unordered_map>

namespace terminal_user_interface {
    namespace ncurses_helper {
        namespace {
            short current_id = 1;
            std::unordered_map<const char *, short> color_pairs;
        }  // private namespace

        int add_color_pair(const std::string& name, short fg_color, short bg_color) {
            color_pairs[name.c_str()] = current_id;
            return init_pair(current_id++, fg_color, bg_color);
        }

        int get_color_pair(const std::string& name) {
            return COLOR_PAIR(color_pairs[name.c_str()]);
        }
    }  // namespace ncurses_helper
}  // namespace terminal_user_interface

