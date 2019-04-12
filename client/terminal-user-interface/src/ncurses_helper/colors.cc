#include "ncurses_helper/colors.hh"

#include <string>
#include <stdexcept>
#include <unordered_map>

#include <ncurses.h>
#include "ncurses_helper/ncurses_exception.hh"

namespace terminal_user_interface {
    namespace ncurses_helper {
        namespace {
            short current_id = 1;
            std::unordered_map<std::string, short> color_pairs;
        }  // private namespace

        void add_color_pair(const std::string& name, color_t fg_color, 
                color_t bg_color) {
            int rc;

            if (fg_color < 0 || bg_color < 0)  // invalid color number
                throw std::invalid_argument("Invalid color number parsed");
                    
            color_pairs.insert(std::make_pair(name, current_id));
            rc = init_pair(current_id++, fg_color, bg_color);
            if (rc == ERR) throw NCursesException("init_pair", rc);
        }

        color_pair_t get_color_pair(const std::string& name) {
            return COLOR_PAIR(color_pairs.at(name));
        }

        void _flush_color_pair_map() noexcept {
            color_pairs.clear();
        }
    }  // namespace ncurses_helper
}  // namespace terminal_user_interface

