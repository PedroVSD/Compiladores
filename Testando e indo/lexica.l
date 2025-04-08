%{
#include <string>
#include "y.tab.h"

using namespace std;

%}

ESPACO [ \t]
DIGITO [0-9]
LETRA [A-Za-z_]

DELIM {ESPACO}+
NUM {DIGITO}+
ID {LETRA}({LETRA}|{DIGITO})*

%%

"main"      { return TK_MAIN; }
"int"       { return TK_TIPO_INT; }
"float"

{NUM}       { yylval.traducao = yytext; return TK_NUM; }
{ID}        { yylval.label = yytext; return TK_ID; }

"="         { return '='; }
[+\-*/]    { return *yytext; }

"("         { return '('; }
")"         { return ')'; }
"{"         { return '{'; }
"}"         { return '}'; }
";"         { return ';'; }

[ \t\n]+    { /* ignora espaço */ }

.           { printf("Caractere inválido: %s\n", yytext); return 0; }

%%
