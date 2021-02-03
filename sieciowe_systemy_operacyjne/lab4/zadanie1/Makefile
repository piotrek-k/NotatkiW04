CFLAGS=-Wall -ggdb -std=c99 -lm

all: build fifo write

test:
	# Uruchomienie aplikacji
	./build/fifo.out

build:
	mkdir -p ./build

fifo: fifo.c
	gcc $(CFLAGS) -o ./build/fifo.out fifo.c

write: write.c
	gcc $(CFLAGS) -o ./build/write.out write.c