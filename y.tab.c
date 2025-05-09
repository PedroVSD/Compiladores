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

#define YYSTYPE atributos

using namespace std;



void adicionaVar(string nome, string tipo, bool temp = false);


int tempVar = 0;
int defVar = 0;

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

extern int numLinha;
int yylex(void);
void yyerror(string);

#line 108 "y.tab.c"

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
    UMINUS = 274                   /* UMINUS  */
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
#define UMINUS 274

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
  YYSYMBOL_19_ = 19,                       /* '<'  */
  YYSYMBOL_20_ = 20,                       /* '>'  */
  YYSYMBOL_21_ = 21,                       /* '+'  */
  YYSYMBOL_22_ = 22,                       /* '-'  */
  YYSYMBOL_23_ = 23,                       /* '*'  */
  YYSYMBOL_24_ = 24,                       /* '/'  */
  YYSYMBOL_UMINUS = 25,                    /* UMINUS  */
  YYSYMBOL_26_ = 26,                       /* '!'  */
  YYSYMBOL_27_ = 27,                       /* '('  */
  YYSYMBOL_28_ = 28,                       /* ')'  */
  YYSYMBOL_29_ = 29,                       /* '{'  */
  YYSYMBOL_30_ = 30,                       /* '}'  */
  YYSYMBOL_31_ = 31,                       /* ';'  */
  YYSYMBOL_32_ = 32,                       /* '='  */
  YYSYMBOL_YYACCEPT = 33,                  /* $accept  */
  YYSYMBOL_S = 34,                         /* S  */
  YYSYMBOL_BLOCO = 35,                     /* BLOCO  */
  YYSYMBOL_COMANDOS = 36,                  /* COMANDOS  */
  YYSYMBOL_COMANDO = 37,                   /* COMANDO  */
  YYSYMBOL_DECLARACAO = 38,                /* DECLARACAO  */
  YYSYMBOL_TIPO = 39,                      /* TIPO  */
  YYSYMBOL_DECLAR_VAR = 40,                /* DECLAR_VAR  */
  YYSYMBOL_ATRIB = 41,                     /* ATRIB  */
  YYSYMBOL_EXPR = 42,                      /* EXPR  */
  YYSYMBOL_EXPR_ARIT = 43,                 /* EXPR_ARIT  */
  YYSYMBOL_EXPR_TERM = 44,                 /* EXPR_TERM  */
  YYSYMBOL_EXPR_LOG = 45,                  /* EXPR_LOG  */
  YYSYMBOL_EXPR_REL = 46,                  /* EXPR_REL  */
  YYSYMBOL_EXPR_NOT = 47,                  /* EXPR_NOT  */
  YYSYMBOL_EXPR_ATOM = 48,                 /* EXPR_ATOM  */
  YYSYMBOL_COVERT_TYPE = 49                /* COVERT_TYPE  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   109

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  46
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  82

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   274


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
       2,     2,     2,    26,     2,     2,     2,     2,     2,     2,
      27,    28,    23,    21,     2,    22,     2,    24,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    31,
      19,    32,    20,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,     2,    30,     2,     2,     2,     2,
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
      15,    16,    17,    18,    25
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    59,    59,    77,    83,    86,    92,    93,    94,    98,
     104,   105,   106,   107,   111,   115,   137,   145,   179,   180,
     185,   218,   251,   257,   289,   321,   329,   337,   345,   351,
     384,   418,   453,   488,   523,   558,   564,   572,   578,   582,
     593,   606,   614,   618,   626,   636,   644
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
  "TK_BOOL_FALSE", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "UMINUS",
  "'!'", "'('", "')'", "'{'", "'}'", "';'", "'='", "$accept", "S", "BLOCO",
  "COMANDOS", "COMANDO", "DECLARACAO", "TIPO", "DECLAR_VAR", "ATRIB",
  "EXPR", "EXPR_ARIT", "EXPR_TERM", "EXPR_LOG", "EXPR_REL", "EXPR_NOT",
  "EXPR_ATOM", "COVERT_TYPE", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-30)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-19)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       3,    15,    24,     2,   -30,     5,    12,     1,   -30,   -30,
      -2,     4,     7,   -30,   -30,   -30,   -30,    65,    59,    59,
      13,     1,    11,    40,   -30,    14,    16,   -10,   -21,    -1,
      78,   -30,   -30,   -30,    59,    59,    59,   -30,     4,     7,
     -30,   -30,    20,   -30,   -30,   -30,    17,   -30,   -30,    65,
      65,    65,    65,    59,    59,    59,    59,    59,    59,    59,
      59,   -30,    25,    26,   -30,    34,   -21,   -21,   -30,   -30,
     -30,    41,    83,    83,   -30,   -30,   -30,   -30,   -30,   -30,
     -30,   -30
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     5,     2,    40,
      41,    10,    11,    12,    13,    43,    44,     0,     0,    18,
       0,     5,     0,     0,     9,     0,     0,    37,    22,    19,
      28,    35,    25,    42,    18,    18,    18,    41,     0,     0,
      39,    36,     0,     3,     4,     6,    14,     7,     8,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    17,     0,     0,    38,    18,    20,    21,    23,    24,
      26,    27,    29,    30,    33,    34,    32,    31,    45,    46,
      16,    15
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -30,   -30,   -30,    36,   -30,   -30,   -30,   -30,   -30,   -19,
     -30,   -29,   -28,    49,    48,   -16,   -30
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     8,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      42,    40,    51,    52,     9,    10,    11,    12,     1,    13,
      14,    49,    50,    53,    54,    61,    62,    63,    15,    16,
      66,    67,     3,    17,     4,    70,    71,    18,    19,     5,
      34,    35,   -18,     6,    36,    68,    69,     9,    37,    38,
      39,     7,    45,    43,    46,    47,    81,    48,    64,    65,
      80,    15,    16,    78,    79,    53,    17,    44,     0,     0,
      18,    19,     9,    37,    38,    39,    41,     0,     9,    37,
      38,    39,     0,     0,     0,     0,    15,    16,     0,     0,
       0,    17,    15,    16,     0,    18,    19,    17,    55,    56,
      57,    58,    19,   -19,   -19,    57,    58,    59,    60,     0,
       0,     0,    59,    60,    72,    73,    74,    75,    76,    77
};

static const yytype_int8 yycheck[] =
{
      19,    17,    23,    24,     3,     4,     5,     6,     5,     8,
       9,    21,    22,    14,    15,    34,    35,    36,    17,    18,
      49,    50,     7,    22,     0,    53,    54,    26,    27,    27,
      32,    27,    31,    28,    27,    51,    52,     3,     4,     5,
       6,    29,    31,    30,     4,    31,    65,    31,    28,    32,
      16,    17,    18,    28,    28,    14,    22,    21,    -1,    -1,
      26,    27,     3,     4,     5,     6,    18,    -1,     3,     4,
       5,     6,    -1,    -1,    -1,    -1,    17,    18,    -1,    -1,
      -1,    22,    17,    18,    -1,    26,    27,    22,    10,    11,
      12,    13,    27,    10,    11,    12,    13,    19,    20,    -1,
      -1,    -1,    19,    20,    55,    56,    57,    58,    59,    60
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     5,    34,     7,     0,    27,    28,    29,    35,     3,
       4,     5,     6,     8,     9,    17,    18,    22,    26,    27,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    32,    27,    27,     4,     5,     6,
      48,    47,    42,    30,    36,    31,     4,    31,    31,    21,
      22,    23,    24,    14,    15,    10,    11,    12,    13,    19,
      20,    42,    42,    42,    28,    32,    44,    44,    48,    48,
      45,    45,    46,    46,    46,    46,    46,    46,    28,    28,
      16,    42
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    33,    34,    35,    36,    36,    37,    37,    37,    38,
      39,    39,    39,    39,    40,    40,    40,    41,    42,    42,
      43,    43,    43,    44,    44,    44,    45,    45,    45,    46,
      46,    46,    46,    46,    46,    46,    47,    47,    48,    48,
      48,    48,    48,    48,    48,    49,    49
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     3,     2,     0,     2,     2,     2,     1,
       1,     1,     1,     1,     2,     4,     4,     3,     0,     1,
       3,     3,     1,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     3,     3,     1,     2,     1,     3,     2,
       1,     1,     1,     1,     1,     4,     4
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
  case 2: /* S: TK_TIPO_INT TK_MAIN '(' ')' BLOCO  */
