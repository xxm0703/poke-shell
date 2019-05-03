# Name of 'json' third party library.
JSON__LIBRARY_NAME := json

# 'json' header files required by library's source code files.
JSON__INCLUDE := include/lib/$(JSON__LIBRARY_NAME)

# C++ source files of 'json' third party library.
# They are prepended their library's relative path to the main Makefile.
JSON__SRC :=
JSON__SRC := $(patsubst %,$(THIRD_PARTY_SRC)/$(JSON__LIBRARY_NAME)/%,$(JSON__SRC))

# Object files of 'json' third party library.
JSON__OBJ := $(patsubst $(THIRD_PARTY_SRC)/%.cc,$(THIRD_PARTY_OBJ)/%.o,$(JSON__SRC))

# Include third party library's source files in the project.
THIRD_PARTY_LIBS_SRC += $(JSON__SRC)

# Include third party library's object files in the project.
THIRD_PARTY_LIBS_OBJ += $(JSON__OBJ)

# Make target for 'json' third party library's object files
$(THIRD_PARTY_OBJ)/$(JSON__LIBRARY_NAME)/%.o: $(THIRD_PARTY_SRC)/$(JSON__LIBRARY_NAME)/%.cc
	@# Create temporary directory for object files.
	@mkdir -p $(THIRD_PARTY_OBJ)/$(JSON__LIBRARY_NAME)
	$(CXX) $(CXXFLAGS) -I $(JSON__INCLUDE) -o $@ -c $<

