#include<stdio.h>
#include <stdlib.h>
#include<time.h>
#include "fila.h"




int ehVazia(lista *l)
{
    return l->cabeca == NULL;
}

lista *criaLista()
{
    lista *l = malloc(sizeof(lista));
    if(l == NULL) return NULL;
    l->cabeca = NULL;
    l->cauda = NULL;
    return l;
}

struct nodoL *criaNodoL(struct nodo* nodo)
{
    struct nodoL *novo = malloc(sizeof(struct nodoL));
    if (novo == NULL) return NULL;
    novo->nodo = nodo;
    novo->ant = NULL;
    novo->prox = NULL;
    return novo;
}

//A inserção feita na cauda
void enfilera(lista *l, struct nodo *nodo)
{
    struct nodoL* novo = criaNodoL(nodo);
    if (ehVazia(l)) 
    {
        l->cabeca = novo;
        l->cauda = novo;
        return;
    }

    l->cauda->prox = novo;
    novo->ant = l->cauda;
    l->cauda = novo;
    novo->prox = NULL;
}


//remocao na cabeca
struct nodoL *desenfilera(lista *l)
{
    if (ehVazia(l)) return NULL; //lista ja esta vazia

    struct nodoL *removido = l->cabeca;
    if (removido->prox == NULL) //lista so tem um elemento
    {
        l->cabeca = NULL;
        l->cauda = NULL;
        removido->prox = NULL;
        removido->ant = NULL;
        return removido;
    }

    l->cabeca = removido->prox;
    removido->prox = NULL;
    removido->ant = NULL;
    return removido;
}

void destroiLista(lista *l)
{
    struct nodoL *aux;
    while(l->cabeca != NULL)
    {
        aux = desenfilera(l);
        free(aux);
    }
    free(l);
}

