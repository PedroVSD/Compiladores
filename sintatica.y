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

//Grupo da funções que mexem em Variáveis
void adicionaVar(string nome, string tipo, int d, int N_d[2], bool temp = false, bool contador = false);
string newTemp(string tipo, bool contador = false, bool malocada = false);
int buscarVariavel(string nome);
stringstream veririficarTipo(string nome, string op, string valor);

// Grupo de funções que mexem com a pilha
void criarPilha();
void addPilhaLaco(string b, string c);
stringstream fecharPilha();
stringstream fecharPilha(stringstream& ss);

// Grupo de funções auxiliares
string qtdTab(int dif = 0);
string generateSwitchCases(string caseData, string switchVar, string switchId); 

//Grupo de funcões prontas
stringstream addFuncao(int num);
/*  
    1- Len
    2- input_string
    3- input_bool

*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Contadores globais
int tempVar = 0;
int defVar = 0;
int defbloco = 0;
int defgoto = 0;
int tempElse = 0;
string current_switch_var = "";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Flag para gerar a funções
bool atribuicaoGlobal = false;
bool len = false;
bool inputString = false;
bool inputBool = false;
bool outputBool = false;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct atributos {
	string label;
	string traducao;
};

// Estrutura para armazenar informações de variáveis
struct tabela{
	string tipo;                // Tipo da variável (int, float, char, bool, string)
	string endereco_memoria;    // Apelido
    int num_dimensoes;          // 0 = escalar, 1 = vetor, 2 = matriz
    int dimensoes[2];           // [0] = tamanho do vetor/linhas, [1] = colunas (se matriz)
    bool inicializado;          // Indica se a variável foi inicializada
    bool temporaria;            // Indica se é uma variável temporária
    int numero;                 // Se for um numero, guarda o valor numérico
	bool contador;  //?
	bool malocada; //?
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
map<string, int> tipoTamanho = {
    {"int", sizeof(int)},
    {"float", sizeof(float)},
    {"char", sizeof(char)},
    {"bool", sizeof(bool)},
    {"string", sizeof(char)}
};


extern int numLinha;
int yylex(void);
void yyerror(string);

string novoRotulo() {
    return "L" + to_string(defgoto++);
}

%}

%token TK_NUM TK_ID TK_TIPO_INT TK_TIPO_FLOAT TK_MAIN
%token TK_TIPO_CHAR TK_TIPO_BOOL TK_IDX
%token TK_IGUAL TK_DIFERENTE TK_MAIOR_IGUAL TK_MENOR_IGUAL
%token TK_AND TK_OR
%token TK_CHAR TK_BOOL_TRUE TK_BOOL_FALSE
%token TK_TIPO_STRING TK_STRING_LITERAL
%token TK_IF TK_ELSE TK_ELSE_IF TK_WHILE TK_FOR TK_DO
%token TK_BREAK TK_CONTINUE
%token TK_ESCREVA TK_LEIA
%token TK_SWITCH TK_CASE TK_DEFAULT
%token TK_IMPRIMIR_VETOR TK_QUICKSORT

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
		cout << "#include\"algoritmos/quicksort.h\"\n\n";

        // Mudei o nome da sua função 'Len' para 'get_string_length' para consistência
        if (len) cout << addFuncao(1).str();
		if (inputString) cout << addFuncao(2).str();
		if(inputBool)  cout << addFuncao(3).str();

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
	//| FUNCOES_VETOR ';'   { $$.traducao = $1.traducao; }
    | SWITCH_STMT       { $$.traducao = $1.traducao; }
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


/*FUNCOES_VETOR:
    TK_IMPRIMIR_VETOR '(' TK_ID ',' TK_NUM ')' {
        string nome_vetor = $3.label;
		string tipo = pilha[buscarVariavel(nome_vetor)][nome_vetor].tipo;
        string tamanho = $5.traducao;
        
        if (buscarVariavel(nome_vetor) == -1) {
            yyerror("Vetor '" + nome_vetor + "' não foi declarado.");
        }
        
        string tipo_var = pilha[buscarVariavel(nome_vetor)][nome_vetor].tipo;
        if (tipo_var != "int" || !pilha[buscarVariavel(nome_vetor)][nome_vetor].eh_vetor) {
            yyerror("'" + nome_vetor + "' não é um vetor de inteiros.");
        }
        
        string endereco_vetor = pilha[buscarVariavel(nome_vetor)][nome_vetor].endereco_memoria;

        // --- Início da Geração do Laço com GOTO ---
        stringstream ss;
        string contador = novaTemp("int");      // Variável para o 'i' do laço (ex: t10)
        string condicao = novaTemp("int");      // Variável para o resultado da condição (ex: t11)
        string rotulo_inicio = novoRotulo();    // Rótulo de início do laço (ex: L3)
        string rotulo_fim = novoRotulo();       // Rótulo de fim do laço (ex: L4)

		string temp = "t" + to_string(tempVar);
		ss << qtdTab() << temp << " = " << nome_vetor << "["<< tamanho << "];\n";
		
		adicionaVar(temp, tipo, true, false, 0, false, 0, 0, false, false);
        ss << qtdTab() << "printf(" << "\"" << tipomascara[tipo] << "\", " << temp << ");\n";
        
        // Inicialização: i = 0;
        ss << qtdTab() << contador << " = 0;\n";
        
        // Rótulo de início do laço
        ss << qtdTab() << rotulo_inicio << ":\n";
        
        // Condição: if (!(i < tamanho)) goto fim;
        ss << qtdTab(1) << condicao << " = " << contador << " < " << tamanho << ";\n";
        ss << qtdTab(1) << "if (!" << condicao << ") goto " << rotulo_fim << ";\n";
        
        // Corpo do laço: printf("%d", vetor[i]);
        ss << qtdTab(1) << "printf(\"%d\", " << endereco_vetor << "[" << contador << "]);\n";
        
        // Corpo do laço: if (i < tamanho - 1) printf(", ");
        ss << qtdTab(1) << condicao << " = " << contador << " < " << tamanho << " - 1;\n";
        ss << qtdTab(1) << "if (" << condicao << ") printf(\", \");\n";
        
        // Incremento: i = i + 1;
        ss << qtdTab(1) << contador << " = " << contador << " + 1;\n";
        
        // Volta para o início
        ss << qtdTab(1) << "goto " << rotulo_inicio << ";\n";
        
        // Rótulo de fim do laço
        ss << qtdTab() << rotulo_fim << ":;\n";
        
        ss << qtdTab() << "printf(\"]\\n\");\n";
        // --- Fim da Geração do Laço com GOTO ---
        
        $$.traducao = ss.str();
    }
    | TK_QUICKSORT '(' TK_ID ',' TK_NUM ')' {
        // ... (código do quicksort permanece o mesmo)
        string nome_vetor = $3.label;
        string tamanho = $5.traducao;
        
        if (buscarVariavel(nome_vetor) == -1) {
            yyerror("Vetor '" + nome_vetor + "' não foi declarado.");
        }
        
        string tipo_var = pilha[buscarVariavel(nome_vetor)][nome_vetor].tipo;
        if (tipo_var != "int" || !pilha[buscarVariavel(nome_vetor)][nome_vetor].eh_vetor) {
            yyerror("'" + nome_vetor + "' não é um vetor de inteiros.");
        }
        
        stringstream ss;
        string endereco_vetor = pilha[buscarVariavel(nome_vetor)][nome_vetor].endereco_memoria;
        
        ss << qtdTab() << "quick_sort_completo(" << endereco_vetor << ", " << tamanho << ");\n";
        
        $$.traducao = ss.str();
    }
;*/

