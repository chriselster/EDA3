#ifndef _TRIE_H
#define _TRIE_H

typedef struct node Node;
typedef struct trie TRIE;

TRIE* cria_trie(int type, int qtd, TRIE *esq, TRIE *dir);
int getQtdOfTrie(TRIE *k);
char getTypeOfTrie(TRIE *k);
void code(TRIE *k, int str[256], int tot);

#endif