#line 59 "sintatica.y"
                                            {
		cout << "/*Compilador DHP*/\n";
		cout << "\n#include<string.h>\n#include<stdio.h>\n";
		cout << "int main(void)\n{\n";

		for (const auto& [nome, info] : tabela_simbolos) {
			string tipo = (info.tipo == "bool") ? "int" : info.tipo;
			if (!(info.temporaria)) {
    			cout << "\t" << tipo  << " " << info.endereco_memoria << ";\t //Variavel: "<< nome << "\n";}
			else {
				cout << "\t" << tipo << " " << info.endereco_memoria << ";\n";}
		}

		cout << "\n" << yyvsp[0].traducao << "\n";
		cout << "\treturn 0;\n}\n";
	  }
#line 1290 "y.tab.c"
    break;

  case 3: /* BLOCO: '{' COMANDOS '}'  */
#line 77 "sintatica.y"
                        {
	yyval.traducao = yyvsp[-1].traducao;
}
#line 1298 "y.tab.c"
    break;

  case 4: /* COMANDOS: COMANDO COMANDOS  */
#line 83 "sintatica.y"
                         {
		yyval.traducao = yyvsp[-1].traducao + yyvsp[0].traducao;
	}
#line 1306 "y.tab.c"
    break;

  case 5: /* COMANDOS: %empty  */
