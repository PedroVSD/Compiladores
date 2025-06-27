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
void adicionaVar(string nome, string tipo, bool temp = false,bool contador = false, bool malocada = false);
stringstream veririficarTipo(string var1, string operador, string var2 = "");
void criarPilha();
void addPilhaLaco(string b, string c);
stringstream fecharPilha();
stringstream fecharPilha(stringstream& ss);
int buscarVariavel(string nome);
string qtdTab(int dif = 0);
string generateSwitchCases(string caseData, string switchVar, string switchId); 

// Contadores globais
int tempVar = 0;
int defVar = 0;
int defbloco = 0;
int defgoto = 0;
int tempElse = 0;
string current_switch_var = "";

// Flag para gerar a funções
bool atribuicaoGlobal = false;
bool precisa_get_length = false;
bool precisa_input_string = false;
bool precisa_input_bool = false;

struct atributos {
	string label;
	string traducao;
};

// Estrutura para armazenar informações de variáveis
struct tabela{
	string tipo;
	string endereco_memoria;
	bool temporaria;
	bool contador;
	bool malocada;
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
%token TK_SWITCH TK_CASE TK_DEFAULT
%token TK_QUICKSORT TK_CRIAR_VETOR TK_IMPRIMIR_VETOR


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
		cout << "#include\"quicksort.h\"\n\n";
		
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
		if (precisa_input_string) {
            cout << "\n// Le uma string da entrada ate o espaco ou nova linha\n";
            cout << "char* input_string() {\n"
			     << "    int scanf_result;\n	int flag_is_terminator;\n	int flag_is_newline;\n	int flag_is_space;\n 	int flag_is_full;\n"
                 << "    char c;\n"
				 << "    char* buffer;\n"
				 << " 	int len;\n"                 
				 << "    int capacity;\n	capacity = 16;\n"
                 << "    len = 0;\n"
                 << "    buffer = (char*)malloc(capacity);\n"
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
		if(precisa_input_bool) {
			cout << "\n// Le um valor booleano da entrada\n";
			cout << "int input_bool() {\n"
				 << "    char c;\n"
				 << "    scanf(\"%c\", &c);\n"
				 << "    aux = c == 't';\n"
				 << "    if (!aux) goto False;\n"
				 << "    scanf(\"%c\", &c);\n"
				 << "    aux = c == 'r';\n"
				 << "    if (!aux) goto False;\n"				
				 << "    scanf(\"%c\", &c);\n"
				 << "    aux = c == 'u';\n"
				 << "    if (!aux) goto False;\n"				 
				 << "    scanf(\"%c\", &c);\n"
				 << "    aux = c == 't';\n"
				 << "    if (!aux) goto False;\n"				 
				 << "    return 1;\n"
				 << "False:\n"
				 << "    return 0;\n"
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
		if($1.traducao.empty()) {
			$$.traducao = $2.traducao;
		} else {
			stringstream ss;
			// função para atribuir os valores das variaveis globais
			ss 	<< "\nvoid D() //Resolve o Problema da atribuição \n{\n"
				<< $1.traducao
				<< "}\n\n";
			$$.traducao = ss.str() + $2.traducao;
		}
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

		ss << "{\n";

		ss << $4.traducao;

		ss << "}\n\n";

		$$.traducao = ss.str();
	  }
;

BLOCO: { criarPilha(); } '{' COMANDOS '}' {
	stringstream ss, free;

	// Declarações das variáveis
	string decls;

	// se estivermos dentro de um loop, jogamos o decls na nova pilha do topo
	tabela_simbolos topPilha;
	if(pilhaDeRotulosDeLaços.size() > 0) {
		topPilha = pilha.back();
		fecharPilha(free);
	}
	else {
		decls = fecharPilha(free).str();
	}
	// juntar a tabela de símbolos do topo com a tabela de símbolos do bloco
	
	if(pilhaDeRotulosDeLaços.size() > 0) {
		pilha.back().insert(topPilha.begin(), topPilha.end());
	}



	if(defbloco == 1 && atribuicaoGlobal){ss << qtdTab(1) << "D();\n";  }
	ss << decls;

	if(!decls.empty() && !$3.traducao.empty()) {
		ss << "\n";
	}

	// Comandos dentro do bloco
    ss << $3.traducao;

	// Se o bloco for o principal, adiciona retorno
	if(defbloco == 1) { 
		ss << "\n" << qtdTab(1) << free.str();	
		ss << "\n" << qtdTab(1) << "return 0;\n"; 
	}

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
	| SWITCH_STMT { $$.traducao = $1.traducao; }
	| QUICKSORT_CMD ';' { $$.traducao = $1.traducao; }
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
        if (tipo == "string") {
            precisa_input_string = true; 
            ss_code << qtdTab() << c_nome << " = input_string();\n";
		}
		else if (tipo == "bool") {
			precisa_input_bool = true; 
			ss_code << qtdTab() << c_nome << " = input_bool();\n";
			}
        else {
            ss_code << qtdTab() << "scanf(\"" << tipomascara[tipo] << "\", &" << c_nome << ");\n";
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

        if (tipo == "string") {
            precisa_input_string = true; 
            ss_code << qtdTab() << c_nome << " = input_string();\n";
		}
		else if (tipo == "bool") {
			precisa_input_bool = true;
			ss_code << qtdTab() << c_nome << " = input_bool();\n";
			}
        else {
            ss_code << qtdTab() << "scanf(\"" << tipomascara[tipo] << "\", &" << c_nome << ");\n";
        }
        
        $$.traducao = $1.traducao + ss_code.str();
    }
;

DECLARACAO:
      DECLAR_VAR ';' DECLARACAO 
	  {
		if(!$1.traducao.empty()) {
			atribuicaoGlobal = true; // Marca que há atribuição global
		}
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

		ss << qtdTab(1) << "if (!" << temp << ") goto "<< rotuloBreak << ";";

		ss << $6.traducao; // Traduz o bloco do loop

		ss << "\n"; // Adiciona uma nova linha para melhor legibilidade

		ss << $4.traducao; // Reavalia a condição do loop

		ss << qtdTab(1) << "goto " << rotuloContinue << ";\n";

		ss << qtdTab(1) << rotuloBreak << ":\n";

		ss << qtdTab() << "}\n"; // Fecha a pilha de variáveis do loop

		// tira o último rótulo de laços da pilha
		pilhaDeRotulosDeLaços.pop_back();

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

		ss << qtdTab(1) << "if (" << temp << ") goto " << rotuloContinue << ";\n";
		
		ss << qtdTab(1) << rotuloBreak << ":\n";
		
		ss << qtdTab() << "}\n"; // Fecha a pilha de variáveis do loop
		
		ss << "\n";

		pilhaDeRotulosDeLaços.pop_back();
		
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
		
		pilhaDeRotulosDeLaços.pop_back();

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

		// Verifica se ta sendo usando no switch
		if(pilhaDeRotulosDeLaços.back().rotuloContinue == "EndSwitch" + to_string(defgoto)) {
			cout << "Erro: 'continue' só pode ser usando em estrutura de loop.\n";
			exit(1);
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
//Até a linha 858 é relacionado ao switch
SWITCH_STMT:
    { 
        criarPilha(); 
        addPilhaLaco("EndSwitch" + to_string(defgoto), "EndSwitch" + to_string(defgoto)); 
    } 
    TK_SWITCH '(' EXPR ')' {
        // Armazenar a variável do switch globalmente
        if (buscarVariavel($4.label) == -1) {
            yyerror("Variável '" + $4.label + "' não declarada no switch.");
        }
        current_switch_var = pilha[buscarVariavel($4.label)][$4.label].endereco_memoria;
    }
    '{' SIMPLE_CASE_LIST '}' {
        
        // Geração de código
        stringstream ss;
        string rotuloEnd = pilhaDeRotulosDeLaços.back().rotuloBreak;
        string switch_id = to_string(defgoto);
        
        ss << qtdTab(-1) << "{\n";
        ss << fecharPilha().str();
        ss << "\n";
        
        // Avalia a expressão do switch

        ss << $4.traducao;
        
        // Gera os cases
        ss << $8.traducao;
        
        // Label de saída do switch
        ss << qtdTab(1) << rotuloEnd << ":\n";
        ss << qtdTab() << "}\n";
        
        // Remove da pilha de laços
        pilhaDeRotulosDeLaços.pop_back();
        defgoto++;
        
        // Limpar a variável global
        current_switch_var = "";
        
        $$.traducao = ss.str();
    }
;

SIMPLE_CASE_LIST:
    SIMPLE_CASE SIMPLE_CASE_LIST {
        $$.traducao = $1.traducao + $2.traducao;
    }
    | SIMPLE_DEFAULT {
        $$.traducao = $1.traducao;
    }
    | /* vazio */ {
        $$.traducao = "";
    }
;

SIMPLE_CASE:
    TK_CASE TK_NUM ':' COMANDOS {
        stringstream ss;
        string case_id = to_string(defgoto);
        
        // Mesmo padrão do if: comparação em três endereços
        string temp_val = "t" + to_string(tempVar);
        adicionaVar(temp_val, "int", true);
        
        string temp_comp = "t" + to_string(tempVar);
        adicionaVar(temp_comp, "bool", true);
        
        ss <<"\n"<< qtdTab() << temp_val << " = " << $2.traducao << ";\n";
        ss << qtdTab() << temp_comp << " = " << current_switch_var << " == " << temp_val << ";\n\n";
        ss << qtdTab() << "if (!" << temp_comp << ") goto NextCase" << case_id << "_" << $2.traducao << ";\n";
        ss << $4.traducao;
        ss << qtdTab() << "NextCase" << case_id << "_" << $2.traducao << ":\n";
        
        $$.traducao = ss.str();
    }
;

SIMPLE_DEFAULT:
    TK_DEFAULT ':' COMANDOS {
        stringstream ss;
        
        ss << "\n" << $3.traducao;
        
        $$.traducao = ss.str();
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
	| EXPR_TERM '%' EXPR_ATOM %prec '%' {
		stringstream ss;
		string var1 = $1.label;
		string var2 = $3.label;
		ss = veririficarTipo(var1, "%", var2);
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
        string chave_temp_sl = "t" + to_string(tempVar);
        
        // 2. Adicionar à tabela com tipo "string"
        adicionaVar(chave_temp_sl, "string", true);

        // 3. Obter o nome C da temporária (será algo como "tN")
        string c_nome_sl = pilha[pilha.size()-1][chave_temp_sl].endereco_memoria;
        
        // 4. Gerar código C
        // $1.traducao do lexer já é o literal C com aspas (ex: "\"ola\"")
        stringstream ss_code;
        ss_code << qtdTab() << c_nome_sl << " = " << $1.traducao << ";\n";

		pilha[pilha.size()-1][chave_temp_sl].malocada = true; // Marca como malocada
        
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

QUICKSORT_CMD:
    TK_QUICKSORT '(' TK_ID ',' TK_NUM ')' {
        if (buscarVariavel($3.label) == -1) {
            yyerror("Vetor '" + $3.label + "' não declarado.");
        }
        
        string tipo_var = pilha[buscarVariavel($3.label)][$3.label].tipo;
        if (tipo_var != "int*" && tipo_var != "vetor_int") {
            yyerror("QuickSort só funciona com vetores de inteiros.");
        }
        
        stringstream ss;
        string endereco_vetor = pilha[buscarVariavel($3.label)][$3.label].endereco_memoria;
        
        ss << qtdTab() << "quick_sort_completo(" << endereco_vetor << ", " << $5.traducao << ");\n";
        
        $$.traducao = ss.str();
    }
    | TK_CRIAR_VETOR '(' TK_ID ',' TK_NUM ')' {
        // Verificar se variável já existe
        if (buscarVariavel($3.label) != -1) {
            yyerror("Variável '" + $3.label + "' já declarada.");
        }
        
        adicionaVar($3.label, "int*", false);
        
        stringstream ss;
        string endereco_vetor = pilha[pilha.size()-1][$3.label].endereco_memoria;
        
        ss << qtdTab() << endereco_vetor << " = criar_vetor(" << $5.traducao << ");\n";
        
        $$.traducao = ss.str();
    }
    | TK_IMPRIMIR_VETOR '(' TK_ID ',' TK_NUM ')' {
        if (buscarVariavel($3.label) == -1) {
            yyerror("Vetor '" + $3.label + "' não declarado.");
        }
        
        stringstream ss;
        string endereco_vetor = pilha[buscarVariavel($3.label)][$3.label].endereco_memoria;
        
        ss << qtdTab() << "imprimir_vetor(" << endereco_vetor << ", " << $5.traducao << ");\n";
        
        $$.traducao = ss.str();
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

void adicionaVar(string nome, string tipo, bool temp,bool c, bool malloc) {
	if (pilha[pilha.size()-1].find(nome) == pilha[pilha.size()-1].end()) {
		pilha[pilha.size()-1][nome].tipo = tipo;
		pilha[pilha.size()-1][nome].temporaria = temp;
		pilha[pilha.size()-1][nome].contador = c;
		pilha[pilha.size()-1][nome].malocada = malloc;
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
			
			// verifica se endereco2 é malocada
			if(pilha[buscarVariavel(var2)][var2].malocada){
				// se for, endereco 1 deve ser malocada também
				pilha[buscarVariavel(var1)][var1].malocada = true;
				// e endereco2 deixa de ser malocada
				pilha[buscarVariavel(var2)][var2].malocada = false;
			}
		}
		return ss;
	}	
	else if(operador == "+" || operador == "-" || operador == "*" || operador == "/" || operador == "%"){		
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
		adicionaVar(temp, "string", true);
		string temp2 = "t" + to_string(tempVar);

		if(endereco2 != endereco1){adicionaVar(temp2, "string", true);}
		else {temp2 = temp;}

		string temp3 = "t" + to_string(tempVar);
		adicionaVar(temp3, "bool", true);
		string temp4 = "t" + to_string(tempVar);
		if(pilhaDeRotulosDeLaços.size() > 0){
			adicionaVar(temp4, "bool", true, true);
		}
		string temp5 = "t" + to_string(tempVar);
		adicionaVar(temp5, "int", true);
		string temp6 = "t" + to_string(tempVar);
		adicionaVar(temp6, "int", true);
		string temp7 = "t" + to_string(tempVar);
		adicionaVar(temp7, "int", true);
		string temp8 = "t" + to_string(tempVar);
		adicionaVar(temp8, "int", true);
		string temp9 = "t" + to_string(tempVar);
		adicionaVar(temp9, "string", true);

		// Criando novo endereço de memória
		ss << "\n\n" << qtdTab() << temp << " = " << endereco1 << ";\n";
		if(endereco2 != endereco1){
			ss << qtdTab() << temp2 << " = " << endereco2 << ";\n";
		}
		if(pilhaDeRotulosDeLaços.size() > 0){
			ss << qtdTab() << temp3 << " = ("<<temp4 <<" == 0);\n"; // Variável temporária para verificar se é string
			ss << qtdTab() << "if(!" << temp3 << ") goto NoFlag;\n"; // Verifica se é string
			ss << qtdTab() << temp4 << " = 0;\n"; // Variável temporária para verificar se é string
			ss << qtdTab() << "NoFlag" << ":\n"; // Rótulo para pular se não for string
		}
		// Usando o Len
		ss << qtdTab() << temp5 << " = Len(" << endereco1 << ");\n";
		ss << qtdTab() << temp6 << " = Len(" << endereco2 << ");\n";

		// Soma das memorias
		ss << qtdTab() << temp7 << " = " << temp5 << " + " << temp6 << ";\n";
		ss << qtdTab() << temp8 << " = " << temp7 << " + 1;\n";
	
		// Alocando memória
		ss << qtdTab() << temp9 << " = (char*)malloc(" << temp8 << ");\n";

		// Iserindo a string
		ss << qtdTab() << "strcpy(" << temp9 << ", " << temp << ");\n";
		ss << qtdTab() << "strcat(" << temp9 << ", " << temp2 << ");\n";

		// liberando memória
		if(pilhaDeRotulosDeLaços.size() > 0){
			ss << qtdTab() << "if(!" << temp4 << ") goto Nofree;\n";
			ss << qtdTab() << "free(" << temp << ");\n";
			if(endereco2 != endereco1){	ss << qtdTab() << "free(" << temp2 << ");\n";}
			ss << qtdTab(-1) << "Nofree:\n\n";
			ss << qtdTab() << temp4 << " = 1;\n"; // Marca que a string foi alocada
		}
		// Atualizando o endereço de memória
		pilha[pilha.size()-1][temp9].malocada = true;
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

stringstream fecharPilha(stringstream& frees) {
	stringstream ss, count, all;
	// Controla a tabulação

	if(defbloco > 0){
		for(const auto& [nome, info] : pilha.back()) {
			if(info.temporaria)
				ss << qtdTab() << tipoTraducao[info.tipo] <<" "<< info.endereco_memoria << ";\n";
			else
				ss << qtdTab() << tipoTraducao[info.tipo] <<" "<< info.endereco_memoria << ";\t //"<< nome << "\n";
			if(info.malocada){
				frees << qtdTab(-1) << "free(" << info.endereco_memoria << ");\n";
			}
			if(info.contador){
				count << qtdTab() << info.endereco_memoria << " = 0;\n";
			}
		}
		defbloco--;
		pilha.pop_back();
	}
	else{
		cout << "Erro: Pilha de escopo vazia.\n";
		exit(1);
	}
	all << ss.str() << count.str();
	return all;
}
stringstream fecharPilha() {
	stringstream ss;
	return fecharPilha(ss);
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

string generateSwitchCases(string caseData, string switchVar, string switchId) {
    stringstream ss;
    
    // Parse dos dados dos cases
    vector<string> cases;
    vector<string> comandos;
    bool hasDefault = false;
    string defaultComandos = "";
    
    // Separar cases e comandos (implementação simplificada)
    // Você precisará adaptar baseado na estrutura real dos seus dados
    
    string var_switch = pilha[buscarVariavel(switchVar)][switchVar].endereco_memoria;
    
    // Gerar comparações para cada case (mesmo padrão do if)
    for (int i = 0; i < cases.size(); i++) {
        string temp_comp = "t" + to_string(tempVar);
        adicionaVar(temp_comp, "bool", true);
        
        ss << qtdTab(1) << temp_comp << " = " << var_switch << " == " << cases[i] << ";\n";
        ss << qtdTab(1) << "if (!" << temp_comp << ") goto Case" << switchId << "_" << (i+1) << ";\n";
        ss << comandos[i];
        ss << qtdTab(1) << "goto EndSwitch" << switchId << ";\n";
        ss << qtdTab(1) << "Case" << switchId << "_" << (i+1) << ":\n";
    }
    
    // Default case se existir
    if (hasDefault) {
        ss << defaultComandos;
    }
    
    return ss.str();
}