/* Óscar Pinto y Luis Cárabe. Pareja 2, grupo 1401*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "afnd.h"

/* ESTOS INCLUDES DEPENDEN DE LA IMPLEMENTACIÓN, TAL VEZ TÚ DISEÑES OTROS MÓDULOS */
#include "alfabeto.h"
#include "estado.h"
#include "palabra.h"


int main(int argc, char ** argv)
{

/* DECLARACIÓN DE UN PUNTERO A UN AFND */
    AFND * p_afnd;


/* INICIALIZACIÓN DE UN NUEVO AFND DE NOMBRE af1 Y CON 3 ESTADOS Y 2 SÍMBOLOS EN SU ALFABETO */
    p_afnd = AFNDNuevo("af1",2,2);


/* DEFINICIÓN DEL ALFABETO DEL AFND */
    AFNDInsertaSimbolo(p_afnd,"a");
    AFNDInsertaSimbolo(p_afnd,"b");

/* DEFINICIÓN DEL CONJUNTO DE ESTADOS */
    AFNDInsertaEstado(p_afnd,"q0",INICIAL_Y_FINAL);
    AFNDInsertaEstado(p_afnd,"q1",FINAL);

/* DEFINICIÓN DE LAS TRANSICIONES NO LAMBDA */
    AFNDInsertaTransicion(p_afnd, "q0", "a", "q1");
    AFNDInsertaTransicion(p_afnd, "q1", "b", "q0");
    AFNDInsertaTransicion(p_afnd, "q1", "a", "q0");

/* SE MUESTRA EL AFND DEFINIDO */
    fprintf(stdout,"\n****************** AFND *********************\n");
    AFNDImprime(stdout,p_afnd);
    fprintf(stdout,"\n*********************************************\n");

/*--------------------CASO 1: ENTRADA NORMAL, FINALIZA CORRECTAMENTE----------------*/
/* DEFINICIÓN DE LA CADENA DE ENTRADA [ a b a b a ] */
    p_afnd= AFNDInsertaLetra(p_afnd,"a");
    p_afnd= AFNDInsertaLetra(p_afnd,"b");
    p_afnd= AFNDInsertaLetra(p_afnd,"a");
    p_afnd= AFNDInsertaLetra(p_afnd,"b");
    p_afnd= AFNDInsertaLetra(p_afnd,"a");

/* SE ESTABLECE COMO ESTADO ACTUAL DEL AUTÓMATA EL INICIAL */

    AFNDInicializaEstado (p_afnd);

/* SE MUESTRA LA CADENA ACTUAL */

    fprintf(stdout,"\n**************** PROCESA CADENA *************\n");
    AFNDImprimeCadenaActual(stdout,p_afnd);
    fprintf(stdout,"\n*********************************************\n");

/* SE PROCESA LA CADENA DE ENTRADA ACTUAL MOSTRANDO UNA TRAZA DEL FUNCIONAMIENTO DEL AUTOMATA: EN CADA PASO DE ANÁLISIS SE MUESTRA LA CADENA ACTUAL Y EL CONJUNTO DE ESTADOS EN LOS QUE SE ENCUENTRA EL AUTÓMATA */

    AFNDProcesaEntrada(stdout,p_afnd);

/*--------------------CASO 2: INSERTA UNA LETRA FUERA DEL ALFABETO (continúa ejecución)----------------*/
/* DEFINICIÓN DE LA CADENA DE ENTRADA [ a b a b z ] */
    p_afnd= AFNDInsertaLetra(p_afnd,"a");
    p_afnd= AFNDInsertaLetra(p_afnd,"b");
    p_afnd= AFNDInsertaLetra(p_afnd,"a");
    p_afnd= AFNDInsertaLetra(p_afnd,"b");
    p_afnd= AFNDInsertaLetra(p_afnd,"z");

/* SE ESTABLECE COMO ESTADO ACTUAL DEL AUTÓMATA EL INICIAL */

    AFNDInicializaEstado (p_afnd);

/* SE MUESTRA LA CADENA ACTUAL */

    fprintf(stdout,"\n**************** PROCESA CADENA *************\n");
    AFNDImprimeCadenaActual(stdout,p_afnd);
    fprintf(stdout,"\n*********************************************\n");


/* SE PROCESA LA CADENA DE ENTRADA ACTUAL MOSTRANDO UNA TRAZA DEL FUNCIONAMIENTO DEL AUTOMATA: EN CADA PASO DE ANÁLISIS SE MUESTRA LA CADENA ACTUAL Y EL CONJUNTO DE ESTADOS EN LOS QUE SE ENCUENTRA EL AUTÓMATA */

    AFNDProcesaEntrada(stdout,p_afnd);

/*--------------------CASO 3: TERMINA EN ESTADO SUMIDERO (cadena no vacía)----------------*/
/* DEFINICIÓN DE LA CADENA DE ENTRADA [ a b a b b ] */
    p_afnd= AFNDInsertaLetra(p_afnd,"a");
    p_afnd= AFNDInsertaLetra(p_afnd,"b");
    p_afnd= AFNDInsertaLetra(p_afnd,"a");
    p_afnd= AFNDInsertaLetra(p_afnd,"b");
    p_afnd= AFNDInsertaLetra(p_afnd,"b");

/* SE ESTABLECE COMO ESTADO ACTUAL DEL AUTÓMATA EL INICIAL */

    AFNDInicializaEstado (p_afnd);

/* SE MUESTRA LA CADENA ACTUAL */

    fprintf(stdout,"\n**************** PROCESA CADENA *************\n");
    AFNDImprimeCadenaActual(stdout,p_afnd);
    fprintf(stdout,"\n*********************************************\n");


/* SE PROCESA LA CADENA DE ENTRADA ACTUAL MOSTRANDO UNA TRAZA DEL FUNCIONAMIENTO DEL AUTOMATA: EN CADA PASO DE ANÁLISIS SE MUESTRA LA CADENA ACTUAL Y EL CONJUNTO DE ESTADOS EN LOS QUE SE ENCUENTRA EL AUTÓMATA */

    AFNDProcesaEntrada(stdout,p_afnd);


/* SE LIBERAN TODOS LOS RECURSOS ASOCIADOS CON EL AFND */
    AFNDElimina(p_afnd);

    return 0;

}
