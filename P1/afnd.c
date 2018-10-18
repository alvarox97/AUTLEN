#include "afnd.h"

typedef struct _AFND {
    char* nombre;
    alfabeto* alfabeto;
    int num_estados;
    int num_simbolos;
    estado** estados;
    palabra* cadena_actual;
    estado** estados_actuales;
    /*Funcion transicion*/
}AFND;

typedef struct _transicion{
    estado* est_inicial;
    char* simbolo_entrante;
    estado** est_final
}transicion;

transicion* crear_transicion(*AFND afnd, char* est_inicial, char* simbolo_entrante, char* est_final){
  transicion* trans = NULL;
  char* est_inicial_aux = NULL;
  char* simbolo_entrante_aux = NULL;
  char* est_final_aux = NULL;
  estado* est_aux = NULL;
  int i;

  if(!afnd || !est_inicial || !simbolo_entrante || !est_final)
    return NULL;

  trans = (transicion*)malloc(sizeof(transicion));
  if(!trans)
    return NULL;

  est_inicial_aux = (char*)malloc((strlen(est_inicial)+1)*sizeof(char));
  if(!est_inicial_aux){
    free(trans);
    return NULL;
  }
  strcpy(est_inicial_aux, est_incial);

  simbolo_entrante_aux = (char *)malloc((strlen(simbolo_entrante)+1)*sizeof(char));
  if(!simbolo_entrante_aux == NULL){
    free(trans);
    free(est_inicial_aux);
    return NULL;
  }
  strcpy(simbolo_entrante_aux, simbolo_entrante);

  trans->est_final = (estado**)malloc(sizeof(estado*));
  if(!trans->est_final){
    free(simbolo_entrante_aux);
    free(trans);
    free(est_inicial_aux);
    return NULL;
  }
  for(i=0, trans->est_final[0] = NULL;i< afnd->num_estados;i++){
    if(estado_es(afnd->estados[i], est_final)){
      trans->est_final[0]=afnd->estados[i];
      break;
    }
  }

  trans->num_est = 1;

  afnd->transiciones = (transicion**)realloc((afnd->num_transiciones + 1)* sizeof(transicion*));

  /*PROBLEMON SI AFND->TRANSICIONES ES NULL (NOS HEMOS CARGADO TODAS LAS TRANSICIONES)*/
  if(!afnd->transiciones){
    free(simbolo_entrante_aux);
    free(trans);
    free(est_inicial_aux);
    return NULL;
  }

  afnd->transciciones[afnd->num_transiciones] = trans;
  afnd->num_transiciones++;

  return trans;
}

AFND* AFNDNuevo(char* nombre, int num_estados, int num_simbolos){
  AFND* afnd = NULL;

  if(!nombre || num_estados < 0 || num_simbolos < 0 )
    return NULL;

  afnd = (AFND*)malloc(sizeof(AFND));
  if(!afnd)
    return NULL;

  afnd->nombre = (char*)malloc(stlen(nombre)*sizeof(char));
  if(!afnd->nombre){
    free(afnd);
    return NULL;
  }
  stdcpy(afnd->nombre, nombre);

  afnd->alfabeto = crear_alfabeto(nombre, num_simbolos);
  if(!afnd->alfabeto){
    free(afnd->nombre);
    free(afnd);
    return NULL;
  }
  afnd->num_estados = num_estados;
  afnd->num_simbolos = num_simbolos;

  afnd->estados = (estado**)malloc(num_estados*sizeof(estado*));
  if(!afnd->estados){
    eliminar_alfabeto(afnd->alfabeto);
    free(afnd->nombre);
    free(afnd);
    return NULL;
  }

  afnd->cadena_actual = crear_palabra();
  if(!afnd->cadena_actual){
    free(afnd->estados);
    eliminar_alfabeto(afnd->alfabeto);
    free(afnd->nombre);
    free(afnd);
    return NULL;
  }

  afnd->estados_actuales = (estado**)malloc(num_estados*sizeof(estado*));
  if(!afnd->estados_actuales){
    eliminar_palabra(afnd->cadena_actual);
    free(afnd->estados);
    eliminar_alfabeto(afnd->alfabeto);
    free(afnd->nombre);
    free(afnd);
    return NULL;
  }

  afnd->num_transiciones = 0;
  afnd->transiciones = (transicion **) malloc(sizeof(transicion*));
  if(!afnd->transiciones){
    free(estados_actuales);
    eliminar_palabra(afnd->cadena_actual);
    free(afnd->estados);
    eliminar_alfabeto(afnd->alfabeto);
    free(afnd->nombre);
    free(afnd);
    return NULL;
  }

  return afnd;
}

void AFNDElimina(AFND* p_afnd);
void AFNDImprime(FILE * fd, AFND* p_afnd);
AFND * AFNDInsertaSimbolo(AFND * p_afnd, char * simbolo);
AFND * AFNDInsertaEstado(AFND * p_afnd, char * nombre, int tipo);
AFND * AFNDInsertaTransicion(AFND * p_afnd,
                             char * nombre_estado_i,
                             char * nombre_simbolo_entrada,
                             char * nombre_estado_f );
AFND * AFNDInsertaLetra(AFND * p_afnd, char * letra);
void AFNDImprimeConjuntoEstadosActual(FILE * fd, AFND * p_afnd);
void AFNDImprimeCadenaActual(FILE *fd, AFND * p_afnd);
AFND * AFNDInicializaEstado (AFND * p_afnd);
void AFNDProcesaEntrada(FILE * fd, AFND * p_afnd);
void AFNDTransita(AFND * p_afnd);
