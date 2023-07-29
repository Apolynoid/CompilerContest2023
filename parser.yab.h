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

#ifndef YY_YY_PARSER_YAB_H_INCLUDED
# define YY_YY_PARSER_YAB_H_INCLUDED
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
    CONST = 258,                   /* CONST  */
    COMMA = 259,                   /* COMMA  */
    LC = 260,                      /* LC  */
    RC = 261,                      /* RC  */
    LB = 262,                      /* LB  */
    RB = 263,                      /* RB  */
    AND = 264,                     /* AND  */
    MINUS = 265,                   /* MINUS  */
    MUL = 266,                     /* MUL  */
    DIV = 267,                     /* DIV  */
    MOD = 268,                     /* MOD  */
    LP = 269,                      /* LP  */
    RP = 270,                      /* RP  */
    NOT = 271,                     /* NOT  */
    SEMICOLON = 272,               /* SEMICOLON  */
    INT = 273,                     /* INT  */
    FLOAT = 274,                   /* FLOAT  */
    VOID = 275,                    /* VOID  */
    RETURN = 276,                  /* RETURN  */
    IF = 277,                      /* IF  */
    ELSE = 278,                    /* ELSE  */
    WHILE = 279,                   /* WHILE  */
    BREAK = 280,                   /* BREAK  */
    CONTINUE = 281,                /* CONTINUE  */
    ASSIGN = 282,                  /* ASSIGN  */
    ADD = 283,                     /* ADD  */
    OR = 284,                      /* OR  */
    EQ = 285,                      /* EQ  */
    NE = 286,                      /* NE  */
    LT = 287,                      /* LT  */
    LE = 288,                      /* LE  */
    GT = 289,                      /* GT  */
    GE = 290,                      /* GE  */
    LEX_ERR = 291,                 /* LEX_ERR  */
    FOR = 292,                     /* FOR  */
    INC = 293,                     /* INC  */
    DEC = 294,                     /* DEC  */
    THEN = 295,                    /* THEN  */
    ID = 296,                      /* ID  */
    INT_LIT = 297,                 /* INT_LIT  */
    FLOAT_LIT = 298                /* FLOAT_LIT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 23 "parser.y"

    int int_val;
    float float_val;
    char* str_val;
    Node* node_val;

#line 114 "parser.yab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_YAB_H_INCLUDED  */
