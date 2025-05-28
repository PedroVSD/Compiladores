%{
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>

#define YYSTYPE atributos

using namespace std;



void adicionaVar(string nome, string tipo, bool temp = false);
stringstream veririficarTipo(string var1, string operador, string var2 = "");

int tempVar = 0;
int defVar = 0;
int defbloco = 0;

struct atributos {
	string label;
	string traducao;
};

struct tabela{
	string tipo;
	string endereco_memoria;
	bool temporaria;
};

map<string, tabela> tabela_simbolos;

extern int numLinha;
int yylex(void);
void yyerror(string);
%}

%token TK_NUM TK_ID TK_TIPO_INT TK_TIPO_FLOAT TK_MAIN
%token TK_TIPO_CHAR TK_TIPO_BOOL
%token TK_IGUAL TK_DIFERENTE TK_MAIOR_IGUAL TK_MENOR_IGUAL
%token TK_AND TK_OR
%token TK_CHAR TK_BOOL_TRUE TK_BOOL_FALSE


%start S

%left TK_OR
%left TK_AND
%nonassoc TK_IGUAL TK_DIFERENTE
%left '<' '>' TK_MAIOR_IGUAL TK_MENOR_IGUAL
%left '+' '-'
%left '*' '/'
%right UMINUS '!'
%nonassoc '(' ')'

%%

S:
	INICIO
	{
		cout << "/*Compilador DHP*/\n";
		cout << "\n#include<string.h>\n#include<stdio.h>\n";		cout << $1.traducao;
	}
;
INICIO:
	COMANDOS MAIN
	{
		$$.traducao = $1.traducao + $2.traducao;
	}
	| COMANDOS
	{
		$$.traducao = $1.traducao;
	}
	;
MAIN:
	TK_MAIN '(' ')' BLOCO {

		stringstream ss;
		ss << "int main(void)\n{\n";

		for (const auto& [nome, info] : tabela_simbolos) {
			string tipo = (info.tipo == "bool") ? "int" : info.tipo;
			if (!(info.temporaria)) {
    			ss << "\t" << tipo  << " " << info.endereco_memoria << ";\t //Variavel: "<< nome << "\n";}
			else {
				ss << "\t" << tipo << " " << info.endereco_memoria << ";\n";}
		}

		ss << "\n" << $4.traducao << "\n";
		ss << "\treturn 0;\n}\n";

		$$.traducao = ss.str();
	  }
;

BLOCO: '{' COMANDOS '}' {
	$$.traducao = $2.traducao;
}
;

COMANDOS:
	COMANDO COMANDOS {
		$$.traducao = $1.traducao + $2.traducao;
	}
	| /* vazio */ {
		$$.traducao = "";
	}
;

COMANDO:
	  DECLARACAO ';' { $$.traducao = $1.traducao; }
	| ATRIB ';'      { $$.traducao = $1.traducao; }
	| EXPR ';'       { $$.traducao = $1.traducao; }
;

DECLARACAO:
      DECLAR_VAR {
        $$.traducao = $1.traducao;
      }
;

TIPO:
      TK_TIPO_INT   { $$.label = "int"; }
    | TK_TIPO_FLOAT { $$.label = "float"; }
    | TK_TIPO_CHAR  { $$.label = "char"; }
    | TK_TIPO_BOOL  { $$.label = "bool"; }
;

DECLAR_VAR:
      TIPO TK_ID {
        adicionaVar($2.label, $1.label);
        $$.traducao = "";
      }
    | TIPO TK_ID '=' EXPR {
        adicionaVar($2.label, $1.label);
        stringstream ss;
		ss = veririficarTipo($2.label, "=", $4.label);
        $$.traducao = $4.traducao + ss.str();
      }
    | TIPO TK_ID '=' TK_CHAR {
        adicionaVar($2.label, $1.label);
        stringstream ss;
        ss << "\t" << tabela_simbolos[$2.label].endereco_memoria << " = " << $4.label << ";\n";
        $$.traducao = ss.str();
      }
;

ATRIB: TK_ID '=' EXPR {
	if (tabela_simbolos.find($1.label) == tabela_simbolos.end()) {
		cout << "Erro: Variável " << $1.label << " não declarada.\n";
		exit(1);
	}
        stringstream ss;
		ss = veririficarTipo($1.label, "=", $3.label);
        $$.traducao = $3.traducao + ss.str();
}

;

EXPR:
	| EXPR_LOG %prec TK_OR {
		$$.traducao = $1.traducao;
	}
