#ifndef PALABRA_H
#define PALABRA_H

typedef struct palabra;

palabra* crear_palabra();

void eliminar_palabra(palabra* palabra);

int palabra_get_size(palabra* palabra);

char** palabra_get_simbolos(palabra* palabra);

char* palabra_insertar_simbolo(palabra* palabra, char* simbolo);

#endif
