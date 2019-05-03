# C++ source files of 'ncurses_helper' module's tests.
# They are prepended their module's relative path to the main Makefile.
NCURSES_HELPER__TEST_SRC := \
	windows_test.cc \
	colors_test.cc \
	ncurses_object_test.cc \
	ncurses_menu_object_test.cc \
	exceptions/ncurses_exception_test.cc
NCURSES_HELPER__TEST_SRC := $(patsubst %,$(TEST)/$(NCURSES_HELPER__MODULE_NAME)/%,$(NCURSES_HELPER__TEST_SRC))

# Object files of 'ncurses_helper' module's tests.
NCURSES_HELPER__TEST_OBJ := $(patsubst $(TEST)/%.cc,$(TEST_OBJ)/%.o,$(NCURSES_HELPER__TEST_SRC))

# Create required subdirectories for module's tests' object files
NCURSES_HELPER__TEST_OBJ_DIRS := $(subst $(TEST),$(TEST_OBJ),$(shell find $(TEST)/$(NCURSES_HELPER__MODULE_NAME)/ -type d))
$(foreach obj_dir,$(NCURSES_HELPER__TEST_OBJ_DIRS),$(shell mkdir -p $(obj_dir)))
# Create required subdirectories for module's tests' binaries
NCURSES_HELPER__TEST_BIN_DIRS := $(subst $(TEST),$(TEST_OUT),$(shell find $(TEST)/$(NCURSES_HELPER__MODULE_NAME)/ -type d))
$(foreach bin_dir,$(NCURSES_HELPER__TEST_BIN_DIRS),$(shell mkdir -p $(bin_dir)))

# C++ source files of 'ncurses_helper' module's test stubs
NCURSES_HELPER__TEST_STUBS_SRC := $(shell find $(SRC)/$(TEST_MODULE)/stubs/$(NCURSES_HELPER__MODULE_NAME)/ -type f -name '*.cc')
# Object files of 'ncurses_helper' module's test stubs
NCURSES_HELPER__TEST_STUBS_OBJ := $(patsubst $(SRC)/%.cc,$(OBJ)/%.o,$(NCURSES_HELPER__TEST_STUBS_SRC))

# Include module's tests as dependencies of the 'test' target.
ALL_TEST_TARGETS += ncurses_helper_test

.PHONY: ncurses_helper_test

# Make target for all of 'ncurses_helper' module's tests.
ncurses_helper_test: $(TEST_CONFIG_OBJ) $(TEST_HELPER_OBJ) $(NCURSES_HELPER__TEST_OBJ) \
		$(NCURSES_HELPER__TEST_STUBS_OBJ) $(HELPER_OBJ)
	@# Create temporary directory for tests' binaries.
	mkdir -p $(TEST_OUT)/$(NCURSES_HELPER__MODULE_NAME)
	@# Compile each test file into its own test binary.
	$(foreach obj, \
			  $(NCURSES_HELPER__TEST_OBJ), \
			  $(CXX) $(CXXFLAGS) -o $(patsubst $(TEST_OBJ)/%.o,$(TEST_OUT)/%,$(obj)) \
			  $(TEST_CONFIG_OBJ) $(TEST_HELPER_OBJ) $(NCURSES_HELPER__TEST_STUBS_OBJ) \
			  $(obj) $(HELPER_OBJ) $(LIBS)$(NEWLINE))
	@echo $(LOG_STAMP): $(NCURSES_HELPER__MODULE_NAME) tests compilation successful.

# Make target for 'ncurses_helper' module's tests' object files.
$(TEST_OBJ)/$(NCURSES_HELPER__MODULE_NAME)/%_test.o: $(TEST)/$(NCURSES_HELPER__MODULE_NAME)/%_test.cc \
		$(SRC)/$(NCURSES_HELPER__MODULE_NAME)/%.cc
	@# Create temporary directory for tests' object files.
	@mkdir -p $(TEST_OBJ)/$(NCURSES_HELPER__MODULE_NAME)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

