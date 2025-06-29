/*Compilador DHP*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"algoritmos/quicksort.h"

int main(void)
{
	int* d0;	 //a
	int t0;
	int t1;
	int t2;
	int t3;

	t2 = t0 * t1;
	t3 = t0 * 4;
	d0 = (int*)malloc(t3);

	{
		int d1;	 //i
		int t4;
		int t5;
		int t6;
		int t7;
		int t8;

		t4 = 0;
		d1 = t4;
		goto ForTest_0;

		ForStep_0:
		t7 = 1;
		t8 = d1 + t7;
		d1 = t8;

		ForTest_0:
		t5 = 2;
		t6 = d1 < t5;
		if (!t6) goto ForEnd_0;


			{
				int d2;	 //j
				int t10;
				int t11;
				int t12;
				int t13;
				int t14;
				int t15;
				int t16;
				int t9;

				t9 = 0;
				d2 = t9;
				goto ForTest_1;

				ForStep_1:
				t12 = 1;
				t13 = d2 + t12;
				d2 = t13;

				ForTest_1:
				t10 = 2;
				t11 = d2 < t10;
				if (!t11) goto ForEnd_1;

					t14 = d1 + d2;
					t15 = d1 * 2;
					t16 = t15 + d2;
					d0[t16] = t14;

				goto ForStep_1;
				ForEnd_1:;
			}

		goto ForStep_0;
		ForEnd_0:;
	}

	{
		int d3;	 //i
		int t17;
		int t18;
		int t19;
		int t20;
		int t21;

		t17 = 0;
		d3 = t17;
		goto ForTest_2;

		ForStep_2:
		t20 = 1;
		t21 = d3 + t20;
		d3 = t21;

		ForTest_2:
		t18 = 2;
		t19 = d3 < t18;
		if (!t19) goto ForEnd_2;


			{
				int d4;	 //j
				int t22;
				int t23;
				int t24;
				int t25;
				int t26;
				int t27;
				int t28;
				int t29;

				t22 = 0;
				d4 = t22;
				goto ForTest_3;

				ForStep_3:
				t25 = 1;
				t26 = d4 + t25;
				d4 = t26;

				ForTest_3:
				t23 = 2;
				t24 = d4 < t23;
				if (!t24) goto ForEnd_3;

					t27 = d3 * 2;
					t28 = t27 + d4;
					t28 = d0[t28];
					printf("%d", t28);
					printf("\n");

				goto ForStep_3;
				ForEnd_3:;
			}

		goto ForStep_2;
		ForEnd_2:;
	}

	
	return 0;
}

