CC = gcc
CFLAGS = -Wall -g 

all : prueba_tabla

clean :
	rm -f prueba_tabla.o prueba_tabla hash_table.o sym_table.o

prueba_tabla : prueba_tabla.c sym_table.o
	$(CC) $(CFLAGS) -o $@ $@.c sym_table.o
	./prueba_tabla

sym_table.o : hash_table.o sym_table.c
	$(CC) $(CFLAGS) -c sym_table.c hash_table.o

hash_table.o : hash_table.c
	$(CC) $(CFLAGS) -c $<