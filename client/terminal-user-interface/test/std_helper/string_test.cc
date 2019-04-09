#include "catch2/catch.hpp"
#include "__test/test_helper.hh"
#include "std_helper/string.hh"

#include <string>
#include <vector>
#include <stdexcept>

using namespace terminal_user_interface;
using namespace terminal_user_interface::std_helper;
using namespace terminal_user_interface::std_helper::string;

TEST_CASE("Provides helper functions for use with std::string", "[std::string]") {
    SECTION("can get the longest string of a sequence") {
        SECTION("with non-empty sequence of strings") {
            std::vector<std::string> v{"Start", "Hello World", "Bye"};

            REQUIRE(get_longest_string(v) == "Hello World");
        }

        SECTION("throws error on empty container") {
            std::vector<std::string> v;

            REQUIRE_THROWS_AS(get_longest_string(v), std::runtime_error);
        }
    }
}

