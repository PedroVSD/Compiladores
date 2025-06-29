/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "sintatica.y"

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

// Estrutura para armazenar a definição de um conjunto (struct)
// Mapeia o nome de um membro para o seu tipo (ex: "x" -> "int")
typedef map<string, string> MembrosConjunto;

// Tabela global para armazenar todas as definições de conjuntos
// Mapeia o nome de um conjunto para a estrutura de seus membros
map<string, MembrosConjunto> definicoesConjunto;

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
    bool eh_set;                // Indica se é um conjunto (struct)
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


#line 207 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TK_NUM = 258,                  /* TK_NUM  */
    TK_ID = 259,                   /* TK_ID  */
    TK_TIPO_INT = 260,             /* TK_TIPO_INT  */
    TK_TIPO_FLOAT = 261,           /* TK_TIPO_FLOAT  */
    TK_MAIN = 262,                 /* TK_MAIN  */
    TK_TIPO_CHAR = 263,            /* TK_TIPO_CHAR  */
    TK_TIPO_BOOL = 264,            /* TK_TIPO_BOOL  */
    TK_IDX = 265,                  /* TK_IDX  */
    TK_IGUAL = 266,                /* TK_IGUAL  */
    TK_DIFERENTE = 267,            /* TK_DIFERENTE  */
    TK_MAIOR_IGUAL = 268,          /* TK_MAIOR_IGUAL  */
    TK_MENOR_IGUAL = 269,          /* TK_MENOR_IGUAL  */
    TK_AND = 270,                  /* TK_AND  */
    TK_OR = 271,                   /* TK_OR  */
    TK_CHAR = 272,                 /* TK_CHAR  */
    TK_BOOL_TRUE = 273,            /* TK_BOOL_TRUE  */
    TK_BOOL_FALSE = 274,           /* TK_BOOL_FALSE  */
    TK_TIPO_STRING = 275,          /* TK_TIPO_STRING  */
    TK_STRING_LITERAL = 276,       /* TK_STRING_LITERAL  */
    TK_IF = 277,                   /* TK_IF  */
    TK_ELSE = 278,                 /* TK_ELSE  */
    TK_ELSE_IF = 279,              /* TK_ELSE_IF  */
    TK_WHILE = 280,                /* TK_WHILE  */
    TK_FOR = 281,                  /* TK_FOR  */
    TK_DO = 282,                   /* TK_DO  */
    TK_BREAK = 283,                /* TK_BREAK  */
    TK_CONTINUE = 284,             /* TK_CONTINUE  */
    TK_ESCREVA = 285,              /* TK_ESCREVA  */
    TK_LEIA = 286,                 /* TK_LEIA  */
    TK_SWITCH = 287,               /* TK_SWITCH  */
    TK_CASE = 288,                 /* TK_CASE  */
    TK_DEFAULT = 289,              /* TK_DEFAULT  */
    TK_IMPRIMIR_VETOR = 290,       /* TK_IMPRIMIR_VETOR  */
    TK_QUICKSORT = 291,            /* TK_QUICKSORT  */
    TK_CONJUNTO = 292,             /* TK_CONJUNTO  */
    TK_PONTO = 293,                /* TK_PONTO  */
    UMINUS = 294,                  /* UMINUS  */
    LOWER_THAN_ELSE = 295          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define TK_NUM 258
