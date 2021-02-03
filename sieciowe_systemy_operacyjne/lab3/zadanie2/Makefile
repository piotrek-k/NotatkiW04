CFLAGS=-Wall -ggdb -std=c99 -lrt -pthread

minishell: minishell.c
	#gcc $(CFLAGS) -o minishell.out minishell.c
	gcc minishell.c -o minishell.out -lrt -pthread -Wall

test:
	./minishell.out ls -la + cat -n + tac + tail -20