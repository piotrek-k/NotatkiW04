CFLAGS=-Wall -ggdb -std=c99 -lm -pthread

all: build bank_account

test:
	# Uruchomienie aplikacji
	./build/bank_account.out

build:
	mkdir -p ./build

bank_account: bank_account.c
	gcc $(CFLAGS) -o ./build/bank_account.out bank_account.c