#define TK_ID 259
#define TK_TIPO_INT 260
#define TK_TIPO_FLOAT 261
#define TK_MAIN 262
#define TK_TIPO_CHAR 263
#define TK_TIPO_BOOL 264
#define TK_IDX 265
#define TK_IGUAL 266
#define TK_DIFERENTE 267
#define TK_MAIOR_IGUAL 268
#define TK_MENOR_IGUAL 269
#define TK_AND 270
#define TK_OR 271
#define TK_CHAR 272
#define TK_BOOL_TRUE 273
#define TK_BOOL_FALSE 274
#define TK_TIPO_STRING 275
#define TK_STRING_LITERAL 276
#define TK_IF 277
#define TK_ELSE 278
#define TK_ELSE_IF 279
#define TK_WHILE 280
#define TK_FOR 281
#define TK_DO 282
#define TK_BREAK 283
#define TK_CONTINUE 284
#define TK_ESCREVA 285
#define TK_LEIA 286
#define TK_SWITCH 287
#define TK_CASE 288
#define TK_DEFAULT 289
#define TK_IMPRIMIR_VETOR 290
#define TK_QUICKSORT 291
#define TK_CONJUNTO 292
#define TK_PONTO 293
#define UMINUS 294
#define LOWER_THAN_ELSE 295

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TK_NUM = 3,                     /* TK_NUM  */
  YYSYMBOL_TK_ID = 4,                      /* TK_ID  */
  YYSYMBOL_TK_TIPO_INT = 5,                /* TK_TIPO_INT  */
  YYSYMBOL_TK_TIPO_FLOAT = 6,              /* TK_TIPO_FLOAT  */
  YYSYMBOL_TK_MAIN = 7,                    /* TK_MAIN  */
  YYSYMBOL_TK_TIPO_CHAR = 8,               /* TK_TIPO_CHAR  */
  YYSYMBOL_TK_TIPO_BOOL = 9,               /* TK_TIPO_BOOL  */
  YYSYMBOL_TK_IDX = 10,                    /* TK_IDX  */
  YYSYMBOL_TK_IGUAL = 11,                  /* TK_IGUAL  */
  YYSYMBOL_TK_DIFERENTE = 12,              /* TK_DIFERENTE  */
  YYSYMBOL_TK_MAIOR_IGUAL = 13,            /* TK_MAIOR_IGUAL  */
  YYSYMBOL_TK_MENOR_IGUAL = 14,            /* TK_MENOR_IGUAL  */
  YYSYMBOL_TK_AND = 15,                    /* TK_AND  */
  YYSYMBOL_TK_OR = 16,                     /* TK_OR  */
  YYSYMBOL_TK_CHAR = 17,                   /* TK_CHAR  */
  YYSYMBOL_TK_BOOL_TRUE = 18,              /* TK_BOOL_TRUE  */
  YYSYMBOL_TK_BOOL_FALSE = 19,             /* TK_BOOL_FALSE  */
  YYSYMBOL_TK_TIPO_STRING = 20,            /* TK_TIPO_STRING  */
  YYSYMBOL_TK_STRING_LITERAL = 21,         /* TK_STRING_LITERAL  */
  YYSYMBOL_TK_IF = 22,                     /* TK_IF  */
  YYSYMBOL_TK_ELSE = 23,                   /* TK_ELSE  */
  YYSYMBOL_TK_ELSE_IF = 24,                /* TK_ELSE_IF  */
  YYSYMBOL_TK_WHILE = 25,                  /* TK_WHILE  */
  YYSYMBOL_TK_FOR = 26,                    /* TK_FOR  */
  YYSYMBOL_TK_DO = 27,                     /* TK_DO  */
  YYSYMBOL_TK_BREAK = 28,                  /* TK_BREAK  */
  YYSYMBOL_TK_CONTINUE = 29,               /* TK_CONTINUE  */
  YYSYMBOL_TK_ESCREVA = 30,                /* TK_ESCREVA  */
  YYSYMBOL_TK_LEIA = 31,                   /* TK_LEIA  */
  YYSYMBOL_TK_SWITCH = 32,                 /* TK_SWITCH  */
  YYSYMBOL_TK_CASE = 33,                   /* TK_CASE  */
  YYSYMBOL_TK_DEFAULT = 34,                /* TK_DEFAULT  */
  YYSYMBOL_TK_IMPRIMIR_VETOR = 35,         /* TK_IMPRIMIR_VETOR  */
  YYSYMBOL_TK_QUICKSORT = 36,              /* TK_QUICKSORT  */
  YYSYMBOL_TK_CONJUNTO = 37,               /* TK_CONJUNTO  */
  YYSYMBOL_TK_PONTO = 38,                  /* TK_PONTO  */
  YYSYMBOL_39_ = 39,                       /* '<'  */
  YYSYMBOL_40_ = 40,                       /* '>'  */
  YYSYMBOL_41_ = 41,                       /* '+'  */
  YYSYMBOL_42_ = 42,                       /* '-'  */
  YYSYMBOL_43_ = 43,                       /* '*'  */
  YYSYMBOL_44_ = 44,                       /* '/'  */
  YYSYMBOL_UMINUS = 45,                    /* UMINUS  */
  YYSYMBOL_46_ = 46,                       /* '!'  */
  YYSYMBOL_47_ = 47,                       /* '('  */
  YYSYMBOL_48_ = 48,                       /* ')'  */
  YYSYMBOL_LOWER_THAN_ELSE = 49,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_50_ = 50,                       /* '{'  */
  YYSYMBOL_51_ = 51,                       /* '}'  */
  YYSYMBOL_52_ = 52,                       /* ';'  */
  YYSYMBOL_53_ = 53,                       /* ','  */
  YYSYMBOL_54_ = 54,                       /* '='  */
  YYSYMBOL_55_ = 55,                       /* '['  */
  YYSYMBOL_56_ = 56,                       /* ']'  */
  YYSYMBOL_57_ = 57,                       /* ':'  */
  YYSYMBOL_58_ = 58,                       /* '%'  */
  YYSYMBOL_YYACCEPT = 59,                  /* $accept  */
  YYSYMBOL_S = 60,                         /* S  */
  YYSYMBOL_INICIO = 61,                    /* INICIO  */
  YYSYMBOL_MAIN = 62,                      /* MAIN  */
  YYSYMBOL_BLOCO = 63,                     /* BLOCO  */
  YYSYMBOL_64_1 = 64,                      /* $@1  */
  YYSYMBOL_COMANDOS = 65,                  /* COMANDOS  */
  YYSYMBOL_COMANDO = 66,                   /* COMANDO  */
  YYSYMBOL_67_2 = 67,                      /* $@2  */
  YYSYMBOL_COMANDO_SAIDA = 68,             /* COMANDO_SAIDA  */
  YYSYMBOL_LISTA_EXPRESSOES = 69,          /* LISTA_EXPRESSOES  */
  YYSYMBOL_COMANDO_ENTRADA = 70,           /* COMANDO_ENTRADA  */
  YYSYMBOL_LISTA_VARIAVEIS = 71,           /* LISTA_VARIAVEIS  */
  YYSYMBOL_DECLARACAO = 72,                /* DECLARACAO  */
  YYSYMBOL_DEFINIR_CONJUNTO = 73,          /* DEFINIR_CONJUNTO  */
  YYSYMBOL_LISTA_MEMBROS = 74,             /* LISTA_MEMBROS  */
  YYSYMBOL_TIPO = 75,                      /* TIPO  */
  YYSYMBOL_DECLAR_VAR = 76,                /* DECLAR_VAR  */
  YYSYMBOL_ATRIB = 77,                     /* ATRIB  */
  YYSYMBOL_LOOP = 78,                      /* LOOP  */
  YYSYMBOL_WHILE_INICIO = 79,              /* WHILE_INICIO  */
  YYSYMBOL_80_3 = 80,                      /* $@3  */
  YYSYMBOL_FOR_INICIO = 81,                /* FOR_INICIO  */
  YYSYMBOL_82_4 = 82,                      /* $@4  */
  YYSYMBOL_DO_WHILE_INICIO = 83,           /* DO_WHILE_INICIO  */
  YYSYMBOL_84_5 = 84,                      /* $@5  */
  YYSYMBOL_COND_IF = 85,                   /* COND_IF  */
  YYSYMBOL_COND_ELSE = 86,                 /* COND_ELSE  */
  YYSYMBOL_SWITCH_STMT = 87,               /* SWITCH_STMT  */
  YYSYMBOL_88_6 = 88,                      /* $@6  */
  YYSYMBOL_89_7 = 89,                      /* $@7  */
  YYSYMBOL_SIMPLE_CASE_LIST = 90,          /* SIMPLE_CASE_LIST  */
  YYSYMBOL_SIMPLE_CASE = 91,               /* SIMPLE_CASE  */
  YYSYMBOL_SIMPLE_DEFAULT = 92,            /* SIMPLE_DEFAULT  */
  YYSYMBOL_EXPR = 93,                      /* EXPR  */
  YYSYMBOL_EXPR_ARIT = 94,                 /* EXPR_ARIT  */
  YYSYMBOL_EXPR_TERM = 95,                 /* EXPR_TERM  */
  YYSYMBOL_EXPR_LOG = 96,                  /* EXPR_LOG  */
  YYSYMBOL_EXPR_REL = 97,                  /* EXPR_REL  */
  YYSYMBOL_EXPR_NOT = 98,                  /* EXPR_NOT  */
  YYSYMBOL_EXPR_ATOM = 99,                 /* EXPR_ATOM  */
  YYSYMBOL_COVERT_TYPE = 100               /* COVERT_TYPE  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   270

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  102
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  231

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   295


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    46,     2,     2,     2,    58,     2,     2,
      47,    48,    43,    41,    53,    42,     2,    44,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    57,    52,
      39,    54,    40,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    55,     2,    56,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    50,     2,    51,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    45,    49
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   166,   166,   183,   196,   203,   218,   218,   262,   265,
     271,   272,   273,   274,   275,   276,   276,   277,   278,   280,
     284,   291,   306,   324,   415,   436,   465,   472,   476,   483,
     515,   519,   527,   528,   529,   530,   531,   535,   542,   552,
     565,   598,   633,   652,   661,   714,   771,   800,   820,   860,
     880,   888,   903,   903,   914,   914,   925,   925,   936,   986,
    1037,  1069,  1075,  1079,  1075,  1120,  1123,  1126,  1132,  1151,
    1161,  1167,  1175,  1184,  1190,  1198,  1206,  1215,  1223,  1229,
    1235,  1241,  1247,  1253,  1259,  1265,  1271,  1277,  1283,  1289,
    1295,  1299,  1312,  1323,  1328,  1332,  1340,  1348,  1357,  1389,
    1442,  1472,  1489
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TK_NUM", "TK_ID",
  "TK_TIPO_INT", "TK_TIPO_FLOAT", "TK_MAIN", "TK_TIPO_CHAR",
  "TK_TIPO_BOOL", "TK_IDX", "TK_IGUAL", "TK_DIFERENTE", "TK_MAIOR_IGUAL",
  "TK_MENOR_IGUAL", "TK_AND", "TK_OR", "TK_CHAR", "TK_BOOL_TRUE",
  "TK_BOOL_FALSE", "TK_TIPO_STRING", "TK_STRING_LITERAL", "TK_IF",
  "TK_ELSE", "TK_ELSE_IF", "TK_WHILE", "TK_FOR", "TK_DO", "TK_BREAK",
  "TK_CONTINUE", "TK_ESCREVA", "TK_LEIA", "TK_SWITCH", "TK_CASE",
  "TK_DEFAULT", "TK_IMPRIMIR_VETOR", "TK_QUICKSORT", "TK_CONJUNTO",
  "TK_PONTO", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "UMINUS", "'!'",
  "'('", "')'", "LOWER_THAN_ELSE", "'{'", "'}'", "';'", "','", "'='",
  "'['", "']'", "':'", "'%'", "$accept", "S", "INICIO", "MAIN", "BLOCO",
  "$@1", "COMANDOS", "COMANDO", "$@2", "COMANDO_SAIDA", "LISTA_EXPRESSOES",
  "COMANDO_ENTRADA", "LISTA_VARIAVEIS", "DECLARACAO", "DEFINIR_CONJUNTO",
  "LISTA_MEMBROS", "TIPO", "DECLAR_VAR", "ATRIB", "LOOP", "WHILE_INICIO",
  "$@3", "FOR_INICIO", "$@4", "DO_WHILE_INICIO", "$@5", "COND_IF",
  "COND_ELSE", "SWITCH_STMT", "$@6", "$@7", "SIMPLE_CASE_LIST",
  "SIMPLE_CASE", "SIMPLE_DEFAULT", "EXPR", "EXPR_ARIT", "EXPR_TERM",
  "EXPR_LOG", "EXPR_REL", "EXPR_NOT", "EXPR_ATOM", "COVERT_TYPE", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-105)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-63)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      16,    11,  -105,  -105,  -105,  -105,  -105,    22,     6,  -105,
      33,    16,    40,     5,  -105,     4,  -105,    20,  -105,  -105,
      -6,    16,   158,    41,    24,   106,  -105,    45,    69,  -105,
    -105,     8,    44,    54,  -105,  -105,  -105,  -105,   154,   106,
     106,  -105,     9,    79,    53,    -2,  -105,  -105,  -105,    50,
      61,    76,  -105,    82,   132,   106,   106,   106,  -105,  -105,
      90,   154,   154,   154,   154,   154,   106,   106,   106,   106,
     106,   106,   106,   106,    85,  -105,   158,    56,  -105,    91,
     108,   114,  -105,    79,    79,  -105,  -105,  -105,    -2,    -2,
      81,    81,  -105,  -105,  -105,  -105,   106,  -105,     1,    44,
      54,   113,   118,   124,   127,  -105,   128,   185,   160,   131,
     133,   134,   135,  -105,   145,   170,   150,   172,  -105,   181,
    -105,   167,   157,   171,  -105,  -105,   173,   224,   106,   106,
    -105,  -105,   106,   226,  -105,  -105,   186,  -105,  -105,  -105,
    -105,  -105,   106,  -105,   125,  -105,   209,  -105,   189,  -105,
     106,  -105,   183,  -105,   182,   -34,  -105,  -105,    -1,   106,
     191,   188,   194,   106,   187,   106,    25,  -105,   106,  -105,
     238,   196,  -105,   106,   106,   197,  -105,  -105,   106,   106,
    -105,  -105,  -105,  -105,   195,   198,  -105,  -105,   192,   225,
     246,   199,   202,   200,   206,   232,   -20,   208,  -105,    66,
     106,   106,  -105,   253,   106,  -105,   255,   203,   210,    66,
    -105,  -105,   211,  -105,   183,   207,  -105,   205,    56,  -105,
    -105,  -105,    88,   185,  -105,   225,   106,  -105,  -105,   212,
     200
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      28,     0,    32,    33,    34,    35,    36,     0,     0,     2,
       4,    28,     0,     0,    42,     0,     1,     0,     3,    27,
      37,    28,    31,     0,     0,     0,    26,     0,     0,     6,
      92,    93,     0,     0,    39,    95,    96,    97,     0,     0,
       0,    38,    89,    73,    70,    80,    87,    77,    94,     0,
       0,     0,     5,     0,     0,     0,     0,     0,    91,    88,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    40,    29,    31,     6,   100,     0,
       0,     0,    90,    71,    72,    74,    75,    76,    78,    79,
      81,    82,    85,    86,    84,    83,     0,    30,    93,    32,
      33,     0,     0,     0,     0,    13,     0,     9,     0,     0,
       0,     0,     0,    14,     0,     0,     0,     0,     6,     0,
      19,     0,     0,    98,   101,   102,     0,     0,     0,     0,
      50,    51,     0,     0,     7,     8,     0,    16,    17,    18,
      10,    11,     0,    53,     0,    55,     0,    57,     0,    12,
       0,    41,   100,    43,     0,     0,    21,    24,     0,     0,
       0,     0,     0,     0,     0,     0,    98,    20,     0,    23,
       0,     0,     6,     0,     0,     0,    99,    46,     0,     0,
      22,    25,     6,    47,     0,     0,    63,    44,     0,    61,
       0,     0,     0,    99,     0,    58,     0,     0,    49,    67,
       0,     0,     6,     0,     0,     6,     0,     0,     0,    67,
      66,    45,     0,    59,     0,     0,    48,     0,     6,    64,
      65,     6,     0,     9,    69,    61,     0,    68,    60,     0,
       0
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -105,  -105,  -105,  -105,   -21,  -105,  -104,  -105,  -105,  -105,
    -105,  -105,  -105,    -4,  -105,   190,   -18,     2,    74,  -105,
    -105,  -105,  -105,  -105,  -105,  -105,  -105,    42,  -105,  -105,
    -105,    60,  -105,  -105,   -24,  -105,   107,  -105,   152,   231,
      52,  -105
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     8,     9,    18,   105,    53,   106,   107,   108,   109,
     155,   110,   158,    10,    11,    27,    12,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   137,   195,   120,   121,
     192,   208,   209,   210,   122,    42,    43,    44,    45,    46,
      47,    48
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      41,    49,    13,   135,    28,    14,    16,    19,    52,    68,
      69,    70,    71,    13,   167,    14,    60,    26,   203,   168,
       1,     2,     3,    13,     4,     5,    15,    30,    31,    32,
      33,    79,    80,    81,   128,   204,     6,    72,    73,   127,
      17,    34,    35,    36,    20,    37,    54,   169,    24,    25,
      61,    62,   170,     7,    22,   128,   129,    21,    28,    30,
      98,    99,   100,    55,     4,     5,    38,    23,    66,    67,
      39,    40,   126,    51,    35,    36,     6,    37,   -15,   178,
     179,   -52,   -54,   -56,   101,   102,   103,   104,   -62,    29,
      58,    56,   -63,   -63,    70,    71,    50,   146,    38,   206,
     207,    57,    39,    40,   153,   154,    74,    -9,   156,    30,
      31,    32,    33,    75,   224,    85,    86,    87,   160,   227,
      72,    73,    63,    64,    35,    36,   164,    37,    76,     1,
       2,     3,    77,     4,     5,   171,    78,    65,    82,   175,
      96,   177,   178,   226,   180,     6,   161,   123,    38,   184,
     185,   183,    39,    40,   187,   188,   124,    30,    31,    32,
      33,   189,   125,     2,     3,   130,     4,     5,    83,    84,
     131,   132,    35,    36,   133,    37,   211,   212,     6,   134,
     215,   213,   136,   138,   216,   139,   140,   141,    30,    98,
      99,   100,   142,     4,     5,   143,    38,   144,   145,   148,
     225,    40,   229,    35,    36,     6,    37,   -15,   147,   149,
     -52,   -54,   -56,   101,   102,   103,   104,   -62,    88,    89,
      90,    91,    92,    93,    94,    95,   150,    38,   152,   151,
     157,    39,    40,   159,   162,    -6,   163,   165,   166,   172,
     173,   174,   181,   176,   182,   186,   191,   190,   193,   194,
     196,   198,   199,   201,   200,   202,   205,   214,   217,   221,
     218,   219,   223,   222,   197,     0,    97,   228,   230,   220,
      59
};

static const yytype_int16 yycheck[] =
{
      24,    25,     0,   107,    22,     4,     0,    11,    29,    11,
      12,    13,    14,    11,    48,     4,    40,    21,    38,    53,
       4,     5,     6,    21,     8,     9,     4,     3,     4,     5,
       6,    55,    56,    57,    54,    55,    20,    39,    40,    38,
       7,    17,    18,    19,     4,    21,    38,    48,    54,    55,
      41,    42,    53,    37,    50,    54,    55,    52,    76,     3,
       4,     5,     6,    55,     8,     9,    42,    47,    15,    16,
      46,    47,    96,     4,    18,    19,    20,    21,    22,    54,
      55,    25,    26,    27,    28,    29,    30,    31,    32,    48,
      38,    47,    11,    12,    13,    14,    51,   118,    42,    33,
      34,    47,    46,    47,   128,   129,    56,    51,   132,     3,
       4,     5,     6,    52,   218,    63,    64,    65,   142,   223,
      39,    40,    43,    44,    18,    19,   150,    21,    52,     4,
       5,     6,    50,     8,     9,   159,     4,    58,    48,   163,
      55,   165,    54,    55,   168,    20,   144,    56,    42,   173,
     174,   172,    46,    47,   178,   179,    48,     3,     4,     5,
       6,   182,    48,     5,     6,    52,     8,     9,    61,    62,
      52,    47,    18,    19,    47,    21,   200,   201,    20,    51,
     204,   202,    22,    52,   205,    52,    52,    52,     3,     4,
       5,     6,    47,     8,     9,    25,    42,    47,    26,    32,
     221,    47,   226,    18,    19,    20,    21,    22,    27,    52,
      25,    26,    27,    28,    29,    30,    31,    32,    66,    67,
      68,    69,    70,    71,    72,    73,    55,    42,     4,    56,
       4,    46,    47,    47,    25,    50,    47,    54,    56,    48,
      52,    47,     4,    56,    48,    48,    48,    52,    56,    24,
       4,    52,    50,    47,    54,    23,    48,     4,     3,    48,
      57,    51,    57,    56,   190,    -1,    76,   225,    56,   209,
      39
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,     6,     8,     9,    20,    37,    60,    61,
      72,    73,    75,    76,     4,     4,     0,     7,    62,    72,
       4,    52,    50,    47,    54,    55,    72,    74,    75,    48,
       3,     4,     5,     6,    17,    18,    19,    21,    42,    46,
      47,    93,    94,    95,    96,    97,    98,    99,   100,    93,
      51,     4,    63,    64,    38,    55,    47,    47,    99,    98,
      93,    41,    42,    43,    44,    58,    15,    16,    11,    12,
      13,    14,    39,    40,    56,    52,    52,    50,     4,    93,
      93,    93,    48,    95,    95,    99,    99,    99,    97,    97,
      97,    97,    97,    97,    97,    97,    55,    74,     4,     5,
       6,    28,    29,    30,    31,    63,    65,    66,    67,    68,
      70,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      87,    88,    93,    56,    48,    48,    93,    38,    54,    55,
      52,    52,    47,    47,    51,    65,    22,    85,    52,    52,
      52,    52,    47,    25,    47,    26,    63,    27,    32,    52,
      55,    56,     4,    93,    93,    69,    93,     4,    71,    47,
      93,    76,    25,    47,    93,    54,    56,    48,    53,    48,
      53,    93,    48,    52,    47,    93,    56,    93,    54,    55,
      93,     4,    48,    63,    93,    93,    48,    93,    93,    63,
      52,    48,    89,    56,    24,    86,     4,    77,    52,    50,
      54,    47,    23,    38,    55,    48,    33,    34,    90,    91,
      92,    93,    93,    63,     4,    93,    63,     3,    57,    51,
      90,    48,    56,    57,    65,    63,    55,    65,    86,    93,
      56
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    59,    60,    61,    61,    62,    64,    63,    65,    65,
      66,    66,    66,    66,    66,    67,    66,    66,    66,    66,
      68,    69,    69,    70,    71,    71,    72,    72,    72,    73,
      74,    74,    75,    75,    75,    75,    75,    76,    76,    76,
      76,    76,    76,    77,    77,    77,    77,    78,    78,    78,
      78,    78,    80,    79,    82,    81,    84,    83,    85,    85,
      86,    86,    88,    89,    87,    90,    90,    90,    91,    92,
      93,    94,    94,    94,    95,    95,    95,    95,    96,    96,
      96,    97,    97,    97,    97,    97,    97,    97,    98,    98,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,   100,   100
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     4,     0,     4,     2,     0,
       2,     2,     2,     1,     1,     0,     2,     2,     2,     1,
       4,     1,     3,     4,     1,     3,     3,     2,     0,     6,
       4,     0,     1,     1,     1,     1,     1,     2,     4,     4,
       5,     8,     2,     3,     6,     9,     5,     5,     9,     7,
       2,     2,     0,     2,     0,     2,     0,     2,     6,     8,
       6,     0,     0,     0,     9,     2,     1,     0,     4,     3,
       1,     3,     3,     1,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     3,     3,     1,     2,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     4,     7,
       3,     4,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* S: INICIO  */
