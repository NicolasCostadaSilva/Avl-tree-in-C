#include "avl.h"
#include "fila.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//substitua por seus dados
struct aluno* getAluno1(){
    struct aluno* retorno = malloc(sizeof(struct aluno));
    if(!retorno)
        exit(1);
    retorno->nome = malloc(sizeof("Rafael Munhoz da Cunha Marques"));//sizeof conta o \0
	if(!retorno->nome)
		exit(1);
    retorno->nomeDinf = malloc(sizeof("rmcm22"));
    if(!retorno->nomeDinf)
        exit(1);
    
	strcpy(retorno->nome, "Rafael Munhoz da Cunha Marques");
    strcpy(retorno->nomeDinf, "rmcm22");
    retorno->grr = 20224385;

	return retorno;
}

struct aluno* getAluno2(){
    return NULL;
}

void imprimirDadosAlunos(){
    struct aluno* aluno = getAluno1();
    
    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);

    aluno = getAluno2();
    if(!aluno)
        return;
    
    printf("...E... \n\n");
    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);
}

//retorna novo nodo com chave passada
struct nodo* criaNodo(int chave)
{
    struct nodo* novo = malloc(sizeof(struct nodo));
    if (!novo) 
        exit(1);
    novo->chave = chave;
    novo->pai = NULL;
    novo->fe = NULL;
    novo->fd = NULL;
    novo->h = 1;
    return novo;
}


void consertaAltura(struct nodo* nodo)
{
    if ((nodo->fd == NULL) && (nodo->fe == NULL)) nodo->h = 1;
    else if ((nodo->fd != NULL) ^ (nodo->fe != NULL))
    {
        if (nodo->fd != NULL) nodo->h = nodo->fd->h + 1;
        else nodo->h = nodo->fe->h + 1;
    }
    else if (nodo->fd->h > nodo->fe->h) nodo->h = nodo->fd->h + 1;
    else nodo->h = nodo->fe->h + 1;
}

struct nodo* inserir(struct nodo** raiz, int chave){
    struct nodo* novo = criaNodo(chave);

	if (*raiz == NULL)
    {
        *raiz = novo;
        return novo;
    }

    struct nodo* atual = *raiz;
    struct nodo* pai = NULL;
    while (atual != NULL)
    {
        pai = atual;
        if (chave > atual->chave) atual = atual->fd;
        else atual = atual->fe;
    }
    novo->pai = pai;
    if (novo->chave > pai->chave) pai->fd = novo;
    else pai->fe = novo;

    while(pai != NULL)
    {
        consertaAltura(pai);
        pai = pai->pai;
    }

    return novo;

}

void transplanta(struct nodo **raiz, struct nodo* removido, struct nodo* novo)
{
    if (removido->pai == NULL) *(raiz) = novo;
    else 
    {
        if (removido->pai->fe == removido) removido->pai->fe = novo;
        else removido->pai->fd = novo;
    }

    if (novo != NULL) 
        novo->pai = removido->pai;
    
    struct nodo *pai = removido->pai;
    while (pai != NULL) 
    {
        consertaAltura(pai);
        pai = pai->pai;
    }
}


struct nodo* minimo(struct nodo* raiz)
{
    struct nodo* minimo = raiz;
    while (minimo->fe != NULL) minimo = minimo->fe;
    return minimo;
}

int excluir(struct nodo** raiz, int chave){
    struct nodo* removido = buscar(*raiz, chave);
    if (removido == NULL) return 0;

    if (removido->fe == NULL)
        transplanta(raiz, removido, removido->fd);

        
    else if (removido->fd == NULL)
        transplanta(raiz, removido, removido->fe);

    else
    {
        struct nodo* substituto = minimo(removido->fd);
        if (substituto != removido->fd)
        {
            transplanta(raiz, substituto, substituto->fd);
            substituto->fd = removido->fd;
            substituto->fd->pai = substituto;
        }
        substituto->fe = removido->fe;
        substituto->fe->pai = substituto;
        consertaAltura(substituto);
        transplanta(raiz, removido, substituto);
    }
    return 1;
}

struct nodo* buscar(struct nodo* nodo, int chave){
    struct nodo *atual = nodo;
    while(atual != NULL)
    {
        if (atual->chave == chave) return atual;
        if (chave > atual->chave) atual = atual->fd;
        else atual = atual->fe;
    }
    return NULL;
}

void emOrdemRecursivo(struct nodo *raiz)
{
    if (raiz == NULL) return;
    emOrdemRecursivo(raiz->fe);
    printf("%d ", raiz->chave);
    emOrdemRecursivo(raiz->fd);
}

void imprimirEmOrdem(struct nodo* raiz){
	printf("Imprimindo em ordem\n");
    emOrdemRecursivo(raiz);
    printf("\n");
}

void imprimirEmLargura(struct nodo* raiz){
	printf("Imprimindo em largura\n");
    lista* fila = criaLista();
    struct nodo* n;
    enfilera(fila, raiz);
    while (!ehVazia(fila))
    {
        n = desenfilera(fila)->nodo;
        printf("%d [%d] ,", n->chave, n->h);
        if(n->fe != NULL) enfilera(fila, n->fe);
        if(n->fd != NULL) enfilera(fila, n->fd);
    }
    destroiLista(fila);
}