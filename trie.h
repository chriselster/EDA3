#ifndef _TRIE_H
#define _TRIE_H

typedef struct node Node;
typedef struct trie TRIE;

TRIE* cria_trie(int type, int qtd, TRIE *esq, TRIE *dir);
int getQtdOfTrie(TRIE *k);
char getTypeOfTrie(TRIE *k);
TRIE* getEsqOfTrie(TRIE *k);
TRIE* getDirOfTrie(TRIE *k);

#endif
