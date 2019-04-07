#include "catch2/catch.hpp"
#include "__test/test_helper.hh"
#include "ncurses_helper/ncurses_object.hh"

#include <stdexcept>

#include <ncurses.h>
#include "ncurses_helper/ncurses_exception.hh"

using namespace terminal_user_interface;
using namespace terminal_user_interface::ncurses_helper;

namespace {
    class NCursesObjectStub: public NCursesObject {
    public:
        NCursesObjectStub(int, int, int = 0, int = 0);
        void mvwprint(int = 0, int = 0) noexcept final;
    };  // class NCursesObjectStub

    inline NCursesObjectStub::NCursesObjectStub(int height, int width, 
            int start_y, int start_x)
        : NCursesObject(height, width, start_y, start_x) {
    }

    inline void NCursesObjectStub::mvwprint(int y, int x) noexcept {
        if (y) {}  // do nothing
        if (x) {}  // do nothing
    }
}  // anonymous namespace

TEST_CASE("NCursesObject represents an ncurses window with some content", "[NCursesObject]") {
    SECTION("setup") {
        __test::ncurses_helper::ncurses_setup();
    }

    SECTION("object construction") {
        SECTION("with valid arguments") {
            int height = 10;
            int width = 10;
            int y = 5;
            int x = 5;

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
            int height = 10;
            int width = 10;
            int y = -5;
            int x = 5;

            SECTION("throws NCursesException on instance creation") {
                REQUIRE_THROWS_AS(NCursesObjectStub(height, width, y, x), NCursesException);
                REQUIRE_THROWS_WITH(NCursesObjectStub(height, width, y, x), 
                        __test::ncurses_helper::ncurses_error_msg("newwin", nullptr));
            }
        }
    }

    SECTION("window manipulation") {
        int rc;
        int height = 10;
        int width = 10;
        int start_y = 0;
        int start_x = 0;
        NCursesObjectStub stub(height, width, start_y, start_x);
        WINDOW *stub_win = stub.get_win();

        SECTION("can clear the window") {
            int move_y = 7;
            int move_x = 9;

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
                int move_y = 9;
                int move_x = 8;

                REQUIRE(getbegy(stub_win) == start_y);
                REQUIRE(getbegx(stub_win) == start_x);

                stub.move_window(move_y, move_x);
                // ensure stub window's cursor has been reset
                REQUIRE(getbegy(stub_win) == move_y);
                REQUIRE(getbegx(stub_win) == move_x);
            }

            SECTION("throws error on invalid coordinates") {
                int move_y = -1;
                int move_x = 8;

                REQUIRE_THROWS_AS(stub.move_window(move_y, move_x), NCursesException);
                REQUIRE_THROWS_WITH(stub.move_window(move_y, move_x), 
                        __test::ncurses_helper::ncurses_error_msg("mvwin", ERR));
            }
        }

        SECTION("can center a window to another reference window") {
            SECTION("successfully center object's window") {
                int ref_height = 20;
                int ref_width = 80;
                int ref_start_y = GENERATE(0, 3);
                int ref_start_x = GENERATE(0, 3);
                WINDOW *ref_win = newwin(ref_height, ref_width, ref_start_y, ref_start_x);
                int centered_y, centered_x;

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
                int ref_height = 6;
                int ref_width = 4;
                WINDOW *ref_win = newwin(ref_height, ref_width, 0, 0);

                REQUIRE_THROWS_AS(stub.center_window(ref_win), std::logic_error);

                delwin(ref_win);
            }
        }

        SECTION("can move the window") {
            SECTION("arbitrary move") {
                SECTION("with valid input") {
                    int move_y = 5;
                    REQUIRE_NOTHROW(stub.move_y(move_y));
                    REQUIRE(getbegy(stub_win) == move_y);

                    int move_x = 7;
                    REQUIRE_NOTHROW(stub.move_x(move_x));
                    REQUIRE(getbegx(stub_win) == move_x);
                }

                SECTION("with invalid input") {
                    int move_y = -1;
                    REQUIRE_THROWS_AS(stub.move_y(move_y), NCursesException);

                    int move_x = -23;
                    REQUIRE_THROWS_AS(stub.move_x(move_x), NCursesException);
                }
            }

            SECTION("applying an offset") {
                SECTION("with valid input") {
                    int move_y = 5;
                    int offset_y = 2;
                    stub.move_y(move_y);
                    REQUIRE_NOTHROW(stub.offset_y(offset_y));
                    REQUIRE(getbegy(stub_win) == move_y + offset_y);

                    int move_x = 4;
                    int offset_x = 4;
                    stub.move_x(move_x);
                    REQUIRE_NOTHROW(stub.offset_x(offset_x));
                    REQUIRE(getbegx(stub_win) == move_x + offset_x);
                }

                SECTION("with invalid input") {
                    int move_y = 5;
                    int offset_y = -7;
                    stub.move_y(move_y);
                    REQUIRE_THROWS_AS(stub.offset_y(offset_y), NCursesException);

                    int move_x = 4;
                    int offset_x = -8;
                    stub.move_x(move_x);
                    REQUIRE_THROWS_AS(stub.offset_x(offset_x), NCursesException);
                }
            }

            SECTION("centering") {
                int ref_height = 20;
                int ref_width = 80;
                int ref_start_y = GENERATE(0, 3);
                int ref_start_x = GENERATE(0, 3);
                WINDOW *ref_win = newwin(ref_height, ref_width, ref_start_y, ref_start_x);
                int centered_y, centered_x;

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
            }
        }
    }

    SECTION("teardown") {
        __test::ncurses_helper::ncurses_teardown();
    }
}

