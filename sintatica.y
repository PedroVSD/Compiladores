%{
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <stack>

#define YYSTYPE atributos

using namespace std;

// Declaração de funções
void adicionaVar(string nome, string tipo, bool temp = false);
stringstream veririficarTipo(string var1, string operador, string var2 = "");
void criarPilha();
void addPilhaLaco(string b, string c);
stringstream fecharPilha();
int buscarVariavel(string nome);
string qtdTab(int dif = 0);

// Contadores globais
int tempVar = 0;
int defVar = 0;
int defbloco = 0;
int defgoto = 0;
int tempElse = 0;

// Flag para gerar a função de tamanho de string
bool precisa_get_length = false;
bool precisa_input_int = false;
bool precisa_input_float = false;
bool precisa_input_string = false;

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

struct RotulosDeLaço {
    string rotuloBreak;    // Rótulo para onde 'break' deve pular (fim do laço)
    string rotuloContinue; // Rótulo para onde 'continue' deve pular (próxima iteração)
};

vector<RotulosDeLaço> pilhaDeRotulosDeLaços;

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
map<string, string> tipomascara{
	{"int", "%d"},
	{"float", "%.6f"},
	{"char", "%c"},
	{"bool", "%d"},
	{"string", "%s"}
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
%token TK_IF TK_ELSE TK_ELSE_IF TK_WHILE TK_FOR TK_DO
%token TK_BREAK TK_CONTINUE
%token TK_ESCREVA TK_LEIA


%start S

%left TK_OR
%left TK_AND
%nonassoc TK_IGUAL TK_DIFERENTE
%left '<' '>' TK_MAIOR_IGUAL TK_MENOR_IGUAL
%left '+' '-'
%left '*' '/'
%right UMINUS '!'
%nonassoc '(' ')'
%nonassoc LOWER_THAN_ELSE
%nonassoc TK_ELSE

%%

S:
    INICIO {
        cout << "/*Compilador DHP*/\n";
        cout << "\n#include<stdio.h>\n#include<string.h>\n#include<stdlib.h>\n";

        // Mudei o nome da sua função 'Len' para 'get_string_length' para consistência
        if (precisa_get_length) {
            cout << "\nint Len(const char* str) {\n"
                 << "    int len;\n	int f0;\n	int f1;\n	int f2;\n\n"
                 << "    len = 0;\n"
                 << "    f0 = (str == NULL);\n"
                 << "    if (f0) goto loop_end_len;\n"
                 << "loop_start_len:\n"
                 << "    f1 = str[len];\n"
                 << "    f2 = (f1 == '\\0');\n" // Usei f1 aqui para estilo 3-endereços
                 << "    if (f2) goto loop_end_len;\n"
                 << "    len = len + 1;\n"
                 << "    goto loop_start_len;\n"
                 << "loop_end_len:;\n" // Adicionado ; para sintaxe C sempre válida
                 << "    return len;\n"
                 << "}\n\n";
        }
        if (precisa_input_int) {
             cout << "\nint input_int() {\n"
                  << "    int num=0;\nint sign=1, flag_is_space, flag_is_newline, flag_is_whitespace;\n"
                  << "    char c;\n"
                  << "    int flag_is_minus, flag_is_less, flag_is_greater, flag_not_digit, temp_val;\n"
                  << "input_ws_loop:\n"
                  << "    scanf(\"%c\", &c);\n"
                  << "    flag_is_space = c == ' ';\n"
                  << "    flag_is_newline = c == '\\n';\n"
                  << "    flag_is_whitespace = flag_is_space || flag_is_newline;\n"
                  << "    if (flag_is_whitespace) goto input_ws_loop;\n"
                  << "after_sign_check:;\n"
                  << "    flag_is_minus = c == '-';\n"
                  << "    if (!flag_is_minus) goto input_digit_loop;\n"
                  << "    sign = -1;\n"
                  << "    scanf(\"%c\", &c);\n"
                  << "input_digit_loop:\n"
                  << "    flag_is_less = c < '0';\n"
                  << "    flag_is_greater = c > '9';\n"
                  << "    flag_not_digit = flag_is_less || flag_is_greater;\n"
                  << "    if (flag_not_digit) goto end_read_digits;\n"
                  << "    temp_val = c - '0';\n"
                  << "    num = num * 10;\n"
                  << "    num = num + temp_val;\n"
                  << "    scanf(\"%c\", &c);\n"
                  << "    goto input_digit_loop;\n"
                  << "end_read_digits:;\n"
                  << "    num = sign * num;\n"
                  << "    return num;\n"
                  << "}\n\n";
        }
		 if (precisa_input_float) {
            cout << "double input_float() {\n" // Usamos double em C para maior precisão
                 << "   double num;\ndouble divisor;\n"
                 << "   int sign;\nint in_fraction;\n" // in_fraction é uma flag
				 << ""
                 << "   char c;\n\n"
				 <<	" 	num = 0.0;\n"
				 << "	divisor = 1.0;\n"
				 << "	sign = 1;\n"
				 << "	in_fraction = 0;\n\n"
                 << "input_float_ws_loop:\n"
                 << "    scanf(\"%c\", &c);\n"
                 << "    if (c == ' ' || c == '\\n') goto input_float_ws_loop;\n\n"
                 << "    // Lida com o sinal\n"
                 << "    if (c == '-') { sign = -1; scanf(\"%c\", &c); }\n\n"
                 << "read_float_loop:\n"
                 << "    if (c == '.' && in_fraction == 0) {\n"
                 << "        in_fraction = 1;\n"
                 << "        scanf(\"%c\", &c);\n"
                 << "        goto read_float_loop;\n"
                 << "    }\n"
                 << "    if (c < '0' || c > '9') { goto read_float_end; }\n\n"
                 << "    if (in_fraction == 0) {\n"
                 << "        num = num * 10.0 + (c - '0');\n"
                 << "    } else {\n"
                 << "        divisor = divisor * 10.0;\n"
                 << "        num = num + (double)(c - '0') / divisor;\n"
                 << "    }\n"
                 << "    scanf(\"%c\", &c);\n"
                 << "    goto read_float_loop;\n\n"
                 << "read_float_end:;\n"
                 << "    num = (double)sign * num;\n"
                 << "    return num;\n"
                 << "}\n\n";
        }
		if (precisa_input_string) {
            cout << "\n// Le uma string da entrada ate o espaco ou nova linha\n";
            cout << "char* input_string() {\n"
                 << "    int capacity = 16;\n"
                 << "    int len = 0;\n"
                 << "    char* buffer = (char*)malloc(capacity);\n"
                 << "    char c;\n"
                 << "    int scanf_result, flag_is_terminator, flag_is_newline, flag_is_space, flag_is_full;\n"
                 << "\n"
                 << "input_str_loop_start:\n"
                 << "    scanf_result = scanf(\"%c\", &c);\n"
                 << "    flag_is_terminator = scanf_result != 1;\n"
                 << "    if (flag_is_terminator) goto input_str_loop_end;\n"
                 << "    flag_is_newline = c == '\\n';\n"
                 << "    flag_is_space = c == ' ';\n"
                 << "    flag_is_terminator = flag_is_newline || flag_is_space;\n"
                 << "    if (flag_is_terminator) goto input_str_loop_end;\n"
                 << "\n"
                 << "    buffer[len] = c;\n"
                 << "    len = len + 1;\n"
                 << "\n"
                 << "    flag_is_full = len >= capacity;\n"
                 << "    if (!flag_is_full) goto input_str_loop_start;\n"
                 << "\n"
                 << "    capacity = capacity * 2;\n"
                 << "    buffer = (char*)realloc(buffer, capacity);\n"
                 << "    goto input_str_loop_start;\n"
                 << "\n"
                 << "input_str_loop_end:;\n"
                 << "    buffer[len] = '\\0';\n"
                 << "    return buffer;\n"
                 << "}\n\n";
        }

        // Imprime o resto do código
        cout << fecharPilha().str();        
        cout << $1.traducao;
    }
;

INICIO:
	DECLARACAO MAIN
	{
		$$.traducao = $1.traducao + $2.traducao;
	}
	| DECLARACAO
	{
		$$.traducao = $1.traducao;
	}
;

MAIN:
	 TK_MAIN '(' ')' BLOCO {

		stringstream ss;
		ss << "int main(void)\n";

		ss << $4.traducao << "\n";


		$$.traducao = ss.str();
	  }
;

BLOCO: { criarPilha(); } '{' COMANDOS '}' {
	stringstream ss;
	ss << qtdTab(-1) << "{\n";

	// Declarações das variáveis
	string decls = "";
	decls = fecharPilha().str();
	ss << decls;

	if(!decls.empty() && !$3.traducao.empty()) {
		ss << "\n";
	}

	// Comandos dentro do bloco
    ss << $3.traducao;

	// Se o bloco for o principal, adiciona retorno
	if(defbloco == 1) { ss << "\n" << qtdTab(1) << "return 0;\n"; }
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
	  DECLAR_VAR ';'{ $$.traducao = $1.traducao; }
	| ATRIB ';'     { $$.traducao = $1.traducao; }
	| EXPR ';'      { $$.traducao = $1.traducao; }
	| BLOCO 		{ $$.traducao = $1.traducao; }
	| LOOP          { $$.traducao = $1.traducao; }
	| { criarPilha(); } COND_IF 		{ $$.traducao = $2.traducao; }
	| COMANDO_SAIDA ';'   { $$.traducao = $1.traducao; }
    | COMANDO_ENTRADA ';' { $$.traducao = $1.traducao; }	
;

COMANDO_SAIDA:
    TK_ESCREVA '(' LISTA_EXPRESSOES ')' 
	{
        $$.traducao = $3.traducao + qtdTab() + "printf(\"\\n\");\n";
    }
;

LISTA_EXPRESSOES:
    EXPR {
        int idx = buscarVariavel($1.label);
        if (idx == -1) { yyerror("Variavel ou expressao '" + $1.label + "' invalida em 'escreva'."); }

        string tipo = pilha[idx][$1.label].tipo;
        string var = pilha[idx][$1.label].endereco_memoria;
        
        stringstream ss;
        ss << $1.traducao; // Inclui o código que calcula a expressão
        
        ss << qtdTab() << "printf(" << "\"" << tipomascara[tipo] << "\", " << var << ");\n"; 
        
        $$.traducao = ss.str();
    }
    // Caso recursivo: Uma lista, vírgula, e mais uma expressão.
    | LISTA_EXPRESSOES ',' EXPR {
        int idx = buscarVariavel($3.label);
        if (idx == -1) { yyerror("Variavel ou expressao '" + $3.label + "' invalida em 'output'."); }
        
        string tipo = pilha[idx][$3.label].tipo;
        string var = pilha[idx][$3.label].endereco_memoria;
        
        stringstream ss;
        ss << $3.traducao;

        ss << qtdTab() << "printf(\"" << tipomascara[tipo] << "\", " << var << ");\n";

                
        $$.traducao = $1.traducao + ss.str();
    }
;

COMANDO_ENTRADA:
    TK_LEIA '(' LISTA_VARIAVEIS ')' {
        $$.traducao = $3.traducao;
    }
;

LISTA_VARIAVEIS:
    TK_ID {
        int idx = buscarVariavel($1.label);
        if (idx == -1) { yyerror("Variavel '" + $1.label + "' nao declarada para 'leia'."); }

        string tipo = pilha[idx][$1.label].tipo;
        string c_nome = pilha[idx][$1.label].endereco_memoria;
        
        stringstream ss_code;
        if (tipo == "int" || tipo == "bool") {
            precisa_input_int = true;
            ss_code << qtdTab() << c_nome << " = input_int();\n";
        } else if (tipo == "float") {
            precisa_input_float = true;
            ss_code << qtdTab() << c_nome << " = input_float();\n";
        } else if (tipo == "char") {
            ss_code << qtdTab() << "scanf(\" %c\", &" << c_nome << ");\n";
        } else if (tipo == "string") {
            precisa_input_string = true; 
            ss_code << qtdTab() << c_nome << " = input_string();\n";
        } else {
            yyerror("Tipo '" + tipo + "' invalido para 'leia'.");
        }
        $$.traducao = ss_code.str();
    }
    | LISTA_VARIAVEIS ',' TK_ID {

        // A lógica é idêntica para o caso recursivo
        int idx = buscarVariavel($3.label);
        if (idx == -1) { yyerror("Variavel '" + $3.label + "' nao declarada para 'leia'."); }

        string tipo = pilha[idx][$3.label].tipo;
        string c_nome = pilha[idx][$3.label].endereco_memoria;
        
        stringstream ss_code;
        if (tipo == "int" || tipo == "bool") {
            precisa_input_int = true;
            ss_code << qtdTab() << c_nome << " = input_int();\n";
        } else if (tipo == "float") {
            precisa_input_float = true;
            ss_code << qtdTab() << c_nome << " = input_float();\n";
        } else if (tipo == "char") {
            ss_code << qtdTab() << "scanf(\" %c\", &" << c_nome << ");\n";
        } else if (tipo == "string") {
            precisa_input_string = true; 
            ss_code << qtdTab() << c_nome << " = input_string();\n";
        } else {
            yyerror("Tipo '" + tipo + "' invalido para 'leia'.");
        }
        
        $$.traducao = $1.traducao + ss_code.str();
    }
;

DECLARACAO:
      DECLAR_VAR ';' DECLARACAO 
	  {
        $$.traducao = $1.traducao;
      }
	  | 
	  {
		$$.traducao = "";
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

LOOP:
	 { criarPilha(); addPilhaLaco("EndWhile" + to_string(defgoto), "BeginWhile" + to_string(defgoto));} TK_WHILE '(' EXPR ')' BLOCO {
		//Verificações
		if (buscarVariavel($4.label) == -1) {
			yyerror("Variável '" + $4.label + "' não declarada no loop while.");
		}
		if (pilha[buscarVariavel($4.label)][$4.label].tipo != "bool") {
			yyerror("Condição do loop while deve ser do tipo booleano, mas é '" + pilha[buscarVariavel($3.label)][$3.label].tipo + "'.");
		}

		// Geração de código		
		stringstream ss;
		string temp = pilha[buscarVariavel($4.label)][$4.label].endereco_memoria; // Endereço de memória da variável condicional
		string rotuloBreak = pilhaDeRotulosDeLaços.back().rotuloBreak;
		string rotuloContinue = pilhaDeRotulosDeLaços.back().rotuloContinue;

		ss << "\n";

		ss << qtdTab(-1) << "{\n"; // Abre a pilha de variáveis para o loop

		ss << fecharPilha().str(); // Fecha a pilha de variáveis antes do loop

		ss << $4.traducao; // Traduz a expressão condicional

		ss << "\n";

		ss << qtdTab(1) << rotuloContinue << ":\n";

		ss << qtdTab(1) << "if (!" << temp << ") goto "<< rotuloBreak << ";\n";

		ss << "\n";

		ss << $6.traducao; // Traduz o bloco do loop

		ss << "\n"; // Adiciona uma nova linha para melhor legibilidade

		ss << $4.traducao; // Reavalia a condição do loop

		ss << qtdTab(1) << "goto " << rotuloContinue << ";\n";

		ss << qtdTab(1) << rotuloBreak << ":\n";

		ss << qtdTab() << "}\n"; // Fecha a pilha de variáveis do loop

		pilhaDeRotulosDeLaços.push_back({ "EndWhile" + to_string(defgoto), "BeginWhile" + to_string(defgoto) });

		defgoto++; // Incrementa o contador de blocos de loop
		$$.traducao = ss.str();
	}
	| { criarPilha(); addPilhaLaco("EndDoWhile" + to_string(defgoto), "BenginDoWhile" + to_string(defgoto)); } TK_DO BLOCO TK_WHILE '(' EXPR ')' ';' {

		// Verificações
		if (buscarVariavel($6.label) == -1) {
			yyerror("Variável '" + $6.label + "' não declarada no loop do-while.");
		}
		if (pilha[buscarVariavel($6.label)][$6.label].tipo != "bool") {
			yyerror("Condição do loop do-while deve ser do tipo booleano, mas é '" + pilha[buscarVariavel($5.label)][$5.label].tipo + "'.");
		}

		// Geração de código
		stringstream ss;
		string temp = pilha[buscarVariavel($6.label)][$6.label].endereco_memoria; // Endereço de memória da variável condicional
		string rotuloBreak = pilhaDeRotulosDeLaços.back().rotuloBreak;
		string rotuloContinue = pilhaDeRotulosDeLaços.back().rotuloContinue;


		ss << "\n";

		ss << qtdTab(-1) << "{\n"; // Abre a pilha de variáveis para o loop

		ss << fecharPilha().str(); // Fecha a pilha de variáveis antes do loop

		ss << "\n";

		ss << qtdTab(1) << rotuloContinue << ":\n";

		ss << $3.traducao; // Traduz o bloco do loop

		ss << "\n";

		ss << $6.traducao; // Traduz a expressão condicional 

		ss << qtdTab(1) << "if (!" << temp << ") goto " << rotuloContinue << ";\n";
		
		ss << qtdTab(1) << rotuloBreak << ":\n";
		
		ss << qtdTab() << "}\n"; // Fecha a pilha de variáveis do loop
		
		ss << "\n";
		
		defgoto++; // Incrementa o contador de blocos de loop
		$$.traducao = ss.str();
	}
	| { criarPilha(); addPilhaLaco("EndFor" + to_string(defgoto), "MidFor" + to_string(defgoto)); } TK_FOR '(' DECLAR_VAR ';' EXPR ';' ATRIB ')' BLOCO {

		// Verificações
		if($4.traducao.empty()) {
			cout << "Erro: A variável de controle do loop Precisa ser inicializada.\n";
			exit(1);
		}
		if (buscarVariavel($6.label) == -1) {
			yyerror("Variável '" + $6.label + "' não declarada no loop for.");
		}
		if (pilha[buscarVariavel($6.label)][$6.label].tipo != "bool") {
			yyerror("Condição do loop for deve ser do tipo booleano, mas é '" + pilha[buscarVariavel($5.label)][$5.label].tipo + "'.");
		}
		if (buscarVariavel($8.label) == -1) {
			yyerror("Variável '" + $7.label + "' não declarada no loop for.");
		}


		// Geração de código
		stringstream ss;
		string temp = pilha[buscarVariavel($6.label)][$6.label].endereco_memoria;
		string rotuloBreak = pilhaDeRotulosDeLaços.back().rotuloBreak;
		string rotuloContinue = pilhaDeRotulosDeLaços.back().rotuloContinue;

		ss << "\n";

		ss << qtdTab(-1) << "{\n"; // Abre a pilha de variáveis para o loop
		ss << fecharPilha().str(); // Fecha a pilha de variáveis antes do loop
		ss << "\n";

		ss << $4.traducao; // Traduz a expressão de inicialização

		ss << qtdTab(1) << "BeginFor" << defgoto << ":\n";

		ss << $6.traducao; // Traduz a expressão condicional

		ss << "\n";

		ss << qtdTab(1) << "if (!" << temp << ") goto " << rotuloBreak << ";\n";

		ss << "\n";

		ss << $10.traducao; // Traduz o bloco do loop

		ss << "\n"; // Adiciona uma nova linha para melhor legibilidade

		ss << qtdTab(1) << rotuloContinue << ":\n";

		ss << $8.traducao; // Traduz a expressão de iteração

		ss << qtdTab(1) << "goto BeginFor" << defgoto << ";\n";

		ss << qtdTab(1) << rotuloBreak << ":\n";

		ss << qtdTab() << "}\n"; // Fecha a pilha de variáveis do loop
		
		defgoto++; // Incrementa o contador de blocos de loop
		$$.traducao = ss.str();
	}
	| TK_BREAK ';' {
        if (pilhaDeRotulosDeLaços.empty()) {
            yyerror("'break' fora de um laco");
        }
        stringstream ss;
        // Pula para o rótulo de 'break' do laço mais interno (o que está no topo da pilha)
        ss << qtdTab() << "goto " << pilhaDeRotulosDeLaços.back().rotuloBreak << ";\n";
        $$.traducao = ss.str();
    }
	| TK_CONTINUE ';' {
        if (pilhaDeRotulosDeLaços.empty()) {
            yyerror("'continue' fora de um laco");
        }
        stringstream ss;
        // Pula para o rótulo de 'continue' do laço mais interno
        ss << qtdTab() << "goto " << pilhaDeRotulosDeLaços.back().rotuloContinue << ";\n";
        $$.traducao = ss.str();
    }
;

COND_IF:
	 TK_IF '(' EXPR ')' BLOCO COND_ELSE %prec LOWER_THAN_ELSE {

		// Verificações
		if (buscarVariavel($3.label) == -1) {
			cout << "Erro: Variável '" << $3.label << "' não declarada na condição do if.\n";
			exit(1);
		}
		if (pilha[buscarVariavel($3.label)][$3.label].tipo != "bool") {
			cout << "Erro: Condição do if deve ser do tipo booleano, mas é '" << pilha[buscarVariavel($3.label)][$3.label].tipo << "'.\n";
			exit(1);
		}

		// Geração de código
		stringstream ss;
		string temp = pilha[buscarVariavel($3.label)][$3.label].endereco_memoria; // Endereço de memória da variável condicional

		ss << "\n";

		ss << qtdTab(-1) << "{\n"; // Abre a pilha de variáveis para o if

		ss << fecharPilha().str(); // Fecha a pilha de variáveis antes do if

		ss << "\n";

		ss << $3.traducao; // Traduz a expressão condicional

		ss << qtdTab(1) << "if (!" << temp << ") goto EndIf" << defgoto << ";\n";

		ss << $5.traducao; // Traduz o bloco do if

		if (!$6.traducao.empty()) {
			ss << qtdTab(1) << "goto EndElse" << defgoto << ";\n"; // Se não houver else-if, pula para o final
		} 

		ss << qtdTab(1) << "EndIf" << defgoto << ":\n";

		ss << "\n";

		ss << $6.traducao; // Traduz o bloco do else-if, se houver
		
		if (!$6.traducao.empty()) {
			ss << qtdTab(1) << "EndElse" << defgoto << ":\n"; // Marca o final do if/else
		}

		ss << qtdTab() << "}\n"; // Fecha a pilha de variáveis do if
		tempElse = 0; // Reseta o contador de else-if
		defgoto++; // Incrementa o contador de blocos de if/else

		$$.traducao = ss.str();
	}
	| TK_IF '(' EXPR ')' BLOCO COND_ELSE TK_ELSE BLOCO %prec TK_ELSE {

		// Verificações
		if (buscarVariavel($3.label) == -1) {
			cout << "Erro: Variável '" << $3.label << "' não declarada na condição do if.\n";
			exit(1);
		}
		if (pilha[buscarVariavel($3.label)][$3.label].tipo != "bool") {
			cout << "Erro: Condição do if deve ser do tipo booleano, mas é '" << pilha[buscarVariavel($3.label)][$3.label].tipo << "'.\n";
			exit(1);
		}

		// Geração de código
		stringstream ss;
		string temp = pilha[buscarVariavel($3.label)][$3.label].endereco_memoria; // Endereço de memória da variável condicional

		ss << "\n";

		ss << qtdTab(-1) << "{\n"; // Abre a pilha de variáveis para o if

		ss << fecharPilha().str(); // Fecha a pilha de variáveis antes do if
		
		ss << "\n";

		ss << $3.traducao; // Traduz a expressão condicional

		ss << qtdTab(1) << "if (!" << temp << ") goto EndIf" << defgoto << ";\n";

		ss << $5.traducao; // Traduz o bloco do if
		
		ss << qtdTab(1) << "goto EndElse" << defgoto << ";\n";

		ss << qtdTab(1) << "EndIf" << defgoto << ":\n";

		ss << $6.traducao; // Traduz o bloco do else-if, se houver

		ss << $8.traducao; // Traduz o bloco do else

		if (!$8.traducao.empty()) {
			ss << qtdTab(1) << "EndElse" << defgoto << ":\n"; // Se houver else, pula para o final
		}

		ss << qtdTab() << "}\n"; // Fecha a pilha de variáveis do if/else

		tempElse = 0; // Reseta o contador de else-if
		defgoto++; // Incrementa o contador de blocos de if/else

		$$.traducao = ss.str();
	} 
;
COND_ELSE:
	TK_ELSE_IF '(' EXPR ')' BLOCO COND_ELSE %prec LOWER_THAN_ELSE {
		
		// Verificações
		if (buscarVariavel($3.label) == -1) {
			cout << "Erro: Variável '" << $3.label << "' não declarada na condição do else-if.\n";
			exit(1);
		}
		if (pilha[buscarVariavel($3.label)][$3.label].tipo != "bool") {
			cout << "Erro: Condição do else-if deve ser do tipo booleano, mas é '" << pilha[buscarVariavel($3.label)][$3.label].tipo << "'.\n";
			exit(1);
		}

		// Geração de código

		stringstream ss;
		string temp = pilha[buscarVariavel($3.label)][$3.label].endereco_memoria; // Endereço de memória da variável condicional

		ss << "\n";

		ss << $3.traducao; // Traduz a expressão condicional do else-if

		ss << qtdTab() << "if (!" << temp << ") goto EndElseIf" << tempElse << ";\n";

		ss << $5.traducao; // Traduz o bloco do else-if

		ss << qtdTab() << "goto EndElse" << defgoto << ";\n";

		ss << qtdTab() << "EndElseIf" << tempElse++ << ":\n";

		$$.traducao = ss.str() + $6.traducao; // Combina com a tradução do bloco do else-if
	}
	| 
	{
		$$.traducao = "";
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
        $$.label = $1.label;
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
		stringstream ss;
		ss = veririficarTipo($2.label, "!", "");
		$$.label = "t" + to_string(tempVar-1);
		$$.traducao = $2.traducao + ss.str();
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
	string tipo2 = "";
	string endereco1 = pilha[buscarVariavel(var1)][var1].endereco_memoria;
	string endereco2 = "";

	if(var2 != ""){
		endereco2 = pilha[buscarVariavel(var2)][var2].endereco_memoria; // Se não houver segundo operando, assume 0
		tipo2 = pilha[buscarVariavel(var2)][var2].tipo; // Tipo padrão para operações unárias
	}

	if(tipo1 == "string" && tipo2 == "string" && operador == "+") {
		operador = "<>";
	}
	
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
			string temp = "t" + to_string(tempVar);
			adicionaVar(temp, "float", true);
			string temp2 = "t" + to_string(tempVar);
			adicionaVar(temp2, "float", true);

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
		else if(tipo1 == "int" || tipo1 == "float"){
			string temp = "t" + to_string(tempVar);
			adicionaVar(temp, tipo1, true);
			ss << qtdTab() << temp << " = " << endereco1 << " " << operador << " " << endereco2 << ";\n";
		}
		else{
			cout << "Erro: Operador aritmético: " << operador << " só pode ser usado com tipos numéricos.\n";
			exit(1);
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
				adicionaVar(temp, "float", true);
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, "bool", true);
				ss << qtdTab() << temp << " = (float)" << endereco1 << ";\n";
				ss << qtdTab() << temp2 << " = " << temp << " " << operador << " " << endereco2 << ";\n";
			}
			else if(tipo1 == "float" && tipo2 == "int"){
				string temp = "t" + to_string(tempVar);
				adicionaVar(temp, "float", true);
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
		else if (tipo1 == "int" || tipo1 == "float" || tipo1 == "bool"){
			string temp = "t" + to_string(tempVar);
			adicionaVar(temp, "bool", true);
			ss << qtdTab() << temp << " = ("<< endereco1 <<" "<< operador <<" "<< endereco2<<");\n";
		}
		else{
			cout << "Erro: Operador de comparação " << operador << " só pode ser usado com tipos numéricos ou booleanos.\n";
			exit(1);
		}
	}
	else if(operador == "!" && var2 == ""){
		if(tipo1 != "bool"){
			cout << "Erro: Operador lógico '!' só pode ser usado com tipos booleanos.\n";
			exit(1);
		}
		string temp = "t" + to_string(tempVar);
		adicionaVar(temp, "bool", true);
		ss << qtdTab() << temp << " = !" << endereco1 << ";\n";
	}

	// operações com stings
	// <> concatenação
	else if(operador == "<>"){
		precisa_get_length = true;
		if(tipo1 != "string" || tipo2 != "string"){
			cout << "Erro: Operador de concatenação '<>' só pode ser usado com strings.\n";
			exit(1);
		}

		string temp = "t" + to_string(tempVar);
		adicionaVar(temp, "int", true);
		string temp2 = "t" + to_string(tempVar);
		adicionaVar(temp2, "int", true);
		string temp3 = "t" + to_string(tempVar);
		adicionaVar(temp3, "int", true);
		string temp4 = "t" + to_string(tempVar);
		adicionaVar(temp4, "int", true);
		string temp5 = "t" + to_string(tempVar);
		adicionaVar(temp5, "string", true);

		// Usando o Len
		ss << qtdTab() << temp << " = Len(" << endereco1 << ");\n";
		ss << qtdTab() << temp2 << " = Len(" << endereco2 << ");\n";

		// Soma das memorias
		ss << qtdTab() << temp3 << " = " << temp << " + " << temp2 << ";\n";
		ss << qtdTab() << temp4 << " = " << temp3 << " + 1;\n";
	
		// Alocando memória
		ss << qtdTab() << temp5 << " = (char*)malloc(" << temp4 << ");\n";

		// Iserindo a string
		ss << qtdTab() << "strcpy(" << temp5 << ", " << endereco1 << ");\n";
		ss << qtdTab() << "strcat(" << temp5 << ", " << endereco2 << ");\n";
	}

	else if(operador == ">" || operador == "<" || operador == ">=" || operador == "<="){
		if(tipo1 != tipo2){
			if(tipo1 == "int" && tipo2 == "float"){
				string temp = "t" + to_string(tempVar);
				adicionaVar(temp, "float", true);
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, "bool", true);
				ss << qtdTab() << temp << " = (float)" << endereco1 << ";\n";
				ss << qtdTab() << temp2 << " = " << temp << " " << operador << " " << endereco2 << ";\n";
			}
			else if(tipo1 == "float" && tipo2 == "int"){
				string temp = "t" + to_string(tempVar);
				adicionaVar(temp, "float", true);
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

void addPilhaLaco(string b, string c){
	RotulosDeLaço temp;
	temp.rotuloBreak = b;
	temp.rotuloContinue = c;

	pilhaDeRotulosDeLaços.push_back(temp);
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
