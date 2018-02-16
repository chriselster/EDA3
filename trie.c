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

TRIE* cria_trie(int type, int qtd, TRIE *esq, TRIE *dir) {
	TRIE *v = malloc(sizeof(TRIE));

	v->n.type = type;
	v->n.qtd = qtd;
	v->esq = esq;
	v->dir = dir;

	return v;
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

