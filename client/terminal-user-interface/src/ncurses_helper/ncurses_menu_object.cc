#include "ncurses_helper/ncurses_menu_object.hh"

#include <algorithm>
#include <string>
#include <sstream>
#include <stdexcept>
#include <limits>

#include "std_helper/string.hh"
#include "ncurses_helper/exceptions/ncurses_exception.hh"

using terminal_user_interface::ncurses_helper::win_coord_t;
using terminal_user_interface::ncurses_helper::win_size_t;

namespace terminal_user_interface {
    namespace ncurses_helper {
        const menu_option_t NCursesMenuObject::no_option_index = std::numeric_limits<menu_option_t>::max();

        NCursesMenuObject::NCursesMenuObject(const std::vector<std::string>& options,
                win_size_t height, win_size_t width, 
                win_coord_t start_y, win_coord_t start_x)
            : NCursesObject(height, width, start_y, start_x),
              options_(options),
              selected_option_(no_option_index) {
        }

        void NCursesMenuObject::select_option(menu_option_t option_index) {
            if (option_index >= options_.size()) {
                std::ostringstream msg;
                msg << "invalid option index parsed (" << option_index << ")";
                throw std::invalid_argument(msg.str());
            }
            selected_option_ = option_index;
        }

        void NCursesMenuObject::select_next_option(bool erroneous) {
            if (selected_option_ == no_option_index) {
                if (erroneous)
                    throw std::invalid_argument("no initial option selected");
            } else if (static_cast<size_t>(selected_option_ + 1) == options_.size()) {
                if (erroneous) {
                    std::ostringstream msg;
                    msg << "cannot select next option (next is " 
                        << selected_option_<< ")";
                    throw std::invalid_argument(msg.str());
                }
            } else {
                ++selected_option_;
            }
        }

        void NCursesMenuObject::select_previous_option(bool erroneous) {
            if (selected_option_ == no_option_index) {
                if (erroneous)
                    throw std::invalid_argument("no initial option selected");
            } else if (selected_option_ == 0) {
                if (erroneous) {
                    std::ostringstream msg;
                    msg << "cannot select previous option (previous is " 
                        << selected_option_<< ")";
                    throw std::invalid_argument(msg.str());
                }
            } else {
                --selected_option_;
            }
        }

        void NCursesMenuObject::deselect() noexcept {
            selected_option_ = no_option_index;
        }

        bool NCursesMenuObject::is_selected() const noexcept {
            return selected_option_ != no_option_index;
        }

        const std::vector<std::string>& NCursesMenuObject::get_options() const noexcept {
            return options_;
        }

        menu_option_t NCursesMenuObject::get_selected_option() const noexcept {
            return selected_option_;
        }
    }  // namespace ncurses_helper
}  // namespace terminal_user_interface

