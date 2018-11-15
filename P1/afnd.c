/* Óscar Pinto y Luis Cárabe. Pareja 2, grupo 1401*/

#include "afnd.h"

typedef struct _transicion{
    char* est_inicial; /*Nombre del estado de partida*/
    char* simbolo_entrante; /*Simbolo que causa la transición*/
    int num_est;/*Número de estados finales*/
    estado** est_final;/*Lista de estados finales*/
}transicion;

typedef struct _AFND {
    char* nombre;
    alfabeto* alfabeto;
    int num_estados;
    int num_simbolos;
    int num_transiciones;
    int num_estados_actuales;
    int num_transiciones_lambda;
    estado** estados;
    palabra* cadena_actual;
    estado** estados_actuales;
    transicion** transiciones;
    transicion** transiciones_lambda;
}AFND;



transicion* crear_transicion(AFND* afnd, char* est_inicial, char* simbolo_entrante, char* est_final){
  transicion* trans = NULL;
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
  if(!trans->simbolo_entrante){
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

  afnd->transiciones = (transicion**)realloc(afnd->transiciones, (afnd->num_transiciones + 1)* sizeof(transicion*));

  /*Comprobamos si ha habido algún error*/
  if(!afnd->transiciones){
    free(trans->simbolo_entrante);
    free(trans->est_inicial);
    free(trans);
    return NULL;
  }
  /*Guardamos la nueva transición en la lista de transciones*/
  afnd->transiciones[afnd->num_transiciones] = trans;
  afnd->num_transiciones++;

  return trans;
}

transicion* crear_transicion_lambda(AFND* afnd, char* est_inicial, char* simbolo_entrante, char* est_final){
  transicion* trans = NULL;
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
  if(!trans->simbolo_entrante){
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

  afnd->transiciones_lambda = (transicion**)realloc(afnd->transiciones_lambda, (afnd->num_transiciones_lambda + 1)* sizeof(transicion*));

  /*Comprobamos si ha habido algún error*/
  if(!afnd->transiciones_lambda){
    free(trans->simbolo_entrante);
    free(trans->est_inicial);
    free(trans);
    return NULL;
  }
  /*Guardamos la nueva transición en la lista de transciones*/
  afnd->transiciones_lambda[afnd->num_transiciones_lambda] = trans;
  afnd->num_transiciones_lambda++;

  return trans;
}

void eliminar_transicion(transicion* trans){
  if(!trans)
    return;
  /*Liberamos todos los recursos (sin liberar cada estado final, ya que apuntan a los estados del afnd)*/
  free(trans->est_inicial);
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
    fprintf(fd, "%s ", estado_nombre(trans->est_final[i]));
  }
  fprintf(fd, "}\n");
}

AFND* AFNDNuevo(char* nombre, int num_estados, int num_simbolos){
  AFND* afnd = NULL;
  int i = 0;

  /*Comprobamos que los argumentos sean válidos*/
  if(!nombre || num_estados < 0 || num_simbolos < 0 )
    return NULL;

  /*Reservamos memoria para el afnd*/
  afnd = (AFND*)malloc(sizeof(AFND));
  if(!afnd)
    return NULL;

  /*Reservamos memoria para su nombre y lo copiamos*/
  afnd->nombre = (char*)malloc((strlen(nombre)+1)*sizeof(char));
  if(!afnd->nombre){
    free(afnd);
    return NULL;
  }
  strcpy(afnd->nombre, nombre);

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
  /*Inicializamos a NULL*/
  for(i=0; i<num_estados; i++){
    afnd->estados[i] = NULL;
  }
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
  afnd->num_estados_actuales = 0;
  afnd->estados_actuales = (estado**)malloc(sizeof(estado*));
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
    free(afnd->estados_actuales);
    eliminar_palabra(afnd->cadena_actual);
    free(afnd->estados);
    eliminar_alfabeto(afnd->alfabeto);
    free(afnd->nombre);
    free(afnd);
    return NULL;
  }

  /*Reservamos transiciones */
  afnd->num_transiciones_lambda = 0;
  afnd->transiciones_lambda = (transicion **) malloc(sizeof(transicion*));
  if(!afnd->transiciones_lambda){
    free(afnd->estados_actuales);
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
  free(p_afnd->estados);
  eliminar_palabra(p_afnd->cadena_actual);

  /*Los estados actuales son referencias a la lista de estados, por tanto no los eliminamos*/

  free(p_afnd->estados_actuales);

  for(i=0 ; i < p_afnd->num_transiciones ; i++){
    eliminar_transicion(p_afnd->transiciones[i]);
  }

  for(i=0 ; i < p_afnd->num_transiciones_lambda ; i++){
    eliminar_transicion(p_afnd->transiciones_lambda[i]);
  }
  free(p_afnd->transiciones);
  free(p_afnd->transiciones_lambda);
  free(p_afnd);
}

void ImprimeMatrizL(FILE * fd, AFND* p_afnd){
  int i,j,k,flag = 0;
  transicion* translambda = NULL;

  /* Comprobamos los argumentos de entrada*/
  if(!fd || !p_afnd)
      return;
  /* Empezamos a imprimir la matriz*/
  fprintf(fd, "\tRL++*={\n\t\t");

  /*Imprimimos la primera fila, que serán los números de todos los estados*/
  for (i = 0 ; i < p_afnd->num_estados ; i++) {
    fprintf(fd, "\t[%d]", i);
  }
  /*Por cada estado, imprimos su fila*/
  for(i = 0 ; i < p_afnd->num_estados ; i++){
    fprintf(fd, "\n\t\t[%d]", i);

    /* Buscamos la transición lambda del estado que estemos analizando*/
    for(k = 0 ; k < p_afnd->num_transiciones_lambda ; k++){
      if(strcmp(p_afnd->transiciones_lambda[k]->est_inicial, estado_nombre(p_afnd->estados[i])) == 0){
        translambda = p_afnd->transiciones_lambda[k];
        break;
      }
    }

    /* Rellenamos toda la fila*/
    for(j = 0 ; j < p_afnd->num_estados ; j++){

      /*Si el estado se encuentra entre los estados finales de la transicion que analizamos, cambiamos el flag*/
      for(k = 0 ; k < translambda->num_est ; k++){
        if (strcmp(estado_nombre(translambda->est_final[k]), estado_nombre(p_afnd->estados[j])) == 0) {
          flag = 1;
          break;
        }
      }
      /*Ponemos un 1*/
      if(flag == 1)
        fprintf(fd, "\t1");
      /*En caso contrario ponemos un 0*/
      else
        fprintf(fd, "\t0");
      flag = 0;
    }
  }
  fprintf(fd, "\n");
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
  alfabeto_imprimir(fd, p_afnd->alfabeto);

  /*... el número de estados y la lista de estados...*/
  fprintf(fd, "\n\tnum_estados = %d\n", p_afnd->num_estados);
  fprintf(fd, "\n\tQ={");
  for(i=0; i < p_afnd->num_estados ; i++){
    estado_imprimir(fd, p_afnd->estados[i]);
  }
  fprintf(fd, "}\n");

  /*... y la función de transición*/
  fprintf(fd, "\n\tFunción de Transición = {\n\n");
  for(i=0 ; i < p_afnd->num_transiciones ; i++){
    fprintf(fd, "\t\t");
    transicion_imprimir(fd, p_afnd->transiciones[i]);
  }

  /*Imprimimos la matriz de lambdas*/

  ImprimeMatrizL(fd, p_afnd);

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
  estado* est = NULL;
  int i = 0;

  if(!p_afnd || !nombre || tipo < 0 || tipo > 3){
    return NULL;
  }

  if(sizeof(*p_afnd->estados)/sizeof(estado *) >= p_afnd->num_estados){
    /*Estoy asumiendo que el numero de estados pasado al crear es inmutable*/
    return NULL;
  }

  /*Creo el estado apropiado*/
  est = crear_estado(nombre, tipo);
  if(!est){
    return NULL;
  }

  /*Inserto en la primera posicion libre*/
  for(i=0; i<p_afnd->num_estados; i++){
    if(!p_afnd->estados[i]){
      p_afnd->estados[i] = est;
      break;
    }

  }

return p_afnd;
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
      break;
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
      if(estado_es(trn->est_final[i], nombre_estado_f)){
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
  int i=0;
  int flag=0;
  char** simbolos = NULL;
  if(!p_afnd || !letra)
    return NULL;
  /*Comprobamos que la letra esté en el alfabeto*/
  simbolos = alfabeto_get_simbolos(p_afnd->alfabeto);
  for(i=0; i<alfabeto_get_size(p_afnd->alfabeto); i++){
    if(strcmp(simbolos[i], letra) == 0){
      flag = 1;
      break;
    }
  }
  if(flag == 0){
    /*Retornamos el autómata pero sin insertar la letra errónea*/
    fprintf(stderr, "La letra introducida no está en el alfabeto\n");
    return p_afnd;
  }
  /*Insertamos el símbolo en la palabra, comprobando que no es NULL la salida*/
  if(!palabra_insertar_simbolo(p_afnd->cadena_actual, letra))
    return NULL;

  return p_afnd;
}

void AFNDImprimeConjuntoEstadosActual(FILE * fd, AFND * p_afnd){
  estado* est = NULL;
  int i=0;

  if(!fd || !p_afnd){
    return;
  }

  if(p_afnd->estados_actuales == NULL){
    return;
  }

  fprintf(fd, "ACTUALMENTE EN ");
  fprintf(fd, "{");

  for(i=0; i<p_afnd->num_estados_actuales; i++){
    est = p_afnd->estados_actuales[i];
    estado_imprimir(fd, est);
  }

  fprintf(fd, "}\n");
}

void AFNDImprimeCadenaActual(FILE *fd, AFND * p_afnd){
  if(!fd || !p_afnd){
    return;
  }

  palabra_imprimir(fd, p_afnd->cadena_actual);

}

void AFNDTransita(AFND * p_afnd){
  int i=0;
  int j=0;
  int z=0;
  estado* est = NULL;
  transicion* trn = NULL;
  char** simbolos = NULL;
  estado ** new_actual = NULL;
  int index = 0;
  palabra* new_word = NULL;

  if(!p_afnd){
    return;
  }

  /*Compruebo que está definido un estado actual*/
  if(!p_afnd->estados_actuales){
    return;
  }
  if(p_afnd->num_estados_actuales==0){
    return;
  }
  /*Obtengo el simbolo*/
  simbolos = palabra_get_simbolos(p_afnd->cadena_actual);
  if(!simbolos)
    return;

  /*Reservo memoria para los nuevos estados */
  new_actual = (estado **) malloc(sizeof(estado*));
  if(!new_actual)
    return;


  /*Itero sobre los est actuales con el simbolo actual para obtener las trans*/
  for(i=0; i<p_afnd->num_estados_actuales; i++){
    est = p_afnd->estados_actuales[i];
    /*Busco la transicion*/
    for(j=0; j<p_afnd->num_transiciones; j++){
      if((strcmp(p_afnd->transiciones[j]->est_inicial, estado_nombre(est)) == 0)
          && (strcmp(p_afnd->transiciones[j]->simbolo_entrante, simbolos[0]) == 0)){
        trn = p_afnd->transiciones[j];
        break;
      }
    }
    /*Si no encuentra transición, no actualizamos nuevos estados, pero seguimos iterando los estados actuales*/
    if(!trn){
      continue;
    }
    /*Obtengo los nuevos estados*/
    for(j=0; j<trn->num_est; j++){
      if(index >= (sizeof(*new_actual)/sizeof(estado*))){
        new_actual = (estado**) realloc(new_actual, sizeof(estado*)*(index+1));
        if(!new_actual){
          return;
        }
      }
      /*Miramos si el nodo final ya está en la lista*/
      for(z=0 ; z < index ; z++){
        if(strcmp(estado_nombre(trn->est_final[j]),estado_nombre(new_actual[z])) == 0){
          break;
        }
      }
      /*Si no está ya, lo añadimos*/
      if(z == index){
        new_actual[index] = trn->est_final[j];
        index++;
      }

    }
  }

  /*Transito a los nuevos estados*/
  free(p_afnd->estados_actuales);
  /*NOTA: solo se libera el puntero pues los estados son referencias no copias*/
  p_afnd->estados_actuales = new_actual;
  p_afnd->num_estados_actuales = index;

  /*Avanzo un simbolo*/
  new_word = crear_palabra();
  if(!new_word)
    return;

  for(i=1; i<palabra_get_size(p_afnd->cadena_actual); i++){
    palabra_insertar_simbolo(new_word, simbolos[i]);
  }

  eliminar_palabra(p_afnd->cadena_actual);
  p_afnd->cadena_actual = new_word;

}

void AFNDTransitaLambda(AFND * p_afnd){
  int i=0;
  int j=0;
  int z=0;
  estado* est = NULL;
  transicion* trn = NULL;
  estado ** new_actual = NULL;
  int index = 0;

  if(!p_afnd){
    return;
  }

  /*Compruebo que está definido un estado actual*/
  if(!p_afnd->estados_actuales){
    return;
  }
  if(p_afnd->num_estados_actuales==0){
    return;
  }

  /*Reservo memoria para los nuevos estados */
  new_actual = (estado **) malloc(sizeof(estado*));
  if(!new_actual)
    return;


  /*Itero sobre los est actuales para obtener las trans lambda*/
  for(i=0; i<p_afnd->num_estados_actuales; i++){
    est = p_afnd->estados_actuales[i];
    /*Busco la transicion*/
    for(j=0; j<p_afnd->num_transiciones_lambda; j++){
      if(strcmp(p_afnd->transiciones_lambda[j]->est_inicial, estado_nombre(est)) == 0){
        trn = p_afnd->transiciones_lambda[j];
        break;
      }
    }
    /*Si no encuentra es que hay error*/
    if(!trn){
      free(new_actual);
      return;
    }
    /*Obtengo los nuevos estados*/
    for(j=0; j<trn->num_est; j++){
      if(index >= (sizeof(*new_actual)/sizeof(estado*))){
        new_actual = (estado**) realloc(new_actual, sizeof(estado*)*(index+1));
        if(!new_actual){
          return;
        }
      }
      /*Miramos si el nodo final ya está en la lista*/
      for(z=0 ; z < index ; z++){
        if(strcmp(estado_nombre(trn->est_final[j]),estado_nombre(new_actual[z])) == 0){
          break;
        }
      }
      /*Si no está ya, lo añadimos*/
      if(z == index){
        new_actual[index] = trn->est_final[j];
        index++;
      }

    }
  }

  /*Transito a los nuevos estados*/
  free(p_afnd->estados_actuales);
  /*NOTA: solo se libera el puntero pues los estados son referencias no copias*/
  p_afnd->estados_actuales = new_actual;
  p_afnd->num_estados_actuales = index;

  /*No avanzo un simbolo al estar con transiciones lambda*/
}

AFND * AFNDInicializaEstado (AFND * p_afnd){
  int i=0;
  estado* est = NULL;

  if(!p_afnd){
    return NULL;
  }

  p_afnd->num_estados_actuales = 0;

  for(i=0; i<p_afnd->num_estados; i++){
    est = p_afnd->estados[i];
    if(!est){
      return NULL;
    }
    /*Comprobamos si es inicial*/
    if(estado_tipo(est) == 0 || estado_tipo(est) == 2){
      if(sizeof(*p_afnd->estados_actuales)/sizeof(estado *) >= p_afnd->num_estados_actuales){
        p_afnd->estados_actuales = (estado **)realloc(p_afnd->estados_actuales, sizeof(estado*)*(p_afnd->num_estados_actuales + 1));
        if(!p_afnd){
          return NULL;
        }
      }
      p_afnd->estados_actuales[p_afnd->num_estados_actuales] = est;
      p_afnd->num_estados_actuales++;
    }
  }

  /*Realizamos las transciones lambda desde el principio*/

  AFNDTransitaLambda(p_afnd);

  return p_afnd;
}

void AFNDProcesaEntrada(FILE * fd, AFND * p_afnd){
  int i = 0;

  if(!fd || !p_afnd){
    return;
  }

  i = palabra_get_size(p_afnd->cadena_actual);

  while(i>0){
    AFNDImprimeConjuntoEstadosActual(fd, p_afnd);
    AFNDImprimeCadenaActual(fd, p_afnd);
    AFNDTransita(p_afnd);
    AFNDTransitaLambda(p_afnd);
    i--;
    if(p_afnd->num_estados_actuales == 0)
      break;
  }
  AFNDImprimeConjuntoEstadosActual(fd, p_afnd);
  AFNDImprimeCadenaActual(fd, p_afnd);

}

AFND * AFNDInsertaLTransicion(AFND * p_afnd, char * nombre_estado_i, char * nombre_estado_f ){

         int i=0,  flag_i=0, flag_f=0, flag_trn=0, index_f=0;
         transicion* trn = NULL;

         if(!p_afnd || !nombre_estado_i || !nombre_estado_f){
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

         /*Buscamos las transiciones del estado inicial*/
         for(i=0; i<p_afnd->num_transiciones_lambda; i++){
           if(strcmp(p_afnd->transiciones_lambda[i]->est_inicial, nombre_estado_i) == 0){
             trn = p_afnd->transiciones_lambda[i];
             break;
           }
         }

         if(!trn){
           /*Creamos una nueva transicion*/
           trn = crear_transicion_lambda(p_afnd, nombre_estado_i, "lambda", nombre_estado_f);
           if(!trn){
             return NULL;
           }
         }else{
           /*Si ya existe la transicion la modifico si es necesario*/

           for(i=0; i<trn->num_est; i++){
             if(estado_es(trn->est_final[i], nombre_estado_f)){
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
             trn->num_est++;
             flag_trn = 0;
           }

         }

/*Si llega hasta aquí es que sorprendentemente todo está correcto*/

return p_afnd;
}

/*Función recursiva para crear el cierre transitivo de las trans lambda*/
/*Est_inicial_principal es el estado sobre el cual estamos aplicando la transitividad
 y est_incial_trans es el estado inicial de la transición lambda que estamos recorriendo en un momento de la recursividad*/

void cierreTransitivoAux(AFND* p_afnd, char* est_inicial_principal, char* est_inicial_trans, estado** est_trans, int num_est_trans){
  int i,j;
  if(!p_afnd || !est_inicial_principal || !est_inicial_trans || !est_trans || num_est_trans <= 0)
    return;
  /* Primero insertamos los estados por los que estamos pasando en la transicion*/
  for(i = 0; i < num_est_trans; i++){
    /*Nos aseguramos de que no crear un bucle infinito debido a la reflexión (toda estado contiene una transición lambda siendo él el estado final)*/
    if(estado_es(est_trans[i], est_inicial_trans))
      continue;
    AFNDInsertaLTransicion(p_afnd, est_inicial_principal, estado_nombre(est_trans[i]));
    /*Miramos las transiciones lambda de cada estado que estamos transitando actualmente*/
    for(j=0 ; j < p_afnd->num_transiciones_lambda ; j++){
      if(strcmp(p_afnd->transiciones_lambda[j]->est_inicial, estado_nombre(est_trans[i])) == 0){
        cierreTransitivoAux(p_afnd, est_inicial_principal, p_afnd->transiciones_lambda[j]->est_inicial, p_afnd->transiciones_lambda[j]->est_final, p_afnd->transiciones_lambda[j]->num_est);
        break;
      }
    }
  }
}

AFND * AFNDCierraLTransicion (AFND * p_afnd){
  int i=0, j=0;

  if(!p_afnd){
    return NULL;
  }

  /*Busco hacer el cierre refexivo si no existe ya
  for(i=0; i<p_afnd->num_estados; i++){
    flag = 0;
    for(j=0; j<p_afnd->num_transiciones_lambda; j++){
      if(strcmp(p_afnd->transiciones_lambda[j]->est_inicial, estado_nombre(p_afnd->estados[i])) == 0 &&
      estado_es(p_afnd->transiciones_lambda[j]->est_final, estado_nombre(p_afnd->estados[i]))){
      flag = 1;
      break;
      }

    }
    Si no encuentra una transicion reflexiva la inserta
    if(flag == 0){
      trn = AFNDInsertaLTransicion(p_afnd, estado_nombre(p_afnd->estados[i]), estado_nombre(p_afnd->estados[i]));
      if(!trn){
        return NULL;
      }
    }
  }*/

  /*Primero realizamos el cierre reflexivo  (AFNDInsertaLTransicion ya comprueba si existe y que el estado final no esté duplicado)*/

  for (i = 0; i < p_afnd->num_estados ; i++){
    AFNDInsertaLTransicion(p_afnd, estado_nombre(p_afnd->estados[i]), estado_nombre(p_afnd->estados[i]));
  }

  /*Busco hacer el cierre transitivo*/

  for(i = 0; i < p_afnd->num_estados ; i++){
    /*Por cada estado, buscamos sus transiciones lambda y vemos si los estados finales tienen más transiciones lambda*/
    for(j=0; j < p_afnd->num_transiciones_lambda ; j++){
      if(strcmp(p_afnd->transiciones_lambda[j]->est_inicial, estado_nombre(p_afnd->estados[i])) == 0){
        cierreTransitivoAux(p_afnd, estado_nombre(p_afnd->estados[i]), estado_nombre(p_afnd->estados[i]), p_afnd->transiciones_lambda[j]->est_final, p_afnd->transiciones_lambda[j]->num_est);
        break;
      }
    }
  }
  return p_afnd;

  /*Busco sobre estados iniciales*/
}

AFND* AFNDInicializaCadenaActual (AFND* p_afnd){
    /* TODO OJOOOOOOO DICE EL ENUNCIADO QUE ESTA FUNCION YA LA HACIAMOS IMPLICITAMENTE ANTES,
    PERO NO HE BORRADO NADA DEL CODIGO ANTIGUO, SI DA PROBLEMAS DE MEMORIA O DE ALGUN TIPO, ECHARLE UN OJO*/
    if(!p_afnd)
      return NULL;
    eliminar_palabra(p_afnd->cadena_actual);
    p_afnd->cadena_actual = crear_palabra();
    return p_afnd;
}
