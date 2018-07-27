/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this_ program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this_
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this_ special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_GRAM_TAB_H_INCLUDED
# define YY_YY_GRAM_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOKEN_BEGIN = 258,
    TOKEN_END = 259,
    TOKEN_GLOBAL = 260,
    TOKEN_FROM = 261,
    TOKEN_IMPORT = 262,
    TOKEN_DEL = 263,
    TOKEN_PASS = 264,
    TOKEN_PRINT = 265,
    TOKEN_ASSERT = 266,
    TOKEN_IF = 267,
    TOKEN_ELIF = 268,
    TOKEN_ELSE = 269,
    TOKEN_FOR = 270,
    TOKEN_WHILE = 271,
    TOKEN_IN = 272,
    TOKEN_CONTINUE = 273,
    TOKEN_BREAK = 274,
    TOKEN_RETURN = 275,
    TOKEN_TRY = 276,
    TOKEN_EXCEPT = 277,
    TOKEN_AS = 278,
    TOKEN_FINALLY = 279,
    TOKEN_RAISE = 280,
    TOKEN_CLASS = 281,
    TOKEN_DEF = 282,
    TOKEN_LAMBDA = 283,
    TOKEN_DOUBLE_CONST = 284,
    TOKEN_STRING_CONST = 285,
    TOKEN_ID = 286,
    TOKEN_NONE = 287,
    TOKEN_TRUE = 288,
    TOKEN_FALSE = 289,
    TOKEN_MUL_ASSIGN = 290,
    TOKEN_DIV_ASSIGN = 291,
    TOKEN_MOD_ASSIGN = 292,
    TOKEN_ADD_ASSIGN = 293,
    TOKEN_SUB_ASSIGN = 294,
    TOKEN_LSH_ASSIGN = 295,
    TOKEN_RSH_ASSIGN = 296,
    TOKEN_AND_ASSIGN = 297,
    TOKEN_XOR_ASSIGN = 298,
    TOKEN_OR_ASSIGN = 299,
    TOKEN_OR = 300,
    TOKEN_AND = 301,
    TOKEN_IS = 302,
    TOKEN_EQ = 303,
    TOKEN_NE = 304,
    TOKEN_LE = 305,
    TOKEN_GE = 306,
    TOKEN_LSH = 307,
    TOKEN_RSH = 308,
    TOKEN_NOT = 309
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (lex_t *lex, ast_t **module);

#endif /* !YY_YY_GRAM_TAB_H_INCLUDED  */
