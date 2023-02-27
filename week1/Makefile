# credit to:
# Job Vranish (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)
# and
# https://makefiletutorial.com/#makefile-cookbook
# and
# https://github.com/repnz/auto-makefile/blob/master/Makefile

# Program for compiling C++ programs; default g++
CXX := g++

# Extra flags to give to the C++ compiler
CXXFLAGS := -Wall -Werror -Wextra -pedantic -std=c++17

# target we wish to build with this makefile
TARGET_EXEC := chess_engine

# Extra flags to give to compilers when they are supposed to invoke the linker
LDFLAGS :=

all: debug
debug: CXXFLAGS += -g
debug: $(TARGET_EXEC)

release: CPPFLAGS += -O3
release: $(TARGET_EXEC)

GREEN=`tput setaf 034`
RED=`tput setaf 160`
RESET=`tput sgr0`

define print_green
	@echo "$(GREEN)$(1)$(RESET)"
endef

define print_red
	@echo "$(RED)$(1)$(RESET)"
endef

# where the target will be built
BUILD_DIR := ./build

# directory with the relevant source files (.h and .cpp)
SRC_DIRS := ./src

# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. Make will incorrectly expand these otherwise.
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')

# String substitution for every C/C++ file.
# As an example, hello.cpp turns into ./build/hello.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# string substitution (suffix version without %).
# As an example, ./build/hello.cpp.o turns into ./build/hello.cpp.d
DEPS := $(OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag.
# example: "./src" turns into "-I./src"
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
# https://gcc.gnu.org/onlinedocs/gcc-3.4.0/gcc/Preprocessor-Options.html#Preprocessor%20Options
# https://make.mad-scientist.net/papers/advanced-auto-dependency-generation/
# https://www.gnu.org/software/make/manual/html_node/Automatic-Prerequisites.html
CPPFLAGS := $(INC_FLAGS) -MMD -MP

# the final build step
$(TARGET_EXEC): $(OBJS)
	$(call print_green,"Linking object files ...")
	@$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	$(call print_green,"$(TARGET_EXEC) has been created successfully!")

# build step for C++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# can be used to print out the contents of a variable in GNU Make
# to the screen by running the shell command: make print-VARNAME
# for example: make print-DEPS
print-%  : ; @echo $* = $($*)

.PHONY: clean
clean:
	$(call print_red,"cleaning make-build")
	@rm -rf $(BUILD_DIR) $(TARGET_EXEC)

# Include the .d makefiles. The  minus sign '-' at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DEPS) # include