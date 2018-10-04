#ifndef ALFABETO_H
#define ALFABETO_H

typedef struct alfabeto;

alfabeto* crear_alfabeto();

void eliminar_alfabeto(alfabeto* alfabeto);

int alfabeto_get_size(alfabeto* alfabeto);

char** alfabeto_get_simbolos(alfabeto* alfabeto);

char* alfabeto_insertar_simbolo(alfabeto* alfabeto, char* simbolo);

#endif
