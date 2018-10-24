/* Óscar Pinto y Luis Cárabe. Pareja 2, grupo 1401*/

#ifndef ESTADO_H
#define ESTADO_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#define INICIAL 0
#define FINAL   1
#define INICIAL_Y_FINAL 2
#define NORMAL 3

typedef struct _estado estado;
estado* crear_estado(char* nombre, int tipo);
void eliminar_estado(estado* est);
void estado_imprimir(FILE* fichero, estado* est);
int estado_es(estado* est, char* nombre); /*Devuelve 1 si el estado est tiene como nombre el char* nombre, 0 si no*/
char* estado_nombre(estado* est); /*Devuelve el nombre del estado*/
int estado_tipo(estado* est); /*Devuelve el tipo del estado*/


#endif
