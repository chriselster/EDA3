#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>       /*abs*/
int main(){
	long n;
	FILE *fp = NULL;
	fp = fopen("input6.txt" ,"a");
	scanf("%ld", &n);
	srand (time(NULL));
	for (int i = 0; i < n; ++i)
	{
		char a;
		a = rand()%243+13;
		fprintf(fp, "%c", a);
	}
}