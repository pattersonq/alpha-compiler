#include <stdio.h>
#include <string.h>
#include "sym_table.h"

#define MAX_LINE_LENGTH 256

// Devolver el numero de espacios en un string
// Y borrar el ultimo caracter 
// para evitar los saltos de linea
int count_spaces(char* line) {
    int n = 0;

    while(*line) {
        if(*line == ' ')
            n++;
        line++;
    }
    line--;
    if(*line == '\n' || *line == '\r')
        (*line) = (char)0;

    return n;
}

int main(int argc, char ** argv) {
    FILE* in_file;
    FILE* out_file;
    stable* table;
    char buffer[MAX_LINE_LENGTH];
    char symbol[MAX_LINE_LENGTH];
    int value;

    // Open input/output files
    in_file = fopen(argv[1], "r");
    if(in_file == NULL) {
        return 1;
    }
    out_file = fopen(argv[2], "w");
    if(out_file == NULL) {
        fclose(in_file);
        return 1;
    }
    
    // Start table
    table = stable_init();
    if(table == NULL){
        fclose(in_file);
        fclose(out_file);
        return 1;
    }

    // Leer y procesar el archivo de entrada
    while(fgets(buffer, MAX_LINE_LENGTH, in_file)) {
        // Procesar la linea leida

        // Si solo hay un espacio hacer una busqueda
        if(count_spaces(buffer) == 0) {
            fprintf(out_file, 
                "%s %d\n", buffer,
                stable_search(table, buffer)
            );
        } else {
            // Leer los valores de la linea
            sscanf(buffer, "%s %d", symbol, &value);

            // Si es un cierre
            if(strcmp(symbol, "cierre") == 0) {
                if(close_ambit(table) == ERROR) {
                    fprintf(out_file, "Error cierre, nada que cerrar!\n");
                } else {
                    fprintf(out_file, "cierre\n");
                }
            } 
            // Si es una apertura
            else if (value < -1) {
                if(open_ambit(table, symbol, value) == ERROR) {
                    fprintf(out_file, "Error apertura, ya hay un ambito local abierto!\n");
                } else {
                    fprintf(out_file, "%s\n", symbol);
                }
            }
            // Si es una insercion
            else {
                if(stable_insert(table, symbol, value) == ERROR) {
                    fprintf(out_file, "%d %s\n", ERROR, symbol);
                } else {
                    fprintf(out_file, "%s\n", symbol);
                }
            }
        }
    }
        
    // Cerrar y salir
    stable_free(table);
    fclose(in_file);
    fclose(out_file);
    return 0;
}