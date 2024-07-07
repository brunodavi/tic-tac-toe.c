EXEC=main.out

CC = gcc
CFLAGS = -Wall -g

build: main.c
	$(CC) $(CFLAGS) main.c -o $(EXEC)
