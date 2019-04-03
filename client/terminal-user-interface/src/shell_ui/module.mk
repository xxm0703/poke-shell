# Name of 'shell_ui' module.
SHELL_UI__MODULE_NAME := shell_ui

# Produced executable file name.
SHELL_UI__EXECUTABLE := shell_ui

# C++ source files of 'shell_ui' executable module.
# NOTE: do not include source file with 'main' function definition (see below).
SHELL_UI__SRC := title.cc
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
$(OBJ)/$(SHELL_UI__MODULE_NAME)/%.o: $(SRC)/$(SHELL_UI__MODULE_NAME)/%.cc
	@# Create temporary directory for object files.
	@mkdir -p $(OBJ)/$(SHELL_UI__MODULE_NAME)
	$(CXX) $(CXXFLAGS) -o $@ -c $< 

