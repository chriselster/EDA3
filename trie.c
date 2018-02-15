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

void code(TRIE *k, int str[256], int tot) {
	if (k == NULL) return;
	
	if (k->esq == NULL && k->dir == NULL) {
		str[k->n.type] = tot;
		return;
	}

	code(k->esq, str, (tot<<1)+0);
	code(k->dir, str, (tot<<1)+1);

	
}