# Ao final da execução será criado um arquivo executável chamado "file"

all: heap.o file.o 
	gcc -g heap.o file.o -o file -Wall
	rm -f *.o
heap.o:
	gcc -g -c heap.c
file.o:
	gcc -g -c file.c

clean:
	rm file