#ifndef SYM_TABLE_H
#define SYM_TABLE_H

#define VARIABLE 1
#define PARAMETER 2
#define FUNCTION 3

#define BOOLEAN 1
#define INT 2

#define ESCALAR 1
#define VECTOR 2

#define ERROR -1


typedef struct stable stable;

// Crea la tabla de simbolos, devolviendo un puntero a ella o NULL en caso de error.
stable* stable_init();

// Libera la memoria asociada a la tabla de simbolos
void stable_free(stable* table);

// Inserta el simbolo dado en el ambito local si esta abierto,
// sino en el ambito global
// Devuelve ERROR en caso de error, sino devuelve el valor insertado
// Si el valor dado es ERROR no se inserta
int stable_insert(stable* table, const char* symbol, int value);

// Devuelve el valor asociado al simbolo dado
// si se encuentra en algun ambito
// sino devuelve ERROR
int stable_search(stable* table, const char* symbol);

// Abre un nuevo ambito con el nombre dado
// Devuelve ERROR en caso de error, sino el valor dado
int open_ambit(stable* table, const char* ambit, int value);

// Cierra el ultimo ambito abierto
// Devuelve ERROR si no hay ningun ambito abierto
int close_ambit(stable* table);

#endif