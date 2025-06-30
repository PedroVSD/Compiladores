/*Compilador DHP*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"algoritmos/quicksort.h"

int main(void)
{
//INÍCIO DO FOR
		void* d0;	 //a
		int t0;
		int t1;
		int t2;
		int t3;
		int t4;
		int t5;
		int t6;
		int t7;
		int t8;

		t0 = 0;
		t1 = 4;
		d0 = (int*)malloc(t1);
		((int*)d0)[0] = t0;
		goto ForTest_0;

		ForStep_0:
		t5 = 1;
		t6 = ((int*)d0)[0];
		t7 = t6 + t5;
		free(d0);
		t8 = 4;
		d0 = (int*)malloc(t8);
		((int*)d0)[0] = t7;

		ForTest_0:
		t2 = 5;
		t3 = ((int*)d0)[0];
		t4 = t3 < t2;
		if (!t4) goto ForEnd_0;

			printf("%d", ((int*)d0)[0]);
			printf("\n");

		goto ForStep_0;
		ForEnd_0:;
//FIM DO FOR

	
	return 0;
}

