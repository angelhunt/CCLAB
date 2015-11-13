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

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1



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




/* Copy the first part of user declarations.  */
#line 2 "./syntax.y"

#include "lex.yy.c"
#include <stdio.h>
#include "parser.h"
#include "nTree.h"
#include "SDD/SDD.h"
bool error_exist = false;
/*bool isErrorOut = false;
bool le = false;
*/


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 15 "./syntax.y"
typedef union YYSTYPE {
    struct Node* np;
} YYSTYPE;
/* Line 186 of yacc.c.  */
#line 156 "./syntax.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

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


/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 180 "./syntax.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   define YYSTACK_ALLOC alloca
#  endif
# else
#  if defined (alloca) || defined (_ALLOCA_H)
#   define YYSTACK_ALLOC alloca
#  else
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYLTYPE_IS_TRIVIAL) && YYLTYPE_IS_TRIVIAL \
             && defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   174

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  38
/* YYNRULES -- Number of rules. */
#define YYNRULES  78
/* YYNRULES -- Number of states. */
#define YYNSTATES  132

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   287

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    10,    15,    16,    20,
      24,    28,    30,    34,    36,    38,    39,    46,    49,    51,
      52,    54,    56,    57,    63,    64,    70,    71,    76,    80,
      82,    85,    86,    92,    95,    98,    99,   100,   104,   106,
     107,   112,   118,   126,   127,   128,   136,   139,   142,   143,
     144,   149,   151,   155,   157,   161,   165,   169,   173,   177,
     181,   185,   189,   193,   194,   199,   202,   205,   206,   212,
     213,   218,   219,   225,   229,   231,   233,   235,   239
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      34,     0,    -1,    35,    -1,    36,    35,    -1,    -1,    -1,
      40,    39,    37,     6,    -1,    -1,    40,    38,     6,    -1,
      40,    47,    52,    -1,    40,    47,     6,    -1,    45,    -1,
      45,     7,    39,    -1,    18,    -1,    41,    -1,    -1,    19,
      43,    24,    60,    42,    25,    -1,    19,    44,    -1,     5,
      -1,    -1,     5,    -1,     5,    -1,    -1,    45,    22,     3,
      46,    23,    -1,    -1,     5,    20,    50,    48,    21,    -1,
      -1,     5,    20,    49,    21,    -1,    51,     7,    50,    -1,
      51,    -1,    40,    45,    -1,    -1,    24,    60,    54,    53,
      25,    -1,     1,    25,    -1,    55,    54,    -1,    -1,    -1,
      65,    56,     6,    -1,    52,    -1,    -1,    26,    65,    57,
       6,    -1,    27,    20,    65,    21,    55,    -1,    27,    20,
      65,    21,    55,    28,    55,    -1,    -1,    -1,    29,    20,
      65,    58,    21,    59,    55,    -1,     1,     6,    -1,    61,
      60,    -1,    -1,    -1,    40,    63,    62,     6,    -1,    64,
      -1,    64,     7,    63,    -1,    45,    -1,    45,     9,    65,
      -1,    65,     9,    65,    -1,    65,    15,    65,    -1,    65,
      16,    65,    -1,    65,    10,    65,    -1,    65,    12,    65,
      -1,    65,    11,    65,    -1,    65,    13,    65,    -1,    65,
      14,    65,    -1,    -1,    20,    65,    66,    21,    -1,    11,
      65,    -1,    17,    65,    -1,    -1,     5,    20,    70,    67,
      21,    -1,    -1,     5,    20,    68,    21,    -1,    -1,    65,
      22,    65,    69,    23,    -1,    65,     8,     5,    -1,     5,
      -1,     3,    -1,     4,    -1,    65,     7,    70,    -1,    65,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,    51,    51,    65,    72,    80,    80,    88,    88,    96,
     103,   112,   119,   132,   139,   148,   148,   156,   165,   172,
     179,   192,   199,   199,   209,   209,   218,   218,   229,   236,
     245,   258,   258,   267,   270,   277,   285,   285,   293,   300,
     300,   308,   315,   322,   322,   322,   329,   336,   343,   350,
     350,   360,   367,   376,   384,   397,   404,   411,   418,   425,
     432,   439,   446,   453,   453,   461,   468,   475,   475,   483,
     483,   491,   491,   499,   506,   513,   520,   529,   536
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "ID", "SEMI", "COMMA",
  "DOT", "ASSIGNOP", "RELOP", "MINUS", "PLUS", "STAR", "DIV", "AND", "OR",
  "NOT", "TYPE", "STRUCT", "LP", "RP", "LB", "RB", "LC", "RC", "RETURN",
  "IF", "ELSE", "WHILE", "UNKNOWN", "LOWER_THAN_ELSE", "NEG", "$accept",
  "Program", "ExtDefList", "ExtDef", "@1", "@2", "ExtDecList", "Specifier",
  "StructSpecifier", "@3", "OptTag", "Tag", "VarDec", "@4", "FunDec", "@5",
  "@6", "VarList", "ParamDec", "CompSt", "@7", "StmtList", "Stmt", "@8",
  "@9", "@10", "@11", "DefList", "Def", "@12", "DecList", "Dec", "Exp",
  "@13", "@14", "@15", "@16", "Args", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    33,    34,    35,    35,    37,    36,    38,    36,    36,
      36,    39,    39,    40,    40,    42,    41,    41,    43,    43,
      44,    45,    46,    45,    48,    47,    49,    47,    50,    50,
      51,    53,    52,    52,    54,    54,    56,    55,    55,    57,
      55,    55,    55,    58,    59,    55,    55,    60,    60,    62,
      61,    63,    63,    64,    64,    65,    65,    65,    65,    65,
      65,    65,    65,    66,    65,    65,    65,    67,    65,    68,
      65,    69,    65,    65,    65,    65,    65,    70,    70
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     2,     0,     0,     4,     0,     3,     3,
       3,     1,     3,     1,     1,     0,     6,     2,     1,     0,
       1,     1,     0,     5,     0,     5,     0,     4,     3,     1,
       2,     0,     5,     2,     2,     0,     0,     3,     1,     0,
       4,     5,     7,     0,     0,     7,     2,     2,     0,     0,
       4,     1,     3,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     0,     4,     2,     2,     0,     5,     0,
       4,     0,     5,     3,     1,     1,     1,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       4,    13,    19,     0,     2,     4,     7,    14,    20,     0,
      17,     1,     3,    21,     0,     5,    11,     0,    48,    26,
       8,     0,     0,     0,     0,    10,    48,     9,     0,    15,
      48,     0,     0,    24,    29,     6,    21,    12,    22,    33,
       0,    53,    49,    51,     0,    47,    30,    27,     0,     0,
       0,     0,    75,    76,    74,     0,     0,     0,     0,     0,
       0,    38,    31,     0,    36,     0,     0,     0,    16,    25,
      28,    23,    46,    69,    65,    66,    63,    39,     0,     0,
       0,    34,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    54,    50,    52,    78,     0,    67,     0,
       0,     0,    43,    32,    73,    55,    58,    60,    59,    61,
      62,    56,    57,    71,    37,     0,    70,     0,    64,    40,
       0,     0,     0,    77,    68,    41,    44,    72,     0,     0,
      42,    45
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     3,     4,     5,    21,    14,    15,    28,     7,    44,
       9,    10,    16,    50,    17,    48,    32,    33,    34,    61,
      80,    62,    63,    92,   100,   121,   129,    29,    30,    66,
      42,    43,    64,    99,   117,    97,   122,    98
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -56
static const short int yypact[] =
{
      -3,   -56,    16,    39,   -56,    -3,    40,   -56,    20,    22,
     -56,   -56,   -56,    27,    44,   -56,    -2,    13,    -3,    -3,
     -56,    50,    53,    64,    45,   -56,    -3,   -56,    53,   -56,
      -3,    53,    52,   -56,    62,   -56,   -56,   -56,   -56,   -56,
      37,     0,   -56,    76,    46,   -56,    65,   -56,    63,    -3,
      66,     2,   -56,   -56,    71,    75,    75,    75,    75,    86,
      87,   -56,   -56,    37,   119,    75,    82,    53,   -56,   -56,
     -56,   -56,   -56,    75,     4,     4,   119,   119,    75,    75,
      83,   -56,   105,    75,    75,    75,    75,    75,    75,    75,
      75,    75,   103,   119,   -56,   -56,    89,   100,   -56,   101,
     117,   104,   119,   -56,   -56,   119,   152,    68,    68,     4,
       4,   145,   132,   119,   -56,    75,   -56,   115,   -56,   -56,
      48,   116,   125,   -56,   -56,    96,   -56,   -56,    48,    48,
     -56,   -56
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
     -56,   -56,   133,   -56,   -56,   -56,   127,     6,   -56,   -56,
     -56,   -56,   -24,   -56,   -56,   -56,   -56,    90,   -56,   134,
     -56,    98,   -35,   -56,   -56,   -56,   -56,   -13,   -56,   -56,
      85,   -56,   -55,   -56,   -56,   -56,   -56,    35
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -36
static const short int yytable[] =
{
      74,    75,    76,    77,    41,    22,     6,    46,    72,    65,
      93,     6,    82,    40,    24,     1,     2,    45,    96,    25,
      23,     8,    23,   101,   102,    31,    91,    39,   105,   106,
     107,   108,   109,   110,   111,   112,   113,    26,    51,    11,
      52,    53,    54,    41,   -18,    13,    18,    19,    55,    51,
      20,    52,    53,    54,    56,    31,    35,    57,    36,    55,
      96,    26,   -35,    58,    59,    56,    60,    38,    57,    49,
      39,    68,    26,    47,    58,    59,    82,    60,    52,    53,
      54,    87,    88,    67,    69,   125,    55,    23,    94,    71,
      91,    73,    56,   130,   131,    57,   115,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    78,    79,   103,   114,
     104,    91,    82,    83,    84,    85,    86,    87,    88,    89,
      90,   116,   118,   119,   128,   120,    91,    82,    83,    84,
      85,    86,    87,    88,    89,    90,   124,   126,    12,    70,
      82,    91,    84,    85,    86,    87,    88,    89,   127,    37,
     123,    27,    95,    82,    91,    84,    85,    86,    87,    88,
      82,    81,     0,    85,    86,    87,    88,    91,     0,     0,
       0,     0,     0,     0,    91
};

static const short int yycheck[] =
{
      55,    56,    57,    58,    28,     7,     0,    31,     6,     9,
      65,     5,     8,    26,     1,    18,    19,    30,    73,     6,
      22,     5,    22,    78,    79,    19,    22,    25,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    24,     1,     0,
       3,     4,     5,    67,    24,     5,    24,    20,    11,     1,
       6,     3,     4,     5,    17,    49,     6,    20,     5,    11,
     115,    24,    25,    26,    27,    17,    29,     3,    20,     7,
      25,    25,    24,    21,    26,    27,     8,    29,     3,     4,
       5,    13,    14,     7,    21,   120,    11,    22,     6,    23,
      22,    20,    17,   128,   129,    20,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    20,    20,    25,     6,
       5,    22,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    21,    21,     6,    28,    21,    22,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    21,    21,     5,    49,
       8,    22,    10,    11,    12,    13,    14,    15,    23,    22,
     115,    17,    67,     8,    22,    10,    11,    12,    13,    14,
       8,    63,    -1,    11,    12,    13,    14,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    22
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    18,    19,    34,    35,    36,    40,    41,     5,    43,
      44,     0,    35,     5,    38,    39,    45,    47,    24,    20,
       6,    37,     7,    22,     1,     6,    24,    52,    40,    60,
      61,    40,    49,    50,    51,     6,     5,    39,     3,    25,
      60,    45,    63,    64,    42,    60,    45,    21,    48,     7,
      46,     1,     3,     4,     5,    11,    17,    20,    26,    27,
      29,    52,    54,    55,    65,     9,    62,     7,    25,    21,
      50,    23,     6,    20,    65,    65,    65,    65,    20,    20,
      53,    54,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    22,    56,    65,     6,    63,    65,    68,    70,    66,
      57,    65,    65,    25,     5,    65,    65,    65,    65,    65,
      65,    65,    65,    65,     6,     7,    21,    67,    21,     6,
      21,    58,    69,    70,    21,    55,    21,    23,    28,    59,
      55,    55
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)		\
   ((Current).first_line   = (Rhs)[1].first_line,	\
    (Current).first_column = (Rhs)[1].first_column,	\
    (Current).last_line    = (Rhs)[N].last_line,	\
    (Current).last_column  = (Rhs)[N].last_column)
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value, Location);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if defined (YYMAXDEPTH) && YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;
  (void) yylocationp;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yytype, yyvaluep, yylocationp)
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;
  (void) yylocationp;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  register short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  YYLTYPE *yylerrsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short int *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
  *++yylsp = yylloc;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, yylsp - yylen, yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 51 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[0].first_line;
        yyval.np = NewNode(Program, 0, &data); 
        TreeInsert(yyval.np, 1, yyvsp[0].np);
        #ifdef DEBUG
        if(error_exist == false)
            DFS(yyval.np, 0);
        #endif
        SDD(yyval.np);
        ;}
    break;

  case 3:
