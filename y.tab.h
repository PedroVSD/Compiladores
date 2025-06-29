/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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
