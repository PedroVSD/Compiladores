/*Compilador DHP*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"algoritmos/quicksort.h"

int teste(int* f0)
{
	int t0;
	int t1;
	return t1;
}

int main(void)
{
	int* d0;	 //a
	int t2;
	int t3;
	int t4;
	int t5;
	int t6;
	int t7;

	t2 = 5; //tamanho do array
	t3 = t2 * 4;
	d0 = (int*)malloc(t3);
	t4 = 0;
	t5 = 3;
	t6 = t4;
	d0[t6] = t5;
	t7 = teste(&d0);
	printf("%d", t7);
	printf("\n");

	
	return 0;
}

