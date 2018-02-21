#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

struct node {
	unsigned char type;
	int qtd;
};

struct trie {
	Node n;
	TRIE *esq, *dir; 
};

TRIE* cria_trie(unsigned char type, int qtd) {
	TRIE *v = malloc(sizeof(TRIE));

	v->n.type = type;
	v->n.qtd = qtd;
	v->esq = v->dir = NULL;

	return v;
}

void adcEsq(TRIE *a, TRIE *b) {
	a->esq = b;
}

void adcDir(TRIE *a, TRIE *b) {
	a->dir = b;
}

int getQtdOfTrie(TRIE *k) {
	return k->n.qtd;
}

unsigned char getTypeOfTrie(TRIE *k) {
	return k->n.type;
}

TRIE* getEsqOfTrie(TRIE *k) {
	return k->esq;
}

TRIE* getDirOfTrie(TRIE *k) {
	return k->dir;
}

void addchar(TRIE *raiz, unsigned char type) {
    raiz->n.type = type;
}

int bitabit(unsigned char *s, int a) {
    int i, j;
    i = a/8;
    j = a%8;
    return s[i]&(128>>j);
}

TRIE* recriar(TRIE *k, unsigned char *s, int *pos, int *tot, int tam) {
	if (*tot == tam) return NULL; 
	k = cria_trie('0', 0);

	if (!bitabit(s, (*pos)++)) {
		k->esq = recriar(getEsqOfTrie(k), s, pos, tot, tam);
		k->dir = recriar(getDirOfTrie(k), s, pos, tot, tam);
	} else {
		unsigned char aux = 0;

		for (int i=0; i<8; i++) {
			int bit = bitabit(s, *pos);
			if (bit) aux = aux | (128>>i);
			(*pos)++;
		}
		(*tot)++;
		
		addchar(k, aux);
	}

	return k;
}

void imprimir(TRIE *k, int ind) {
	if (k == NULL) return;

	if (k->esq == NULL && k->dir == NULL) printf("C: %c %x | FOLHA\n", k->n.type, k->n.type);

	printf("ESQ C: %c | IND: %d\n", k->n.type, ind);
	imprimir(k->esq, ind+1);
	printf("DIR C: %c | IND: %d\n", k->n.type, ind);
	imprimir(k->dir, ind+1);
}