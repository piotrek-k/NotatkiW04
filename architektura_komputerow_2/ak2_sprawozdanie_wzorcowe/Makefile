# reguła linkowania
hello: hello.o
	ld -o ./build/hello ./build/hello.o

# reguła kompilacji
hello.o: hello.s
	mkdir build
	as -o ./build/hello.o hello.s