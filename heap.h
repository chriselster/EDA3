#ifndef _HEAP_H
#define _HEAP_H
#include "trie.h"

typedef struct heap HEAP;
typedef struct node Node;

HEAP* cria_heap();
HEAP* insere(HEAP *v, TRIE *t, char type, int qtd);
void constroi_min(HEAP *v, int n);
void corrige_descendo(HEAP *v, int n, int i);
void corrige_subindo(HEAP *v, int m);
void heapsort(HEAP *v, int n);
int getQtd(HEAP *v, int pos);
char getType(HEAP *v, int pos);
HEAP* setQtd(HEAP *v, int pos, int val);
HEAP* atribui(HEAP *v, int i, HEAP *t, int j);
TRIE* remove_max(HEAP *v);
void imprima(HEAP *v);

#endif
