/* Óscar Pinto y Luis Cárabe. Pareja 2, grupo 1401*/

#ifndef PALABRA_H
#define PALABRA_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct _palabra palabra;

palabra* crear_palabra();

void eliminar_palabra(palabra* palabra);

int palabra_get_size(palabra* palabra);

char** palabra_get_simbolos(palabra* palabra);

char* palabra_insertar_simbolo(palabra* palabra, char* simbolo);

void palabra_imprimir(FILE* fichero, palabra* palabra);


#endif
