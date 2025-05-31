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
	{"bool", "int"},
	{"string", "char*"}
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
%token TK_TIPO_STRING TK_STRING_LITERAL


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
	| TK_TIPO_STRING { $$.label = "string"; } // <<< ADICIONE ESTA ALTERNATIVA
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
    EXPR_LOG { // Removido o '|' inicial e o '%prec TK_OR'
        $$.label = $1.label;     // <<< ADICIONADO E CRUCIAL
        $$.traducao = $1.traducao;
    }
;
EXPR_ARIT:
	EXPR_ARIT '+' EXPR_TERM %prec '+' {
        // Buscar informações dos operandos da tabela de símbolos (usando buscarVariavel)
        int idx_op1 = buscarVariavel($1.label);
        int idx_op2 = buscarVariavel($3.label);

        // Adicione checagens de erro se idx_op1 ou idx_op2 for -1

        string tipo1 = pilha[idx_op1][$1.label].tipo;
        string tipo2 = pilha[idx_op2][$3.label].tipo;
        string op1_c_name = pilha[idx_op1][$1.label].endereco_memoria;
        string op2_c_name = pilha[idx_op2][$3.label].endereco_memoria;
        
        stringstream ss_op_code;

        if (tipo1 == "string" && tipo2 == "string") {
            // LÓGICA DE CONCATENAÇÃO INLINE (como no exemplo C que você aprovou)

            // 1. Criar chaves para temporárias de tamanho e resultado, e adicioná-las
            string chave_len1 = "t_len_" + to_string(tempVar);
            adicionaVar(chave_len1, "int", true);
            string c_nome_len1 = pilha[pilha.size()-1][chave_len1].endereco_memoria;

            string chave_len2 = "t_len_" + to_string(tempVar);
            adicionaVar(chave_len2, "int", true);
            string c_nome_len2 = pilha[pilha.size()-1][chave_len2].endereco_memoria;

            string chave_res_str = "t_str_res_" + to_string(tempVar);
            adicionaVar(chave_res_str, "string", true);
            string c_nome_res_str = pilha[pilha.size()-1][chave_res_str].endereco_memoria;

            // 2. Gerar código C para calcular tamanho de op1_c_name -> c_nome_len1
            ss_op_code << qtdTab() << c_nome_len1 << " = 0;\n";
            ss_op_code << qtdTab() << "if (" << op1_c_name << " != NULL) {\n";
            ss_op_code << qtdTab(1) << "while (" << op1_c_name << "[" << c_nome_len1 << "] != '\\0') {\n";
            ss_op_code << qtdTab(2) << c_nome_len1 << "++;\n";
            ss_op_code << qtdTab(1) << "}\n";
            ss_op_code << qtdTab() << "}\n";

            // 3. Gerar código C para calcular tamanho de op2_c_name -> c_nome_len2
            ss_op_code << qtdTab() << c_nome_len2 << " = 0;\n";
            ss_op_code << qtdTab() << "if (" << op2_c_name << " != NULL) {\n";
            ss_op_code << qtdTab(1) << "while (" << op2_c_name << "[" << c_nome_len2 << "] != '\\0') {\n";
            ss_op_code << qtdTab(2) << c_nome_len2 << "++;\n";
            ss_op_code << qtdTab(1) << "}\n";
            ss_op_code << qtdTab() << "}\n";

            // 4. Gerar código C para alocar memória (malloc) -> c_nome_res_str
            ss_op_code << qtdTab() << c_nome_res_str << " = (char*)malloc("
                       << c_nome_len1 << " + " << c_nome_len2 << " + 1);\n";
            ss_op_code << qtdTab() << "if (" << c_nome_res_str << " == NULL) {\n";
            ss_op_code << qtdTab(1) << "fprintf(stderr, \"Erro critico: Falha na alocacao de memoria para string concatenada.\\n\");\n";
            ss_op_code << qtdTab(1) << "exit(1);\n";
            ss_op_code << qtdTab() << "}\n";

            // 5. Gerar código C para copiar op1_c_name para c_nome_res_str (strcpy)
            ss_op_code << qtdTab() << "if (" << op1_c_name << " != NULL) {\n";
            ss_op_code << qtdTab(1) << "strcpy(" << c_nome_res_str << ", " << op1_c_name << ");\n";
            ss_op_code << qtdTab() << "} else {\n";
            ss_op_code << qtdTab(1) << c_nome_res_str << "[0] = '\\0';\n";
            ss_op_code << qtdTab() << "}\n";

            // 6. Gerar código C para concatenar op2_c_name a c_nome_res_str (strcat)
            ss_op_code << qtdTab() << "if (" << op2_c_name << " != NULL) {\n";
            ss_op_code << qtdTab(1) << "strcat(" << c_nome_res_str << ", " << op2_c_name << ");\n";
            ss_op_code << qtdTab() << "}\n";

            $$.label = chave_res_str; 
            $$.traducao = $1.traducao + $3.traducao + ss_op_code.str();

        } else if ( (tipo1 == "string" && tipo2 != "string") || (tipo1 != "string" && tipo2 == "string") ) {
            yyerror("Concatenacao de string com tipo incompativel (" + tipo1 + ", " + tipo2 + ")");
        } else { // Caso numérico: chamar veririficarTipo
            // Note que veririficarTipo retorna stringstream, não string diretamente.
            // E $$.label precisa ser "t" + to_string(tempVar-1) se veririficarTipo cria a temp.
            stringstream resultado_verificacao;
            resultado_verificacao = veririficarTipo($1.label, "+", $3.label);
            $$.label = "t" + to_string(tempVar-1); // Assume que veririficarTipo criou uma temp e incrementou tempVar
            $$.traducao = $1.traducao + $3.traducao + resultado_verificacao.str();
        }
    }
    | EXPR_ARIT '-' EXPR_TERM %prec '-' {
        // Chamar veririficarTipo aqui, mas antes verificar se algum é string
        int idx_op1 = buscarVariavel($1.label);
        int idx_op2 = buscarVariavel($3.label);
        string tipo1 = pilha[idx_op1][$1.label].tipo;
        string tipo2 = pilha[idx_op2][$3.label].tipo;

        if (tipo1 == "string" || tipo2 == "string") {
            yyerror("Operador '-' nao aplicavel a strings");
        } else {
            stringstream resultado_verificacao;
            resultado_verificacao = veririficarTipo($1.label, "-", $3.label);
            $$.label = "t" + to_string(tempVar-1);
            $$.traducao = $1.traducao + $3.traducao + resultado_verificacao.str();
        }
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
        // 1. Buscar informações do operando ($2)
        int indice_escopo_operando = buscarVariavel($2.label);
        if (indice_escopo_operando == -1) {
            yyerror("Variavel '" + $2.label + "' nao declarada (operando de UMINUS)");
        }
        string tipo_operando = pilha[indice_escopo_operando][$2.label].tipo;
        string c_nome_operando = pilha[indice_escopo_operando][$2.label].endereco_memoria;

        // 2. Verificar tipo do operando
        if (tipo_operando == "string" || tipo_operando == "bool") {
            yyerror("Operador unario '-' nao pode ser aplicado ao tipo '" + tipo_operando + "'");
        }
        string tipo_resultado = tipo_operando;

        // 3. Criar chave para a nova temporária e adicionar à tabela
        string chave_temp_resultado = "t_uminus_" + to_string(tempVar);
        adicionaVar(chave_temp_resultado, tipo_resultado, true);

        // 4. Obter o nome C da nova temporária
        string c_nome_resultado = pilha[pilha.size()-1][chave_temp_resultado].endereco_memoria;

        // 5. Gerar código C
        stringstream ss_code;
        ss_code << qtdTab() << c_nome_resultado << " = -" << c_nome_operando << ";\n";
        
        // 6. Definir atributos
        $$.label = chave_temp_resultado;
        $$.traducao = $2.traducao + ss_code.str();
    }
    | TK_NUM {
        // 1. Criar chave para a temporária do número
        string chave_temp_num = "t_num_" + to_string(tempVar);
        
        // 2. Inferir tipo e adicionar à tabela
        string tipo_num = ($1.traducao.find('.') != string::npos) ? "float" : "int";
        adicionaVar(chave_temp_num, tipo_num, true);

        // 3. Obter o nome C da temporária
        string c_nome_num = pilha[pilha.size()-1][chave_temp_num].endereco_memoria;
        
        // 4. Gerar código C
        stringstream ss_code;
        ss_code << qtdTab() << c_nome_num << " = " << $1.traducao << ";\n"; // $1.traducao é o valor literal do número
        
        // 5. Definir atributos
        $$.label = chave_temp_num;
        $$.traducao = ss_code.str();
    }
    | TK_ID {
        if (buscarVariavel($1.label) == -1) { // $1.label é a chave (nome original do ID)
            yyerror("Variavel '" + $1.label + "' nao declarada");
        }
        // Para um ID usado como valor, o label é o próprio nome/chave do ID.
        // O endereco_memoria será usado por regras superiores quando precisarem do valor.
        $$.label = $1.label; 
        $$.traducao = ""; // Não gera novo código C aqui, apenas passa o nome/chave
    }
    | COVERT_TYPE { // Assumindo que COVERT_TYPE já define $$.label e $$.traducao corretamente
        $$.label = $1.label;
        $$.traducao = $1.traducao;
    }
    | TK_BOOL_TRUE {
        // 1. Criar chave para a temporária do booleano
        string chave_temp_true = "t_bool_" + to_string(tempVar);
        
        // 2. Adicionar à tabela
        adicionaVar(chave_temp_true, "bool", true);

        // 3. Obter o nome C da temporária
        string c_nome_true = pilha[pilha.size()-1][chave_temp_true].endereco_memoria;
        
        // 4. Gerar código C
        stringstream ss_code;
        ss_code << qtdTab() << c_nome_true << " = 1;\n"; // true é 1 em C
        
        // 5. Definir atributos
        $$.label = chave_temp_true;
        $$.traducao = ss_code.str();
    }
    | TK_BOOL_FALSE {
        // 1. Criar chave para a temporária do booleano
        string chave_temp_false = "t_bool_" + to_string(tempVar);

        // 2. Adicionar à tabela
        adicionaVar(chave_temp_false, "bool", true);
        
        // 3. Obter o nome C da temporária
        string c_nome_false = pilha[pilha.size()-1][chave_temp_false].endereco_memoria;

        // 4. Gerar código C
        stringstream ss_code;
        ss_code << qtdTab() << c_nome_false << " = 0;\n"; // false é 0 em C
        
        // 5. Definir atributos
        $$.label = chave_temp_false;
        $$.traducao = ss_code.str();
    }
    | TK_STRING_LITERAL { // <<< ADICIONADO E CORRIGIDO
        // 1. Criar chave para a temporária do literal string
        string chave_temp_sl = "t_sl_" + to_string(tempVar);
        
        // 2. Adicionar à tabela com tipo "string"
        adicionaVar(chave_temp_sl, "string", true);

        // 3. Obter o nome C da temporária (será algo como "tN")
        string c_nome_sl = pilha[pilha.size()-1][chave_temp_sl].endereco_memoria;
        
        // 4. Gerar código C
        // $1.traducao do lexer já é o literal C com aspas (ex: "\"ola\"")
        stringstream ss_code;
        ss_code << qtdTab() << c_nome_sl << " = " << $1.traducao << ";\n";
        
        // 5. Definir atributos
        $$.label = chave_temp_sl; // O label é a chave da temporária
        $$.traducao = ss_code.str();  // O código C gerado
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
