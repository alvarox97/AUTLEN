/*Grupò 2*/
#include "estado.h"

typedef struct _estado{
    char* nombre;
    int tipo;
}estado;

estado* crear_estado(char* nombre, int tipo){

  estado* est = NULL;

  if((tipo > 3 || tipo < 0) || (nombre == NULL))
    return NULL;

  /*Asignamos memoria para la estructura estado*/

  est = (estado *)malloc(sizeof(estado));
  if(!est)
    return NULL;

  /*Guardamos tipo en la estructura*/
  est->tipo = tipo;

  /*Reservamos memoria para el nombre del estado y copiamos el nombre correspondiente*/

  est->nombre = (char*)malloc((strlen(nombre)+1)*(sizeof(char)));
  if(!est->nombre)
    return NULL;
  strcpy(est->nombre, nombre);

  return est;
}

void eliminar_estado(estado* est){
  if (!est)
    return;

  free(est->nombre);
  free(est);

  return;
}

void estado_imprimir(FILE* fichero, estado* est){
  if (!fichero || !est)
    return;

  switch(est->tipo){
    case EST_INICIAL:
      fprintf(fichero, "->%s ", est->nombre);
      break;
    case EST_FINAL:
      fprintf(fichero, "%s* ", est->nombre);
      break;
    case EST_NORMAL:
      fprintf(fichero, "%s ", est->nombre);
      break;
    case EST_INICIAL_Y_FINAL:
      fprintf(fichero, "%s* ", est->nombre);
      break;
  }
  return;
}

int estado_es(estado* est, char* nombre){
  if(!est || !nombre)
    return 0;
  if(strcmp(est->nombre, nombre) == 0)
    return 1;
  else{
    return 0;
  }
}

char* estado_nombre(estado* est){
  if(!est)
    return NULL;
  return est->nombre;
}

int estado_tipo(estado* est){
  if(!est)
    return 4;
  return est->tipo;
}
