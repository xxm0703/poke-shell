# Name of 'ncurses_helper' module.
NCURSES_HELPER__MODULE_NAME := ncurses_helper

# C++ header files of 'ncurses_helper' module.
# Each implementation file ('.cc' file) in this module depends on the interface
# which each header provides. Source files are recompiled if any one of these 
# headers is altered.
NCURSES_HELPER__INCLUDE := \
	input.hh \
	colors.hh \
	windows.hh \
	ncurses_object.hh \
	ncurses_exception.hh \
	ncurses_menu_object.hh
NCURSES_HELPER__INCLUDE := $(patsubst %,$(INCLUDE)/$(NCURSES_HELPER__MODULE_NAME)/%,$(NCURSES_HELPER__INCLUDE))

# C++ source files of 'ncurses_helper' module.
# They are prepended their module's relative path to the main Makefile.
NCURSES_HELPER__SRC := \
	input.cc \
	colors.cc \
	windows.cc \
	ncurses_object.cc \
	ncurses_exception.cc \
	ncurses_menu_object.cc
NCURSES_HELPER__SRC := $(patsubst %,$(SRC)/$(NCURSES_HELPER__MODULE_NAME)/%,$(NCURSES_HELPER__SRC))

# Object files of 'ncurses_helper' helper module.
NCURSES_HELPER__OBJ := $(patsubst $(SRC)/%.cc,$(OBJ)/%.o,$(NCURSES_HELPER__SRC))

# Create required subdirectories for module's object files
NCURSES_HELPER__OBJ_DIRS := $(subst $(SRC),$(OBJ),$(shell find $(SRC)/$(NCURSES_HELPER__MODULE_NAME)/ -type d))
$(foreach obj_dir,$(NCURSES_HELPER__OBJ_DIRS),$(shell mkdir -p $(obj_dir)))

# Include module's object files in the project.
HELPER_OBJ += $(NCURSES_HELPER__OBJ)

# Make target for 'ncurses_helper' module's object files
$(OBJ)/$(NCURSES_HELPER__MODULE_NAME)/%.o: $(SRC)/$(NCURSES_HELPER__MODULE_NAME)/%.cc $(NCURSES_HELPER__INCLUDE)
	@# Create temporary directory for object files.
	@mkdir -p $(OBJ)/$(NCURSES_HELPER__MODULE_NAME)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

