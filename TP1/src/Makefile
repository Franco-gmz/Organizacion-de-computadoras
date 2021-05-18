CC = gcc
CFLAGS = -Wall -c -std=c99

all: autcel

autcel: main.o
	$(CC) main.o -o autcel

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm -rf *.o autcel
