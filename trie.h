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
void addchar(TRIE *raiz, char type);
int bitabit(char *s, int a);
int readchar(char *s, long long a);
int recria(TRIE* raiz, char *s, long long i);
TRIE* recria_trie(char *s);
TRIE* recriar(TRIE *k, char *s, int *pos, int *tot, int tam);
void imprimir(TRIE *k);

#endif
