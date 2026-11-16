CC = gcc
CFLAGS = -std=c11 -O2 -Wall -Wextra -Iinclude
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC = src/main.c src/engine/physics.c src/engine/spatial_grid.c src/platform/raylib_backend.c
TARGET = sim

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
