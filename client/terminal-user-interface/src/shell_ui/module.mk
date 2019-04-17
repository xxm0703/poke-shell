# Name of 'shell_ui' module.
SHELL_UI__MODULE_NAME := shell_ui

# Produced executable file name.
SHELL_UI__EXECUTABLE := shell_ui

# C++ header files of 'shell_ui' executable module.
# Each implementation file ('.cc' file) in this module depends on the interface
# which each header provides. Source files are recompiled if any one of these 
# headers is altered.
SHELL_UI__INCLUDE := title.hh vertical_menu.hh text.hh aligned_text.hh scene.hh
SHELL_UI__INCLUDE := $(patsubst %,$(INCLUDE)/$(SHELL_UI__MODULE_NAME)/%,$(SHELL_UI__INCLUDE))

# C++ source files of 'shell_ui' executable module.
# NOTE: do not include source file with 'main' function definition (see below).
SHELL_UI__SRC := title.cc vertical_menu.cc text.cc aligned_text.cc scene.cc
SHELL_UI__SRC := $(patsubst %,$(SRC)/$(SHELL_UI__MODULE_NAME)/%,$(SHELL_UI__SRC))
# C++ source file with 'main' function definition.
SHELL_UI__MAIN_SRC := main.cc
SHELL_UI__MAIN_SRC := $(patsubst %,$(SRC)/$(SHELL_UI__MODULE_NAME)/%,$(SHELL_UI__MAIN_SRC))

# Object files of 'shell_ui' executable module.
SHELL_UI__OBJ := $(patsubst $(SRC)/%.cc,$(OBJ)/%.o,$(SHELL_UI__SRC))
SHELL_UI__MAIN_OBJ := $(patsubst $(SRC)/%.cc,$(OBJ)/%.o,$(SHELL_UI__MAIN_SRC))

# Add executable module's target as dependency of the 'all' target.
ALL_TARGETS += shell_ui

# Make target for 'shell_ui' module's object files
$(OBJ)/$(SHELL_UI__MODULE_NAME)/%.o: $(SRC)/$(SHELL_UI__MODULE_NAME)/%.cc $(SHELL_UI__INCLUDE)
	@# Create temporary directory for object files.
	@mkdir -p $(OBJ)/$(SHELL_UI__MODULE_NAME)
	$(CXX) $(CXXFLAGS) -o $@ -c $< 

