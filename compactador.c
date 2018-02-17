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
		if (f<n-1 && v[f].qtd>v[f+1].qtd){
			f = f+1;
		}
		printf("%d <= %d?\n", v[f].qtd,v[j].qtd);
		if (v[j].qtd<=v[f].qtd){
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

void heapsort(no v[129], int n) {
   int i = n / 2, pai, filho;
   no t;
   while(1) {
      if (i > 1) {
          i--;
          t = v[i];
      } else {
          n--;
          if (n == 1) return;
          t = v[n];
          v[n] = v[1];
      }
      pai = i;
      filho = i * 2;
      while (filho < n) {
          if ((filho + 1 < n)  &&  (v[filho + 1].qtd > v[filho].qtd))
              filho++;
          if (v[filho].qtd > t.qtd) {
             v[pai] = v[filho];
             pai = filho;
             filho = pai * 2;
          } else {
             break;
          }
      }
      v[pai] = t;
   }
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
	
	for (int i = 129/2; i > 0; --i)
	{
		min_heapfy(v,129,i);
	}

	heapsort(v,129);

	for (int i = 1; i < 129; ++i)
	{
		printf("%c: %d\n",v[i].type, v[i].qtd);
	}
}