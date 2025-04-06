%{
    #include <iostream>
    #include <cstdio>
    #include <sstream>
    #include <string>
    #include <variant>
    #include <unordered_map>
    #include <map>

    #define YYSTYPE atributos

    using namespace std;

    int vat_temp_qnt;
    enum Type{
        INT,
        FLOAT,
        CHAR,
        BOOL,
        STRING
    };

    /*using Tipo_var = variant<int, float, char*, bool>;*/

    struct atributos{
        string nome;
        string label;
        string traducao;
        Type tipo;
    };

    map<string, atributos> tabela_simbolos;
    
    string gentempcode()
    int yylex(void);
    void yyerror(char *msg);
%}


/*Tipos*/

%token INT_TK
%token FLOAT_TK
%token CHAR_TK
%token BOOL_TK
%token STRING_TK
%token TK_ATRIBUTO

/*Simbolos e operadores*/

%token PLUS_TK
%token LESS_TK
%token PROD_TK
%token DIVIDE_TK
%token EQUAL_EQUAL_TK
%token NOT_EQUAL_TK
%token AND_TK
%token OR_TK
%token NOT_TK
%token ATRIBUICAO_TK
%token INCREMENT_TK
%token DECREMENT_TK

/*Palavras*/
%token MAIN_TK
%token IF_TK
%token WHILE_TK
%token FOR_TK
%token VAR


%token INICIO_LINHA_TK
%token FIM_LINHA_TK



%start INICIO

%left PLUS_TK LESS_TK
%left PROD_TK DIVIDE_TK


%%

INICIO          : INT_TK MAIN_TK '(' ')' BLOCO
                {
                    string codigo = "/*Compilador DHP*/\n"
                                            "#include <stdio.h>\n"
                                            "#include <iostream>\n"
                                            "int main();"

                    codigo += $5.traducao;

                    codigo += "\treturn 0;\n"
                                "}\n";

                    cout << codigo << endl;
                }
                ;


BLOCO           : '{' COMANDOS '}'
                {   
                    $$.traducao = $2.traducao;   
                }
                ;

COMANDOS        :   COMANDO COMANDOS
                {
                    $$.traducao = $1.traducao;
                }   
                | 
                {
                    $$.traducao = "";
                }
    ;

COMANDO         : E ';'
                {
                    $$ = $1;
                }
                ;

E 			: E '+' E
			{
				$$.label = gentempcode();
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + 
					" = " + $1.label + " + " + $3.label + ";\n";
			}
			| E '-' E
			{
				$$.label = gentempcode();
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + 
					" = " + $1.label + " - " + $3.label + ";\n";
			}
			| VAR '=' E
			{
				$$.traducao = $1.traducao + $3.traducao + "\t" + $1.label + " = " + $3.label + ";\n";
			}
			| INT_TK
			{
				$$.label = gentempcode();
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
			}
			| VAR
			{
				$$.label = gentempcode();
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
			}
			;
%%
#include "lex.yy.c"

int yyparse();

string gentempcode()
{
	var_temp_qnt++;
	return "t" + to_string(var_temp_qnt);
}


int main(int argc, char **argv){
    return yyparse();
}

/*Função de erro do bison*/
void yyerror(char *msg){
    fprintf(stderr, "erro: %s\n", msg);
    cerr << "erro: " << msg << endl;
}