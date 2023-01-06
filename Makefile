PROJECT_NAME := chess_engine
CC        := g++
SRCDIR    := src
BUILDDIR  := build
TARGET    := $(PROJECT_NAME)
SOURCES   := $(shell find $(SRCDIR) -type f -name *.c*)
OBJECTS   := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(addsuffix .o,$(basename $(SOURCES))))
DEPS      := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(addsuffix .d,$(basename $(SOURCES))))
CFLAGS    := -Wall -Werror -Wextra -pedantic -std=c++20
LIB       :=
INC       := -I include -I src

all: debug
debug: CFLAGS += -g
debug: $(TARGET)
release: $(TARGET)
release: CFLAGS += -O3

GREEN=`tput setaf 119`
RED=`tput setaf 160`
RESET=`tput sgr0`

define print_green
	@echo "$(GREEN)$(1)$(RESET)"
endef

define print_red
	@echo "$(RED)$(1)$(RESET)"
endef

all: $(TARGET)

clean:
	$(call print_red,"cleaning make-build by running the command: rm $(BUILDDIR) $(PROJECT_NAME) -rf")
	@rm $(BUILDDIR) $(PROJECT_NAME) -rf

$(TARGET): $(BUILDDIR) $(OBJECTS)
	$(call print_green,"Linking object files ...")
	@$(CC) $(OBJECTS) -o $(TARGET) $(LIB)
	$(call print_green,"$(TARGET) has been created!")

$(BUILDDIR):
	mkdir $(BUILDDIR)
	
$(BUILDDIR)/%.o: $(SRCDIR)/%.c*
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@$(CC) $(CFLAGS) $(INC) -M $< -MT $@ > $(@:.o=.td)
	@cp $(@:.o=.td) $(@:.o=.d);
	@sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' -e '/^$$/ d' -e 's/$$/ :/' < $(@:.o=.td) >> $(@:.o=.d); 
	@rm -f $(@:.o=.td)

-include $(DEPS)

.PHONY: clean all