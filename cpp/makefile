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
###                     T H E   B U I L D                     ###
#################################################################


# recursively find all .cpp files in the SRC_DIR
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


#################################################################
###                 P H O N Y   T A R G E T S                 ###
#################################################################


PHONY_TARGETS := executable run clean help

.PHONY: $(PHONY_TARGETS)


args := # optional args passed from command line to executable

executable: $(EXECUTABLE)

run: executable
	@echo "running $(EXECUTABLE) $(args)"
	@$(EXECUTABLE) $(args)

clean:
	rm -rf $(OUT_DIR)

help:
	@echo "Available targets:"
	@echo "  make ------- build the code"
	@echo "  make run --- build & run the code. to pass args: make run args='arg1 arg2 arg3'"
	@echo "  make clean - delete the build folder"
	@echo "  make help -- show this menu"
