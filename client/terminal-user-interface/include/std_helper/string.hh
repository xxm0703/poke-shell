#ifndef TERMINAL_USER_INTERFACE__STD_HELPER__STRING_HH
#define TERMINAL_USER_INTERFACE__STD_HELPER__STRING_HH

#include <vector>
#include <string>

namespace terminal_user_interface {
    namespace std_helper {
        namespace string {
            const std::string& get_longest_string(const std::vector<std::string>&);
            std::string lpad_string(const std::string&, size_t, char = ' ');
            std::string rpad_string(const std::string&, size_t, char = ' ');
            std::string pad_string(const std::string&, size_t, char = ' ');
            std::vector<std::string> split(const std::string&, 
                    const char * = " ") noexcept;
        }  // namespace string
    }  // namespace std_helper
}  // namespace terminal_user_interface

#endif

