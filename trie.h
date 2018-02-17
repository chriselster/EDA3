#ifndef _TRIE_H
#define _TRIE_H

typedef struct node Node;
typedef struct trie TRIE;

TRIE* cria_trie(char type, int qtd);
void adcEsq(TRIE *a, TRIE *b);
void adcDir(TRIE *a, TRIE *b);
int getQtdOfTrie(TRIE *k);
char getTypeOfTrie(TRIE *k);
TRIE* getEsqOfTrie(TRIE *k);
TRIE* getDirOfTrie(TRIE *k);
void imprimir(TRIE *k);

#endif