LISTA_VARIAVEIS:
    TK_ID {
        int idx = buscarVariavel($1.label);
        if (idx == -1) { yyerror("Variavel '" + $1.label + "' nao declarada para 'leia'."); }

        string tipo = pilha[idx][$1.label].tipo;
        string c_nome = pilha[idx][$1.label].endereco_memoria;
        
        stringstream ss_code;
        if (tipo == "string") {
            inputString = true; 
            ss_code << qtdTab() << c_nome << " = input_string();\n";
		}
		else if (tipo == "bool") {
			inputBool = true; 
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
            inputString = true; 
			pilha[idx][c_nome].malocada = true; // Marca que a string foi alocada dinamicamente
            ss_code << qtdTab() << c_nome << " = input_string();\n";
		}
		else if (tipo == "bool") {
			inputBool = true;
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
	| TK_TIPO_STRING { $$.label = "string"; }
;

DECLAR_VAR:
    TIPO TK_ID {
        string nome = $2.label;
        string tipo = $1.label;
        int dimensoes[] = {0, 0}; // Inicializa dimensões como 0
        adicionaVar(nome, tipo, 0, dimensoes, false, false);
        $$.traducao = "";
    }   
    | TIPO TK_ID '=' EXPR {
        string nome = $2.label;
        string tipo = $1.label;
        int dimensoes[] = {0, 0}; // Inicializa dimensões como 0
        adicionaVar(nome, tipo, 0, dimensoes, false, false);
        pilha[pilha.size()-1][nome].inicializado = true;
        stringstream ss;
        ss = veririficarTipo($2.label, "=", $4.label);
        $$.traducao = $4.traducao + ss.str();
    }
    | TIPO TK_ID '=' TK_CHAR {
        string nome = $2.label;
        string tipo = $1.label;
        int dimensoes[] = {0, 0}; // Inicializa dimensões como 0
        adicionaVar(nome, tipo, 0, dimensoes, false, false);
        if(tipo != "char") {
            cout << "Atribuindo char a variavel '" << nome << "' do tipo '" << tipo << "'\n";
            exit(1);}
        pilha[pilha.size()-1][nome].inicializado = true; 
        stringstream ss;
        ss << qtdTab() << pilha[pilha.size()-1][nome].endereco_memoria << " = " << $4.label << ";\n";
        $$.traducao = ss.str();
    }
    | TIPO TK_ID '[' EXPR ']' {
        string tipo_elemento = $1.label;
        string nome_vetor = $2.label;
        string tamanho = $4.label;
        int dimensoes[] = {pilha[buscarVariavel(tamanho)][tamanho].numero, 0}; // Inicializa dimensões como vetor de 1 dimensão
        adicionaVar(nome_vetor, tipo_elemento, 1, dimensoes, false, false);
        // Verificações
        if(pilha[buscarVariavel(tamanho)][tamanho].tipo != "int") {
            cout << "Tamanho do vetor '" << nome_vetor << "' deve ser um inteiro.\n";
            exit(1);
        }
        if(pilha[buscarVariavel(tamanho)][tamanho].inicializado == false){
            cout << "Tamanho do vetor '" << tamanho << "' deve ser inicializado.\n";
            exit(1);
        }
        if(pilha[buscarVariavel(tamanho)][tamanho].num_dimensoes > 0) {
            cout << tamanho << " ja foi declarado como vetor ou matriz.\n";
            exit(1);
        }
        if(pilha[buscarVariavel(tamanho)][tamanho].numero < 1){
            cout << "Vetor '" << nome_vetor << "' nao pode ser negativo ou nulo.\n";
            exit(1);
        }

        stringstream ss;
        string endereco = pilha[buscarVariavel(nome_vetor)][nome_vetor].endereco_memoria;
        string temp = newTemp("int");
        if(tipo_elemento == "string") tipo_elemento = "char"; 
        ss << qtdTab() << temp << " = " << tamanho << " * " << tipoTamanho[tipo_elemento] << ";\n";
        ss << qtdTab() << endereco << " = (" << tipoTraducao[tipo_elemento] << "*)malloc(" << temp << ");\n";

        $$.traducao = ss.str();
    }
    | TIPO TK_ID '[' EXPR ']' '[' EXPR ']' {        
        string tipo_elemento = $1.label;
        string nome_matriz = $2.label;
        string linha = $4.label;
        string colunas = $7.label;
        int dimensoes[] = {pilha[buscarVariavel(linha)][linha].numero, pilha[buscarVariavel(colunas)][colunas].numero}; // Inicializa dimensões como matriz de 2 dimensões
        adicionaVar(nome_matriz, tipo_elemento, 2, dimensoes, false, false);
        // Verificações
        if(pilha[buscarVariavel(linha)][linha].tipo != "int" || pilha[buscarVariavel(colunas)][colunas].tipo != "int") {
            cout << "Tamanho da matriz '" << nome_matriz << "' deve ser um inteiro.\n";
            exit(1);
        }
        if(pilha[buscarVariavel(linha)][linha].inicializado == false || pilha[buscarVariavel(colunas)][colunas].inicializado == false) {
            cout << "Tamanho da matriz '" << nome_matriz << "' deve ser inicializado.\n";
            exit(1);
        }
        if(pilha[buscarVariavel(linha)][linha].num_dimensoes > 0 || pilha[buscarVariavel(colunas)][colunas].num_dimensoes > 0) {
            cout << linha << " ou " << colunas << " ja foi declarado como vetor ou matriz.\n";
            exit(1);
        }
        if(pilha[buscarVariavel(linha)][linha].numero < 1 || pilha[buscarVariavel(colunas)][colunas].numero < 1) {
            cout << "Matriz '" << nome_matriz << "' nao pode ter dimensoes negativas ou nulas.\n";
            exit(1);
        }
      
        stringstream ss;
        string endereco = pilha[buscarVariavel(nome_matriz)][nome_matriz].endereco_memoria;   
        string temp1 = newTemp("int");
        string temp2 = newTemp("int");
        if(tipo_elemento == "string") tipo_elemento = "char";
        ss << qtdTab() << temp1 << " = " << pilha[buscarVariavel(linha)][linha].endereco_memoria << " * " << pilha[buscarVariavel(colunas)][colunas].endereco_memoria << ";\n";
        ss << qtdTab() << temp2 << " = " << pilha[buscarVariavel(linha)][linha].endereco_memoria << " * " << tipoTamanho[tipo_elemento] << ";\n";
        ss << qtdTab() << endereco << " = (" << tipoTraducao[tipo_elemento] << "*)malloc(" << temp2 << ");\n";
        $$.traducao = ss.str();
    }
;

ATRIB:
    TK_ID '=' EXPR {
        if (buscarVariavel($1.label) == -1) { 
            yyerror("Variavel '" + $1.label + "' nao declarada."); 
        }
        stringstream ss;
        ss = veririficarTipo($1.label, "=", $3.label);
        $$.traducao = $3.traducao + ss.str();
    }

   | TK_ID '[' EXPR ']' '=' EXPR {

        string nome = $1.label;
        string tipo1 = pilha[buscarVariavel(nome)][nome].tipo;
        
        string nome2 = $6.label;
        string tipo2 = pilha[buscarVariavel(nome2)][nome2].tipo;



        string idx = $3.label;
        if (pilha[buscarVariavel(idx)][idx].tipo != "int") {
            cout << "Indice do vetor '" << nome << "' deve ser um inteiro.\n";
            exit(1);
        }
        if (pilha[buscarVariavel(idx)][idx].inicializado == false) {
            cout << "Indice do vetor '" << nome << "' deve ser inicializado.\n";
            exit(1);
        }
        if (pilha[buscarVariavel(idx)][idx].num_dimensoes > 0) {
            cout << idx << " ja foi declarado como vetor ou matriz.\n";
            exit(1);
        }
        if (pilha[buscarVariavel(idx)][idx].numero < 0) {
            cout << "Vetor '" << nome << "' nao pode ter indice negativo.\n";
            exit(1);
        }
        if(pilha[buscarVariavel(idx)][idx].dimensoes[0] < pilha[buscarVariavel(idx)][idx].numero) {
            cout << "Indice do vetor '" << nome << "' fora dos limites.\n";
            exit(1);
        }
        if( pilha[buscarVariavel(nome)][nome].num_dimensoes != 1) {
            cout << "Variavel '" << nome << "' nao e um vetor.\n";
            exit(1);
        }
        if (pilha[buscarVariavel(nome)][nome].tipo != pilha[buscarVariavel(nome2)][nome2].tipo) {
            cout << "Tipos incompatíveis na atribuição: '" << tipo1 << "' e '" << tipo2 << "'.\n";
            exit(1);
        }
        
        stringstream ss;
        
        ss << $3.traducao; // Código do índice
        ss << $6.traducao; // Código da expressão à direita

        string new_temp = newTemp(tipo1);
        ss << qtdTab() << new_temp << " = " << idx << ";\n"; // Cria uma temporária para o índice
        ss << qtdTab() << pilha[buscarVariavel(nome)][nome].endereco_memoria << "[" << new_temp << "] = " << $6.label << ";\n";
        

        $$.traducao = ss.str();
    }

   | TK_ID '[' EXPR ']' '[' EXPR ']' '=' EXPR {
        
        string nome = $1.label;
        string tipo1 = pilha[buscarVariavel(nome)][nome].tipo;

        string nome2 = $8.label;
        string tipo2 = pilha[buscarVariavel(nome2)][nome2].tipo;

        string idx_linha = $3.label;
        string idx_coluna = $6.label;

        if (pilha[buscarVariavel(idx_linha)][idx_linha].tipo != "int" || pilha[buscarVariavel(idx_coluna)][idx_coluna].tipo != "int") {
            cout << "Indices da matriz '" << nome << "' devem ser inteiros.\n";
            exit(1);
        }
        if (pilha[buscarVariavel(idx_linha)][idx_linha].inicializado == false || pilha[buscarVariavel(idx_coluna)][idx_coluna].inicializado == false) {
            cout << "Indices da matriz '" << nome << "' devem ser inicializados.\n";
            exit(1);
        }
        if (pilha[buscarVariavel(idx_linha)][idx_linha].num_dimensoes > 0 || pilha[buscarVariavel(idx_coluna)][idx_coluna].num_dimensoes > 0) {
            cout << idx_linha << " ou " << idx_coluna << " ja foi declarado como vetor ou matriz.\n";
            exit(1);
        }
        if (pilha[buscarVariavel(idx_linha)][idx_linha].numero < 0 || pilha[buscarVariavel(idx_coluna)][idx_coluna].numero < 0) {
            cout << "Matriz '" << nome << "' nao pode ter indices negativos.\n";
            exit(1);
        }
        if (pilha[buscarVariavel(nome)][nome].num_dimensoes != 2) {
            cout << "Variavel '" << nome << "' nao e uma matriz.\n";
            exit(1);
        }
        if (pilha[buscarVariavel(nome)][nome].tipo != pilha[buscarVariavel(nome2)][nome2].tipo) {
            cout << "Tipos incompatíveis na atribuição: '" << tipo1 << "' e '" << tipo2 << "'.\n";
            exit(1);
        }
        if(pilha[buscarVariavel(idx_linha)][idx_linha].numero >= pilha[buscarVariavel(nome)][nome].dimensoes[0] || 
           pilha[buscarVariavel(idx_coluna)][idx_coluna].numero >= pilha[buscarVariavel(nome)][nome].dimensoes[1]) {
            cout << "Indices da matriz '" << nome << "' fora dos limites.\n";
            exit(1);
        }

        stringstream ss;
        
        // Incluir o código das sub-expressões
        ss << $3.traducao; // Código do primeiro índice (linha)
        ss << $6.traducao; // Código do segundo índice (coluna)
        ss << $9.traducao; // Código da expressão à direita

        string temp = newTemp("int"); // Temporária para o cálculo do offset
        string temp2 = newTemp("int"); // Temporária para o cálculo do offset
        ss << qtdTab() << temp << " = " << pilha[buscarVariavel(idx_linha)][idx_linha].endereco_memoria << " * " << pilha[buscarVariavel(nome)][nome].dimensoes[1] << ";\n";
        ss << qtdTab() << temp2 << " = " << temp << " + " << pilha[buscarVariavel(idx_coluna)][idx_coluna].endereco_memoria << ";\n";
        ss << qtdTab() << pilha[buscarVariavel(nome)][nome].endereco_memoria << "[" << temp2 << "] = " << $9.label << ";\n"; // Atribuição ao elemento da matriz

        $$.traducao = ss.str();
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
        stringstream ss;
        string case_id = to_string(defgoto);
        
        // Mesmo padrão do if: comparação em três endereços
        string temp_val = newTemp("int");
        string temp_comp = newTemp("bool");
        
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
        string tipo = pilha[pilha.size()-1][$2.label].tipo;
        if (tipo != "int" && tipo != "float") {
            cout << "Erro: Operador unário '-' só pode ser aplicado a tipos 'int' ou 'float'.\n";
            exit(1);
        }
        string temp_tipo = (tipo == "int") ? "int" : "float";
        string temp = newTemp(temp_tipo);
        stringstream ss;
        ss << qtdTab() << temp << " = -(" << $2.traducao << ");\n";
        $$.label = temp;
        $$.traducao = $2.traducao + ss.str();
    }
    | TK_NUM {
        string tipo_num = ($1.traducao.find('.') != string::npos) ? "float" : "int";
        string temp = newTemp(tipo_num);
        string num = $1.traducao;
        if(tipo_num == "int")  pilha[pilha.size()-1][temp].numero = stoi(num);
        pilha[pilha.size()-1][temp].inicializado = true;
        stringstream ss;
        ss << qtdTab() << temp << " = " << $1.traducao << ";\n";
        $$.label = temp;
        $$.traducao = ss.str();
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
        string chave_temp_true = newTemp("bool");
        string c_nome_true = pilha[pilha.size()-1][chave_temp_true].endereco_memoria;
        stringstream ss_code;
        ss_code << qtdTab() << c_nome_true << " = 1;\n";
        $$.label = chave_temp_true;
        $$.traducao = ss_code.str();
    }
    | TK_BOOL_FALSE {
        string chave_temp_false = newTemp("bool");
        string c_nome_false = pilha[pilha.size()-1][chave_temp_false].endereco_memoria;
        stringstream ss_code;
        ss_code << qtdTab() << c_nome_false << " = 0;\n";
        $$.label = chave_temp_false;
        $$.traducao = ss_code.str();
    }
    | TK_STRING_LITERAL {
        string chave_temp_sl = newTemp("string", false, true);
        string c_nome_sl = pilha[pilha.size()-1][chave_temp_sl].endereco_memoria;
        stringstream ss_code;
        ss_code << qtdTab() << c_nome_sl << " = (char*)malloc(" << $1.label.length() + 1 << ");\n";
        ss_code << qtdTab() << "strcpy(" << c_nome_sl << ", " << $1.traducao << ");\n";
        $$.label = chave_temp_sl;
        $$.traducao = ss_code.str();
    }
    | TK_ID '[' EXPR ']' {
        string nome = $1.label;
        string tipo = pilha[buscarVariavel(nome)][nome].tipo;
        string indice = $3.label;

        if (buscarVariavel(nome) == -1) {
            cout << "Erro: Variável '" << nome << "' não declarada.\n";
            exit(1);
        }
        if (buscarVariavel(indice) == -1) {
            cout << "Erro: Variável '" << indice << "' não declarada.\n";
            exit(1);
        }
        if (pilha[buscarVariavel(indice)][indice].tipo != "int") {
            cout << "Erro: Índice de vetor deve ser do tipo 'int', mas é '" << pilha[buscarVariavel(indice)][indice].tipo << "'.\n";
            exit(1);
        }
        if(pilha[buscarVariavel(nome)][nome].num_dimensoes != 1) {
            cout << "Erro: Acesso a vetor '" << nome << "' deve ser unidimensional.\n";
            exit(1);
        }
        if(pilha[buscarVariavel(indice)][indice].numero < 0 || pilha[buscarVariavel(indice)][indice].numero >= pilha[buscarVariavel(nome)][nome].dimensoes[0]) {
            cout << "Erro: Índice '" << indice << "' fora dos limites do vetor '" << nome << "'.\n";
            exit(1);
        }
        string temp = newTemp(tipo);
        stringstream ss;
        ss << $3.traducao;
        ss << qtdTab() << temp << " = " << pilha[buscarVariavel(nome)][nome].endereco_memoria << "[" << $3.label << "];\n";
        $$.traducao = ss.str();
        $$.label = temp;
    }
    | TK_ID '[' EXPR ']' '[' EXPR ']' {
        string nome = $1.label;
        string linha = $3.label;
        string coluna = $6.label;

        if (buscarVariavel(nome) == -1) {
            cout << "Erro: Variável '" << nome << "' não declarada.\n";
            exit(1);
        }
        if (buscarVariavel(linha) == -1) {
            cout << "Erro: Variável '" << linha << "' não declarada.\n";
            exit(1);
        }
        if (buscarVariavel(coluna) == -1) {
            cout << "Erro: Variável '" << coluna << "' não declarada.\n";
            exit(1);
        }
        if (pilha[buscarVariavel(linha)][linha].tipo != "int") {
            cout << "Erro: Índice de linha deve ser do tipo 'int', mas é '" << pilha[buscarVariavel(linha)][linha].tipo << "'.\n";
            exit(1);
        }
        if (pilha[buscarVariavel(coluna)][coluna].tipo != "int") {
            cout << "Erro: Índice de coluna deve ser do tipo 'int', mas é '" << pilha[buscarVariavel(coluna)][coluna].tipo << "'.\n";
            exit(1);
        }
        if(pilha[buscarVariavel(nome)][nome].num_dimensoes != 2) {
            cout << "Erro: Acesso a matriz '" << nome << "' deve ser bidimensional.\n";
            exit(1);
        }
        if(pilha[buscarVariavel(linha)][linha].numero < 0 || pilha[buscarVariavel(linha)][linha].numero >= pilha[buscarVariavel(nome)][nome].dimensoes[0]) {
            cout << "Erro: Índice de linha '" << linha << "' fora dos limites da matriz '" << nome << "'.\n";
            exit(1);
        }
        if(pilha[buscarVariavel(coluna)][coluna].numero < 0 || pilha[buscarVariavel(coluna)][coluna].numero >= pilha[buscarVariavel(nome)][nome].dimensoes[1]) {
            cout << "Erro: Índice de coluna '" << coluna << "' fora dos limites da matriz '" << nome << "'.\n";
            exit(1);
        }
        string tipo = pilha[buscarVariavel(nome)][nome].tipo;
        string temp1 = newTemp("int");
        string temp2 = newTemp("int");
        string temp3 = newTemp(tipo);
        stringstream ss;
        ss << $3.traducao; // Código para calcular o índice da linha
        ss << $6.traducao; // Código para calcular o índice da coluna
        
        ss << qtdTab() << temp1 << " = " << pilha[buscarVariavel(linha)][linha].endereco_memoria << " * " << pilha[buscarVariavel(nome)][nome].dimensoes[1] << ";\n";
        ss << qtdTab() << temp2 << " = " << temp1 << " + " << pilha[buscarVariavel(coluna)][coluna].endereco_memoria << ";\n"; 
        ss << qtdTab() << temp2 << " = " << pilha[buscarVariavel(nome)][nome].endereco_memoria << "[" << temp2 << "];\n";

        $$.traducao = ss.str();
        $$.label = temp2;
    }
;
COVERT_TYPE:
    TK_TIPO_INT '(' EXPR ')' {
        int indice_expr = buscarVariavel($3.label);
        if (indice_expr == -1) { yyerror("Variavel '" + $3.label + "' nao declarada (em cast para int)."); }
        string tipo_original = pilha[indice_expr][$3.label].tipo;
        string c_nome_original = pilha[indice_expr][$3.label].endereco_memoria;
        if (tipo_original != "int" && tipo_original != "float") {
            cout << "Erro: Conversao de tipo '" << tipo_original << "' para 'int' nao e possivel.\n";
            exit(1);
        }
        string chave_temp_cast = newTemp("int");
        string c_nome_cast = pilha[pilha.size()-1][chave_temp_cast].endereco_memoria;
        stringstream ss_code;
        ss_code << $3.traducao; // Primeiro, o código da expressão original, se houver
        ss_code << qtdTab() << c_nome_cast << " = (int)" << c_nome_original << ";\n";
        $$.label = chave_temp_cast; // O label é a CHAVE da nova temporária
        $$.traducao = ss_code.str();
    }
    | TK_TIPO_FLOAT '(' EXPR ')' {
        int indice_expr = buscarVariavel($3.label);
        if (indice_expr == -1) { yyerror("Variavel '" + $3.label + "' nao declarada (em cast para float)."); }
        string tipo_original = pilha[indice_expr][$3.label].tipo;
        string c_nome_original = pilha[indice_expr][$3.label].endereco_memoria;

        if (tipo_original != "int" && tipo_original != "float") {
            cout << "Erro: Conversao de tipo '" << tipo_original << "' para 'float' nao e possivel.\n";
            exit(1);
        }
        string chave_temp_cast = newTemp("float");
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

void adicionaVar(string nome, string tipo, int d, int N_d[2], bool temp, bool contador) {
    if (buscarVariavel(nome) != -1) {
        cout << "Erro: Variável '" << nome << "' já declarada no escopo atual." << endl;
        exit(1);
    }
    // Pega uma referência para o escopo atual para facilitar a leitura
    tabela_simbolos& Escopo = pilha.back();
    // Preenche a tabela de símbolos
    Escopo[nome].tipo = tipo;
    Escopo[nome].num_dimensoes = d;
    Escopo[nome].dimensoes[0] = N_d[0];
    Escopo[nome].dimensoes[1] = N_d[1];
    Escopo[nome].temporaria = temp;
    Escopo[nome].contador = contador;
    Escopo[nome].malocada = false;
    // Gera o nome da variável C
    if (temp) Escopo[nome].endereco_memoria = "t" + to_string(tempVar++);
    else Escopo[nome].endereco_memoria = "d" + to_string(defVar++);
}

string newTemp(string tipo, bool contador, bool malocada) {
    string nomeTemp = "t" + to_string(tempVar);
    int dimensoes[2] = {0, 0}; // Inicializa dimensões como 0
    adicionaVar(nomeTemp, tipo, 0, dimensoes, true, contador);
    pilha.back()[nomeTemp].malocada = malocada;
    return nomeTemp;
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
			else{
                if(info.num_dimensoes == 0)
				    ss << qtdTab() << tipoTraducao[info.tipo] <<" "<< info.endereco_memoria << ";\t //"<< nome << "\n";
                else
                    ss << qtdTab() << tipoTraducao[info.tipo] <<"* "<< info.endereco_memoria << ";\t //"<< nome << "\n";
            }
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
    return -1; // Nunca deve chegar aqui, mas é para evitar warning
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
        string temp_comp = newTemp("bool");
        
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

stringstream addFuncao(int num){
    stringstream ss;
    switch (num) {
        case 1: // Função para obter o tamanho de uma string
            ss << qtdTab() << "void Len(const char* str) {\n";
            ss << qtdTab(1)<< "int len;\n";
            ss << qtdTab(1)<< "int f0;\n";
            ss << qtdTab(1)<< "int f1;\n";
            ss << qtdTab(1)<< "int f2;\n\n";
            ss << qtdTab(1)<< "len = 0;\n";
            ss << qtdTab(1)<< "f0 = (str == NULL);\n";
            ss << qtdTab(1)<< "if (f0) goto loop_end_len;\n";
            ss << qtdTab(1)<< "loop_start_len:\n";
            ss << qtdTab(2)<< "f1 = str[len];\n";
            ss << qtdTab(2)<< "f2 = (f1 == '\\0');\n"; // Usei f1 aqui para estilo 3-endereços
            ss << qtdTab(2)<< "if (f2) goto loop_end_len;\n";
            ss << qtdTab(2)<< "len = len + 1;\n";
            ss << qtdTab(1)<< "goto loop_start_len;\n";
            ss << qtdTab(1)<< "loop_end_len:;\n"; // Adicionado ; para sintaxe C sempre válida
            ss << qtdTab(1)<< "return len;\n";
            ss << qtdTab() << "}\n\n";
            break;
        case 2: // Função para ler uma string
            ss << qtdTab() << "char* input_string() {\n";
            ss << qtdTab(1) << "int scanf_result;\n";
            ss << qtdTab(1) << "int flag_is_terminator;\n";
            ss << qtdTab(1) << "int flag_is_newline;\n";
            ss << qtdTab(1) << "int flag_is_space;\n";
            ss << qtdTab(1) << "int flag_is_full;\n";
            ss << qtdTab(1) << "char c;\n";
            ss << qtdTab(1) << "char* buffer;\n";
            ss << qtdTab(1) << "int len;\n";
            ss << qtdTab(1) << "int capacity;\n";
            ss << qtdTab(1) << "capacity = 16;\n";
            ss << qtdTab(1) << "len = 0;\n";
            ss << qtdTab(1) << "buffer = (char*)malloc(capacity);\n";
            ss << qtdTab() << "\n";
            ss << qtdTab() << "input_str_loop_start:\n";
            ss << qtdTab(1) << "scanf_result = scanf(\"%c\", &c);\n";
            ss << qtdTab(1) << "flag_is_terminator = scanf_result != 1;\n";
            ss << qtdTab(1) << "if (flag_is_terminator) goto input_str_loop_end;\n";
            ss << qtdTab(1) << "flag_is_newline = c == '\\n';\n";
            ss << qtdTab(1) << "flag_is_space = c == ' ';\n";
            ss << qtdTab(1) << "flag_is_terminator = flag_is_newline || flag_is_space;\n";
            ss << qtdTab(1) << "if (flag_is_terminator) goto input_str_loop_end;\n";
            ss << qtdTab(1) << "\n";
            ss << qtdTab(1) << "buffer[len] = c;\n";
            ss << qtdTab(1) << "len = len + 1;\n";
            ss << qtdTab(1) << "\n";
            ss << qtdTab(1) << "flag_is_full = len >= capacity;\n";
            ss << qtdTab(1) << "if (!flag_is_full) goto input_str_loop_start;\n";
            ss << qtdTab(1) << "\n";
            ss << qtdTab(1) << "capacity = capacity * 2;\n";
            ss << qtdTab(1) << "buffer = (char*)realloc(buffer, capacity);\n";
            ss << qtdTab(1) << "goto input_str_loop_start;\n";
            ss << qtdTab() << "\n";
            ss << qtdTab() << "input_str_loop_end:;\n";
            ss << qtdTab(1) << "buffer[len] = '\\0';\n";
            ss << qtdTab(1) << "return buffer;\n";
            ss << qtdTab() << "}\n\n";
            break;
        case 3: // Função para ler booleano
            
            ss << qtdTab() << "inr input_bool();\n";
            ss << qtdTab(1) << "char c;\n";
            ss << qtdTab(1) << "int aux;\n";
            ss << qtdTab(1) << "// Ignora espacos em branco antes de ler\n";
            ss << qtdTab(1) << "do { scanf(\"%c\", &c); } while (c == ' ' || c == '\\n');\n\n";
            ss << qtdTab(1) << "// Checa a palavra 'true'\n";
            ss << qtdTab(1) << "aux = c == 't';\n";
            ss << qtdTab(1) << "if (!aux) goto input_bool_false;\n";
            ss << qtdTab(1) << "scanf(\"%c\", &c);\n";
            ss << qtdTab(1) << "aux = c == 'r';\n";
            ss << qtdTab(1) << "if (!aux) goto input_bool_false;\n";
            ss << qtdTab(1) << "scanf(\"%c\", &c);\n";
            ss << qtdTab(1) << "aux = c == 'u';\n";
            ss << qtdTab(1) << "if (!aux) goto input_bool_false;\n";
            ss << qtdTab(1) << "scanf(\"%c\", &c);\n";
            ss << qtdTab(1) << "aux = c == 'e';\n";
            ss << qtdTab(1) << "if (!aux) goto input_bool_false\n";
            ss << qtdTab(1) << "return 1; // 'true' foi lido\n\n";
            ss << qtdTab(1) << "input_bool_false:\n";
            ss << qtdTab(1) << "// Qualquer outra coisa é considerada 'false'\n";
            ss << qtdTab(1) << "return 0;\n";
            ss << qtdTab() << "}\n\n";
            break;
            }
    return ss;
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
			string temp = newTemp("float");
			string temp2 = newTemp("float");

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
			string temp = newTemp(tipo1);
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
		string temp = newTemp("bool");
		ss << qtdTab() << temp << " = " << endereco1 << " " << operador << " " << endereco2 << ";\n";
	}
	else if(operador == "==" || operador == "!="){
		if(tipo1 != tipo2){
			if(tipo1 == "int" && tipo2 == "float"){
				string temp = newTemp("float");
				string temp2 = newTemp("bool");
				ss << qtdTab() << temp << " = (float)" << endereco1 << ";\n";
				ss << qtdTab() << temp2 << " = " << temp << " " << operador << " " << endereco2 << ";\n";
			}
			else if(tipo1 == "float" && tipo2 == "int"){
				string temp = newTemp("float");
				string temp2 = newTemp("bool");
				ss << qtdTab() << temp << " = (float)" << endereco2 << ";\n";
				ss << qtdTab() << temp2 << " = " << temp << " " << operador << " " << endereco1 << ";\n";
			}
			else{
				cout << "Erro: Tipos incompatíveis para operação de comparação.\n";
				exit(1);
			}
		}
		else if (tipo1 == "int" || tipo1 == "float" || tipo1 == "bool"){
			string temp = newTemp("bool");
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
		string temp = newTemp("bool");
		ss << qtdTab() << temp << " = !" << endereco1 << ";\n";
	}

	// operações com stings
	// <> concatenação
	else if(operador == "<>") {
		// 1. Validar tipos e ativar a flag para a função Len (get_string_length)
		len = true; // Garante que a função Len() seja gerada
		if(tipo1 != "string" || tipo2 != "string"){
			yyerror("Operador de concatenacao '+' so pode ser usado com strings.");
		}

		// 2. Criar TODAS as temporárias necessárias para a operação
		string temp_len1 = newTemp("int");
		string temp_len2 = newTemp("int");
		string temp_total_len = newTemp("int");
		string temp_result_str = newTemp("string", false, true); // String temporária para o resultado

		// 3. Gerar o código C para a concatenação em estilo 3-endereços
		ss << qtdTab() << pilha[buscarVariavel(temp_len1)][temp_len1].endereco_memoria << " = Len(" << endereco1 << ");\n";
		ss << qtdTab() << pilha[buscarVariavel(temp_len2)][temp_len2].endereco_memoria << " = Len(" << endereco2 << ");\n";
		ss << qtdTab() << pilha[buscarVariavel(temp_total_len)][temp_total_len].endereco_memoria << " = " << pilha[buscarVariavel(temp_len1)][temp_len1].endereco_memoria << " + " << pilha[buscarVariavel(temp_len2)][temp_len2].endereco_memoria << " + 1;\n";
		ss << qtdTab() << pilha[buscarVariavel(temp_result_str)][temp_result_str].endereco_memoria << " = (char*)malloc(" << pilha[buscarVariavel(temp_total_len)][temp_total_len].endereco_memoria << ");\n";
		ss << qtdTab() << "strcpy(" << pilha[buscarVariavel(temp_result_str)][temp_result_str].endereco_memoria << ", " << endereco1 << ");\n";
		ss << qtdTab() << "strcat(" << pilha[buscarVariavel(temp_result_str)][temp_result_str].endereco_memoria << ", " << endereco2 << ");\n";
 	}

	else if(operador == ">" || operador == "<" || operador == ">=" || operador == "<="){
		if(tipo1 != tipo2){
			if(tipo1 == "int" && tipo2 == "float"){
				string temp = newTemp("float");
				string temp2 = newTemp("bool");
				ss << qtdTab() << temp << " = (float)" << endereco1 << ";\n";
				ss << qtdTab() << temp2 << " = " << temp << " " << operador << " " << endereco2 << ";\n";
			}
			else if(tipo1 == "float" && tipo2 == "int"){
				string temp = newTemp("float");
				string temp2 = newTemp("bool");
				ss << qtdTab() << temp << " = (float)" << endereco2 << ";\n";
				ss << qtdTab() << temp2 << " = " << temp << " " << operador << " " << endereco1 << ";\n";
			}
			else{
				cout << "Erro: Tipos incompatíveis para operação de comparação.\n";
				exit(1);
			}
		}
		else if(tipo1 != "bool" && tipo2 != "bool"){
			string temp = newTemp("bool");  
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