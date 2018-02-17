#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "trie.h"

struct node {
	char type;
	int qtd;
	TRIE *t;
};

struct heap {
	int tam;
	Node *n;	
};

HEAP* cria_heap() {
	HEAP *v = malloc(sizeof(HEAP));
	v->n = malloc(sizeof(Node)*257);
	v->tam = 0;
	return v;
}

HEAP* insere(HEAP *v, TRIE *t, char type, int qtd) {
	v->n[++v->tam].type = type;
	v->n[v->tam].qtd = qtd;
	v->n[v->tam].t = t;
	corrige_subindo(v, v->tam);
	return v;
}

void constroi(HEAP *v, int n) {
	int i;
	for (i=n/2; i>=1; i--) {
		corrige_descendo(v, n, i);
	}
}

void corrige_descendo(HEAP *v, int n, int i) {
	int j = i;

	while (2*j <= n) {
		int f = 2*j;

		if (f < n && v->n[f].qtd > v->n[f+1].qtd) f++;

		if (v->n[j].qtd <= v->n[f].qtd) break;
		else {
			Node temp = v->n[j];
			v->n[j] = v->n[f];
			v->n[f] = temp;
			j = f;
		}
	}
}

void corrige_subindo(HEAP *v, int m) {
	int i = m;

	while (i>=2 && v->n[i/2].qtd > v->n[i].qtd) {
		Node temp = v->n[i/2];
		v->n[i/2] = v->n[i];
		v->n[i] = temp;
		i = i/2;
	}
}

void heapsort(HEAP *v, int n) {
	constroi(v, n);
	int k = n;

	while (k >= 1) {
		Node temp = v->n[k];
		v->n[k] = v->n[1];
		v->n[1] = temp;
		k--;
		corrige_descendo(v, k, 1);
	}
}

int getQtd(HEAP *v, int pos) {
	return v->n[pos].qtd;
}

char getType(HEAP *v, int pos) {
	return v->n[pos].type;
}

HEAP* setQtd(HEAP *v, int pos, int val) {
	v->n[pos].qtd = val;
	return v;
}

HEAP* atribui(HEAP *v, int i, HEAP *t, int j) {
	v->n[i] = t->n[j];
	return v;
}

TRIE* remove_max(HEAP *v){
	Node max = v->n[1];
	v->n[1]=v->n[v->tam--];
	corrige_descendo(v,v->tam,1);
	TRIE *t;
	if (max.t == NULL) t = cria_trie(max.type, max.qtd, NULL, NULL);
	else t = max.t;
	return t;
}

void imprima(HEAP *v) {
	for (int i=1; i<=v->tam; i++) printf("C: %c | QTD: %d\n", v->n[i].type, v->n[i].qtd);
}