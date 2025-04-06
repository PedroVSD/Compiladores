%{
#include <iostream>
#include <unordered_map>
#include <string>
#include <stack>
#include <FlexLexer.h>  // Inclusão do cabeçalho do Flex

#define MAIN 1001
#define IF 1002
#define FOR 1003
#define WHILE 1004
#define INT 1005
#define DOUBLE 1006
#define CHAR 1007
#define STRING 1008
#define BOOL 1009
#define PLUS 1010
#define LESS 1011
#define PROD 1012
#define DIVIDE 1013
#define EQUAL 1014
#define LEFT_PARE 1015
#define RIGHT_PARE 1016
#define LEFT_KEY 1017
#define RIGHT_KEY 1018
#define VAR 1019

using namespace std;

unordered_map<string , int> table;

int count_left_paren = 0;
int count_right_paren = 0;
int count_left_key = 0;
int count_right_key = 0;

extern FILE *yyin;  // Declaração da variável yyin

%}

%option c++

%%

"main"        { table["main"] = MAIN; }
"if"          { table["if"] = IF; }
"for"         { table["for"] = FOR; }
"while"       { table["while"] = WHILE; }
"int"         { table["int"] = INT; }
"double"      { table["double"] = DOUBLE; }
"char"        { table["char"] = CHAR; }
"string"      { table["string"] = STRING; }
"bool"        { table["bool"] = BOOL; }

[a-zA-Z_][a-zA-Z0-9_]* { 
    table[yytext] = VAR; 
}

\(          { 
    table["("] = LEFT_PARE; 
    count_left_paren++; 
}
\)          { 
    table[")"] = RIGHT_PARE; 
    count_right_paren++; 
}
\{          { 
    table["{"] = LEFT_KEY; 
    count_left_key++; 
}
\}          { 
    table["}"] = RIGHT_KEY; 
    count_right_key++; 
}

\=          { table["="] = EQUAL; }
\+          { table["+"] = PLUS; }
\-          { table["-"] = LESS; }
\*          { table["*"] = PROD; }
\/          { table["/"] = DIVIDE; }

[ \t\n]      { /* Ignora espaços em branco e quebras de linha */ }

.|\n { /* Ignora outros caracteres */ }

%%

bool conta_simbolos(int count_left_paren, int count_right_paren, int count_left_key, int count_right_key) {
    return count_left_paren == count_right_paren && count_left_key == count_right_key;
}

int yywrap() {
    return 1;  // Retorna 1 para indicar que o arquivo terminou
}

int main() {
    yyin = stdin;  // Define a entrada como stdin
    yylex();        // Chama o analisador léxico

    // Exibe um exemplo de variável mapeada
    cout << "Var token: " << table["var"] << endl;

    if (conta_simbolos(count_left_paren, count_right_paren, count_left_key, count_right_key)) {
        cout << "Símbolos balanceados" << endl;
    } else {
        cout << "Símbolos não balanceados" << endl;
    }

    return 0;
}
