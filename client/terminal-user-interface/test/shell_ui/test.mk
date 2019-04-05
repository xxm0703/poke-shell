# C++ source files of 'shell_ui' module's tests.
# They are prepended their module's relative path to the main Makefile.
SHELL_UI__TEST_SRC :=
SHELL_UI__TEST_SRC := $(patsubst %,$(TEST)/$(SHELL_UI__MODULE_NAME)/%,$(SHELL_UI__TEST_SRC))

# Object files of 'shell_ui' module's tests.
SHELL_UI__TEST_OBJ := $(patsubst $(TEST)/%.cc,$(TEST_OBJ)/%.o,$(SHELL_UI__TEST_SRC))

# Include module's tests as dependencies of the 'test' target.
ALL_TEST_TARGETS += shell_ui_test

.PHONY: shell_ui_test

# Make target for all of 'shell_ui' module's tests.
shell_ui_test: setup_testing $(SHELL_UI__TEST_OBJ) $(SHELL_UI__OBJ) $(HELPER_OBJ)
	@# Create temporary directory for tests' binaries.
	mkdir -p $(TEST_OUT)/$(SHELL_UI__MODULE_NAME)
	@# Compile each test file into its own test binary.
	$(foreach obj, \
			  $(SHELL_UI__TEST_OBJ), \
			  $(CXX) $(CXXFLAGS) $(TEST_CONFIG_OBJ) $(obj) $(SHELL_UI__OBJ) $(HELPER_OBJ) \
			  -o $(patsubst $(TEST_OBJ)/%.o,$(TEST_OUT)/%,$(obj))$(NEWLINE))
	@echo $(LOG_STAMP): $(SHELL_UI__MODULE_NAME) tests compilation successful.

# Make target for 'shell_ui' module's tests' object files.
$(TEST_OBJ)/$(SHELL_UI__MODULE_NAME)/%.o: $(TEST)/$(SHELL_UI__MODULE_NAME)/%.cc
	@# Create temporary directory for tests' object files.
	@mkdir -p $(TEST_OBJ)/$(SHELL_UI__MODULE_NAME)
	$(CXX) $(CXXFLAGS) -o $@ -c $<
