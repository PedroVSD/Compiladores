%{
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>

#define YYSTYPE atributos

using namespace std;

void adicionaVar(string nome, string tipo);

int tempVar = 0;
set<string> variaveisDeclaradas; // Armazena t0, t1, a, b etc.
set<string> variaveisGlobaisDeclaradas; // Armazena apenas as variáveis do usuário

struct atributos {
	string label;
	string traducao;
};

struct tabela{
	string tipo;
	string nome;
	string endereco_memoria;
	bool existe;
};

map<string, tabela> tabela_simbolos;

int yylex(void);
void yyerror(string);
%}

%token TK_NUM TK_ID TK_TIPO_INT TK_MAIN

%start S

%left '+' '-'
%left '*' '/'
%right UMINUS

%%

S: TK_TIPO_INT TK_MAIN '(' ')' BLOCO {
	cout << "/*Compilador FOCA*/\n";
	cout << "#include <iostream>\n#include<string.h>\n#include<stdio.h>\n";
	cout << "int main(void)\n{\n";

	// Declarar variáveis do usuário
	for (auto& v : variaveisGlobaisDeclaradas)
		cout << "\tint " << v << ";\n";

	// Declarar temporárias
	for (auto& v : variaveisDeclaradas)
		if (variaveisGlobaisDeclaradas.count(v) == 0)
			cout << "\tint " << v << ";\n";

	cout << $5.traducao;
	cout << "\treturn 0;\n}\n";
}
;

BLOCO: '{' COMANDOS '}' {
	$$.traducao = $2.traducao;
}
;

COMANDOS: COMANDO COMANDOS {
	$$.traducao = $1.traducao + $2.traducao;
}
| /* vazio */ {
	$$.traducao = "";
}
;

COMANDO:
	  DECLARACAO ';'
	| ATRIB ';'
	| EXPR ';'
;

DECLARACAO:
	  TK_TIPO_INT TK_ID {
		if (variaveisGlobaisDeclaradas.count($2.label)) {
			cout << "Erro: Variável " << $2.label << " já declarada.\n";
			exit(1);
		}
		adicionaVar($2.label, "int");
		variaveisGlobaisDeclaradas.insert($2.label);
		$$.traducao = ""; // Apenas declara
	  }
	| TK_TIPO_INT TK_ID '=' EXPR {
		if (variaveisGlobaisDeclaradas.count($2.label)) {
			cout << "Erro: Variável " << $2.label << " já declarada.\n";
			exit(1);
		}
		adicionaVar($2.label, "int");
		variaveisGlobaisDeclaradas.insert($2.label);

		stringstream ss;
		ss << "\t" << $2.label << " = " << $4.label << ";\n";
		$$.traducao = $4.traducao + ss.str();
	  }
;



ATRIB: TK_ID '=' EXPR {
	stringstream ss;
	ss << "\t" << $1.label << " = " << $3.label << ";\n";
	$$.traducao = $3.traducao + ss.str();
}
;

EXPR:
	  EXPR '+' EXPR {
		string temp = "t" + to_string(tempVar++);
		stringstream ss;
		ss << "\t" << temp << " = " << $1.label << " + " << $3.label << ";\n";
		$$.label = temp;
		$$.traducao = $1.traducao + $3.traducao + ss.str();
		variaveisDeclaradas.insert(temp);
	  }
	| EXPR '-' EXPR {
		string temp = "t" + to_string(tempVar++);
		stringstream ss;
		ss << "\t" << temp << " = " << $1.label << " - " << $3.label << ";\n";
		$$.label = temp;
		$$.traducao = $1.traducao + $3.traducao + ss.str();
		variaveisDeclaradas.insert(temp);
	  }
	| EXPR '*' EXPR {
		string temp = "t" + to_string(tempVar++);
		stringstream ss;
		ss << "\t" << temp << " = " << $1.label << " * " << $3.label << ";\n";
		$$.label = temp;
		$$.traducao = $1.traducao + $3.traducao + ss.str();
		variaveisDeclaradas.insert(temp);
	  }
	| EXPR '/' EXPR {
		string temp = "t" + to_string(tempVar++);
		stringstream ss;
		ss << "\t" << temp << " = " << $1.label << " / " << $3.label << ";\n";
		$$.label = temp;
		$$.traducao = $1.traducao + $3.traducao + ss.str();
		variaveisDeclaradas.insert(temp);
	  }
	| '(' EXPR ')' {
		// Apenas propaga a expressão interna
		$$ = $2;
	}
	| TK_NUM {
		string temp = "t" + to_string(tempVar++);
		stringstream ss;
		ss << "\t" << temp << " = " << $1.traducao << ";\n";
		$$.label = temp;
		$$.traducao = ss.str();
		variaveisDeclaradas.insert(temp);
	}
	| TK_ID {
		$$.label = $1.label;
		$$.traducao = "";
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
	cout << "Erro sintático: " << MSG << endl;
	exit(1);
}

void adicionaVar(string nome, string tipo){
	if(tabela_simbolos.find(nome)==tabela_simbolos.end()){
		tabela_simbolos[nome].tipo = tipo;
		tabela_simbolos[nome].nome = nome;
		tabela_simbolos[nome].endereco_memoria = "t" + to_string(tempVar++);
		tabela_simbolos[nome].existe = true;
		variaveisDeclaradas.insert(tabela_simbolos[nome].endereco_memoria);
	}else{
		cout << "Erro: Variável " << nome << " já declarada." << endl;
		exit(1);
	}
}