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

#line 157 "y.tab.c"

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
    TK_IGUAL = 265,                /* TK_IGUAL  */
    TK_DIFERENTE = 266,            /* TK_DIFERENTE  */
    TK_MAIOR_IGUAL = 267,          /* TK_MAIOR_IGUAL  */
    TK_MENOR_IGUAL = 268,          /* TK_MENOR_IGUAL  */
    TK_AND = 269,                  /* TK_AND  */
    TK_OR = 270,                   /* TK_OR  */
    TK_CHAR = 271,                 /* TK_CHAR  */
    TK_BOOL_TRUE = 272,            /* TK_BOOL_TRUE  */
    TK_BOOL_FALSE = 273,           /* TK_BOOL_FALSE  */
    TK_TIPO_STRING = 274,          /* TK_TIPO_STRING  */
    TK_STRING_LITERAL = 275,       /* TK_STRING_LITERAL  */
    TK_IF = 276,                   /* TK_IF  */
    TK_ELSE = 277,                 /* TK_ELSE  */
    TK_ELSE_IF = 278,              /* TK_ELSE_IF  */
    TK_WHILE = 279,                /* TK_WHILE  */
    TK_FOR = 280,                  /* TK_FOR  */
    TK_DO = 281,                   /* TK_DO  */
    TK_BREAK = 282,                /* TK_BREAK  */
    TK_CONTINUE = 283,             /* TK_CONTINUE  */
    TK_ESCREVA = 284,              /* TK_ESCREVA  */
    TK_LEIA = 285,                 /* TK_LEIA  */
    TK_SWITCH = 286,               /* TK_SWITCH  */
    TK_CASE = 287,                 /* TK_CASE  */
    TK_DEFAULT = 288,              /* TK_DEFAULT  */
    TK_QUICKSORT = 289,            /* TK_QUICKSORT  */
    TK_CRIAR_VETOR = 290,          /* TK_CRIAR_VETOR  */
    TK_IMPRIMIR_VETOR = 291,       /* TK_IMPRIMIR_VETOR  */
    UMINUS = 292,                  /* UMINUS  */
    LOWER_THAN_ELSE = 293          /* LOWER_THAN_ELSE  */
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
#define TK_IGUAL 265
#define TK_DIFERENTE 266
#define TK_MAIOR_IGUAL 267
#define TK_MENOR_IGUAL 268
#define TK_AND 269
#define TK_OR 270
#define TK_CHAR 271
#define TK_BOOL_TRUE 272
#define TK_BOOL_FALSE 273
#define TK_TIPO_STRING 274
#define TK_STRING_LITERAL 275
#define TK_IF 276
#define TK_ELSE 277
#define TK_ELSE_IF 278
#define TK_WHILE 279
#define TK_FOR 280
#define TK_DO 281
#define TK_BREAK 282
#define TK_CONTINUE 283
#define TK_ESCREVA 284
#define TK_LEIA 285
#define TK_SWITCH 286
#define TK_CASE 287
#define TK_DEFAULT 288
#define TK_QUICKSORT 289
#define TK_CRIAR_VETOR 290
#define TK_IMPRIMIR_VETOR 291
#define UMINUS 292
#define LOWER_THAN_ELSE 293

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
  YYSYMBOL_TK_IGUAL = 10,                  /* TK_IGUAL  */
  YYSYMBOL_TK_DIFERENTE = 11,              /* TK_DIFERENTE  */
  YYSYMBOL_TK_MAIOR_IGUAL = 12,            /* TK_MAIOR_IGUAL  */
  YYSYMBOL_TK_MENOR_IGUAL = 13,            /* TK_MENOR_IGUAL  */
  YYSYMBOL_TK_AND = 14,                    /* TK_AND  */
  YYSYMBOL_TK_OR = 15,                     /* TK_OR  */
  YYSYMBOL_TK_CHAR = 16,                   /* TK_CHAR  */
  YYSYMBOL_TK_BOOL_TRUE = 17,              /* TK_BOOL_TRUE  */
  YYSYMBOL_TK_BOOL_FALSE = 18,             /* TK_BOOL_FALSE  */
  YYSYMBOL_TK_TIPO_STRING = 19,            /* TK_TIPO_STRING  */
  YYSYMBOL_TK_STRING_LITERAL = 20,         /* TK_STRING_LITERAL  */
  YYSYMBOL_TK_IF = 21,                     /* TK_IF  */
  YYSYMBOL_TK_ELSE = 22,                   /* TK_ELSE  */
  YYSYMBOL_TK_ELSE_IF = 23,                /* TK_ELSE_IF  */
  YYSYMBOL_TK_WHILE = 24,                  /* TK_WHILE  */
  YYSYMBOL_TK_FOR = 25,                    /* TK_FOR  */
  YYSYMBOL_TK_DO = 26,                     /* TK_DO  */
  YYSYMBOL_TK_BREAK = 27,                  /* TK_BREAK  */
  YYSYMBOL_TK_CONTINUE = 28,               /* TK_CONTINUE  */
  YYSYMBOL_TK_ESCREVA = 29,                /* TK_ESCREVA  */
  YYSYMBOL_TK_LEIA = 30,                   /* TK_LEIA  */
  YYSYMBOL_TK_SWITCH = 31,                 /* TK_SWITCH  */
  YYSYMBOL_TK_CASE = 32,                   /* TK_CASE  */
  YYSYMBOL_TK_DEFAULT = 33,                /* TK_DEFAULT  */
  YYSYMBOL_TK_QUICKSORT = 34,              /* TK_QUICKSORT  */
  YYSYMBOL_TK_CRIAR_VETOR = 35,            /* TK_CRIAR_VETOR  */
  YYSYMBOL_TK_IMPRIMIR_VETOR = 36,         /* TK_IMPRIMIR_VETOR  */
  YYSYMBOL_37_ = 37,                       /* '<'  */
  YYSYMBOL_38_ = 38,                       /* '>'  */
  YYSYMBOL_39_ = 39,                       /* '+'  */
  YYSYMBOL_40_ = 40,                       /* '-'  */
  YYSYMBOL_41_ = 41,                       /* '*'  */
  YYSYMBOL_42_ = 42,                       /* '/'  */
  YYSYMBOL_UMINUS = 43,                    /* UMINUS  */
  YYSYMBOL_44_ = 44,                       /* '!'  */
  YYSYMBOL_45_ = 45,                       /* '('  */
  YYSYMBOL_46_ = 46,                       /* ')'  */
  YYSYMBOL_LOWER_THAN_ELSE = 47,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_48_ = 48,                       /* '{'  */
  YYSYMBOL_49_ = 49,                       /* '}'  */
  YYSYMBOL_50_ = 50,                       /* ';'  */
  YYSYMBOL_51_ = 51,                       /* ','  */
  YYSYMBOL_52_ = 52,                       /* '='  */
  YYSYMBOL_53_ = 53,                       /* ':'  */
  YYSYMBOL_54_ = 54,                       /* '%'  */
  YYSYMBOL_YYACCEPT = 55,                  /* $accept  */
  YYSYMBOL_S = 56,                         /* S  */
  YYSYMBOL_INICIO = 57,                    /* INICIO  */
  YYSYMBOL_MAIN = 58,                      /* MAIN  */
  YYSYMBOL_BLOCO = 59,                     /* BLOCO  */
  YYSYMBOL_60_1 = 60,                      /* $@1  */
  YYSYMBOL_COMANDOS = 61,                  /* COMANDOS  */
  YYSYMBOL_COMANDO = 62,                   /* COMANDO  */
  YYSYMBOL_63_2 = 63,                      /* $@2  */
  YYSYMBOL_COMANDO_SAIDA = 64,             /* COMANDO_SAIDA  */
  YYSYMBOL_LISTA_EXPRESSOES = 65,          /* LISTA_EXPRESSOES  */
  YYSYMBOL_COMANDO_ENTRADA = 66,           /* COMANDO_ENTRADA  */
  YYSYMBOL_LISTA_VARIAVEIS = 67,           /* LISTA_VARIAVEIS  */
  YYSYMBOL_DECLARACAO = 68,                /* DECLARACAO  */
  YYSYMBOL_TIPO = 69,                      /* TIPO  */
  YYSYMBOL_DECLAR_VAR = 70,                /* DECLAR_VAR  */
  YYSYMBOL_ATRIB = 71,                     /* ATRIB  */
  YYSYMBOL_LOOP = 72,                      /* LOOP  */
  YYSYMBOL_73_3 = 73,                      /* $@3  */
  YYSYMBOL_74_4 = 74,                      /* $@4  */
  YYSYMBOL_75_5 = 75,                      /* $@5  */
  YYSYMBOL_COND_IF = 76,                   /* COND_IF  */
  YYSYMBOL_COND_ELSE = 77,                 /* COND_ELSE  */
  YYSYMBOL_SWITCH_STMT = 78,               /* SWITCH_STMT  */
  YYSYMBOL_79_6 = 79,                      /* $@6  */
  YYSYMBOL_80_7 = 80,                      /* $@7  */
  YYSYMBOL_SIMPLE_CASE_LIST = 81,          /* SIMPLE_CASE_LIST  */
  YYSYMBOL_SIMPLE_CASE = 82,               /* SIMPLE_CASE  */
  YYSYMBOL_SIMPLE_DEFAULT = 83,            /* SIMPLE_DEFAULT  */
  YYSYMBOL_EXPR = 84,                      /* EXPR  */
  YYSYMBOL_EXPR_ARIT = 85,                 /* EXPR_ARIT  */
  YYSYMBOL_EXPR_TERM = 86,                 /* EXPR_TERM  */
  YYSYMBOL_EXPR_LOG = 87,                  /* EXPR_LOG  */
  YYSYMBOL_EXPR_REL = 88,                  /* EXPR_REL  */
  YYSYMBOL_EXPR_NOT = 89,                  /* EXPR_NOT  */
  YYSYMBOL_EXPR_ATOM = 90,                 /* EXPR_ATOM  */
  YYSYMBOL_COVERT_TYPE = 91,               /* COVERT_TYPE  */
  YYSYMBOL_QUICKSORT_CMD = 92              /* QUICKSORT_CMD  */
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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   227

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  90
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  198

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


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
       2,     2,     2,    44,     2,     2,     2,    54,     2,     2,
      45,    46,    41,    39,    51,    40,     2,    42,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    53,    50,
      37,    52,    38,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,     2,    49,     2,     2,     2,     2,
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
      35,    36,    43,    47
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   116,   116,   202,   215,   222,   237,   237,   281,   284,
     290,   291,   292,   293,   294,   295,   295,   296,   297,   298,
     299,   303,   310,   325,   343,   349,   370,   398,   406,   412,
     413,   414,   415,   416,   420,   424,   430,   438,   450,   450,
     497,   497,   543,   543,   604,   613,   632,   682,   733,   765,
     771,   775,   771,   816,   819,   822,   828,   850,   860,   866,
     874,   883,   889,   897,   905,   914,   922,   928,   934,   940,
     946,   952,   958,   964,   970,   976,   982,   988,   994,   998,
    1028,  1047,  1056,  1060,  1078,  1096,  1120,  1128,  1139,  1156,
    1171
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
  "TK_TIPO_BOOL", "TK_IGUAL", "TK_DIFERENTE", "TK_MAIOR_IGUAL",
  "TK_MENOR_IGUAL", "TK_AND", "TK_OR", "TK_CHAR", "TK_BOOL_TRUE",
  "TK_BOOL_FALSE", "TK_TIPO_STRING", "TK_STRING_LITERAL", "TK_IF",
  "TK_ELSE", "TK_ELSE_IF", "TK_WHILE", "TK_FOR", "TK_DO", "TK_BREAK",
  "TK_CONTINUE", "TK_ESCREVA", "TK_LEIA", "TK_SWITCH", "TK_CASE",
  "TK_DEFAULT", "TK_QUICKSORT", "TK_CRIAR_VETOR", "TK_IMPRIMIR_VETOR",
  "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "UMINUS", "'!'", "'('", "')'",
  "LOWER_THAN_ELSE", "'{'", "'}'", "';'", "','", "'='", "':'", "'%'",
  "$accept", "S", "INICIO", "MAIN", "BLOCO", "$@1", "COMANDOS", "COMANDO",
  "$@2", "COMANDO_SAIDA", "LISTA_EXPRESSOES", "COMANDO_ENTRADA",
  "LISTA_VARIAVEIS", "DECLARACAO", "TIPO", "DECLAR_VAR", "ATRIB", "LOOP",
  "$@3", "$@4", "$@5", "COND_IF", "COND_ELSE", "SWITCH_STMT", "$@6", "$@7",
  "SIMPLE_CASE_LIST", "SIMPLE_CASE", "SIMPLE_DEFAULT", "EXPR", "EXPR_ARIT",
  "EXPR_TERM", "EXPR_LOG", "EXPR_REL", "EXPR_NOT", "EXPR_ATOM",
  "COVERT_TYPE", "QUICKSORT_CMD", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-86)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-51)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      91,   -86,   -86,   -86,   -86,   -86,     4,   -86,    37,    15,
      -1,   -86,    19,   -86,     5,    91,    20,   109,   -86,   -86,
     -86,   -86,    27,    28,   -86,   -86,   -86,   -86,   159,   130,
     130,   -86,   -24,     9,    21,    94,   -86,   -86,   -86,   -86,
      17,   130,   130,   -86,   -86,    36,   159,   159,   159,   159,
     159,   130,   130,   130,   130,   130,   130,   130,   130,     3,
      41,    43,   -86,     9,     9,   -86,   -86,   -86,    94,    94,
     170,   170,   -86,   -86,   -86,   -86,    31,    27,    28,    42,
      51,    48,    64,    66,    71,    72,   -86,    74,    50,    99,
      78,    80,    90,    95,   -86,    97,   115,   119,   -86,   120,
      96,   102,   -86,   -86,   130,   -86,   -86,   130,   151,   153,
     155,   156,   -86,   -86,   116,   -86,   -86,   -86,   -86,   -86,
     121,   -86,   123,   124,   -86,   -86,   -86,   -41,   -86,   -86,
     -33,   122,   127,   141,   130,   130,   147,    91,   130,   -86,
     130,   -86,   189,   191,   192,   193,   152,   154,   157,   160,
     163,   -86,   -86,   165,   166,   167,   -86,   -86,   130,   130,
     -86,   -86,   -86,   -86,   174,   -86,   168,   169,   158,   171,
     179,   172,   199,    13,   130,   -86,   -86,    31,   175,   202,
     162,   176,    13,   -86,   177,   -86,   -86,   164,     3,   -86,
     -86,   -86,   -86,    50,   -86,   174,   -86,   -86
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      28,    29,    30,    31,    32,    33,     0,     2,     4,     0,
       0,     1,     0,     3,    34,    28,     0,     0,    27,     6,
      80,    81,     0,     0,    36,    83,    84,    85,     0,     0,
       0,    35,    77,    61,    58,    68,    75,    65,    82,     5,
       0,     0,     0,    79,    76,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     6,
       0,     0,    78,    59,    60,    62,    63,    64,    66,    67,
      69,    70,    73,    74,    72,    71,    81,    29,    30,     0,
       0,     0,     0,     0,     0,     0,    13,     0,     9,     0,
       0,     0,     0,     0,    14,     0,     0,     0,    19,     0,
       0,     0,    86,    87,     0,    44,    45,     0,     0,     0,
       0,     0,     7,     8,     0,    16,    17,    18,    10,    11,
       0,     6,     0,     0,    12,    20,    37,     0,    22,    25,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    21,
       0,    24,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    23,    26,     0,     0,     0,     6,     6,     0,     0,
      51,    88,    89,    90,    49,    39,     0,     0,     0,     0,
      46,     0,     0,    55,     0,     6,    41,     0,     0,     0,
       0,     0,    55,    54,     0,    47,     6,     0,     6,    52,
      53,     6,    43,     9,    57,    49,    56,    48
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -86,   -86,   -86,   -86,   -19,   -86,   -85,   -86,   -86,   -86,
     -86,   -86,   -86,   203,   -86,     2,    52,   -86,   -86,   -86,
     -86,   -86,    25,   -86,   -86,   -86,    44,   -86,   -86,   -16,
     -86,    -5,   -86,   133,   198,    12,   -86,   -86
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     6,     7,    13,    86,    40,    87,    88,    89,    90,
     127,    91,   130,     8,     9,    92,    93,    94,    95,    96,
      97,   115,   170,    98,    99,   168,   181,   182,   183,   100,
      32,    33,    34,    35,    36,    37,    38,   101
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      39,    31,    10,   113,    11,   139,    20,    76,    77,    78,
     140,     3,     4,   141,    45,    46,    47,    10,   142,    14,
      25,    26,     5,    27,   -15,    60,    61,   -38,   -42,   -40,
      79,    80,    81,    82,   -50,    51,    52,    83,    84,    85,
      43,    63,    64,    28,    12,   179,   180,    29,    30,    15,
      48,    49,    -9,    20,    76,    77,    78,    17,     3,     4,
      65,    66,    67,    50,    16,    59,    19,    25,    26,     5,
      27,   -15,    41,    42,   -38,   -42,   -40,    79,    80,    81,
      82,   -50,    62,   104,    83,    84,    85,   102,   126,   103,
      28,   128,   105,   107,    29,    30,     1,     2,    -6,     3,
       4,   106,   136,   194,    53,    54,    55,    56,   196,   108,
       5,   109,    20,    21,    22,    23,   110,   111,   146,   147,
     114,   120,   150,   112,   151,    24,    25,    26,   116,    27,
     117,    57,    58,    20,    21,    22,    23,   164,   165,   149,
     118,   121,   166,   167,   122,   119,   124,    25,    26,    28,
      27,   123,   125,    29,    30,   129,   185,   131,   184,   132,
     133,   134,    20,    21,    22,    23,   135,   192,   137,   138,
      28,   148,   195,   143,    29,    30,    25,    26,   144,    27,
     -51,   -51,    55,    56,    68,    69,    70,    71,    72,    73,
      74,    75,   145,   152,   153,   154,   155,   169,   156,    28,
     157,   175,   158,   177,    30,   187,   173,    57,    58,   160,
     159,   161,   162,   163,   171,   188,   174,   193,    18,   172,
     197,   186,   176,   191,   178,   189,   190,    44
};

