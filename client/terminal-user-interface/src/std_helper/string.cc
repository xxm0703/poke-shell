#include "std_helper/string.hh"

#include <algorithm>
#include <string>
#include <vector>
#include <stdexcept>

namespace terminal_user_interface {
    namespace std_helper {
        namespace string {
            const std::string& get_longest_string(const std::vector<std::string>& v) {
                if (v.empty()) throw std::runtime_error("empty sequence of strings presented");

                return *std::max_element(v.begin(), v.end(), 
                        [](const std::string& a, const std::string& b) {
                            return a.length() < b.length();
                        });
            }
        }  // namespace string
    }  // namespace std_helper
}  // namespace terminal_user_interface

