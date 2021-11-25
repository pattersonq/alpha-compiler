// Estructura de la tabla hash: creada con ht_create y destruida con ht_destroy.
typedef struct ht ht;

// Crea la tabla hash devolviendo un puntero a ella o NULL en caso de error.
ht* ht_create(void);

// Libera la memoria asociada a una tabla hash.
void ht_destroy(ht* table);

// Dada una llave de la tabla hash devolvemos su valor. En caso de
// que no exista la llave se devuelve NULL.
void* ht_get(ht* table, const char* key);

// Dada una llave y un valor se añaden a la tabla hash. Si la llave
// no existe aun se copia reserva nueva memoria. Se devuelve la
// direccion de la llave o NULL si hay algun error de memoria.
// El valor de entrada no puede ser NULL.
const char* ht_set(ht* table, const char* key, void* value);

// Devuelve el numero de elementos en la tabla hash.
size_t ht_length(ht* table);

// Estructura de un iterador de la tabla hash.
// Se crea con ht_iterator y se itera con ht_next.
typedef struct {
    const char* key;  // Llave actaul
    void* value;      // Valor actual

    ht* _table;       // referencia a la tabla hash que se esta iterando
    size_t _index;    // indice actual en el array entries
} hti;

// Devuelve un iterador de la tabla hash indicada
hti ht_iterator(ht* table);

// Mueve el iterador al siguiente elemento de la tabla hash. Si no
// quedan elementos en la tabla hash devuelve False. No se debe llamar
// a ht_set mientras se itera por la tabla.
bool ht_next(hti* it);