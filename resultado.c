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
	char* d0;	 //s
	char* d1;	 //t
	int t10;
	int t11;
	char* t12;
	int t3;
	int t4;
	int t5;
	int t6;
	char* t7;
	int t8;
	int t9;
	char* t0;
	char* t1;
	char* t2;
	char* d2;	 //u

	t0 = "Hello";
	d0 = t0;
	t1 = "World";
	d1 = t1;
	t2 = " ";
	t3 = Len(d0);
	t4 = Len(t2);
	t5 = t3 + t4;
	t6 = t5 + 1;
	t7 = (char*)malloc(t6);
	strcpy(t7, d0);
	strcat(t7, t2);
	t8 = Len(t7);
	t9 = Len(d1);
	t10 = t8 + t9;
	t11 = t10 + 1;
	t12 = (char*)malloc(t11);
	strcpy(t12, t7);
	strcat(t12, d1);
	d2 = t12;

	return 0;
}

