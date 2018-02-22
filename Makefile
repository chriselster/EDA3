# Ao final da execução será criado um arquivo executável chamado "file"

all: trie.o heap.o file.o 
	gcc -g file.o heap.o trie.o -o file -Wall -Wextra -Werror -Wpedantic
	rm -f *.o
heap.o:
	gcc -g -c heap.c
file.o:
	gcc -g -c file.c
trie.o:
	gcc -g -c trie.c
clean:
	rm file