#ifndef FILA_H
#define FILA_H

#include "avl.h"

//implementacao de uma fila atraves de uma lista duplamente encadeada

struct nodoL
{
    struct nodo* nodo;
    struct nodoL *prox;
    struct nodoL *ant;
};

typedef struct
{
    struct nodoL *cabeca;
    struct nodoL *cauda;
} lista;

lista *criaLista();

//inserção feita cauda
void enfilera(lista *l, struct nodo *novo);

//remocao feita na cabeca
struct nodoL *desenfilera(lista *l);

void destroiLista(lista *l);

int ehVazia(lista *l);

#endif
