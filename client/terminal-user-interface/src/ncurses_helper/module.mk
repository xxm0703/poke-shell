# Name of 'ncurses_helper' module.
NCURSES_HELPER__MODULE_NAME := ncurses_helper

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
$(OBJ)/$(NCURSES_HELPER__MODULE_NAME)/%.o: $(SRC)/$(NCURSES_HELPER__MODULE_NAME)/%.cc
	@# Create temporary directory for object files.
	@mkdir -p $(OBJ)/$(NCURSES_HELPER__MODULE_NAME)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

