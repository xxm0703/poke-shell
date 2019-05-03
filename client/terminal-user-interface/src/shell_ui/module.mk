# Name of 'shell_ui' module.
SHELL_UI__MODULE_NAME := shell_ui

# Produced executable file name.
SHELL_UI__EXECUTABLE := shell_ui

# C++ header files of 'shell_ui' executable module.
# Each implementation file ('.cc' file) in this module depends on the interface
# which each header provides. Source files are recompiled if any one of these 
# headers is altered.
SHELL_UI__INCLUDE := \
	config.hh \
	title.hh \
	vertical_menu.hh \
	text.hh \
	aligned_text.hh \
	scene.hh \
	scene_with_input.hh \
	scenes/main_menu_scene.hh \
	functional_menu.hh \
	factories/main_menu_factory.hh
SHELL_UI__INCLUDE := $(patsubst %,$(INCLUDE)/$(SHELL_UI__MODULE_NAME)/%,$(SHELL_UI__INCLUDE))

# C++ source files of 'shell_ui' executable module.
# NOTE: do not include source file with 'main' function definition (see below).
SHELL_UI__SRC := \
	config.cc \
	title.cc \
	vertical_menu.cc \
	text.cc \
	aligned_text.cc \
	scene.cc \
	scene_with_input.cc \
	scenes/main_menu_scene.cc \
	functional_menu.cc \
	factories/main_menu_factory.cc
SHELL_UI__SRC := $(patsubst %,$(SRC)/$(SHELL_UI__MODULE_NAME)/%,$(SHELL_UI__SRC))
# C++ source file with 'main' function definition.
SHELL_UI__MAIN_SRC := main.cc
SHELL_UI__MAIN_SRC := $(patsubst %,$(SRC)/$(SHELL_UI__MODULE_NAME)/%,$(SHELL_UI__MAIN_SRC))

# Object files of 'shell_ui' executable module.
SHELL_UI__OBJ := $(patsubst $(SRC)/%.cc,$(OBJ)/%.o,$(SHELL_UI__SRC))
SHELL_UI__MAIN_OBJ := $(patsubst $(SRC)/%.cc,$(OBJ)/%.o,$(SHELL_UI__MAIN_SRC))

# Create required subdirectories for module's object files
SHELL_UI__OBJ_DIRS := $(subst $(SRC),$(OBJ),$(shell find $(SRC)/$(SHELL_UI__MODULE_NAME)/ -type d))
$(foreach obj_dir,$(SHELL_UI__OBJ_DIRS),$(shell mkdir -p $(obj_dir)))

# Add executable module's target as dependency of the 'all' target.
ALL_TARGETS += shell_ui

# Make target for 'shell_ui' module's object files
$(OBJ)/$(SHELL_UI__MODULE_NAME)/%.o: $(SRC)/$(SHELL_UI__MODULE_NAME)/%.cc $(SHELL_UI__INCLUDE)
	@# Create temporary directory for object files.
	@mkdir -p $(OBJ)/$(SHELL_UI__MODULE_NAME)
	$(CXX) $(CXXFLAGS) -o $@ -c $< 