#line 86 "sintatica.y"
                      {
		yyval.traducao = "";
	}
#line 1314 "y.tab.c"
    break;

  case 6: /* COMANDO: DECLARACAO ';'  */
#line 92 "sintatica.y"
                         { yyval.traducao = yyvsp[-1].traducao; }
#line 1320 "y.tab.c"
    break;

  case 7: /* COMANDO: ATRIB ';'  */
#line 93 "sintatica.y"
                         { yyval.traducao = yyvsp[-1].traducao; }
#line 1326 "y.tab.c"
    break;

  case 8: /* COMANDO: EXPR ';'  */
#line 94 "sintatica.y"
                         { yyval.traducao = yyvsp[-1].traducao; }
#line 1332 "y.tab.c"
    break;

  case 9: /* DECLARACAO: DECLAR_VAR  */
#line 98 "sintatica.y"
                 {
        yyval.traducao = yyvsp[0].traducao;
      }
#line 1340 "y.tab.c"
    break;

  case 10: /* TIPO: TK_TIPO_INT  */
#line 104 "sintatica.y"
                    { yyval.label = "int"; }
#line 1346 "y.tab.c"
    break;

  case 11: /* TIPO: TK_TIPO_FLOAT  */
#line 105 "sintatica.y"
                    { yyval.label = "float"; }
#line 1352 "y.tab.c"
    break;

  case 12: /* TIPO: TK_TIPO_CHAR  */
#line 106 "sintatica.y"
                    { yyval.label = "char"; }
#line 1358 "y.tab.c"
    break;

  case 13: /* TIPO: TK_TIPO_BOOL  */
#line 107 "sintatica.y"
                    { yyval.label = "bool"; }
#line 1364 "y.tab.c"
    break;

  case 14: /* DECLAR_VAR: TIPO TK_ID  */
#line 111 "sintatica.y"
                 {
        adicionaVar(yyvsp[0].label, yyvsp[-1].label);
        yyval.traducao = "";
      }
#line 1373 "y.tab.c"
    break;

  case 15: /* DECLAR_VAR: TIPO TK_ID '=' EXPR  */
#line 115 "sintatica.y"
                          {
        adicionaVar(yyvsp[-2].label, yyvsp[-3].label);

		string tipo1 = yyvsp[-3].label;
		string tipo2 = tabela_simbolos[yyvsp[0].label].tipo;
		string result = yyvsp[0].label;
		if (tipo1 != tipo2) {
			if(tipo1 == "int" && tipo2 == "float"){
				result = "(int)" + yyvsp[0].label;
			}
			else if(tipo1 == "float" && tipo2 == "int"){
				result = "(float)" + yyvsp[0].label;
			}
			else{
				cout << "Erro: Tipos incompatíveis para atribuição na linha " << numLinha << ".\n";
				exit(1);
			}
		}
        stringstream ss;
        ss << "\t" << tabela_simbolos[yyvsp[-2].label].endereco_memoria << " = " << result << ";\n";
        yyval.traducao = yyvsp[0].traducao + ss.str();
      }
#line 1400 "y.tab.c"
    break;

  case 16: /* DECLAR_VAR: TIPO TK_ID '=' TK_CHAR  */
#line 137 "sintatica.y"
                             {
        adicionaVar(yyvsp[-2].label, yyvsp[-3].label);
        stringstream ss;
        ss << "\t" << tabela_simbolos[yyvsp[-2].label].endereco_memoria << " = " << yyvsp[0].label << ";\n";
        yyval.traducao = ss.str();
      }
#line 1411 "y.tab.c"
    break;

  case 17: /* ATRIB: TK_ID '=' EXPR  */
