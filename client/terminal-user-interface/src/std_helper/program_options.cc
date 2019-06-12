#include <iostream>  // FIXME
#include <algorithm>
#include <string>

#include "std_helper/program_options.hh"

namespace terminal_user_interface {
    namespace std_helper {
        ProgramOptions::ProgramOptions(int argc, char **argv) noexcept {
            std::string option_value;

            options["__command__"] = argv[0];
            for (int i = 1; i < argc; ++i) {
                if (argv[i][0] == '-')  {  // command line option found
                    option_value = (i + 1 < argc && argv[i+1][0] != '-') ? argv[i+1] : "";
                    options[argv[i]] = option_value; 
                } 
            }
        }

        std::string ProgramOptions::option_value(const std::string& option) noexcept {
            return "";
        }

        bool ProgramOptions::has_option(const std::string& option) noexcept {
            return options.find(option) != options.end();
        }
    }  // namespace std_helper
}  // namespace terminal_user_interface

