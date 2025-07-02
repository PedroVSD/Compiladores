/*Compilador DHP*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"algoritmos/quicksort.h"

int sum(int* f0,int f1)
{
	void* d0;	 //soma
	int t0;
	int t1;
	int t15;

	t0 = 0;
	t1 = 4;
	d0 = (int*)malloc(t1);
	((int*)d0)[0] = t0;
//INÍCIO DO FOR
		void* d1;	 //i
		int t10;
		int t11;
		int t12;
		int t13;
		int t14;
		int t2;
		int t3;
		int t4;
		int t5;
		int t6;
		int t7;
		int t8;
		int t9;

		t2 = 0;
		t3 = 4;
		d1 = (int*)malloc(t3);
		((int*)d1)[0] = t2;
		goto ForTest_0;

		ForStep_0:
		t6 = 1;
		t7 = ((int*)d1)[0];
		t8 = t7 + t6;
		free(d1);
		t9 = 4;
		d1 = (int*)malloc(t9);
		((int*)d1)[0] = t8;

		ForTest_0:
		t4 = ((int*)d1)[0];
		t5 = t4 < f1;
		if (!t5) goto ForEnd_0;

			t11 = ((int*)d1)[0];
			t10 = f0[t11];
			t12 = ((int*)d0)[0];
			t13 = t12 + t10;
			free(d0);
			t14 = 4;
			d0 = (int*)malloc(t14);
			((int*)d0)[0] = t13;

		goto ForStep_0;
		ForEnd_0:;
//FIM DO FOR
	t15 = ((int*)d0)[0];
	return t15;
	free(d0);
}

int main(void)
{
	int* d3;	 //a
	int t16;
	int t17;
	int t18;
	int t19;
	int t31;
	int t32;
	int t33;
	void* d2;	 //tamanho
	void* d5;	 //total

	scanf("%d", &t16);
	t17 = 4;
	d2 = (int*)malloc(t17);
	((int*)d2)[0] = t16;
	t18 = ((int*)d2)[0];
	t19 = t18 * 4;
	d3 = (int*)malloc(t19);
//INÍCIO DO FOR
		void* d4;	 //i
		int t20;
		int t21;
		int t22;
		int t23;
		int t24;
		int t25;
		int t26;
		int t27;
		int t28;
		int t29;
		int t30;

		t20 = 0;
		t21 = 4;
		d4 = (int*)malloc(t21);
		((int*)d4)[0] = t20;
		goto ForTest_1;

		ForStep_1:
		t25 = 1;
		t26 = ((int*)d4)[0];
		t27 = t26 + t25;
		free(d4);
		t28 = 4;
		d4 = (int*)malloc(t28);
		((int*)d4)[0] = t27;

		ForTest_1:
		t22 = ((int*)d4)[0];
		t23 = ((int*)d2)[0];
		t24 = t22 < t23;
		if (!t24) goto ForEnd_1;

			scanf("%d", &t29);
			t30 = ((int*)d4)[0];
			d3[t30] = t29;

		goto ForStep_1;
		ForEnd_1:;
//FIM DO FOR
	t31 = ((int*)d2)[0];
	t32 = sum(d3, t31);
	t33 = 4;
	d5 = (int*)malloc(t33);
	((int*)d5)[0] = t32;
	printf("%d", ((int*)d5)[0]);
	printf("\n");

	free(d3);
free(d2);
free(d5);

	return 0;
}

