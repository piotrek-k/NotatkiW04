build_app:
	mkdir -p build
	gcc init.c -o ./build/init -lm -lrt -pthread
	gcc prod.c -o ./build/prod -lrt -pthread
	gcc cons.c -o ./build/cons -lrt -pthread