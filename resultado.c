/*Compilador DHP*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
	int d0;	 //i
	int t0;
int main(void)
	{
		int t2;
		int t1;
		int t7;
		int d1;	 //x

	t0 = 0;
	d0 = t0;

		BeginWhile0:
		t1 = 10;
		t2 = d0 < t1;
			if (!t2) goto EndWhile0;
		{
			int t6;
			int t5;


			{
				int t4;
				int t3;

				t3 = 5;
				t4 = (d0 == t3);
				if (!t4) goto EndIf1;
				{
					goto EndWhile0;
				}
				EndIf1:

			}
			t5 = 1;
			t6 = d0 + t5;
			d0 = t6;
		}
			goto BeginWhile0;
		EndWhile0:;
		t7 = 0;
		d1 = t7;

		{
			int d2;	 //i
			int t10;
			int t12;
			int t11;
			int t8;
			int t9;

			t8 = 0;
			d2 = t8;
			goto ForTest_2;

			ForStep_2:
			t11 = 1;
			t12 = d2 + t11;
			d2 = t12;

			ForTest_2:
			t9 = 5;
			t10 = d2 < t9;
			if (!t10) goto ForEnd_2;

			{
				int t16;
				int t15;


				{
					int t14;
					int t13;

					t13 = 2;
					t14 = (d2 == t13);
					if (!t14) goto EndIf3;
					{
						goto ForStep_2;
					}
					EndIf3:

				}
				t15 = 1;
				t16 = d1 + t15;
				d1 = t16;
			}

			goto ForStep_2;
			ForEnd_2:;
		}
	}

