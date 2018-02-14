#ifndef _HEAP_H
#define _HEAP_H

typedef struct heap HEAP;

HEAP* cria_heap(int tam);
void constroi(HEAP *v, int n);
void corrige_descendo(HEAP *v, int n, int i);
void heapsort(HEAP *v, int n);

#endif
