# Newline character which may be expanded via '$(NEWLINE)'
define NEWLINE


endef

# A timestamp which should prefix every log message.
LOG_STAMP = \(log $(shell date '+%Y-%m-%d,%H:%M:%S')\)

# All directories and files which contain the 
# project's necessary C++ header files.
INCLUDE := include
# Furthermore, source files are also included because of the following reason: if
# any header defines a template class/function, its implementing source code
# must also be included. Otherwise, the linker reports a linking error.
INCLUDE_SRC := src

# All project executables should go into this directory.
BIN := bin

# All C++ source files (inside modules) should go into this directory.
SRC := src

# All object files should go into this directory.
OBJ := tmp/obj

# All C++ unit test files (using 'Catch2')
TEST := test
# Output directory of compiled C++ unit test binaries
TEST_OUT := $(BIN)/test
# Output directory of compiled C++ unit test object files
TEST_OBJ := $(OBJ)/test
# Configuration file for 'Catch2'
TEST_CONFIG_FILENAME = config
TEST_CONFIG_FILE := $(TEST)/$(TEST_CONFIG_FILENAME).cc
# Compiled configuration object file for 'Catch2'
TEST_CONFIG_OBJ := $(TEST_OBJ)/$(TEST_CONFIG_FILENAME).o
# Compiled config binary with empty example test for 'Catch2'
TEST_CONFIG_BIN := $(TEST_OUT)/$(TEST_CONFIG_FILENAME)
# File with helper functionality for unit tests
TEST_HELPER_FILENAME = test_helper
TEST_HELPER_FILE := $(TEST)/$(TEST_HELPER_FILENAME).cc
# Compiled test helper object file
TEST_HELPER_OBJ := $(TEST_OBJ)/$(TEST_HELPER_FILENAME).o
# Targets which compile the module's unit tests.
# All of them are run with 'make test'.
ALL_TEST_TARGETS :=
# Object stubs which are utilized to test an abstract class.
TEST_STUBS = $(shell find $(INCLUDE)/__test/ -type f -name "*_stub.hh")

# Compiler options.
CXX := g++
CXXFLAGS := -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic --std=c++14 \
	-I $(INCLUDE) -I $(INCLUDE_SRC)

# The project's helper modules.
# They should be essential for every executable module.
HELPER_MODULES := std_helper ncurses_helper

# Executable modules - specific representations of the same project.
# They have the following characteristics:
#   - be independant of one another;
#   - define a main function;
#   - an executable is generated for each of them.
EXECUTABLE_MODULES := shell_ui

# Extra libraries, if required by the project.
# Each module should add its required libraries to this variable's value.
LIBS := -lncurses -pthread

# All C++ source files of third party libraries should go into this directory.
THIRD_PARTY_SRC := lib
# All third party libraries' object files should go into this directory.
THIRD_PARTY_OBJ := tmp/obj/lib
# The project's third party libraries.
# They are compiled for use by each project module.
# Third party libraries should be self-contained i.e. they shouldn't depend
# on any project specific module (usually libraries are contained within
# their own header files and occasionally source files).
THIRD_PARTY_LIBS :=

# Targets which are run with 'make all' (or just 'make').
# Every executable module should add their declared target's name to this 
# variable's value.
ALL_TARGETS :=

# The C++ source files of the project's helper modules.
# Each helper module should add its source files to this variable's value.
HELPER_SRC :=

# Helper modules' object files.
# Each helper module should add its object files to this variable's value.
HELPER_OBJ :=

# Include the description for each helper module.
include $(patsubst %,$(SRC)/%/module.mk,$(HELPER_MODULES))

# Include all executable modules' descriptions.
include $(patsubst %,$(SRC)/%/module.mk,$(EXECUTABLE_MODULES))

# The C++ source files of the project's third party libraries.
# Each third party library source file should be added to this variable's value.
THIRD_PARTY_LIBS_SRC := 

# Third party libraries' object files.
# Each third party library object file should be added to this variable's value.
THIRD_PARTY_LIBS_OBJ := 

# Include all third party libraries' descriptions.
include $(patsubst %,$(THIRD_PARTY_SRC)/%/module.mk,$(THIRD_PARTY_LIBS))

.PHONY: all helper libs clean setup_testing test clean_tests

all: $(ALL_TARGETS) 
	@echo $(LOG_STAMP): Project compilation successful.

# Compile all of project's helper modules.
helper: $(HELPER_OBJ)
	@echo $(LOG_STAMP): Helper modules compilation successful.

# Compile all of project's third party libraries.
libs: $(THIRD_PARTY_LIBS_OBJ)
	@echo $(LOG_STAMP): Third party libraries compilation successful.

# WARNING: ALWAYS hardcode the directories which are to be cleaned.
# Using 'rm -r' with make variables may lead to removal of directories or
# files you may not want deleted.
clean:
	@echo $(LOG_STAMP): Project binaries output directory: $(BIN)
	@echo $(LOG_STAMP): Project object files output directory: $(OBJ)
	rm -r -i -f ././bin/*
	rm -r -i -f ././tmp/obj/*
	@echo $(LOG_STAMP): Completed cleaning process

# Include all executable modules' targets.
include $(patsubst %,$(SRC)/%/target.mk,$(EXECUTABLE_MODULES))

# Include each module's tests' make targets.
include $(patsubst %,$(TEST)/%/test.mk,$(HELPER_MODULES))
include $(patsubst %,$(TEST)/%/test.mk,$(EXECUTABLE_MODULES))

# Setup testing environment for 'Catch2'.
setup_testing:
	@# Create temporary directory for tests' object files.
	mkdir -p $(TEST_OUT)
	mkdir -p $(TEST_OBJ)
	@# Compile config file into object file for linking by other tests
	make $(TEST_CONFIG_OBJ)
	@# Compile test helper file into object file for linking by other tests
	make $(TEST_HELPER_OBJ)
	@# Compile example empty test
	$(CXX) $(CXXFLAGS) $(TEST_CONFIG_OBJ) -o $(TEST_CONFIG_BIN)
	@echo $(LOG_STAMP): \'Catch2\' testing environment setup successful.

# Execute every test target.
test: $(ALL_TEST_TARGETS)
	@echo $(LOG_STAMP): All tests have been compiled successfully.

# Execute all tests.
run_all_tests:
	$(foreach test,$(shell find $(TEST_OUT)/ -type f),./$(test)$(NEWLINE))
	@echo $(LOG_STAMP): All tests have been run.

# Compile 'Catch2' tests' config source file to object file.
$(TEST_CONFIG_OBJ): $(TEST_CONFIG_FILE)
	mkdir -p $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ -c $<
	@echo $(LOG_STAMP): Test config file compiled successfully.

# Compile test helper source file to object file.
$(TEST_HELPER_OBJ): $(TEST_HELPER_FILE)
	mkdir -p $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ -c $<
	@echo $(LOG_STAMP): Test helper file compiled successfully.

# WARNING: ALWAYS hardcode the directories which are to be cleaned.
# Using 'rm -r' with make variables may lead to removal of directories or
# files you may not want deleted.
clean_tests:
	@echo $(LOG_STAMP): Test binaries output directory: $(TEST_OUT)
	@echo $(LOG_STAMP): Test object files output directory: $(TEST_OBJ)
	rm -r -i -f ././bin/test/*
	rm -r -i -f ././tmp/obj/test/*
	@echo $(LOG_STAMP): Completed test cleaning process

