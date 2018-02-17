#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

struct node {
	char type;
	int qtd;
};

struct trie {
	Node n;
	TRIE *esq, *dir; 
};

TRIE* cria_trie(char type, int qtd) {
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

char getTypeOfTrie(TRIE *k) {
	return k->n.type;
}

TRIE* getEsqOfTrie(TRIE *k) {
	return k->esq;
}

TRIE* getDirOfTrie(TRIE *k) {
	return k->dir;
}

void imprimir(TRIE *k) {
	if (k == NULL) return;

	printf("C: %c\n", k->n.type);

	imprimir(k->esq);
	imprimir(k->dir);
}