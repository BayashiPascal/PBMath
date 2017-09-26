OPTIONS_DEBUG=-ggdb -g3 -Wall
OPTIONS_RELEASE=-O3 
OPTIONS=$(OPTIONS_DEBUG)

all : main

main: main.o pbmath.o Makefile 
	gcc $(OPTIONS) main.o pbmath.o -o main -lm

main.o : main.c pbmath.h Makefile
	gcc $(OPTIONS) -c main.c

pbmath.o : pbmath.c pbmath.h Makefile
	gcc $(OPTIONS) -c pbmath.c

clean : 
	rm -rf *.o main

valgrind :
	valgrind -v --track-origins=yes --leak-check=full --gen-suppressions=yes --show-leak-kinds=all ./main
