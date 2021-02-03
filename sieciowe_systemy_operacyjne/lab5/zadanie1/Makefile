CFLAGS=-Wall -ggdb -std=c99 -lm

all: build shared_mem

test:
	# Uruchomienie aplikacji
	./build/shared_mem.out

build:
	mkdir -p ./build

shared_mem: shared_mem.c
	gcc $(CFLAGS) -o ./build/shared_mem.out shared_mem.c