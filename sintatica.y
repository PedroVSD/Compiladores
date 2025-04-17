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
set<string> variaveisDeclaradas;
set<string> variaveisGlobaisDeclaradas;

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
		cout << "/*Compilador FOCA*/\n";
		cout << "#include <iostream>\n#include<string.h>\n#include<stdio.h>\n";
		cout << "int main(void)\n{\n";

		for (auto& v : variaveisGlobaisDeclaradas)
			cout << "\t" << tabela_simbolos[v].tipo << " " << v << ";\n";


		for (auto& v : variaveisDeclaradas){
			if (variaveisGlobaisDeclaradas.count(v) == 0){
				cout << "\t" << tabela_simbolos[v].tipo << " " << v << ";\n";
			}
		}

		cout << $5.traducao;
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
		if (variaveisGlobaisDeclaradas.count($2.label)) {
			cout << "Erro: Variável " << $2.label << " já declarada.\n";
			exit(1);
		}
		adicionaVar($2.label, "int");
		variaveisGlobaisDeclaradas.insert($2.label);
		$$.traducao = "";
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
	| TK_TIPO_FLOAT TK_ID {
		if (variaveisGlobaisDeclaradas.count($2.label)) {
			cout << "Erro: Variável " << $2.label << " já declarada.\n";
			exit(1);
		}
		adicionaVar($2.label, "float");
		variaveisGlobaisDeclaradas.insert($2.label);
		$$.traducao = "";
	  }
	| TK_TIPO_FLOAT TK_ID '=' EXPR {
		if (variaveisGlobaisDeclaradas.count($2.label)) {
			cout << "Erro: Variável " << $2.label << " já declarada.\n";
			exit(1);
		}
		adicionaVar($2.label, "float");
		variaveisGlobaisDeclaradas.insert($2.label);
		stringstream ss;
		ss << "\t" << $2.label << " = " << $4.label << ";\n";
		$$.traducao = $4.traducao + ss.str();
	  }
	| TK_TIPO_CHAR TK_ID {
		if (variaveisGlobaisDeclaradas.count($2.label)) {
			cout << "Erro: Variável " << $2.label << " já declarada.\n";
			exit(1);
		}
		adicionaVar($2.label, "char");
		variaveisGlobaisDeclaradas.insert($2.label);
		$$.traducao = "";
	}	
	| TK_TIPO_CHAR TK_ID '=' TK_CHAR {
		if (variaveisGlobaisDeclaradas.count($2.label)) {
			cout << "Erro: Variável " << $2.label << " já declarada.\n";
			exit(1);
		}
		adicionaVar($2.label, "char");
		variaveisGlobaisDeclaradas.insert($2.label);
		stringstream ss;
		ss << "\t" << $2.label << " = " << $4.label << ";\n";
		$$.traducao = ss.str();
	}
	| TK_TIPO_BOOL TK_ID {
		if (variaveisGlobaisDeclaradas.count($2.label)) {
			cout << "Erro: Variável " << $2.label << " já declarada.\n";
			exit(1);
		}
		adicionaVar($2.label, "bool");
		variaveisGlobaisDeclaradas.insert($2.label);
		$$.traducao = "";
	}
	| TK_TIPO_BOOL TK_ID '=' EXPR {
		if (variaveisGlobaisDeclaradas.count($2.label)) {
			cout << "Erro: Variável " << $2.label << " já declarada.\n";
			exit(1);
		}
		adicionaVar($2.label, "bool");
		variaveisGlobaisDeclaradas.insert($2.label);
		stringstream ss;
		ss << "\t" << $2.label << " = " << $4.label << ";\n";
		$$.traducao = $4.traducao + ss.str();
	}

;

ATRIB: TK_ID '=' EXPR {
	if (tabela_simbolos.find($1.label) == tabela_simbolos.end()) {
		cout << "Erro: Variável " << $1.label << " não declarada.\n";
		exit(1);
	}
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

		// Inferência simplificada: se um dos lados for float, resultado é float
		string tipo1 = tabela_simbolos[$1.label].tipo;
		string tipo2 = tabela_simbolos[$3.label].tipo;
		string tipo_result = (tipo1 == "float" || tipo2 == "float") ? "float" : "int";
		adicionaVar(temp, tipo_result);
	}

	| EXPR '-' EXPR {
		string temp = "t" + to_string(tempVar++);
		stringstream ss;
		ss << "\t" << temp << " = " << $1.label << " - " << $3.label << ";\n";
		$$.label = temp;
		$$.traducao = $1.traducao + $3.traducao + ss.str();

		string tipo1 = tabela_simbolos[$1.label].tipo;
		string tipo2 = tabela_simbolos[$3.label].tipo;
		string tipo_result = (tipo1 == "float" || tipo2 == "float") ? "float" : "int";
		adicionaVar(temp, tipo_result);
	}

	| EXPR '*' EXPR {
		string temp = "t" + to_string(tempVar++);
		stringstream ss;
		ss << "\t" << temp << " = " << $1.label << " * " << $3.label << ";\n";
		$$.label = temp;
		$$.traducao = $1.traducao + $3.traducao + ss.str();

		string tipo1 = tabela_simbolos[$1.label].tipo;
		string tipo2 = tabela_simbolos[$3.label].tipo;
		string tipo_result = (tipo1 == "float" || tipo2 == "float") ? "float" : "int";
		adicionaVar(temp, tipo_result);
	}

	| EXPR '/' EXPR {
		string temp = "t" + to_string(tempVar++);
		stringstream ss;
		ss << "\t" << temp << " = " << $1.label << " / " << $3.label << ";\n";
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
		string temp = "t" + to_string(tempVar++);
		stringstream ss;
		ss << "\t" << temp << " = " << $1.traducao << ";\n";
		$$.label = temp;
		$$.traducao = ss.str();

		// Inferir tipo
		string tipo = ($1.traducao.find('.') != string::npos) ? "float" :
					($1.traducao == "true" || $1.traducao == "false") ? "bool" :
					($1.traducao.front() == '\'' && $1.traducao.back() == '\'') ? "char" : "int";

		adicionaVar(temp, tipo);
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
		string temp = "t" + to_string(tempVar++);
		stringstream ss;
		ss << "\t" << temp << " = " << $1.label << ";\n";
		$$.label = temp;
		$$.traducao = ss.str();
		adicionaVar(temp, "char"); // <--- aqui
	}

	| TK_BOOL_TRUE {
		string temp = "t" + to_string(tempVar++);
		stringstream ss;
		ss << "\t" << temp << " = true;\n";
		$$.label = temp;
		$$.traducao = ss.str();
		adicionaVar(temp, "bool"); // <--- aqui
	}
	| TK_BOOL_FALSE {
		string temp = "t" + to_string(tempVar++);
		stringstream ss;
		ss << "\t" << temp << " = false;\n";
		$$.label = temp;
		$$.traducao = ss.str();
		adicionaVar(temp, "bool"); // <--- aqui
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
	if (tabela_simbolos.find(nome) == tabela_simbolos.end()) {
		tabela_simbolos[nome].tipo = tipo;
		tabela_simbolos[nome].nome = nome;
		tabela_simbolos[nome].endereco_memoria = nome;  // pode ser t0, x, etc.
		tabela_simbolos[nome].existe = true;
		variaveisDeclaradas.insert(nome);
	} else {
		cout << "Erro: Variável " << nome << " já declarada." << endl;
		exit(1);
	}
}

