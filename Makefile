CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src/*.c
OUT = build/mathinator

all:
	$(CC) $(SRC) $(CFLAGS) -o $(OUT) -lm

clean:
	rm -f $(OUT)