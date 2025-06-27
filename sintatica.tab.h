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

#ifndef YY_YY_SINTATICA_TAB_H_INCLUDED
# define YY_YY_SINTATICA_TAB_H_INCLUDED
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
    UMINUS = 289,                  /* UMINUS  */
    LOWER_THAN_ELSE = 290          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SINTATICA_TAB_H_INCLUDED  */
