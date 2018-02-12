#include <stdio.h>

int main(){
	char a;
	int v[128];

	for (int i = 0; i < 128; ++i)
	{
		v[i]=0;
	}

	while(scanf("%c", &a) != EOF){
		v[a]++;
	}
	
	for (int i = 0; i < 128; ++i)
	{
		printf("%c: %d\n", i, v[i]);
	}
}