#line 65 "./syntax.y"
    { 
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-1].first_line;
        yyval.np = NewNode(ExtDefList, 0, &data);
        TreeInsert(yyval.np, 2, yyvsp[-1].np, yyvsp[0].np);
        ;}
    break;

  case 4:
#line 72 "./syntax.y"
    { Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = -1;
        yyval.np = NewNode(ExtDefList, 1, &data);
        ;}
    break;

  case 5:
#line 80 "./syntax.y"
    { et = MISSSEMI; ;}
    break;

  case 6:
#line 80 "./syntax.y"
    {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-3].first_line;
        yyval.np = NewNode(ExtDef, 0, &data);
        TreeInsert(yyval.np, 3, yyvsp[-3].np, yyvsp[-2].np, yyvsp[0].np);
       ;}
    break;

  case 7:
#line 88 "./syntax.y"
    { et = MISSSEMI; ;}
    break;

  case 8:
#line 88 "./syntax.y"
    {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-2].first_line;
        yyval.np = NewNode(ExtDef, 1, &data); 
        TreeInsert(yyval.np, 2, yyvsp[-2].np, yyvsp[0].np);
        ;}
    break;

  case 9:
#line 96 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-2].first_line;
        yyval.np = NewNode(ExtDef, 2, &data); 
        TreeInsert(yyval.np, 3, yyvsp[-2].np, yyvsp[-1].np, yyvsp[0].np);
        ;}
    break;

  case 10:
