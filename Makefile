CC = gcc
CFLAGS = -Wall -Wextra -g3

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = .

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
DEP_FILES = $(OBJ_FILES:.o=.d)

.PHONY: all
all: setup chip8

.PHONY: setup
setup:
	mkdir -p $(BIN_DIR) $(OBJ_DIR)

chip8: $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/$@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -MMD -MP $< -o $@

-include $(DEP_FILES)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d $(addprefix $(BIN_DIR)/,$(PROGRAMS))

