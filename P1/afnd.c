#include "afnd.h"

typedef struct _AFND {
    char* nombre;
    alfabeto* alfabeto;
    int num_estados;
    int num_simbolos;
    int num_transiciones;
    estado** estados;
    palabra* cadena_actual;
    estado** estados_actuales;
    transicion** transiciones;
}AFND;

typedef struct _transicion{
    char* est_inicial;
    char* simbolo_entrante;
    int num_est;
    estado** est_final;
}transicion;

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

  return afnd;
}

void AFNDElimina(AFND* p_afnd);
void AFNDImprime(FILE * fd, AFND* p_afnd);
AFND * AFNDInsertaSimbolo(AFND * p_afnd, char * simbolo);
AFND * AFNDInsertaEstado(AFND * p_afnd, char * nombre, int tipo);

AFND * AFNDInsertaTransicion(AFND * p_afnd, char * nombre_estado_i, char * nombre_simbolo_entrada,char * nombre_estado_f ){

  int i=0,  flag_i=0, flag_f=0, flag_trn=0, index_f=0;
  char** simbolos = NULL;
  transicion* trn = NULL;

  if(!p_afnd || !nombre_estado_i || !nombre_simbolo_entrada || !nombre_estado_f){
    return NULL;
  }


  for(i=0; i<p_afnd->num_estados; i++){
      /*Comprobamos si tenemos el estado en el automata*/
    if(estado_es(p_afnd->estados[i], nombre_estado_i)){
      flag_i = 1;
    }
      /*Comprobamos que está el estado final */
    if(estado_es(p_afnd->estados[i], nombre_estado_f)){
      flag_f = 1;
      index_f = i;
    }

  }

  /*Si no esta alguno salimos */
  if(flag_i*flag_f != 1){
    return NULL;
  }

  /*Comprobamos que el simbolo está*/
  simbolos = alfabeto_get_simbolos(p_afnd->alfabeto);

  if(!simbolos){
    return NULL;
  }

  for(i=0; i<=p_afnd->num_simbolos; i++){
    if(strcmp(simbolos[i], nombre_simbolo_entrada) == 0){
      break;
    }

    if(i == p_afnd->num_simbolos){
      return NULL;
    }
  }

  /*Buscamos las transiciones del estado inicial*/
  for(i=0; i<p_afnd->num_transiciones; i++){
    if((strcmp(p_afnd->transiciones[i]->est_inicial, nombre_estado_i) == 0)
        && (strcmp(p_afnd->transiciones[i]->simbolo_entrante, nombre_simbolo_entrada) == 0)){
      trn = p_afnd->transiciones[i];
    }
  }

  if(!trn){
    /*Creamos una nueva transicion*/
    trn = crear_transicion(p_afnd, nombre_estado_i, nombre_simbolo_entrada, nombre_estado_f);
    if(!trn){
      return NULL;
    }
  }else{
    /*Si ya existe la transicion la modifico si es necesario*/

    for(i=0; i<trn->num_est; i++){
      if(estado_es(trn->est_final, nombre_estado_f)){
        /*Si ya está hemos acabado*/
        flag_trn = 1;
        break;
      }
    }

    /*Si no lo he encontrado en los estados finales de la transicion*/
    if(flag_trn == 0){
      /*Hago espacio para el estado*/
      trn->est_final = (estado**) realloc(trn->est_final, sizeof(estado *)*(trn->num_est + 1));
      if(!trn->est_final){
        return NULL;
      }
      /*Añado el estado*/
      trn->est_final[trn->num_est] = p_afnd->estados[index_f];
      trn->num_est += 1;
    }

  }

  /*Si llega hasta aquí es que sorprendentemente todo está correcto*/

  return p_afnd;


}
AFND * AFNDInsertaLetra(AFND * p_afnd, char * letra);
void AFNDImprimeConjuntoEstadosActual(FILE * fd, AFND * p_afnd);
void AFNDImprimeCadenaActual(FILE *fd, AFND * p_afnd);
AFND * AFNDInicializaEstado (AFND * p_afnd);
void AFNDProcesaEntrada(FILE * fd, AFND * p_afnd);
void AFNDTransita(AFND * p_afnd);
