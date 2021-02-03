CFLAGS=-Wall -ggdb -std=c99
INC=
CC=gcc
SRCS=$(wildcard *.c)
DSTS=$(patsubst %.c, %, $(SRCS))
OBJS=$(patsubst %.c, %.o, $(SRCS))

SRCDIR=zadanie1

# CC=gcc

# szukaj plików z rozszerzeniem .c w folderze
# SRCDIR
vpath %.c $(SRCDIR)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INC) -o $@ -c $<

fork: fork.c
	gcc $(CFLAGS) -o fork fork.c

test:
	@echo Źródła: '$(SRCS)'
	@echo OBJS: '$(OBJS)'
	@echo Cele: '$(DSTS)'

clean:
	rm -f fork
	# ignorowanie błędu:
	# -rm
	# nie wypisywanie wykonywanej komendy
	# @rm

pliki.zip: $(SRCS) Makefile
	zip $@ $^

zip: pliki.zip

.PHONY: clean zip