#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "palabra.h"

/**
 * Implementacion de hash con una lista enlazada para controlar
 * colisiones
 */
typedef struct _palabra{
  char** simbolos;
  int size;
}palabra;

palabra* crear_palabra(){

  palabra* palabra = NULL;

  if(!simbolos){
    return NULL;
  }

  /*Asignamos memoria para la palabra*/
  palabra = (palabra *) malloc(sizeof(palabra));

  if(!palabra){
    return NULL;
  }

  /*Asignamos memoria para el puntero de simbolos*/
  palabra->simbolos = (char **) malloc(sizeof(char *));

  if(!palabra->simbolos){
    free(palabra);
    return NULL;
  }

  /*Asignamos el tamaño de la palabra*/
  palabra->size = 0;

  /*Devolvemos la palabra*/
  return palabra;
}

void eliminar_palabra(palabra* palabra){
  int i = 0:
  if(!palabra){
    return;
  }

  if(!palabra->simbolos){
    free(palabra):
    return;
  }

  /*En caso de tener simbolos los liberamos tambien*/
  for(i=0; i<palabra->size; i++){
    if(palabra->simbolos[i]){
      free(palabra->simbolos[i]);
    }
  }
  free(palabra->simbolos);
  free(palabra);
}

int palabra_get_size(palabra* palabra){
  if(!palabra){
    return -1;
  }

  return palabra->size;
}

char** palabra_get_simbolos(palabra* palabra){
  if(!palabra){
    return NULL;
  }

  return palabra->simbolos;
}

char* palabra_insertar_simbolo(palabra* palabra, char* simbolo){
  if(!palabra || !simbolo){
    return NULL;
  }

  /*Comprobamos si existe suficiente memoria en el array*/
  if(palabra->size >= sizeof(*palabra->simbolos)/sizeof(char*)){
    /*Si no la hay hacemos realloc y añadimos memoria para un simbolo*/
		palabra->simbolos = (char**) realloc(palabra->simbolos, sizeof(*palabra->simbolos) + sizeof(char*));
  }

  /*Comprobamos que el puntero no ha explosionado como una bomba H*/
  if(!palabra->simbolos){
    return NULL;
  }

  /*Reservamos memoria para el nuevo simbolo*/
  palabra->simbolos[palabra->size] = (char*) malloc(sizeof(char)*(strlen(simbolo) + 1));

  if(!palabra->simbolos[palabra->size]){
    return NULL;
  }

  /*Añadimos el simbolo a la palabra*/
  if(!strcpy(palabra->simbolos[palabra->size], simbolo)){
    free(palabra->simbolos[palabra->size]);
    return NULL;
  }

  /*Si todo correcto devolvemos la palabra*/
  palabra->size++;
  return palabra;
}