#line 166 "sintatica.y"
           {
        cout << "/*Compilador DHP*/\n";
        cout << "\n#include<stdio.h>\n#include<string.h>\n#include<stdlib.h>\n";
		cout << "#include\"algoritmos/quicksort.h\"\n\n";

        // Mudei o nome da sua função 'Len' para 'get_string_length' para consistência
        if (len) cout << addFuncao(1).str();
		if (inputString) cout << addFuncao(2).str();
		if(inputBool)  cout << addFuncao(3).str();

        // Imprime o resto do código
        cout << fecharPilha().str();        
        cout << yyvsp[0].traducao;
    }
#line 1594 "y.tab.c"
    break;

  case 3: /* INICIO: DECLARACAO MAIN  */
#line 184 "sintatica.y"
        {
		if(yyvsp[-1].traducao.empty()) {
			yyval.traducao = yyvsp[0].traducao;
		} else {
			stringstream ss;
			// função para atribuir os valores das variaveis globais
			ss 	<< "\nvoid D() //Resolve o Problema da atribuição \n{\n"
				<< yyvsp[-1].traducao
				<< "}\n\n";
			yyval.traducao = ss.str() + yyvsp[0].traducao;
		}
	}
#line 1611 "y.tab.c"
    break;

  case 4: /* INICIO: DECLARACAO  */
#line 197 "sintatica.y"
        {
		yyval.traducao = yyvsp[0].traducao;
	}
#line 1619 "y.tab.c"
    break;

  case 5: /* MAIN: TK_MAIN '(' ')' BLOCO  */
#line 203 "sintatica.y"
                               {

		stringstream ss;
		ss << "int main(void)\n";

		ss << "{\n";

		ss << yyvsp[0].traducao;

		ss << "}\n\n";

		yyval.traducao = ss.str();
	  }
#line 1637 "y.tab.c"
    break;

  case 6: /* $@1: %empty  */
#line 218 "sintatica.y"
       { criarPilha(); }
#line 1643 "y.tab.c"
    break;

  case 7: /* BLOCO: $@1 '{' COMANDOS '}'  */
#line 218 "sintatica.y"
                                          {
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

	if(!decls.empty() && !yyvsp[-1].traducao.empty()) {
		ss << "\n";
	}

	// Comandos dentro do bloco
    ss << yyvsp[-1].traducao;

	// Se o bloco for o principal, adiciona retorno
	if(defbloco == 1) { 
		ss << "\n" << qtdTab(1) << free.str();	
		ss << "\n" << qtdTab(1) << "return 0;\n"; 
	}

	yyval.traducao = ss.str();
}
#line 1689 "y.tab.c"
    break;

  case 8: /* COMANDOS: COMANDO COMANDOS  */
#line 262 "sintatica.y"
                         {
		yyval.traducao = yyvsp[-1].traducao + yyvsp[0].traducao;
	}
#line 1697 "y.tab.c"
    break;

  case 9: /* COMANDOS: %empty  */
#line 265 "sintatica.y"
                      {
		yyval.traducao = "";
	}
#line 1705 "y.tab.c"
    break;

  case 10: /* COMANDO: DECLAR_VAR ';'  */
#line 271 "sintatica.y"
                        { yyval.traducao = yyvsp[-1].traducao; }
#line 1711 "y.tab.c"
    break;

  case 11: /* COMANDO: ATRIB ';'  */
#line 272 "sintatica.y"
                        { yyval.traducao = yyvsp[-1].traducao; }
