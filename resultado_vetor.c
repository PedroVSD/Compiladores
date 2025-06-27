/*Compilador DHP*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(void)
{
{
	/* Declaracoes para este escopo */
	int d2;	//a
	int d1;	//i
	int t0;
	int t1;
	int t2;
	int* d0 = NULL;	//v

	d0 = (int*)malloc(5 * sizeof(int));
	if (d0 == NULL) { fprintf(stderr, "Falha ao alocar memoria para o vetor!\n"); exit(1); }
	t0 = 0;
	d1 = t0;
	t1 = 10;
	d0[d1] = t1;
	t2 = d0[d1];
	d2 = t2;
	printf("%d", d2);
	printf("\n");

	/* Liberando memoria alocada neste escopo */
	if (d0 != NULL) free(d0);
}
}

