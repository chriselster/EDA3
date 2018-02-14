#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void help() {
	printf("Comandos:\n");
	printf("C NOMEDOARQUIVO.ext - Compacta o arquivo NOMEDOARQUIVO.ext.\n");
	printf("D NOMEDOARQUIVO.cpt - Descompacta o arquivo NOMEDOARQUIVO.cpt.\n");
	printf("H - Exibe os comandos disponíveis.\n");
	printf("Q - Encerra o programa.\n\n");
}

void compacta(HEAP *v, char *url, FILE *arq) {
	int tot = 0;
	char c;

	
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
				char *url;

				scanf(" %s", url);

				arq = fopen(url, "r");
				if (!arq) {
					printf("Erro ao acessar arquivo.\n");
				} else {
					v = cria_heap(128);
					compacta(v, url, arq);
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