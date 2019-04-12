#include "catch2/catch.hpp"
#include "__test/test_helper.hh"
#include "std_helper/string.hh"

#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>

using namespace terminal_user_interface;
using namespace terminal_user_interface::std_helper;

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

    SECTION("can split a string into an array of substrings") {
        SECTION("with a single word") {
            std::string str("Line");
            std::vector<std::string> result = split(str);
            REQUIRE(result.size() == 1);
            REQUIRE(result[0] == "Line");
        }

        SECTION("with multiple words") {
            std::string str("Multiple words sentence");
            std::vector<std::string> result = split(str);
            REQUIRE(result.size() == 3);
            REQUIRE(result[0] == "Multiple");
            REQUIRE(result[1] == "words");
            REQUIRE(result[2] == "sentence");
        }

        SECTION("with a custom delimiter") {
            SECTION("and string with no occurrence of this delimiter") {
                std::string str("Multiple words sentence");
                std::vector<std::string> result = split(str, "\n");
                REQUIRE(result.size() == 1);
                REQUIRE(result[0] == "Multiple words sentence");
            }

            SECTION("and string with occurrences of this delimiter") {
                std::string str("Multiple\nwords\nsentence");
                std::vector<std::string> result = split(str, "\n");
                REQUIRE(result.size() == 3);
                REQUIRE(result[0] == "Multiple");
                REQUIRE(result[1] == "words");
                REQUIRE(result[2] == "sentence");
            }

            SECTION("which is made of multiple symbols") {
                std::string str("Multiple->words->sentence");
                std::vector<std::string> result = split(str, "->");
                REQUIRE(result.size() == 3);
                REQUIRE(result[0] == "Multiple");
                REQUIRE(result[1] == "words");
                REQUIRE(result[2] == "sentence");
            }
        }
    }
}