static const yytype_uint8 yycheck[] =
{
      19,    17,     0,    88,     0,    46,     3,     4,     5,     6,
      51,     8,     9,    46,    30,    39,    40,    15,    51,     4,
      17,    18,    19,    20,    21,    41,    42,    24,    25,    26,
      27,    28,    29,    30,    31,    14,    15,    34,    35,    36,
      28,    46,    47,    40,     7,    32,    33,    44,    45,    50,
      41,    42,    49,     3,     4,     5,     6,    52,     8,     9,
      48,    49,    50,    54,    45,    48,    46,    17,    18,    19,
      20,    21,    45,    45,    24,    25,    26,    27,    28,    29,
      30,    31,    46,    52,    34,    35,    36,    46,   104,    46,
      40,   107,    50,    45,    44,    45,     5,     6,    48,     8,
       9,    50,   121,   188,    10,    11,    12,    13,   193,    45,
      19,    45,     3,     4,     5,     6,    45,    45,   134,   135,
      21,    24,   138,    49,   140,    16,    17,    18,    50,    20,
      50,    37,    38,     3,     4,     5,     6,   156,   157,   137,
      50,    26,   158,   159,    25,    50,    50,    17,    18,    40,
      20,    31,    50,    44,    45,     4,   175,     4,   174,     4,
       4,    45,     3,     4,     5,     6,    45,   186,    45,    45,
      40,    24,   191,    51,    44,    45,    17,    18,    51,    20,
      10,    11,    12,    13,    51,    52,    53,    54,    55,    56,
      57,    58,    51,     4,     3,     3,     3,    23,    46,    40,
      46,    22,    45,     4,    45,     3,    48,    37,    38,    46,
      50,    46,    46,    46,    46,    53,    45,    53,    15,    50,
     195,    46,    50,    46,   172,    49,   182,    29
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     5,     6,     8,     9,    19,    56,    57,    68,    69,
      70,     0,     7,    58,     4,    50,    45,    52,    68,    46,
       3,     4,     5,     6,    16,    17,    18,    20,    40,    44,
      45,    84,    85,    86,    87,    88,    89,    90,    91,    59,
      60,    45,    45,    90,    89,    84,    39,    40,    41,    42,
      54,    14,    15,    10,    11,    12,    13,    37,    38,    48,
      84,    84,    46,    86,    86,    90,    90,    90,    88,    88,
      88,    88,    88,    88,    88,    88,     4,     5,     6,    27,
      28,    29,    30,    34,    35,    36,    59,    61,    62,    63,
      64,    66,    70,    71,    72,    73,    74,    75,    78,    79,
      84,    92,    46,    46,    52,    50,    50,    45,    45,    45,
      45,    45,    49,    61,    21,    76,    50,    50,    50,    50,
      24,    26,    25,    31,    50,    50,    84,    65,    84,     4,
      67,     4,     4,     4,    45,    45,    59,    45,    45,    46,
      51,    46,    51,    51,    51,    51,    84,    84,    24,    70,
      84,    84,     4,     3,     3,     3,    46,    46,    45,    50,
      46,    46,    46,    46,    59,    59,    84,    84,    80,    23,
      77,    46,    50,    48,    45,    22,    50,     4,    71,    32,
      33,    81,    82,    83,    84,    59,    46,     3,    53,    49,
      81,    46,    59,    53,    61,    59,    61,    77
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    55,    56,    57,    57,    58,    60,    59,    61,    61,
      62,    62,    62,    62,    62,    63,    62,    62,    62,    62,
      62,    64,    65,    65,    66,    67,    67,    68,    68,    69,
      69,    69,    69,    69,    70,    70,    70,    71,    73,    72,
      74,    72,    75,    72,    72,    72,    76,    76,    77,    77,
      79,    80,    78,    81,    81,    81,    82,    83,    84,    85,
      85,    85,    86,    86,    86,    86,    87,    87,    87,    88,
      88,    88,    88,    88,    88,    88,    89,    89,    90,    90,
      90,    90,    90,    90,    90,    90,    91,    91,    92,    92,
      92
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     4,     0,     4,     2,     0,
       2,     2,     2,     1,     1,     0,     2,     2,     2,     1,
       2,     4,     1,     3,     4,     1,     3,     3,     0,     1,
       1,     1,     1,     1,     2,     4,     4,     3,     0,     6,
       0,     8,     0,    10,     2,     2,     6,     8,     6,     0,
       0,     0,     9,     2,     1,     0,     4,     3,     1,     3,
       3,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     3,     3,     1,     2,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     4,     4,     6,     6,
       6
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
#line 116 "sintatica.y"
           {
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
        cout << yyvsp[0].traducao;
    }
#line 1573 "y.tab.c"
    break;

  case 3: /* INICIO: DECLARACAO MAIN  */
#line 203 "sintatica.y"
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
#line 1590 "y.tab.c"
    break;

  case 4: /* INICIO: DECLARACAO  */
#line 216 "sintatica.y"
        {
		yyval.traducao = yyvsp[0].traducao;
	}
#line 1598 "y.tab.c"
    break;

  case 5: /* MAIN: TK_MAIN '(' ')' BLOCO  */
#line 222 "sintatica.y"
                               {

		stringstream ss;
		ss << "int main(void)\n";

		ss << "{\n";

		ss << yyvsp[0].traducao;

		ss << "}\n\n";

		yyval.traducao = ss.str();
	  }
#line 1616 "y.tab.c"
    break;

  case 6: /* $@1: %empty  */
#line 237 "sintatica.y"
       { criarPilha(); }
#line 1622 "y.tab.c"
    break;

  case 7: /* BLOCO: $@1 '{' COMANDOS '}'  */
#line 237 "sintatica.y"
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
#line 1668 "y.tab.c"
    break;

  case 8: /* COMANDOS: COMANDO COMANDOS  */
#line 281 "sintatica.y"
                         {
		yyval.traducao = yyvsp[-1].traducao + yyvsp[0].traducao;
	}
#line 1676 "y.tab.c"
    break;

  case 9: /* COMANDOS: %empty  */
#line 284 "sintatica.y"
                      {
		yyval.traducao = "";
	}
#line 1684 "y.tab.c"
    break;

  case 10: /* COMANDO: DECLAR_VAR ';'  */
#line 290 "sintatica.y"
                        { yyval.traducao = yyvsp[-1].traducao; }
#line 1690 "y.tab.c"
    break;

  case 11: /* COMANDO: ATRIB ';'  */
#line 291 "sintatica.y"
                        { yyval.traducao = yyvsp[-1].traducao; }
#line 1696 "y.tab.c"
    break;

  case 12: /* COMANDO: EXPR ';'  */
#line 292 "sintatica.y"
                        { yyval.traducao = yyvsp[-1].traducao; }
#line 1702 "y.tab.c"
    break;

  case 13: /* COMANDO: BLOCO  */
#line 293 "sintatica.y"
                                { yyval.traducao = yyvsp[0].traducao; }
#line 1708 "y.tab.c"
    break;

  case 14: /* COMANDO: LOOP  */
#line 294 "sintatica.y"
                        { yyval.traducao = yyvsp[0].traducao; }
#line 1714 "y.tab.c"
    break;

  case 15: /* $@2: %empty  */
#line 295 "sintatica.y"
          { criarPilha(); }
#line 1720 "y.tab.c"
    break;

  case 16: /* COMANDO: $@2 COND_IF  */
#line 295 "sintatica.y"
                                                { yyval.traducao = yyvsp[0].traducao; }
#line 1726 "y.tab.c"
    break;

  case 17: /* COMANDO: COMANDO_SAIDA ';'  */
#line 296 "sintatica.y"
                              { yyval.traducao = yyvsp[-1].traducao; }
#line 1732 "y.tab.c"
    break;

  case 18: /* COMANDO: COMANDO_ENTRADA ';'  */
#line 297 "sintatica.y"
                          { yyval.traducao = yyvsp[-1].traducao; }
#line 1738 "y.tab.c"
    break;

  case 19: /* COMANDO: SWITCH_STMT  */
#line 298 "sintatica.y"
                      { yyval.traducao = yyvsp[0].traducao; }
#line 1744 "y.tab.c"
    break;

  case 20: /* COMANDO: QUICKSORT_CMD ';'  */
#line 299 "sintatica.y"
                            { yyval.traducao = yyvsp[-1].traducao; }
#line 1750 "y.tab.c"
    break;

  case 21: /* COMANDO_SAIDA: TK_ESCREVA '(' LISTA_EXPRESSOES ')'  */
#line 304 "sintatica.y"
        {
        yyval.traducao = yyvsp[-1].traducao + qtdTab() + "printf(\"\\n\");\n";
    }
#line 1758 "y.tab.c"
    break;

  case 22: /* LISTA_EXPRESSOES: EXPR  */
#line 310 "sintatica.y"
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
#line 1777 "y.tab.c"
    break;

  case 23: /* LISTA_EXPRESSOES: LISTA_EXPRESSOES ',' EXPR  */
#line 325 "sintatica.y"
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
#line 1797 "y.tab.c"
    break;

  case 24: /* COMANDO_ENTRADA: TK_LEIA '(' LISTA_VARIAVEIS ')'  */
#line 343 "sintatica.y"
                                    {
        yyval.traducao = yyvsp[-1].traducao;
    }
#line 1805 "y.tab.c"
    break;

  case 25: /* LISTA_VARIAVEIS: TK_ID  */
#line 349 "sintatica.y"
          {
        int idx = buscarVariavel(yyvsp[0].label);
        if (idx == -1) { yyerror("Variavel '" + yyvsp[0].label + "' nao declarada para 'leia'."); }

        string tipo = pilha[idx][yyvsp[0].label].tipo;
        string c_nome = pilha[idx][yyvsp[0].label].endereco_memoria;
        
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
        yyval.traducao = ss_code.str();
    }
#line 1831 "y.tab.c"
    break;

  case 26: /* LISTA_VARIAVEIS: LISTA_VARIAVEIS ',' TK_ID  */
#line 370 "sintatica.y"
                                {

        // A lógica é idêntica para o caso recursivo
        int idx = buscarVariavel(yyvsp[0].label);
        if (idx == -1) { yyerror("Variavel '" + yyvsp[0].label + "' nao declarada para 'leia'."); }

        string tipo = pilha[idx][yyvsp[0].label].tipo;
        string c_nome = pilha[idx][yyvsp[0].label].endereco_memoria;
        
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
        
        yyval.traducao = yyvsp[-2].traducao + ss_code.str();
    }
#line 1861 "y.tab.c"
    break;

  case 27: /* DECLARACAO: DECLAR_VAR ';' DECLARACAO  */
#line 399 "sintatica.y"
          {
		if(!yyvsp[-2].traducao.empty()) {
			atribuicaoGlobal = true; // Marca que há atribuição global
		}
        yyval.traducao = yyvsp[-2].traducao;
      }
#line 1872 "y.tab.c"
    break;

  case 28: /* DECLARACAO: %empty  */
#line 406 "sintatica.y"
          {
		yyval.traducao = "";
	  }
#line 1880 "y.tab.c"
    break;

  case 29: /* TIPO: TK_TIPO_INT  */
#line 412 "sintatica.y"
                    { yyval.label = "int"; }
#line 1886 "y.tab.c"
    break;

  case 30: /* TIPO: TK_TIPO_FLOAT  */
#line 413 "sintatica.y"
                    { yyval.label = "float"; }
#line 1892 "y.tab.c"
    break;

  case 31: /* TIPO: TK_TIPO_CHAR  */
#line 414 "sintatica.y"
                    { yyval.label = "char"; }
#line 1898 "y.tab.c"
    break;

  case 32: /* TIPO: TK_TIPO_BOOL  */
#line 415 "sintatica.y"
                    { yyval.label = "bool"; }
#line 1904 "y.tab.c"
    break;

  case 33: /* TIPO: TK_TIPO_STRING  */
#line 416 "sintatica.y"
                         { yyval.label = "string"; }
#line 1910 "y.tab.c"
    break;

  case 34: /* DECLAR_VAR: TIPO TK_ID  */
#line 420 "sintatica.y"
                 {
        adicionaVar(yyvsp[0].label, yyvsp[-1].label);
        yyval.traducao = "";
      }
#line 1919 "y.tab.c"
    break;

  case 35: /* DECLAR_VAR: TIPO TK_ID '=' EXPR  */
#line 424 "sintatica.y"
                          {
        adicionaVar(yyvsp[-2].label, yyvsp[-3].label);
        stringstream ss;
		ss = veririficarTipo(yyvsp[-2].label, "=", yyvsp[0].label);
        yyval.traducao = yyvsp[0].traducao + ss.str();
      }
#line 1930 "y.tab.c"
    break;

  case 36: /* DECLAR_VAR: TIPO TK_ID '=' TK_CHAR  */
#line 430 "sintatica.y"
                             {
        adicionaVar(yyvsp[-2].label, yyvsp[-3].label);
        stringstream ss;
        ss << qtdTab() << pilha[pilha.size()-1][yyvsp[-2].label].endereco_memoria << " = " << yyvsp[0].label << ";\n";
        yyval.traducao = ss.str();
      }
#line 1941 "y.tab.c"
    break;

  case 37: /* ATRIB: TK_ID '=' EXPR  */
#line 438 "sintatica.y"
                      {
	if (buscarVariavel(yyvsp[-2].label) == -1) {
		cout << "Erro: Variável " << yyvsp[-2].label << " não declarada.\n";
		exit(1);
	}
        stringstream ss;
		ss = veririficarTipo(yyvsp[-2].label, "=", yyvsp[0].label);
        yyval.traducao = yyvsp[0].traducao + ss.str();
}
#line 1955 "y.tab.c"
    break;

  case 38: /* $@3: %empty  */
#line 450 "sintatica.y"
         { criarPilha(); addPilhaLaco("EndWhile" + to_string(defgoto), "BeginWhile" + to_string(defgoto));}
#line 1961 "y.tab.c"
    break;

  case 39: /* LOOP: $@3 TK_WHILE '(' EXPR ')' BLOCO  */
#line 450 "sintatica.y"
                                                                                                                                        {
		//Verificações
		if (buscarVariavel(yyvsp[-2].label) == -1) {
			yyerror("Variável '" + yyvsp[-2].label + "' não declarada no loop while.");
		}
		if (pilha[buscarVariavel(yyvsp[-2].label)][yyvsp[-2].label].tipo != "bool") {
			yyerror("Condição do loop while deve ser do tipo booleano, mas é '" + pilha[buscarVariavel(yyvsp[-3].label)][yyvsp[-3].label].tipo + "'.");
		}

		// Geração de código		
		stringstream ss;
		string temp = pilha[buscarVariavel(yyvsp[-2].label)][yyvsp[-2].label].endereco_memoria; // Endereço de memória da variável condicional
		string rotuloBreak = pilhaDeRotulosDeLaços.back().rotuloBreak;
		string rotuloContinue = pilhaDeRotulosDeLaços.back().rotuloContinue;

		ss << "\n";

		ss << qtdTab(-1) << "{\n"; // Abre a pilha de variáveis para o loop

		ss << fecharPilha().str(); // Fecha a pilha de variáveis antes do loop

		ss << yyvsp[-2].traducao; // Traduz a expressão condicional

		ss << "\n";

		ss << qtdTab(1) << rotuloContinue << ":\n";

		ss << qtdTab(1) << "if (!" << temp << ") goto "<< rotuloBreak << ";";

		ss << yyvsp[0].traducao; // Traduz o bloco do loop

		ss << "\n"; // Adiciona uma nova linha para melhor legibilidade

		ss << yyvsp[-2].traducao; // Reavalia a condição do loop

		ss << qtdTab(1) << "goto " << rotuloContinue << ";\n";

		ss << qtdTab(1) << rotuloBreak << ":\n";

		ss << qtdTab() << "}\n"; // Fecha a pilha de variáveis do loop

		// tira o último rótulo de laços da pilha
		pilhaDeRotulosDeLaços.pop_back();

		defgoto++; // Incrementa o contador de blocos de loop
		yyval.traducao = ss.str();
	}
#line 2013 "y.tab.c"
    break;

  case 40: /* $@4: %empty  */
#line 497 "sintatica.y"
          { criarPilha(); addPilhaLaco("EndDoWhile" + to_string(defgoto), "BenginDoWhile" + to_string(defgoto)); }
#line 2019 "y.tab.c"
    break;

  case 41: /* LOOP: $@4 TK_DO BLOCO TK_WHILE '(' EXPR ')' ';'  */
#line 497 "sintatica.y"
                                                                                                                                                         {

		// Verificações
		if (buscarVariavel(yyvsp[-2].label) == -1) {
			yyerror("Variável '" + yyvsp[-2].label + "' não declarada no loop do-while.");
		}
		if (pilha[buscarVariavel(yyvsp[-2].label)][yyvsp[-2].label].tipo != "bool") {
			yyerror("Condição do loop do-while deve ser do tipo booleano, mas é '" + pilha[buscarVariavel(yyvsp[-3].label)][yyvsp[-3].label].tipo + "'.");
		}

		// Geração de código
		stringstream ss;
		string temp = pilha[buscarVariavel(yyvsp[-2].label)][yyvsp[-2].label].endereco_memoria; // Endereço de memória da variável condicional
		string rotuloBreak = pilhaDeRotulosDeLaços.back().rotuloBreak;
		string rotuloContinue = pilhaDeRotulosDeLaços.back().rotuloContinue;


		ss << "\n";

		ss << qtdTab(-1) << "{\n"; // Abre a pilha de variáveis para o loop

		ss << fecharPilha().str(); // Fecha a pilha de variáveis antes do loop

		ss << "\n";

		ss << qtdTab(1) << rotuloContinue << ":\n";

		ss << yyvsp[-5].traducao; // Traduz o bloco do loop

		ss << "\n";

		ss << yyvsp[-2].traducao; // Traduz a expressão condicional 

		ss << qtdTab(1) << "if (" << temp << ") goto " << rotuloContinue << ";\n";
		
		ss << qtdTab(1) << rotuloBreak << ":\n";
		
		ss << qtdTab() << "}\n"; // Fecha a pilha de variáveis do loop
		
		ss << "\n";

		pilhaDeRotulosDeLaços.pop_back();
		
		defgoto++; // Incrementa o contador de blocos de loop
		yyval.traducao = ss.str();
	}
#line 2070 "y.tab.c"
    break;

  case 42: /* $@5: %empty  */
#line 543 "sintatica.y"
          { criarPilha(); addPilhaLaco("EndFor" + to_string(defgoto), "MidFor" + to_string(defgoto)); }
#line 2076 "y.tab.c"
    break;

  case 43: /* LOOP: $@5 TK_FOR '(' DECLAR_VAR ';' EXPR ';' ATRIB ')' BLOCO  */
#line 543 "sintatica.y"
                                                                                                                                                           {

		// Verificações
		if(yyvsp[-6].traducao.empty()) {
			cout << "Erro: A variável de controle do loop Precisa ser inicializada.\n";
			exit(1);
		}
		if (buscarVariavel(yyvsp[-4].label) == -1) {
			yyerror("Variável '" + yyvsp[-4].label + "' não declarada no loop for.");
		}
		if (pilha[buscarVariavel(yyvsp[-4].label)][yyvsp[-4].label].tipo != "bool") {
			yyerror("Condição do loop for deve ser do tipo booleano, mas é '" + pilha[buscarVariavel(yyvsp[-5].label)][yyvsp[-5].label].tipo + "'.");
		}
		if (buscarVariavel(yyvsp[-2].label) == -1) {
			yyerror("Variável '" + yyvsp[-3].label + "' não declarada no loop for.");
		}


		// Geração de código
		stringstream ss;
		string temp = pilha[buscarVariavel(yyvsp[-4].label)][yyvsp[-4].label].endereco_memoria;
		string rotuloBreak = pilhaDeRotulosDeLaços.back().rotuloBreak;
		string rotuloContinue = pilhaDeRotulosDeLaços.back().rotuloContinue;

		ss << "\n";

		ss << qtdTab(-1) << "{\n"; // Abre a pilha de variáveis para o loop
		ss << fecharPilha().str(); // Fecha a pilha de variáveis antes do loop
		ss << "\n";

		ss << yyvsp[-6].traducao; // Traduz a expressão de inicialização

		ss << qtdTab(1) << "BeginFor" << defgoto << ":\n";

		ss << yyvsp[-4].traducao; // Traduz a expressão condicional

		ss << "\n";

		ss << qtdTab(1) << "if (!" << temp << ") goto " << rotuloBreak << ";\n";

		ss << "\n";

		ss << yyvsp[0].traducao; // Traduz o bloco do loop

		ss << "\n"; // Adiciona uma nova linha para melhor legibilidade

		ss << qtdTab(1) << rotuloContinue << ":\n";

		ss << yyvsp[-2].traducao; // Traduz a expressão de iteração

		ss << qtdTab(1) << "goto BeginFor" << defgoto << ";\n";

		ss << qtdTab(1) << rotuloBreak << ":\n";

		ss << qtdTab() << "}\n"; // Fecha a pilha de variáveis do loop
		
		pilhaDeRotulosDeLaços.pop_back();

		defgoto++; // Incrementa o contador de blocos de loop
		yyval.traducao = ss.str();
	}
#line 2142 "y.tab.c"
    break;

  case 44: /* LOOP: TK_BREAK ';'  */
#line 604 "sintatica.y"
                       {
        if (pilhaDeRotulosDeLaços.empty()) {
            yyerror("'break' fora de um laco");
        }
        stringstream ss;
        // Pula para o rótulo de 'break' do laço mais interno (o que está no topo da pilha)
        ss << qtdTab() << "goto " << pilhaDeRotulosDeLaços.back().rotuloBreak << ";\n";
        yyval.traducao = ss.str();
    }
#line 2156 "y.tab.c"
    break;

  case 45: /* LOOP: TK_CONTINUE ';'  */
#line 613 "sintatica.y"
                          {
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
        yyval.traducao = ss.str();
    }
#line 2177 "y.tab.c"
    break;

  case 46: /* COND_IF: TK_IF '(' EXPR ')' BLOCO COND_ELSE  */
#line 632 "sintatica.y"
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
#line 2232 "y.tab.c"
    break;

  case 47: /* COND_IF: TK_IF '(' EXPR ')' BLOCO COND_ELSE TK_ELSE BLOCO  */
#line 682 "sintatica.y"
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
#line 2286 "y.tab.c"
    break;

  case 48: /* COND_ELSE: TK_ELSE_IF '(' EXPR ')' BLOCO COND_ELSE  */
#line 733 "sintatica.y"
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
#line 2322 "y.tab.c"
    break;

  case 49: /* COND_ELSE: %empty  */
#line 765 "sintatica.y"
        {
		yyval.traducao = "";
	}
#line 2330 "y.tab.c"
    break;

  case 50: /* $@6: %empty  */
#line 771 "sintatica.y"
    { 
        criarPilha(); 
        addPilhaLaco("EndSwitch" + to_string(defgoto), "EndSwitch" + to_string(defgoto)); 
    }
#line 2339 "y.tab.c"
    break;

  case 51: /* $@7: %empty  */
#line 775 "sintatica.y"
                           {
        // Armazenar a variável do switch globalmente
        if (buscarVariavel(yyvsp[-1].label) == -1) {
            yyerror("Variável '" + yyvsp[-1].label + "' não declarada no switch.");
        }
        current_switch_var = pilha[buscarVariavel(yyvsp[-1].label)][yyvsp[-1].label].endereco_memoria;
    }
#line 2351 "y.tab.c"
    break;

  case 52: /* SWITCH_STMT: $@6 TK_SWITCH '(' EXPR ')' $@7 '{' SIMPLE_CASE_LIST '}'  */
#line 782 "sintatica.y"
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
#line 2387 "y.tab.c"
    break;

  case 53: /* SIMPLE_CASE_LIST: SIMPLE_CASE SIMPLE_CASE_LIST  */
#line 816 "sintatica.y"
                                 {
        yyval.traducao = yyvsp[-1].traducao + yyvsp[0].traducao;
    }
#line 2395 "y.tab.c"
    break;

  case 54: /* SIMPLE_CASE_LIST: SIMPLE_DEFAULT  */
#line 819 "sintatica.y"
                     {
        yyval.traducao = yyvsp[0].traducao;
    }
#line 2403 "y.tab.c"
    break;

  case 55: /* SIMPLE_CASE_LIST: %empty  */
#line 822 "sintatica.y"
                  {
        yyval.traducao = "";
    }
#line 2411 "y.tab.c"
    break;

  case 56: /* SIMPLE_CASE: TK_CASE TK_NUM ':' COMANDOS  */
#line 828 "sintatica.y"
                                {
        stringstream ss;
        string case_id = to_string(defgoto);
        
        // Mesmo padrão do if: comparação em três endereços
        string temp_val = "t" + to_string(tempVar);
        adicionaVar(temp_val, "int", true);
        
        string temp_comp = "t" + to_string(tempVar);
        adicionaVar(temp_comp, "bool", true);
        
        ss <<"\n"<< qtdTab() << temp_val << " = " << yyvsp[-2].traducao << ";\n";
        ss << qtdTab() << temp_comp << " = " << current_switch_var << " == " << temp_val << ";\n\n";
        ss << qtdTab() << "if (!" << temp_comp << ") goto NextCase" << case_id << "_" << yyvsp[-2].traducao << ";\n";
        ss << yyvsp[0].traducao;
        ss << qtdTab() << "NextCase" << case_id << "_" << yyvsp[-2].traducao << ":\n";
        
        yyval.traducao = ss.str();
    }
#line 2435 "y.tab.c"
    break;

  case 57: /* SIMPLE_DEFAULT: TK_DEFAULT ':' COMANDOS  */
#line 850 "sintatica.y"
                            {
        stringstream ss;
        
        ss << "\n" << yyvsp[0].traducao;
        
        yyval.traducao = ss.str();
    }
#line 2447 "y.tab.c"
    break;

  case 58: /* EXPR: EXPR_LOG  */
#line 860 "sintatica.y"
             { // Removido o '|' inicial e o '%prec TK_OR'
        yyval.label = yyvsp[0].label;     // <<< ADICIONADO E CRUCIAL
        yyval.traducao = yyvsp[0].traducao;
    }
#line 2456 "y.tab.c"
    break;

  case 59: /* EXPR_ARIT: EXPR_ARIT '+' EXPR_TERM  */
#line 866 "sintatica.y"
                                          {
		stringstream ss;
		string var1 = yyvsp[-2].label;
		string var2 = yyvsp[0].label;
		ss = veririficarTipo(var1, "+", var2);
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
    }
#line 2469 "y.tab.c"
    break;

  case 60: /* EXPR_ARIT: EXPR_ARIT '-' EXPR_TERM  */
#line 874 "sintatica.y"
                                        {
        stringstream ss;
		string var1 = yyvsp[-2].label;
		string var2 = yyvsp[0].label;
		ss = veririficarTipo(var1, "-", var2);
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();

	}
#line 2483 "y.tab.c"
    break;

  case 61: /* EXPR_ARIT: EXPR_TERM  */
#line 883 "sintatica.y"
                {
        yyval.label = yyvsp[0].label;
        yyval.traducao = yyvsp[0].traducao;
    }
#line 2492 "y.tab.c"
    break;

  case 62: /* EXPR_TERM: EXPR_TERM '*' EXPR_ATOM  */
#line 889 "sintatica.y"
                                                  {
		stringstream ss;
		string var1 = yyvsp[-2].label;
		string var2 = yyvsp[0].label;
		ss = veririficarTipo(var1, "*", var2);
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 2505 "y.tab.c"
    break;

  case 63: /* EXPR_TERM: EXPR_TERM '/' EXPR_ATOM  */
#line 897 "sintatica.y"
                                            {
		stringstream ss;
		string var1 = yyvsp[-2].label;
		string var2 = yyvsp[0].label;
		ss = veririficarTipo(var1, "/", var2);
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 2518 "y.tab.c"
    break;

  case 64: /* EXPR_TERM: EXPR_TERM '%' EXPR_ATOM  */
#line 905 "sintatica.y"
                                            {
		stringstream ss;
		string var1 = yyvsp[-2].label;
		string var2 = yyvsp[0].label;
		ss = veririficarTipo(var1, "%", var2);
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 2531 "y.tab.c"
    break;

  case 65: /* EXPR_TERM: EXPR_ATOM  */
#line 914 "sintatica.y"
                    {
		yyval.label = yyvsp[0].label;
		yyval.traducao = yyvsp[0].traducao;
	}
#line 2540 "y.tab.c"
    break;

  case 66: /* EXPR_LOG: EXPR_LOG TK_AND EXPR_REL  */
#line 922 "sintatica.y"
                                              {
		stringstream ss;
		ss = veririficarTipo(yyvsp[-2].label, "&&", yyvsp[0].label);
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 2551 "y.tab.c"
    break;

  case 67: /* EXPR_LOG: EXPR_LOG TK_OR EXPR_REL  */
#line 928 "sintatica.y"
                                              {
		stringstream ss;
		ss = veririficarTipo(yyvsp[-2].label, "||", yyvsp[0].label);
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 2562 "y.tab.c"
    break;

  case 68: /* EXPR_LOG: EXPR_REL  */
#line 934 "sintatica.y"
                   {
		yyval.label = yyvsp[0].label;
		yyval.traducao = yyvsp[0].traducao;
	}
#line 2571 "y.tab.c"
    break;

  case 69: /* EXPR_REL: EXPR_REL TK_IGUAL EXPR_REL  */
#line 940 "sintatica.y"
                                                  {
		stringstream ss;
		ss = veririficarTipo(yyvsp[-2].label, "==", yyvsp[0].label);
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 2582 "y.tab.c"
    break;

  case 70: /* EXPR_REL: EXPR_REL TK_DIFERENTE EXPR_REL  */
#line 946 "sintatica.y"
                                                            {
		stringstream ss;
		ss = veririficarTipo(yyvsp[-2].label, "!=", yyvsp[0].label);
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 2593 "y.tab.c"
    break;

  case 71: /* EXPR_REL: EXPR_REL '>' EXPR_REL  */
#line 952 "sintatica.y"
                                          {
		stringstream ss;
		ss = veririficarTipo(yyvsp[-2].label, ">", yyvsp[0].label);
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 2604 "y.tab.c"
    break;

  case 72: /* EXPR_REL: EXPR_REL '<' EXPR_REL  */
#line 958 "sintatica.y"
                                          {
		stringstream ss;	
		ss = veririficarTipo(yyvsp[-2].label, "<", yyvsp[0].label);
		yyval.label = "t" + to_string(tempVar-1);		
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 2615 "y.tab.c"
    break;

  case 73: /* EXPR_REL: EXPR_REL TK_MAIOR_IGUAL EXPR_REL  */
#line 964 "sintatica.y"
                                                                {
		stringstream ss;
		ss = veririficarTipo(yyvsp[-2].label, ">=", yyvsp[0].label);
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 2626 "y.tab.c"
    break;

  case 74: /* EXPR_REL: EXPR_REL TK_MENOR_IGUAL EXPR_REL  */
#line 970 "sintatica.y"
                                                                {
		stringstream ss;
		ss = veririficarTipo(yyvsp[-2].label, "<=", yyvsp[0].label);
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 2637 "y.tab.c"
    break;

  case 75: /* EXPR_REL: EXPR_NOT  */
#line 976 "sintatica.y"
                   {
		yyval.label = yyvsp[0].label;
		yyval.traducao = yyvsp[0].traducao;
	}
#line 2646 "y.tab.c"
    break;

  case 76: /* EXPR_NOT: '!' EXPR_NOT  */
#line 982 "sintatica.y"
                               {
		stringstream ss;
		ss = veririficarTipo(yyvsp[0].label, "!", "");
		yyval.label = "t" + to_string(tempVar-1);
		yyval.traducao = yyvsp[0].traducao + ss.str();
	}
#line 2657 "y.tab.c"
    break;

  case 77: /* EXPR_NOT: EXPR_ARIT  */
#line 988 "sintatica.y"
                    {
		yyval.label = yyvsp[0].label;
		yyval.traducao = yyvsp[0].traducao;
	}
#line 2666 "y.tab.c"
    break;

  case 78: /* EXPR_ATOM: '(' EXPR ')'  */
#line 994 "sintatica.y"
                            {
        yyval.label = yyvsp[-1].label;
        yyval.traducao = yyvsp[-1].traducao;
    }
#line 2675 "y.tab.c"
    break;

  case 79: /* EXPR_ATOM: '-' EXPR_ATOM  */
#line 998 "sintatica.y"
                                 {
        // 1. Buscar informações do operando ($2)
        int indice_escopo_operando = buscarVariavel(yyvsp[0].label);
        if (indice_escopo_operando == -1) {
            yyerror("Variavel '" + yyvsp[0].label + "' nao declarada (operando de UMINUS)");
        }
        string tipo_operando = pilha[indice_escopo_operando][yyvsp[0].label].tipo;
        string c_nome_operando = pilha[indice_escopo_operando][yyvsp[0].label].endereco_memoria;

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
        yyval.label = chave_temp_resultado;
        yyval.traducao = yyvsp[0].traducao + ss_code.str();
    }
#line 2710 "y.tab.c"
    break;

  case 80: /* EXPR_ATOM: TK_NUM  */
#line 1028 "sintatica.y"
             {
        // 1. Criar chave para a temporária do número
        string chave_temp_num = "t_num_" + to_string(tempVar);
        
        // 2. Inferir tipo e adicionar à tabela
        string tipo_num = (yyvsp[0].traducao.find('.') != string::npos) ? "float" : "int";
        adicionaVar(chave_temp_num, tipo_num, true);

        // 3. Obter o nome C da temporária
        string c_nome_num = pilha[pilha.size()-1][chave_temp_num].endereco_memoria;
        
        // 4. Gerar código C
        stringstream ss_code;
        ss_code << qtdTab() << c_nome_num << " = " << yyvsp[0].traducao << ";\n"; // $1.traducao é o valor literal do número
        
        // 5. Definir atributos
        yyval.label = chave_temp_num;
        yyval.traducao = ss_code.str();
    }
#line 2734 "y.tab.c"
    break;

  case 81: /* EXPR_ATOM: TK_ID  */
#line 1047 "sintatica.y"
            {
        if (buscarVariavel(yyvsp[0].label) == -1) { // $1.label é a chave (nome original do ID)
            yyerror("Variavel '" + yyvsp[0].label + "' nao declarada");
        }
        // Para um ID usado como valor, o label é o próprio nome/chave do ID.
        // O endereco_memoria será usado por regras superiores quando precisarem do valor.
        yyval.label = yyvsp[0].label; 
        yyval.traducao = ""; // Não gera novo código C aqui, apenas passa o nome/chave
    }
#line 2748 "y.tab.c"
    break;

  case 82: /* EXPR_ATOM: COVERT_TYPE  */
#line 1056 "sintatica.y"
                  { // Assumindo que COVERT_TYPE já define $$.label e $$.traducao corretamente
        yyval.label = yyvsp[0].label;
        yyval.traducao = yyvsp[0].traducao;
    }
#line 2757 "y.tab.c"
    break;

  case 83: /* EXPR_ATOM: TK_BOOL_TRUE  */
#line 1060 "sintatica.y"
                   {
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
        yyval.label = chave_temp_true;
        yyval.traducao = ss_code.str();
    }
#line 2780 "y.tab.c"
    break;

  case 84: /* EXPR_ATOM: TK_BOOL_FALSE  */
#line 1078 "sintatica.y"
                    {
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
        yyval.label = chave_temp_false;
        yyval.traducao = ss_code.str();
    }
#line 2803 "y.tab.c"
    break;

  case 85: /* EXPR_ATOM: TK_STRING_LITERAL  */
#line 1096 "sintatica.y"
                        { // <<< ADICIONADO E CORRIGIDO
        // 1. Criar chave para a temporária do literal string
        string chave_temp_sl = "t" + to_string(tempVar);
        
        // 2. Adicionar à tabela com tipo "string"
        adicionaVar(chave_temp_sl, "string", true);

        // 3. Obter o nome C da temporária (será algo como "tN")
        string c_nome_sl = pilha[pilha.size()-1][chave_temp_sl].endereco_memoria;
        
        // 4. Gerar código C
        // $1.traducao do lexer já é o literal C com aspas (ex: "\"ola\"")
        stringstream ss_code;
        ss_code << qtdTab() << c_nome_sl << " = " << yyvsp[0].traducao << ";\n";

		pilha[pilha.size()-1][chave_temp_sl].malocada = true; // Marca como malocada
        
        // 5. Definir atributos
        yyval.label = chave_temp_sl; // O label é a chave da temporária
        yyval.traducao = ss_code.str();  // O código C gerado
    }
#line 2829 "y.tab.c"
    break;

  case 86: /* COVERT_TYPE: TK_TIPO_INT '(' EXPR ')'  */
#line 1120 "sintatica.y"
                                 {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << qtdTab() << temp << " = (int)" << pilha[buscarVariavel(yyvsp[-1].label)][yyvsp[-1].label].endereco_memoria << ";\n";
		yyval.label = temp;
		yyval.traducao = yyvsp[-1].traducao + ss.str();
		adicionaVar(temp, "int", true);
	}
#line 2842 "y.tab.c"
    break;

  case 87: /* COVERT_TYPE: TK_TIPO_FLOAT '(' EXPR ')'  */
#line 1128 "sintatica.y"
                                     {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << qtdTab() << temp << " = (float)" << pilha[buscarVariavel(yyvsp[-1].label)][yyvsp[-1].label].endereco_memoria << ";\n";
		yyval.label = temp;
		yyval.traducao = yyvsp[-1].traducao + ss.str();
		adicionaVar(temp, "float", true);
	}
#line 2855 "y.tab.c"
    break;

  case 88: /* QUICKSORT_CMD: TK_QUICKSORT '(' TK_ID ',' TK_NUM ')'  */
#line 1139 "sintatica.y"
                                          {
        if (buscarVariavel(yyvsp[-3].label) == -1) {
            yyerror("Vetor '" + yyvsp[-3].label + "' não declarado.");
        }
        
        string tipo_var = pilha[buscarVariavel(yyvsp[-3].label)][yyvsp[-3].label].tipo;
        if (tipo_var != "int*" && tipo_var != "vetor_int") {
            yyerror("QuickSort só funciona com vetores de inteiros.");
        }
        
        stringstream ss;
        string endereco_vetor = pilha[buscarVariavel(yyvsp[-3].label)][yyvsp[-3].label].endereco_memoria;
        
        ss << qtdTab() << "quick_sort_completo(" << endereco_vetor << ", " << yyvsp[-1].traducao << ");\n";
        
        yyval.traducao = ss.str();
    }
#line 2877 "y.tab.c"
    break;

  case 89: /* QUICKSORT_CMD: TK_CRIAR_VETOR '(' TK_ID ',' TK_NUM ')'  */
#line 1156 "sintatica.y"
                                              {
        // Verificar se variável já existe
        if (buscarVariavel(yyvsp[-3].label) != -1) {
            yyerror("Variável '" + yyvsp[-3].label + "' já declarada.");
        }
        
        adicionaVar(yyvsp[-3].label, "int*", false);
        
        stringstream ss;
        string endereco_vetor = pilha[pilha.size()-1][yyvsp[-3].label].endereco_memoria;
        
        ss << qtdTab() << endereco_vetor << " = criar_vetor(" << yyvsp[-1].traducao << ");\n";
        
        yyval.traducao = ss.str();
    }
#line 2897 "y.tab.c"
    break;

  case 90: /* QUICKSORT_CMD: TK_IMPRIMIR_VETOR '(' TK_ID ',' TK_NUM ')'  */
#line 1171 "sintatica.y"
                                                 {
        if (buscarVariavel(yyvsp[-3].label) == -1) {
            yyerror("Vetor '" + yyvsp[-3].label + "' não declarado.");
        }
        
        stringstream ss;
        string endereco_vetor = pilha[buscarVariavel(yyvsp[-3].label)][yyvsp[-3].label].endereco_memoria;
        
        ss << qtdTab() << "imprimir_vetor(" << endereco_vetor << ", " << yyvsp[-1].traducao << ");\n";
        
        yyval.traducao = ss.str();
    }
#line 2914 "y.tab.c"
    break;


#line 2918 "y.tab.c"

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

#line 1184 "sintatica.y"


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