#line 103 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-2].first_line;
        yyval.np = NewNode(ExtDef, 2, &data); 
        TreeInsert(yyval.np, 3, yyvsp[-2].np, yyvsp[-1].np, yyvsp[0].np);
        ;}
    break;

  case 11:
#line 112 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[0].first_line;
        yyval.np = NewNode(ExtDecList, 0, &data);
        TreeInsert(yyval.np, 1, yyvsp[0].np);
        ;}
    break;

  case 12:
#line 119 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-2].first_line;
        yyval.np = NewNode(ExtDecList, 1, &data);
        TreeInsert(yyval.np, 3, yyvsp[-2].np, yyvsp[-2].np, yyvsp[0].np);
        ;}
    break;

  case 13:
#line 132 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[0].first_line;
        yyval.np = NewNode(Specifier, 0, &data); 
        TreeInsert(yyval.np, 1, yyvsp[0].np);
        ;}
    break;

  case 14:
#line 139 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[0].first_line;
        yyval.np = NewNode(Specifier, 1, &data);
        TreeInsert(yyval.np, 1, yyvsp[0].np);
        ;}
    break;

  case 15:
#line 148 "./syntax.y"
    {et = MISSRC;;}
    break;

  case 16:
#line 148 "./syntax.y"
    {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-5].first_line;
        yyval.np = NewNode(StructSpecifier, 0, &data); 
        TreeInsert(yyval.np, 5, yyvsp[-5].np, yyvsp[-4].np, yyvsp[-3].np, yyvsp[-2].np, yyvsp[0].np);
        ;}
    break;

  case 17:
