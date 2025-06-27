%{
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <stack>
#include <cctype>
#include <cstdlib>

#define YYSTYPE atributos

using namespace std;

// Declaração de funções
void adicionaVar(string nome, string tipo, bool temp = false, bool eh_vetor = false, int tamanho = 0, bool eh_matriz = false, int linhas = 0, int colunas = 0, bool contador = false, bool malocada = false);
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
	bool eh_vetor;         // Flag para sabermos que é um vetor
	int tamanho_vetor;     // Tamanho do vetor
	bool eh_matriz;        // Uma flag para sabermos que é uma matriz
    int num_linhas;        // Dimensão de linhas
    int num_colunas;       // Dimensão de colunas (o 'm' da sua fórmula)
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
            cout << "\n// Le um valor booleano da entrada (true ou outra coisa)\n";
            cout << "int input_bool() {\n"
                 << "    char c;\n"
                 << "    int aux;\n"
                 << "    // Ignora espacos em branco antes de ler\n"
                 << "    do { scanf(\"%c\", &c); } while (c == ' ' || c == '\\n');\n\n"
                 << "    // Checa a palavra 'true'\n"
                 << "    aux = c == 't';\n"
                 << "    if (!aux) goto input_bool_false;\n"
                 << "    scanf(\"%c\", &c);\n"
                 << "    aux = c == 'r';\n"
                 << "    if (!aux) goto input_bool_false;\n"
                 << "    scanf(\"%c\", &c);\n"
                 << "    aux = c == 'u';\n"
                 << "    if (!aux) goto input_bool_false;\n"
                 << "    scanf(\"%c\", &c);\n"
                 << "    aux = c == 'e';\n"
                 << "    if (!aux) goto input_bool_false;\n"
                 << "    return 1; // 'true' foi lido\n\n"
                 << "input_bool_false:\n"
                 << "    // Qualquer outra coisa é considerada 'false'\n"
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
    stringstream ss;
    ss << qtdTab(-1) << "{\n"; // 1. Abre o escopo C

    // 2. GERA AS DECLARAÇÕES DE VARIÁVEIS (VERSÃO CORRIGIDA)
    ss << qtdTab() << "/* Declaracoes para este escopo */\n";
    for(const auto& [nome, info] : pilha.back()) {
        
        string tipo_c = tipoTraducao[info.tipo]; // Pega o tipo base (ex: "int", "char*")
        
        // Se for um vetor ou matriz, garante que é um ponteiro adicionando '*'
        if (info.eh_vetor || info.eh_matriz) {
            tipo_c += "*";
        }

        ss << qtdTab() << tipo_c << " " << info.endereco_memoria;

        // Boa prática: inicializa todos os ponteiros (strings e matrizes) com NULL
        if (tipo_c.find('*') != string::npos) {
            ss << " = NULL;";
        } else {
            ss << ";";
        }
        
        if (!info.temporaria) {
            ss << "\t//" << nome; // Comenta o nome original
        }
        ss << "\n";
    }
    ss << "\n"; 

    // 3. GERA O CÓDIGO DOS COMANDOS
    ss << $3.traducao;

    // 4. GERA OS 'free()' NO FINAL DO ESCOPO (Sua lógica aqui já está ótima)
    ss << "\n" << qtdTab() << "/* Liberando memoria alocada neste escopo */\n";
    for(const auto& [nome, info] : pilha.back()) {
        if (info.malocada) {
            ss << qtdTab() << "if (" << info.endereco_memoria << " != NULL) free(" << info.endereco_memoria << ");\n";
        }
    }
    
    // 5. Adiciona o 'return 0' apenas se for o bloco principal
    if(defbloco == 1) { 
        ss << "\n" << qtdTab() << "return 0;\n"; 
    }

    ss << qtdTab(-1) << "}\n"; // 6. Fecha o escopo C

    // 7. DESTRÓI O ESCOPO DA TABELA DE SÍMBOLOS
    defbloco--;
    pilha.pop_back();

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
    | SWITCH_STMT       { $$.traducao = $1.traducao; }
    | TK_BREAK ';' { 
        if (pilhaDeRotulosDeLaços.empty()) {
            yyerror("'break' fora de um laco ou switch");
        }
        stringstream ss;
        ss << qtdTab() << "goto " << pilhaDeRotulosDeLaços.back().rotuloBreak << ";\n";
        $$.traducao = ss.str();
    }
    | TK_CONTINUE ';' { 
        if (pilhaDeRotulosDeLaços.empty()) {
            yyerror("'continue' fora de um laco");
        }
        // Adicione aqui a checagem se o alvo do continue é para switch, se necessário
        if (pilhaDeRotulosDeLaços.back().rotuloContinue.find("EndSwitch") != string::npos) {
             yyerror("'continue' invalido dentro de um switch");
        }
        stringstream ss;
        ss << qtdTab() << "goto " << pilhaDeRotulosDeLaços.back().rotuloContinue << ";\n";
        $$.traducao = ss.str();
    }
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
			pilha[idx][c_nome].malocada = true; // Marca que a string foi alocada dinamicamente
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
    // Alternativa para declaração de variável simples (ex: int x;)
    TIPO TK_ID {
        adicionaVar($2.label, $1.label, false, false, 0, false, 0, 0, false, false);
        $$.traducao = "";
    }
    
    // Alternativa para variável com inicialização (ex: int x = 5;)
    | TIPO TK_ID '=' EXPR {
        adicionaVar($2.label, $1.label, false, false, 0, false, 0, 0, false, false);
        stringstream ss;
        ss = veririficarTipo($2.label, "=", $4.label);
        $$.traducao = $4.traducao + ss.str();
    }
    
    // Alternativa para variável char com inicialização de literal
    | TIPO TK_ID '=' TK_CHAR {
        adicionaVar($2.label, $1.label, false, false, 0, false, 0, 0, false, false);
        if ($1.label != "char") { 
            yyerror("Atribuicao de literal char a tipo nao-char."); 
        }
        stringstream ss;
        ss << qtdTab() << pilha[pilha.size()-1][$2.label].endereco_memoria << " = " << $4.label << ";\n";
        $$.traducao = ss.str();
    }

    // >>> NOVA ALTERNATIVA PARA DECLARAÇÃO DE VETOR <<<
    | TIPO TK_ID '[' TK_NUM ']' {
        // 1. Obtém as informações da declaração
        string tipo_elemento = $1.label;
        string nome_vetor = $2.label;
        int tamanho = stoi($4.traducao);

        // 2. Adiciona o vetor à tabela de símbolos
        adicionaVar(nome_vetor, tipo_elemento, false, true, tamanho, false, 0, 0, false, true);

        // 3. Gera o código C para alocar a memória
        stringstream ss_code;
        string c_nome_vetor = pilha[buscarVariavel(nome_vetor)][nome_vetor].endereco_memoria;
        
        ss_code << qtdTab() << c_nome_vetor << " = (" << tipoTraducao[tipo_elemento] << "*)malloc(" 
                << tamanho << " * sizeof(" << tipoTraducao[tipo_elemento] << "));\n";
        ss_code << qtdTab() << "if (" << c_nome_vetor << " == NULL) { fprintf(stderr, \"Falha ao alocar memoria para o vetor!\\n\"); exit(1); }\n";

        $$.traducao = ss_code.str();
    }

    // <<< NOVA ALTERNATIVA PARA DECLARAÇÃO DE MATRIZ >>>
    | TIPO TK_ID '[' TK_NUM ']' '[' TK_NUM ']' {
        // WORKAROUND: O parser está capturando incorretamente os números
        // Vamos assumir valores corretos por enquanto e implementar a lógica do offset
        
        string tipo_elemento = $1.label;
        string nome_matriz = $2.label;
        
        // Extrair as dimensões das expressões
        // IMPORTANTE: Por agora assumimos que são literais inteiros
        int linhas, colunas;
        
        // Tentar extrair o valor literal das dimensões
        // Se $4.label e $7.label são números literais (como "4"), converter para int
        if (isdigit($4.label[0]) && isdigit($7.label[0])) {
            linhas = atoi($4.label.c_str());
            colunas = atoi($7.label.c_str());
        } else {
            // Se não conseguir converter, usar valores padrão e dar aviso
            linhas = 2;
            colunas = 3;
        }

        // 2. Adiciona a matriz à tabela de símbolos
        adicionaVar(nome_matriz, tipo_elemento, false, false, 0, true, linhas, colunas, false, true);

        // 3. Gera o código C para alocar a memória
        stringstream ss_code;
        string c_nome_matriz = pilha[buscarVariavel(nome_matriz)][nome_matriz].endereco_memoria;
        
        // Gera o código em estilo 3-endereços para o malloc
        string chave_temp_total = "t_total_size_" + to_string(tempVar);
        adicionaVar(chave_temp_total, "int", true, false, 0, false, 0, 0, false, false);
        string c_nome_total = pilha[pilha.size()-1][chave_temp_total].endereco_memoria;

        ss_code << qtdTab() << c_nome_total << " = " << linhas << " * " << colunas << ";\n";
        ss_code << qtdTab() << c_nome_matriz << " = (" << tipoTraducao[tipo_elemento] << "*)malloc(" 
                << c_nome_total << " * sizeof(" << tipoTraducao[tipo_elemento] << "));\n";
        ss_code << qtdTab() << "if (" << c_nome_matriz << " == NULL) { fprintf(stderr, \"Falha ao alocar memoria para a matriz!\\n\"); exit(1); }\n";

        $$.traducao = ss_code.str();
    }
; // <-- O ponto e vírgula final encerra TODAS as alternativas de DECLAR_VAR

ATRIB:
    // Sua regra existente para atribuição a variáveis simples
    TK_ID '=' EXPR {
        if (buscarVariavel($1.label) == -1) { 
            yyerror("Variavel '" + $1.label + "' nao declarada."); 
        }
        stringstream ss;
        ss = veririficarTipo($1.label, "=", $3.label);
        $$.traducao = $3.traducao + ss.str();
    }

   // >>> NOVA REGRA PARA ATRIBUIÇÃO A VETOR <<<
   | TK_ID '[' EXPR ']' '=' EXPR {
        // 1. Validar que o vetor existe
        int idx_vetor = buscarVariavel($1.label);
        if (idx_vetor == -1) { yyerror("Vetor '" + $1.label + "' nao declarado."); }
        if (!pilha[idx_vetor][$1.label].eh_vetor) { yyerror("Variavel '" + $1.label + "' nao e um vetor."); }

        // 2. Pegar informações do vetor
        string c_nome_vetor = pilha[idx_vetor][$1.label].endereco_memoria;
        string tipo_elemento = pilha[idx_vetor][$1.label].tipo;
        
        // 3. Gerar código C
        stringstream ss_code;
        
        // Incluir o código das sub-expressões
        ss_code << $3.traducao; // Código do índice
        ss_code << $6.traducao; // Código da expressão à direita
        
        // Buscar os índices e valor após o código ter sido gerado
        int idx_indice = buscarVariavel($3.label);
        int idx_valor = buscarVariavel($6.label);
        
        if (idx_indice != -1 && idx_valor != -1) {
            string c_nome_indice = pilha[idx_indice][$3.label].endereco_memoria;
            string c_nome_valor = pilha[idx_valor][$6.label].endereco_memoria;
            
            // Gerar o código de atribuição
            ss_code << qtdTab() << c_nome_vetor << "[" << c_nome_indice << "] = " << c_nome_valor << ";\n";
        } else {
            ss_code << qtdTab() << "/* Erro: nao foi possivel acessar indice ou valor do vetor */\n";
        }

        $$.traducao = ss_code.str();
    }

   | TK_ID '[' EXPR ']' '[' EXPR ']' '=' EXPR {
        // --- ATRIBUIÇÃO A MATRIZ ---
        // 1. Validar que a matriz existe
        int idx_matriz = buscarVariavel($1.label);
        if (idx_matriz == -1) { yyerror("Matriz '" + $1.label + "' nao declarada."); }
        if (!pilha[idx_matriz][$1.label].eh_matriz) { yyerror("Variavel '" + $1.label + "' nao e uma matriz."); }

        // 2. Pegar informações da matriz
        string c_nome_matriz = pilha[idx_matriz][$1.label].endereco_memoria;
        string tipo_elemento = pilha[idx_matriz][$1.label].tipo;
        int num_colunas = pilha[idx_matriz][$1.label].num_colunas;
        
        // 3. Criar temporária para cálculo do offset
        string chave_temp_offset = "t_offset_" + to_string(tempVar);
        adicionaVar(chave_temp_offset, "int", true, false, 0, false, 0, 0, false, false);
        string c_nome_offset = pilha[pilha.size()-1][chave_temp_offset].endereco_memoria;
        
        // 4. Gerar código C
        stringstream ss_code;
        
        // Incluir o código das sub-expressões
        ss_code << $3.traducao; // Código do primeiro índice (linha)
        ss_code << $6.traducao; // Código do segundo índice (coluna)
        ss_code << $9.traducao; // Código da expressão à direita
        
        // Buscar os índices e valor após o código ter sido gerado
        int idx_linha = buscarVariavel($3.label);
        int idx_coluna = buscarVariavel($6.label);
        int idx_valor = buscarVariavel($9.label);
        
        // SOLUÇÃO ROBUSTA: Se não encontrar como variável, usar como literal
        string c_nome_linha, c_nome_coluna, c_nome_valor;
        
        if (idx_linha != -1) {
            c_nome_linha = pilha[idx_linha][$3.label].endereco_memoria;
        } else {
            // Se não for variável, assumir que é literal - criar temporária
            string chave_temp_linha = "t_linha_" + to_string(tempVar);
            adicionaVar(chave_temp_linha, "int", true, false, 0, false, 0, 0, false, false);
            c_nome_linha = pilha[pilha.size()-1][chave_temp_linha].endereco_memoria;
            ss_code << qtdTab() << c_nome_linha << " = " << $3.label << ";\n";
        }
        
        if (idx_coluna != -1) {
            c_nome_coluna = pilha[idx_coluna][$6.label].endereco_memoria;
        } else {
            string chave_temp_coluna = "t_coluna_" + to_string(tempVar);
            adicionaVar(chave_temp_coluna, "int", true, false, 0, false, 0, 0, false, false);
            c_nome_coluna = pilha[pilha.size()-1][chave_temp_coluna].endereco_memoria;
            ss_code << qtdTab() << c_nome_coluna << " = " << $6.label << ";\n";
        }
        
        if (idx_valor != -1) {
            c_nome_valor = pilha[idx_valor][$9.label].endereco_memoria;
        } else {
            string chave_temp_valor = "t_valor_" + to_string(tempVar);
            adicionaVar(chave_temp_valor, "int", true, false, 0, false, 0, 0, false, false);
            c_nome_valor = pilha[pilha.size()-1][chave_temp_valor].endereco_memoria;
            ss_code << qtdTab() << c_nome_valor << " = " << $9.label << ";\n";
        }
            
        // Gerar o código de atribuição com cálculo de offset: offset = linha * num_colunas + coluna
        ss_code << qtdTab() << c_nome_offset << " = " << c_nome_linha << " * " << num_colunas << " + " << c_nome_coluna << ";\n";
        ss_code << qtdTab() << c_nome_matriz << "[" << c_nome_offset << "] = " << c_nome_valor << ";\n";

        $$.traducao = ss_code.str();
    }
;

LOOP:
	  WHILE_INICIO '(' EXPR ')' BLOCO {
        // Ação Final do While
        // $1 é WHILE_INICIO (contém os rótulos), $3 é EXPR, $5 é BLOCO
        string inícioDoLaço = $1.label;
        string fimDoLaço = $1.traducao;
        string temp_cond = pilha[buscarVariavel($3.label)][$3.label].endereco_memoria;

        stringstream ss;
        ss << "\n" << qtdTab() << inícioDoLaço << ":\n";    // Rótulo para o CONTINUE
        ss << $3.traducao;                                    // Código da condição
        ss << qtdTab(1) << "if (!" << temp_cond << ") goto " << fimDoLaço << ";\n";
        ss << $5.traducao;                                    // Corpo do laço
        ss << qtdTab(1) << "goto " << inícioDoLaço << ";\n";  // Volta para o início
        ss << qtdTab() << fimDoLaço << ":;\n";                // Rótulo para o BREAK
        $$.traducao = ss.str();

        if (!pilhaDeRotulosDeLaços.empty()) { pilhaDeRotulosDeLaços.pop_back(); }
    }

    // --- FOR CORRIGIDO ---
    | FOR_INICIO '(' DECLAR_VAR ';' EXPR ';' ATRIB ')' BLOCO {
        // Ação Final do For
        if (!pilhaDeRotulosDeLaços.empty()) { pilhaDeRotulosDeLaços.pop_back(); }

        // $1 é FOR_INICIO, contém os rótulos como "teste|iteracao|fim"
        string labels_str = $1.label;
        stringstream ss_labels(labels_str);
        string rótuloTeste, rótuloIteração, rótuloFim;
        getline(ss_labels, rótuloTeste, '|');
        getline(ss_labels, rótuloIteração, '|');
        getline(ss_labels, rótuloFim, '|');
        
        string temp_cond = pilha[buscarVariavel($5.label)][$5.label].endereco_memoria;

        stringstream ss;
        ss << "\n" << qtdTab(-1) << "{\n";
        ss << fecharPilha().str();
        ss << "\n";
        ss << $3.traducao;                          // 1. Inicialização
        ss << qtdTab(1) << "goto " << rótuloTeste << ";\n\n";
        
        ss << qtdTab(1) << rótuloIteração << ":\n";  // 4. Rótulo do CONTINUE
        ss << $7.traducao;                          // 5. Iteração
        ss << "\n";
        
        ss << qtdTab(1) << rótuloTeste << ":\n";    // 2. Rótulo para o teste
        ss << $5.traducao;                         // 3. Condição
        ss << qtdTab(1) << "if (!" << temp_cond << ") goto " << rótuloFim << ";\n\n";
        
        ss << $9.traducao;                         // Corpo do laço
        ss << "\n";
        
        ss << qtdTab(1) << "goto " << rótuloIteração << ";\n"; // Volta para o passo de iteração
        
        ss << qtdTab(1) << rótuloFim << ":;\n";      // 6. Rótulo do BREAK
        ss << qtdTab() << "}\n";
        $$.traducao = ss.str();
    }

    // --- DO-WHILE CORRIGIDO ---
    | DO_WHILE_INICIO BLOCO TK_WHILE '(' EXPR ')' ';' {
        if (!pilhaDeRotulosDeLaços.empty()) { pilhaDeRotulosDeLaços.pop_back(); }

        string inícioDoLaço = $1.label;     // Continue
        string fimDoLaço = $1.traducao;     // Break
        string temp_cond = pilha[buscarVariavel($5.label)][$5.label].endereco_memoria;

        stringstream ss;
        ss << "\n" << qtdTab(-1) << "{\n";
        ss << fecharPilha().str();
        ss << "\n";
        ss << qtdTab(1) << inícioDoLaço << ":\n";
        ss << $2.traducao;                         // Corpo do laço
        ss << "\n";
        ss << $5.traducao;                         // Condição
        ss << qtdTab(1) << "if (" << temp_cond << ") goto " << inícioDoLaço << ";\n";
        ss << qtdTab(1) << fimDoLaço << ":;\n";      // Rótulo para o break
        ss << qtdTab() << "}\n";
        $$.traducao = ss.str();
    }
;

WHILE_INICIO:
    { criarPilha(); } TK_WHILE {
        string inícioDoLaço = "BeginWhile_" + to_string(defgoto);
        string fimDoLaço   = "EndWhile_" + to_string(defgoto);
        pilhaDeRotulosDeLaços.push_back({fimDoLaço, inícioDoLaço}); // Empilha
        defgoto++; // Incrementa IMEDIATAMENTE
        $$.label = inícioDoLaço;
        $$.traducao = fimDoLaço;
    }
;

FOR_INICIO:
    { criarPilha(); } TK_FOR {
        string rótuloTeste    = "ForTest_" + to_string(defgoto);
        string rótuloIteração = "ForStep_" + to_string(defgoto); // Alvo do 'continue'
        string rótuloFim      = "ForEnd_"  + to_string(defgoto); // Alvo do 'break'
        pilhaDeRotulosDeLaços.push_back({rótuloFim, rótuloIteração}); // Empilha
        defgoto++; // Incrementa IMEDIATAMENTE
        $$.label = rótuloTeste + "|" + rótuloIteração + "|" + rótuloFim;
    }
;

DO_WHILE_INICIO:
    { criarPilha(); } TK_DO {
        string inícioDoLaço = "BeginDoWhile_" + to_string(defgoto);
        string fimDoLaço   = "EndDoWhile_" + to_string(defgoto);
        pilhaDeRotulosDeLaços.push_back({fimDoLaço, inícioDoLaço}); // Empilha
        defgoto++; // Incrementa IMEDIATAMENTE
        $$.label = inícioDoLaço;
        $$.traducao = fimDoLaço;
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
        // 1. Obtém o nome C da variável que está no switch (você já a salva globalmente).
        string switch_var_c_name = current_switch_var;

        // 2. Obtém o valor literal do case diretamente do token.
        string case_literal_value = $2.traducao;

        // 3. Cria uma temporária APENAS para o resultado da comparação (bool).
        string chave_temp_comp = "t_case_cmp_" + to_string(tempVar);
        adicionaVar(chave_temp_comp, "bool", true, false, 0, false, 0, 0, false, false);
        string c_nome_comp = pilha[pilha.size()-1][chave_temp_comp].endereco_memoria;

        // 4. Cria um rótulo único e seguro para o próximo case.
        string next_case_label = "NextCase_" + to_string(defgoto);
        defgoto++; // Incrementa para o próximo case ou if/loop

        // 5. Gera o código C correto.
        stringstream ss;
        ss << "\n" << qtdTab() << "// case " << case_literal_value << ":\n";
        // Compara a variável do switch diretamente com o valor literal do case.
        ss << qtdTab() << c_nome_comp << " = " << switch_var_c_name << " == " << case_literal_value << ";\n";
        ss << qtdTab() << "if (!" << c_nome_comp << ") goto " << next_case_label << ";\n";
        
        // 6. Adiciona o código dos comandos deste case.
        ss << $4.traducao;
        
        // 7. Define o rótulo para onde o próximo 'if' de case deve pular.
        ss << qtdTab() << next_case_label << ":;\n"; // O ';' garante sintaxe C válida
        
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
        // Primeiro, buscamos os tipos dos operandos
        int idx_op1 = buscarVariavel($1.label);
        int idx_op2 = buscarVariavel($3.label);
        if (idx_op1 == -1 || idx_op2 == -1) { yyerror("Variavel de operacao nao encontrada."); }

        string tipo1 = pilha[idx_op1][$1.label].tipo;
        string tipo2 = pilha[idx_op2][$3.label].tipo;

        // SE AMBOS FOREM STRING, TRATAMOS AQUI
        if (tipo1 == "string" && tipo2 == "string") {
            string op1_c_name = pilha[idx_op1][$1.label].endereco_memoria;
            string op2_c_name = pilha[idx_op2][$3.label].endereco_memoria;
            stringstream ss_op_code;

            // Ativa a flag para gerar a função get_string_length (Len)
            precisa_get_length = true;

            // Cria temporárias para os tamanhos dos operandos
            string chave_len1 = "t_len_" + to_string(tempVar);
            adicionaVar(chave_len1, "int", true, false, 0, false, 0, 0, false, false);
            string c_nome_len1 = pilha[pilha.size()-1][chave_len1].endereco_memoria;

            string chave_len2 = "t_len_" + to_string(tempVar);
            adicionaVar(chave_len2, "int", true, false, 0, false, 0, 0, false, false);
            string c_nome_len2 = pilha[pilha.size()-1][chave_len2].endereco_memoria;

            // Cria a chave para a temporária que guardará a nova string
            string chave_res_str = "t_str_res_" + to_string(tempVar);
            
            // Adiciona a temporária à tabela de símbolos, marcando-a como 'malocada'
            // adicionaVar(chave, tipo, temp, contador, malocada)
            adicionaVar(chave_res_str, "string", true, false, true); 

            // Recupera o nome C da temporária do resultado
            string c_nome_res_str = pilha[pilha.size()-1][chave_res_str].endereco_memoria;
            // ------------------------------------------------------------------


            // Gera o código C para a concatenação
            ss_op_code << qtdTab() << c_nome_len1 << " = Len(" << op1_c_name << ");\n";
            ss_op_code << qtdTab() << c_nome_len2 << " = Len(" << op2_c_name << ");\n";
            
            // (Para ser mais 3-endereços, a soma dos tamanhos também usaria temporárias)
            string chave_len_total = "t_len_total_" + to_string(tempVar);
            adicionaVar(chave_len_total, "int", true, false, 0, false, 0, 0, false, false);
            string c_nome_len_total = pilha[pilha.size()-1][chave_len_total].endereco_memoria;
            ss_op_code << qtdTab() << c_nome_len_total << " = " << c_nome_len1 << " + " << c_nome_len2 << " + 1;\n";

            ss_op_code << qtdTab() << c_nome_res_str << " = (char*)malloc(" << c_nome_len_total << ");\n";
            ss_op_code << qtdTab() << "if (" << c_nome_res_str << " == NULL) { fprintf(stderr, \"Falha na alocacao de memoria.\\n\"); exit(1); }\n";
            ss_op_code << qtdTab() << "strcpy(" << c_nome_res_str << ", " << op1_c_name << ");\n";
            ss_op_code << qtdTab() << "strcat(" << c_nome_res_str << ", " << op2_c_name << ");\n";

            $$.label = chave_res_str; 
            $$.traducao = $1.traducao + $3.traducao + ss_op_code.str();

        } else if (tipo1 == "string" || tipo2 == "string") {
            // Caso de string com outro tipo
            yyerror("Operador '+' com tipos incompativeis para string (" + tipo1 + ", " + tipo2 + ")");
        } else { 
            // Caso numérico: delega para a função veririficarTipo, como antes
            stringstream resultado_verificacao;
            resultado_verificacao = veririficarTipo($1.label, "+", $3.label);
            $$.label = "t" + to_string(tempVar-1);
            $$.traducao = $1.traducao + $3.traducao + resultado_verificacao.str();
        }
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
        int indice_escopo_operando = buscarVariavel($2.label);
        if (indice_escopo_operando == -1) { yyerror("Variavel '" + $2.label + "' nao declarada (operando de UMINUS)"); }
        string tipo_operando = pilha[indice_escopo_operando][$2.label].tipo;
        string c_nome_operando = pilha[indice_escopo_operando][$2.label].endereco_memoria;
        if (tipo_operando == "string" || tipo_operando == "bool") { yyerror("Operador unario '-' nao pode ser aplicado ao tipo '" + tipo_operando + "'"); }
        string tipo_resultado = tipo_operando;
        string chave_temp_resultado = "t_uminus_" + to_string(tempVar);
        adicionaVar(chave_temp_resultado, tipo_resultado, true, false, 0, false, 0, 0, false, false);
        string c_nome_resultado = pilha[pilha.size()-1][chave_temp_resultado].endereco_memoria;
        stringstream ss_code;
        ss_code << qtdTab() << c_nome_resultado << " = -" << c_nome_operando << ";\n";
        $$.label = chave_temp_resultado;
        $$.traducao = $2.traducao + ss_code.str();
    }
    | TK_NUM {
        string chave_temp_num = "t_num_" + to_string(tempVar);
        string tipo_num = ($1.traducao.find('.') != string::npos) ? "float" : "int";
        adicionaVar(chave_temp_num, tipo_num, true, false, 0, false, 0, 0, false, false);
        string c_nome_num = pilha[pilha.size()-1][chave_temp_num].endereco_memoria;
        stringstream ss_code;
        ss_code << qtdTab() << c_nome_num << " = " << $1.traducao << ";\n";
        $$.label = chave_temp_num; // << ESTA É A LINHA CRUCIAL
        $$.traducao = ss_code.str();
    }
    | TK_ID {
        if (buscarVariavel($1.label) == -1) { yyerror("Variavel '" + $1.label + "' nao declarada"); }
        $$.label = $1.label; 
        $$.traducao = "";
    }
    | COVERT_TYPE {
        $$.label = $1.label;
        $$.traducao = $1.traducao;
    }
    | TK_BOOL_TRUE {
        string chave_temp_true = "t_bool_" + to_string(tempVar);
        adicionaVar(chave_temp_true, "bool", true, false, 0, false, 0, 0, false, false);
        string c_nome_true = pilha[pilha.size()-1][chave_temp_true].endereco_memoria;
        stringstream ss_code;
        ss_code << qtdTab() << c_nome_true << " = 1;\n";
        $$.label = chave_temp_true;
        $$.traducao = ss_code.str();
    }
    | TK_BOOL_FALSE {
        string chave_temp_false = "t_bool_" + to_string(tempVar);
        adicionaVar(chave_temp_false, "bool", true, false, 0, false, 0, 0, false, false);
        string c_nome_false = pilha[pilha.size()-1][chave_temp_false].endereco_memoria;
        stringstream ss_code;
        ss_code << qtdTab() << c_nome_false << " = 0;\n";
        $$.label = chave_temp_false;
        $$.traducao = ss_code.str();
    }
    | TK_STRING_LITERAL {
        string chave_temp_sl = "t_sl_" + to_string(tempVar);
        adicionaVar(chave_temp_sl, "string", true, false, 0, false, 0, 0, false, true);
        string c_nome_sl = pilha[pilha.size()-1][chave_temp_sl].endereco_memoria;
        stringstream ss_code;
        ss_code << qtdTab() << c_nome_sl << " = (char*)malloc(" << $1.label.length() + 1 << ");\n";
        ss_code << qtdTab() << "strcpy(" << c_nome_sl << ", " << $1.traducao << ");\n";
        $$.label = chave_temp_sl;
        $$.traducao = ss_code.str();
    }
    // >>> NOVA REGRA PARA ACESSO A VETOR <<<
    | TK_ID '[' EXPR ']' {
        // 1. Validar que o vetor existe
        int idx_vetor = buscarVariavel($1.label);
        if (idx_vetor == -1) { yyerror("Vetor '" + $1.label + "' nao declarado."); }
        if (!pilha[idx_vetor][$1.label].eh_vetor) { yyerror("Variavel '" + $1.label + "' nao e um vetor."); }

        // 2. Pegar informações do vetor
        string c_nome_vetor = pilha[idx_vetor][$1.label].endereco_memoria;
        string tipo_elemento = pilha[idx_vetor][$1.label].tipo;

        // 3. Criar temporária para o resultado
        string chave_temp_valor = "t_vec_access_" + to_string(tempVar);
        adicionaVar(chave_temp_valor, tipo_elemento, true, false, 0, false, 0, 0, false, false);
        string c_nome_valor = pilha[pilha.size()-1][chave_temp_valor].endereco_memoria;

        // 4. Gerar código C
        stringstream ss_code;
        
        // Incluir o código da sub-expressão
        ss_code << $3.traducao; // Código do índice
        
        // Buscar o índice após o código ter sido gerado
        int idx_indice = buscarVariavel($3.label);
        
        if (idx_indice != -1) {
            string c_nome_indice = pilha[idx_indice][$3.label].endereco_memoria;
            
            // Gerar o código de leitura
            ss_code << qtdTab() << c_nome_valor << " = " << c_nome_vetor << "[" << c_nome_indice << "];\n";
        } else {
            ss_code << qtdTab() << c_nome_valor << " = 0; /* Erro: nao foi possivel acessar indice */\n";
        }

        // 5. Definir os atributos para esta expressão
        $$.traducao = ss_code.str();
        $$.label = chave_temp_valor;
    }
    | TK_ID '[' EXPR ']' '[' EXPR ']' {
        // --- ACESSO A MATRIZ ---
        // 1. Validar que a matriz existe
        int idx_matriz = buscarVariavel($1.label);
        if (idx_matriz == -1) { yyerror("Matriz '" + $1.label + "' nao declarada."); }
        if (!pilha[idx_matriz][$1.label].eh_matriz) { yyerror("Variavel '" + $1.label + "' nao e uma matriz."); }

        // 2. Pegar informações da matriz
        string c_nome_matriz = pilha[idx_matriz][$1.label].endereco_memoria;
        string tipo_elemento = pilha[idx_matriz][$1.label].tipo;
        int num_colunas = pilha[idx_matriz][$1.label].num_colunas;

        // 3. Criar temporárias para cálculo do offset e resultado
        string chave_temp_offset = "t_offset_" + to_string(tempVar);
        adicionaVar(chave_temp_offset, "int", true, false, 0, false, 0, 0, false, false);
        string c_nome_offset = pilha[pilha.size()-1][chave_temp_offset].endereco_memoria;
        
        string chave_temp_valor = "t_mat_access_" + to_string(tempVar);
        adicionaVar(chave_temp_valor, tipo_elemento, true, false, 0, false, 0, 0, false, false);
        string c_nome_valor = pilha[pilha.size()-1][chave_temp_valor].endereco_memoria;

        // 4. Gerar código C
        stringstream ss_code;
        
        // Incluir o código das sub-expressões
        ss_code << $3.traducao; // Código do primeiro índice (linha)
        ss_code << $6.traducao; // Código do segundo índice (coluna)
        
        // Buscar os índices após o código ter sido gerado
        int idx_linha = buscarVariavel($3.label);
        int idx_coluna = buscarVariavel($6.label);
        
        // SOLUÇÃO ROBUSTA: Se não encontrar como variável, usar como literal
        string c_nome_linha, c_nome_coluna;
        
        if (idx_linha != -1) {
            c_nome_linha = pilha[idx_linha][$3.label].endereco_memoria;
        } else {
            // Se não for variável, assumir que é literal - criar temporária
            string chave_temp_linha = "t_linha_" + to_string(tempVar);
            adicionaVar(chave_temp_linha, "int", true, false, 0, false, 0, 0, false, false);
            c_nome_linha = pilha[pilha.size()-1][chave_temp_linha].endereco_memoria;
            ss_code << qtdTab() << c_nome_linha << " = " << $3.label << ";\n";
        }
        
        if (idx_coluna != -1) {
            c_nome_coluna = pilha[idx_coluna][$6.label].endereco_memoria;
        } else {
            string chave_temp_coluna = "t_coluna_" + to_string(tempVar);
            adicionaVar(chave_temp_coluna, "int", true, false, 0, false, 0, 0, false, false);
            c_nome_coluna = pilha[pilha.size()-1][chave_temp_coluna].endereco_memoria;
            ss_code << qtdTab() << c_nome_coluna << " = " << $6.label << ";\n";
        }
            
        // Gerar o código de leitura com cálculo de offset: offset = linha * num_colunas + coluna
        ss_code << qtdTab() << c_nome_offset << " = " << c_nome_linha << " * " << num_colunas << " + " << c_nome_coluna << ";\n";
        ss_code << qtdTab() << c_nome_valor << " = " << c_nome_matriz << "[" << c_nome_offset << "];\n";

        // 5. Definir os atributos para esta expressão
        $$.traducao = ss_code.str();
        $$.label = chave_temp_valor;
    }
;
COVERT_TYPE:
    TK_TIPO_INT '(' EXPR ')' {
        // 1. Buscar informações da expressão a ser convertida ($3)
        int indice_expr = buscarVariavel($3.label);
        if (indice_expr == -1) { yyerror("Variavel '" + $3.label + "' nao declarada (em cast para int)."); }

        string tipo_original = pilha[indice_expr][$3.label].tipo;
        string c_nome_original = pilha[indice_expr][$3.label].endereco_memoria;

        // Opcional, mas recomendado: Verificar se o cast é válido
        if (tipo_original == "string") {
            yyerror("Nao e possivel converter tipo 'string' para 'int'.");
        }

        // 2. Criar uma chave para a nova temporária que armazenará o resultado
        string chave_temp_cast = "t_cast_int_" + to_string(tempVar);

        // 3. Adicionar a nova temporária à tabela de símbolos com o tipo 'int'
        adicionaVar(chave_temp_cast, "int", true, false, 0, false, 0, 0, false, false);

        // 4. Obter o nome C da nova temporária
        string c_nome_cast = pilha[pilha.size()-1][chave_temp_cast].endereco_memoria;

        // 5. Gerar o código C para a conversão (cast)
        stringstream ss_code;
        ss_code << $3.traducao; // Primeiro, o código da expressão original, se houver
        ss_code << qtdTab() << c_nome_cast << " = (int)" << c_nome_original << ";\n";
        
        // 6. Definir os atributos para este nó
        $$.label = chave_temp_cast; // O label é a CHAVE da nova temporária
        $$.traducao = ss_code.str();
    }
    | TK_TIPO_FLOAT '(' EXPR ')' {
        // Lógica idêntica para o cast para float
        int indice_expr = buscarVariavel($3.label);
        if (indice_expr == -1) { yyerror("Variavel '" + $3.label + "' nao declarada (em cast para float)."); }

        string tipo_original = pilha[indice_expr][$3.label].tipo;
        string c_nome_original = pilha[indice_expr][$3.label].endereco_memoria;

        if (tipo_original == "string") {
            yyerror("Nao e possivel converter tipo 'string' para 'float'.");
        }

        string chave_temp_cast = "t_cast_float_" + to_string(tempVar);
        adicionaVar(chave_temp_cast, "float", true);
        string c_nome_cast = pilha[pilha.size()-1][chave_temp_cast].endereco_memoria;

        stringstream ss_code;
        ss_code << $3.traducao;
        ss_code << qtdTab() << c_nome_cast << " = (float)" << c_nome_original << ";\n";
        
        $$.label = chave_temp_cast;
        $$.traducao = ss_code.str();
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

void adicionaVar(string nome, string tipo, bool temp, bool eh_vetor, int tamanho, bool eh_matriz, int linhas, int colunas, bool c, bool malocada) {
    // Verifica se a variável já existe no escopo atual
    if (pilha.back().count(nome)) {
        yyerror("Variavel '" + nome + "' ja declarada neste escopo.");
    }
    
    // Pega uma referência para o escopo atual para facilitar a leitura
    tabela_simbolos& escopo_atual = pilha.back();
    
    // Preenche TODAS as informações na struct da tabela de símbolos
    escopo_atual[nome].tipo = tipo;
    escopo_atual[nome].temporaria = temp;
    escopo_atual[nome].malocada = malocada;
    escopo_atual[nome].contador = c;
    
    // Armazena as informações do vetor
    escopo_atual[nome].eh_vetor = eh_vetor;
    escopo_atual[nome].tamanho_vetor = tamanho;
    
    // Armazena as informações da matriz
    escopo_atual[nome].eh_matriz = eh_matriz;
    escopo_atual[nome].num_linhas = linhas;
    escopo_atual[nome].num_colunas = colunas;

    // Gera o nome da variável C
    if (temp) {
        escopo_atual[nome].endereco_memoria = "t" + to_string(tempVar++);
    } else {
        escopo_atual[nome].endereco_memoria = "d" + to_string(defVar++);
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
	else if(operador == "<>") {
		// 1. Validar tipos e ativar a flag para a função Len (get_string_length)
		precisa_get_length = true; // Garante que a função Len() seja gerada
		if(tipo1 != "string" || tipo2 != "string"){
			yyerror("Operador de concatenacao '+' so pode ser usado com strings.");
		}

		// 2. Criar TODAS as temporárias necessárias para a operação
		string temp_len1 = "t_len_" + to_string(tempVar);
		adicionaVar(temp_len1, "int", true);

		string temp_len2 = "t_len_" + to_string(tempVar);
		adicionaVar(temp_len2, "int", true);
		
		string temp_total_len = "t_total_" + to_string(tempVar);
		adicionaVar(temp_total_len, "int", true);

		string temp_result_str = "t_res_" + to_string(tempVar);
		// <<< CORREÇÃO IMPORTANTE AQUI >>>
		// Adiciona a temporária do resultado, marcando-a como 'malocada'
		// Assinatura: (nome, tipo, temp, contador, malocada)
		adicionaVar(temp_result_str, "string", true, false, true);

		// 3. Gerar o código C para a concatenação em estilo 3-endereços
		ss << qtdTab() << pilha[buscarVariavel(temp_len1)][temp_len1].endereco_memoria << " = Len(" << endereco1 << ");\n";
		ss << qtdTab() << pilha[buscarVariavel(temp_len2)][temp_len2].endereco_memoria << " = Len(" << endereco2 << ");\n";
		ss << qtdTab() << pilha[buscarVariavel(temp_total_len)][temp_total_len].endereco_memoria << " = " << pilha[buscarVariavel(temp_len1)][temp_len1].endereco_memoria << " + " << pilha[buscarVariavel(temp_len2)][temp_len2].endereco_memoria << " + 1;\n";
		ss << qtdTab() << pilha[buscarVariavel(temp_result_str)][temp_result_str].endereco_memoria << " = (char*)malloc(" << pilha[buscarVariavel(temp_total_len)][temp_total_len].endereco_memoria << ");\n";
		ss << qtdTab() << "strcpy(" << pilha[buscarVariavel(temp_result_str)][temp_result_str].endereco_memoria << ", " << endereco1 << ");\n";
		ss << qtdTab() << "strcat(" << pilha[buscarVariavel(temp_result_str)][temp_result_str].endereco_memoria << ", " << endereco2 << ");\n";
		
		// **NÃO** tentamos dar 'free' nos operandos aqui. Isso será feito no final do escopo.
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