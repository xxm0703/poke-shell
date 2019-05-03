# C++ source files of 'poker_api' module's tests.
# They are prepended their module's relative path to the main Makefile.
POKER_API__TEST_SRC :=
POKER_API__TEST_SRC := $(patsubst %,$(TEST)/$(POKER_API__MODULE_NAME)/%,$(POKER_API__TEST_SRC))

# Object files of 'poker_api' module's tests.
POKER_API__TEST_OBJ := $(patsubst $(TEST)/%.cc,$(TEST_OBJ)/%.o,$(POKER_API__TEST_SRC))

# Create required subdirectories for module's tests' object files
POKER_API__TEST_OBJ_DIRS := $(subst $(TEST),$(TEST_OBJ),$(shell find $(TEST)/$(POKER_API__MODULE_NAME)/ -type d))
$(foreach obj_dir,$(POKER_API__TEST_OBJ_DIRS),$(shell mkdir -p $(obj_dir)))
# Create required subdirectories for module's tests' binaries
POKER_API__TEST_BIN_DIRS := $(subst $(TEST),$(TEST_OUT),$(shell find $(TEST)/$(POKER_API__MODULE_NAME)/ -type d))
$(foreach bin_dir,$(POKER_API__TEST_BIN_DIRS),$(shell mkdir -p $(bin_dir)))

# C++ source files of 'poker_api' module's test stubs
POKER_API__TEST_STUBS_SRC := $(shell find $(SRC)/$(TEST_MODULE)/stubs/$(POKER_API__MODULE_NAME)/ -type f -name '*.cc')
# Object files of 'poker_api' module's test stubs
POKER_API__TEST_STUBS_OBJ := $(patsubst $(SRC)/%.cc,$(OBJ)/%.o,$(POKER_API__TEST_STUBS_SRC))

# Include module's tests as dependencies of the 'test' target.
ALL_TEST_TARGETS += poker_api_test

.PHONY: poker_api_test

# Make target for all of 'poker_api' module's tests.
poker_api_test: $(TEST_CONFIG_OBJ) $(TEST_HELPER_OBJ) $(POKER_API__TEST_OBJ) \
		$(POKER_API__TEST_STUBS_OBJ) $(HELPER_OBJ)
	@# Create temporary directory for tests' binaries.
	mkdir -p $(TEST_OUT)/$(POKER_API__MODULE_NAME)
	@# Compile each test file into its own test binary.
	$(foreach obj, \
			  $(POKER_API__TEST_OBJ), \
			  $(CXX) $(CXXFLAGS) -o $(patsubst $(TEST_OBJ)/%.o,$(TEST_OUT)/%,$(obj)) \
			  $(TEST_CONFIG_OBJ) $(TEST_HELPER_OBJ) $(POKER_API__TEST_STUBS_OBJ) \
			  $(obj) $(HELPER_OBJ) $(LIBS)$(NEWLINE))
	@echo $(LOG_STAMP): $(POKER_API__MODULE_NAME) tests compilation successful.

# Make target for 'poker_api' module's tests' object files.
$(TEST_OBJ)/$(POKER_API__MODULE_NAME)/%_test.o: $(TEST)/$(POKER_API__MODULE_NAME)/%_test.cc \
		$(SRC)/$(POKER_API__MODULE_NAME)/%.cc
	@# Create temporary directory for tests' object files.
	@mkdir -p $(TEST_OBJ)/$(POKER_API__MODULE_NAME)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

