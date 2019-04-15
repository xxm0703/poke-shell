#include "shell_ui/aligned_text.hh"

#include <unordered_map>
#include <functional>
#include <string>
#include <vector>

#include "std_helper/string.hh"

using terminal_user_interface::ncurses_helper::win_coord_t;

namespace terminal_user_interface {
    namespace shell_ui {
        namespace {
            void left_align(std::string& str, size_t ref_size) {
                size_t pad_size = ref_size - str.length();

                str = std_helper::rpad_string(str, pad_size);
            }

            void right_align(std::string& str, size_t ref_size) {
                size_t pad_size = ref_size - str.length();

                str = std_helper::lpad_string(str, pad_size);
            }

            void center_align(std::string& str, size_t ref_size) {
                size_t pad_size = (ref_size - str.length()) / 2;

                str = std_helper::pad_string(str, pad_size);
            }

            std::unordered_map<AlignedText::AlignmentOption, 
                std::function<void(std::string&, size_t)>> alignments({
                        { AlignedText::AlignmentOption::left, left_align },
                        { AlignedText::AlignmentOption::right, right_align },
                        { AlignedText::AlignmentOption::center, center_align }
                        });
        }  // anonymous namespace

        AlignedText::AlignedText(const std::string& text, AlignmentOption alignment,
                win_coord_t start_y, win_coord_t start_x)
            : Text(text, start_y, start_x),
              alignment_(alignment) {
        }

        void AlignedText::alter_split_text(std::vector<std::string>& text_lines) const {
            std::string longest_line = std_helper::get_longest_string(text_lines);
            for (auto& line : text_lines)
                alignments[alignment_](line, longest_line.length());
        }
        
        void AlignedText::realign(AlignedText::AlignmentOption alignment) noexcept {
            alignment_ = alignment;
        }
    }  // shell_ui
}  // namespace terminal_user_interface