#line 156 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-1].first_line;
        yyval.np = NewNode(StructSpecifier, 1, &data);
        TreeInsert(yyval.np, 2, yyvsp[-1].np, yyvsp[0].np);
        ;}
    break;

  case 18:
#line 165 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[0].first_line;
        yyval.np = NewNode(OptTag, 0, &data);
        TreeInsert(yyval.np, 1, yyvsp[0].np);
        ;}
    break;

  case 19:
#line 172 "./syntax.y"
    { Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = -1;
        yyval.np = NewNode(OptTag, 1, &data);
        ;}
    break;

  case 20:
#line 179 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[0].first_line;
        yyval.np = NewNode(Tag, 0, &data);
        TreeInsert(yyval.np, 1, yyvsp[0].np);
        ;}
    break;

  case 21:
#line 192 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[0].first_line;
        yyval.np = NewNode(VarDec, 0, &data);
        TreeInsert(yyval.np, 1, yyvsp[0].np);
        ;}
    break;

  case 22:
#line 199 "./syntax.y"
    {et = MISSRB; ;}
    break;

  case 23:
#line 199 "./syntax.y"
    {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-4].first_line;
        yyval.np = NewNode(VarDec, 1, &data);
        TreeInsert(yyval.np, 4, yyvsp[-4].np, yyvsp[-3].np, yyvsp[-2].np, yyvsp[0].np);
        ;}
    break;

  case 24:
