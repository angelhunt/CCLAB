/* A Bison parser, made by GNU Bison 1.875d.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     FLOAT = 259,
     ID = 260,
     SEMI = 261,
     COMMA = 262,
     DOT = 263,
     ASSIGNOP = 264,
     RELOP = 265,
     MINUS = 266,
     PLUS = 267,
     STAR = 268,
     DIV = 269,
     AND = 270,
     OR = 271,
     NOT = 272,
     TYPE = 273,
     STRUCT = 274,
     LP = 275,
     RP = 276,
     LB = 277,
     RB = 278,
     LC = 279,
     RC = 280,
     RETURN = 281,
     IF = 282,
     ELSE = 283,
     WHILE = 284,
     UNKNOWN = 285,
     LOWER_THAN_ELSE = 286,
     NEG = 287
   };
#endif
#define INT 258
#define FLOAT 259
#define ID 260
#define SEMI 261
#define COMMA 262
#define DOT 263
#define ASSIGNOP 264
#define RELOP 265
#define MINUS 266
#define PLUS 267
#define STAR 268
#define DIV 269
#define AND 270
#define OR 271
#define NOT 272
#define TYPE 273
#define STRUCT 274
#define LP 275
#define RP 276
#define LB 277
#define RB 278
#define LC 279
#define RC 280
#define RETURN 281
#define IF 282
#define ELSE 283
#define WHILE 284
#define UNKNOWN 285
#define LOWER_THAN_ELSE 286
#define NEG 287




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 15 "./syntax.y"
typedef union YYSTYPE {
    struct Node* np;
} YYSTYPE;
/* Line 1241 of yacc.c.  */
#line 105 "./syntax.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

#if ! defined (YYLTYPE) && ! defined (YYLTYPE_IS_DECLARED)
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;


