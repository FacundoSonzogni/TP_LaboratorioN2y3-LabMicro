SRC_DIR = ./src
INC_DIR = ./inc

OUT_DIR = ./build
OBJ_DIR = $(OUT_DIR)/obj
BIN_DIR = $(OUT_DIR)/bin
DOC_DIR = $(OUT_DIR)/doc

CFLAGS = -Wall -Wextra -Werror -std=c99

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

-include $(OBJ_DIR)/*.d

all: $(OBJ_FILES) | $(BIN_DIR)
	@gcc $(OBJ_FILES) -o $(BIN_DIR)/a.exe -mconsole

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "Compilando $< a $@"
	@gcc $(CFLAGS) -c $< -o $@ $(foreach DIR, $(INC_DIR), -I $(INC_DIR)) -MMD

clean:
	@if [ -d $(OUT_DIR) ]; then rm -rf $(OUT_DIR); fi

info:
	@echo "OBJ_FILES = $(OBJ_FILES)"

doc: | $(DOC_DIR)
	@doxygen Doxyfile

$(BIN_DIR):
	mkdir -p $(BIN_DIR)
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
$(DOC_DIR):
	mkdir -p $(DOC_DIR)
