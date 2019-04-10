#include "catch2/catch.hpp"
#include "__test/test_helper.hh"
#include "std_helper/string.hh"

#include <string>
#include <sstream>
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

    SECTION("can pad the string with additional characters") {
        std::string str("string");
        size_t n = GENERATE(0, 2);
        char c = ' ';

        SECTION("pad left side") {
            std::ostringstream expected_result;
            std::string result = lpad_string(str, n, c);
            for (register size_t i = 0; i < n; ++i) expected_result << c;
            expected_result << str;
            REQUIRE(result.length() == str.length() + n);
            REQUIRE(result == expected_result.str());
        }

        SECTION("pad right side") {
            std::ostringstream expected_result;
            std::string result = rpad_string(str, n, c);
            expected_result << str;
            for (register size_t i = 0; i < n; ++i) expected_result << c;
            REQUIRE(result.length() == str.length() + n);
            REQUIRE(result == expected_result.str());
        }

        SECTION("pad both sides of a string") {
            std::ostringstream expected_result;
            std::string result = pad_string(str, n, c);
            for (register size_t i = 0; i < n; ++i) expected_result << c;
            expected_result << str;
            for (register size_t i = 0; i < n; ++i) expected_result << c;
            REQUIRE(result.length() == str.length() + 2 * n);
            REQUIRE(result == expected_result.str());
        }
    }
}

