#ifndef TERMINAL_USER_INTERFACE__STD_HELPER_PROGRAM_OPTIONS_HH
#define TERMINAL_USER_INTERFACE__STD_HELPER_PROGRAM_OPTIONS_HH

#include <unordered_map>
#include <string>

namespace terminal_user_interface {
    namespace std_helper {
        class ProgramOptions {
        public:
            explicit ProgramOptions(int, char **) noexcept;
            std::string option_value(const std::string&) noexcept;
            bool has_option(const std::string&) noexcept;
        private:
            std::unordered_map<std::string, std::string> options;
        };  // class ProgramOptions
    }  // namespace std_helper
}  // namespace terminal_user_interface

#endif

