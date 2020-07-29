build_app:
	mkdir -p build
	gcc init.c -o ./build/init -lrt -lm
	gcc prod.c -o ./build/prod -lrt -lm
	gcc cons.c -o ./build/cons -lrt -lm

test:
	./build/mq_snd 1 100