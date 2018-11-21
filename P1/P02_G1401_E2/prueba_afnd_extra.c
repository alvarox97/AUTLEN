#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "alfabeto.h"
#include "estado.h"
#include "afnd.h"
#include "palabra.h"


int main(int argc, char ** argv)
{

    AFND * p_afnd_l;



    p_afnd_l = AFNDNuevo("afl1",5,2);

    AFNDInsertaSimbolo(p_afnd_l,"0");
    AFNDInsertaSimbolo(p_afnd_l,"1");

    AFNDInsertaEstado(p_afnd_l,"q0",INICIAL);
    AFNDInsertaEstado(p_afnd_l,"q1",FINAL);
    AFNDInsertaEstado(p_afnd_l,"q2",NORMAL);
    AFNDInsertaEstado(p_afnd_l,"q3",FINAL);
    AFNDInsertaEstado(p_afnd_l,"q4",NORMAL);


    AFNDInsertaTransicion(p_afnd_l, "q1", "0", "q2");
    AFNDInsertaTransicion(p_afnd_l, "q1", "1", "q1");
    AFNDInsertaTransicion(p_afnd_l, "q2", "1", "q2");
    AFNDInsertaTransicion(p_afnd_l, "q2", "0", "q1");
    AFNDInsertaTransicion(p_afnd_l, "q3", "1", "q4");
    AFNDInsertaTransicion(p_afnd_l, "q3", "0", "q3");
    AFNDInsertaTransicion(p_afnd_l, "q4", "0", "q4");
    AFNDInsertaTransicion(p_afnd_l, "q4", "1", "q3");

    AFNDInsertaLTransicion(p_afnd_l, "q0", "q1");
    AFNDInsertaLTransicion(p_afnd_l, "q0", "q3");

    AFNDCierraLTransicion(p_afnd_l);

    AFNDImprime(stdout,p_afnd_l);

    AFNDInsertaLetra(p_afnd_l,"1");
    AFNDInsertaLetra(p_afnd_l,"1");
    AFNDInsertaLetra(p_afnd_l,"1");
    AFNDInsertaLetra(p_afnd_l,"1");
    AFNDInsertaLetra(p_afnd_l,"0");
    AFNDInsertaLetra(p_afnd_l,"0");
    AFNDInsertaLetra(p_afnd_l,"0");


    p_afnd_l = AFNDInicializaEstado(p_afnd_l);

    fprintf(stdout,"\n**************** PROCESA CADENA *************\n");
    AFNDImprimeCadenaActual(stdout,p_afnd_l);
    fprintf(stdout,"\n*********************************************\n");

    AFNDProcesaEntrada(stdout,p_afnd_l);

/*********************************************************************************/

    p_afnd_l = AFNDInicializaCadenaActual(p_afnd_l);
    AFNDInsertaLetra(p_afnd_l,"1");
    AFNDInsertaLetra(p_afnd_l,"0");
    AFNDInsertaLetra(p_afnd_l,"0");
    AFNDInsertaLetra(p_afnd_l,"0");
    AFNDInsertaLetra(p_afnd_l,"0");
    AFNDInsertaLetra(p_afnd_l,"0");

    p_afnd_l = AFNDInicializaEstado(p_afnd_l);

    fprintf(stdout,"\n**************** PROCESA CADENA *************\n");
    AFNDProcesaEntrada(stdout,p_afnd_l);
    fprintf(stdout,"\n*********************************************\n");


/*********************************************************************************/

    p_afnd_l = AFNDInicializaCadenaActual(p_afnd_l);
    AFNDInsertaLetra(p_afnd_l,"1");
    AFNDInsertaLetra(p_afnd_l,"1");
    AFNDInsertaLetra(p_afnd_l,"1");
    AFNDInsertaLetra(p_afnd_l,"0");
    AFNDInsertaLetra(p_afnd_l,"0");

    p_afnd_l = AFNDInicializaEstado(p_afnd_l);

    fprintf(stdout,"\n**************** PROCESA CADENA *************\n");
    AFNDProcesaEntrada(stdout,p_afnd_l);
    fprintf(stdout,"\n*********************************************\n");


/*********************************************************************************/

    p_afnd_l = AFNDInicializaCadenaActual(p_afnd_l);
    AFNDInsertaLetra(p_afnd_l,"0");
    AFNDInsertaLetra(p_afnd_l,"1");
    AFNDInsertaLetra(p_afnd_l,"0");
    AFNDInsertaLetra(p_afnd_l,"1");
    AFNDInsertaLetra(p_afnd_l,"0");
    AFNDInsertaLetra(p_afnd_l,"1");
    AFNDInsertaLetra(p_afnd_l,"0");
    AFNDInsertaLetra(p_afnd_l,"1");

    p_afnd_l = AFNDInicializaEstado(p_afnd_l);

    fprintf(stdout,"\n**************** PROCESA CADENA *************\n");
    AFNDProcesaEntrada(stdout,p_afnd_l);
    fprintf(stdout,"\n*********************************************\n");


/*********************************************************************************/





    AFNDElimina(p_afnd_l);

/********************************************************************************/


    return 0;

}
