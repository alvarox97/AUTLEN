#include "alfabeto.h"

typedef struct alfabeto;

alfabeto* crear_alfabeto(){
  alfabeto* new_alfabeto = NULL;

  new_alfabeto = (alfabeto*) malloc(sizeof(alfabeto));

  if(!new_alfabeto){
    return NULL;
  }

  new_alfabeto->palabra = crear_palabra();

  if(!new_alfabeto->palabra){
    free(new_alfabeto);
    return NULL;
  }

  return new_alfabeto;
}

void eliminar_alfabeto(alfabeto* alfabeto){
  
}

int alfabeto_get_size(alfabeto* alfabeto);

char** alfabeto_get_simbolos(alfabeto* alfabeto);

char* alfabeto_insertar_simbolo(alfabeto* alfabeto, char* simbolo);
