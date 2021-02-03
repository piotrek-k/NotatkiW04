CFLAGS=-Wall -ggdb -std=c99 -lm -pthread -lrt

all: build server klientTCP klientUDP

test_server:
	# Uruchomienie aplikacji
	./build/server.out

build:
	mkdir -p ./build

server: server.c
	gcc $(CFLAGS) -o ./build/server.out server.c

klientTCP: klientTCP.c
	gcc $(CFLAGS) -o ./build/klientTCP.out klientTCP.c

klientUDP: klientUDP.c
	gcc $(CFLAGS) -o ./build/klientUDP.out klientUDP.c