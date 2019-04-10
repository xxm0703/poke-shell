#ifndef TERMINAL_USER_INTERFACE__NCURSES_HELPER__NCURSES_MENU_OBJECT_HH
#define TERMINAL_USER_INTERFACE__NCURSES_HELPER__NCURSES_MENU_OBJECT_HH

#include <string>
#include <vector>

#include "ncurses_helper/ncurses_object.hh"

namespace terminal_user_interface {
    namespace ncurses_helper {
        using menu_option_t = unsigned short;

        class NCursesMenuObject: public NCursesObject {
        public:
            static const menu_option_t no_option_index;
            explicit NCursesMenuObject(const std::vector<std::string>&,
                    win_size_t = 0, win_size_t = 0, 
                    win_coord_t = 0, win_coord_t = 0);
            void select_option(menu_option_t);
            void deselect() noexcept;
            bool is_selected() const noexcept;
            const std::vector<std::string>& get_options() const noexcept;
            menu_option_t get_selected_option() const noexcept;
        protected:
            virtual win_size_t calc_height(win_size_t,
                    const std::vector<std::string>&) const = 0;
            virtual win_size_t calc_width(win_size_t, 
                    const std::vector<std::string>&) const = 0;
        private:
            std::vector<std::string> options_;
            menu_option_t selected_option_;
        };  // class NCursesMenuObject
    }  // namespace ncurses_helper
}  // namespace terminal_user_interface

#endif

