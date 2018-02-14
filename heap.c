#include <stdlib.h>
#include "heap.h"

struct heap {
	char type;
	int qtd;
};

HEAP* cria_heap(int tam) {
	HEAP *v = malloc(sizeof(HEAP)*tam);

	for (int i=0; i<tam; i++) {
		v[i].type = i;
		v[i].qtd = 0;
	}

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

		if (f < n && v[f].qtd < v[f+1].qtd) f++;

		if (v[j].qtd >= v[f].qtd) break;
		else {
			HEAP temp = v[j];
			v[j] = v[f];
			v[f] = temp;
			j = f;
		}
	}
}

void heapsort(HEAP *v, int n) {
	constroi(v, n);
	int k = n;

	while (k >= 1) {
		HEAP temp = v[k];
		v[k] = v[1];
		v[1] = temp;
		k--;
		corrige_descendo(v, k, 1);
	}
}