#line 1717 "y.tab.c"
    break;

  case 12: /* COMANDO: EXPR ';'  */
#line 273 "sintatica.y"
                        { yyval.traducao = yyvsp[-1].traducao; }
#line 1723 "y.tab.c"
    break;

  case 13: /* COMANDO: BLOCO  */
#line 274 "sintatica.y"
                                { yyval.traducao = yyvsp[0].traducao; }
#line 1729 "y.tab.c"
    break;

  case 14: /* COMANDO: LOOP  */
#line 275 "sintatica.y"
                        { yyval.traducao = yyvsp[0].traducao; }
#line 1735 "y.tab.c"
    break;

  case 15: /* $@2: %empty  */
#line 276 "sintatica.y"
          { criarPilha(); }
#line 1741 "y.tab.c"
    break;

  case 16: /* COMANDO: $@2 COND_IF  */
#line 276 "sintatica.y"
                                                { yyval.traducao = yyvsp[0].traducao; }
#line 1747 "y.tab.c"
    break;

  case 17: /* COMANDO: COMANDO_SAIDA ';'  */
#line 277 "sintatica.y"
                              { yyval.traducao = yyvsp[-1].traducao; }
#line 1753 "y.tab.c"
    break;

  case 18: /* COMANDO: COMANDO_ENTRADA ';'  */
#line 278 "sintatica.y"
                          { yyval.traducao = yyvsp[-1].traducao; }
#line 1759 "y.tab.c"
    break;

  case 19: /* COMANDO: SWITCH_STMT  */
#line 280 "sintatica.y"
                        { yyval.traducao = yyvsp[0].traducao; }
#line 1765 "y.tab.c"
    break;

  case 20: /* COMANDO_SAIDA: TK_ESCREVA '(' LISTA_EXPRESSOES ')'  */
#line 285 "sintatica.y"
        {
        yyval.traducao = yyvsp[-1].traducao + qtdTab() + "printf(\"\\n\");\n";
    }
#line 1773 "y.tab.c"
    break;

  case 21: /* LISTA_EXPRESSOES: EXPR  */
#line 291 "sintatica.y"
         {
        int idx = buscarVariavel(yyvsp[0].label);
        if (idx == -1) { yyerror("Variavel ou expressao '" + yyvsp[0].label + "' invalida em 'escreva'."); }

        string tipo = pilha[idx][yyvsp[0].label].tipo;
        string var = pilha[idx][yyvsp[0].label].endereco_memoria;
        
        stringstream ss;
        ss << yyvsp[0].traducao; // Inclui o código que calcula a expressão
        
        ss << qtdTab() << "printf(" << "\"" << tipomascara[tipo] << "\", " << var << ");\n"; 
        
        yyval.traducao = ss.str();
    }
#line 1792 "y.tab.c"
    break;

  case 22: /* LISTA_EXPRESSOES: LISTA_EXPRESSOES ',' EXPR  */
#line 306 "sintatica.y"
                                {
        int idx = buscarVariavel(yyvsp[0].label);
        if (idx == -1) { yyerror("Variavel ou expressao '" + yyvsp[0].label + "' invalida em 'output'."); }
        
        string tipo = pilha[idx][yyvsp[0].label].tipo;
        string var = pilha[idx][yyvsp[0].label].endereco_memoria;
        
        stringstream ss;
        ss << yyvsp[0].traducao;

        ss << qtdTab() << "printf(\"" << tipomascara[tipo] << "\", " << var << ");\n";

                
        yyval.traducao = yyvsp[-2].traducao + ss.str();
    }
#line 1812 "y.tab.c"
    break;

  case 23: /* COMANDO_ENTRADA: TK_LEIA '(' LISTA_VARIAVEIS ')'  */
#line 324 "sintatica.y"
                                    {
        yyval.traducao = yyvsp[-1].traducao;
    }
#line 1820 "y.tab.c"
    break;

  case 24: /* LISTA_VARIAVEIS: TK_ID  */
#line 415 "sintatica.y"
          {
        int idx = buscarVariavel(yyvsp[0].label);
        if (idx == -1) { yyerror("Variavel '" + yyvsp[0].label + "' nao declarada para 'leia'."); }

        string tipo = pilha[idx][yyvsp[0].label].tipo;
        string c_nome = pilha[idx][yyvsp[0].label].endereco_memoria;
        
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
        yyval.traducao = ss_code.str();
    }
#line 1846 "y.tab.c"
    break;

  case 25: /* LISTA_VARIAVEIS: LISTA_VARIAVEIS ',' TK_ID  */
#line 436 "sintatica.y"
                                {

        // A lógica é idêntica para o caso recursivo
        int idx = buscarVariavel(yyvsp[0].label);
        if (idx == -1) { yyerror("Variavel '" + yyvsp[0].label + "' nao declarada para 'leia'."); }

        string tipo = pilha[idx][yyvsp[0].label].tipo;
        string c_nome = pilha[idx][yyvsp[0].label].endereco_memoria;
        
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
        
        yyval.traducao = yyvsp[-2].traducao + ss_code.str();
    }
#line 1877 "y.tab.c"
    break;

  case 26: /* DECLARACAO: DECLAR_VAR ';' DECLARACAO  */
#line 466 "sintatica.y"
          {
		if(!yyvsp[-2].traducao.empty()) {
			atribuicaoGlobal = true; // Marca que há atribuição global
		}
        yyval.traducao = yyvsp[-2].traducao;
      }
#line 1888 "y.tab.c"
    break;

  case 27: /* DECLARACAO: DEFINIR_CONJUNTO DECLARACAO  */
#line 472 "sintatica.y"
                                   { //Linhas 472 até 474 são referentes a definição de conjuntos
        yyval.traducao = yyvsp[-1].traducao + yyvsp[0].traducao;
      }
#line 1896 "y.tab.c"
    break;

  case 28: /* DECLARACAO: %empty  */
#line 476 "sintatica.y"
          {
		yyval.traducao = "";
	  }
#line 1904 "y.tab.c"
    break;

  case 29: /* DEFINIR_CONJUNTO: TK_CONJUNTO TK_ID '{' LISTA_MEMBROS '}' ';'  */
#line 483 "sintatica.y"
                                                {
        string nomeConjunto = yyvsp[-4].label;
        if (definicoesConjunto.count(nomeConjunto)) {
            yyerror("Conjunto '" + nomeConjunto + "' ja foi definido.");
        }
        
        // $4.label contém os nomes dos membros e $4.traducao os tipos, separados por '|'
        stringstream ss_nomes(yyvsp[-2].label);
        stringstream ss_tipos(yyvsp[-2].traducao);
        string nomeMembro, tipoMembro;
        MembrosConjunto membros;

        while(getline(ss_nomes, nomeMembro, '|') && getline(ss_tipos, tipoMembro, '|')) {
            if (!nomeMembro.empty()) {
                membros[nomeMembro] = tipoMembro;
            }
        }
        definicoesConjunto[nomeConjunto] = membros;

        // Geração do código C para a struct (isso vai para o topo do resultado.c)
        stringstream ss_code;
        ss_code << "struct " << nomeConjunto << " {\n";
        for(auto const& [membro, tipo] : membros) {
            ss_code << "\t" << tipoTraducao[tipo] << " " << membro << ";\n";
        }
        ss_code << "};\n\n";
        yyval.traducao = ss_code.str();
    }
#line 1937 "y.tab.c"
    break;

  case 30: /* LISTA_MEMBROS: TIPO TK_ID ';' LISTA_MEMBROS  */
#line 515 "sintatica.y"
                                 {
        yyval.label = yyvsp[-2].label + "|" + yyvsp[0].label;
        yyval.traducao = yyvsp[-3].label + "|" + yyvsp[0].traducao;
    }
#line 1946 "y.tab.c"
    break;

  case 31: /* LISTA_MEMBROS: %empty  */
#line 519 "sintatica.y"
                  {
        yyval.label = "";
        yyval.traducao = "";
    }
#line 1955 "y.tab.c"
    break;

  case 32: /* TIPO: TK_TIPO_INT  */
#line 527 "sintatica.y"
                    { yyval.label = "int"; }
#line 1961 "y.tab.c"
    break;

  case 33: /* TIPO: TK_TIPO_FLOAT  */
#line 528 "sintatica.y"
                    { yyval.label = "float"; }
#line 1967 "y.tab.c"
    break;

  case 34: /* TIPO: TK_TIPO_CHAR  */
#line 529 "sintatica.y"
                    { yyval.label = "char"; }
#line 1973 "y.tab.c"
    break;

  case 35: /* TIPO: TK_TIPO_BOOL  */
#line 530 "sintatica.y"
                    { yyval.label = "bool"; }
#line 1979 "y.tab.c"
    break;

  case 36: /* TIPO: TK_TIPO_STRING  */
#line 531 "sintatica.y"
                         { yyval.label = "string"; }
#line 1985 "y.tab.c"
    break;

  case 37: /* DECLAR_VAR: TIPO TK_ID  */
#line 535 "sintatica.y"
               {
        string nome = yyvsp[0].label;
        string tipo = yyvsp[-1].label;
        int dimensoes[] = {0, 0}; // Inicializa dimensões como 0
        adicionaVar(nome, tipo, 0, dimensoes, false, false);
        yyval.traducao = "";
    }
#line 1997 "y.tab.c"
    break;

  case 38: /* DECLAR_VAR: TIPO TK_ID '=' EXPR  */
#line 542 "sintatica.y"
                          {
        string nome = yyvsp[-2].label;
        string tipo = yyvsp[-3].label;
        int dimensoes[] = {0, 0}; // Inicializa dimensões como 0
        adicionaVar(nome, tipo, 0, dimensoes, false, false);
        pilha[pilha.size()-1][nome].inicializado = true;
        stringstream ss;
        ss = veririficarTipo(yyvsp[-2].label, "=", yyvsp[0].label);
        yyval.traducao = yyvsp[0].traducao + ss.str();
    }
#line 2012 "y.tab.c"
    break;

  case 39: /* DECLAR_VAR: TIPO TK_ID '=' TK_CHAR  */
#line 552 "sintatica.y"
                             {
        string nome = yyvsp[-2].label;
        string tipo = yyvsp[-3].label;
        int dimensoes[] = {0, 0}; // Inicializa dimensões como 0
        adicionaVar(nome, tipo, 0, dimensoes, false, false);
        if(tipo != "char") {
            cout << "Atribuindo char a variavel '" << nome << "' do tipo '" << tipo << "'\n";
            exit(1);}
        pilha[pilha.size()-1][nome].inicializado = true; 
        stringstream ss;
        ss << qtdTab() << pilha[pilha.size()-1][nome].endereco_memoria << " = " << yyvsp[0].label << ";\n";
        yyval.traducao = ss.str();
    }
