TEST_NUMBERS = 1 2 3 4
MAIN = pruebaSintactico

all: pruebaSintactico

pruebaSintactico: y.tab.o lex.yy.o pruebaSintactico.o
	gcc -o pruebaSintactico y.tab.o lex.yy.o pruebaSintactico.o

pruebaSintactico.o: pruebaSintactico.c
	gcc -Wall -ansi -pedantic -c -o pruebaSintactico.o pruebaSintactico.c

lex.yy.o: lex.yy.c
	gcc -ansi -pedantic -c -o lex.yy.o lex.yy.c

y.tab.o: y.tab.c
	gcc -ansi -pedantic -c -o y.tab.o y.tab.c

y.tab.c: alfa.y
	bison -dyv alfa.y

y.tab.h: alfa.y
	bison -dyv alfa.y

lex.yy.c: alfa.l y.tab.h
	flex alfa.l

clean:
	rm -rf -rf pruebaSintactico *.o lex.yy.c y.tab.h y.tab.c y.output salidas_programa/*

test: pruebaSintactico
	@printf "\n"
	@for number in $(TEST_NUMBERS) ; do \
		printf "\n\nDirerencias $$number\n" ; \
		./$(MAIN) entradas/entrada_sin_$$number.txt salidas_programa/misalida_sin_$$number.txt; \
		diff -B -b salidas/salida_sin_$$number.txt salidas_programa/misalida_sin_$$number.txt; \
	done
	@printf "\n"

