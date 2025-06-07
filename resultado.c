/*Compilador DHP*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int Len(const char* str)
{
	int len;
	int f0;
	int f1;
	int f2;	

	len = 0;
	f0 =  str == NULL;
    if (f0) goto loop_end_len;

loop_start_len:

    f1 = str[len];
	f2 = str[len] == '\0';
    if (f2) goto loop_end_len;
    len = len + 1;
    goto loop_start_len;

loop_end_len:

    return len;
}

int main(void)
{
	char* d0;	 //a
	char* d1;	 //b
	char* d2;	 //c
	int t2;
	int t3;
	int t4;
	int t5;
	char* t6;
	char* t0;
	char* t1;

	t0 = "a";
	d0 = t0;
	t1 = "b";
	d1 = t1;
	t2 = Len(d0);
	t3 = Len(d1);
	t4 = t2 + t3;
	t5 = t4 + 1;
	t6 = (char*)malloc(t5);
	strcpy(t6, d0);
	strcat(t6, d1);
	d2 = t6;

	return 0;
}