#line 145 "sintatica.y"
                      {
	if (tabela_simbolos.find(yyvsp[-2].label) == tabela_simbolos.end()) {
		cout << "Erro: Variável " << yyvsp[-2].label << " não declarada.\n";
		exit(1);
	}
	string tipo1 = tabela_simbolos[yyvsp[-2].label].tipo;
	string tipo2 = tabela_simbolos[yyvsp[0].label].tipo;
	stringstream ss;

	if (tipo1 != tipo2) {
		if(tipo1 == "int" && tipo2 == "float"){
			string temp = "t" + to_string(tempVar);
			adicionaVar(temp, tipo1, true);
			ss << "\t" << temp << " = (int)" << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
			yyval.label = temp;
		}
		else if(tipo1 == "float" && tipo2 == "int"){
			string temp = "t" + to_string(tempVar);
			adicionaVar(temp, tipo1, true);
			ss << "\t" << temp << " = (float)" << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
			yyval.label = temp;
		}
		else{
			cout << "Erro: Tipos incompatíveis para atribuição.\n";
			exit(1);
		}
	}

	ss << "\t" << tabela_simbolos[yyvsp[-2].label].endereco_memoria << " = " << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
	yyval.traducao = yyvsp[0].traducao + ss.str();
}
#line 1447 "y.tab.c"
    break;

  case 19: /* EXPR: EXPR_LOG  */
#line 180 "sintatica.y"
                               {
		yyval.traducao = yyvsp[0].traducao;
	}
#line 1455 "y.tab.c"
    break;

  case 20: /* EXPR_ARIT: EXPR_ARIT '+' EXPR_TERM  */
#line 185 "sintatica.y"
                                          {
		string temp = "t" + to_string(tempVar);
		stringstream ss;

		// Inferência simplificada: se um dos lados for float, resultado é float
		string tipo1 = tabela_simbolos[yyvsp[-2].label].tipo;
		string tipo2 = tabela_simbolos[yyvsp[0].label].tipo;
		string tipo_result = (tipo1 == "float" || tipo2 == "float") ? "float" : "int";
		adicionaVar(temp, tipo_result, true);

		if(tipo1 != tipo2){
			if(tipo1 == "int" && tipo2 == "float"){
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, tipo_result, true);
				ss << "\t" << temp << " = (float)" << tabela_simbolos[yyvsp[-2].label].endereco_memoria << ";\n";
				ss << "\t" << temp2 << " = " << temp << " + " << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
				yyval.label = temp2;
			}
			else{
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, tipo_result, true);
				ss << "\t" << temp << " = (float)" << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
				ss << "\t" << temp2 << " = " << temp << " + " << tabela_simbolos[yyvsp[-2].label].endereco_memoria << ";\n";
				yyval.label = temp2;
			}
		}
		else{
			ss << "\t" << temp << " = " << tabela_simbolos[yyvsp[-2].label].endereco_memoria << " + " << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
			yyval.label = temp;
		}
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();

	}
#line 1493 "y.tab.c"
    break;

  case 21: /* EXPR_ARIT: EXPR_ARIT '-' EXPR_TERM  */
#line 218 "sintatica.y"
                                            {
		string temp = "t" + to_string(tempVar);
		stringstream ss;

		// Inferência simplificada: se um dos lados for float, resultado é float
		string tipo1 = tabela_simbolos[yyvsp[-2].label].tipo;
		string tipo2 = tabela_simbolos[yyvsp[0].label].tipo;
		string tipo_result = (tipo1 == "float" || tipo2 == "float") ? "float" : "int";
		adicionaVar(temp, tipo_result, true);

		if(tipo1 != tipo2){
			if(tipo1 == "int" && tipo2 == "float"){
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, tipo_result, true);
				ss << "\t" << temp << " = (float)" << tabela_simbolos[yyvsp[-2].label].endereco_memoria << ";\n";
				ss << "\t" << temp2 << " = " << temp << " - " << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
				yyval.label = temp2;
			}
			else{
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, tipo_result, true);
				ss << "\t" << temp << " = (float)" << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
				ss << "\t" << temp2 << " = " << temp << " - " << tabela_simbolos[yyvsp[-2].label].endereco_memoria << ";\n";
				yyval.label = temp2;
			}
		}
		else{
			ss << "\t" << temp << " = " << tabela_simbolos[yyvsp[-2].label].endereco_memoria << " - " << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
			yyval.label = temp;
		}
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();

	}
#line 1531 "y.tab.c"
    break;

  case 22: /* EXPR_ARIT: EXPR_TERM  */
#line 251 "sintatica.y"
                    {
		yyval. label = yyvsp[0].label;
		yyval.traducao = yyvsp[0].traducao;
	}
