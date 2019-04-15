#ifndef TERMINAL_USER_INTERFACE__SHELL_UI__ALIGNED_TEXT_HH
#define TERMINAL_USER_INTERFACE__SHELL_UI__ALIGNED_TEXT_HH

#include <functional>
#include <string>
#include <vector>

#include "shell_ui/text.hh"
#include "ncurses_helper/windows.hh"

namespace terminal_user_interface {
    namespace shell_ui {
        class AlignedText: public Text {
        public:
            enum class AlignmentOption { left, right, center };
            explicit AlignedText(const std::string&, AlignmentOption = AlignmentOption::center,
                    ncurses_helper::win_coord_t = 0, ncurses_helper::win_coord_t = 0);
        protected:
            virtual void alter_split_text(std::vector<std::string>&) const override;
            void realign(AlignmentOption) noexcept;
        private:
            AlignmentOption alignment_;
        };  // class AlignedText
    }  // shell_ui
}  // namespace terminal_user_interface

#endif

