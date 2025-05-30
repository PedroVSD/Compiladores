%{
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <vector>


#define YYSTYPE atributos

using namespace std;


// Declaração de funções
void adicionaVar(string nome, string tipo, bool temp = false);
stringstream veririficarTipo(string var1, string operador, string var2 = "");
void criarPilha();
stringstream fecharPilha();
int buscarVariavel(string nome);
string qtdTab(int dif = 0);

// Contadores globais
int tempVar = 0;
int defVar = 0;
int defbloco = 0;

struct atributos {
	string label;
	string traducao;
};

// Estrutura para armazenar informações de variáveis
struct tabela{
	string tipo;
	string endereco_memoria;
	bool temporaria;
};

// Tabela de símbolos
typedef map<string, tabela> tabela_simbolos;
vector<tabela_simbolos> pilha;

// tradução dos tipos
map<string, string> tipoTraducao = {
	{"int", "int"},
	{"float", "float"},
	{"char", "char"},
	{"bool", "int"}
};


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
		cout << "\n#include<string.h>\n#include<stdio.h>\n";
		cout << fecharPilha().str();		
		cout << $1.traducao;
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
		ss << "int main(void)\n";

		ss << $4.traducao << "\n";

		ss << "\treturn 0;\n";

		$$.traducao = ss.str();
	  }
;

BLOCO: { criarPilha(); } '{' COMANDOS '}' {
	stringstream ss;
	ss << qtdTab(-1) << "{\n";
	ss << fecharPilha().str();
	ss << "\n";
    ss << $3.traducao;
	ss << qtdTab() << "}\n";
	$$.traducao = ss.str();
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
	  DECLARACAO ';'{ $$.traducao = $1.traducao; }
	| ATRIB ';'     { $$.traducao = $1.traducao; }
	| EXPR ';'      { $$.traducao = $1.traducao; }
	| BLOCO 		{ $$.traducao = $1.traducao; }
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
        ss << qtdTab() << pilha[pilha.size()-1][$2.label].endereco_memoria << " = " << $4.label << ";\n";
        $$.traducao = ss.str();
      }
;

