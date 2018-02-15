#include <stdlib.h>
#include "heap.h"

struct heap {
	char type;
	int qtd;
};

struct no
{
	int qtd;
	HEAP *esq;
	HEAP *dir;
};

HEAP* cria_heap(int tam) {
	HEAP *v = malloc(sizeof(HEAP)*tam);

	for (int i=1; i<tam+1; i++) {
		v[i].type = i-1;
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

void corrige_subindo(HEAP *v, int n) {
	int i = n;

	while (i>=2 && v[i/2].qtd >v[i].qtd ) {
		HEAP temp = v[i];
		v[i] = v[i/2];
		v[i/2] = temp;
		i = i/2;
		
	}
}

HEAP remove_max(HEAP*v,int n){
	HEAP max = v[1];
	v[1]=v[n];
	n=n-1;
	corrige_descendo(v,n,1);
	return max;
}


HEAP* insere_no(HEAP*v, int n, HEAP c){
	v[n+1]=c;
	corrige_subindo(v,n+1);
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