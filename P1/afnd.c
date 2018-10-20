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

transicion* crear_transicion(*AFND afnd, char* est_inicial, char* simbolo_entrante, char* est_final){
  transicion* trans = NULL;
  estado* est_aux = NULL;
  int i;
  /*Comprobamos que los argumentos recibidos no están vacíos*/
  if(!afnd || !est_inicial || !simbolo_entrante || !est_final)
    return NULL;

  /*Reservamos memoria para la transición*/
  trans = (transicion*)malloc(sizeof(transicion));
  if(!trans)
    return NULL;

  /*Reservamos memoria y copiamos el nombre de nuestro estado inicial*/

  trans->est_inicial = (char*)malloc((strlen(est_inicial)+1)*sizeof(char));
  if(!trans->est_inicial){
    free(trans);
    return NULL;
  }
  strcpy(trans->est_inicial, est_inicial);

  /*Reservamos memoria y copiamos el símbolo introducido*/

  trans->simbolo_entrante = (char *)malloc((strlen(simbolo_entrante)+1)*sizeof(char));
  if(!trans->simbolo_entrante == NULL){
    free(trans->est_inicial);
    free(trans);
    return NULL;
  }
  strcpy(trans->simbolo_entrante, simbolo_entrante);

  /*Reservamos memoria para la lista de estados finales*/

  trans->est_final = (estado**)malloc(sizeof(estado*));
  if(!trans->est_final){
    free(trans->simbolo_entrante);
    free(trans->est_inicial);
    free(trans);
    return NULL;
  }

  /*Buscamos el estado final en la lista de estados y lo añadimos*/

  for(i=0, trans->est_final[0] = NULL;i< afnd->num_estados;i++){
    if(estado_es(afnd->estados[i], est_final)){
      trans->est_final[0]=afnd->estados[i];
      break;
    }
  }

  /*Por el momento solo tenemos un estado final*/
  trans->num_est = 1;

  /*Guardamos la transición el el array de transiciones, comprobando si necesitamos reservar más memoria*/

  afnd->transiciones = (transicion**)realloc((afnd->num_transiciones + 1)* sizeof(transicion*));

  /*Comprobamos si ha habido algún error*/
  if(!afnd->transiciones){
    free(trans->simbolo_entrante);
    free(trans->est_inicial);
    free(trans);
    return NULL;
  }
  /*Guardamos la nueva transición en la lista de transciones*/
  afnd->transciciones[afnd->num_transiciones] = trans;
  afnd->num_transiciones++;

  return trans;
}

void eliminar_transicion(transicion* trans){
  if(!trans)
    return;
  /*Liberamos todos los recursos (sin liberar cada estado final, ya que apuntan a los estados del afnd)*/
  free(trans->est_incial);
  free(trans->simbolo_entrante);
  free(trans->est_final);
  free(trans);
}

void transicion_imprimir(FILE* fd, transicion* trans){
  int i;
  /*Comprobamos que los argumentos de entrada sean válidos*/
  if(!fd || !trans)
    return;
  /*Imprimimos el estado inicial y el símbolo entrante*/
  fprintf(fd, "f(%s,%s)={ ", trans->est_inicial, trans->simbolo_entrante);

  /*Imprimimos todos los estados finales*/
  for(i=0 ; i < trans->num_est ; i++){
    fprintf(fd, "%s ", estado_nombre(trans->est_final));
  }
  fprintf("}\n");
}

