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

all: $(TARGET)
	@mkdir -p $(INCLUDE_DIR)/och
	@cp $(SRC_DIR)/*.h $(INCLUDE_DIR)/och/

#create objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

#create library
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(AR) rcs $@ $(OBJECTS)

#dir makers
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)
	rm -rf $(INCLUDE_DIR)

.PHONY: clean install all
