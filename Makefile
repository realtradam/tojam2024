BUILD_DIR=build
SRC_DIRS := ./src
ifeq ($(MAKECMDGOALS),n64)
	include $(N64_INST)/include/n64.mk
else
	CC = emcc
endif

#include $(N64_INST)/include/n64.mk
//src = src/main.c
src := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
N64_INCLUDEDIR := $(addprefix -I,$(INC_DIRS))
WEB_INCLUDEDIR := raylib/src
assets_png = $(wildcard assets/*.png)
#assets_m3d = $(wildcard assets/*.m3d)

assets_conv = $(addprefix filesystem/,$(notdir $(assets_png:%.png=%.sprite)))
#assets_conv = $(addprefix filesystem/,$(notdir $(assets_m3d:%.m3d=%.m3d)))

MKSPRITE_FLAGS ?=

ifeq ($(MAKECMDGOALS),n64)
	LDFLAGS += -lraylib
endif


ifeq ($(MAKECMDGOALS),n64)

else
# The final build step.
$(BUILD_DIR)/index.html: $(OBJS)
	mkdir -p $(dir $@)
	$(CC) $(src) -o $@ $(LDFLAGS) -Os -Wall raylib/src/libraylib.a -I. -Iraylib/src -L. -Lraylib/src -s USE_GLFW=3 -DPLATFORM_WEB -sASYNCIFY --shell-file raylib/src/minshell.html

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
endif

n64: raylib.z64

filesystem/%.sprite: assets/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	echo @$(N64_MKSPRITE) -v -f RGBA16 --compress -o "$(dir $@)" "$<"
	@cp "$<" "$(dir $@)"

#filesystem/%.m3d: assets/%.m3d
#	@mkdir -p $(dir $@)
#	@echo "    [MODEL] $@"
#	echo @$(N64_MKMODEL) -v -o "$(dir $@)" "$<"
#	@cp "$<" "$(dir $@)"

$(BUILD_DIR)/raylib.dfs: $(assets_conv)
$(BUILD_DIR)/raylib.elf: $(src:%.c=$(BUILD_DIR)/%.o)

raylib.z64: N64_ROM_TITLE="raylib"
raylib.z64: $(BUILD_DIR)/raylib.dfs

clean:
	rm -rf $(BUILD_DIR) filesystem/ raylib.z64

-include $(wildcard $(BUILD_DIR)/*.d)

.PHONY: n64 clean
