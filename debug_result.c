/*Compilador DHP*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(void)
{
{
	/* Declaracoes para este escopo */
	int* d0 = NULL;	//m
	int t0;

	t0 = 2 * 2;
	d0 = (int*)malloc(t0 * sizeof(int));
	if (d0 == NULL) { fprintf(stderr, "Falha ao alocar memoria para a matriz!\n"); exit(1); }

	/* Liberando memoria alocada neste escopo */
	if (d0 != NULL) free(d0);
}
}