#line 1540 "y.tab.c"
    break;

  case 23: /* EXPR_TERM: EXPR_TERM '*' EXPR_ATOM  */
#line 257 "sintatica.y"
                                                  {
		string temp = "t" + to_string(tempVar);
		stringstream ss;

		// Inferência simplificada: se um dos lados for float, resultado é float
		string tipo1 = tabela_simbolos[yyvsp[-2].label].tipo;
		string tipo2 = tabela_simbolos[yyvsp[0].label].tipo;
		string tipo_result = (tipo1 == "float" || tipo2 == "float") ? "float" : "int";
		adicionaVar(temp, tipo_result, true);

		if(tipo1 != tipo2){
			if(tipo1 == "int" && tipo2 == "float"){
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, tipo_result, true);
				ss << "\t" << temp << " = (float)" << tabela_simbolos[yyvsp[-2].label].endereco_memoria << ";\n";
				ss << "\t" << temp2 << " = " << temp << " * " << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
				yyval.label = temp2;
			}
			else{
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, tipo_result, true);
				ss << "\t" << temp << " = (float)" << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
				ss << "\t" << temp2 << " = " << temp << " * " << tabela_simbolos[yyvsp[-2].label].endereco_memoria << ";\n";
				yyval.label = temp2;
			}
		}
		else{
			ss << "\t" << temp << " = " << tabela_simbolos[yyvsp[-2].label].endereco_memoria << " * " << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
			yyval.label = temp;
		}
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 1577 "y.tab.c"
    break;

  case 24: /* EXPR_TERM: EXPR_TERM '/' EXPR_ATOM  */
#line 289 "sintatica.y"
                                            {
		string temp = "t" + to_string(tempVar);
		stringstream ss;

		// Inferência simplificada: se um dos lados for float, resultado é float
		string tipo1 = tabela_simbolos[yyvsp[-2].label].tipo;
		string tipo2 = tabela_simbolos[yyvsp[0].label].tipo;
		string tipo_result = (tipo1 == "float" || tipo2 == "float") ? "float" : "int";
		adicionaVar(temp, tipo_result, true);

		if(tipo1 != tipo2){
			if(tipo1 == "int" && tipo2 == "float"){
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, tipo_result, true);
				ss << "\t" << temp << " = (float)" << tabela_simbolos[yyvsp[-2].label].endereco_memoria << ";\n";
				ss << "\t" << temp2 << " = " << temp << " / " << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
				yyval.label = temp2;
			}
			else{
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, tipo_result, true);
				ss << "\t" << temp << " = (float)" << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
				ss << "\t" << temp2 << " = " << temp << " / " << tabela_simbolos[yyvsp[-2].label].endereco_memoria << ";\n";
				yyval.label = temp2;
			}
		}
		else{
			ss << "\t" << temp << " = " << tabela_simbolos[yyvsp[-2].label].endereco_memoria << " / " << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
			yyval.label = temp;
		}
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 1614 "y.tab.c"
    break;

  case 25: /* EXPR_TERM: EXPR_ATOM  */
#line 321 "sintatica.y"
                    {
		yyval.label = yyvsp[0].label;
		yyval.traducao = yyvsp[0].traducao;
	}
#line 1623 "y.tab.c"
    break;

  case 26: /* EXPR_LOG: EXPR_LOG TK_AND EXPR_LOG  */
#line 329 "sintatica.y"
                                              {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << "\t" << temp << " = " << tabela_simbolos[yyvsp[-2].label].endereco_memoria << " && " << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
		yyval.label = temp;
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
		adicionaVar(temp, "bool", true);
	}
#line 1636 "y.tab.c"
    break;

  case 27: /* EXPR_LOG: EXPR_LOG TK_OR EXPR_LOG  */
#line 337 "sintatica.y"
                                              {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << "\t" << temp << " = " << tabela_simbolos[yyvsp[-2].label].endereco_memoria << " || " << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
		yyval.label = temp;
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
		adicionaVar(temp, "bool", true);
	}
#line 1649 "y.tab.c"
    break;

  case 28: /* EXPR_LOG: EXPR_REL  */
#line 345 "sintatica.y"
                   {
		yyval.label = yyvsp[0].label;
		yyval.traducao = yyvsp[0].traducao;
	}
#line 1658 "y.tab.c"
    break;

  case 29: /* EXPR_REL: EXPR_REL TK_IGUAL EXPR_REL  */
