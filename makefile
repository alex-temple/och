CC := gcc
CFLAGS := -Wall -Werror -O2
AR := ar

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

INCLUDE_DIR := ./include

TARGET := $(BIN_DIR)/och.a

SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

all: $(TARGET) | $(INCLUDE_DIR)
	cp $(SRC_DIR)/*.h $(INCLUDE_DIR)/och/

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(AR) rcs $@ $(OBJECTS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(INCLUDE_DIR):
	mkdir -p $(INCLUDE_DIR)/och

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)
	rm -rf $(INCLUDE_DIR)

.PHONY: clean all
