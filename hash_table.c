#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "hash_table.h"

#define OFFSET 14695981039346656037UL
#define PRIME 1099511628211UL

// Entrada en la tabla hash
typedef struct {
    const char* key;  
    int value;
} htable_entry;

// Estructura tabla hash
struct htable {
    htable_entry* items;  // las propias entrada
    size_t space;    // tamaño del array
    size_t size;      // numero de elementos en la tabla
};

// Crea la tabla hash devolviendo un puntero a ella o NULL en caso de error.
htable* htable_init() {
    // Reservar memoria para la tabla hash
    htable* table = malloc(sizeof(htable));
    if (table == NULL) {
        return NULL;
    }
    table->size = 0;
    table->space = START_SIZE;

    // Ponemos a cero las entradas libres
    table->items = calloc(table->space, sizeof(htable_entry));
    if (table->items == NULL) {
        free(table);
        return NULL;
    }

    return table;
}

// Libera la memoria asociada a una tabla hash.
void htable_free(htable* table) {
    // Si la tabla no es NULL
    if(table == NULL)
        return;

    // Liberamos las claves hash
    for (size_t i = 0; i < table->space; i++) {
        if (table->items[i].key != NULL) {
            free((void*)table->items[i].key);
        }
    }

    // Liberamos las entradas y la tabla
    free(table->items);
    free(table);
}

// Calcular un hash a partir de la clave dada
static uint64_t hash_key(const char* key) {
    // Generar un hash a partir 
    // de una de las claves de la tabla
    uint64_t hash = OFFSET;
    for (const char* p = key; *p; p++) {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= PRIME;
    }
    return hash;
}

// Dada una llave de la tabla hash devolvemos su valor. En caso de
// que no exista la llave se devuelve NULL.
int htable_get(htable* table, const char* key) {
    // Comprobamos que la clave dada esta en la tabla
    uint64_t hash = hash_key(key);

    // Calculamos el indice en la tabla a partir del 
    // hash y de la capacidad de la tabla
    size_t idx = (size_t)(hash % (uint64_t)table->space);

    // Recorremos todas las posiciones ocupadas
    // desde el indice hasta que se encuentre alguna vacia
    // La clave dada, de estar, estara en alguna de estas posiciones
    while (table->items[idx].key != NULL) {
        if (strcmp(key, table->items[idx].key) == 0) {
            // Si la encontamos la devolvemos
            return table->items[idx].value;
        }
        idx++;
        if (idx >= table->space) {
            // Si llegamos al final damos la vuelta
            idx = 0;
        }
    }

    // Si no la encontramos devolvemos NULL
    return ERROR;
}

// Función interna para actualizar/anadir una entrada.
int htable_set_entry(htable_entry* items, size_t space,
        const char* key, int value, size_t* psize) {
    // Calculamos el indice correspondiente a la entrada a partir del hash
    // Y del tamano de la tabla
    uint64_t hash = hash_key(key);
    size_t index = (size_t)(hash % (uint64_t)space);

    // Iteramos hasta encontrar una entrada vacia
    while (items[index].key != NULL) {
        if (strcmp(key, items[index].key) == 0) {
            // Si encontramos que la llave ya existe, devolvemos NULL
            return ERROR;
        }
        // Como la llave no esta en esta entrada, avanzamos a la siguiente
        index++;
        if (index >= space) {
            // Si alcanzamos el final del array, volvemos al comienzo.
            index = 0;
        }
    }

    // Si no encontramos la llave, reservamos memoria y añadimos la entrada
    if (psize != NULL) {
        key = strdup(key);
        if (key == NULL) {
            return ERROR;
        }
        (*psize)++;
    }
    items[index].key = (char*)key;
    items[index].value = value;
    return value;
}

// Agrandar la tabla al doble de su tamano
int htable_expand(htable* table) {
    // Nuevo espacio para las entradas
    size_t new_space = table->space * 2;
    if (new_space < table->space)
        return ERROR;  // Error de overflow numerico
    // Reservar nuevo espacio
    htable_entry* new_items = calloc(new_space, sizeof(htable_entry));
    if (new_items == NULL) {
        return ERROR;
    }

    // Copiar todas las entradas no vacias a la nueva tabla
    htable_entry entry;
    for (size_t i = 0; i < table->space; i++) {
        entry = table->items[i];
        if (entry.key != NULL) {
            htable_set_entry(
                new_items, 
                new_space, 
                entry.key,
                entry.value, 
                NULL
            );
        }
    }

    // Liberar las entradas antiguas.
    free(table->items);
    table->items = new_items;
    table->space = new_space;
    return ERROR + 1;
}

// Dada una llave y un valor se añaden a la tabla hash. 
// Si la llave no existe aun se reserva nueva memoria. 
// Se devuelve el valor dado o ERROR si hay algun error de memoria.
// Si la llave ya existe se devuelve ERROR tambien.
// El valor no puede ser ERROR, de serlo no se inserta.
int htable_set(htable* table, const char* key, int value) {
    // Comprobamos que el valor dado no es ERROR
    if (value == ERROR)
        return ERROR;

    // Expandimos la tabla si se va a sobrepasar la
    // mitad de la capacidad
    if (table->size >= table->space / 2) {
        if (htable_expand(table) == ERROR) {
            return ERROR;
        }
    }

    // Añadimos la entrada y actualizamos el tamaño
    return htable_set_entry(table->items, table->space, key, value,
                        &table->size);
}

