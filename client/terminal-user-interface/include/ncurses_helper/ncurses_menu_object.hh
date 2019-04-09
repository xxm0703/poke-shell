#ifndef TERMINAL_USER_INTERFACE__NCURSES_HELPER__NCURSES_MENU_OBJECT_HH
#define TERMINAL_USER_INTERFACE__NCURSES_HELPER__NCURSES_MENU_OBJECT_HH

#include <string>
#include <vector>

#include "ncurses_helper/ncurses_object.hh"

namespace terminal_user_interface {
    namespace ncurses_helper {
        using menu_option_t = int;

        template <template <class...> class ContainerT = std::vector>
        class NCursesMenuObject: public NCursesObject {
        public:
            static const menu_option_t no_option_index;
            explicit NCursesMenuObject(const ContainerT<std::string>&,
                    windows::win_size_t = 0, windows::win_size_t = 0, 
                    windows::win_coord_t = 0, windows::win_coord_t = 0);
            virtual void mvwprint(windows::win_coord_t, windows::win_coord_t) override;
            void select_option(menu_option_t);
            void deselect();
            bool is_selected() const noexcept;
            menu_option_t get_selected_option() const noexcept;
        protected:
            virtual windows::win_size_t get_min_height(windows::win_size_t) const noexcept;
            virtual windows::win_size_t get_min_width(windows::win_size_t) const noexcept;
        private:
            std::vector<std::string> options_;
            menu_option_t selected_option_;
        };  // class NCursesMenuObject
    }  // namespace ncurses_helper
}  // namespace terminal_user_interface

#include "ncurses_helper/ncurses_menu_object.cc"

#endif

