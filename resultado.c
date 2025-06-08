/*Compilador DHP*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int Len(const char* str) {
    int len, f0, f1, f2;
    len = 0;
    f0 = str == NULL;
    if (f0) goto loop_end_len;
loop_start_len:
    f1 = str[len];
    f2 = f1 == '\0';
    if (f2) goto loop_end_len;
    len = len + 1;
    goto loop_start_len;
loop_end_len:;
    return len;
}


void output_string(const char* s) {
    int i = 0;
    int flag_null = s == NULL;
    if (flag_null) goto output_str_end;
output_str_loop_start:
    char c = s[i];
    int flag_fim = c == '\0';
    if (flag_fim) goto output_str_end;
    putchar(c);
    i = i + 1;
    goto output_str_loop_start;
output_str_end:;
}


// Le uma string da entrada ate o espaco ou nova linha
char* input_string() {
    int capacity = 16;
    int len = 0;
    char* buffer = (char*)malloc(capacity);
    char c;
    int scanf_result, flag_is_terminator, flag_is_newline, flag_is_space, flag_is_full;
    if (buffer == NULL) { fprintf(stderr, "Falha na alocacao inicial para input_string\n"); exit(1); }

input_str_loop_start:
    scanf_result = scanf("%c", &c);
    flag_is_terminator = scanf_result != 1;
    if (flag_is_terminator) goto input_str_loop_end;
    flag_is_newline = c == '\n';
    flag_is_space = c == ' ';
    flag_is_terminator = flag_is_newline || flag_is_space;
    if (flag_is_terminator) goto input_str_loop_end;

    buffer[len] = c;
    len = len + 1;

    flag_is_full = len >= capacity;
    if (!flag_is_full) goto input_str_loop_start;

    capacity = capacity * 2;
    buffer = (char*)realloc(buffer, capacity);
    if (buffer == NULL) { fprintf(stderr, "Falha na realocacao de memoria para input_string\n"); exit(1); }
    goto input_str_loop_start;

input_str_loop_end:;
    buffer[len] = '\0';
    return buffer;
}

int main(void)
{
	char* d0;	 //s1
	char* d1;	 //s2
	char* d2;	 //s3
	int t1;
	char* t10;
	int t2;
	int t3;
	int t4;
	char* t5;
	int t6;
	int t7;
	int t8;
	int t9;
	char* t0;

	// AVISO: Se 's1' ja continha uma string, a memoria antiga pode vazar.
	d0 = input_string();
	// AVISO: Se 's2' ja continha uma string, a memoria antiga pode vazar.
	d1 = input_string();
	t0 = " ";
	t1 = Len(d0);
	t2 = Len(t0);
	t3 = t1 + t2;
	t4 = t3 + 1;
	t5 = (char*)malloc(t4);
	strcpy(t5, d0);
	strcat(t5, t0);
	t6 = Len(t5);
	t7 = Len(d1);
	t8 = t6 + t7;
	t9 = t8 + 1;
	t10 = (char*)malloc(t9);
	strcpy(t10, t5);
	strcat(t10, d1);
	d2 = t10;
	output_string(d0);
	printf("\n");
	output_string(d1);
	printf("\n");
	output_string(d2);
	printf("\n");

	return 0;
}

