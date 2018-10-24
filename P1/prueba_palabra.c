

#include "palabra.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
        palabra * pal;
        int i;
        char letra [20];

        pal = crear_palabra();

        for (i=0; i < argc-1; i++)
        {
                sprintf(letra,"l_%d_%s",i,argv[1+i]);
                palabra_insertar_simbolo(pal,letra);
                fprintf(stdout,"pal_%d:\n",i);
                palabra_imprimir(stdout,pal);
                fprintf(stdout,"\n");
        }

        eliminar_palabra(pal);

        return 0;
}