#line 2030 "y.tab.c"
    break;

  case 40: /* DECLAR_VAR: TIPO TK_ID '[' EXPR ']'  */
#line 565 "sintatica.y"
                              {
        string tipo_elemento = yyvsp[-4].label;
        string nome_vetor = yyvsp[-3].label;
        string tamanho = yyvsp[-1].label;
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

        yyval.traducao = ss.str();
    }
#line 2068 "y.tab.c"
    break;

  case 41: /* DECLAR_VAR: TIPO TK_ID '[' EXPR ']' '[' EXPR ']'  */
#line 598 "sintatica.y"
                                           {        
        string tipo_elemento = yyvsp[-7].label;
        string nome_matriz = yyvsp[-6].label;
        string linha = yyvsp[-4].label;
        string colunas = yyvsp[-1].label;
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
        yyval.traducao = ss.str();
    }
#line 2108 "y.tab.c"
    break;

  case 42: /* DECLAR_VAR: TK_ID TK_ID  */
#line 633 "sintatica.y"
                  { // Definição o conjunto Ex: Ponto p1; (onde Ponto é um conjunto já definido)
        string nomeConjunto = yyvsp[-1].label;
        string nomeVariavel = yyvsp[0].label;

        if (!definicoesConjunto.count(nomeConjunto)) {
            // Se não for um conjunto definido, pode ser um erro ou outra regra.
            // O Bison/Yacc tentará outras alternativas. Se nenhuma funcionar, dará erro.
            // Para ser mais explícito, você pode deixar esta regra mais específica se necessário.
            yyerror("Tipo '" + nomeConjunto + "' nao e um tipo de conjunto definido.");
        }
        
        int dimensoes[] = {0, 0};
        adicionaVar(nomeVariavel, nomeConjunto, 0, dimensoes, false, false);
        pilha.back()[nomeVariavel].eh_set = true; // Marca como conjunto
        yyval.traducao = ""; // A declaração será feita por fecharPilha()
    }
#line 2129 "y.tab.c"
    break;

  case 43: /* ATRIB: TK_ID '=' EXPR  */
#line 652 "sintatica.y"
                   {
        if (buscarVariavel(yyvsp[-2].label) == -1) { 
            yyerror("Variavel '" + yyvsp[-2].label + "' nao declarada."); 
        }
        stringstream ss;
        ss = veririficarTipo(yyvsp[-2].label, "=", yyvsp[0].label);
        yyval.traducao = yyvsp[0].traducao + ss.str();
    }
#line 2142 "y.tab.c"
    break;

  case 44: /* ATRIB: TK_ID '[' EXPR ']' '=' EXPR  */
#line 661 "sintatica.y"
                                 {

        string nome = yyvsp[-5].label;
        string tipo1 = pilha[buscarVariavel(nome)][nome].tipo;
        
        string nome2 = yyvsp[0].label;
        string tipo2 = pilha[buscarVariavel(nome2)][nome2].tipo;



        string idx = yyvsp[-3].label;
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
        
        ss << yyvsp[-3].traducao; // Código do índice
        ss << yyvsp[0].traducao; // Código da expressão à direita

        string new_temp = newTemp(tipo1);
        ss << qtdTab() << new_temp << " = " << idx << ";\n"; // Cria uma temporária para o índice
        ss << qtdTab() << pilha[buscarVariavel(nome)][nome].endereco_memoria << "[" << new_temp << "] = " << yyvsp[0].label << ";\n";
        

        yyval.traducao = ss.str();
    }
#line 2199 "y.tab.c"
    break;

  case 45: /* ATRIB: TK_ID '[' EXPR ']' '[' EXPR ']' '=' EXPR  */
#line 714 "sintatica.y"
                                              {
        
        string nome = yyvsp[-8].label;
        string tipo1 = pilha[buscarVariavel(nome)][nome].tipo;

        string nome2 = yyvsp[-1].label;
        string tipo2 = pilha[buscarVariavel(nome2)][nome2].tipo;

        string idx_linha = yyvsp[-6].label;
        string idx_coluna = yyvsp[-3].label;

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
        ss << yyvsp[-6].traducao; // Código do primeiro índice (linha)
        ss << yyvsp[-3].traducao; // Código do segundo índice (coluna)
        ss << yyvsp[0].traducao; // Código da expressão à direita

        string temp = newTemp("int"); // Temporária para o cálculo do offset
        string temp2 = newTemp("int"); // Temporária para o cálculo do offset
        ss << qtdTab() << temp << " = " << pilha[buscarVariavel(idx_linha)][idx_linha].endereco_memoria << " * " << pilha[buscarVariavel(nome)][nome].dimensoes[1] << ";\n";
        ss << qtdTab() << temp2 << " = " << temp << " + " << pilha[buscarVariavel(idx_coluna)][idx_coluna].endereco_memoria << ";\n";
        ss << qtdTab() << pilha[buscarVariavel(nome)][nome].endereco_memoria << "[" << temp2 << "] = " << yyvsp[0].label << ";\n"; // Atribuição ao elemento da matriz

        yyval.traducao = ss.str();
    }
#line 2260 "y.tab.c"
    break;

  case 46: /* ATRIB: TK_ID TK_PONTO TK_ID '=' EXPR  */
#line 771 "sintatica.y"
                                    {
        string nomeVariavel = yyvsp[-4].label;
        string nomeMembro = yyvsp[-2].label;
        int idx = buscarVariavel(nomeVariavel);

        // Validações
        if (idx == -1) { yyerror("Variavel '" + nomeVariavel + "' nao declarada."); }
        if (!pilha[idx][nomeVariavel].eh_set) { yyerror("Variavel '" + nomeVariavel + "' nao e um conjunto."); }
        
        string tipoConjunto = pilha[idx][nomeVariavel].tipo;
        if (!definicoesConjunto[tipoConjunto].count(nomeMembro)) {
            yyerror("Conjunto '" + tipoConjunto + "' nao tem o membro '" + nomeMembro + "'.");
        }

        // Geração de código 3AC
        stringstream ss;
        ss << yyvsp[0].traducao; // 1. Gera o código para a expressão da direita (EXPR)
        
        string enderecoVar = pilha[idx][nomeVariavel].endereco_memoria;
        string enderecoExpr = pilha[buscarVariavel(yyvsp[0].label)][yyvsp[0].label].endereco_memoria;
        
        // 2. Gera a atribuição final
        ss << qtdTab() << enderecoVar << "." << nomeMembro << " = " << enderecoExpr << ";\n";
        
        yyval.traducao = ss.str();
    }
#line 2291 "y.tab.c"
    break;

  case 47: /* LOOP: WHILE_INICIO '(' EXPR ')' BLOCO  */
#line 800 "sintatica.y"
                                          {
        // Ação Final do While
        // $1 é WHILE_INICIO (contém os rótulos), $3 é EXPR, $5 é BLOCO
        string inícioDoLaço = yyvsp[-4].label;
        string fimDoLaço = yyvsp[-4].traducao;
        string temp_cond = pilha[buscarVariavel(yyvsp[-2].label)][yyvsp[-2].label].endereco_memoria;

        stringstream ss;
        ss << "\n" << qtdTab() << inícioDoLaço << ":\n";    // Rótulo para o CONTINUE
        ss << yyvsp[-2].traducao;                                    // Código da condição
        ss << qtdTab(1) << "if (!" << temp_cond << ") goto " << fimDoLaço << ";\n";
        ss << yyvsp[0].traducao;                                    // Corpo do laço
        ss << qtdTab(1) << "goto " << inícioDoLaço << ";\n";  // Volta para o início
        ss << qtdTab() << fimDoLaço << ":;\n";                // Rótulo para o BREAK
        yyval.traducao = ss.str();

        if (!pilhaDeRotulosDeLaços.empty()) { pilhaDeRotulosDeLaços.pop_back(); }
    }
#line 2314 "y.tab.c"
    break;

  case 48: /* LOOP: FOR_INICIO '(' DECLAR_VAR ';' EXPR ';' ATRIB ')' BLOCO  */
#line 820 "sintatica.y"
                                                             {
        // Ação Final do For
        if (!pilhaDeRotulosDeLaços.empty()) { pilhaDeRotulosDeLaços.pop_back(); }

        // $1 é FOR_INICIO, contém os rótulos como "teste|iteracao|fim"
        string labels_str = yyvsp[-8].label;
        stringstream ss_labels(labels_str);
        string rótuloTeste, rótuloIteração, rótuloFim;
        getline(ss_labels, rótuloTeste, '|');
        getline(ss_labels, rótuloIteração, '|');
        getline(ss_labels, rótuloFim, '|');
        
        string temp_cond = pilha[buscarVariavel(yyvsp[-4].label)][yyvsp[-4].label].endereco_memoria;

        stringstream ss;
        ss << "\n" << qtdTab(-1) << "{\n";
        ss << fecharPilha().str();
        ss << "\n";
        ss << yyvsp[-6].traducao;                          // 1. Inicialização
        ss << qtdTab(1) << "goto " << rótuloTeste << ";\n\n";
        
        ss << qtdTab(1) << rótuloIteração << ":\n";  // 4. Rótulo do CONTINUE
        ss << yyvsp[-2].traducao;                          // 5. Iteração
        ss << "\n";
        
        ss << qtdTab(1) << rótuloTeste << ":\n";    // 2. Rótulo para o teste
        ss << yyvsp[-4].traducao;                         // 3. Condição
        ss << qtdTab(1) << "if (!" << temp_cond << ") goto " << rótuloFim << ";\n\n";
        
        ss << yyvsp[0].traducao;                         // Corpo do laço
        ss << "\n";
        
        ss << qtdTab(1) << "goto " << rótuloIteração << ";\n"; // Volta para o passo de iteração
        
        ss << qtdTab(1) << rótuloFim << ":;\n";      // 6. Rótulo do BREAK
        ss << qtdTab() << "}\n";
        yyval.traducao = ss.str();
    }
#line 2357 "y.tab.c"
    break;

  case 49: /* LOOP: DO_WHILE_INICIO BLOCO TK_WHILE '(' EXPR ')' ';'  */
