CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -O0 -g -Isrc/include
LIBS = -lpthread -ldl -lm -lraylib

SRCS := $(shell find src -name "*.c")
OBJS := $(patsubst src/%.c,obj/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

PROJECT_NAME = game
EXEC = executables
TARGET = $(EXEC)/$(PROJECT_NAME)
ASSETS = assets

$(TARGET): $(OBJS)
	@mkdir -p $(EXEC)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	rm -rf $(EXEC)
	rm -rf obj
	rm -rf vendor
	rm -rf *.zip

run: $(TARGET)
	./$(TARGET)

debug: clean $(TARGET)
	gdb ./$(TARGET)

WEB_CC = emcc
WEB_TARGET = $(EXEC)/web/index.html
WEB_OBJS := $(patsubst src/%.c,obj/web/%.o,$(SRCS))
WEB_CFLAGS = -std=c99 -Wall -Wextra -O2 -Isrc/include -Ivendor/raylib/src -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
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

web-zip: web
	cd $(EXEC)/web && zip -r ../../$(PROJECT_NAME)-web.zip *
	@echo "Created $(PROJECT_NAME)-web.zip"

clean-web:
	rm -rf $(EXEC)/web obj/web vendor/raylib

.PHONY: clean run debug web web-run clean-web

-include $(DEPS)
