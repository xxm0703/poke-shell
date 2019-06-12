.PHONY: shell_ui

# Make target of 'shell_ui' executable module.
shell_ui: $(SHELL_UI__MAIN_OBJ) $(SHELL_UI__OBJ) $(HELPER_OBJ) $(THIRD_PARTY_LIBS_OBJ)
	$(CXX) $(CXXFLAGS) -o $(BIN)/$(SHELL_UI__EXECUTABLE) $(SHELL_UI__MAIN_OBJ) $(SHELL_UI__OBJ) $(HELPER_OBJ) $(THIRD_PARTY_LIBS_OBJ) $(LIBS)
	@echo $(LOG_STAMP): $(SHELL_UI__MODULE_NAME) executable module compilation successful.