#line 860 "sintatica.y"
                                                      {
        if (!pilhaDeRotulosDeLaços.empty()) { pilhaDeRotulosDeLaços.pop_back(); }

        string inícioDoLaço = yyvsp[-6].label;     // Continue
        string fimDoLaço = yyvsp[-6].traducao;     // Break
        string temp_cond = pilha[buscarVariavel(yyvsp[-2].label)][yyvsp[-2].label].endereco_memoria;

        stringstream ss;
        ss << "\n" << qtdTab(-1) << "{\n";
        ss << fecharPilha().str();
        ss << "\n";
        ss << qtdTab(1) << inícioDoLaço << ":\n";
        ss << yyvsp[-5].traducao;                         // Corpo do laço
        ss << "\n";
        ss << yyvsp[-2].traducao;                         // Condição
        ss << qtdTab(1) << "if (" << temp_cond << ") goto " << inícioDoLaço << ";\n";
        ss << qtdTab(1) << fimDoLaço << ":;\n";      // Rótulo para o break
        ss << qtdTab() << "}\n";
        yyval.traducao = ss.str();
    }
#line 2382 "y.tab.c"
    break;

  case 50: /* LOOP: TK_BREAK ';'  */
#line 880 "sintatica.y"
                   { 
        if (pilhaDeRotulosDeLaços.empty()) {
            yyerror("'break' fora de um laco ou switch");
        }
        stringstream ss;
        ss << qtdTab() << "goto " << pilhaDeRotulosDeLaços.back().rotuloBreak << ";\n";
        yyval.traducao = ss.str();
    }
#line 2395 "y.tab.c"
    break;

  case 51: /* LOOP: TK_CONTINUE ';'  */
#line 888 "sintatica.y"
                      { 
        if (pilhaDeRotulosDeLaços.empty()) {
            yyerror("'continue' fora de um laco");
        }
        // Adicione aqui a checagem se o alvo do continue é para switch, se necessário
        if (pilhaDeRotulosDeLaços.back().rotuloContinue.find("EndSwitch") != string::npos) {
             yyerror("'continue' invalido dentro de um switch");
        }
        stringstream ss;
        ss << qtdTab() << "goto " << pilhaDeRotulosDeLaços.back().rotuloContinue << ";\n";
        yyval.traducao = ss.str();
    }
#line 2412 "y.tab.c"
    break;

  case 52: /* $@3: %empty  */
#line 903 "sintatica.y"
    { criarPilha(); }
#line 2418 "y.tab.c"
    break;

  case 53: /* WHILE_INICIO: $@3 TK_WHILE  */
#line 903 "sintatica.y"
                               {
        string inícioDoLaço = "BeginWhile_" + to_string(defgoto);
        string fimDoLaço   = "EndWhile_" + to_string(defgoto);
        pilhaDeRotulosDeLaços.push_back({fimDoLaço, inícioDoLaço}); // Empilha
        defgoto++; // Incrementa IMEDIATAMENTE
        yyval.label = inícioDoLaço;
        yyval.traducao = fimDoLaço;
    }
#line 2431 "y.tab.c"
    break;

  case 54: /* $@4: %empty  */
#line 914 "sintatica.y"
    { criarPilha(); }
#line 2437 "y.tab.c"
    break;

  case 55: /* FOR_INICIO: $@4 TK_FOR  */
#line 914 "sintatica.y"
                             {
        string rótuloTeste    = "ForTest_" + to_string(defgoto);
        string rótuloIteração = "ForStep_" + to_string(defgoto); // Alvo do 'continue'
        string rótuloFim      = "ForEnd_"  + to_string(defgoto); // Alvo do 'break'
        pilhaDeRotulosDeLaços.push_back({rótuloFim, rótuloIteração}); // Empilha
        defgoto++; // Incrementa IMEDIATAMENTE
        yyval.label = rótuloTeste + "|" + rótuloIteração + "|" + rótuloFim;
    }
#line 2450 "y.tab.c"
    break;

  case 56: /* $@5: %empty  */
#line 925 "sintatica.y"
    { criarPilha(); }
#line 2456 "y.tab.c"
    break;

  case 57: /* DO_WHILE_INICIO: $@5 TK_DO  */
#line 925 "sintatica.y"
                            {
        string inícioDoLaço = "BeginDoWhile_" + to_string(defgoto);
        string fimDoLaço   = "EndDoWhile_" + to_string(defgoto);
        pilhaDeRotulosDeLaços.push_back({fimDoLaço, inícioDoLaço}); // Empilha
        defgoto++; // Incrementa IMEDIATAMENTE
        yyval.label = inícioDoLaço;
        yyval.traducao = fimDoLaço;
    }
#line 2469 "y.tab.c"
    break;

  case 58: /* COND_IF: TK_IF '(' EXPR ')' BLOCO COND_ELSE  */
#line 936 "sintatica.y"
                                                                  {

		// Verificações
		if (buscarVariavel(yyvsp[-3].label) == -1) {
			cout << "Erro: Variável '" << yyvsp[-3].label << "' não declarada na condição do if.\n";
			exit(1);
		}
		if (pilha[buscarVariavel(yyvsp[-3].label)][yyvsp[-3].label].tipo != "bool") {
			cout << "Erro: Condição do if deve ser do tipo booleano, mas é '" << pilha[buscarVariavel(yyvsp[-3].label)][yyvsp[-3].label].tipo << "'.\n";
			exit(1);
		}

		// Geração de código
		stringstream ss;
		string temp = pilha[buscarVariavel(yyvsp[-3].label)][yyvsp[-3].label].endereco_memoria; // Endereço de memória da variável condicional

		ss << "\n";

		ss << qtdTab(-1) << "{\n"; // Abre a pilha de variáveis para o if

		ss << fecharPilha().str(); // Fecha a pilha de variáveis antes do if

		ss << "\n";

		ss << yyvsp[-3].traducao; // Traduz a expressão condicional

		ss << qtdTab(1) << "if (!" << temp << ") goto EndIf" << defgoto << ";\n";

		ss << yyvsp[-1].traducao; // Traduz o bloco do if

		if (!yyvsp[0].traducao.empty()) {
			ss << qtdTab(1) << "goto EndElse" << defgoto << ";\n"; // Se não houver else-if, pula para o final
		} 

		ss << qtdTab(1) << "EndIf" << defgoto << ":\n";

		ss << "\n";

		ss << yyvsp[0].traducao; // Traduz o bloco do else-if, se houver
		
		if (!yyvsp[0].traducao.empty()) {
			ss << qtdTab(1) << "EndElse" << defgoto << ":\n"; // Marca o final do if/else
		}

		ss << qtdTab() << "}\n"; // Fecha a pilha de variáveis do if
		tempElse = 0; // Reseta o contador de else-if
		defgoto++; // Incrementa o contador de blocos de if/else

		yyval.traducao = ss.str();
	}
#line 2524 "y.tab.c"
    break;

  case 59: /* COND_IF: TK_IF '(' EXPR ')' BLOCO COND_ELSE TK_ELSE BLOCO  */
#line 986 "sintatica.y"
                                                                         {

		// Verificações
		if (buscarVariavel(yyvsp[-5].label) == -1) {
			cout << "Erro: Variável '" << yyvsp[-5].label << "' não declarada na condição do if.\n";
			exit(1);
		}
		if (pilha[buscarVariavel(yyvsp[-5].label)][yyvsp[-5].label].tipo != "bool") {
			cout << "Erro: Condição do if deve ser do tipo booleano, mas é '" << pilha[buscarVariavel(yyvsp[-5].label)][yyvsp[-5].label].tipo << "'.\n";
			exit(1);
		}

		// Geração de código
		stringstream ss;
		string temp = pilha[buscarVariavel(yyvsp[-5].label)][yyvsp[-5].label].endereco_memoria; // Endereço de memória da variável condicional

		ss << "\n";

		ss << qtdTab(-1) << "{\n"; // Abre a pilha de variáveis para o if

		ss << fecharPilha().str(); // Fecha a pilha de variáveis antes do if
		
		ss << "\n";

		ss << yyvsp[-5].traducao; // Traduz a expressão condicional

		ss << qtdTab(1) << "if (!" << temp << ") goto EndIf" << defgoto << ";\n";

		ss << yyvsp[-3].traducao; // Traduz o bloco do if
		
		ss << qtdTab(1) << "goto EndElse" << defgoto << ";\n";

		ss << qtdTab(1) << "EndIf" << defgoto << ":\n";

		ss << yyvsp[-2].traducao; // Traduz o bloco do else-if, se houver

		ss << yyvsp[0].traducao; // Traduz o bloco do else

		if (!yyvsp[0].traducao.empty()) {
			ss << qtdTab(1) << "EndElse" << defgoto << ":\n"; // Se houver else, pula para o final
		}

		ss << qtdTab() << "}\n"; // Fecha a pilha de variáveis do if/else

		tempElse = 0; // Reseta o contador de else-if
		defgoto++; // Incrementa o contador de blocos de if/else

		yyval.traducao = ss.str();
	}
#line 2578 "y.tab.c"
    break;

  case 60: /* COND_ELSE: TK_ELSE_IF '(' EXPR ')' BLOCO COND_ELSE  */
#line 1037 "sintatica.y"
                                                                      {
		
		// Verificações
		if (buscarVariavel(yyvsp[-3].label) == -1) {
			cout << "Erro: Variável '" << yyvsp[-3].label << "' não declarada na condição do else-if.\n";
			exit(1);
		}
		if (pilha[buscarVariavel(yyvsp[-3].label)][yyvsp[-3].label].tipo != "bool") {
			cout << "Erro: Condição do else-if deve ser do tipo booleano, mas é '" << pilha[buscarVariavel(yyvsp[-3].label)][yyvsp[-3].label].tipo << "'.\n";
			exit(1);
		}

		// Geração de código

		stringstream ss;
		string temp = pilha[buscarVariavel(yyvsp[-3].label)][yyvsp[-3].label].endereco_memoria; // Endereço de memória da variável condicional

		ss << "\n";

		ss << yyvsp[-3].traducao; // Traduz a expressão condicional do else-if

		ss << qtdTab() << "if (!" << temp << ") goto EndElseIf" << tempElse << ";\n";

		ss << yyvsp[-1].traducao; // Traduz o bloco do else-if

		ss << qtdTab() << "goto EndElse" << defgoto << ";\n";

		ss << qtdTab() << "EndElseIf" << tempElse++ << ":\n";

		yyval.traducao = ss.str() + yyvsp[0].traducao; // Combina com a tradução do bloco do else-if
	}
