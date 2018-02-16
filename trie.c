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

void code(TRIE *k, char str[256][256], char s[256], int len) {
	if (k == NULL) return;
	
	if (k->esq == NULL && k->dir == NULL) {
		for (int i=0; i<len; i++) str[k->n.type][i] = s[i];
		return;
	}

	s[len] = '0';
	code(k->esq, str, s, len+1);
	s[len] = '1';
	code(k->dir, str, s, len+1);
}