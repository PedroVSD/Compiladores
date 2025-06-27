/*Compilador DHP*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(void)
{
{
	/* Declaracoes para este escopo */
	int d1;	//a
	int* d0 = NULL;	//m
	int t0;
	int t1;
	int t2;
	int t3;

	d0 = (int*)malloc(4 * sizeof(int));
	if (d0 == NULL) { fprintf(stderr, "Falha ao alocar memoria para o vetor!\n"); exit(1); }
	t0 = 0;
	t1 = 10;
	d0[t0] = t1;
	t2 = 0;
	t3 = d0[t2];
	d1 = t3;
	printf("%d", d1);
	printf("\n");

	/* Liberando memoria alocada neste escopo */
	if (d0 != NULL) free(d0);
}
}

