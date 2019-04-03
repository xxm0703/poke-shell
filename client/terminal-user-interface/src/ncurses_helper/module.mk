# Name of 'ncurses_helper' module.
NCURSES_HELPER__MODULE_NAME := ncurses_helper

# C++ header files of 'ncurses_helper' module.
# Each implementation file ('.cc' file) in this module depends on the interface
# which each header provides. Source files are recompiled if any one of these 
# headers is altered.
NCURSES_HELPER__INCLUDE := colors.hh
NCURSES_HELPER__INCLUDE := $(patsubst %,$(INCLUDE)/$(NCURSES_HELPER__MODULE_NAME)/%,$(NCURSES_HELPER__INCLUDE))

# C++ source files of 'ncurses_helper' module.
# They are prepended their module's relative path to the main Makefile.
NCURSES_HELPER__SRC := colors.cc
NCURSES_HELPER__SRC := $(patsubst %,$(SRC)/$(NCURSES_HELPER__MODULE_NAME)/%,$(NCURSES_HELPER__SRC))

# Object files of 'ncurses_helper' helper module.
NCURSES_HELPER__OBJ := $(patsubst $(SRC)/%.cc,$(OBJ)/%.o,$(NCURSES_HELPER__SRC))

# Include helper module's source files in the project.
HELPER_SRC += $(NCURSES_HELPER__SRC)

# Include module's object files in the project.
HELPER_OBJ += $(NCURSES_HELPER__OBJ)

# Make target for 'ncurses_helper' module's object files
$(OBJ)/$(NCURSES_HELPER__MODULE_NAME)/%.o: $(SRC)/$(NCURSES_HELPER__MODULE_NAME)/%.cc $(NCURSES_HELPER__INCLUDE)
	@# Create temporary directory for object files.
	@mkdir -p $(OBJ)/$(NCURSES_HELPER__MODULE_NAME)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

