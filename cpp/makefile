SRC_DIR := src
OUT_DIR := build

OBJ_DIR := $(OUT_DIR)/.o
DEP_DIR := $(OUT_DIR)/.d

EXECUTABLE := $(OUT_DIR)/a.out

__generate_depenencies :=  -MMD -MP -I./$(SRC_DIR)

CXX := g++

CXXFLAGS := -std=c++20 -Wall -Wextra $(__generate_depenencies) -O3

LINKER_FLAGS := 

#################################################################
###                 P H O N Y   T A R G E T S                 ###
#################################################################

PHONY_TARGETS := executable run clean help

.PHONY: $(PHONY_TARGETS)

executable: $(EXECUTABLE)

# If the first argument is "run"...
ifeq (run,$(firstword $(MAKECMDGOALS)))
  # use the rest as arguments for "run"
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  # ...and turn them into do-nothing targets
  $(eval $(RUN_ARGS):;@:)
endif

run: executable
	@echo "running $(EXECUTABLE) $(RUN_ARGS)"
	@$(EXECUTABLE) $(RUN_ARGS)

clean:
	rm -rf $(OUT_DIR)

help:
	@echo "Available targets:"
	@echo "  make"
	@echo "  make run [args...]"
	@echo "  make clean"
	@echo "  make help"

#################################################################
###                 B U I L D   T A R G E T S                 ###
#################################################################

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
DEP_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(DEP_DIR)/%.d,$(SRC_FILES))

-include $(DEP_FILES)

$(EXECUTABLE): $(OBJ_FILES)
	@mkdir -p $(OUT_DIR)
	@echo "linking $@"
	@$(CXX) $(LINKER_FLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@) $(dir $(DEP_DIR)/$*.d)
	@echo "compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@mv $(OBJ_DIR)/$*.d $(DEP_DIR)/$*.d
