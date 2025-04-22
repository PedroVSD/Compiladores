%{
#include <string>
#include "y.tab.h"
int numLinha = 1;

using namespace std;

extern YYSTYPE yylval;
%}

ESPACO [ \t]
DIGITO [0-9]
LETRA [A-Za-z_]

NUM_INTEIRO -?{DIGITO}+
NUM_PONTO -?{DIGITO}+"."{DIGITO}+


ID {LETRA}({LETRA}|{DIGITO})*

%%

"main"      { return TK_MAIN;}
"int"       { return TK_TIPO_INT;}
"float"     { return TK_TIPO_FLOAT;}
"char"      { return TK_TIPO_CHAR;}
"bool"      { return TK_TIPO_BOOL;}


"true"      {
	yylval.traducao = "true";
	yylval.label = "true";
	return TK_BOOL_TRUE;
}

"false"     {
	yylval.traducao = "false";
	yylval.label = "false";
	return TK_BOOL_FALSE;
}

\'[^\']\'   {
	yylval.traducao = yytext;
	yylval.label = yytext;
	return TK_CHAR;
}

{NUM_PONTO} {
	yylval.traducao = yytext;
	yylval.label = yytext;
	return TK_NUM;
}

{NUM_INTEIRO} {
	yylval.traducao = yytext;
	yylval.label = yytext;
	return TK_NUM;
}

{ID} {
	yylval.label = yytext;
	return TK_ID;
}

"="         { return '='; }
[+\-*/]     { return *yytext; }
"=="        { return TK_IGUAL; }
"!="        { return TK_DIFERENTE; }
"<"         { return '<'; }
"<="        { return TK_MENOR_IGUAL; }
">"         { return '>'; }
">="        { return TK_MAIOR_IGUAL; }

"&&"       { return TK_AND; }
"||"        { return TK_OR; }
"!"        	{ return '!'; }

"("         { return '('; }
")"         { return ')'; }
"{"         { return '{'; }
"}"         { return '}'; }
";"         { return ';'; }

[ \t\n]+    { /* ignora espaços */ numLinha++;}

.           {
	//printf("Caractere inválido: %s\n", yytext);
	printf("Erro léxico: Caractere inválido '%s' na linha %d\n", yytext, numLinha);
	return 0;
}

%%
