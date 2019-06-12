#include "poker_api/authentication.hh"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <curl/curl.h>
#include <memory>

#include <ncurses.h>
#include "lib/nlohmann/json/json.hpp"

using nlohmann::json;

namespace {
    size_t write_callback(void *, size_t, size_t, void *);
}  // anonymous namespace

namespace terminal_user_interface {
    namespace poker_api {
        json register_user(url_t target_url, username_t username, 
                display_name_t display_name, 
                password_t password, password_t password_confirmation) noexcept {
            static size_t static_post_data_size = std::strlen("display_name=&username=&password=&password_confirmation=");

            size_t post_data_size = static_post_data_size 
                + username.length()
                + display_name.length() 
                + password.length() 
                + password_confirmation.length();
            auto post_data = std::unique_ptr<char[]>(new char[post_data_size + 1]);
            CURL *curl;
            CURLcode res;
            json read_json;

            // Format data to POST to server
            std::sprintf(post_data.get(), 
                    "display_name=%s&username=%s&password=%s&password_confirmation=%s",
                    display_name.c_str(), username.c_str(), 
                    password.c_str(), password_confirmation.c_str());

            curl_global_init(CURL_GLOBAL_ALL);  // initialize cURL global config
            curl = curl_easy_init();
            if (curl) {
                // set various cURL options
                curl_easy_setopt(curl, CURLOPT_URL, target_url.c_str());
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.get());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_json);
                res = curl_easy_perform(curl);  // execute cURL request
                if (res != CURLE_OK) {
                    // TODO: throw some sort of exception here
                    endwin();
                    std::cerr << "curl_easy_perform() failed: " 
                        << curl_easy_strerror(res) << std::endl;
                    std::exit(0);
                }
                curl_easy_cleanup(curl);
            }
            curl_global_cleanup();
            return read_json;
        }
    }  // namespace poker_api
}  // namespace terminal_user_interface

namespace {
    size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
        std::string read_buffer(static_cast<char *>(contents), size * nmemb);
        *static_cast<json *>(userp) = json::parse(read_buffer);
        return size * nmemb;
    }
}  // anonymous namespace

