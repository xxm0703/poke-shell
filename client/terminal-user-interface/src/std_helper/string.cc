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

            std::string lpad_string(const std::string& str, size_t n, char c) {
                std::string res(str);

                res.insert(0, n, c);
                return res;
            }

            std::string rpad_string(const std::string& str, size_t n, char c) {
                std::string res(str);

                res.append(n, c);
                return res;
            }

            std::string pad_string(const std::string& str, size_t n, char c) {
                std::string res(str);

                res.insert(0, n, c);
                res.append(n, c);
                return res;
            }
        }  // namespace string
    }  // namespace std_helper
}  // namespace terminal_user_interface