#line 209 "./syntax.y"
    { et = MISSRP; ;}
    break;

  case 25:
#line 209 "./syntax.y"
    {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-4].first_line;
        yyval.np = NewNode(FunDec, 0, &data);
        TreeInsert(yyval.np, 4, yyvsp[-4].np, yyvsp[-3].np, yyvsp[-2].np, yyvsp[0].np);
        et = B;
       ;}
    break;

  case 26:
#line 218 "./syntax.y"
    { et = MISSRP; ;}
    break;

  case 27:
#line 218 "./syntax.y"
    {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-3].first_line;
        yyval.np = NewNode(FunDec, 1, &data);
        TreeInsert(yyval.np, 3, yyvsp[-3].np, yyvsp[-2].np, yyvsp[0].np);
        et = B;
    ;}
    break;

  case 28:
#line 229 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-2].first_line;
        yyval.np = NewNode(VarList, 0, &data);
        TreeInsert(yyval.np, 3, yyvsp[-2].np, yyvsp[-1].np, yyvsp[0].np);
        ;}
    break;

  case 29:
#line 236 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[0].first_line;
        yyval.np = NewNode(VarList, 1, &data);
        TreeInsert(yyval.np, 1, yyvsp[0].np);
    ;}
    break;

  case 30:
#line 245 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-1].first_line;
        yyval.np = NewNode(ParamDec, 0, &data);
        TreeInsert(yyval.np, 2, yyvsp[-1].np, yyvsp[0].np);
         ;}
    break;

  case 31:
#line 258 "./syntax.y"
    {et = MISSRC; ;}
    break;

  case 32:
#line 258 "./syntax.y"
    {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-2].first_line;
        yyval.np = NewNode(CompSt, 0, &data);
        TreeInsert(yyval.np, 4, yyvsp[-4].np, yyvsp[-3].np, yyvsp[-2].np, yyvsp[0].np);
        et = B;
       ;}
    break;

  case 34:
#line 270 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-1].first_line;
        yyval.np = NewNode(StmtList, 0, &data);
        TreeInsert(yyval.np, 2, yyvsp[-1].np, yyvsp[0].np);
    ;}
    break;

  case 35:
#line 277 "./syntax.y"
    { Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = -1;
        yyval.np = NewNode(StmtList, 1, &data);
        ;}
    break;

  case 36:
#line 285 "./syntax.y"
    {et = MISSSEMI; ;}
    break;

  case 37:
#line 285 "./syntax.y"
    {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-2].first_line;
        yyval.np = NewNode(Stmt, 0, &data);
        TreeInsert(yyval.np, 2, yyvsp[-2].np, yyvsp[0].np);
     ;}
    break;

  case 38:
#line 293 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[0].first_line;
        yyval.np = NewNode(Stmt, 1, &data);
        TreeInsert(yyval.np, 1, yyvsp[0].np);
        ;}
    break;

  case 39:
#line 300 "./syntax.y"
    {et = MISSSEMI; ;}
    break;

  case 40:
#line 300 "./syntax.y"
    {
        et = B; 
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-3].first_line;
        yyval.np = NewNode(Stmt, 2, &data);
        TreeInsert(yyval.np, 3, yyvsp[-3].np, yyvsp[-2].np, yyvsp[0].np);
    ;}
    break;

  case 41:
#line 308 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-4].first_line;
        yyval.np = NewNode(Stmt, 3, &data);
        TreeInsert(yyval.np, 5, yyvsp[-4].np, yyvsp[-3].np, yyvsp[-2].np, yyvsp[-1].np, yyvsp[0].np);
    ;}
    break;

  case 42:
