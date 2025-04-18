%{
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>

#define YYSTYPE atributos

using namespace std;

void adicionaVar(string nome, string tipo, bool temp = false);

int tempVar = 0;
int defVar = 0;
//set<string> variaveisDeclaradas;
//set<string> variaveisGlobaisDeclaradas;

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

int yylex(void);
void yyerror(string);
%}

%token TK_NUM TK_ID TK_TIPO_INT TK_TIPO_FLOAT TK_MAIN
%token TK_TIPO_CHAR TK_TIPO_BOOL
%token TK_CHAR TK_BOOL_TRUE TK_BOOL_FALSE


%start S

%left '+' '-'
%left '*' '/'
%right UMINUS

%%

S:
	  TK_TIPO_INT TK_MAIN '(' ')' BLOCO {
		cout << "/*Compilador DHP*/\n";
		cout << "\n#include<string.h>\n#include<stdio.h>\n";
		cout << "int main(void)\n{\n";

		for (const auto& [nome, info] : tabela_simbolos) {
			if (!(info.temporaria)) {
    			cout << "\t" <<info.tipo << " " << info.endereco_memoria << ";\t //Variavel: "<< nome << "\n";}
			else {
				cout << "\t" << info.tipo << " " << info.endereco_memoria << ";\n";}
		}
/*
		for (auto& v : variaveisGlobaisDeclaradas)
			cout << "\t" << tabela_simbolos[v].tipo << " " << v << ";\n";


		for (auto& v : variaveisDeclaradas){
			if (variaveisGlobaisDeclaradas.count(v) == 0){
				cout << "\t" << tabela_simbolos[v].tipo << " " << v << ";"\n";
			}
		}
*/
		cout << "\n" << $5.traducao << "\n";
		cout << "\treturn 0;\n}\n";
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
	  TK_TIPO_INT TK_ID {
		adicionaVar($2.label, "int");
		$$.traducao = "";
	  }
	| TK_TIPO_INT TK_ID '=' EXPR {

		adicionaVar($2.label, "int");
		stringstream ss;
		ss << "\t" << tabela_simbolos[$2.label].endereco_memoria << " = " << $4.label << ";\n";
		$$.traducao = $4.traducao + ss.str();
	  }
	| TK_TIPO_FLOAT TK_ID {
		adicionaVar($2.label, "float");
		$$.traducao = "";
	  }
	| TK_TIPO_FLOAT TK_ID '=' EXPR {

		adicionaVar($2.label, "float");
		stringstream ss;
		ss << "\t" << tabela_simbolos[$2.label].endereco_memoria << " = " << $4.label << ";\n";
		$$.traducao = $4.traducao + ss.str();
	  }
	| TK_TIPO_CHAR TK_ID {
		adicionaVar($2.label, "char");
		$$.traducao = "";
	}	
	| TK_TIPO_CHAR TK_ID '=' TK_CHAR {
		adicionaVar($2.label, "char");
		stringstream ss;
		ss << "\t" << tabela_simbolos[$2.label].endereco_memoria << " = " << $4.label << ";\n";
		$$.traducao = ss.str();
	}
	| TK_TIPO_BOOL TK_ID {
		adicionaVar($2.label, "bool");
		$$.traducao = "";
	}
	| TK_TIPO_BOOL TK_ID '=' EXPR {
		adicionaVar($2.label, "bool");
		stringstream ss;
		ss << "\t" << tabela_simbolos[$2.label].endereco_memoria << " = " << $4.label << ";\n";
		$$.traducao = $4.traducao + ss.str();
	}

;

ATRIB: TK_ID '=' EXPR {
	if (tabela_simbolos.find($1.label) == tabela_simbolos.end()) {
		cout << "Erro: Variável " << $1.label << " não declarada.\n";
		exit(1);
	}
	stringstream ss;
	ss << "\t" << tabela_simbolos[$1.label].endereco_memoria << " = " << $3.label << ";\n";
	$$.traducao = $3.traducao + ss.str();
}

;

EXPR:
	  EXPR '+' EXPR {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << "\t" << temp << " = " << tabela_simbolos[$1.label].endereco_memoria << " + " << tabela_simbolos[$3.label].endereco_memoria << ";\n";
		$$.label = temp;
		$$.traducao = $1.traducao + $3.traducao + ss.str();

		// Inferência simplificada: se um dos lados for float, resultado é float
		string tipo1 = tabela_simbolos[$1.label].tipo;
		string tipo2 = tabela_simbolos[$3.label].tipo;
		string tipo_result = (tipo1 == "float" || tipo2 == "float") ? "float" : "int";
		adicionaVar(temp, tipo_result, true);
	}
	| '-' EXPR %prec UMINUS {
	string temp = "t" + to_string(tempVar);
	stringstream ss;
	ss << "\t" << temp << " = -" << $2.label << ";\n";
	$$.label = temp;
	$$.traducao = $2.traducao + ss.str();

	// Inferir tipo baseado em $2
	string tipo = tabela_simbolos[$2.label].tipo;
	adicionaVar(temp, tipo, true);
	}

	| EXPR '-' EXPR {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << "\t" << temp << " = " << tabela_simbolos[$1.label].endereco_memoria << " - " << tabela_simbolos[$3.label].endereco_memoria << ";\n";
		$$.label = temp;
		$$.traducao = $1.traducao + $3.traducao + ss.str();

		string tipo1 = tabela_simbolos[$1.label].tipo;
		string tipo2 = tabela_simbolos[$3.label].tipo;
		string tipo_result = (tipo1 == "float" || tipo2 == "float") ? "float" : "int";
		adicionaVar(temp, tipo_result, true);
	}

	| EXPR '*' EXPR {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << "\t" << temp << " = " << tabela_simbolos[$1.label].endereco_memoria << " * " << tabela_simbolos[$3.label].endereco_memoria << ";\n";
		$$.label = temp;
		$$.traducao = $1.traducao + $3.traducao + ss.str();

		string tipo1 = tabela_simbolos[$1.label].tipo;
		string tipo2 = tabela_simbolos[$3.label].tipo;
		string tipo_result = (tipo1 == "float" || tipo2 == "float") ? "float" : "int";
		adicionaVar(temp, tipo_result, true);
	}

	| EXPR '/' EXPR {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << "\t" << temp << " = " << tabela_simbolos[$1.label].endereco_memoria << " / " << tabela_simbolos[$3.label].endereco_memoria << ";\n";
		$$.label = temp;
		$$.traducao = $1.traducao + $3.traducao + ss.str();

		string tipo1 = tabela_simbolos[$1.label].tipo;
		string tipo2 = tabela_simbolos[$3.label].tipo;
		string tipo_result = (tipo1 == "float" || tipo2 == "float") ? "float" : "int";
		adicionaVar(temp, tipo_result);
	}

	| '(' EXPR ')' {
		$$ = $2;
	}
	| TK_NUM {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << "\t" << temp << " = " << $1.traducao << ";\n";
		$$.label = temp;
		$$.traducao = ss.str();

		// Inferir tipo
		string tipo = ($1.traducao.find('.') != string::npos) ? "float" :
					($1.traducao == "true" || $1.traducao == "false") ? "bool" :
					($1.traducao.front() == '\'' && $1.traducao.back() == '\'') ? "char" : "int";

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
	| TK_CHAR {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << "\t" << temp << " = " << $1.label << ";\n";
		$$.label = temp;
		$$.traducao = ss.str();
		adicionaVar(temp, "char", true); // <--- aqui
	}

	| TK_BOOL_TRUE {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << "\t" << temp << " = true;\n";
		$$.label = temp;
		$$.traducao = ss.str();
		adicionaVar(temp, "bool", true); // <--- aqui
	}
	| TK_BOOL_FALSE {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << "\t" << temp << " = false;\n";
		$$.label = temp;
		$$.traducao = ss.str();
		adicionaVar(temp, "bool", true); // <--- aqui
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

