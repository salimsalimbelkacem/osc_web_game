.PHONY: all clean
CC = emcc

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

RAYLIB_DIR = /home/salim_belkacem/libs/raylib-5.5_webassembly

RAYLIB_INCLUDE = -I$(RAYLIB_DIR)/include
RAYLIB_LIB = $(RAYLIB_DIR)/lib/libraylib.a

CFLAGS = -Os -Wall -s USE_GLFW=3 -DPLATFORM_WEB -I. $(RAYLIB_INCLUDE)
LDFLAGS = $(RAYLIB_LIB)

SHELL_FILE = ./shell.html

SRCS = $(shell find $(SRC_DIR) -name '*.c')

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(BIN_DIR)/main.html

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)  # create subdirectories if needed
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/main.html: $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@ --shell-file $(SHELL_FILE)


clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

tests/%:
	gcc -g -O0 -o $@ $(SRC_DIR)/$*/*.c $(SRC_DIR)/$@.c \
	-lraygui -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	./$@
	rm $@