#line 315 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-6].first_line;
        yyval.np = NewNode(Stmt, 4, &data);
        TreeInsert(yyval.np, 7, yyvsp[-6].np, yyvsp[-5].np, yyvsp[-4].np, yyvsp[-3].np, yyvsp[-2].np, yyvsp[-1].np, yyvsp[0].np);
    ;}
    break;

  case 43:
#line 322 "./syntax.y"
    { et = MISSRP; ;}
    break;

  case 44:
#line 322 "./syntax.y"
    { et = B; ;}
    break;

  case 45:
#line 322 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-6].first_line;
        yyval.np = NewNode(Stmt, 5, &data);
        TreeInsert(yyval.np, 5, yyvsp[-6].np, yyvsp[-5].np, yyvsp[-4].np, yyvsp[-2].np, yyvsp[0].np);
    ;}
    break;

  case 47:
#line 336 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-1].first_line;
        yyval.np = NewNode(DefList, 0, &data);
        TreeInsert(yyval.np, 2, yyvsp[-1].np, yyvsp[0].np);
    ;}
    break;

  case 48:
#line 343 "./syntax.y"
    { Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = -1;
        yyval.np = NewNode(DefList, 1, &data);
        ;}
    break;

  case 49:
#line 350 "./syntax.y"
    { et = MISSSEMI; ;}
    break;

  case 50:
#line 350 "./syntax.y"
    {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-3].first_line;
        yyval.np = NewNode(Def, 0, &data);
        TreeInsert(yyval.np, 3, yyvsp[-3].np, yyvsp[-2].np, yyvsp[0].np);
    ;}
    break;

  case 51:
#line 360 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[0].first_line;
        yyval.np = NewNode(DecList, 0, &data);
        TreeInsert(yyval.np, 1, yyvsp[0].np);
        ;}
    break;

  case 52:
#line 367 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-2].first_line;
        yyval.np = NewNode(DecList, 1, &data);
        TreeInsert(yyval.np, 3, yyvsp[-2].np, yyvsp[-1].np, yyvsp[0].np);
    ;}
    break;

  case 53:
#line 376 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[0].first_line;
        yyval.np = NewNode(Dec, 0, &data);
        TreeInsert(yyval.np, 1, yyvsp[0].np);
        
    ;}
    break;

  case 54:
#line 384 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-2].first_line;
        yyval.np = NewNode(Dec, 1, &data);
        TreeInsert(yyval.np, 3, yyvsp[-2].np, yyvsp[-1].np, yyvsp[0].np);
    ;}
    break;

  case 55:
#line 397 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-2].first_line;
        yyval.np = NewNode(Exp, 0, &data);
        TreeInsert(yyval.np, 3, yyvsp[-2].np, yyvsp[-1].np, yyvsp[0].np);
    ;}
    break;

  case 56:
#line 404 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-2].first_line;
        yyval.np = NewNode(Exp, 1, &data);
        TreeInsert(yyval.np, 3, yyvsp[-2].np, yyvsp[-1].np, yyvsp[0].np);
    ;}
    break;

  case 57:
#line 411 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-2].first_line;
        yyval.np = NewNode(Exp, 2, &data);
        TreeInsert(yyval.np, 3, yyvsp[-2].np, yyvsp[-1].np, yyvsp[0].np);
    ;}
    break;

  case 58:
#line 418 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-2].first_line;
        yyval.np = NewNode(Exp, 3, &data);
        TreeInsert(yyval.np, 3, yyvsp[-2].np, yyvsp[-1].np, yyvsp[0].np);
    ;}
    break;

  case 59:
#line 425 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-2].first_line;
        yyval.np = NewNode(Exp, 4, &data);
        TreeInsert(yyval.np, 3, yyvsp[-2].np, yyvsp[-1].np, yyvsp[0].np);
    ;}
    break;

  case 60:
#line 432 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-2].first_line;
        yyval.np = NewNode(Exp, 5, &data);
        TreeInsert(yyval.np, 3, yyvsp[-2].np, yyvsp[-1].np, yyvsp[0].np);
    ;}
    break;

  case 61:
#line 439 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-2].first_line;
        yyval.np = NewNode(Exp, 6, &data);
        TreeInsert(yyval.np, 3, yyvsp[-2].np, yyvsp[-1].np, yyvsp[0].np);
    ;}
    break;

  case 62:
