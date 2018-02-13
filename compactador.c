#include <stdio.h>

typedef struct no
{
	char type;
	int qtd;
}no;

void min_heapfy(no v[129], int n, int i){
	int j = i;
	while(2*j <= n){
		int f = 2*j;
		if (f<=n && v[f].qtd<v[f+1].qtd){
			f = f+1;
		}
		printf("%d, %d?\n", f,j);
		if (v[j].qtd>=v[f].qtd){
			j=n;
		}else{
			no aux;
			aux = v[f];
			v[f] = v[j];
			v[j] = aux;
			j = f;
		}
	}
	return;
}



int main(){
	char a;
	no v[129];

	for (int i = 0; i < 129; ++i)
	{
		v[i].type=i-1;
		v[i].qtd=0;
	}

	while(scanf("%c", &a) != EOF){
		v[a+1].qtd++;
	}
	
	for (int i = 129/2; i > 1; --i)
	{
		min_heapfy(v,129,i);
	}

	for (int i = 1; i < 129; ++i)
	{
		printf("%c: %d\n",v[i].type, v[i].qtd);
	}
}