;
EXPR_ARIT:
	EXPR_ARIT '+' EXPR_TERM %prec '+' {
		stringstream ss;
		string var1 = $1.label;
		string var2 = $3.label;
		ss = veririficarTipo(var1, "+", var2);
		$$.label = "t" + to_string(tempVar-1);
		$$.traducao = $1.traducao + $3.traducao + ss.str();
	}
	| EXPR_ARIT '-' EXPR_TERM %prec '-' {
		stringstream ss;
		string var1 = $1.label;
		string var2 = $3.label;
		ss = veririficarTipo(var1, "-", var2);
		$$.label = "t" + to_string(tempVar-1);
		$$.traducao = $1.traducao + $3.traducao + ss.str();

	}
	| EXPR_TERM {
		$$. label = $1.label;
		$$.traducao = $1.traducao;
	}
;
EXPR_TERM:
		EXPR_TERM '*' EXPR_ATOM %prec '*' {
		stringstream ss;
		string var1 = $1.label;
		string var2 = $3.label;
		ss = veririficarTipo(var1, "*", var2);
		$$.label = "t" + to_string(tempVar-1);
		$$.traducao = $1.traducao + $3.traducao + ss.str();
	}
	| EXPR_TERM '/' EXPR_ATOM %prec '/' {
		stringstream ss;
		string var1 = $1.label;
		string var2 = $3.label;
		ss = veririficarTipo(var1, "/", var2);
		$$.label = "t" + to_string(tempVar-1);
		$$.traducao = $1.traducao + $3.traducao + ss.str();
	}
	| EXPR_ATOM {
		$$.label = $1.label;
		$$.traducao = $1.traducao;
	}

;

EXPR_LOG:
	EXPR_LOG TK_AND EXPR_REL %prec TK_AND {
		stringstream ss;
		ss = veririficarTipo($1.label, "&&", $3.label);
		$$.label = "t" + to_string(tempVar-1);
		$$.traducao = $1.traducao + $3.traducao + ss.str();
	}
	| EXPR_LOG TK_OR EXPR_REL %prec TK_OR {
		stringstream ss;
		ss = veririficarTipo($1.label, "||", $3.label);
		$$.label = "t" + to_string(tempVar-1);
		$$.traducao = $1.traducao + $3.traducao + ss.str();
	}
	| EXPR_REL {
		$$.label = $1.label;
		$$.traducao = $1.traducao;
	}
;
EXPR_REL:
	EXPR_REL TK_IGUAL EXPR_REL %prec TK_IGUAL {
		stringstream ss;
		ss = veririficarTipo($1.label, "==", $3.label);
		$$.label = "t" + to_string(tempVar-1);
		$$.traducao = $1.traducao + $3.traducao + ss.str();
	}
	| EXPR_REL TK_DIFERENTE EXPR_REL %prec TK_DIFERENTE {
		stringstream ss;
		ss = veririficarTipo($1.label, "!=", $3.label);
		$$.label = "t" + to_string(tempVar-1);
		$$.traducao = $1.traducao + $3.traducao + ss.str();
	}
	| EXPR_REL '>' EXPR_REL %prec '>' {
		stringstream ss;
		ss = veririficarTipo($1.label, ">", $3.label);
		$$.label = "t" + to_string(tempVar-1);
		$$.traducao = $1.traducao + $3.traducao + ss.str();
	}
	| EXPR_REL '<' EXPR_REL %prec '<' {
		stringstream ss;	
		ss = veririficarTipo($1.label, "<", $3.label);
		$$.label = "t" + to_string(tempVar-1);		
		$$.traducao = $1.traducao + $3.traducao + ss.str();
	}
	| EXPR_REL TK_MAIOR_IGUAL EXPR_REL %prec TK_MAIOR_IGUAL {
		stringstream ss;
		ss = veririficarTipo($1.label, ">=", $3.label);
		$$.label = "t" + to_string(tempVar-1);
		$$.traducao = $1.traducao + $3.traducao + ss.str();
	}
	| EXPR_REL TK_MENOR_IGUAL EXPR_REL %prec TK_MENOR_IGUAL {
		stringstream ss;
		ss = veririficarTipo($1.label, "<=", $3.label);
		$$.label = "t" + to_string(tempVar-1);
		$$.traducao = $1.traducao + $3.traducao + ss.str();
	}
	| EXPR_NOT {
		$$.label = $1.label;
		$$.traducao = $1.traducao;
	}
