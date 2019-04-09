#ifndef TERMINAL_USER_INTERFACE__NCURSES_HELPER__NCURSES_MENU_OBJECT_CC
#define TERMINAL_USER_INTERFACE__NCURSES_HELPER__NCURSES_MENU_OBJECT_CC

#include "ncurses_helper/ncurses_menu_object.hh"

#include <string>

using terminal_user_interface::ncurses_helper::windows::win_coord_t;
using terminal_user_interface::ncurses_helper::windows::win_size_t;

namespace terminal_user_interface {
    namespace ncurses_helper {
        template <template <class...> class ContainerT>
        const menu_option_t NCursesMenuObject<ContainerT>::no_option_index = -1;

        template <template <class...> class ContainerT>
        NCursesMenuObject<ContainerT>::NCursesMenuObject(const ContainerT<std::string>&,
                win_size_t height, win_size_t width, 
                win_coord_t start_y, win_coord_t start_x)
            : NCursesObject(get_min_height(height), get_min_width(width), start_y, start_x) {
            // TODO: implement
        }

        template <template <class...> class ContainerT>
        void NCursesMenuObject<ContainerT>::mvwprint(win_coord_t y, win_coord_t x) {
            // TODO: implement
        }

        template <template <class...> class ContainerT>
        void NCursesMenuObject<ContainerT>::select_option(menu_option_t option_index) {
            // TODO: implement
        }

        template <template <class...> class ContainerT>
        void NCursesMenuObject<ContainerT>::deselect() {
            // TODO: implement
        }

        template <template <class...> class ContainerT>
        bool NCursesMenuObject<ContainerT>::is_selected() const noexcept {
            // TODO implement
            return false;
        }

        template <template <class...> class ContainerT>
        menu_option_t NCursesMenuObject<ContainerT>::get_selected_option() const noexcept {
            // TODO implement
            return 0;
        }

        template <template <class...> class ContainerT>
        win_size_t NCursesMenuObject<ContainerT>::get_min_height(
                win_size_t height) const noexcept {
            // TODO: implement
            return 0;
        }

        template <template <class...> class ContainerT>
        win_size_t NCursesMenuObject<ContainerT>::get_min_width(
                win_size_t width) const noexcept {
            // TODO: implement
            return 0;
        }
    }  // namespace ncurses_helper
}  // namespace terminal_user_interface

#endif

