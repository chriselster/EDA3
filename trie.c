#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void addchar(TRIE *raiz, char type) {
    raiz->n.type = type;
}

int bitabit(char *s, int a) {
    int i, j;
    i = a/8;
    j = a%8;
    return s[i]&(128>>j);
}

int readchar(char *s, long long a) {
    int i, j, k, type;
    i = a/8;
    j = a%8;
    for(k=j;k>=0;k--){
        type += s[i]&(1<<k);
    }
    for(k=7;k>j;k--){
        type += s[i-1]&(1<<k);
    }
    return type;
}

int recria(TRIE* raiz, char *s, long long i) {
    if(!bitabit(s, i)){
        i--;
        i = recria(getEsqOfTrie(raiz), s, i);
    }else{
        i--;
        addchar(raiz, readchar(s, i));
        i-=7;
        return i;
    }
    if(i>0){
        i--;
        i = recria(getDirOfTrie(raiz), s, i);
    }
    return i;
}

TRIE* recria_trie(char *s) {
    TRIE *raiz = cria_trie(0, 0);
    recria(raiz, s, strlen(s)*8);
    return raiz;
}

TRIE* recriar(TRIE *k, char *s, int *pos, int *tot, int tam) {
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

void imprimir(TRIE *k) {
	if (k == NULL) return;

	printf("C: %c\n", k->n.type);

	imprimir(k->esq);
	imprimir(k->dir);
}