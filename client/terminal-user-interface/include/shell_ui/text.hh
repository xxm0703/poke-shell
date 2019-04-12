#ifndef TERMINAL_USER_INTERFACE__SHELL_UI__TEXT_HH
#define TERMINAL_USER_INTERFACE__SHELL_UI__TEXT_HH

#include <string>

#include "ncurses_helper/windows.hh"
#include "ncurses_helper/ncurses_object.hh"

namespace terminal_user_interface {
    namespace shell_ui {
        class Text: public ncurses_helper::NCursesObject {
        public:
            explicit Text(const std::string&, ncurses_helper::win_coord_t = 0,
                    ncurses_helper::win_coord_t = 0);
            void mvwprint(ncurses_helper::win_coord_t = 0,
                    ncurses_helper::win_coord_t = 0) override;
            std::string get_text() const noexcept;
        private:
            std::string text_;
            ncurses_helper::win_size_t calc_height(const std::string&) noexcept;
            ncurses_helper::win_size_t calc_width(const std::string&) noexcept;
        };  // class Text
    }  // namespace shell_ui
}  // namespace terminal_user_interface

#endif

