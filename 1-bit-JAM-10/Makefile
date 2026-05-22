CC = gcc
CFLAGS = -std=c23 -Wall -Wextra -O0 -g -Isrc/include
LDFLAGS = -lpthread -ldl -lm -DLOGGING
LIBS = -lraylib

SRCS := $(shell find src -name "*.c")
OBJS := $(patsubst src/%.c,obj/%.o,$(SRCS))
TARGET = temp
EXEC = executables
ASSETS = assets

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS) $(LIBS)

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
	rm -rf $(EXEC)
	rm -rf obj/

run: $(TARGET)
	./$(TARGET)

debug: clean $(TARGET)
	gdb ./$(TARGET)

WEB_CC = emcc
WEB_TARGET = $(EXEC)/web/index.html
WEB_OBJS := $(patsubst src/%.c,obj/web/%.o,$(SRCS))
WEB_CFLAGS = -std=c23 -Wall -Wextra -O2 -Isrc/include -Ivendor/raylib/src -DPLATFORM_WEB
WEB_LDFLAGS = -sASYNCIFY -sALLOW_MEMORY_GROWTH -sUSE_GLFW=3 --shell-file shell.html --preload-file $(ASSETS)
WEB_LIBS = vendor/raylib/src/libraylib.web.a

vendor/raylib/src/libraylib.web.a:
	@mkdir -p vendor
	if [ ! -d "vendor/raylib" ]; then \
		git clone https://github.com/raysan5/raylib.git vendor/raylib; \
	fi
	if [ ! -f "vendor/raylib/src/libraylib.web.a" ]; then \
		cd vendor/raylib/src && make PLATFORM=PLATFORM_WEB -B; \
	fi

obj/web/%.o: src/%.c | vendor/raylib/src/libraylib.web.a
	@mkdir -p $(dir $@)
	$(WEB_CC) $(WEB_CFLAGS) -c $< -o $@

web: $(WEB_TARGET)

$(WEB_TARGET): $(WEB_OBJS)
	@mkdir -p $(EXEC)/web
	$(WEB_CC) $(WEB_CFLAGS) -o $(WEB_TARGET) $(WEB_OBJS) $(WEB_LDFLAGS) $(WEB_LIBS)

web-run: web
	emrun $(WEB_TARGET)

.PHONY: clean run debug web web-run
