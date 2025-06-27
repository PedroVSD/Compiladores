/*Compilador DHP*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// Le um valor booleano da entrada
int input_bool() {
    char c;
    scanf("%c", &c);
    aux = c == 't';
    if (!aux) goto False;
    scanf("%c", &c);
    aux = c == 'r';
    if (!aux) goto False;
    scanf("%c", &c);
    aux = c == 'u';
    if (!aux) goto False;
    scanf("%c", &c);
    aux = c == 't';
    if (!aux) goto False;
    return 1;
False:
    return 0;
}

int main(void)
{
	int d0;	 //a

	d0 = input_bool();
	printf("%d", d0);
	printf("\n");

	
	return 0;
}

