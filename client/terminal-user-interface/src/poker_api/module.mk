# Name of 'poker_api' module.
POKER_API__MODULE_NAME := poker_api

# C++ header files of 'poker_api' module.
# Each implementation file ('.cc' file) in this module depends on the interface
# which each header provides. Source files are recompiled if any one of these 
# headers is altered.
POKER_API__INCLUDE := \
	authentication.hh
POKER_API__INCLUDE := $(patsubst %,$(INCLUDE)/$(POKER_API__MODULE_NAME)/%,$(POKER_API__INCLUDE))

# C++ source files of 'poker_api' module.
# They are prepended their module's relative path to the main Makefile.
POKER_API__SRC := \
	authentication.cc
POKER_API__SRC := $(patsubst %,$(SRC)/$(POKER_API__MODULE_NAME)/%,$(POKER_API__SRC))

# Object files of 'poker_api' helper module.
POKER_API__OBJ := $(patsubst $(SRC)/%.cc,$(OBJ)/%.o,$(POKER_API__SRC))

# Create required subdirectories for module's object files
POKER_API__OBJ_DIRS := $(subst $(SRC),$(OBJ),$(shell find $(SRC)/$(POKER_API__MODULE_NAME)/ -type d))
$(foreach obj_dir,$(POKER_API__OBJ_DIRS),$(shell mkdir -p $(obj_dir)))

# Include module's object files in the project.
HELPER_OBJ += $(POKER_API__OBJ)

# Make target for 'poker_api' module's object files
$(OBJ)/$(POKER_API__MODULE_NAME)/%.o: $(SRC)/$(POKER_API__MODULE_NAME)/%.cc $(POKER_API__INCLUDE)
	@# Create temporary directory for object files.
	@mkdir -p $(OBJ)/$(POKER_API__MODULE_NAME)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

