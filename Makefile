SRC_DIR = ./src
INC_DIR = ./inc

OUT_DIR = ./build
OBJ_DIR = $(OUT_DIR)/obj
BIN_DIR = $(OUT_DIR)/bin

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

-include $(OBJ_DIR)/*.d

all: $(OBJ_FILES)
	@if [ ! -d $(BIN_DIR) ]; then mkdir -p $(BIN_DIR); fi
	@gcc $(OBJ_FILES) -o $(BIN_DIR)/a.exe -mconsole

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@if [ ! -d $(OBJ_DIR) ]; then mkdir -p $(OBJ_DIR); fi
	@echo "Compilando $< a $@"
	@gcc -c $< -o $@ $(foreach DIR, $(INC_DIR), -I $(INC_DIR)) -MMD 

clean:
	@if [ -d $(OUT_DIR) ]; then rm -rf $(OUT_DIR); fi

info:
	@echo "OBJ_FILES = $(OBJ_FILES)"
