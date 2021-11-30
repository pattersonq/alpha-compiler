#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"
#include "sym_table.h"

struct stable {
    htable* global_table;
    htable* local_table;
};

// Crea la tabla de simbolos, devolviendo un puntero a ella o NULL en caso de error.
stable* stable_init() {
    // Reservar memoria para la tabla de sumbolos
    stable* table = malloc(sizeof(stable));
    if (table == NULL) {
        return NULL;
    }

    // Inicializa la tabla global
    table->global_table = htable_init();

    // Marca la tabla local como cerrada
    table->local_table = NULL;

    return table;
}

// Libera la memoria asociada a la tabla de simbolos
void stable_free(stable* table){
    // Libera las tablas hash de los ambitos
    htable_free(table->global_table);
    htable_free(table->local_table); // (htable_free ya hace un NULL check)

    // Libera la tabla de simbolos
    free(table);
}

// Inserta el simbolo dado en el ambito local si esta abierto,
// sino en el ambito global
// Devuelve ERROR en caso de error, sino devuelve el valor insertado
// Si el valor dado es ERROR no se inserta
int stable_insert(stable* table, const char* symbol, int value) {
    if(table == NULL || symbol == NULL)
        return ERROR;

    // Si la tabla local esta abierta lo insertamos en esta
    if(table->local_table != NULL)
        return htable_set(table->local_table, symbol, value);
        
    // Sino lo insertamos en la tabla global
    return htable_set(table->global_table, symbol, value);
}

// Devuelve el valor asociado al simbolo dado
// si se encuentra en algun ambito
// sino devuelve ERROR
int stable_search(stable* table, const char* symbol) {
    int value;
    if(table == NULL || symbol == NULL)
        return ERROR;

    // Buscamos el valor en la tabla local si esta abierta
    if(table->local_table != NULL) {
        value = htable_get(table->local_table, symbol);
        if(value != ERROR)
            return value;
    }

    // Si la tabla no esta abierta o el valor no se ha encontrado
    // Se busca en la tabla local
    return htable_get(table->global_table, symbol);
}

// Abre un nuevo ambito con el nombre dado
// Devuelve ERROR en caso de error, sino el valor dado
int open_ambit(stable* table, const char* ambit, int value) {
    // Si ya hay un ambito abierto devuelve NULL
    if(table == NULL || ambit == NULL || table->local_table != NULL)
        return ERROR;

    // Insertar el nuevo ambito en la tabla global
    if(htable_set(table->global_table, ambit, value) == ERROR)
        return ERROR;

    // Abrir ambito local
    table->local_table = htable_init();
    if(table->local_table == NULL)
        return ERROR;

    // Insertar el nuevo ambito en la tabla local
    return htable_set(table->local_table, ambit, value);
}

// Cierra el ultimo ambito abierto
// Devuelve ERROR si no hay ningun ambito abierto
int close_ambit(stable* table) {
    if(table == NULL || table->local_table == NULL)
        return ERROR;

    // Liberar la tabla local
    htable_free(table->local_table);
    table->local_table = NULL;
    return ERROR + 1;
}