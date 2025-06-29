/*Compilador DHP*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"algoritmos/quicksort.h"

struct teste {
	int x;
	int y;
};

void D() //Resolve o Problema da atribuição 
{


}

int main(void)
{
	struct teste d0;	 //haduken
	int d1;	 //resultado
	int t0;
	int t1;
	int t2;
	int t3;
	int t4;

	t0 = 1;
	d0.x = t0;
	t1 = 9;
	d0.y = t1;
	t2 = d0.x;
	t3 = d0.y;
	t4 = t2 + t3;
	d1 = t4;
	printf("%d", d1);
	printf("\n");

	
	return 0;
}

