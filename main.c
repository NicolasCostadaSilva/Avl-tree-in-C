#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

int main(){
	imprimirDadosAlunos();

	struct nodo** raiz = malloc(sizeof(struct nodo*));
	*raiz = NULL;
	int chave; int op;


	printf("1 insere, 2 imprime, 3 wxclui: ");
	scanf("%d", &op);
	while (op != -1)
	{
		if (op == 1)
		{
			printf("dado: ");
			scanf("%d", &chave);
			inserir(raiz, chave);
		}
		if (op == 2)
		{
			imprimirEmLargura(*raiz);
		}
		if(op == 3)
		{
			printf("buscar: ");
			scanf("%d", &chave);
			excluir(raiz, chave);
		}
		printf("1 insere, 2 imprime, 3 esclui: ");
		scanf("%d", &op);
	}

	




	return 0;
}