;
EXPR_NOT:
	'!' EXPR_NOT %prec '!' {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << "\t" << temp << " = !" << tabela_simbolos[$2.label].endereco_memoria << ";\n";
		$$.label = temp;
		$$.traducao = $2.traducao + ss.str();
		adicionaVar(temp, "bool", true);
	}
	| EXPR_ARIT {
		$$.label = $1.label;
		$$.traducao = $1.traducao;
	}
;
EXPR_ATOM:
	'(' EXPR ')'  %prec '(' {
		$$.label = $2.label;
		$$.traducao = $2.traducao;
	}
	| '-' EXPR_ATOM %prec UMINUS {
	string temp = "t" + to_string(tempVar);
	stringstream ss;
	ss << "\t" << temp << " = -" << $2.label << ";\n";
	$$.label = temp;
	$$.traducao = $2.traducao + ss.str();

	// Inferir tipo baseado em $2
	string tipo = tabela_simbolos[$2.label].tipo;
	adicionaVar(temp, tipo, true);
	}
	| TK_NUM {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << "\t" << temp << " = " << $1.traducao << ";\n";
		$$.label = temp;
		$$.traducao = ss.str();

		// Inferir tipo
		string tipo = ($1.traducao.find('.') != string::npos) ? "float" : "int";
					

		adicionaVar(temp, tipo, true);
	}
	| TK_ID {
		if (tabela_simbolos.find($1.label) == tabela_simbolos.end()) {
			cout << "Erro: Variável " << $1.label << " não declarada.\n";
			exit(1);
		}
		$$.label = $1.label;
		$$.traducao = "";
	}
	| COVERT_TYPE {
		$$.label = $1.label;
		$$.traducao = $1.traducao;
	}
	| TK_BOOL_TRUE {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << "\t" << temp << " = 1;\n";
		$$.label = temp;
		$$.traducao = ss.str();
		adicionaVar(temp, "bool", true);
	}
	| TK_BOOL_FALSE {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << "\t" << temp << " = 0;\n";
		$$.label = temp;
		$$.traducao = ss.str();
		adicionaVar(temp, "bool", true);
	}
;
COVERT_TYPE:
	TK_TIPO_INT '(' EXPR ')' {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << "\t" << temp << " = (int)" << tabela_simbolos[$3.label].endereco_memoria << ";\n";
		$$.label = temp;
		$$.traducao = $3.traducao + ss.str();
		adicionaVar(temp, "int", true);
	}
	| TK_TIPO_FLOAT '(' EXPR ')' {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << "\t" << temp << " = (float)" << tabela_simbolos[$3.label].endereco_memoria << ";\n";
		$$.label = temp;
		$$.traducao = $3.traducao + ss.str();
		adicionaVar(temp, "float", true);
	}
;
%%

#include "lex.yy.c"

int yyparse();

int main(int argc, char* argv[]) {
	yyparse();
	return 0;
}

void yyerror(string MSG) {
	cout << "Erro sintático: " << MSG << " na linha: " << numLinha << endl;
	exit(1);
}

void adicionaVar(string nome, string tipo, bool temp) {
	if (tabela_simbolos.find(nome) == tabela_simbolos.end()) {
		tabela_simbolos[nome].tipo = tipo;
		tabela_simbolos[nome].temporaria = temp;
		if (temp) {
			tabela_simbolos[nome].endereco_memoria = "t" + to_string(tempVar++);
		} else {
			tabela_simbolos[nome].endereco_memoria = "d" + to_string(defVar++);
		}
	} else {
		cout << "Erro: Variável " << nome << " já declarada." << endl;
		exit(1);
	}
}

