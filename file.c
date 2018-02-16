#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "trie.h"

void help() {
	printf("Comandos:\n");
	printf("C NOMEDOARQUIVO.ext - Compacta o arquivo NOMEDOARQUIVO.ext.\n");
	printf("D NOMEDOARQUIVO.cpt - Descompacta o arquivo NOMEDOARQUIVO.cpt.\n");
	printf("H - Exibe os comandos disponíveis.\n");
	printf("Q - Encerra o programa.\n\n");
}

void tamVerify(FILE *arq, unsigned char *aux, int *tam) {
	(*tam)++;
	if (*tam%8 == 0) {
		fwrite(aux, 1, 1, arq);
		*aux = 0;
	}
}

HEAP* lerArquivo(HEAP *v, FILE *arq, int *j, int *cont) {
	int i=1;
	char c;
	HEAP *a;
	
	while((c = fgetc(arq))!=EOF) {
		v = setQtd(v, c+1, getQtd(v, c+1) + 1);
		(*cont)++;
	}

	heapsort(v,257);

	while(getQtd(v, i)) i++;

	a = cria_heap();

	for (int p=1; p<i; p++, (*j)++) insere(a, NULL, getType(v, p), getQtd(v, p));

	return a;
}

void codifica(TRIE *k, FILE *cpt, char str[256][256], char s[256], unsigned char *aux, int *tam, int len) {
	if (k == NULL) return;
	if (getEsqOfTrie(k) == NULL && getDirOfTrie(k) == NULL) {
		char c = getTypeOfTrie(k);

		*aux = *aux | (128>>(*tam%8));
		tamVerify(cpt, aux, tam);
		for (int i=0; i<8; i++) {
			int mark = c & (128>>i);
			if (c & (128>>i)) *aux = (unsigned)(*aux | (128>>(*tam%8)));
			
			tamVerify(cpt, aux, tam);
		}

		for (int i=0; i<len; i++) str[c][i] = s[i];
		return;
	}

	tamVerify(cpt, aux, tam);

	s[len] = '0';
	codifica(getEsqOfTrie(k), cpt, str, s, aux, tam, len+1);
	s[len] = '1';
	codifica(getDirOfTrie(k), cpt, str, s, aux, tam, len+1);
}

void writeVal(char* val, int* pos, int bit) {
    (*pos)++;
    if (bit == 1) {
        *val = *val | (128 >> *pos);
    }
}

void codeTable(FILE *arq, FILE *cpt, char s[256][256], char *name) {
	char c;
	
	if (cpt) {
		char val = 0;
    	int pos = -1;
	    
		while((c = fgetc(arq)) != EOF) {
			int i = 0;
			
			while(s[c][i] != '\0') {
				if (pos < 7)
					writeVal(&val, &pos, s[c][i] - '0');
				else {
					fputc(val, cpt);
					val = 0;
	    			pos = -1;
					
					writeVal(&val, &pos, s[c][i] - '0');
				}
				i++;
			}
		}
		
		fputc(val, cpt);
	}

}

TRIE* newTrie(HEAP *t, int j) {
	TRIE *a, *b, *k;
	if (j == 1) {
		a = remove_max(t);
		k = cria_trie('0', getQtdOfTrie(a), a, NULL);
	} else while(j-- - 1){
		a = remove_max(t);
		b = remove_max(t);

		k = cria_trie('0', getQtdOfTrie(a)+getQtdOfTrie(b), a, b);
		insere(t, k, '0', getQtdOfTrie(k));
	}

	return k;
}

void compacta(HEAP *v, FILE *arq, char *name) {
	int j=0, cont=0;
	char c;

	HEAP *t = lerArquivo(v, arq, &j, &cont);

	if (j == 0) {
		printf("Arquivo vazio.\n");
		return;
	}
	
	TRIE *k = newTrie(t, j);

	char str[256][256], s[256];
	rewind(arq);

	FILE *cpt = fopen(name, "w+b");
	int tam = 0;
	unsigned char aux = 0;

	if (j <= 255) {
		aux = 0;
		fwrite(&aux, 1, 1, cpt);
		aux = j;
		fwrite(&aux, 1, 1, cpt);
	} else {
		aux = 1;
		fwrite(&aux, 1, 1, cpt);
		aux = 255;
		fwrite(&aux, 1, 1, cpt);
	}

	aux = 0;
	codifica(k, cpt, str, s, &aux, &tam, 0);
	fwrite(&aux, 1, 1, cpt);

	for (int i = 3; i>=0; i--) {
		aux = (cont & (0xFF << (8*i))) >> (8*i);
		fwrite(&aux, 1, 1, cpt);
	}

	codeTable(arq, cpt, str, name);
	fclose(cpt);
	
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
	
	
	
	printf("Compactei v1.0 \n\n");
	
	help();

	while (scanf(" %c", &act)) {
		if (act == 'Q') break;
		switch (act) {
			case 'C': {
				char url[280000], name[280000];

				scanf(" %s", url);

				FILE *arq = fopen(url, "r+b");

				if (!arq) {
					printf("Erro ao acessar arquivo.\n");
				} else {
					strncpy(name, url, strlen(url)-4);
					strcat(name, ".bin");

					HEAP *v = cria_heap();
					for (i=1; i<257; i++) v = insere(v, NULL, i-1, 0);

					compacta(v, arq, name);
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