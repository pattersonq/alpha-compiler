CFLAGS = -Wall -g 

all : prueba_tabla

clean :
	rm -f *.o
	rm test_files/test.txt
	rm prueba_tabla

prueba_tabla : prueba_tabla.c sym_table.c hash_table.c
	$(CC) $(CFLAGS) -o $@ $@.c sym_table.c hash_table.c

test: prueba_tabla
	./prueba_tabla test_files/entrada1_p4.txt test_files/test.txt
	diff -b -B test_files/test.txt test_files/salida1_p4.txt
	./prueba_tabla test_files/entrada2_p4.txt test_files/test.txt
	diff -b -B test_files/test.txt test_files/salida2_p4.txt

valgrind_test: prueba_tabla
	valgrind --leak-check=full ./prueba_tabla test_files/entrada1_p4.txt test_files/test.txt
	diff -b -B test_files/test.txt test_files/salida1_p4.txt
	valgrind --leak-check=full ./prueba_tabla test_files/entrada2_p4.txt test_files/test.txt
	diff -b -B test_files/test.txt test_files/salida2_p4.txt
