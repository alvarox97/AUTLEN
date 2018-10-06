#include "alfabeto.h"

typedef struct _alfabeto{
  palabra* palabra;
} alfabeto;

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
  if(!alfabeto){
    return;
  }

  if(!alfabeto->palabra){
    free(alfabeto);
    return;
  }

  eliminar_palabra(alfabeto->palabra);
  free(alfabeto);
}

int alfabeto_get_size(alfabeto* alfabeto){
  if(!alfabeto || !alfabeto->palabra){
    return -1;
  }

  return palabra_get_size(alfabeto->palabra);
}

char** alfabeto_get_simbolos(alfabeto* alfabeto){
  if(!alfabeto || !alfabeto->palabra){
    return NULL;
  }

  return palabra_get_simbolos(alfabeto->palabra);
}

char* alfabeto_insertar_simbolo(alfabeto* alfabeto, char* simbolo){
  int i = 0;
  char ** simbolos = NULL;

  if(!alafabeto || !alfabeto->palabra || !simbolo){
    return NULL;
  }


  /*Obtenemos la lista de simbolos*/
  simbolos = palabra_get_simbolos(alfabeto->palabra);

  if(!simbolos){
    return NULL;
  }

  /*Comprobamos que no se repite el simbolo*/
  for(i=0; i<alfabeto_get_size(alfabeto); i++){
    if(strcmp(simbolos[i], simbolo) == 0){
      return NULL;
    }
  }

  /*Si no se repite lo insertamos */

  if(!palabra_insertar_simbolo(alfabeto->palabra, simbolo)){
    return NULL;
  }

  /*Devolvemos el simbolo insertado*/
  return simbolos[alfabeto_get_size(alfabeto) - 1];
}