#line 351 "sintatica.y"
                                                  {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		string tipo1 = tabela_simbolos[yyvsp[-2].label].tipo;
		string tipo2 = tabela_simbolos[yyvsp[0].label].tipo;
		adicionaVar(temp, "bool", true);

		if(tipo1 != tipo2){
			if(tipo1 == "int" && tipo2 == "float"){
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, "bool", true);
				ss << "\t" << temp << " = (float)" << tabela_simbolos[yyvsp[-2].label].endereco_memoria << ";\n";
				ss << "\t" << temp2 << " = " << temp << " == " << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
				yyval.label = temp2;
			}
			else if(tipo1 == "float" && tipo2 == "int"){
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, "bool", true);
				ss << "\t" << temp << " = (float)" << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
				ss << "\t" << temp2 << " = " << temp << " == " << tabela_simbolos[yyvsp[-2].label].endereco_memoria << ";\n";
				yyval.label = temp2;
			}
			else{
				cout << "Erro: Tipos incompatíveis para comparação.\n";
				exit(1);
			}
		}
		else{
			ss << "\t" << temp << " = " << tabela_simbolos[yyvsp[-2].label].endereco_memoria << " == " << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
			yyval.label = temp;
		}
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 1696 "y.tab.c"
    break;

  case 30: /* EXPR_REL: EXPR_REL TK_DIFERENTE EXPR_REL  */
#line 384 "sintatica.y"
                                                            {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		string tipo1 = tabela_simbolos[yyvsp[-2].label].tipo;
		string tipo2 = tabela_simbolos[yyvsp[0].label].tipo;
		string tipo_result = (tipo1 == "float" || tipo2 == "float") ? "float" : "int";
		adicionaVar(temp, "bool", true);

		if(tipo1 != tipo2){
			if(tipo1 == "int" && tipo2 == "float"){
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, "bool", true);
				ss << "\t" << temp << " = (float)" << tabela_simbolos[yyvsp[-2].label].endereco_memoria << ";\n";
				ss << "\t" << temp2 << " = " << temp << " != " << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
				yyval.label = temp2;
			}
			else if(tipo1 == "float" && tipo2 == "int"){
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, "bool", true);
				ss << "\t" << temp << " = (float)" << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
				ss << "\t" << temp2 << " = " << temp << " != " << tabela_simbolos[yyvsp[-2].label].endereco_memoria << ";\n";
				yyval.label = temp2;
			}
			else{
				cout << "Erro: Tipos incompatíveis para comparação.\n";
				exit(1);
			}
		}
		else{
			ss << "\t" << temp << " = " << tabela_simbolos[yyvsp[-2].label].endereco_memoria << " != " << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
			yyval.label = temp;
		}
		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 1735 "y.tab.c"
    break;

  case 31: /* EXPR_REL: EXPR_REL '>' EXPR_REL  */
#line 418 "sintatica.y"
                                          {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		string tipo1 = tabela_simbolos[yyvsp[-2].label].tipo;
		string tipo2 = tabela_simbolos[yyvsp[0].label].tipo;
		string tipo_result = (tipo1 == "float" || tipo2 == "float") ? "float" : "int";
		adicionaVar(temp, "bool", true);

		if(tipo1 != tipo2){
			if(tipo1 == "int" && tipo2 == "float"){
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, "bool", true);
				ss << "\t" << temp << " = (float)" << tabela_simbolos[yyvsp[-2].label].endereco_memoria << ";\n";
				ss << "\t" << temp2 << " = " << temp << " > " << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
				yyval.label = temp2;
			}
			else if(tipo1 == "float" && tipo2 == "int"){
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, "bool", true);
				ss << "\t" << temp << " = (float)" << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
				ss << "\t" << temp2 << " = " << temp << " > " << tabela_simbolos[yyvsp[-2].label].endereco_memoria << ";\n";
				yyval.label = temp2;
			}
			else{
				cout << "Erro: Tipos incompatíveis para comparação.\n";
				exit(1);
			}
		}
		else{
			ss << "\t" << temp << " = " << tabela_simbolos[yyvsp[-2].label].endereco_memoria << " > " << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
			yyval.label = temp;
		}

		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 1775 "y.tab.c"
    break;

  case 32: /* EXPR_REL: EXPR_REL '<' EXPR_REL  */
