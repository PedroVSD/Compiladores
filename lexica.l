%{
#include <string>
#include "y.tab.h"
int numLinha = 1;

using namespace std;

extern YYSTYPE yylval;
%}

ESPACO [\t]
DIGITO [0-9]
LETRA [A-Za-z_]

NUM_INTEIRO -?{DIGITO}+
NUM_PONTO -?{DIGITO}+"."{DIGITO}+
STRING_LITERAL \"[^\"\n]*\"


ID {LETRA}({LETRA}|{DIGITO})*

%%

"int main"      { return TK_MAIN;}
"int"       { return TK_TIPO_INT;}
"float"     { return TK_TIPO_FLOAT;}
"char"      { return TK_TIPO_CHAR;}
"bool"      { return TK_TIPO_BOOL;}
"string"    { return TK_TIPO_STRING; }
"if"        { return TK_IF; }
"else"      { return TK_ELSE; }
"while"     { return TK_WHILE; }
"do"        { return TK_DO; }
"for"       { return TK_FOR; }

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

{STRING_LITERAL} {
    string s = yytext;
    // Remove as aspas do valor para yylval.label, mas mantém em traducao para o C
    yylval.label = s.substr(1, s.length() - 2);
    yylval.traducao = yytext; // Ex: "\"ola\"" (para o código C)
    return TK_STRING_LITERAL;
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

[ \t]+    { /* ignora espaços */}
\n 	   { numLinha++; }
.           {
	//printf("Caractere inválido: %s\n", yytext);
	printf("Erro léxico: Caractere inválido '%s' na linha %d\n", yytext, numLinha);
	return 0;
}

%%
