# Name of 'jsoncpp' third party library.
JSONCPP__LIBRARY_NAME := jsoncpp

# 'jsoncpp' header files required by library's source code files.
JSONCPP__INCLUDE := include/lib/$(JSONCPP__LIBRARY_NAME)

# C++ source files of 'jsoncpp' third party library.
# They are prepended their library's relative path to the main Makefile.
JSONCPP__SRC := jsoncpp.cc
JSONCPP__SRC := $(patsubst %,$(THIRD_PARTY_SRC)/$(JSONCPP__LIBRARY_NAME)/%,$(JSONCPP__SRC))

# Object files of 'jsoncpp' third party library.
JSONCPP__OBJ := $(patsubst $(THIRD_PARTY_SRC)/%.cc,$(THIRD_PARTY_OBJ)/%.o,$(JSONCPP__SRC))

# Include third party library's source files in the project.
THIRD_PARTY_LIBS_SRC += $(JSONCPP__SRC)

# Include third party library's object files in the project.
THIRD_PARTY_LIBS_OBJ += $(JSONCPP__OBJ)

# Make target for 'jsoncpp' third party library's object files
$(THIRD_PARTY_OBJ)/$(JSONCPP__LIBRARY_NAME)/%.o: $(THIRD_PARTY_SRC)/$(JSONCPP__LIBRARY_NAME)/%.cc
	@# Create temporary directory for object files.
	@mkdir -p $(THIRD_PARTY_OBJ)/$(JSONCPP__LIBRARY_NAME)
	$(CXX) $(CXXFLAGS) -I $(JSONCPP__INCLUDE) -o $@ -c $<

