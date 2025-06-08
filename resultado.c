/*Compilador DHP*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void output_int(int n) {
    if (n == 0) { printf("0"); return; }
    if (n < 0) { putchar('-'); n = -n; }
    if (n >= 10) output_int(n / 10);
    putchar((n % 10) + '0');
}


// Le um float caractere por caractere, em estilo 3-enderecos
double input_float() {
    double num = 0.0, divisor = 1.0;
    int sign = 1, in_fraction = 0;
    char c;
    // ... (declaração das suas flags temporárias int)

    // Ignora espacos em branco
input_float_ws_loop:
    scanf("%c", &c);
    if (c == ' ' || c == '\n') goto input_float_ws_loop;

    // Lida com o sinal
    if (c == '-') { sign = -1; scanf("%c", &c); }

read_float_loop:
    if (c == '.' && in_fraction == 0) {
        in_fraction = 1;
        scanf("%c", &c);
        goto read_float_loop;
    }
    if (c < '0' || c > '9') { goto read_float_end; }

    if (in_fraction == 0) {
        num = num * 10.0 + (c - '0');
    } else {
        divisor = divisor * 10.0;
        num = num + (double)(c - '0') / divisor;
    }
    scanf("%c", &c);
    goto read_float_loop;

read_float_end:;
    num = (double)sign * num;
    return num;
}


// Escreve um float caractere por caractere
void output_float(double n) {
    int parte_inteira;
    double parte_fracionaria;
    int digito_frac, i;

    if (n < 0) { putchar('-'); n = -n; }

    parte_inteira = (int)n;
    parte_fracionaria = n - parte_inteira;

    output_int(parte_inteira); // Reutiliza a função para imprimir a parte inteira
    putchar('.');

    i = 0;
loop_frac_start:
    if (i >= 6) goto loop_frac_end;
    parte_fracionaria = parte_fracionaria * 10.0;
    digito_frac = (int)parte_fracionaria;
    putchar(digito_frac + '0');
    parte_fracionaria = parte_fracionaria - digito_frac;
    i = i + 1;
    goto loop_frac_start;
loop_frac_end:;
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

int main(void)
{
	float d0;	 //a
	char* t0;

	d0 = input_float();
	t0 = "Variavel a vale: ";
	output_string(t0);
	printf(" ");
	output_float(d0);
	printf("\n");

	return 0;
}