#line 2614 "y.tab.c"
    break;

  case 61: /* COND_ELSE: %empty  */
#line 1069 "sintatica.y"
        {
		yyval.traducao = "";
	}
#line 2622 "y.tab.c"
    break;

  case 62: /* $@6: %empty  */
#line 1075 "sintatica.y"
    { 
        criarPilha(); 
        addPilhaLaco("EndSwitch" + to_string(defgoto), "EndSwitch" + to_string(defgoto)); 
    }
#line 2631 "y.tab.c"
    break;

  case 63: /* $@7: %empty  */
#line 1079 "sintatica.y"
                           {
        // Armazenar a variável do switch globalmente
        if (buscarVariavel(yyvsp[-1].label) == -1) {
            yyerror("Variável '" + yyvsp[-1].label + "' não declarada no switch.");
        }
        current_switch_var = pilha[buscarVariavel(yyvsp[-1].label)][yyvsp[-1].label].endereco_memoria;
    }
#line 2643 "y.tab.c"
    break;

  case 64: /* SWITCH_STMT: $@6 TK_SWITCH '(' EXPR ')' $@7 '{' SIMPLE_CASE_LIST '}'  */
#line 1086 "sintatica.y"
                             {
        
        // Geração de código
        stringstream ss;
        string rotuloEnd = pilhaDeRotulosDeLaços.back().rotuloBreak;
        string switch_id = to_string(defgoto);
        
        ss << qtdTab(-1) << "{\n";
        ss << fecharPilha().str();
        ss << "\n";
        
        // Avalia a expressão do switch

        ss << yyvsp[-5].traducao;
        
        // Gera os cases
        ss << yyvsp[-1].traducao;
        
        // Label de saída do switch
        ss << qtdTab(1) << rotuloEnd << ":\n";
        ss << qtdTab() << "}\n";
        
        // Remove da pilha de laços
        pilhaDeRotulosDeLaços.pop_back();
        defgoto++;
        
        // Limpar a variável global
        current_switch_var = "";
        
        yyval.traducao = ss.str();
    }
#line 2679 "y.tab.c"
    break;

  case 65: /* SIMPLE_CASE_LIST: SIMPLE_CASE SIMPLE_CASE_LIST  */
#line 1120 "sintatica.y"
                                 {
        yyval.traducao = yyvsp[-1].traducao + yyvsp[0].traducao;
    }
#line 2687 "y.tab.c"
    break;

  case 66: /* SIMPLE_CASE_LIST: SIMPLE_DEFAULT  */
#line 1123 "sintatica.y"
                     {
        yyval.traducao = yyvsp[0].traducao;
    }
#line 2695 "y.tab.c"
    break;

  case 67: /* SIMPLE_CASE_LIST: %empty  */
#line 1126 "sintatica.y"
                  {
        yyval.traducao = "";
    }
#line 2703 "y.tab.c"
    break;

  case 68: /* SIMPLE_CASE: TK_CASE TK_NUM ':' COMANDOS  */
#line 1132 "sintatica.y"
                                {
        stringstream ss;
        string case_id = to_string(defgoto);
        
        // Mesmo padrão do if: comparação em três endereços
        string temp_val = newTemp("int");
        string temp_comp = newTemp("bool");
        
        ss <<"\n"<< qtdTab() << temp_val << " = " << yyvsp[-2].traducao << ";\n";
        ss << qtdTab() << temp_comp << " = " << current_switch_var << " == " << temp_val << ";\n\n";
        ss << qtdTab() << "if (!" << temp_comp << ") goto NextCase" << case_id << "_" << yyvsp[-2].traducao << ";\n";
        ss << yyvsp[0].traducao;
        ss << qtdTab() << "NextCase" << case_id << "_" << yyvsp[-2].traducao << ":\n";
        
        yyval.traducao = ss.str();
    }
#line 2724 "y.tab.c"
    break;

  case 69: /* SIMPLE_DEFAULT: TK_DEFAULT ':' COMANDOS  */
#line 1151 "sintatica.y"
                            {
        stringstream ss;
        
        ss << "\n" << yyvsp[0].traducao;
        
        yyval.traducao = ss.str();
    }
#line 2736 "y.tab.c"
    break;

  case 70: /* EXPR: EXPR_LOG  */
#line 1161 "sintatica.y"
             { // Removido o '|' inicial e o '%prec TK_OR'
        yyval.label = yyvsp[0].label;     // <<< ADICIONADO E CRUCIAL
        yyval.traducao = yyvsp[0].traducao;
    }
#line 2745 "y.tab.c"
    break;

  case 71: /* EXPR_ARIT: EXPR_ARIT '+' EXPR_TERM  */
#line 1167 "sintatica.y"
                                           {
		stringstream ss;
		string var1 = yyvsp[-2].label;
		string var2 = yyvsp[0].label;
		ss = veririficarTipo(var1, "+", var2);
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
        }
#line 2758 "y.tab.c"
    break;

  case 72: /* EXPR_ARIT: EXPR_ARIT '-' EXPR_TERM  */
#line 1175 "sintatica.y"
                                        {
        stringstream ss;
		string var1 = yyvsp[-2].label;
		string var2 = yyvsp[0].label;
		ss = veririficarTipo(var1, "-", var2);
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();

	}
#line 2772 "y.tab.c"
    break;

  case 73: /* EXPR_ARIT: EXPR_TERM  */
#line 1184 "sintatica.y"
                {
        yyval.label = yyvsp[0].label;
        yyval.traducao = yyvsp[0].traducao;
    }
#line 2781 "y.tab.c"
    break;

  case 74: /* EXPR_TERM: EXPR_TERM '*' EXPR_ATOM  */
