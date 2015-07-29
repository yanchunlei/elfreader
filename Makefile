$CFLAGS=-g -wall

main.o: src/main.c
	cc $(CFLAGS) -c src/main.c -o intermediate/main.o
all: main.o
	cc -g intermediate/main.o -o bin/elfreader
