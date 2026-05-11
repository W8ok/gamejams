CC = gcc

CFLAGS = -std=c99 -Wall -Wextra -O0 -g -Isrc/include
LIBS = -lpthread -ldl -lm -lraylib

SRCS := $(shell find src -name "*.c")
OBJS := $(patsubst src/%.c,obj/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

TARGET_DIR = executables
TARGET = $(TARGET_DIR)/game

$(TARGET): $(OBJS)
	@mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	rm -rf $(TARGET_DIR)
	rm -rf obj

run: $(TARGET)
	./$(TARGET)

debug: clean $(TARGET)
	gdb ./$(TARGET)

.PHONY: clean run debug

-include $(DEPS)
