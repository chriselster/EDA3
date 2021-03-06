#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "trie.h"

// Funcao para comando H que imprime todos os outros disponiveis
void help() {
	printf("Comandos:\n");
	printf("C nomedoarq.ext - Compacta o arquivo NOMEDOARQUIVO.ext.\n");
	printf("D nomedoarq.bin novonome.ext - Descompacta o arquivo NOMEDOARQUIVO.bin para o NOVONOME.ext.\n");
	printf("H - Exibe os comandos disponíveis.\n");
	printf("Q - Encerra o programa.\n\n");
}

// Permite a leitura de uma string com tamanho qualquer
char* readstr(char* str, size_t size, size_t tam){
	char ch;
	str = realloc(NULL, sizeof(char)*size);
    if(!str)return str;
    
    while(EOF!=(ch=fgetc(stdin)) && (ch != '\n' && ch != ' ')){
        str[tam++]=ch;
        if(tam==size){
            str = realloc(str, sizeof(char)*(size+=16));
            if(!str)return str;
        }
    }
    str[tam++]='\0';
    
    return realloc(str, sizeof(char)*tam);
}

// Concatena duas strings
void concatChar(unsigned char *s, unsigned char aux, int *len) {
	s = realloc(s, sizeof(char)*(*len+1));
	s[(*len)++] = aux;
}

// Verifica se está completo os 8 bits, se sim, escreve aux no arquivo arq
void tamVerify(FILE *arq, unsigned char *aux, int *tam) {
	(*tam)++;
	if (*tam%8 == 0) {
		fwrite(aux, 1, 1, arq);
		*aux = 0;
	}
}

// Processa o arquivo e cria um heap maximo baseado na frequencia dos caracteres
HEAP* lerArquivo(HEAP *v, FILE *arq, int *j, int *cont) {
	int i = 1, p;
	unsigned char c;
	HEAP *a;

	while(c = fgetc(arq)) {
		if (feof(arq)) break;
		v = setQtd(v, c+1, getQtd(v, c+1) + 1);
		(*cont)++;
	}

	heapsort(v,256);

	while(getQtd(v, i)) i++;

	a = cria_heap();
	
	if (a == NULL) return a;

	for (p = 1; p < i; p++, (*j)++) 
		insere(a, NULL, getType(v, p), getQtd(v, p));
	
	return a;
}

// Realizara a codificacao do texto em sequencia de 0 e 1 pela arvore ja existente
void codifica(TRIE *k, FILE *cpt, unsigned char str[256][256], unsigned char s[256], unsigned char *aux, int *tam, int len) {
	if (k == NULL)
		return;

	if (getEsqOfTrie(k) == NULL && getDirOfTrie(k) == NULL) {
		int i;
		unsigned char c = getTypeOfTrie(k);
		*aux = *aux | (128>>(*tam%8));
		
		tamVerify(cpt, aux, tam);
		
		for (i = 0; i < 8; i++) {
			if (c & (128>>i)) 
				*aux = (unsigned) (*aux | (128>>(*tam%8)));
			tamVerify(cpt, aux, tam);
		}
		
		for (i = 0; i < len; i++) 
			str[c][i] = s[i];

		str[c][len] = '\0';
		return;
	}

	tamVerify(cpt, aux, tam);

	s[len] = '0';
	codifica(getEsqOfTrie(k), cpt, str, s, aux, tam, len+1);
	s[len] = '1';
	codifica(getDirOfTrie(k), cpt, str, s, aux, tam, len+1);
}

// Manipula bit a bit um char para escrever no arquivo de byte em byte
void writeVal(char* val, int* pos, int bit) {
    (*pos)++;
    if (bit == 1) {
        *val = *val | (128 >> *pos);
    }
}

