#include "catch2/catch.hpp"
#include "__test/test_helper.hh"
#include "__test/stubs/ncurses_object_stub.hh"
#include "ncurses_helper/ncurses_object.hh"

#include <stdexcept>

#include <ncurses.h>
#include "ncurses_helper/ncurses_exception.hh"
#include "ncurses_helper/windows.hh"

using namespace terminal_user_interface;
using namespace terminal_user_interface::ncurses_helper;
using terminal_user_interface::ncurses_helper::win_coord_t;
using terminal_user_interface::ncurses_helper::win_size_t;
using terminal_user_interface::ncurses_helper::get_window_height;
using terminal_user_interface::ncurses_helper::get_window_width;
using terminal_user_interface::__test::NCursesObjectStub;

TEST_CASE("NCursesObject represents an ncurses window with some content", "[ncurses_helper::NCursesObject]") {
    SECTION("setup") {
        __test::ncurses_setup();
    }

    SECTION("object construction") {
        SECTION("with valid arguments") {
            win_size_t height = 10;
            win_size_t width = 10;
            win_coord_t y = 5;
            win_coord_t x = 5;

            SECTION("causes no errors") {
                REQUIRE_NOTHROW(NCursesObjectStub(height, width, y, x));
            }

            SECTION("can retrieve associated ncurses window") {
                NCursesObjectStub stub(height, width, y, x);

                REQUIRE(stub.get_win() != nullptr);
            }

            SECTION("starting coordinates default to 0") {
                NCursesObjectStub stub(height, width);
                WINDOW *stub_win = stub.get_win();

                REQUIRE(getcury(stub_win) == 0);
                REQUIRE(getcurx(stub_win) == 0);
            }
        }
        
        SECTION("with invalid arguments") {
            win_size_t height = 10;
            win_size_t width = 10;
            win_coord_t y = -5;
            win_coord_t x = 5;

            SECTION("throws NCursesException on instance creation") {
                REQUIRE_THROWS_AS(NCursesObjectStub(height, width, y, x), NCursesException);
                REQUIRE_THROWS_WITH(NCursesObjectStub(height, width, y, x), 
                        __test::ncurses_error_msg("newwin", nullptr));
            }
        }
    }

    SECTION("window manipulation") {
        ncurses_errno_t rc;
        win_size_t height = 10;
        win_size_t width = 10;
        win_coord_t start_y = 0;
        win_coord_t start_x = 0;
        NCursesObjectStub stub(height, width, start_y, start_x);
        WINDOW *stub_win = stub.get_win();

        SECTION("can clear the window") {
            win_coord_t move_y = 7;
            win_coord_t move_x = 9;

            rc = wmove(stub_win, move_y, move_x); 
            REQUIRE(rc != ERR);  // ensure ncurses does not return an error code
            // ensure stub window's cursor has been moved
            REQUIRE(getcury(stub_win) == move_y);
            REQUIRE(getcurx(stub_win) == move_x);

            REQUIRE_NOTHROW(stub.clear_window());
            // ensure stub window's cursor has been reset
            REQUIRE(getcury(stub_win) == 0);
            REQUIRE(getcurx(stub_win) == 0);
        }

        SECTION("can move the window") {
            SECTION("successfully moves window with valid coordinates") {
                win_coord_t move_y = 9;
                win_coord_t move_x = 8;

                REQUIRE(getbegy(stub_win) == start_y);
                REQUIRE(getbegx(stub_win) == start_x);

                stub.move_window(move_y, move_x);
                // ensure stub window's cursor has been reset
                REQUIRE(getbegy(stub_win) == move_y);
                REQUIRE(getbegx(stub_win) == move_x);
            }

            SECTION("throws error on invalid coordinates") {
                win_coord_t move_y = -1;
                win_coord_t move_x = 8;

                REQUIRE_THROWS_AS(stub.move_window(move_y, move_x), NCursesException);
                REQUIRE_THROWS_WITH(stub.move_window(move_y, move_x), 
                        __test::ncurses_error_msg("mvwin", ERR));
            }
        }

        SECTION("can center a window to another reference window") {
            SECTION("successfully center object's window") {
                win_size_t ref_height = 20;
                win_size_t ref_width = 80;
                win_coord_t ref_start_y = GENERATE(0, 3);
                win_coord_t ref_start_x = GENERATE(0, 3);
                WINDOW *ref_win = newwin(ref_height, ref_width, ref_start_y, ref_start_x);
                win_coord_t centered_y, centered_x;

                REQUIRE(ref_height >= height);
                REQUIRE(ref_width >= width);
                centered_y = ref_start_y + ref_height / 2 - height / 2;
                centered_x = ref_start_x + ref_width / 2 - width / 2;

                SECTION("in both dimensions") {
                    REQUIRE(getbegy(stub_win) == start_y);
                    REQUIRE(getbegx(stub_win) == start_x);

                    stub.center_window(ref_win, true, true);
                    REQUIRE(getbegy(stub_win) == centered_y);
                    REQUIRE(getbegx(stub_win) == centered_x);
                }

                SECTION("only vertically") {
                    REQUIRE(getbegy(stub_win) == start_y);
                    REQUIRE(getbegx(stub_win) == start_x);

                    stub.center_window(ref_win, true, false);
                    REQUIRE(getbegy(stub_win) == centered_y);
                    REQUIRE(getbegx(stub_win) == start_x);
                }

                SECTION("only horizontally") {
                    REQUIRE(getbegy(stub_win) == start_y);
                    REQUIRE(getbegx(stub_win) == start_x);

                    stub.center_window(ref_win, false, true);
                    REQUIRE(getbegy(stub_win) == start_y);
                    REQUIRE(getbegx(stub_win) == centered_x);
                }

                delwin(ref_win);
            } 

            SECTION("raises logic error if reference window is smaller than this window") {
                win_size_t ref_height = 6;
                win_size_t ref_width = 4;
                WINDOW *ref_win = newwin(ref_height, ref_width, 0, 0);

                REQUIRE_THROWS_AS(stub.center_window(ref_win), std::logic_error);

                delwin(ref_win);
            }
        }

        SECTION("can move the window") {
            SECTION("arbitrary move") {
                SECTION("with valid input") {
                    win_coord_t move_y = 5;
                    REQUIRE_NOTHROW(stub.move_y(move_y));
                    REQUIRE(getbegy(stub_win) == move_y);

                    win_coord_t move_x = 7;
                    REQUIRE_NOTHROW(stub.move_x(move_x));
                    REQUIRE(getbegx(stub_win) == move_x);
                }

                SECTION("with invalid input") {
                    win_coord_t move_y = -1;
                    REQUIRE_THROWS_AS(stub.move_y(move_y), NCursesException);

                    win_coord_t move_x = -23;
                    REQUIRE_THROWS_AS(stub.move_x(move_x), NCursesException);
                }
            }

            SECTION("applying an offset") {
                SECTION("with valid input") {
                    win_coord_t move_y = 5;
                    win_coord_t offset_y = 2;
                    stub.move_y(move_y);
                    REQUIRE_NOTHROW(stub.offset_y(offset_y));
                    REQUIRE(getbegy(stub_win) == move_y + offset_y);

                    win_coord_t move_x = 4;
                    win_coord_t offset_x = 4;
                    stub.move_x(move_x);
                    REQUIRE_NOTHROW(stub.offset_x(offset_x));
                    REQUIRE(getbegx(stub_win) == move_x + offset_x);
                }

                SECTION("with invalid input") {
                    win_coord_t move_y = 5;
                    win_coord_t offset_y = -7;
                    stub.move_y(move_y);
                    REQUIRE_THROWS_AS(stub.offset_y(offset_y), NCursesException);

                    win_coord_t move_x = 4;
                    win_coord_t offset_x = -8;
                    stub.move_x(move_x);
                    REQUIRE_THROWS_AS(stub.offset_x(offset_x), NCursesException);
                }
            }

            SECTION("centering") {
                win_size_t ref_height = 20;
                win_size_t ref_width = 80;
                win_coord_t ref_start_y = GENERATE(0, 3);
                win_coord_t ref_start_x = GENERATE(0, 3);
                WINDOW *ref_win = newwin(ref_height, ref_width, ref_start_y, ref_start_x);
                win_coord_t centered_y, centered_x;

                REQUIRE(ref_height >= height);
                REQUIRE(ref_width >= width);
                centered_y = ref_start_y + ref_height / 2 - height / 2;
                centered_x = ref_start_x + ref_width / 2 - width / 2;

                SECTION("vertically") {
                    stub.center_y(ref_win);
                    REQUIRE(getbegy(stub_win) == centered_y);
                    REQUIRE(getbegx(stub_win) == start_x);
                }

                SECTION("horizontally") {
                    stub.center_x(ref_win);
                    REQUIRE(getbegy(stub_win) == start_y);
                    REQUIRE(getbegx(stub_win) == centered_x);
                }

                delwin(ref_win);
            }

            SECTION("anchoring") {
                win_size_t ref_height = 10;
                win_size_t ref_width = 40;
                win_coord_t ref_start_y = GENERATE(0, 3);
                win_coord_t ref_start_x = GENERATE(0, 3);
                WINDOW *ref_win = newwin(ref_height, ref_width, ref_start_y, ref_start_x);
                win_coord_t anchored_y, anchored_x;

                REQUIRE(ref_height >= height);
                REQUIRE(ref_width >= width);
                anchored_y = get_window_height(ref_win) - 1;
                anchored_x = get_window_width(ref_win) - 1;

                SECTION("vertically") {
                    stub.anchor_y(ref_win);
                    REQUIRE(getbegy(stub_win) == anchored_y);
                    REQUIRE(getbegx(stub_win) == start_x);
                }

                SECTION("horizontally") {
                    stub.anchor_x(ref_win);
                    REQUIRE(getbegy(stub_win) == start_y);
                    REQUIRE(getbegx(stub_win) == anchored_x);
                }

                delwin(ref_win);
            }
        }
    }

    SECTION("teardown") {
        __test::ncurses_teardown();
    }
}

