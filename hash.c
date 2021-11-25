#include "hash.h"
#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

// Entrada en la tabla hash
typedef struct {
    const char* key;  
    void* value;
} ht_entry;

// Estructura tabla hash
struct ht {
    ht_entry* entries;  // las propias entrada
    size_t capacity;    // tamaño del array
    size_t length;      // numero de elementos en la tabla
};

ht* ht_create(void) {
    // Reservar memoria para la tabla hash
    ht* table = malloc(sizeof(ht));
    if (table == NULL) {
        return NULL;
    }
    table->length = 0;
    table->capacity = INITIAL_CAPACITY;

    // Ponemos a cero las entradas libres
    table->entries = calloc(table->capacity, sizeof(ht_entry));
    if (table->entries == NULL) {
        free(table); // error, free table before we return!
        return NULL;
    }
    return table;
}

void ht_destroy(ht* table) {
    // Liberamos las claves hash
    for (size_t i = 0; i < table->capacity; i++) {
        if (table->entries[i].key != NULL) {
            free((void*)table->entries[i].key);
        }
    }

    // Liberamos las entradas y la tabla en si
    free(table->entries);
    free(table);
}

static uint64_t hash_key(const char* key) {
    uint64_t hash = FNV_OFFSET;
    for (const char* p = key; *p; p++) {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
}

void* ht_get(ht* table, const char* key) {
    // Anadimos el hash para asegurarnos que esta en la tabla
    uint64_t hash = hash_key(key);
    size_t index = (size_t)(hash & (uint64_t)(table->capacity - 1));

    // Buscamos entrada libre
    while (table->entries[index].key != NULL) {
        if (strcmp(key, table->entries[index].key) == 0) {
            // Si la encontamos la devolvemos
            return table->entries[index].value;
        }
        index++;
        if (index >= table->capacity) {
            // Si no encontramos volvemos a empezar
            index = 0;
        }
    }
    return NULL;
}

// Expand hash table to twice its current size. Return true on success,
// false if out of memory.
static bool ht_expand(ht* table) {
    // Allocate new entries array.
    size_t new_capacity = table->capacity * 2;
    if (new_capacity < table->capacity) {
        return false;  // overflow (capacity would be too big)
    }
    ht_entry* new_entries = calloc(new_capacity, sizeof(ht_entry));
    if (new_entries == NULL) {
        return false;
    }

    // Iterate entries, move all non-empty ones to new table's entries.
    for (size_t i = 0; i < table->capacity; i++) {
        ht_entry entry = table->entries[i];
        if (entry.key != NULL) {
            ht_set_entry(new_entries, new_capacity, entry.key,
                         entry.value, NULL);
        }
    }

    // Free old entries array and update this table's details.
    free(table->entries);
    table->entries = new_entries;
    table->capacity = new_capacity;
    return true;
}

const char* ht_set(ht* table, const char* key, void* value) {
    // Comprobamos que el valor dado no es NULL
    assert(value != NULL);
    if (value == NULL) {
        return NULL;
    }

    // Expandimos la tabla si se va a sobrepasar la
    // mitad de la capacidad
    if (table->length >= table->capacity / 2) {
        if (!ht_expand(table)) {
            return NULL;
        }
    }

    // Añadimos la entrada y actualizamos el tamaño
    return ht_set_entry(table->entries, table->capacity, key, value,
                        &table->length);
}

// Función interna para settear una entrada.
static const char* ht_set_entry(ht_entry* entries, size_t capacity,
        const char* key, void* value, size_t* plength) {
    // AND hash with capacity-1 to ensure it's within entries array.
    uint64_t hash = hash_key(key);
    size_t index = (size_t)(hash & (uint64_t)(capacity - 1));

    // Iteramos hasta encontrar una entrada vacia
    while (entries[index].key != NULL) {
        if (strcmp(key, entries[index].key) == 0) {
            // Si encontramos que la llave ya existe, actualizamos su valor
            entries[index].value = value;
            return entries[index].key;
        }
        // Como la llave no esta en esta entrada, avanzamos a la siguiente
        index++;
        if (index >= capacity) {
            // Si alcanzamos el final del array, volvemos al comienzo.
            index = 0;
        }
    }

    // Si no encontramos la llave, reservamos memoria y añadimos la entrada
    if (plength != NULL) {
        key = strdup(key);
        if (key == NULL) {
            return NULL;
        }
        (*plength)++;
    }
    entries[index].key = (char*)key;
    entries[index].value = value;
    return key;
}

// Devuelve un objeto por el que se puede iterar
hti ht_iterator(ht* table) {
    hti it;
    it._table = table;
    it._index = 0;
    return it;
}

bool ht_next(hti* it) {
    // Iteramos hasta encontrar un espacio lleno en la tabla
    ht* table = it->_table;
    while (it->_index < table->capacity) {
        size_t i = it->_index;
        it->_index++;
        if (table->entries[i].key != NULL) {
            // Encontramos una entrada no vacia asi que cambiamos el indice 
            ht_entry entry = table->entries[i];
            it->key = entry.key;
            it->value = entry.value;
            return true;
        }
    }
    return false;
}

