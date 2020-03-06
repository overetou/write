#Work title
TARGET=storyline

#Directories
OBJ_DIR=obj
SRC_DIR=src
INC_DIRS=includes

#Compilation related indications
CC=gcc
CFLAGS=-Wall -Wextra -Werror
LIBS=SDL2

#From there we use the info to compile everything.
SOURCES:=$(wildcard $(SRC_DIR)/*.c)
OBJS:=$(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
INC_FLAGS=$(addprefix -I,$(INC_DIRS))
CFLAGS+=$(INC_FLAGS)
LIBS_FLAGS=$(addprefix -l,$(LIBS))
VPATH=$(SRC_DIR)

.phony: $(TARGET) clean re

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS_FLAGS)
	@echo -e "\033[0;32mCompilation succeeded.\033[0m"

$(OBJS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c |$(OBJ_DIR)
	$(COMPILE.c) $(OUTPUT_OPTIONS) -o $@ $<

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJS) $(TARGET)

re: clean $(TARGET)