#line 453 "sintatica.y"
                                          {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		string tipo1 = tabela_simbolos[yyvsp[-2].label].tipo;
		string tipo2 = tabela_simbolos[yyvsp[0].label].tipo;
		string tipo_result = (tipo1 == "float" || tipo2 == "float") ? "float" : "int";
		adicionaVar(temp, "bool", true);

		if(tipo1 != tipo2){
			if(tipo1 == "int" && tipo2 == "float"){
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, "bool", true);
				ss << "\t" << temp << " = (float)" << tabela_simbolos[yyvsp[-2].label].endereco_memoria << ";\n";
				ss << "\t" << temp2 << " = " << temp << " < " << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
				yyval.label = temp2;
			}
			else if(tipo1 == "float" && tipo2 == "int"){
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, "bool", true);
				ss << "\t" << temp << " = (float)" << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
				ss << "\t" << temp2 << " = " << temp << " < " << tabela_simbolos[yyvsp[-2].label].endereco_memoria << ";\n";
				yyval.label = temp2;
			}
			else{
				cout << "Erro: Tipos incompatíveis para comparação.\n";
				exit(1);
			}
		}
		else{
			ss << "\t" << temp << " = " << tabela_simbolos[yyvsp[-2].label].endereco_memoria << " < " << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
			yyval.label = temp;
		}

		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 1815 "y.tab.c"
    break;

  case 33: /* EXPR_REL: EXPR_REL TK_MAIOR_IGUAL EXPR_REL  */
#line 488 "sintatica.y"
                                                                {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		string tipo1 = tabela_simbolos[yyvsp[-2].label].tipo;
		string tipo2 = tabela_simbolos[yyvsp[0].label].tipo;
		string tipo_result = (tipo1 == "float" || tipo2 == "float") ? "float" : "int";
		adicionaVar(temp, "bool", true);

		if(tipo1 != tipo2){
			if(tipo1 == "int" && tipo2 == "float"){
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, "bool", true);
				ss << "\t" << temp << " = (float)" << tabela_simbolos[yyvsp[-2].label].endereco_memoria << ";\n";
				ss << "\t" << temp2 << " = " << temp << " >= " << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
				yyval.label = temp2;
			}
			else if(tipo1 == "float" && tipo2 == "int"){
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, "bool", true);
				ss << "\t" << temp << " = (float)" << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
				ss << "\t" << temp2 << " = " << temp << " >= " << tabela_simbolos[yyvsp[-2].label].endereco_memoria << ";\n";
				yyval.label = temp2;
			}
			else{
				cout << "Erro: Tipos incompatíveis para comparação.\n";
				exit(1);
			}
		}
		else{
			ss << "\t" << temp << " = " << tabela_simbolos[yyvsp[-2].label].endereco_memoria << " >= " << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
			yyval.label = temp;
		}

		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 1855 "y.tab.c"
    break;

  case 34: /* EXPR_REL: EXPR_REL TK_MENOR_IGUAL EXPR_REL  */
#line 523 "sintatica.y"
                                                                {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		string tipo1 = tabela_simbolos[yyvsp[-2].label].tipo;
		string tipo2 = tabela_simbolos[yyvsp[0].label].tipo;
		string tipo_result = (tipo1 == "float" || tipo2 == "float") ? "float" : "int";
		adicionaVar(temp, "bool", true);

		if(tipo1 != tipo2){
			if(tipo1 == "int" && tipo2 == "float"){
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, "bool", true);
				ss << "\t" << temp << " = (float)" << tabela_simbolos[yyvsp[-2].label].endereco_memoria << ";\n";
				ss << "\t" << temp2 << " = " << temp << " <= " << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
				yyval.label = temp2;
			}
			else if(tipo1 == "float" && tipo2 == "int"){
				string temp2 = "t" + to_string(tempVar);
				adicionaVar(temp2, "bool", true);
				ss << "\t" << temp << " = (float)" << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
				ss << "\t" << temp2 << " = " << temp << " <= " << tabela_simbolos[yyvsp[-2].label].endereco_memoria << ";\n";
				yyval.label = temp2;
			}
			else{
				cout << "Erro: Tipos incompatíveis para comparação.\n";
				exit(1);
			}
		}
		else{
			ss << "\t" << temp << " = " << tabela_simbolos[yyvsp[-2].label].endereco_memoria << " <= " << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
			yyval.label = temp;
		}

		yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + ss.str();
	}
#line 1895 "y.tab.c"
    break;

  case 35: /* EXPR_REL: EXPR_NOT  */
#line 558 "sintatica.y"
                   {
		yyval.label = yyvsp[0].label;
		yyval.traducao = yyvsp[0].traducao;
	}
#line 1904 "y.tab.c"
    break;

  case 36: /* EXPR_NOT: '!' EXPR_NOT  */
#line 564 "sintatica.y"
                               {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << "\t" << temp << " = !" << tabela_simbolos[yyvsp[0].label].endereco_memoria << ";\n";
		yyval.label = temp;
		yyval.traducao = yyvsp[0].traducao + ss.str();
		adicionaVar(temp, "bool", true);
	}