#line 1190 "sintatica.y"
                                                  {
		stringstream ss;
		string var1 = yyvsp[-2].label;
		string var2 = yyvsp[0].label;
		ss = veririficarTipo(var1, "*", var2);
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 2794 "y.tab.c"
    break;

  case 75: /* EXPR_TERM: EXPR_TERM '/' EXPR_ATOM  */
#line 1198 "sintatica.y"
                                            {
		stringstream ss;
		string var1 = yyvsp[-2].label;
		string var2 = yyvsp[0].label;
		ss = veririficarTipo(var1, "/", var2);
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 2807 "y.tab.c"
    break;

  case 76: /* EXPR_TERM: EXPR_TERM '%' EXPR_ATOM  */
#line 1206 "sintatica.y"
                                            {
		stringstream ss;
		string var1 = yyvsp[-2].label;
		string var2 = yyvsp[0].label;
		ss = veririficarTipo(var1, "%", var2);
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 2820 "y.tab.c"
    break;

  case 77: /* EXPR_TERM: EXPR_ATOM  */
#line 1215 "sintatica.y"
                    {
		yyval.label = yyvsp[0].label;
		yyval.traducao = yyvsp[0].traducao;
	}
#line 2829 "y.tab.c"
    break;

  case 78: /* EXPR_LOG: EXPR_LOG TK_AND EXPR_REL  */
#line 1223 "sintatica.y"
                                              {
		stringstream ss;
		ss = veririficarTipo(yyvsp[-2].label, "&&", yyvsp[0].label);
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 2840 "y.tab.c"
    break;

  case 79: /* EXPR_LOG: EXPR_LOG TK_OR EXPR_REL  */
#line 1229 "sintatica.y"
                                              {
		stringstream ss;
		ss = veririficarTipo(yyvsp[-2].label, "||", yyvsp[0].label);
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 2851 "y.tab.c"
    break;

  case 80: /* EXPR_LOG: EXPR_REL  */
#line 1235 "sintatica.y"
                   {
		yyval.label = yyvsp[0].label;
		yyval.traducao = yyvsp[0].traducao;
	}
#line 2860 "y.tab.c"
    break;

  case 81: /* EXPR_REL: EXPR_REL TK_IGUAL EXPR_REL  */
#line 1241 "sintatica.y"
                                                  {
		stringstream ss;
		ss = veririficarTipo(yyvsp[-2].label, "==", yyvsp[0].label);
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 2871 "y.tab.c"
    break;

  case 82: /* EXPR_REL: EXPR_REL TK_DIFERENTE EXPR_REL  */
#line 1247 "sintatica.y"
                                                            {
		stringstream ss;
		ss = veririficarTipo(yyvsp[-2].label, "!=", yyvsp[0].label);
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 2882 "y.tab.c"
    break;

  case 83: /* EXPR_REL: EXPR_REL '>' EXPR_REL  */
#line 1253 "sintatica.y"
                                          {
		stringstream ss;
		ss = veririficarTipo(yyvsp[-2].label, ">", yyvsp[0].label);
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 2893 "y.tab.c"
    break;

  case 84: /* EXPR_REL: EXPR_REL '<' EXPR_REL  */
#line 1259 "sintatica.y"
                                          {
		stringstream ss;	
		ss = veririficarTipo(yyvsp[-2].label, "<", yyvsp[0].label);
		yyval.label = "t" + to_string(tempVar-1);		
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 2904 "y.tab.c"
    break;

  case 85: /* EXPR_REL: EXPR_REL TK_MAIOR_IGUAL EXPR_REL  */
#line 1265 "sintatica.y"
                                                                {
		stringstream ss;
		ss = veririficarTipo(yyvsp[-2].label, ">=", yyvsp[0].label);
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 2915 "y.tab.c"
    break;

  case 86: /* EXPR_REL: EXPR_REL TK_MENOR_IGUAL EXPR_REL  */
#line 1271 "sintatica.y"
                                                                {
		stringstream ss;
		ss = veririficarTipo(yyvsp[-2].label, "<=", yyvsp[0].label);
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 2926 "y.tab.c"
    break;

  case 87: /* EXPR_REL: EXPR_NOT  */
#line 1277 "sintatica.y"
                   {
		yyval.label = yyvsp[0].label;
		yyval.traducao = yyvsp[0].traducao;
	}
#line 2935 "y.tab.c"
    break;

  case 88: /* EXPR_NOT: '!' EXPR_NOT  */
#line 1283 "sintatica.y"
                               {
		stringstream ss;
		ss = veririficarTipo(yyvsp[0].label, "!", "");
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[0].traducao + ss.str();
	}
#line 2946 "y.tab.c"
    break;

  case 89: /* EXPR_NOT: EXPR_ARIT  */
#line 1289 "sintatica.y"
                    {
		yyval.label = yyvsp[0].label;
		yyval.traducao = yyvsp[0].traducao;
	}
#line 2955 "y.tab.c"
    break;

  case 90: /* EXPR_ATOM: '(' EXPR ')'  */
#line 1295 "sintatica.y"
                            {
        yyval.label = yyvsp[-1].label;
        yyval.traducao = yyvsp[-1].traducao;
    }
#line 2964 "y.tab.c"
    break;

  case 91: /* EXPR_ATOM: '-' EXPR_ATOM  */
#line 1299 "sintatica.y"
                                 {
        string tipo = pilha[pilha.size()-1][yyvsp[0].label].tipo;
        if (tipo != "int" && tipo != "float") {
            cout << "Erro: Operador unário '-' só pode ser aplicado a tipos 'int' ou 'float'.\n";
            exit(1);
        }
        string temp_tipo = (tipo == "int") ? "int" : "float";
        string temp = newTemp(temp_tipo);
        stringstream ss;
        ss << qtdTab() << temp << " = -(" << yyvsp[0].traducao << ");\n";
        yyval.label = temp;
        yyval.traducao = yyvsp[0].traducao + ss.str();
    }
#line 2982 "y.tab.c"
    break;

  case 92: /* EXPR_ATOM: TK_NUM  */
#line 1312 "sintatica.y"
             {
        string tipo_num = (yyvsp[0].traducao.find('.') != string::npos) ? "float" : "int";
        string temp = newTemp(tipo_num);
        string num = yyvsp[0].traducao;
        if(tipo_num == "int")  pilha[pilha.size()-1][temp].numero = stoi(num);
        pilha[pilha.size()-1][temp].inicializado = true;
        stringstream ss;
        ss << qtdTab() << temp << " = " << yyvsp[0].traducao << ";\n";
        yyval.label = temp;
        yyval.traducao = ss.str();
    }
#line 2998 "y.tab.c"
    break;

  case 93: /* EXPR_ATOM: TK_ID  */
#line 1323 "sintatica.y"
            {
        if (buscarVariavel(yyvsp[0].label) == -1) { yyerror("Variavel '" + yyvsp[0].label + "' nao declarada"); }
        yyval.label = yyvsp[0].label; 
        yyval.traducao = "";
    }
#line 3008 "y.tab.c"
    break;

  case 94: /* EXPR_ATOM: COVERT_TYPE  */
#line 1328 "sintatica.y"
                  {
        yyval.label = yyvsp[0].label;
        yyval.traducao = yyvsp[0].traducao;
    }
#line 3017 "y.tab.c"
    break;

  case 95: /* EXPR_ATOM: TK_BOOL_TRUE  */
#line 1332 "sintatica.y"
                   {
        string chave_temp_true = newTemp("bool");
        string c_nome_true = pilha[pilha.size()-1][chave_temp_true].endereco_memoria;
        stringstream ss_code;
        ss_code << qtdTab() << c_nome_true << " = 1;\n";
        yyval.label = chave_temp_true;
        yyval.traducao = ss_code.str();
    }
#line 3030 "y.tab.c"
    break;

  case 96: /* EXPR_ATOM: TK_BOOL_FALSE  */
#line 1340 "sintatica.y"
                    {
        string chave_temp_false = newTemp("bool");
        string c_nome_false = pilha[pilha.size()-1][chave_temp_false].endereco_memoria;
        stringstream ss_code;
        ss_code << qtdTab() << c_nome_false << " = 0;\n";
        yyval.label = chave_temp_false;
        yyval.traducao = ss_code.str();
    }
#line 3043 "y.tab.c"
    break;

  case 97: /* EXPR_ATOM: TK_STRING_LITERAL  */
#line 1348 "sintatica.y"
                        {
        string chave_temp_sl = newTemp("string", false, true);
        string c_nome_sl = pilha[pilha.size()-1][chave_temp_sl].endereco_memoria;
        stringstream ss_code;
        ss_code << qtdTab() << c_nome_sl << " = (char*)malloc(" << yyvsp[0].label.length() + 1 << ");\n";
        ss_code << qtdTab() << "strcpy(" << c_nome_sl << ", " << yyvsp[0].traducao << ");\n";
        yyval.label = chave_temp_sl;
        yyval.traducao = ss_code.str();
    }
#line 3057 "y.tab.c"
    break;

  case 98: /* EXPR_ATOM: TK_ID '[' EXPR ']'  */
#line 1357 "sintatica.y"
                         {
        string nome = yyvsp[-3].label;
        string tipo = pilha[buscarVariavel(nome)][nome].tipo;
        string indice = yyvsp[-1].label;

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
        ss << yyvsp[-1].traducao;
        ss << qtdTab() << temp << " = " << pilha[buscarVariavel(nome)][nome].endereco_memoria << "[" << yyvsp[-1].label << "];\n";
        yyval.traducao = ss.str();
        yyval.label = temp;
    }
#line 3094 "y.tab.c"
    break;

  case 99: /* EXPR_ATOM: TK_ID '[' EXPR ']' '[' EXPR ']'  */
#line 1389 "sintatica.y"
                                      {
        string nome = yyvsp[-6].label;
        string linha = yyvsp[-4].label;
        string coluna = yyvsp[-1].label;

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
        ss << yyvsp[-4].traducao; // Código para calcular o índice da linha
        ss << yyvsp[-1].traducao; // Código para calcular o índice da coluna
        
        ss << qtdTab() << temp1 << " = " << pilha[buscarVariavel(linha)][linha].endereco_memoria << " * " << pilha[buscarVariavel(nome)][nome].dimensoes[1] << ";\n";
        ss << qtdTab() << temp2 << " = " << temp1 << " + " << pilha[buscarVariavel(coluna)][coluna].endereco_memoria << ";\n"; 
        ss << qtdTab() << temp2 << " = " << pilha[buscarVariavel(nome)][nome].endereco_memoria << "[" << temp2 << "];\n";

        yyval.traducao = ss.str();
        yyval.label = temp2;
    }
#line 3151 "y.tab.c"
    break;

  case 100: /* EXPR_ATOM: TK_ID TK_PONTO TK_ID  */
#line 1442 "sintatica.y"
                           {
        string nomeVariavel = yyvsp[-2].label;
        string nomeMembro = yyvsp[0].label;
        int idx = buscarVariavel(nomeVariavel);

        // Validações
        if (idx == -1) { yyerror("Variavel '" + nomeVariavel + "' nao declarada."); }
        if (!pilha[idx][nomeVariavel].eh_set) { yyerror("Variavel '" + nomeVariavel + "' nao e um conjunto."); }

        string tipoConjunto = pilha[idx][nomeVariavel].tipo;
        if (!definicoesConjunto[tipoConjunto].count(nomeMembro)) {
            yyerror("Conjunto '" + tipoConjunto + "' nao tem o membro '" + nomeMembro + "'.");
        }

        // Geração de código 3AC
        string tipoMembro = definicoesConjunto[tipoConjunto][nomeMembro];
        string temp = newTemp(tipoMembro); // 1. Cria uma nova variável temporária
        
        string enderecoVar = pilha[idx][nomeVariavel].endereco_memoria;
        string enderecoTemp = pilha.back()[temp].endereco_memoria;

        stringstream ss;
        // 2. Gera a atribuição do membro para a temporária
        ss << qtdTab() << enderecoTemp << " = " << enderecoVar << "." << nomeMembro << ";\n";
        
        yyval.label = temp; // O resultado desta expressão é a nova temporária
        yyval.traducao = ss.str();
    }
#line 3184 "y.tab.c"
    break;

  case 101: /* COVERT_TYPE: TK_TIPO_INT '(' EXPR ')'  */
#line 1472 "sintatica.y"
                             {
        int indice_expr = buscarVariavel(yyvsp[-1].label);
        if (indice_expr == -1) { yyerror("Variavel '" + yyvsp[-1].label + "' nao declarada (em cast para int)."); }
        string tipo_original = pilha[indice_expr][yyvsp[-1].label].tipo;
        string c_nome_original = pilha[indice_expr][yyvsp[-1].label].endereco_memoria;
        if (tipo_original != "int" && tipo_original != "float") {
            cout << "Erro: Conversao de tipo '" << tipo_original << "' para 'int' nao e possivel.\n";
            exit(1);
        }
        string chave_temp_cast = newTemp("int");
        string c_nome_cast = pilha[pilha.size()-1][chave_temp_cast].endereco_memoria;
        stringstream ss_code;
        ss_code << yyvsp[-1].traducao; // Primeiro, o código da expressão original, se houver
        ss_code << qtdTab() << c_nome_cast << " = (int)" << c_nome_original << ";\n";
        yyval.label = chave_temp_cast; // O label é a CHAVE da nova temporária
        yyval.traducao = ss_code.str();
    }
#line 3206 "y.tab.c"
    break;

  case 102: /* COVERT_TYPE: TK_TIPO_FLOAT '(' EXPR ')'  */
#line 1489 "sintatica.y"
                                 {
        int indice_expr = buscarVariavel(yyvsp[-1].label);
        if (indice_expr == -1) { yyerror("Variavel '" + yyvsp[-1].label + "' nao declarada (em cast para float)."); }
        string tipo_original = pilha[indice_expr][yyvsp[-1].label].tipo;
        string c_nome_original = pilha[indice_expr][yyvsp[-1].label].endereco_memoria;

        if (tipo_original != "int" && tipo_original != "float") {
            cout << "Erro: Conversao de tipo '" << tipo_original << "' para 'float' nao e possivel.\n";
            exit(1);
        }
        string chave_temp_cast = newTemp("float");
        string c_nome_cast = pilha[pilha.size()-1][chave_temp_cast].endereco_memoria;
        stringstream ss_code;
        ss_code << yyvsp[-1].traducao;
        ss_code << qtdTab() << c_nome_cast << " = (float)" << c_nome_original << ";\n"; 
        yyval.label = chave_temp_cast;
        yyval.traducao = ss_code.str();
    }
#line 3229 "y.tab.c"
    break;


#line 3233 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1508 "sintatica.y"


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
                if (info.eh_set) { // <-- ADICIONE ESTA CONDIÇÃO
                    ss << qtdTab() << "struct " << info.tipo << " " << info.endereco_memoria << ";\t //" << nome << "\n";
            } else if (info.num_dimensoes == 0)
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
