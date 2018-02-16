#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "trie.h"

typedef struct tempChar {
    char val;
    int pos;
} tempChar;

void writeVal(tempChar *var, int bit) {
    var->pos++;
    if (bit == 1) {
        var->val += (128 >> var->pos);
    }
}


void help() {
	printf("Comandos:\n");
	printf("C NOMEDOARQUIVO.ext - Compacta o arquivo NOMEDOARQUIVO.ext.\n");
	printf("D NOMEDOARQUIVO.cpt - Descompacta o arquivo NOMEDOARQUIVO.cpt.\n");
	printf("H - Exibe os comandos disponíveis.\n");
	printf("Q - Encerra o programa.\n\n");
}

HEAP* lerArquivo(HEAP *v, FILE *arq, int *j) {
	int i=1;
	char c;
	HEAP *a;
	
	while((c = fgetc(arq))!=EOF) v = setQtd(v, c+1, getQtd(v, c+1) + 1);

	heapsort(v,257);

	while(getQtd(v, i)) i++;

	a = cria_heap();

	for (int p=1; p<i; p++, (*j)++) insere(a, NULL, getType(v, p), getQtd(v, p));

	return a;
}

void codifica(FILE *arq, char s[256][256], char *name) {
	char c;
	FILE *cpt;
	cpt = fopen("text.bin", "wb");
	
	if (cpt) {
		tempChar* var = malloc(sizeof(tempChar));
	    var->val = 0;
	    var->pos = -1;
	    
		while((c = fgetc(arq)) != EOF) {
			int i = 0;
			
			while(s[c][i] != '\0') {
				if (var->pos < 7)
					writeVal(var, s[c][i] - '0');
				else {
					fputc(var->val, cpt);
					var->val = 0;
	    			var->pos = -1;
					
					writeVal(var, s[c][i] - '0');
				}
				i++;
			}
		}
		
		fputc(var->val, cpt);
	}
	cpt = fopen("text.bin", "rb");
	c = fgetc(cpt);
	printf("C:%hu\n", c);
}

void compacta(HEAP *v, FILE *arq, FILE *arq2, char *name) {
	int j=0;
	char c;
	HEAP *t = lerArquivo(v, arq, &j);
	
	TRIE *k;
	
	while(j-- - 1){
		TRIE *a, *b, *new;
		a = remove_max(t);
		b = remove_max(t);

		k = cria_trie('0', getQtdOfTrie(a)+getQtdOfTrie(b), a, b);
		insere(t, k, '0', getQtdOfTrie(k));
	}

	char str[256][256], s[256];
	code(k, str, s, 0);
	codifica(arq2, str, name);
	return;
}

void descompacta() {

}

void organiza(HEAP *v) {
	int tam = 0;
}

int main() {
	int i;
	char act;
	
	FILE *arq, *arq2;
	HEAP *v;
	
	printf("Compactei v1.0 \n\n");
	
	help();

	while (scanf(" %c", &act)) {
		if (act == 'Q') break;
		switch (act) {
			case 'C': {
				char url[280000], nam;

				scanf(" %s", url);

				arq = fopen(url, "rb");
				arq2 = fopen(url, "rb");

				if (!arq) {
					printf("Erro ao acessar arquivo.\n");
				} else {
					int i = 0;
					while(url[i++] != '.');
					url[i++] = 'b';
					url[i++] = 'i';
					url[i++] = 'n';

					v = cria_heap();
					for (i=1; i<257; i++) v = insere(v, NULL, i-1, 0);

					compacta(v, arq, arq2, url);
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