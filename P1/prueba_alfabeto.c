#include "alfabeto.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>


int main(int argc, char ** argv)
{
    alfabeto * binario;


    binario = crear_alfabeto("0_1",2);

    alfabeto_insertar_simbolo(binario,"el_0");
    alfabeto_imprimir(stdout, binario);

    alfabeto_insertar_simbolo(binario,"el_1");
    alfabeto_imprimir(stdout, binario);

    alfabeto_insertar_simbolo(binario,"el_bicho");
    alfabeto_imprimir(stdout, binario);

    eliminar_alfabeto(binario);

    return 0;
}
