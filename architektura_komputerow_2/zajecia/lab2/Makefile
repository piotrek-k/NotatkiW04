# reguła linkowania
zadanie: zadanie.o
	ld -o ./build/zadanie ./build/zadanie.o

# reguła kompilacji
zadanie.o: zadanie.s
	mkdir -p build
	as -o ./build/zadanie.o zadanie.s -gstabs