#line 1917 "y.tab.c"
    break;

  case 37: /* EXPR_NOT: EXPR_ARIT  */
#line 572 "sintatica.y"
                    {
		yyval.label = yyvsp[0].label;
		yyval.traducao = yyvsp[0].traducao;
	}
#line 1926 "y.tab.c"
    break;

  case 38: /* EXPR_ATOM: '(' EXPR ')'  */
#line 578 "sintatica.y"
                                {
		yyval.label = yyvsp[-1].label;
		yyval.traducao = yyvsp[-1].traducao;
	}
#line 1935 "y.tab.c"
    break;

  case 39: /* EXPR_ATOM: '-' EXPR_ATOM  */
#line 582 "sintatica.y"
                                     {
	string temp = "t" + to_string(tempVar);
	stringstream ss;
	ss << "\t" << temp << " = -" << yyvsp[0].label << ";\n";
	yyval.label = temp;
	yyval.traducao = yyvsp[0].traducao + ss.str();

	// Inferir tipo baseado em $2
	string tipo = tabela_simbolos[yyvsp[0].label].tipo;
	adicionaVar(temp, tipo, true);
	}
#line 1951 "y.tab.c"
    break;

  case 40: /* EXPR_ATOM: TK_NUM  */
#line 593 "sintatica.y"
                 {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << "\t" << temp << " = " << yyvsp[0].traducao << ";\n";
		yyval.label = temp;
		yyval.traducao = ss.str();

		// Inferir tipo
		string tipo = (yyvsp[0].traducao.find('.') != string::npos) ? "float" : "int";
					

		adicionaVar(temp, tipo, true);
	}
#line 1969 "y.tab.c"
    break;

  case 41: /* EXPR_ATOM: TK_ID  */
#line 606 "sintatica.y"
                {
		if (tabela_simbolos.find(yyvsp[0].label) == tabela_simbolos.end()) {
			cout << "Erro: Variável " << yyvsp[0].label << " não declarada.\n";
			exit(1);
		}
		yyval.label = yyvsp[0].label;
		yyval.traducao = "";
	}
#line 1982 "y.tab.c"
    break;

  case 42: /* EXPR_ATOM: COVERT_TYPE  */
#line 614 "sintatica.y"
                      {
		yyval.label = yyvsp[0].label;
		yyval.traducao = yyvsp[0].traducao;
	}
#line 1991 "y.tab.c"
    break;

  case 43: /* EXPR_ATOM: TK_BOOL_TRUE  */
#line 618 "sintatica.y"
                       {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << "\t" << temp << " = 1;\n";
		yyval.label = temp;
		yyval.traducao = ss.str();
		adicionaVar(temp, "bool", true);
	}
#line 2004 "y.tab.c"
    break;

  case 44: /* EXPR_ATOM: TK_BOOL_FALSE  */
#line 626 "sintatica.y"
                        {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << "\t" << temp << " = 0;\n";
		yyval.label = temp;
		yyval.traducao = ss.str();
		adicionaVar(temp, "bool", true);
	}
#line 2017 "y.tab.c"
    break;

  case 45: /* COVERT_TYPE: TK_TIPO_INT '(' EXPR ')'  */
#line 636 "sintatica.y"
                                 {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << "\t" << temp << " = (int)" << tabela_simbolos[yyvsp[-1].label].endereco_memoria << ";\n";
		yyval.label = temp;
		yyval.traducao = yyvsp[-1].traducao + ss.str();
		adicionaVar(temp, "int", true);
	}
#line 2030 "y.tab.c"
    break;

  case 46: /* COVERT_TYPE: TK_TIPO_FLOAT '(' EXPR ')'  */
#line 644 "sintatica.y"
                                     {
		string temp = "t" + to_string(tempVar);
		stringstream ss;
		ss << "\t" << temp << " = (float)" << tabela_simbolos[yyvsp[-1].label].endereco_memoria << ";\n";
		yyval.label = temp;
		yyval.traducao = yyvsp[-1].traducao + ss.str();
		adicionaVar(temp, "float", true);
	}
#line 2043 "y.tab.c"
    break;


#line 2047 "y.tab.c"

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

#line 653 "sintatica.y"


#include "lex.yy.c"

int yyparse();

int main(int argc, char* argv[]) {
	yyparse();
	return 0;
}

void yyerror(string MSG) {
	cout << "Erro sintático: " << MSG << "na linha: " << numLinha << endl;
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