// Escreve bit a bit a sequencia gerada pela arvore do algoritmo de huffman para cada caractere
void codeTable(FILE *arq, FILE *cpt, unsigned char s[256][256], char *name) {
	unsigned char c;
	
	if (cpt) {
		unsigned char val = 0;
    	int pos = -1;
	    
		while((c = fgetc(arq)) | 1) {
			if (feof(arq)) break;
			int i = 0;
			
			while(s[c][i] != '\0') {
				if (pos < 7) {
					writeVal(&val, &pos, s[c][i] - '0');
				} else {
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

// Cria uma arvore de huffman com base no heap maximo criado
TRIE* newTrie(HEAP *t, int j) {
	TRIE *a, *b, *k;
	if (j == 1) {
		a = remove_max(t);
		k = cria_trie('0', getQtdOfTrie(a));
		adcEsq(k, a);
	} else while(j-- - 1){
		a = remove_max(t);
		b = remove_max(t);

		k = cria_trie('0', getQtdOfTrie(a)+getQtdOfTrie(b));
		adcEsq(k, a);
		adcDir(k, b);
		insere(t, k, '0', getQtdOfTrie(k));
	}

	return k;
}

// Comanda a compactacao do texto, criando um heap-maximo, uma trie baseado no algoritmo de huffman
// Em seguida escreve a arvore e o texto compactado no arquivo binario
void compacta(HEAP *v, FILE *arq, char *name) {
	int j = 0, cont = 0;

	printf("\nLendo caracteres...\n");

	HEAP *t = lerArquivo(v, arq, &j, &cont);

	if (t == NULL) {
		printf("\nErro - Heap nulo.\n");
		exit(1);
	}

	if (j == 0) {
		printf("\nErro - Arquivo vazio.\n");
		exit(1);
	}

	printf("Construindo a arvore atraves da tabela de frequencia...\n");
	
	TRIE *k = newTrie(t, j);

	if (k == NULL) {
		printf("\nErro - Trie nula.\n");
		exit(1);
	}
		

	unsigned char str[256][256], s[256];
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
	printf("Codificando a arvore...\n");
	codifica(k, cpt, str, s, &aux, &tam, 0);
	fwrite(&aux, 1, 1, cpt);

 	fwrite(&cont, sizeof(int), 1, cpt);

 	printf("Codificando o texto...\n");
	codeTable(arq, cpt, str, name);

	if (!ferror(cpt)) {
		printf("\nArquivo compactado com sucesso!\nPara descompactar o arquivo, digite D %s NOMEDOARQUIVO.ext.\n\n", name);
	} else {
		printf("\nErro ao compactar.\n");
		exit(1);
	}

	fclose(arq);
	fclose(cpt);
	deletarTrie(k);
	deletarHeap(t);
	
	return;
}

// Retorna o bit mais significativo do char val (mais à esquerda)
int getBit(char* val, int* pos) {
	int k = (*val & 128) >> 7;
	*val = *val << 1;
	(*pos)++;
	return k;
}

// Processa (ler) tamanho quantidade de bytes do arquivo arq
int tamBytes(FILE *arq, int tamanho) {
	int aux = 0, i;
	unsigned char tam[tamanho];

	fread(tam, tamanho, 1, arq);

	for (i = 0; i < tamanho; i++) 
		aux = aux | (tam[i] << (8*((tamanho-1)-i)));

	return aux;
}

// Retorna a quantidade de caracteres da arvore
void bytesOfTrie(FILE *arq, unsigned char *s, int *len, int tam) {
	unsigned char c, aux = 0;
	int pos = 0, cont = 0, bt = 8;
	int ok = 0, pass = 1;
	
	while((c = fgetc(arq)) | 1) {
		if (feof(arq))
			break;

		while (pass && pos < 8) {
			if (!ok && (c & (128>>(pos)))) {
				aux = aux | (128>>(pos));
				ok = 1;
				if (++pos >= 8) {
					concatChar(s, aux, len);
					break;
				}
			}

			if (!ok) {
				if (++pos >= 8) {
					concatChar(s, aux, len);
					break;
				}
			}
			
			if (ok) {
				if (bt--) {
					if (c & (128>>(pos))) aux = aux | (128>>(pos));
					pos++;

					if (pos >= 8) {
						concatChar(s, aux, len);
						break;
					}
				} else {
					ok = 0;
					bt = 8;
					cont++;
					if (cont == tam) {
						pass = 0;
					}
				}
			}
		}

		if (!pass) {
			concatChar(s, aux, len);
			(*len)--;
			break;
		}
		
		pos = 0;
		aux = 0;
	}
}

// Processa a parte do arquivo compactador referente ao texto original e reescreve-o no novo arquivo
void decodeStr(FILE *arq, FILE *dcpt, long long totalCh, TRIE* trie) {
	unsigned char c;
	
	if (arq) {
		unsigned char val = 0;
    	int pos = -1;
	    long long qntCh = 0;
	    
	    TRIE* aux = trie;
	    
		while(1) {
			c = fgetc(arq);
			val = c;
			if (feof(arq)) break;
			if (qntCh == totalCh) break;

			while(pos < 7 && qntCh < totalCh) {
				int i = getBit(&val, &pos);

				if (i == 1) aux = getDirOfTrie(aux);
				else aux = getEsqOfTrie(aux);
				
				if (getEsqOfTrie(aux) == NULL && getDirOfTrie(aux) == NULL)  {
					unsigned char t = getTypeOfTrie(aux);
					fputc(t, dcpt);
					
					aux = trie;
					qntCh++;
				}
			}

			pos = -1;
		}
	}
}

// Comanda o processo de descompactar o arquivo binario, decodificando a arvore e a sequencia de 0 e 1
// do texto original
void descompacta(FILE *arq, FILE *dcpt) {
	int len = 0, pos = 0, tot = 0, tamStr = 0;
	unsigned char *s = malloc(sizeof(char)*0);

	int tamTrie = tamBytes(arq, 2);
	printf("\nDecodificando a arvore...\n");
	bytesOfTrie(arq, s, &len, tamTrie);

	fread(&tamStr, sizeof(int), 1, arq);
	printf("Recriando a arvore...\n");
	
	TRIE *k = recriar(k, s, &pos, &tot, len);
	
	if (k == NULL) {
		printf("\nErro - Trie nula.\n\n");
		exit(1);
	}

	printf("Decodificando o texto...\n");
	decodeStr(arq, dcpt, tamStr, k);

	if (!ferror(dcpt)) {
		printf("\nArquivo descompactado com sucesso!\n\n");
	} else {
		printf("\nErro ao compactar.\n");
		exit(1);
	}

	fclose(arq);
	fclose(dcpt);
	deletarTrie(k);
	free(s);

	return;
}

int main() {
	int i;
	char act;
	
	printf("Compactei v1.0\n\n");
	
	help();

	while (scanf(" %c", &act)) {
		if (act == 'Q') break;

		switch (act) {
			case 'C': {
				// Cria-se um arquivo de mesmo nome com extensao .bin e sera o compactado
				char c, *url, *name;
				c = fgetc(stdin);
				url = readstr(url, 10, 0);
				name = malloc(sizeof(char)*strlen(url));

				FILE *arq = fopen(url, "r+b");

				if (!arq) {
					printf("\nErro ao acessar arquivo.\n\n");
				} else {
					int i = 0;
					while (url[i] != '.') i++;
					strncpy(name, url, i);
					strcat(name, ".bin");

					HEAP *v = cria_heap();
					for (i = 1; i < 257; i++) 
						v = insere(v, NULL, i-1, 0);

					compacta(v, arq, name);
				}
				
				free(name);
				free(url);				

				break;
			}

			case 'D': {
				char c, *url, *name;
				c = fgetc(stdin);
				url = readstr(url, 10, 0);
				name = readstr(name, 10, 0);

				FILE *arq = fopen(url, "r+b");
				FILE *dcpt = fopen(name, "w");

				if (!arq) printf("\nErro ao acessar arquivo.\n\n");
				else descompacta(arq, dcpt);

				break;
			}

			case 'H': {
				printf("\n");
				help();
				break;
			}

			default: {
				printf("\nErro - Comando nao encontrado.\n\n");
				break;
			}
		}

	}

	printf("\nObrigado por utilizar os nossos servicos, a equipe da Compactei agradece. =)\n");
}
