CC = clang
CFLAGS = -Iinclude -Wall -Wextra -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Winit-self -O2

LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC_DIR = src
OUT_DIR = out
ASSETS_DIR = assets

SRCS =	$(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)

TARGET = $(OUT_DIR)/game

all: $(OUT_DIR) $(TARGET) copy_assets

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

copy_assets:
	cp -r $(ASSETS_DIR) $(OUT_DIR)

clean:
	rm -rf $(OUT_DIR)

run: $(OUT_DIR) $(TARGET)
	./$(TARGET)

.PHONY: all clean run copy_assets
