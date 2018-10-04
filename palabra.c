#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "palabra.h"
#define TAMHASH 157286

/**
 * Implementacion de hash con una lista enlazada para controlar
 * colisiones
 */
typedef struct _hash_node{
    void* value;
    char* key;
    struct _hash_node* next;
}hash_node;

typedef struct _hash{
    hash_node **data;
    void (*free_value)(void *);
}hash;
