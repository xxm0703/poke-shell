# C++ source files of 'ncurses_helper' module's tests.
# They are prepended their module's relative path to the main Makefile.
NCURSES_HELPER__TEST_SRC :=
NCURSES_HELPER__TEST_SRC := $(patsubst %,$(TEST)/$(NCURSES_HELPER__MODULE_NAME)/%,$(NCURSES_HELPER__TEST_SRC))

# Object files of 'ncurses_helper' module's tests.
NCURSES_HELPER__TEST_OBJ := $(patsubst $(TEST)/%.cc,$(TEST_OBJ)/%.o,$(NCURSES_HELPER__TEST_SRC))

# Include module's tests as dependencies of the 'test' target.
ALL_TEST_TARGETS += ncurses_helper_test

.PHONY: ncurses_helper_test

# Make target for all of 'ncurses_helper' module's tests.
ncurses_helper_test: setup_testing $(NCURSES_HELPER__TEST_OBJ) $(HELPER_OBJ)
	@# Create temporary directory for tests' binaries.
	mkdir -p $(TEST_OUT)/$(NCURSES_HELPER__MODULE_NAME)
	@# Compile each test file into its own test binary.
	$(foreach obj, \
			  $(NCURSES_HELPER__TEST_OBJ), \
			  $(CXX) $(CXXFLAGS) $(TEST_CONFIG_OBJ) $(obj) $(HELPER_OBJ) \
			  -o $(patsubst $(TEST_OBJ)/%.o,$(TEST_OUT)/%,$(obj))$(NEWLINE))
	@echo $(LOG_STAMP): $(NCURSES_HELPER__MODULE_NAME) tests compilation successful.

# Make target for 'ncurses_helper' module's tests' object files.
$(TEST_OBJ)/$(NCURSES_HELPER__MODULE_NAME)/%.o: $(TEST)/$(NCURSES_HELPER__MODULE_NAME)/%.cc
	@# Create temporary directory for tests' object files.
	@mkdir -p $(TEST_OBJ)/$(NCURSES_HELPER__MODULE_NAME)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

