#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "alfabeto.h"
#include "estado.h"
#include "afnd.h"
#include "palabra.h"


int main(int argc, char ** argv)
{

        AFND * p_afnd_l0;
        AFND * p_afnd_l1;
        AFND * p_afnd_l2;
        AFND * p_afnd_l3;
        AFND * p_afnd_l4;
        AFND * p_afnd_l5;
        AFND * p_afnd_l6;
        AFND * p_afndExp1;
        AFND * p_afndExp2_aux;
        AFND * p_afndExp2;
        AFND * p_afndExp3_aux;
        AFND * p_afndExp3;
        AFND * p_afndExp4_aux1;
        AFND * p_afndExp4_aux2;
        AFND * p_afndExp4;

/* SE CREA UN AUTÓMATA FINITO PARA LA EXPRESION REGULAR “1” */
        p_afnd_l1 = AFND1ODeSimbolo("1");
/* SE CREA UN AUTÓMATA FINITO PARA LA EXPRESION REGULAR “0” */
        p_afnd_l0 = AFND1ODeSimbolo("0");
/* SE CREA UN AUTÓMATA FINITO PARA LA EXPRESION REGULAR “1”.”1” */
        p_afnd_l2 = AFND1OConcatena(p_afnd_l1, p_afnd_l1);
/* SE CREA UN AUTÓMATA FINITO PARA LA EXPRESION REGULAR “0”+“1” */
        p_afnd_l4 = AFND1OUne(p_afnd_l0, p_afnd_l1);
/* SE CREA UN AUTÓMATA FINITO PARA LA EXPRESIÓN ( “0”+”1” ) */
        p_afnd_l5 = AFND1OEstrella(p_afnd_l4);
/* SE CREA UN AUTÓMATA FINITO PARA LA EXPRESIÓN “1”.”1”.( “0”+”1” )*/
        p_afnd_l3 = AFND1OConcatena(p_afnd_l2, p_afnd_l5);


/* SE CREA UN AUTÓMATA FINITO PARA LA EXPRESIÓN "1" */
        p_afnd_l6 = AFND1OEstrella(p_afnd_l1);



/****** AUTOMATAS FINITOS DE LA CORRECCION **********/

  p_afndExp1 = AFND1OConcatena(p_afnd_l1, p_afnd_l0); /* 10 */
  p_afndExp2_aux = AFND1OConcatena(p_afnd_l0, p_afnd_l1); /* 01 */
  p_afndExp2 = AFND1OUne(p_afndExp1, p_afndExp2_aux); /* 10 + 01 */
  p_afndExp3_aux = AFND1OConcatena(p_afnd_l2, p_afnd_l1); /* 111 */
  p_afndExp3 = AFND1OUne(p_afndExp2, p_afndExp3_aux); /* 10 + 01 + 111*/
  p_afndExp4_aux1 = AFND1OConcatena(p_afndExp2_aux, p_afnd_l0); /* 010 */
  p_afndExp4_aux2 = AFND1OEstrella(p_afndExp4_aux1); /* (010)*   */
  p_afndExp4 = AFND1OConcatena(p_afnd_l1, p_afndExp4_aux2); /* 1(010)*  */


/**************************************************/

/*Dot de los afnd*/
      //AFNDADot(p_afnd_l0);
      //AFNDADot(p_afnd_l1);
      //AFNDADot(p_afnd_l2);
      AFNDADot(p_afnd_l3);
      //AFNDADot(p_afnd_l4);
      //AFNDADot(p_afnd_l5);
      //AFNDADot(p_afnd_l6);

/* SE CALCULA EL CIERRE REFLEXIVO-TRANSITIVO DE TODOS LOS AUTÓMATAS */
      p_afnd_l0 = AFNDCierraLTransicion(p_afnd_l0);
      p_afnd_l1 = AFNDCierraLTransicion(p_afnd_l1);
      p_afnd_l2 = AFNDCierraLTransicion(p_afnd_l2);
      p_afnd_l3 = AFNDCierraLTransicion(p_afnd_l3);
      p_afnd_l4 = AFNDCierraLTransicion(p_afnd_l4);
      p_afnd_l5 = AFNDCierraLTransicion(p_afnd_l5);
      p_afnd_l6 = AFNDCierraLTransicion(p_afnd_l6);

      p_afndExp1 = AFNDCierraLTransicion(p_afndExp1);
      p_afndExp2_aux = AFNDCierraLTransicion(p_afndExp2_aux);
      p_afndExp2 = AFNDCierraLTransicion(p_afndExp2);
      p_afndExp3_aux = AFNDCierraLTransicion(p_afndExp3_aux);
      p_afndExp3 = AFNDCierraLTransicion(p_afndExp3);
      p_afndExp4_aux1 = AFNDCierraLTransicion(p_afndExp4_aux1);
      p_afndExp4_aux2 = AFNDCierraLTransicion(p_afndExp4_aux2);
      p_afndExp4 = AFNDCierraLTransicion(p_afndExp4);

      fprintf(stdout,"EXPRESION 1: 10\n");
      AFNDImprime(stdout,p_afndExp1);

      fprintf(stdout,"EXPRESION 2: 10 + 01\n");
      AFNDImprime(stdout,p_afndExp2);

      fprintf(stdout,"EXPRESION 3: 10 + 01 + 111\n");
      AFNDImprime(stdout,p_afndExp3);

      fprintf(stdout,"EXPRESION 4: 1(010)*\n");
      AFNDImprime(stdout,p_afndExp4);

/******************************************************
        fprintf(stdout,"EJEMPLO DE AUTÓMATA DE UNA EXPRESIÓN CORRESPONDIENTE A UN SÍMBOLO: \"1\"\n");
        AFNDImprime(stdout,p_afnd_l1);


        fprintf(stdout,"EJEMPLO DE AUTÓMATA DE UNA EXPRESIÓN CORRESPONDIENTE A LA CONCATENACIÓN DE OTROS DOS, JUSTAMENTE CONCATENA EL ANTERIOR CONSIGO MISMO\n");
        AFNDImprime(stdout,p_afnd_l2);


        fprintf(stdout,"A CONTINUACIÓN SE VA A MOSTRAR LA UNIÓN DE DOS AUTÓMATAS QUE VIENEN DE EXPRESIONES REGULARES, UNO DE ELLOS ES EL CORRESPONDIENTE A LA EXPRESION \"1\" QUE YA SE MOSTRÓ ANTERIORMENTE, EL OTRO ES EL DE LA EXPRESIÓN \"0\" QUE SE MUESTRA A CONTINUACIÓN\n");
        AFNDImprime(stdout,p_afnd_l0);


        fprintf(stdout, "Y ESTA ES SU UNIÓN\n");
        AFNDImprime(stdout,p_afnd_l4);

        fprintf(stdout,"SE MUESTRA EL AUTÓMATA FINITO CORRESPONDIENTE A LA EXPRESION \"1\" * A PARTIR DEL AUTÓMATA ASOCIADO CON \"1\" QUE YA SE MOSTRÓ ANTERIORMENTE\n");
        AFNDImprime(stdout,p_afnd_l6);


******************************************************
        fprintf(stdout,"Y, A CONTINUACIÓN, ALGUNOS EJEMPLOS DE PROCESADO DE CADENAS DEL AUTÓMATA DE LA EXPRESIÓN 11(0+1)*\n");
        AFNDImprime(stdout,p_afnd_l3);
        fprintf(stdout,"\tLA CADENA 11 ES RECONOCIDA POR EL AUTOMATA DE 11(0+1)* POR SU PRINCIPIO\n");
        AFNDInsertaLetra(p_afnd_l3,"1");
        AFNDInsertaLetra(p_afnd_l3,"1");
        AFNDImprimeCadenaActual(stdout,p_afnd_l3);
        AFNDInicializaEstado(p_afnd_l3);
        AFNDProcesaEntrada(stdout,p_afnd_l3);
        AFNDInicializaCadenaActual(p_afnd_l3);
        fprintf(stdout,"\tLA CADENA 110 TAMBIÉN ES RECONOCIDA POR EL AUTOMATA DE 11(0+1)* \n");
        AFNDInsertaLetra(p_afnd_l3,"1");
        AFNDInsertaLetra(p_afnd_l3,"1");
        AFNDInsertaLetra(p_afnd_l3,"0");
        AFNDImprimeCadenaActual(stdout,p_afnd_l3);
        AFNDInicializaEstado(p_afnd_l3);
        AFNDProcesaEntrada(stdout,p_afnd_l3);
        AFNDInicializaCadenaActual(p_afnd_l3);
        fprintf(stdout,"\tLA CADENA 111 TAMBIÉN ES RECONOCIDA POR EL AUTOMATA DE 11(0+1)* \n");
        AFNDInsertaLetra(p_afnd_l3,"1");
        AFNDInsertaLetra(p_afnd_l3,"1");
        AFNDInsertaLetra(p_afnd_l3,"1");
        AFNDImprimeCadenaActual(stdout,p_afnd_l3);
        AFNDInicializaEstado(p_afnd_l3);
        AFNDProcesaEntrada(stdout,p_afnd_l3);
        AFNDInicializaCadenaActual(p_afnd_l3);
        fprintf(stdout,"\tLA CADENA 1111001 TAMBIÉN ES RECONOCIDA POR EL AUTOMATA DE 11(0+1)* \n");
        AFNDInsertaLetra(p_afnd_l3,"1");
        AFNDInsertaLetra(p_afnd_l3,"1");
        AFNDInsertaLetra(p_afnd_l3,"1");
        AFNDInsertaLetra(p_afnd_l3,"1");
        AFNDInsertaLetra(p_afnd_l3,"0");
        AFNDInsertaLetra(p_afnd_l3,"0");
        AFNDInsertaLetra(p_afnd_l3,"1");
        AFNDImprimeCadenaActual(stdout,p_afnd_l3);
        AFNDInicializaEstado(p_afnd_l3);
        AFNDProcesaEntrada(stdout,p_afnd_l3);
        AFNDInicializaCadenaActual(p_afnd_l3);
        fprintf(stdout,"\tLA CADENA VACIA SIN EMBARGO NO ES RECONOCIDA POR EL AUTOMATA DE 11(0+1)* \n");
        AFNDImprimeCadenaActual(stdout,p_afnd_l3);
        AFNDInicializaEstado(p_afnd_l3);
        AFNDProcesaEntrada(stdout,p_afnd_l3);
        AFNDInicializaCadenaActual(p_afnd_l3);

        fprintf(stdout,"\tLA CADENA 10 NO ES RECONOCIDA POR EL AUTOMATA DE 11(0+1)* POR SU PRINCIPIO\n");
        AFNDInsertaLetra(p_afnd_l3,"1");
        AFNDInsertaLetra(p_afnd_l3,"0");
        AFNDImprimeCadenaActual(stdout,p_afnd_l3);
        AFNDInicializaEstado(p_afnd_l3);
        AFNDProcesaEntrada(stdout,p_afnd_l3);
        AFNDInicializaCadenaActual(p_afnd_l3);

********************************************************/


        fprintf(stdout,"\tLA CADENA 10 ES RECONOCIDA POR EL AUTOMATA DE 10 POR SU PRINCIPIO\n");
        AFNDInsertaLetra(p_afndExp1,"1");
        AFNDInsertaLetra(p_afndExp1,"0");
        AFNDImprimeCadenaActual(stdout,p_afndExp1);
        AFNDInicializaEstado(p_afndExp1);
        AFNDProcesaEntrada(stdout,p_afndExp1);
        AFNDInicializaCadenaActual(p_afndExp1);

        fprintf(stdout,"\tLA CADENA 01 NO ES RECONOCIDA POR EL AUTOMATA DE 10 POR SU PRINCIPIO\n");
        AFNDInsertaLetra(p_afndExp1,"0");
        AFNDInsertaLetra(p_afndExp1,"1");
        AFNDImprimeCadenaActual(stdout,p_afndExp1);
        AFNDInicializaEstado(p_afndExp1);
        AFNDProcesaEntrada(stdout,p_afndExp1);
        AFNDInicializaCadenaActual(p_afndExp1);

        fprintf(stdout,"\tLA CADENA 00 NO ES RECONOCIDA POR EL AUTOMATA DE 10 POR SU PRINCIPIO\n");
        AFNDInsertaLetra(p_afndExp1,"0");
        AFNDInsertaLetra(p_afndExp1,"0");
        AFNDImprimeCadenaActual(stdout,p_afndExp1);
        AFNDInicializaEstado(p_afndExp1);
        AFNDProcesaEntrada(stdout,p_afndExp1);
        AFNDInicializaCadenaActual(p_afndExp1);


        fprintf(stdout,"\tLA CADENA 11 NO ES RECONOCIDA POR EL AUTOMATA DE 10\n");
        AFNDInsertaLetra(p_afndExp1,"1");
        AFNDInsertaLetra(p_afndExp1,"1");
        AFNDImprimeCadenaActual(stdout,p_afndExp1);
        AFNDInicializaEstado(p_afndExp1);
        AFNDProcesaEntrada(stdout,p_afndExp1);
        AFNDInicializaCadenaActual(p_afndExp1);

        fprintf(stdout,"\tLA CADENA 10 ES RECONOCIDA POR EL AUTOMATA DE 10 + 01\n");
        AFNDInsertaLetra(p_afndExp2,"1");
        AFNDInsertaLetra(p_afndExp2,"0");
        AFNDImprimeCadenaActual(stdout,p_afndExp2);
        AFNDInicializaEstado(p_afndExp2);
        AFNDProcesaEntrada(stdout,p_afndExp2);
        AFNDInicializaCadenaActual(p_afndExp2);

        fprintf(stdout,"\tLA CADENA 01 ES RECONOCIDA POR EL AUTOMATA DE 10 + 01\n");
        AFNDInsertaLetra(p_afndExp2,"0");
        AFNDInsertaLetra(p_afndExp2,"1");
        AFNDImprimeCadenaActual(stdout,p_afndExp2);
        AFNDInicializaEstado(p_afndExp2);
        AFNDProcesaEntrada(stdout,p_afndExp2);
        AFNDInicializaCadenaActual(p_afndExp2);

        fprintf(stdout,"\tLA CADENA 00 NO ES RECONOCIDA POR EL AUTOMATA DE 10 + 01\n\n");
        AFNDInsertaLetra(p_afndExp2,"0");
        AFNDInsertaLetra(p_afndExp2,"0");
        AFNDImprimeCadenaActual(stdout,p_afndExp2);
        AFNDInicializaEstado(p_afndExp2);
        AFNDProcesaEntrada(stdout,p_afndExp2);
        AFNDInicializaCadenaActual(p_afndExp2);


        fprintf(stdout,"\tLA CADENA 11 NO ES RECONOCIDA POR EL AUTOMATA DE 10 + 01 \n");
        AFNDInsertaLetra(p_afndExp2,"1");
        AFNDInsertaLetra(p_afndExp2,"1");
        AFNDImprimeCadenaActual(stdout,p_afndExp2);
        AFNDInicializaEstado(p_afndExp2);
        AFNDProcesaEntrada(stdout,p_afndExp2);
        AFNDInicializaCadenaActual(p_afndExp2);

        fprintf(stdout,"\tLA CADENA 10 ES RECONOCIDA POR EL AUTOMATA DE 10 + 01 + 111\n");
        AFNDInsertaLetra(p_afndExp3,"1");
        AFNDInsertaLetra(p_afndExp3,"0");
        AFNDImprimeCadenaActual(stdout,p_afndExp3);
        AFNDInicializaEstado(p_afndExp3);
        AFNDProcesaEntrada(stdout,p_afndExp3);
        AFNDInicializaCadenaActual(p_afndExp3);

        fprintf(stdout,"\tLA CADENA 01 ES RECONOCIDA POR EL AUTOMATA DE 10 + 01 + 111\n");
        AFNDInsertaLetra(p_afndExp3,"0");
        AFNDInsertaLetra(p_afndExp3,"1");
        AFNDImprimeCadenaActual(stdout,p_afndExp3);
        AFNDInicializaEstado(p_afndExp3);
        AFNDProcesaEntrada(stdout,p_afndExp3);
        AFNDInicializaCadenaActual(p_afndExp3);

        fprintf(stdout,"\tLA CADENA 00 NO ES RECONOCIDA POR EL AUTOMATA DE 10 + 01 + 111\n");
        AFNDInsertaLetra(p_afndExp3,"0");
        AFNDInsertaLetra(p_afndExp3,"0");
        AFNDImprimeCadenaActual(stdout,p_afndExp3);
        AFNDInicializaEstado(p_afndExp3);
        AFNDProcesaEntrada(stdout,p_afndExp3);
        AFNDInicializaCadenaActual(p_afndExp3);


        fprintf(stdout,"\tLA CADENA 11 NO ES RECONOCIDA POR EL AUTOMATA DE 10 + 01 + 111\n");
        AFNDInsertaLetra(p_afndExp3,"1");
        AFNDInsertaLetra(p_afndExp3,"1");
        AFNDImprimeCadenaActual(stdout,p_afndExp3);
        AFNDInicializaEstado(p_afndExp3);
        AFNDProcesaEntrada(stdout,p_afndExp3);
        AFNDInicializaCadenaActual(p_afndExp3);

        fprintf(stdout,"\tLA CADENA 110 NO ES RECONOCIDA POR EL AUTOMATA DE 10 + 01 + 111\n");
        AFNDInsertaLetra(p_afndExp3,"1");
        AFNDInsertaLetra(p_afndExp3,"1");
        AFNDInsertaLetra(p_afndExp3,"0");
        AFNDImprimeCadenaActual(stdout,p_afndExp3);
        AFNDInicializaEstado(p_afndExp3);
        AFNDProcesaEntrada(stdout,p_afndExp3);
        AFNDInicializaCadenaActual(p_afndExp3);

        fprintf(stdout,"\tLA CADENA 111 ES RECONOCIDA POR EL AUTOMATA DE 10 + 01 + 111\n");
        AFNDInsertaLetra(p_afndExp3,"1");
        AFNDInsertaLetra(p_afndExp3,"1");
        AFNDInsertaLetra(p_afndExp3,"1");
        AFNDImprimeCadenaActual(stdout,p_afndExp3);
        AFNDInicializaEstado(p_afndExp3);
        AFNDProcesaEntrada(stdout,p_afndExp3);
        AFNDInicializaCadenaActual(p_afndExp3);

        fprintf(stdout,"\tLA CADENA 1 ES RECONOCIDA POR EL AUTOMATA DE 1(010)*\n");
        AFNDInsertaLetra(p_afndExp4,"1");
        AFNDImprimeCadenaActual(stdout,p_afndExp4);
        AFNDInicializaEstado(p_afndExp4);
        AFNDProcesaEntrada(stdout,p_afndExp4);
        AFNDInicializaCadenaActual(p_afndExp4);

        fprintf(stdout,"\tLA CADENA 0 NO ES RECONOCIDA POR EL AUTOMATA DE 1(010)*\n");
        AFNDInsertaLetra(p_afndExp4,"0");
        AFNDImprimeCadenaActual(stdout,p_afndExp4);
        AFNDInicializaEstado(p_afndExp4);
        AFNDProcesaEntrada(stdout,p_afndExp4);
        AFNDInicializaCadenaActual(p_afndExp4);

        fprintf(stdout,"\tLA CADENA 0010 NO ES RECONOCIDA POR EL AUTOMATA DE 1(010)*\n");
        AFNDInsertaLetra(p_afndExp4,"0");
        AFNDInsertaLetra(p_afndExp4,"0");
        AFNDInsertaLetra(p_afndExp4,"1");
        AFNDInsertaLetra(p_afndExp4,"0");
        AFNDImprimeCadenaActual(stdout,p_afndExp4);
        AFNDInicializaEstado(p_afndExp4);
        AFNDProcesaEntrada(stdout,p_afndExp4);
        AFNDInicializaCadenaActual(p_afndExp4);


        fprintf(stdout,"\tLA CADENA 1010 ES RECONOCIDA POR EL AUTOMATA DE 1(010)*\n");
        AFNDInsertaLetra(p_afndExp4,"1");
        AFNDInsertaLetra(p_afndExp4,"0");
        AFNDInsertaLetra(p_afndExp4,"1");
        AFNDInsertaLetra(p_afndExp4,"0");
        AFNDImprimeCadenaActual(stdout,p_afndExp4);
        AFNDInicializaEstado(p_afndExp4);
        AFNDProcesaEntrada(stdout,p_afndExp4);
        AFNDInicializaCadenaActual(p_afndExp4);

        fprintf(stdout,"\tLA CADENA 1011 NO ES RECONOCIDA POR EL AUTOMATA DE 1(010)*\n");
        AFNDInsertaLetra(p_afndExp4,"1");
        AFNDInsertaLetra(p_afndExp4,"0");
        AFNDInsertaLetra(p_afndExp4,"1");
        AFNDInsertaLetra(p_afndExp4,"1");
        AFNDImprimeCadenaActual(stdout,p_afndExp4);
        AFNDInicializaEstado(p_afndExp4);
        AFNDProcesaEntrada(stdout,p_afndExp4);
        AFNDInicializaCadenaActual(p_afndExp4);

        fprintf(stdout,"\tLA CADENA 1010010 ES RECONOCIDA POR EL AUTOMATA DE 1(010)*\n");
        AFNDInsertaLetra(p_afndExp4,"1");
        AFNDInsertaLetra(p_afndExp4,"0");
        AFNDInsertaLetra(p_afndExp4,"1");
        AFNDInsertaLetra(p_afndExp4,"0");
        AFNDInsertaLetra(p_afndExp4,"0");
        AFNDInsertaLetra(p_afndExp4,"1");
        AFNDInsertaLetra(p_afndExp4,"0");
        AFNDImprimeCadenaActual(stdout,p_afndExp4);
        AFNDInicializaEstado(p_afndExp4);
        AFNDProcesaEntrada(stdout,p_afndExp4);
        AFNDInicializaCadenaActual(p_afndExp4);

        fprintf(stdout,"\tLA CADENA 1010011 NO ES RECONOCIDA POR EL AUTOMATA DE 1(010)*\n");
        AFNDInsertaLetra(p_afndExp4,"1");
        AFNDInsertaLetra(p_afndExp4,"0");
        AFNDInsertaLetra(p_afndExp4,"1");
        AFNDInsertaLetra(p_afndExp4,"0");
        AFNDInsertaLetra(p_afndExp4,"0");
        AFNDInsertaLetra(p_afndExp4,"1");
        AFNDInsertaLetra(p_afndExp4,"1");
        AFNDImprimeCadenaActual(stdout,p_afndExp4);
        AFNDInicializaEstado(p_afndExp4);
        AFNDProcesaEntrada(stdout,p_afndExp4);
        AFNDInicializaCadenaActual(p_afndExp4);






        AFNDElimina(p_afnd_l0);
        AFNDElimina(p_afnd_l1);
        AFNDElimina(p_afnd_l2);
        AFNDElimina(p_afnd_l3);
        AFNDElimina(p_afnd_l4);
        AFNDElimina(p_afnd_l5);
        AFNDElimina(p_afnd_l6);
        AFNDElimina(p_afndExp1);
        AFNDElimina(p_afndExp2_aux);
        AFNDElimina(p_afndExp2);
        AFNDElimina(p_afndExp3_aux);
        AFNDElimina(p_afndExp3);
        AFNDElimina(p_afndExp4_aux1);
        AFNDElimina(p_afndExp4_aux2);
        AFNDElimina(p_afndExp4);

/********************************************************************************/
/********************************************************************************/
        return 0;

}
