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
OBJS=$(patsubst %.c,%.o,$(wildcard $(SRC_DIR)/*.c))
INC_FLAGS=$(addprefix -I,$(INC_DIRS))
LIBS_FLAGS=$(addprefix -l,$(LIBS))
VPATH=$(SRC_DIR)

.phony: $(TARGET) clean re

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS_FLAGS)
	@echo "Compilation succeded."

$(OBJS): |$(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o:%.c
	$(COMPILE.c) $(OUTPUT_OPTIONS) $(CFLAGS) $<

clean:
	rm -rf OBJS

re: clean $(TARGET)