#ifndef _TRIE_H
#define _TRIE_H

typedef struct node Node;
typedef struct trie TRIE;

TRIE* cria_trie(unsigned char type, int qtd);
void adcEsq(TRIE *a, TRIE *b);
void adcDir(TRIE *a, TRIE *b);
int getQtdOfTrie(TRIE *k);
unsigned char getTypeOfTrie(TRIE *k);
TRIE* getEsqOfTrie(TRIE *k);
TRIE* getDirOfTrie(TRIE *k);
void addchar(TRIE *raiz, unsigned char type);
int bitabit(unsigned char *s, int a);
TRIE* recriar(TRIE *k, unsigned char *s, int *pos, int *tot, int tam);
void deletarTrie(TRIE *k);

#endif
