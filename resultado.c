/*Compilador DHP*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"algoritmos/quicksort.h"

int main(void)
{
{
	/* Declaracoes para este escopo */
	int* d0 = NULL;	//m
	int t11;
	int t15;
	int t10;
	int t13;
	int t14;
	int t9;
	int t0;
	int t1;
	int t2;
	int t3;
	int t4;
	int t5;
	int t6;
	int t7;
	char* t12 = NULL;
	char* t8 = NULL;

	d0 = (int*)malloc(4 * sizeof(int));
	if (d0 == NULL) { fprintf(stderr, "Falha ao alocar memoria para o vetor!\n"); exit(1); }
	t0 = 0;
	t1 = 10;
	d0[t0] = t1;
	t2 = 1;
	t3 = 1;
	d0[t2] = t3;
	t4 = 2;
	t5 = 9;
	d0[t4] = t5;
	t6 = 3;
	t7 = -1;
	d0[t6] = t7;
	t8 = (char*)malloc(20);
	strcpy(t8, "Antes da ordenacao:");
	printf("%s", t8);
	printf("\n");
	t11 = m[4];
	printf("%d", t11);
	t9 = 0;
	L0:
		t10 = t9 < 4;
		if (!t10) goto L1;
		printf("%d", d0[t9]);
		t10 = t9 < 4 - 1;
		if (t10) printf(", ");
		t9 = t9 + 1;
		goto L0;
	L1:;
	printf("]\n");
	quick_sort_completo(d0, 4);
	t12 = (char*)malloc(21);
	strcpy(t12, "Depois da ordenacao:");
	printf("%s", t12);
	printf("\n");
	t15 = m[4];
	printf("%d", t15);
	t13 = 0;
	L2:
		t14 = t13 < 4;
		if (!t14) goto L3;
		printf("%d", d0[t13]);
		t14 = t13 < 4 - 1;
		if (t14) printf(", ");
		t13 = t13 + 1;
		goto L2;
	L3:;
	printf("]\n");

	/* Liberando memoria alocada neste escopo */
	if (d0 != NULL) free(d0);
	if (t12 != NULL) free(t12);
	if (t8 != NULL) free(t8);
}
}

