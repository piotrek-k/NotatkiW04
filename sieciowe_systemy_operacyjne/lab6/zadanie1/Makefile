CFLAGS=-Wall -ggdb -std=c99 -lm

all: build shared_mem

test:
	# Uruchomienie aplikacji
	# ./run_parallel.sh "./build/shared_mem.out 1" "./build/shared_mem.out 2"

build:
	mkdir -p ./build

shared_mem: shared_mem.c
	gcc $(CFLAGS) -o ./build/shared_mem.out shared_mem.c