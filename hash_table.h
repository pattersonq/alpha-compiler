#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define START_SIZE 32
#define ERROR -1

// Estructura de la tabla hash: creada con htable_init y destruida con htable_free.
typedef struct htable htable;

// Crea la tabla hash devolviendo un puntero a ella o NULL en caso de error.
htable* htable_init();

// Libera la memoria asociada a una tabla hash.
void htable_free(htable* table);

// Dada una llave de la tabla hash devolvemos su valor. En caso de
// que no exista la llave se devuelve ERROR.
int htable_get(htable* table, const char* key);

// Dada una llave y un valor se añaden a la tabla hash. 
// Si la llave no existe aun se reserva nueva memoria. 
// Se devuelve el valor dado o ERROR si hay algun error de memoria.
// Si la llave ya existe se devuelve ERROR tambien.
// El valor no puede ser ERROR, de serlo no se inserta.
int htable_set(htable* table, const char* key, int value);

#endif