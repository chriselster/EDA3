#include <stdio.h>
#include <stdlib.h>


#include "heap.h"
struct heap {
	char type;
	int qtd;
};

struct no
{
	int qtd;
	HEAP *esq;
	HEAP *dir;
};

void help() {
	printf("Comandos:\n");
	printf("C NOMEDOARQUIVO.ext - Compacta o arquivo NOMEDOARQUIVO.ext.\n");
	printf("D NOMEDOARQUIVO.cpt - Descompacta o arquivo NOMEDOARQUIVO.cpt.\n");
	printf("H - Exibe os comandos disponíveis.\n");
	printf("Q - Encerra o programa.\n\n");
}

void compacta(HEAP *v, FILE *arq) {
	HEAP *semzero;
	char c;
	c = fgetc(arq);
	while(c!=EOF){
		v[c+1].qtd++;
		c = fgetc(arq);
	}


	heapsort(v,128);
	int i = 0;
	while(!v[i].qtd)i++;
	semzero = cria_heap(129-i);
	int j = 0;
	for (i; i < 129; ++i)
	{
		semzero[j++] = v[i];
	}
	no C;
	while(j>1){
		HEAP a,b,novo;
		a = remove_max(semzero,j--);
		b = remove_max(semzero,j--);
		C.qtd = a.qtd + b.qtd;
		C.esq = &a;
		C.dir = &b;
		novo.qtd = C.qtd;
		insere_no(semzero,j++,novo);
		// printf("%d\n",C.dir->qtd);
		// printf("%d\n",C.esq->qtd);
	}

	return ;
}

void descompacta() {

}

void organiza(HEAP *v) {
	int tam = 0;
}

int main() {
	int i;
	char act;
	
	FILE *arq;
	HEAP *v;
	printf("Compactei v1.0 \n\n");
	
	help();

	while (scanf(" %c", &act)) {
		if (act == 'Q') break;
		switch (act) {
			case 'C': {
				char url[3000000];

				scanf("%s", url);
				arq = fopen(url, "r");
				if (!arq) {
					printf("Erro ao acessar arquivo.\n");
				} else {
					v = cria_heap(129);
					compacta(v, arq);
				}
				

				break;
			}

			case 'D': {
				break;
			}

			case 'H': {
				printf("\n");
				help();
				break;
			}

			default: {
				printf("Erro - Comando não encontrado.\n\n");
				break;
			}
		}

	}

	printf("Obrigado por utilizar os nossos serviços, a equipe da Compactei agradece. =)\n");
}