stringstream veririficarTipo(string var1, string operador, string var2) {
	stringstream ss;
	string tipo1 = tabela_simbolos[var1].tipo;
	string tipo2 = tabela_simbolos[var2].tipo;
	string endereco1 = tabela_simbolos[var1].endereco_memoria;
	string endereco2 = tabela_simbolos[var2].endereco_memoria;
	
	if(operador == "="){
		if(tipo1 != tipo2){
			if(tipo1 == "int" && tipo2 == "float"){
				ss << "\t" << endereco1 << " = (int)" << endereco2 << ";\n";
			}
			else if(tipo1 == "float" && tipo2 == "int"){
				ss << "\t" << endereco1 << " = (float)" << endereco2 << ";\n";
			}
			else{
				cout << "Erro: Tipos incompatíveis para atribuição da variavel: " << var1 << "\n" ;
				exit(1);
			}
		}
		else{
			ss << "\t" << endereco1 << " = " << endereco2 << ";\n";
		}
		return ss;
	}	
	else if(operador == "+" || operador == "-" || operador == "*" || operador == "/"){		
		if(tipo1 != tipo2){
			string result_tipo = (tipo1 == "float" || tipo2 == "float") ? "float" : "int";
			string temp = "t" + to_string(tempVar);
			adicionaVar(temp, result_tipo, true);
			string temp2 = "t" + to_string(tempVar);
			adicionaVar(temp2, result_tipo, true);

			if(tipo1 == "int" && tipo2 == "float"){
				ss << "\t" << temp << " = (float)" << endereco1 << ";\n";
				ss << "\t" << temp2 << " = " << temp << " " << operador << " " << endereco2 << ";\n";
			}
			else if(tipo1 == "float" && tipo2 == "int"){
				ss << "\t" << temp << " = (float)" << endereco2 << ";\n";
				ss << "\t" << temp2 << " = " << temp << " " << operador << " " << endereco1 << ";\n";
			}
			else{
				cout << "Erro: Tipos incompatíveis para operação " << operador << ".\n";
				exit(1);
			}
		}
		else{
			string temp = "t" + to_string(tempVar);
			adicionaVar(temp, tipo1, true);
			ss << "\t" << temp << " = " << endereco1 << " " << operador << " " << endereco2 << ";\n";
		}
	}
	else if(operador == "||" || operador == "&&"){
		if(tipo1 != "bool" || tipo2 != "bool"){
			cout << "Erro: Operador lógico " << operador << " só pode ser usado com tipos booleanos.\n";
			exit(1);
		}
		string temp = "t" + to_string(tempVar);
		adicionaVar(temp, "bool", true);
		ss << "\t" << temp << " = " << endereco1 << " " << operador << " " << endereco2 << ";\n";
	}

	else if(operador == "==" || operador == "!="){
		if(tipo1 != tipo2){
			if(tipo1 == "int" && tipo2 == "float"){
				string temp = "t" + to_string(tempVar);
				adicionaVar(temp, "bool", true);
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, "bool", true);
				ss << "\t" << temp << " = (float)" << endereco1 << ";\n";
				ss << "\t" << temp2 << " = " << temp << " " << operador << " " << endereco2 << ";\n";
			}
			else if(tipo1 == "float" && tipo2 == "int"){
				string temp = "t" + to_string(tempVar);
				adicionaVar(temp, "bool", true);
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, "bool", true);
				ss << "\t" << temp << " = (float)" << endereco2 << ";\n";
				ss << "\t" << temp2 << " = " << temp << " " << operador << " " << endereco1 << ";\n";
			}
			else{
				cout << "Erro: Tipos incompatíveis para operação de comparação.\n";
				exit(1);
			}
		}
		else{
			string temp = "t" + to_string(tempVar);
			adicionaVar(temp, "bool", true);
			ss << "\t" << temp << " = ("<< endereco1 <<" "<< operador <<" "<< endereco2<<");\n";
		}
	}

	else if(operador == ">" || operador == "<" || operador == ">=" || operador == "<="){
		if(tipo1 != tipo2){
			if(tipo1 == "int" && tipo2 == "float"){
				string temp = "t" + to_string(tempVar);
				adicionaVar(temp, "bool", true);
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, "bool", true);
				ss << "\t" << temp << " = (float)" << endereco1 << ";\n";
				ss << "\t" << temp2 << " = " << temp << " " << operador << " " << endereco2 << ";\n";
			}
			else if(tipo1 == "float" && tipo2 == "int"){
				string temp = "t" + to_string(tempVar);
				adicionaVar(temp, "bool", true);
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, "bool", true);
				ss << "\t" << temp << " = (float)" << endereco2 << ";\n";
				ss << "\t" << temp2 << " = " << temp << " " << operador << " " << endereco1 << ";\n";
			}
			else{
				cout << "Erro: Tipos incompatíveis para operação de comparação.\n";
				exit(1);
			}
		}
		else if(tipo1 != "bool" && tipo2 != "bool"){
			string temp = "t" + to_string(tempVar);
			adicionaVar(temp, "bool", true);
			ss << "\t" << temp << " = " << endereco1 << " " << operador << " " << endereco2 << ";\n";
		}
		else{
			cout << "Erro: Operador de comparação " << operador << " só pode ser usado com tipos numéricos.\n";
			exit(1);
		}
	}
	else{
		cout << "Erro: Operador " << operador << " não suportado para tipos " << tipo1 << " e " << tipo2 << ".\n";
		exit(1);
	}
	return ss;
}