#line 446 "./syntax.y"
    {
       Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-2].first_line;
        yyval.np = NewNode(Exp, 7, &data);
        TreeInsert(yyval.np, 3, yyvsp[-2].np, yyvsp[-1].np, yyvsp[0].np);
    ;}
    break;

  case 63:
#line 453 "./syntax.y"
    {et = MISSRP; ;}
    break;

  case 64:
#line 453 "./syntax.y"
    {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-3].first_line;
        yyval.np = NewNode(Exp, 8, &data);
        TreeInsert(yyval.np, 3, yyvsp[-3].np, yyvsp[-2].np, yyvsp[0].np);
    ;}
    break;

  case 65:
#line 461 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-1].first_line;
        yyval.np = NewNode(Exp, 9, &data);
        TreeInsert(yyval.np, 2, yyvsp[-1].np, yyvsp[0].np);
    ;}
    break;

  case 66:
#line 468 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-1].first_line;
        yyval.np = NewNode(Exp, 10, &data);
        TreeInsert(yyval.np, 2, yyvsp[-1].np, yyvsp[0].np);
    ;}
    break;

  case 67:
#line 475 "./syntax.y"
    { et = MISSRP; ;}
    break;

  case 68:
#line 475 "./syntax.y"
    {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-4].first_line;
        yyval.np = NewNode(Exp, 11, &data);
        TreeInsert(yyval.np, 4, yyvsp[-4].np, yyvsp[-3].np, yyvsp[-2].np, yyvsp[0].np);
    ;}
    break;

  case 69:
#line 483 "./syntax.y"
    { et = MISSRP; ;}
    break;

  case 70:
#line 483 "./syntax.y"
    {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-3].first_line;
        yyval.np = NewNode(Exp, 12, &data);
        TreeInsert(yyval.np, 3, yyvsp[-3].np, yyvsp[-2].np, yyvsp[0].np);
    ;}
    break;

  case 71:
#line 491 "./syntax.y"
    { et = MISSRB; ;}
    break;

  case 72:
#line 491 "./syntax.y"
    {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-4].first_line;
        yyval.np = NewNode(Exp, 13, &data);
        TreeInsert(yyval.np, 4, yyvsp[-4].np, yyvsp[-3].np, yyvsp[-2].np, yyvsp[0].np);
    ;}
    break;

  case 73:
#line 499 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-2].first_line;
        yyval.np = NewNode(Exp, 14, &data);
        TreeInsert(yyval.np, 3, yyvsp[-2].np, yyvsp[-1].np, yyvsp[0].np);
    ;}
    break;

  case 74:
#line 506 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[0].first_line;
        yyval.np = NewNode(Exp, 15, &data);
        TreeInsert(yyval.np, 1, yyvsp[0].np);
    ;}
    break;

  case 75:
#line 513 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[0].first_line;
        yyval.np = NewNode(Exp, 16, &data);
        TreeInsert(yyval.np, 1, yyvsp[0].np);
    ;}
    break;

  case 76:
#line 520 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[0].first_line;
        yyval.np = NewNode(Exp, 17, &data);
        TreeInsert(yyval.np, 1, yyvsp[0].np);
    ;}
    break;

  case 77:
#line 529 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[-2].first_line;
        yyval.np = NewNode(Args, 0, &data);
        TreeInsert(yyval.np, 3, yyvsp[-2].np, yyvsp[-1].np, yyvsp[0].np);
     ;}
    break;

  case 78:
#line 536 "./syntax.y"
    {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = yylsp[0].first_line;
        yyval.np = NewNode(Args, 1, &data);
        TreeInsert(yyval.np, 1, yyvsp[0].np);
    ;}
    break;


    }

/* Line 1010 of yacc.c.  */
#line 1950 "./syntax.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;
  yylsp -= yylen;

  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }

  yylerrsp = yylsp;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {
		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
		 yydestruct (yystos[*yyssp], yyvsp, yylsp);
	       }
        }
      else
	{
	  YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
	  yydestruct (yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	  *++yylerrsp = yylloc;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

  yyvsp -= yylen;
  yyssp -= yylen;
  yystate = *yyssp;
  yylerrsp = yylsp;
  *++yylerrsp = yyloc;
  yylsp -= yylen;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
  YYLLOC_DEFAULT (yyloc, yylsp, yylerrsp - yylsp);
  *++yylsp = yyloc;

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 546 "./syntax.y"


