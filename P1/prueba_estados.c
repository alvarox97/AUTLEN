#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estado.h"

int posEstado (estado ** estados, char * nombre, int max)
{
    int i;

    for (i=0; i < max; i++)
    {
        if ( estado_es(estados[i], nombre) )
        {
            return i;
        }
    }
    return -1;
}

int main (int argc, char ** argv)
{
    estado * estados [10];
    int i;
    char nombre_estado[20];


    for (i=0; i< 10; i++)
    {

        sprintf(nombre_estado,"s_%d",i);
        switch ( i % 4 )
        {
            case 0:
                estados[i] =
                               crear_estado(nombre_estado,INICIAL_Y_FINAL);
                break;
            case 1:
                estados[i] = crear_estado(nombre_estado,INICIAL);
                break;
            case 2:
                estados[i] = crear_estado(nombre_estado,FINAL);
                break;
            case 3:
                estados[i] = crear_estado(nombre_estado,NORMAL);
                break;


        }
    }

    fprintf(stdout,"El estado %s está en la posicion %d\n", argv[1], posEstado(estados, argv[1], 10 ) );


    for (i=0; i< 10; i++)
    {
        fprintf(stdout,"El tipo del estado %s es %d\n", estado_nombre(estados[i]),estado_tipo(estados[i]));
    }

    for (i=0; i< 10; i++)
    {
        estado_imprimir(stdout,estados[i]);
    }


    for (i=0; i< 10; i++)
    {
               eliminar_estado(estados[i]);
    }

    return 0;


}
