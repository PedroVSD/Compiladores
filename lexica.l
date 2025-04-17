%{
#include <string>
#include "y.tab.h"

using namespace std;

extern YYSTYPE yylval;
%}

ESPACO [ \t]
DIGITO [0-9]
LETRA [A-Za-z_]

NUM_INTEIRO {DIGITO}+
NUM_PONTO {DIGITO}+"."{DIGITO}+

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

"("         { return '('; }
")"         { return ')'; }
"{"         { return '{'; }
"}"         { return '}'; }
";"         { return ';'; }

[ \t\n]+    { /* ignora espaços */ }

.           {
	printf("Caractere inválido: %s\n", yytext);
	return 0;
}

%%
