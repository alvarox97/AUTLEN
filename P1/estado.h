#ifndef ESTADO_H
#define ESTADO_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#define EST_INICIAL 0
#define EST_FINAL   1
#define EST_INICIAL_Y_FINAL 2
#define EST_NORMAL 3

typedef struct _estado estado;
estado* crear_estado(char* nombre, int tipo);
void eliminar_estado(estado* est);
void estado_imprimir(FILE* fichero, estado* est);
int estado_es(estado* est, char* nombre);
char* estado_nombre(estado* est);
int estado_tipo(estado* est);


#endif