ATRIB: TK_ID '=' EXPR {
	if (buscarVariavel($1.label) == -1) {
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
		ss << qtdTab() << temp << " = !" << pilha[buscarVariavel($2.label)][$2.label].endereco_memoria << ";\n";
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
	ss << qtdTab() << temp << " = -" << $2.label << ";\n";
	$$.label = temp;
	$$.traducao = $2.traducao + ss.str();

	// Inferir tipo baseado em $2
	string tipo = pilha[buscarVariavel($2.label)][$2.label].tipo;
	adicionaVar(temp, tipo, true);
	}
	| TK_NUM {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << qtdTab() << temp << " = " << $1.traducao << ";\n";
		$$.label = temp;
		$$.traducao = ss.str();

		// Inferir tipo
		string tipo = ($1.traducao.find('.') != string::npos) ? "float" : "int";
					

		adicionaVar(temp, tipo, true);
	}
	| TK_ID {
		if (buscarVariavel($1.label) == -1) {
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
		ss << qtdTab() << temp << " = 1;\n";
		$$.label = temp;
		$$.traducao = ss.str();
		adicionaVar(temp, "bool", true);
	}
	| TK_BOOL_FALSE {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << qtdTab() << temp << " = 0;\n";
		$$.label = temp;
		$$.traducao = ss.str();
		adicionaVar(temp, "bool", true);
	}
;
COVERT_TYPE:
	TK_TIPO_INT '(' EXPR ')' {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << qtdTab() << temp << " = (int)" << pilha[buscarVariavel($3.label)][$3.label].endereco_memoria << ";\n";
		$$.label = temp;
		$$.traducao = $3.traducao + ss.str();
		adicionaVar(temp, "int", true);
	}
	| TK_TIPO_FLOAT '(' EXPR ')' {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << qtdTab() << temp << " = (float)" << pilha[buscarVariavel($3.label)][$3.label].endereco_memoria << ";\n";
		$$.label = temp;
		$$.traducao = $3.traducao + ss.str();
		adicionaVar(temp, "float", true);
	}
;
%%

#include "lex.yy.c"

int yyparse();

int main(int argc, char* argv[]) {
	criarPilha();
	yyparse();

	return 0;
}

void yyerror(string MSG) {
	cout << "Erro sintático: " << MSG << " na linha: " << numLinha << endl;
	exit(1);
}

void adicionaVar(string nome, string tipo, bool temp) {
	if (pilha[pilha.size()-1].find(nome) == pilha[pilha.size()-1].end()) {
		pilha[pilha.size()-1][nome].tipo = tipo;
		pilha[pilha.size()-1][nome].temporaria = temp;
		if (temp) {
			pilha[pilha.size()-1][nome].endereco_memoria = "t" + to_string(tempVar++);
		} else {
			pilha[pilha.size()-1][nome].endereco_memoria = "d" + to_string(defVar++);
		}
	} else {
		cout << "Erro: Variável " << nome << " já declarada." << endl;
		exit(1);
	}
}

stringstream veririficarTipo(string var1, string operador, string var2) {
	stringstream ss;
	string tipo1 = pilha[buscarVariavel(var1)][var1].tipo;
	string tipo2 = pilha[buscarVariavel(var2)][var2].tipo;
	string endereco1 = pilha[buscarVariavel(var1)][var1].endereco_memoria;
	string endereco2 = pilha[buscarVariavel(var2)][var2].endereco_memoria;
	
	if(operador == "="){
		if(tipo1 != tipo2){
			if(tipo1 == "int" && tipo2 == "float"){
				ss << qtdTab() << endereco1 << " = (int)" << endereco2 << ";\n";
			}
			else if(tipo1 == "float" && tipo2 == "int"){
				ss << qtdTab() << endereco1 << " = (float)" << endereco2 << ";\n";
			}
			else{
				cout << "Erro: Tipos incompatíveis para atribuição da variavel: " << var1 << "\n" ;
				exit(1);
			}
		}
		else{
			ss << qtdTab() << endereco1 << " = " << endereco2 << ";\n";
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
				ss << qtdTab() << temp << " = (float)" << endereco1 << ";\n";
				ss << qtdTab() << temp2 << " = " << temp << " " << operador << " " << endereco2 << ";\n";
			}
			else if(tipo1 == "float" && tipo2 == "int"){
				ss << qtdTab() << temp << " = (float)" << endereco2 << ";\n";
				ss << qtdTab() << temp2 << " = " << temp << " " << operador << " " << endereco1 << ";\n";
			}
			else{
				cout << "Erro: Tipos incompatíveis para operação " << operador << ".\n";
				exit(1);
			}
		}
		else{
			string temp = "t" + to_string(tempVar);
			adicionaVar(temp, tipo1, true);
			ss << qtdTab() << temp << " = " << endereco1 << " " << operador << " " << endereco2 << ";\n";
		}
	}
	else if(operador == "||" || operador == "&&"){
		if(tipo1 != "bool" || tipo2 != "bool"){
			cout << "Erro: Operador lógico " << operador << " só pode ser usado com tipos booleanos.\n";
			exit(1);
		}
		string temp = "t" + to_string(tempVar);
		adicionaVar(temp, "bool", true);
		ss << qtdTab() << temp << " = " << endereco1 << " " << operador << " " << endereco2 << ";\n";
	}

	else if(operador == "==" || operador == "!="){
		if(tipo1 != tipo2){
			if(tipo1 == "int" && tipo2 == "float"){
				string temp = "t" + to_string(tempVar);
				adicionaVar(temp, "bool", true);
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, "bool", true);
				ss << qtdTab() << temp << " = (float)" << endereco1 << ";\n";
				ss << qtdTab() << temp2 << " = " << temp << " " << operador << " " << endereco2 << ";\n";
			}
			else if(tipo1 == "float" && tipo2 == "int"){
				string temp = "t" + to_string(tempVar);
				adicionaVar(temp, "bool", true);
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, "bool", true);
				ss << qtdTab() << temp << " = (float)" << endereco2 << ";\n";
				ss << qtdTab() << temp2 << " = " << temp << " " << operador << " " << endereco1 << ";\n";
			}
			else{
				cout << "Erro: Tipos incompatíveis para operação de comparação.\n";
				exit(1);
			}
		}
		else{
			string temp = "t" + to_string(tempVar);
			adicionaVar(temp, "bool", true);
			ss << qtdTab() << temp << " = ("<< endereco1 <<" "<< operador <<" "<< endereco2<<");\n";
		}
	}

	else if(operador == ">" || operador == "<" || operador == ">=" || operador == "<="){
		if(tipo1 != tipo2){
			if(tipo1 == "int" && tipo2 == "float"){
				string temp = "t" + to_string(tempVar);
				adicionaVar(temp, "bool", true);
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, "bool", true);
				ss << qtdTab() << temp << " = (float)" << endereco1 << ";\n";
				ss << qtdTab() << temp2 << " = " << temp << " " << operador << " " << endereco2 << ";\n";
			}
			else if(tipo1 == "float" && tipo2 == "int"){
				string temp = "t" + to_string(tempVar);
				adicionaVar(temp, "bool", true);
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, "bool", true);
				ss << qtdTab() << temp << " = (float)" << endereco2 << ";\n";
				ss << qtdTab() << temp2 << " = " << temp << " " << operador << " " << endereco1 << ";\n";
			}
			else{
				cout << "Erro: Tipos incompatíveis para operação de comparação.\n";
				exit(1);
			}
		}
		else if(tipo1 != "bool" && tipo2 != "bool"){
			string temp = "t" + to_string(tempVar);
			adicionaVar(temp, "bool", true);
			ss << qtdTab() << temp << " = " << endereco1 << " " << operador << " " << endereco2 << ";\n";
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

void criarPilha(){
	defbloco++;
	pilha.push_back(tabela_simbolos());
}

stringstream fecharPilha(){
	stringstream ss;
	// Controla a tabulação

	if(defbloco > 0){
		for(const auto& [nome, info] : pilha.back()) {
			if(info.temporaria)
				ss << qtdTab() << tipoTraducao[info.tipo] <<" "<< info.endereco_memoria << ";\n";
			else
				ss << qtdTab() << tipoTraducao[info.tipo] <<" "<< info.endereco_memoria << ";\t //"<< nome << "\n";
		}
		defbloco--;
		pilha.pop_back();
	}
	else{
		cout << "Erro: Pilha de escopo vazia.\n";
		exit(1);
	}
	return ss;
}

int buscarVariavel(string nome){
	if (pilha.empty()) {
		cout << "Erro: Pilha de escopo vazia.\n";
		exit(1);
	}

	int i = pilha.size() -1;

	while(i >= 0){
		if(pilha[i].find(nome) != pilha[i].end()){
			return i;
		}
		i--;
	}
	return -1;
}
string qtdTab(int dif){
	string tab = "";
	for(int i = 1; i < (defbloco + dif); i++){
		tab += "\t";
	}
	return tab;
}