AFND* AFNDNuevo(char* nombre, int num_estados, int num_simbolos){
  AFND* afnd = NULL;

  /*Comprobamos que los argumentos sean válidos*/
  if(!nombre || num_estados < 0 || num_simbolos < 0 )
    return NULL;

  /*Reservamos memoria para el afnd*/
  afnd = (AFND*)malloc(sizeof(AFND));
  if(!afnd)
    return NULL;

  /*Reservamos memoria para su nombre y lo copiamos*/
  afnd->nombre = (char*)malloc(stlen(nombre)*sizeof(char));
  if(!afnd->nombre){
    free(afnd);
    return NULL;
  }
  stdcpy(afnd->nombre, nombre);

  /*Creamos su alfabeto*/
  afnd->alfabeto = crear_alfabeto("A", num_simbolos);
  if(!afnd->alfabeto){
    free(afnd->nombre);
    free(afnd);
    return NULL;
  }
  /*Copiamos el numero de estados y de simbolos*/
  afnd->num_estados = num_estados;
  afnd->num_simbolos = num_simbolos;

  /*Reservamos memoria para la lista de estados*/
  afnd->estados = (estado**)malloc(num_estados*sizeof(estado*));
  if(!afnd->estados){
    eliminar_alfabeto(afnd->alfabeto);
    free(afnd->nombre);
    free(afnd);
    return NULL;
  }

  /*Reservamos memoria para la cadena actual (es un apalabra)*/
  afnd->cadena_actual = crear_palabra();
  if(!afnd->cadena_actual){
    free(afnd->estados);
    eliminar_alfabeto(afnd->alfabeto);
    free(afnd->nombre);
    free(afnd);
    return NULL;
  }

  /*Reservamos memoria para la lista de estados actuales, que apuntarán a la lista de estados*/
  afnd->estados_actuales = (estado**)malloc(num_estados*sizeof(estado*));
  if(!afnd->estados_actuales){
    eliminar_palabra(afnd->cadena_actual);
    free(afnd->estados);
    eliminar_alfabeto(afnd->alfabeto);
    free(afnd->nombre);
    free(afnd);
    return NULL;
  }

  /*Reservamos memoria para las transiciones, si necesitamos más, luego haremos realloc*/
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

void AFNDElimina(AFND* p_afnd){
  int i;
  if(!p_afnd)
    return;

  /*Liberamos todos los recursos*/

  free(p_afnd->nombre);
  eliminar_alfabeto(p_afnd->alfabeto);
  for (i=0 ; i < p_afnd->num_estados ; i++){
    eliminar_estado(p_afnd->estados[i]);
  }
  free(estados);
  eliminar_palabra(p_afnd->cadena_actual);
  
  /*Los estados actuales son referencias a la lista de estados, por tanto no los eliminamos*/

  free(estados_actuales);

  for(i=0 ; i < p_afnd->num_transiciones ; i++){
    eliminar_transicion(p_afnd->transiciones[i]);
  }
  free(p_afnd->transiciones);
  free(p_afnd);
}

void AFNDImprime(FILE * fd, AFND* p_afnd){
  int i;
  /*Comprobamos que los argumentos de entrada sean válidos*/
  if(!fd || !p_afnd)
      return;

  /*Imprimimos el nombre...*/
  fprintf(fd, "%s={\n", p_afnd->nombre);
  /*... el número de simbolos y el alfabeto...*/
  fprintf(fd, "\tnum_simbolos = %d\n\n\t", p_afnd->num_simbolos);
  alfabeto_ìmprimir(fd, p_afnd->alfabeto);

  /*... el número de estados y la lista de estados...*/
  fprinf(fd, "\n\tnum_estados = %d\n", p_afnd->num_estados);
  fprintf(fd, "\n\tQ={");
  for(i=0; i < p_afnd->num_estados ; i++){
    estado_ìmprimir(fd, p_afnd->estados[i]);
  }
  fprintf(fd, "}\n");

  /*... y la función de transición*/
  fprintf(fd, "\n\tFunción de Transición = {\n\n");
  for(i=0 ; i < p_afnd->num_transiciones ; i++){
    fprintf(fd, "\t\t%s",transicion_imprimir(fd, p_afnd->transiciones));
  }
  fprintf(fd, "\t}\n}");
}

AFND * AFNDInsertaSimbolo(AFND * p_afnd, char * simbolo){
  if(!p_afnd || !simbolo)
    return NULL;
  /*Insertamos el símbolo en el alfabeto, comprobando que no es NULL la salida*/
  if(!alfabeto_insertar_simbolo(p_afnd->alfabeto, simbolo))
    return NULL;

  return p_afnd;
}

AFND * AFNDInsertaEstado(AFND * p_afnd, char * nombre, int tipo){
  /*Esta funcion tambien es miaaa, la hago en otro momentoo que ahora me da pere. Fdo: Luis*/
}

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

AFND * AFNDInsertaLetra(AFND * p_afnd, char * letra){
  if(!p_afnd || !letra)
    return NULL;
  /*Insertamos el símbolo en la palabra, comprobando que no es NULL la salida*/
  if(!palabra_insertar_simbolo(p_afnd->cadena_actual, letra))
    return NULL;

  return p_afnd;
}
void AFNDImprimeConjuntoEstadosActual(FILE * fd, AFND * p_afnd);
void AFNDImprimeCadenaActual(FILE *fd, AFND * p_afnd){
  /*REcuerda que hay funcion para imprimir palabra*/
}
AFND * AFNDInicializaEstado (AFND * p_afnd);
void AFNDProcesaEntrada(FILE * fd, AFND * p_afnd);
void AFNDTransita(AFND * p_afnd);
