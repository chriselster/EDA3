#ifndef _HEAP_H
#define _HEAP_H

typedef struct heap HEAP;
typedef struct no no;

HEAP* cria_heap(int tam);
void constroi(HEAP *v, int n);
void corrige_descendo(HEAP *v, int n, int i);
void heapsort(HEAP *v, int n);
void corrige_subindo(HEAP *v, int n);
HEAP remove_max(HEAP*v,int n);
HEAP* insere_no(HEAP*v, int n, HEAP c);
#endif
