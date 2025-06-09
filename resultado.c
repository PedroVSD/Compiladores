/*Compilador DHP*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(void)
{
	int d0;	 //opcao
	int t0;

	t0 = 2;
	d0 = t0;
	{
		int t2;
		int t3;
		int t5;
		int t6;
		char* t1;
		char* t4;
		char* t7;

			t2 = 1;
			t3 = d0 == t2;
			if (!t3) goto NextCase0_1;
		t1 = "Um";
		printf("%s", t1);
		printf("\n");
		goto EndSwitch0;
			goto EndSwitch0;
			NextCase0_1:
			t5 = 2;
			t6 = d0 == t5;
			if (!t6) goto NextCase0_2;
		t4 = "Dois";
		printf("%s", t4);
		printf("\n");
		goto EndSwitch0;
			goto EndSwitch0;
			NextCase0_2:
		t7 = "Outro";
		printf("%s", t7);
		printf("\n");
		goto EndSwitch0;
		EndSwitch0:
	}

	return 0;
}

