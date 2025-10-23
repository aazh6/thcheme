INC_DIR := include
SRC_DIR := src
BUILD_DIR := build

CC := gcc
CFLAGS := -Wall -Wextra -I$(INC_DIR) -MMD -MP

SRCS := $(SRC_DIR)/dystr.c $(SRC_DIR)/parser.c $(SRC_DIR)/main.c
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

TARGET := $(BUILD_DIR)/main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

-include $(DEPS)

.PHONY: all clean
