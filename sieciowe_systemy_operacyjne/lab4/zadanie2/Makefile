CFLAGS=-Wall -ggdb -std=c99 -lm

all: build player

test:
	# Uruchomienie aplikacji
	./tmp/player.out

build:
	mkdir -p ./tmp

player: player.c
	gcc $(CFLAGS) -o ./tmp/player.out player.c