CFLAGS=-Wall -ggdb -std=c99 -lm -pthread -lrt

all: build server klient

test_server:
	# Uruchomienie aplikacji
	./build/server.out

build:
	mkdir -p ./build

server: server.c
	gcc $(CFLAGS) -o ./build/server.out server.c

klient: klient.c
	gcc $(CFLAGS) -o ./build/klient.out klient.c