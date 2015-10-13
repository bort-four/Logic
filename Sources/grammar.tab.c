/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Skeleton implementation for Bison GLR parsers in C

   Copyright (C) 2002-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* C GLR parser skeleton written by Paul Hilfinger.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "glr.c"

/* Pure parsers.  */
#define YYPURE 0






/* First part of user declarations.  */
#line 3 "grammar.y" /* glr.c:240  */

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#include "Parser.h"
	#include "Logic.h"
	int  yylex(Source* sourcePtr);
	void yyerror(Source* sourcePtr, ParserNode* parseTreePtr,
				Vector* errVectPtr, char const *msg);
	
	#define addErrorOnBegin(msg, loc)                                          \
	{                                                                          \
		Error error = createParserError((msg), sourcePtr,                      \
							(loc).first_line, (loc).first_column);             \
		addBack(*errVectPtr, Error, error);                                    \
	}

	#define addErrorOnEnd(msg, loc)                                            \
	{                                                                          \
		Error error = createParserError((msg), sourcePtr,                      \
							(loc).last_line, (loc).last_column);               \
		addBack(*errVectPtr, Error, error);                                    \
	}
	
	#define setNullNode(ndPtr, loc)                                            \
	{                                                                          \
		(ndPtr)                                                                \
			= createNode(ND_NULL, NULL, (loc).first_line, (loc).first_column); \
	}
	

#line 87 "grammar.tab.c" /* glr.c:240  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NAME = 258,
    DECLARATIONS_TITLE = 259,
    FACTS_TITLE = 260,
    RESTRICTIONS_TITLE = 261,
    SINGLE_FACT = 262,
    SINGLE_AXIOM = 263,
    SINGLE_RESTRICTION = 264,
    SINGLE_DECLARATION = 265,
    ALL = 266,
    EXT = 267,
    REAL = 268,
    INTEGER = 269,
    QUANT = 270,
    ARROW = 271,
    ARROW_IMP = 272,
    ARROW_EQ = 273,
    LES_OR_EQ = 274,
    MORE_OR_EQ = 275,
    NEG = 276,
    BRAC = 277,
    FUNC = 278,
    UNAR_MINUS = 279
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef  ParserNode*  YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (Source* sourcePtr, ParserNode* parseTreePtr, Vector* errVectPtr);


/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Default (constant) value used for initialization for null
   right-hand sides.  Unlike the standard yacc.c template, here we set
   the default value of $$ to a zeroed-out value.  Since the default
   value is undefined, this behavior is technically correct.  */
static YYSTYPE yyval_default;
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;

/* Copy the second part of user declarations.  */

#line 183 "grammar.tab.c" /* glr.c:263  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#ifndef YYFREE
# define YYFREE free
#endif
#ifndef YYMALLOC
# define YYMALLOC malloc
#endif
#ifndef YYREALLOC
# define YYREALLOC realloc
#endif

#define YYSIZEMAX ((size_t) -1)

#ifdef __cplusplus
   typedef Boolean yybool;
#else
   typedef unsigned char yybool;
#endif
#define yytrue 1
#define yyfalse 0

#ifndef YYSETJMP
# include <setjmp.h>
# define YYJMP_BUF jmp_buf
# define YYSETJMP(Env) setjmp (Env)
/* Pacify clang.  */
# define YYLONGJMP(Env, Val) (longjmp (Env, Val), YYASSERT (0))
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#ifndef YYASSERT
# define YYASSERT(Condition) ((void) ((Condition) || (abort (), 0)))
#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  51
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   373

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  129
/* YYNRULES -- Number of states.  */
#define YYNSTATES  219
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule.  */
#define YYMAXRHS 8
/* YYMAXLEFT -- Maximum number of symbols to the left of a handle
   accessed by $0, $-1, etc., in any rule.  */
#define YYMAXLEFT 0

/* YYTRANSLATE(X) -- Bison symbol number corresponding to X.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   279

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,     2,     2,    28,    23,     2,
      30,    31,    26,    24,    37,    25,     2,    27,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    38,    36,
      40,    16,    41,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    29,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    22,     2,     2,     2,     2,     2,
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
      15,    17,    18,    19,    20,    21,    32,    33,    34,    35
};

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,    71,    71,    72,    73,    74,    75,    76,    81,    88,
      95,   108,   109,   113,   114,   118,   119,   124,   129,   130,
     134,   139,   140,   144,   149,   150,   154,   159,   160,   166,
     173,   189,   190,   198,   199,   200,   205,   212,   221,   227,
     233,   239,   248,   249,   250,   258,   259,   265,   266,   274,
     275,   276,   281,   282,   286,   286,   286,   289,   293,   298,
     304,   314,   320,   328,   334,   343,   350,   363,   364,   365,
     373,   374,   375,   376,   388,   395,   407,   412,   417,   418,
     425,   443,   448,   454,   459,   466,   467,   472,   481,   482,
     492,   493,   500,   507,   514,   521,   529,   530,   539,   540,
     545,   546,   547,   554,   561,   568,   575,   582,   589,   594,
     595,   606,   629,   655,   659,   668,   669,   670,   671,   679,
     683,   684,   689,   695,   701,   707,   713,   719,   726,   733
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NAME", "DECLARATIONS_TITLE",
  "FACTS_TITLE", "RESTRICTIONS_TITLE", "SINGLE_FACT", "SINGLE_AXIOM",
  "SINGLE_RESTRICTION", "SINGLE_DECLARATION", "ALL", "EXT", "REAL",
  "INTEGER", "QUANT", "'='", "ARROW", "ARROW_IMP", "ARROW_EQ", "LES_OR_EQ",
  "MORE_OR_EQ", "'|'", "'&'", "'+'", "'-'", "'*'", "'/'", "'%'", "'^'",
  "'('", "')'", "NEG", "BRAC", "FUNC", "UNAR_MINUS", "';'", "','", "':'",
  "'!'", "'<'", "'>'", "$accept", "input", "query", "query_param_list",
  "query_param", "query_result", "single_decl", "single_fact",
  "single_axiom", "single_restr", "program", "declarations", "decls_list",
  "declaration", "name_list", "name", "facts", "fact_list",
  "fact_or_axiom", "fact", "positive_fact", "negative_fact",
  "function_fact", "const_list", "constant", "axiom", "axiom_vars",
  "var_block_list", "var_block", "premise", "result", "conjunct",
  "res_conjunct", "predicate", "function", "term_list", "term",
  "all_quant", "ext_quant", "restrictions", "restr_list", "restriction",
  "formula", YY_NULLPTR
};
#endif

#define YYPACT_NINF -54
#define YYTABLE_NINF -115

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const short int yypact[] =
{
     353,    15,   -54,   -54,    17,    86,   164,    85,    92,   -54,
     -54,   -54,   -54,   -54,   -54,     7,     8,   225,   161,   110,
      10,    26,   -54,   -54,   -54,   -54,   110,    33,   204,   264,
      75,   110,   110,   -54,   -54,   266,   184,   -54,   184,    80,
     -54,   -54,   232,   282,   184,   184,   117,   295,   170,   106,
      22,   -54,   -54,   185,   -54,    54,   -54,   -54,   -54,   150,
     -54,   239,   -54,   -54,    52,   -54,   155,   -54,   -54,   -54,
     226,   110,   266,   275,    43,   -54,   -54,   300,   155,   155,
     172,   -54,   -54,    23,   324,   -54,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   295,   295,
     -54,   184,   184,   184,   184,   -54,   -54,   175,   192,   147,
     -54,   -54,   -54,   -54,   -21,   -54,   -54,   -54,   239,    83,
     -54,   -54,   110,   110,   110,   155,   246,   -54,   310,   275,
     207,   266,   -54,   -54,   -54,   103,   340,   340,   340,   340,
     344,   344,   177,   177,   177,   177,   340,   340,   216,   108,
     -54,   -54,   -54,   180,   110,   -54,   -54,   -54,   -54,   132,
     197,    54,   118,   183,   168,   239,   -54,   -54,   -54,   136,
     -54,   -54,   105,   -54,   340,   -54,   -54,   266,   -54,   151,
     -54,   124,   239,   137,   -54,   188,   138,   -54,   -54,   239,
     -54,   -54,   -54,   275,   -54,   266,   340,   205,    12,   -54,
     -54,   -54,   -54,   -54,   -54,   -54,   -54,   163,   -54,   340,
     -54,   222,   110,   -54,   -54,   -54,   200,   -54,   -54
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,    46,    45,    33,     0,     0,     0,     0,     0,     7,
       3,     4,     5,     6,     2,    47,     0,     0,    46,     0,
       0,     0,    54,    55,    56,    24,     0,     0,     0,    73,
      70,     0,     0,    72,    71,     0,     0,    26,     0,     0,
     100,   120,   101,     0,     0,     0,     0,   119,    46,     0,
       0,     1,    49,   113,     9,     0,    46,    34,    35,     0,
      59,     0,    22,    20,     0,    42,    76,    78,    25,    23,
      73,     0,     0,     0,     0,    81,    85,     0,   111,   112,
      73,   101,   108,     0,     0,   121,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   127,   128,
      28,     0,     0,     0,     0,    19,    17,     0,     0,     0,
     115,    29,    73,    70,     0,    11,    14,    63,     0,     0,
      67,    44,     0,     0,     0,    77,     0,    86,     0,     0,
       0,     0,   110,   109,   129,     0,    98,   122,    93,    94,
     102,   104,   103,   105,   107,   106,    91,    92,   126,   123,
     124,   125,    38,     0,     0,    50,    51,    52,    53,     0,
      15,     0,     0,    69,     0,     0,    43,    80,    79,     0,
      83,    88,   101,    82,    87,    97,    96,     0,    39,     0,
     116,     0,     0,     0,    12,    69,     0,    60,    58,     0,
      57,    68,    75,     0,    74,     0,    99,    44,     0,   118,
     117,    16,    10,     8,    64,    62,    61,     0,    84,    89,
      40,     0,     0,    66,    65,    41,     0,    37,    36
};

  /* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
     -54,   -54,   -54,   -54,    98,   -54,   -54,   -54,   -54,   -54,
     -54,   -54,   -54,   243,   112,     0,   -54,   -54,   -54,   176,
     -54,   -54,   -54,   166,   -53,   181,   -54,   -26,   157,   -54,
     -54,   162,   100,   -27,    -3,   -54,   -14,   -54,   -54,   -54,
     -54,   140,    -8
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const short int yydefgoto[] =
{
      -1,     8,     9,   114,   115,   183,    10,    11,    12,    13,
      14,    15,    17,    49,    64,    39,    53,   109,   156,    21,
      22,    23,    24,   119,    40,    27,    28,    66,    67,    74,
     169,    75,   170,    41,    81,   135,    43,    44,    45,   111,
     159,    46,    47
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const short int yytable[] =
{
      16,    76,   116,    42,    20,    78,    79,    50,   120,    54,
     160,    60,    52,   211,    77,   -30,   161,    50,    18,    59,
       2,    82,    83,   107,   132,    42,    65,    62,    84,   212,
      85,    65,    65,    42,    68,    42,    98,    99,    55,    87,
      61,    42,    42,    88,    89,   125,   127,    90,    91,    92,
      93,    94,    95,   121,   133,   112,    19,   113,   126,   128,
     108,   129,    63,    96,    97,   120,   130,    33,    34,    69,
      42,    65,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   163,   -13,    48,    25,     2,   122,
     123,   -13,    51,   148,   149,   150,   151,    26,    42,    42,
      42,    42,   171,    76,   175,   -45,   -90,   105,   116,    20,
      86,    56,   191,     2,   164,   128,    77,   174,   100,   185,
     165,   195,   166,   167,    65,   199,   172,    42,   -90,   201,
     103,   104,  -114,    70,   176,    30,   207,   192,   202,   205,
     177,   -90,   106,    31,    32,    33,    34,   -48,    56,   186,
       2,   117,   197,   -48,    65,   165,    42,    35,    26,   193,
     200,   -21,    36,   196,   213,    29,   171,    30,   180,   188,
     -18,    38,   194,   203,   206,    31,    32,    33,    34,   128,
     118,   209,   198,   155,   189,    70,    19,    30,   122,    35,
     172,   110,   124,   153,    36,    31,    32,    33,    34,   214,
      37,   217,   -46,    38,   190,    70,    95,    30,    70,    35,
      30,   152,   216,   182,    36,    71,   178,    33,    34,   187,
      33,    34,   154,    38,   204,   -32,    56,   -73,     2,    35,
     -32,   -32,    35,   -90,    72,   102,   218,    72,   103,   104,
     112,   210,   113,    73,   -95,   -95,    73,   132,   -95,   -95,
     -90,   -90,    33,    34,   -90,   -90,   -46,   -73,   215,   184,
      58,    57,   -95,   -90,   -27,   -95,   179,    80,   -90,    30,
      90,    91,    92,    93,    94,    95,    70,   133,    30,    33,
      34,   168,   -95,   -95,   162,   157,   -95,   -95,    33,    34,
     158,    35,   173,   208,   -46,     0,    72,     0,    87,   181,
      35,     0,    88,    89,     0,    72,    90,    91,    92,    93,
      94,    95,     0,   101,   102,     0,   131,   103,   104,     0,
      88,    89,    96,    97,    90,    91,    92,    93,    94,    95,
      88,    89,     0,     0,    90,    91,    92,    93,    94,    95,
      96,    97,   101,   102,     0,     0,   103,   104,     0,     0,
      96,    97,     0,   -31,     1,   134,     2,     3,   -31,   -31,
       4,     5,     6,     7,    90,    91,    92,    93,    94,    95,
      92,    93,    94,    95
};

static const short int yycheck[] =
{
       0,    28,    55,     6,     4,    31,    32,     7,    61,     1,
      31,     1,     5,     1,    28,     0,    37,    17,     1,    19,
       3,    35,    36,     1,     1,    28,    26,     1,    36,    17,
      38,    31,    32,    36,     1,    38,    44,    45,    30,    16,
      30,    44,    45,    20,    21,    71,    73,    24,    25,    26,
      27,    28,    29,     1,    31,     1,    39,     3,    72,    73,
      38,    18,    36,    40,    41,   118,    23,    13,    14,    36,
      73,    71,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,     1,    31,     1,     1,     3,    37,
      38,    37,     0,   101,   102,   103,   104,    11,   101,   102,
     103,   104,   129,   130,     1,    30,     1,     1,   161,   109,
      30,     1,   165,     3,    31,   129,   130,   131,     1,     1,
      37,    16,   122,   123,   124,     1,   129,   130,    23,   182,
      22,    23,     0,     1,    31,     3,   189,     1,     1,     1,
      37,    36,    36,    11,    12,    13,    14,     0,     1,    31,
       3,     1,     1,     6,   154,    37,   159,    25,    11,    23,
      36,     0,    30,   177,     1,     1,   193,     3,    36,     1,
       0,    39,    36,    36,    36,    11,    12,    13,    14,   193,
      30,   195,    31,    36,    16,     1,    39,     3,    37,    25,
     193,     6,    37,     1,    30,    11,    12,    13,    14,    36,
      36,     1,    30,    39,    36,     1,    29,     3,     1,    25,
       3,    36,   212,    16,    30,    11,    36,    13,    14,    36,
      13,    14,    30,    39,    36,     0,     1,     1,     3,    25,
       5,     6,    25,     1,    30,    19,    36,    30,    22,    23,
       1,    36,     3,    39,    18,    19,    39,     1,    22,    23,
      18,    19,    13,    14,    22,    23,    30,    31,    36,   161,
      17,    36,    36,    31,     0,     1,   154,     1,    36,     3,
      24,    25,    26,    27,    28,    29,     1,    31,     3,    13,
      14,   124,    18,    19,   118,   109,    22,    23,    13,    14,
     109,    25,   130,   193,    30,    -1,    30,    -1,    16,   159,
      25,    -1,    20,    21,    -1,    30,    24,    25,    26,    27,
      28,    29,    -1,    18,    19,    -1,    16,    22,    23,    -1,
      20,    21,    40,    41,    24,    25,    26,    27,    28,    29,
      20,    21,    -1,    -1,    24,    25,    26,    27,    28,    29,
      40,    41,    18,    19,    -1,    -1,    22,    23,    -1,    -1,
      40,    41,    -1,     0,     1,    31,     3,     4,     5,     6,
       7,     8,     9,    10,    24,    25,    26,    27,    28,    29,
      26,    27,    28,    29
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     1,     3,     4,     7,     8,     9,    10,    43,    44,
      48,    49,    50,    51,    52,    53,    57,    54,     1,    39,
      57,    61,    62,    63,    64,     1,    11,    67,    68,     1,
       3,    11,    12,    13,    14,    25,    30,    36,    39,    57,
      66,    75,    76,    78,    79,    80,    83,    84,     1,    55,
      57,     0,     5,    58,     1,    30,     1,    36,    55,    57,
       1,    30,     1,    36,    56,    57,    69,    70,     1,    36,
       1,    11,    30,    39,    71,    73,    75,    78,    69,    69,
       1,    76,    78,    78,    84,    84,    30,    16,    20,    21,
      24,    25,    26,    27,    28,    29,    40,    41,    84,    84,
       1,    18,    19,    22,    23,     1,    36,     1,    38,    59,
       6,    81,     1,     3,    45,    46,    66,     1,    30,    65,
      66,     1,    37,    38,    37,    69,    78,    75,    78,    18,
      23,    16,     1,    31,    31,    77,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    84,    84,
      84,    84,    36,     1,    30,    36,    60,    61,    67,    82,
      31,    37,    65,     1,    31,    37,    57,    57,    70,    72,
      74,    75,    76,    73,    78,     1,    31,    37,    36,    56,
      36,    83,    16,    47,    46,     1,    31,    36,     1,    16,
      36,    66,     1,    23,    36,    16,    78,     1,    31,     1,
      36,    66,     1,    36,    36,     1,    36,    66,    74,    78,
      36,     1,    17,     1,    36,    36,    57,     1,    36
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    42,    43,    43,    43,    43,    43,    43,    44,    44,
      44,    45,    45,    46,    46,    47,    47,    48,    48,    48,
      49,    49,    49,    50,    50,    50,    51,    51,    51,    52,
      52,    53,    53,    54,    54,    54,    55,    55,    55,    55,
      55,    55,    56,    56,    56,    57,    57,    58,    58,    59,
      59,    59,    60,    60,    61,    61,    61,    62,    62,    62,
      62,    63,    63,    63,    63,    64,    64,    65,    65,    65,
      66,    66,    66,    66,    67,    67,    68,    68,    69,    69,
      70,    71,    71,    72,    72,    73,    73,    73,    74,    74,
      75,    75,    75,    75,    75,    75,    76,    76,    77,    77,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    79,    80,    81,    81,    82,    82,    82,    82,    83,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     6,     2,
       6,     1,     3,     0,     1,     0,     2,     3,     2,     3,
       3,     2,     3,     3,     2,     3,     2,     2,     3,     3,
       1,     0,     2,     0,     2,     2,     8,     8,     3,     4,
       6,     7,     1,     3,     2,     1,     1,     0,     2,     0,
       2,     2,     1,     1,     1,     1,     1,     5,     5,     2,
       5,     6,     6,     3,     6,     7,     7,     1,     3,     2,
       1,     1,     1,     1,     5,     5,     2,     3,     1,     3,
       3,     1,     3,     1,     3,     1,     2,     3,     1,     3,
       1,     3,     3,     3,     3,     1,     4,     4,     1,     3,
       1,     1,     3,     3,     3,     3,     3,     3,     2,     3,
       3,     2,     2,     0,     2,     0,     2,     3,     3,     1,
       1,     2,     3,     3,     3,     3,     3,     2,     2,     3
};


/* YYDPREC[RULE-NUM] -- Dynamic precedence of rule #RULE-NUM (0 if none).  */
static const unsigned char yydprec[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0
};

/* YYMERGER[RULE-NUM] -- Index of merging function for rule #RULE-NUM.  */
static const unsigned char yymerger[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0
};

/* YYIMMEDIATE[RULE-NUM] -- True iff rule #RULE-NUM is not to be deferred, as
   in the case of predicates.  */
static const yybool yyimmediate[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0
};

/* YYCONFLP[YYPACT[STATE-NUM]] -- Pointer into YYCONFL of start of
   list of conflicting reductions corresponding to action entry for
   state STATE-NUM in yytable.  0 means no conflicts.  The list in
   yyconfl is terminated by a rule number of 0.  */
static const unsigned char yyconflp[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     5,     0,     0,
       0,     0,     0,     1,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     7,     0,     0,
       0,     0,     0,     3,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
static const short int yyconfl[] =
{
       0,   101,     0,   101,     0,    95,     0,    95,     0
};

/* Error token number */
#define YYTERROR 1


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

# define YYRHSLOC(Rhs, K) ((Rhs)[K].yystate.yyloc)


YYSTYPE yylval;
YYLTYPE yylloc;

int yynerrs;
int yychar;

static const int YYEOF = 0;
static const int YYEMPTY = -2;

typedef enum { yyok, yyaccept, yyabort, yyerr } YYRESULTTAG;

#define YYCHK(YYE)                              \
  do {                                          \
    YYRESULTTAG yychk_flag = YYE;               \
    if (yychk_flag != yyok)                     \
      return yychk_flag;                        \
  } while (0)

#if YYDEBUG

# ifndef YYFPRINTF
#  define YYFPRINTF fprintf
# endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YYDPRINTF(Args)                        \
  do {                                          \
    if (yydebug)                                \
      YYFPRINTF Args;                           \
  } while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, Source* sourcePtr, ParserNode* parseTreePtr, Vector* errVectPtr)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (sourcePtr);
  YYUSE (parseTreePtr);
  YYUSE (errVectPtr);
  if (!yyvaluep)
    return;
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, Source* sourcePtr, ParserNode* parseTreePtr, Vector* errVectPtr)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, sourcePtr, parseTreePtr, errVectPtr);
  YYFPRINTF (yyoutput, ")");
}

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                  \
  do {                                                                  \
    if (yydebug)                                                        \
      {                                                                 \
        YYFPRINTF (stderr, "%s ", Title);                               \
        yy_symbol_print (stderr, Type, Value, Location, sourcePtr, parseTreePtr, errVectPtr);        \
        YYFPRINTF (stderr, "\n");                                       \
      }                                                                 \
  } while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;

struct yyGLRStack;
static void yypstack (struct yyGLRStack* yystackp, size_t yyk)
  YY_ATTRIBUTE_UNUSED;
static void yypdumpstack (struct yyGLRStack* yystackp)
  YY_ATTRIBUTE_UNUSED;

#else /* !YYDEBUG */

# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)

#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYMAXDEPTH * sizeof (GLRStackItem)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Minimum number of free items on the stack allowed after an
   allocation.  This is to allow allocation and initialization
   to be completed by functions that call yyexpandGLRStack before the
   stack is expanded, thus insuring that all necessary pointers get
   properly redirected to new data.  */
#define YYHEADROOM 2

#ifndef YYSTACKEXPANDABLE
#  define YYSTACKEXPANDABLE 1
#endif

#if YYSTACKEXPANDABLE
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyexpandGLRStack (Yystack);                       \
  } while (0)
#else
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyMemoryExhausted (Yystack);                      \
  } while (0)
#endif


#if YYERROR_VERBOSE

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static size_t
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      size_t yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return strlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

#endif /* !YYERROR_VERBOSE */

/** State numbers, as in LALR(1) machine */
typedef int yyStateNum;

/** Rule numbers, as in LALR(1) machine */
typedef int yyRuleNum;

/** Grammar symbol */
typedef int yySymbol;

/** Item references, as in LALR(1) machine */
typedef short int yyItemNum;

typedef struct yyGLRState yyGLRState;
typedef struct yyGLRStateSet yyGLRStateSet;
typedef struct yySemanticOption yySemanticOption;
typedef union yyGLRStackItem yyGLRStackItem;
typedef struct yyGLRStack yyGLRStack;

struct yyGLRState {
  /** Type tag: always true.  */
  yybool yyisState;
  /** Type tag for yysemantics.  If true, yysval applies, otherwise
   *  yyfirstVal applies.  */
  yybool yyresolved;
  /** Number of corresponding LALR(1) machine state.  */
  yyStateNum yylrState;
  /** Preceding state in this stack */
  yyGLRState* yypred;
  /** Source position of the last token produced by my symbol */
  size_t yyposn;
  union {
    /** First in a chain of alternative reductions producing the
     *  non-terminal corresponding to this state, threaded through
     *  yynext.  */
    yySemanticOption* yyfirstVal;
    /** Semantic value for this state.  */
    YYSTYPE yysval;
  } yysemantics;
  /** Source location for this state.  */
  YYLTYPE yyloc;
};

struct yyGLRStateSet {
  yyGLRState** yystates;
  /** During nondeterministic operation, yylookaheadNeeds tracks which
   *  stacks have actually needed the current lookahead.  During deterministic
   *  operation, yylookaheadNeeds[0] is not maintained since it would merely
   *  duplicate yychar != YYEMPTY.  */
  yybool* yylookaheadNeeds;
  size_t yysize, yycapacity;
};

struct yySemanticOption {
  /** Type tag: always false.  */
  yybool yyisState;
  /** Rule number for this reduction */
  yyRuleNum yyrule;
  /** The last RHS state in the list of states to be reduced.  */
  yyGLRState* yystate;
  /** The lookahead for this reduction.  */
  int yyrawchar;
  YYSTYPE yyval;
  YYLTYPE yyloc;
  /** Next sibling in chain of options.  To facilitate merging,
   *  options are chained in decreasing order by address.  */
  yySemanticOption* yynext;
};

/** Type of the items in the GLR stack.  The yyisState field
 *  indicates which item of the union is valid.  */
union yyGLRStackItem {
  yyGLRState yystate;
  yySemanticOption yyoption;
};

struct yyGLRStack {
  int yyerrState;
  /* To compute the location of the error token.  */
  yyGLRStackItem yyerror_range[3];

  YYJMP_BUF yyexception_buffer;
  yyGLRStackItem* yyitems;
  yyGLRStackItem* yynextFree;
  size_t yyspaceLeft;
  yyGLRState* yysplitPoint;
  yyGLRState* yylastDeleted;
  yyGLRStateSet yytops;
};

#if YYSTACKEXPANDABLE
static void yyexpandGLRStack (yyGLRStack* yystackp);
#endif

static _Noreturn void
yyFail (yyGLRStack* yystackp, Source* sourcePtr, ParserNode* parseTreePtr, Vector* errVectPtr, const char* yymsg)
{
  if (yymsg != YY_NULLPTR)
    yyerror (sourcePtr, parseTreePtr, errVectPtr, yymsg);
  YYLONGJMP (yystackp->yyexception_buffer, 1);
}

static _Noreturn void
yyMemoryExhausted (yyGLRStack* yystackp)
{
  YYLONGJMP (yystackp->yyexception_buffer, 2);
}

#if YYDEBUG || YYERROR_VERBOSE
/** A printable representation of TOKEN.  */
static inline const char*
yytokenName (yySymbol yytoken)
{
  if (yytoken == YYEMPTY)
    return "";

  return yytname[yytoken];
}
#endif

/** Fill in YYVSP[YYLOW1 .. YYLOW0-1] from the chain of states starting
 *  at YYVSP[YYLOW0].yystate.yypred.  Leaves YYVSP[YYLOW1].yystate.yypred
 *  containing the pointer to the next state in the chain.  */
static void yyfillin (yyGLRStackItem *, int, int) YY_ATTRIBUTE_UNUSED;
static void
yyfillin (yyGLRStackItem *yyvsp, int yylow0, int yylow1)
{
  int i;
  yyGLRState *s = yyvsp[yylow0].yystate.yypred;
  for (i = yylow0-1; i >= yylow1; i -= 1)
    {
#if YYDEBUG
      yyvsp[i].yystate.yylrState = s->yylrState;
#endif
      yyvsp[i].yystate.yyresolved = s->yyresolved;
      if (s->yyresolved)
        yyvsp[i].yystate.yysemantics.yysval = s->yysemantics.yysval;
      else
        /* The effect of using yysval or yyloc (in an immediate rule) is
         * undefined.  */
        yyvsp[i].yystate.yysemantics.yyfirstVal = YY_NULLPTR;
      yyvsp[i].yystate.yyloc = s->yyloc;
      s = yyvsp[i].yystate.yypred = s->yypred;
    }
}

/* Do nothing if YYNORMAL or if *YYLOW <= YYLOW1.  Otherwise, fill in
 * YYVSP[YYLOW1 .. *YYLOW-1] as in yyfillin and set *YYLOW = YYLOW1.
 * For convenience, always return YYLOW1.  */
static inline int yyfill (yyGLRStackItem *, int *, int, yybool)
     YY_ATTRIBUTE_UNUSED;
static inline int
yyfill (yyGLRStackItem *yyvsp, int *yylow, int yylow1, yybool yynormal)
{
  if (!yynormal && yylow1 < *yylow)
    {
      yyfillin (yyvsp, *yylow, yylow1);
      *yylow = yylow1;
    }
  return yylow1;
}

/** Perform user action for rule number YYN, with RHS length YYRHSLEN,
 *  and top stack item YYVSP.  YYLVALP points to place to put semantic
 *  value ($$), and yylocp points to place for location information
 *  (@$).  Returns yyok for normal return, yyaccept for YYACCEPT,
 *  yyerr for YYERROR, yyabort for YYABORT.  */
static YYRESULTTAG
yyuserAction (yyRuleNum yyn, size_t yyrhslen, yyGLRStackItem* yyvsp,
              yyGLRStack* yystackp,
              YYSTYPE* yyvalp, YYLTYPE *yylocp, Source* sourcePtr, ParserNode* parseTreePtr, Vector* errVectPtr)
{
  yybool yynormal YY_ATTRIBUTE_UNUSED = (yystackp->yysplitPoint == YY_NULLPTR);
  int yylow;
  YYUSE (yyvalp);
  YYUSE (yylocp);
  YYUSE (sourcePtr);
  YYUSE (parseTreePtr);
  YYUSE (errVectPtr);
  YYUSE (yyrhslen);
# undef yyerrok
# define yyerrok (yystackp->yyerrState = 0)
# undef YYACCEPT
# define YYACCEPT return yyaccept
# undef YYABORT
# define YYABORT return yyabort
# undef YYERROR
# define YYERROR return yyerrok, yyerr
# undef YYRECOVERING
# define YYRECOVERING() (yystackp->yyerrState != 0)
# undef yyclearin
# define yyclearin (yychar = YYEMPTY)
# undef YYFILL
# define YYFILL(N) yyfill (yyvsp, &yylow, N, yynormal)
# undef YYBACKUP
# define YYBACKUP(Token, Value)                                              \
  return yyerror (sourcePtr, parseTreePtr, errVectPtr, YY_("syntax error: cannot back up")),     \
         yyerrok, yyerr

  yylow = 1;
  if (yyrhslen == 0)
    *yyvalp = yyval_default;
  else
    *yyvalp = yyvsp[YYFILL (1-yyrhslen)].yystate.yysemantics.yysval;
  YYLLOC_DEFAULT ((*yylocp), (yyvsp - yyrhslen), yyrhslen);
  yystackp->yyerror_range[1].yystate.yyloc = *yylocp;

  switch (yyn)
    {
        case 8:
#line 82 "grammar.y" /* glr.c:816  */
    {
		setType(parseTreePtr, ND_QUERY);
		addParamToNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval));
		addNeighborToNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
		addParamToNode(parseTreePtr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval));
	}
#line 1229 "grammar.tab.c" /* glr.c:816  */
    break;

  case 9:
#line 89 "grammar.y" /* glr.c:816  */
    {
		setType(parseTreePtr, ND_QUERY);
		setNullNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc));
		addErrorOnBegin("expected \'(\' token after name", (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc));
		freeNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
	}
#line 1240 "grammar.tab.c" /* glr.c:816  */
    break;

  case 10:
#line 96 "grammar.y" /* glr.c:816  */
    {
		setType(parseTreePtr, ND_QUERY);
		addParamToNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval));
		addNeighborToNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
		addParamToNode(parseTreePtr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval));
		
		addErrorOnEnd("expected \';\' token after query", (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc));
	}
#line 1253 "grammar.tab.c" /* glr.c:816  */
    break;

  case 12:
#line 109 "grammar.y" /* glr.c:816  */
    { ((*yyvalp)) = addNeighborToNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)); }
#line 1259 "grammar.tab.c" /* glr.c:816  */
    break;

  case 13:
#line 113 "grammar.y" /* glr.c:816  */
    { ((*yyvalp)) = createNode(ND_NAME, "", (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc).first_column); }
#line 1265 "grammar.tab.c" /* glr.c:816  */
    break;

  case 15:
#line 118 "grammar.y" /* glr.c:816  */
    { ((*yyvalp)) = createNode(ND_NAME, "", (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc).first_column); }
#line 1271 "grammar.tab.c" /* glr.c:816  */
    break;

  case 16:
#line 119 "grammar.y" /* glr.c:816  */
    { ((*yyvalp)) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval); }
#line 1277 "grammar.tab.c" /* glr.c:816  */
    break;

  case 17:
#line 125 "grammar.y" /* glr.c:816  */
    {
		setType(parseTreePtr, ND_S_DECL);
		addParamToNode(parseTreePtr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
	}
#line 1286 "grammar.tab.c" /* glr.c:816  */
    break;

  case 18:
#line 129 "grammar.y" /* glr.c:816  */
    { addErrorOnBegin("invalid declaration", (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc)); }
#line 1292 "grammar.tab.c" /* glr.c:816  */
    break;

  case 19:
#line 131 "grammar.y" /* glr.c:816  */
    { addErrorOnEnd("expected ';' after declaration", (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc)); }
#line 1298 "grammar.tab.c" /* glr.c:816  */
    break;

  case 20:
#line 135 "grammar.y" /* glr.c:816  */
    {
		setType(parseTreePtr, ND_S_FACT);
		addParamToNode(parseTreePtr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
	}
#line 1307 "grammar.tab.c" /* glr.c:816  */
    break;

  case 21:
#line 139 "grammar.y" /* glr.c:816  */
    { addErrorOnBegin("invalid fact", (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc)); }
#line 1313 "grammar.tab.c" /* glr.c:816  */
    break;

  case 22:
#line 141 "grammar.y" /* glr.c:816  */
    { addErrorOnEnd("expected ';' after fact", (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc)); }
#line 1319 "grammar.tab.c" /* glr.c:816  */
    break;

  case 23:
#line 145 "grammar.y" /* glr.c:816  */
    {
		setType(parseTreePtr, ND_S_AXIOM);
		addParamToNode(parseTreePtr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
	}
#line 1328 "grammar.tab.c" /* glr.c:816  */
    break;

  case 24:
#line 149 "grammar.y" /* glr.c:816  */
    { addErrorOnBegin("invalid axiom", (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc)); }
#line 1334 "grammar.tab.c" /* glr.c:816  */
    break;

  case 25:
#line 151 "grammar.y" /* glr.c:816  */
    { addErrorOnEnd("expected ';' after axiom", (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc)); }
#line 1340 "grammar.tab.c" /* glr.c:816  */
    break;

  case 26:
#line 155 "grammar.y" /* glr.c:816  */
    {
		setType(parseTreePtr, ND_S_RESTR);
		addParamToNode(parseTreePtr, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 1349 "grammar.tab.c" /* glr.c:816  */
    break;

  case 27:
#line 159 "grammar.y" /* glr.c:816  */
    { addErrorOnBegin("invalid restriction", (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc)); }
#line 1355 "grammar.tab.c" /* glr.c:816  */
    break;

  case 28:
#line 161 "grammar.y" /* glr.c:816  */
    { addErrorOnEnd("expected ';' after restriction", (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc)); }
#line 1361 "grammar.tab.c" /* glr.c:816  */
    break;

  case 29:
#line 167 "grammar.y" /* glr.c:816  */
    {
		setType(parseTreePtr, ND_PROG);
		addParamToNode(parseTreePtr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
		addParamToNode(parseTreePtr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
		addParamToNode(parseTreePtr, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 1372 "grammar.tab.c" /* glr.c:816  */
    break;

  case 30:
#line 174 "grammar.y" /* glr.c:816  */
    {
		setType(parseTreePtr, ND_PROG);
		addErrorOnBegin("Unknown programm segment. "
						"Start with one of follow keywords:\n"
						"    DECLARATIONS\n"
						"    FACTS\n"
						"    RESTRICTIONS\n", (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc));
	}
#line 1385 "grammar.tab.c" /* glr.c:816  */
    break;

  case 31:
#line 189 "grammar.y" /* glr.c:816  */
    { ((*yyvalp)) = createNode(ND_DECLS, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc).first_column); }
#line 1391 "grammar.tab.c" /* glr.c:816  */
    break;

  case 32:
#line 191 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = addParamToNode(createNode(ND_DECLS, NULL,
							(((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc).first_column), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 1400 "grammar.tab.c" /* glr.c:816  */
    break;

  case 33:
#line 198 "grammar.y" /* glr.c:816  */
    { ((*yyvalp)) = NULL; }
#line 1406 "grammar.tab.c" /* glr.c:816  */
    break;

  case 35:
#line 200 "grammar.y" /* glr.c:816  */
    { ((*yyvalp)) = addNeighborToNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)); }
#line 1412 "grammar.tab.c" /* glr.c:816  */
    break;

  case 36:
#line 206 "grammar.y" /* glr.c:816  */
    {
		(((yyGLRStackItem const *)yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval)->type = ND_FUNC_DEC;
		((*yyvalp)) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval);
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
	}
#line 1423 "grammar.tab.c" /* glr.c:816  */
    break;

  case 37:
#line 213 "grammar.y" /* glr.c:816  */
    {
		(((yyGLRStackItem const *)yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval)->type = ND_FUNC_DEC;
		((*yyvalp)) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval);
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
		
		addErrorOnEnd("expexted \';\' after declaration", (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc));
	}
#line 1436 "grammar.tab.c" /* glr.c:816  */
    break;

  case 38:
#line 222 "grammar.y" /* glr.c:816  */
    {
		addErrorOnBegin("expexted \':\' after name", (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc));
		setNullNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc));
		freeNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	}
#line 1446 "grammar.tab.c" /* glr.c:816  */
    break;

  case 39:
#line 228 "grammar.y" /* glr.c:816  */
    {
		addErrorOnBegin("expexted \'(\' after \':\' token", (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc));
		setNullNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc));
		freeNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval));
	}
#line 1456 "grammar.tab.c" /* glr.c:816  */
    break;

  case 40:
#line 234 "grammar.y" /* glr.c:816  */
    {
		addErrorOnBegin("expexted \')\' after list of types", (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc));
		setNullNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc));
		freeNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)); freeNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	}
#line 1466 "grammar.tab.c" /* glr.c:816  */
    break;

  case 41:
#line 240 "grammar.y" /* glr.c:816  */
    {
		addErrorOnBegin("expexted \'->\' after list of types", (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc));
		setNullNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc));
		freeNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)); freeNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval));
	}
#line 1476 "grammar.tab.c" /* glr.c:816  */
    break;

  case 43:
#line 249 "grammar.y" /* glr.c:816  */
    { ((*yyvalp)) = addNeighborToNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)); }
#line 1482 "grammar.tab.c" /* glr.c:816  */
    break;

  case 44:
#line 251 "grammar.y" /* glr.c:816  */
    {
		addErrorOnBegin("expected \',\' token after name", (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc));
		((*yyvalp)) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval);
	}
#line 1491 "grammar.tab.c" /* glr.c:816  */
    break;

  case 46:
#line 259 "grammar.y" /* glr.c:816  */
    { addErrorOnBegin("invalid name", (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc)); setNullNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc)); }
#line 1497 "grammar.tab.c" /* glr.c:816  */
    break;

  case 47:
#line 265 "grammar.y" /* glr.c:816  */
    { ((*yyvalp)) = createNode(ND_FACTS, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc).first_column); }
#line 1503 "grammar.tab.c" /* glr.c:816  */
    break;

  case 48:
#line 267 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = addParamToNode(createNode(ND_FACTS, NULL,
							(((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc).first_column), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 1512 "grammar.tab.c" /* glr.c:816  */
    break;

  case 49:
#line 274 "grammar.y" /* glr.c:816  */
    { ((*yyvalp)) = NULL; }
#line 1518 "grammar.tab.c" /* glr.c:816  */
    break;

  case 51:
#line 276 "grammar.y" /* glr.c:816  */
    { ((*yyvalp)) = addNeighborToNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)); }
#line 1524 "grammar.tab.c" /* glr.c:816  */
    break;

  case 57:
#line 290 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = addParamToNode(setType((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval), ND_PRED), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	}
#line 1532 "grammar.tab.c" /* glr.c:816  */
    break;

  case 58:
#line 294 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = addParamToNode(setType((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval), ND_PRED), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
		addErrorOnEnd("expexted \';\' after fact expression", (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc));
	}
#line 1541 "grammar.tab.c" /* glr.c:816  */
    break;

  case 59:
#line 299 "grammar.y" /* glr.c:816  */
    {
		addErrorOnBegin("expexted \'(\' after name", (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc));
		setNullNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc));
		freeNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
	}
#line 1551 "grammar.tab.c" /* glr.c:816  */
    break;

  case 60:
#line 305 "grammar.y" /* glr.c:816  */
    {
		addErrorOnBegin("expexted \')\' after constants list", (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc));
		setNullNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc));
		freeNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)); freeNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	}
#line 1561 "grammar.tab.c" /* glr.c:816  */
    break;

  case 61:
#line 315 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = createNode(ND_NOT, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yyloc).first_column);
		addParamToNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), setType((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval), ND_PRED));
	}
#line 1571 "grammar.tab.c" /* glr.c:816  */
    break;

  case 62:
#line 321 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = createNode(ND_NOT, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yyloc).first_column);
		addParamToNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), setType((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval), ND_PRED));
		
		addErrorOnEnd("expexted \';\' after fact expression", (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc));
	}
#line 1583 "grammar.tab.c" /* glr.c:816  */
    break;

  case 63:
#line 329 "grammar.y" /* glr.c:816  */
    {
		addErrorOnBegin("expexted \'(\' after name", (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc));
		setNullNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc));
		freeNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
	}
#line 1593 "grammar.tab.c" /* glr.c:816  */
    break;

  case 64:
#line 335 "grammar.y" /* glr.c:816  */
    {
		addErrorOnBegin("expexted \')\' after constants list", (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc));
		setNullNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc));
		freeNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)); freeNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	}
#line 1603 "grammar.tab.c" /* glr.c:816  */
    break;

  case 65:
#line 344 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = createNode(ND_EQ, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yyloc).first_column);
		addParamToNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval), (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), setType((((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval), ND_FUNC));
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
	}
#line 1614 "grammar.tab.c" /* glr.c:816  */
    break;

  case 66:
#line 351 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = createNode(ND_EQ, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yyloc).first_column);
		addParamToNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval), (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), setType((((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval), ND_FUNC));
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
		
		addErrorOnEnd("expexted \';\' after fact expression", (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc));
	}
#line 1627 "grammar.tab.c" /* glr.c:816  */
    break;

  case 68:
#line 364 "grammar.y" /* glr.c:816  */
    { ((*yyvalp)) = addNeighborToNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)); }
#line 1633 "grammar.tab.c" /* glr.c:816  */
    break;

  case 69:
#line 366 "grammar.y" /* glr.c:816  */
    {
		addErrorOnEnd("expected \',\' token after constant", (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc));
		((*yyvalp)) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval);
	}
#line 1642 "grammar.tab.c" /* glr.c:816  */
    break;

  case 70:
#line 373 "grammar.y" /* glr.c:816  */
    { ((*yyvalp)) = setType((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval), ND_NAMED_CONST); }
#line 1648 "grammar.tab.c" /* glr.c:816  */
    break;

  case 73:
#line 377 "grammar.y" /* glr.c:816  */
    {
		addErrorOnEnd("invalid constant", (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc));
		setNullNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc));
	}
#line 1657 "grammar.tab.c" /* glr.c:816  */
    break;

  case 74:
#line 389 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = addParamToNode(createNode(ND_AXIOM, NULL,
							(((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yyloc).first_column), (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
	}
#line 1668 "grammar.tab.c" /* glr.c:816  */
    break;

  case 75:
#line 396 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = addParamToNode(createNode(ND_AXIOM, NULL,
							(((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yyloc).first_column), (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
		
		addErrorOnEnd("expexted \';\' after axiom", (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yyloc));
	}
#line 1681 "grammar.tab.c" /* glr.c:816  */
    break;

  case 76:
#line 408 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = addParamToNode(createNode(ND_VARS, NULL,
										(((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc).first_column), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 1690 "grammar.tab.c" /* glr.c:816  */
    break;

  case 77:
#line 412 "grammar.y" /* glr.c:816  */
    { ((*yyvalp)) = addParamToNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)); }
#line 1696 "grammar.tab.c" /* glr.c:816  */
    break;

  case 79:
#line 419 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = addNeighborToNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 1704 "grammar.tab.c" /* glr.c:816  */
    break;

  case 80:
#line 426 "grammar.y" /* glr.c:816  */
    {
		ParserNode* pnVarPtr = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval);
		for (; pnVarPtr != NULL; pnVarPtr = pnVarPtr->next)
		{
			pnVarPtr->type = ND_VAR;
			addParamToNode(pnVarPtr,
				createNode(ND_NAME, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)->name, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc).first_column));
		}
		
		((*yyvalp)) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval);
		freeNode((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 1721 "grammar.tab.c" /* glr.c:816  */
    break;

  case 81:
#line 444 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = addParamToNode(createNode(ND_PREM, NULL,
							(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc).first_column), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 1730 "grammar.tab.c" /* glr.c:816  */
    break;

  case 82:
#line 448 "grammar.y" /* glr.c:816  */
    { ((*yyvalp)) = addParamToNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)); }
#line 1736 "grammar.tab.c" /* glr.c:816  */
    break;

  case 83:
#line 455 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = addParamToNode(createNode(ND_RES, NULL,
										(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc).first_column), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 1745 "grammar.tab.c" /* glr.c:816  */
    break;

  case 84:
#line 459 "grammar.y" /* glr.c:816  */
    { ((*yyvalp)) = addParamToNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)); }
#line 1751 "grammar.tab.c" /* glr.c:816  */
    break;

  case 86:
#line 468 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = addParamToNode(createNode(ND_NOT, NULL,
										(((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc).first_column), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 1760 "grammar.tab.c" /* glr.c:816  */
    break;

  case 87:
#line 473 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = createNode(ND_EQ, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_column);
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 1770 "grammar.tab.c" /* glr.c:816  */
    break;

  case 89:
#line 483 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = createNode(ND_EQ, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_column);
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 1780 "grammar.tab.c" /* glr.c:816  */
    break;

  case 90:
#line 492 "grammar.y" /* glr.c:816  */
    { ((*yyvalp)) = setType((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval), ND_PRED); }
#line 1786 "grammar.tab.c" /* glr.c:816  */
    break;

  case 91:
#line 494 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = createNode(ND_PRED, (char*)ARITH_RELATION_NAMES[AR_LESS],
						(((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_column);
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 1797 "grammar.tab.c" /* glr.c:816  */
    break;

  case 92:
#line 501 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = createNode(ND_PRED, (char*)ARITH_RELATION_NAMES[AR_MORE],
						(((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_column);
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 1808 "grammar.tab.c" /* glr.c:816  */
    break;

  case 93:
#line 508 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = createNode(ND_PRED, (char*)ARITH_RELATION_NAMES[AR_LESS_EQ],
						(((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_column);
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 1819 "grammar.tab.c" /* glr.c:816  */
    break;

  case 94:
#line 515 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = createNode(ND_PRED, (char*)ARITH_RELATION_NAMES[AR_MORE_EQ],
						(((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_column);
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 1830 "grammar.tab.c" /* glr.c:816  */
    break;

  case 95:
#line 522 "grammar.y" /* glr.c:816  */
    {
		addErrorOnBegin("invalid predicate expression", (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc));
		setNullNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc));
	}
#line 1839 "grammar.tab.c" /* glr.c:816  */
    break;

  case 96:
#line 529 "grammar.y" /* glr.c:816  */
    { ((*yyvalp)) = addParamToNode(setType((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval), ND_FUNC), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)); }
#line 1845 "grammar.tab.c" /* glr.c:816  */
    break;

  case 97:
#line 531 "grammar.y" /* glr.c:816  */
    {
		addErrorOnBegin("expexted \')\' after parametrs", (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc));
		setNullNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc));
		freeNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)); freeNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
	}
#line 1855 "grammar.tab.c" /* glr.c:816  */
    break;

  case 99:
#line 540 "grammar.y" /* glr.c:816  */
    { ((*yyvalp)) = addNeighborToNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)); }
#line 1861 "grammar.tab.c" /* glr.c:816  */
    break;

  case 102:
#line 548 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = createNode(ND_FUNC, (char*)ARITH_FUNCTION_NAMES[AF_PLUS],
						(((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_column);
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 1872 "grammar.tab.c" /* glr.c:816  */
    break;

  case 103:
#line 555 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = createNode(ND_FUNC, (char*)ARITH_FUNCTION_NAMES[AF_MULT],
						(((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_column);
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 1883 "grammar.tab.c" /* glr.c:816  */
    break;

  case 104:
#line 562 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = createNode(ND_FUNC, (char*)ARITH_FUNCTION_NAMES[AF_MINUS],
						(((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_column);
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 1894 "grammar.tab.c" /* glr.c:816  */
    break;

  case 105:
#line 569 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = createNode(ND_FUNC, (char*)ARITH_FUNCTION_NAMES[AF_DIV],
						(((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_column);
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 1905 "grammar.tab.c" /* glr.c:816  */
    break;

  case 106:
#line 576 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = createNode(ND_FUNC, (char*)ARITH_FUNCTION_NAMES[AF_POW],
						(((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_column);
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 1916 "grammar.tab.c" /* glr.c:816  */
    break;

  case 107:
#line 583 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = createNode(ND_FUNC, (char*)ARITH_FUNCTION_NAMES[AF_MOD],
						(((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_column);
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 1927 "grammar.tab.c" /* glr.c:816  */
    break;

  case 108:
#line 590 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = addParamToNode(createNode(ND_FUNC, "-1",
										(((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc).first_column), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 1936 "grammar.tab.c" /* glr.c:816  */
    break;

  case 109:
#line 594 "grammar.y" /* glr.c:816  */
    { ((*yyvalp)) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval); }
#line 1942 "grammar.tab.c" /* glr.c:816  */
    break;

  case 110:
#line 596 "grammar.y" /* glr.c:816  */
    {
		setNullNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc));
		addErrorOnBegin("expected \')\' token", (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc));
		freeNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
	}
#line 1952 "grammar.tab.c" /* glr.c:816  */
    break;

  case 111:
#line 607 "grammar.y" /* glr.c:816  */
    {
		ParserNode* pnVarPtr = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval);
		ParserNode* pnQuanPtr = ((*yyvalp))
			= createNode(ND_ALL, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc).first_column);
		addParamToNode(pnQuanPtr, pnVarPtr);
		pnVarPtr = pnVarPtr->next;
		pnQuanPtr->params->next = NULL;
		
		for (; pnVarPtr != NULL; )
		{
			addParamToNode(pnQuanPtr,
					createNode(ND_ALL, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc).first_column));
			pnQuanPtr = pnQuanPtr->params->next;
			addParamToNode(pnQuanPtr, pnVarPtr);
			pnVarPtr = pnVarPtr->next;
			pnQuanPtr->params->next = NULL;
		}
	}
#line 1975 "grammar.tab.c" /* glr.c:816  */
    break;

  case 112:
#line 630 "grammar.y" /* glr.c:816  */
    {
		ParserNode* pnVarPtr = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval);
		ParserNode* pnQuanPtr = ((*yyvalp))
			= createNode(ND_EXT, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc).first_column);
		addParamToNode(pnQuanPtr, pnVarPtr);
		pnVarPtr = pnVarPtr->next;
		pnQuanPtr->params->next = NULL;
		
		for (; pnVarPtr != NULL; )
		{
			addParamToNode(pnQuanPtr,
					createNode(ND_EXT, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc).first_column));
			pnQuanPtr = pnQuanPtr->params->next;
			addParamToNode(pnQuanPtr, pnVarPtr);
			pnVarPtr = pnVarPtr->next;
			pnQuanPtr->params->next = NULL;
		}
	}
#line 1998 "grammar.tab.c" /* glr.c:816  */
    break;

  case 113:
#line 656 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = createNode(ND_RESTRS, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc).first_column);
	}
#line 2006 "grammar.tab.c" /* glr.c:816  */
    break;

  case 114:
#line 660 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = addParamToNode(createNode(ND_RESTRS, NULL,
							(((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc).first_column), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 2015 "grammar.tab.c" /* glr.c:816  */
    break;

  case 115:
#line 668 "grammar.y" /* glr.c:816  */
    { ((*yyvalp)) = NULL; }
#line 2021 "grammar.tab.c" /* glr.c:816  */
    break;

  case 117:
#line 670 "grammar.y" /* glr.c:816  */
    { ((*yyvalp)) = addNeighborToNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)); }
#line 2027 "grammar.tab.c" /* glr.c:816  */
    break;

  case 118:
#line 672 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = addNeighborToNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
		addErrorOnEnd("expected ';' after restriction", (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc));
	}
#line 2036 "grammar.tab.c" /* glr.c:816  */
    break;

  case 121:
#line 685 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = addParamToNode(createNode(ND_NOT, NULL,
							(((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc).first_column), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 2045 "grammar.tab.c" /* glr.c:816  */
    break;

  case 122:
#line 690 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = createNode(ND_EQ, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_column);
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 2055 "grammar.tab.c" /* glr.c:816  */
    break;

  case 123:
#line 696 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = createNode(ND_LEQ, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_column);
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 2065 "grammar.tab.c" /* glr.c:816  */
    break;

  case 124:
#line 702 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = createNode(ND_OR, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_column);
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 2075 "grammar.tab.c" /* glr.c:816  */
    break;

  case 125:
#line 708 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = createNode(ND_AND, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_column);
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 2085 "grammar.tab.c" /* glr.c:816  */
    break;

  case 126:
#line 714 "grammar.y" /* glr.c:816  */
    {
		((*yyvalp)) = createNode(ND_IMP, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc).first_column);
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
		addParamToNode(((*yyvalp)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 2095 "grammar.tab.c" /* glr.c:816  */
    break;

  case 127:
#line 720 "grammar.y" /* glr.c:816  */
    {
		ParserNode* pnQuanPtr = ((*yyvalp)) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval);
		for (; pnQuanPtr->params->next != NULL;
			pnQuanPtr = pnQuanPtr->params->next);
		addParamToNode(pnQuanPtr, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 2106 "grammar.tab.c" /* glr.c:816  */
    break;

  case 128:
#line 727 "grammar.y" /* glr.c:816  */
    {
		ParserNode* pnQuanPtr = ((*yyvalp)) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval);
		for (; pnQuanPtr->params->next != NULL;
			pnQuanPtr = pnQuanPtr->params->next);
		addParamToNode(pnQuanPtr, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
#line 2117 "grammar.tab.c" /* glr.c:816  */
    break;

  case 129:
#line 733 "grammar.y" /* glr.c:816  */
    { ((*yyvalp)) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval); }
#line 2123 "grammar.tab.c" /* glr.c:816  */
    break;


#line 2127 "grammar.tab.c" /* glr.c:816  */
      default: break;
    }

  return yyok;
# undef yyerrok
# undef YYABORT
# undef YYACCEPT
# undef YYERROR
# undef YYBACKUP
# undef yyclearin
# undef YYRECOVERING
}


static void
yyuserMerge (int yyn, YYSTYPE* yy0, YYSTYPE* yy1)
{
  YYUSE (yy0);
  YYUSE (yy1);

  switch (yyn)
    {

      default: break;
    }
}

                              /* Bison grammar-table manipulation.  */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, Source* sourcePtr, ParserNode* parseTreePtr, Vector* errVectPtr)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (sourcePtr);
  YYUSE (parseTreePtr);
  YYUSE (errVectPtr);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}

/** Number of symbols composing the right hand side of rule #RULE.  */
static inline int
yyrhsLength (yyRuleNum yyrule)
{
  return yyr2[yyrule];
}

static void
yydestroyGLRState (char const *yymsg, yyGLRState *yys, Source* sourcePtr, ParserNode* parseTreePtr, Vector* errVectPtr)
{
  if (yys->yyresolved)
    yydestruct (yymsg, yystos[yys->yylrState],
                &yys->yysemantics.yysval, &yys->yyloc, sourcePtr, parseTreePtr, errVectPtr);
  else
    {
#if YYDEBUG
      if (yydebug)
        {
          if (yys->yysemantics.yyfirstVal)
            YYFPRINTF (stderr, "%s unresolved", yymsg);
          else
            YYFPRINTF (stderr, "%s incomplete", yymsg);
          YY_SYMBOL_PRINT ("", yystos[yys->yylrState], YY_NULLPTR, &yys->yyloc);
        }
#endif

      if (yys->yysemantics.yyfirstVal)
        {
          yySemanticOption *yyoption = yys->yysemantics.yyfirstVal;
          yyGLRState *yyrh;
          int yyn;
          for (yyrh = yyoption->yystate, yyn = yyrhsLength (yyoption->yyrule);
               yyn > 0;
               yyrh = yyrh->yypred, yyn -= 1)
            yydestroyGLRState (yymsg, yyrh, sourcePtr, parseTreePtr, errVectPtr);
        }
    }
}

/** Left-hand-side symbol for rule #YYRULE.  */
static inline yySymbol
yylhsNonterm (yyRuleNum yyrule)
{
  return yyr1[yyrule];
}

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-54)))

/** True iff LR state YYSTATE has only a default reduction (regardless
 *  of token).  */
static inline yybool
yyisDefaultedState (yyStateNum yystate)
{
  return yypact_value_is_default (yypact[yystate]);
}

/** The default reduction for YYSTATE, assuming it has one.  */
static inline yyRuleNum
yydefaultAction (yyStateNum yystate)
{
  return yydefact[yystate];
}

#define yytable_value_is_error(Yytable_value) \
  0

/** Set *YYACTION to the action to take in YYSTATE on seeing YYTOKEN.
 *  Result R means
 *    R < 0:  Reduce on rule -R.
 *    R = 0:  Error.
 *    R > 0:  Shift to state R.
 *  Set *YYCONFLICTS to a pointer into yyconfl to a 0-terminated list
 *  of conflicting reductions.
 */
static inline void
yygetLRActions (yyStateNum yystate, int yytoken,
                int* yyaction, const short int** yyconflicts)
{
  int yyindex = yypact[yystate] + yytoken;
  if (yypact_value_is_default (yypact[yystate])
      || yyindex < 0 || YYLAST < yyindex || yycheck[yyindex] != yytoken)
    {
      *yyaction = -yydefact[yystate];
      *yyconflicts = yyconfl;
    }
  else if (! yytable_value_is_error (yytable[yyindex]))
    {
      *yyaction = yytable[yyindex];
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
  else
    {
      *yyaction = 0;
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
}

/** Compute post-reduction state.
 * \param yystate   the current state
 * \param yysym     the nonterminal to push on the stack
 */
static inline yyStateNum
yyLRgotoState (yyStateNum yystate, yySymbol yysym)
{
  int yyr = yypgoto[yysym - YYNTOKENS] + yystate;
  if (0 <= yyr && yyr <= YYLAST && yycheck[yyr] == yystate)
    return yytable[yyr];
  else
    return yydefgoto[yysym - YYNTOKENS];
}

static inline yybool
yyisShiftAction (int yyaction)
{
  return 0 < yyaction;
}

static inline yybool
yyisErrorAction (int yyaction)
{
  return yyaction == 0;
}

                                /* GLRStates */

/** Return a fresh GLRStackItem in YYSTACKP.  The item is an LR state
 *  if YYISSTATE, and otherwise a semantic option.  Callers should call
 *  YY_RESERVE_GLRSTACK afterwards to make sure there is sufficient
 *  headroom.  */

static inline yyGLRStackItem*
yynewGLRStackItem (yyGLRStack* yystackp, yybool yyisState)
{
  yyGLRStackItem* yynewItem = yystackp->yynextFree;
  yystackp->yyspaceLeft -= 1;
  yystackp->yynextFree += 1;
  yynewItem->yystate.yyisState = yyisState;
  return yynewItem;
}

/** Add a new semantic action that will execute the action for rule
 *  YYRULE on the semantic values in YYRHS to the list of
 *  alternative actions for YYSTATE.  Assumes that YYRHS comes from
 *  stack #YYK of *YYSTACKP. */
static void
yyaddDeferredAction (yyGLRStack* yystackp, size_t yyk, yyGLRState* yystate,
                     yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yySemanticOption* yynewOption =
    &yynewGLRStackItem (yystackp, yyfalse)->yyoption;
  YYASSERT (!yynewOption->yyisState);
  yynewOption->yystate = yyrhs;
  yynewOption->yyrule = yyrule;
  if (yystackp->yytops.yylookaheadNeeds[yyk])
    {
      yynewOption->yyrawchar = yychar;
      yynewOption->yyval = yylval;
      yynewOption->yyloc = yylloc;
    }
  else
    yynewOption->yyrawchar = YYEMPTY;
  yynewOption->yynext = yystate->yysemantics.yyfirstVal;
  yystate->yysemantics.yyfirstVal = yynewOption;

  YY_RESERVE_GLRSTACK (yystackp);
}

                                /* GLRStacks */

/** Initialize YYSET to a singleton set containing an empty stack.  */
static yybool
yyinitStateSet (yyGLRStateSet* yyset)
{
  yyset->yysize = 1;
  yyset->yycapacity = 16;
  yyset->yystates = (yyGLRState**) YYMALLOC (16 * sizeof yyset->yystates[0]);
  if (! yyset->yystates)
    return yyfalse;
  yyset->yystates[0] = YY_NULLPTR;
  yyset->yylookaheadNeeds =
    (yybool*) YYMALLOC (16 * sizeof yyset->yylookaheadNeeds[0]);
  if (! yyset->yylookaheadNeeds)
    {
      YYFREE (yyset->yystates);
      return yyfalse;
    }
  return yytrue;
}

static void yyfreeStateSet (yyGLRStateSet* yyset)
{
  YYFREE (yyset->yystates);
  YYFREE (yyset->yylookaheadNeeds);
}

/** Initialize *YYSTACKP to a single empty stack, with total maximum
 *  capacity for all stacks of YYSIZE.  */
static yybool
yyinitGLRStack (yyGLRStack* yystackp, size_t yysize)
{
  yystackp->yyerrState = 0;
  yynerrs = 0;
  yystackp->yyspaceLeft = yysize;
  yystackp->yyitems =
    (yyGLRStackItem*) YYMALLOC (yysize * sizeof yystackp->yynextFree[0]);
  if (!yystackp->yyitems)
    return yyfalse;
  yystackp->yynextFree = yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULLPTR;
  yystackp->yylastDeleted = YY_NULLPTR;
  return yyinitStateSet (&yystackp->yytops);
}


#if YYSTACKEXPANDABLE
# define YYRELOC(YYFROMITEMS,YYTOITEMS,YYX,YYTYPE) \
  &((YYTOITEMS) - ((YYFROMITEMS) - (yyGLRStackItem*) (YYX)))->YYTYPE

/** If *YYSTACKP is expandable, extend it.  WARNING: Pointers into the
    stack from outside should be considered invalid after this call.
    We always expand when there are 1 or fewer items left AFTER an
    allocation, so that we can avoid having external pointers exist
    across an allocation.  */
static void
yyexpandGLRStack (yyGLRStack* yystackp)
{
  yyGLRStackItem* yynewItems;
  yyGLRStackItem* yyp0, *yyp1;
  size_t yynewSize;
  size_t yyn;
  size_t yysize = yystackp->yynextFree - yystackp->yyitems;
  if (YYMAXDEPTH - YYHEADROOM < yysize)
    yyMemoryExhausted (yystackp);
  yynewSize = 2*yysize;
  if (YYMAXDEPTH < yynewSize)
    yynewSize = YYMAXDEPTH;
  yynewItems = (yyGLRStackItem*) YYMALLOC (yynewSize * sizeof yynewItems[0]);
  if (! yynewItems)
    yyMemoryExhausted (yystackp);
  for (yyp0 = yystackp->yyitems, yyp1 = yynewItems, yyn = yysize;
       0 < yyn;
       yyn -= 1, yyp0 += 1, yyp1 += 1)
    {
      *yyp1 = *yyp0;
      if (*(yybool *) yyp0)
        {
          yyGLRState* yys0 = &yyp0->yystate;
          yyGLRState* yys1 = &yyp1->yystate;
          if (yys0->yypred != YY_NULLPTR)
            yys1->yypred =
              YYRELOC (yyp0, yyp1, yys0->yypred, yystate);
          if (! yys0->yyresolved && yys0->yysemantics.yyfirstVal != YY_NULLPTR)
            yys1->yysemantics.yyfirstVal =
              YYRELOC (yyp0, yyp1, yys0->yysemantics.yyfirstVal, yyoption);
        }
      else
        {
          yySemanticOption* yyv0 = &yyp0->yyoption;
          yySemanticOption* yyv1 = &yyp1->yyoption;
          if (yyv0->yystate != YY_NULLPTR)
            yyv1->yystate = YYRELOC (yyp0, yyp1, yyv0->yystate, yystate);
          if (yyv0->yynext != YY_NULLPTR)
            yyv1->yynext = YYRELOC (yyp0, yyp1, yyv0->yynext, yyoption);
        }
    }
  if (yystackp->yysplitPoint != YY_NULLPTR)
    yystackp->yysplitPoint = YYRELOC (yystackp->yyitems, yynewItems,
                                      yystackp->yysplitPoint, yystate);

  for (yyn = 0; yyn < yystackp->yytops.yysize; yyn += 1)
    if (yystackp->yytops.yystates[yyn] != YY_NULLPTR)
      yystackp->yytops.yystates[yyn] =
        YYRELOC (yystackp->yyitems, yynewItems,
                 yystackp->yytops.yystates[yyn], yystate);
  YYFREE (yystackp->yyitems);
  yystackp->yyitems = yynewItems;
  yystackp->yynextFree = yynewItems + yysize;
  yystackp->yyspaceLeft = yynewSize - yysize;
}
#endif

static void
yyfreeGLRStack (yyGLRStack* yystackp)
{
  YYFREE (yystackp->yyitems);
  yyfreeStateSet (&yystackp->yytops);
}

/** Assuming that YYS is a GLRState somewhere on *YYSTACKP, update the
 *  splitpoint of *YYSTACKP, if needed, so that it is at least as deep as
 *  YYS.  */
static inline void
yyupdateSplit (yyGLRStack* yystackp, yyGLRState* yys)
{
  if (yystackp->yysplitPoint != YY_NULLPTR && yystackp->yysplitPoint > yys)
    yystackp->yysplitPoint = yys;
}

/** Invalidate stack #YYK in *YYSTACKP.  */
static inline void
yymarkStackDeleted (yyGLRStack* yystackp, size_t yyk)
{
  if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
    yystackp->yylastDeleted = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yystates[yyk] = YY_NULLPTR;
}

/** Undelete the last stack in *YYSTACKP that was marked as deleted.  Can
    only be done once after a deletion, and only when all other stacks have
    been deleted.  */
static void
yyundeleteLastStack (yyGLRStack* yystackp)
{
  if (yystackp->yylastDeleted == YY_NULLPTR || yystackp->yytops.yysize != 0)
    return;
  yystackp->yytops.yystates[0] = yystackp->yylastDeleted;
  yystackp->yytops.yysize = 1;
  YYDPRINTF ((stderr, "Restoring last deleted stack as stack #0.\n"));
  yystackp->yylastDeleted = YY_NULLPTR;
}

static inline void
yyremoveDeletes (yyGLRStack* yystackp)
{
  size_t yyi, yyj;
  yyi = yyj = 0;
  while (yyj < yystackp->yytops.yysize)
    {
      if (yystackp->yytops.yystates[yyi] == YY_NULLPTR)
        {
          if (yyi == yyj)
            {
              YYDPRINTF ((stderr, "Removing dead stacks.\n"));
            }
          yystackp->yytops.yysize -= 1;
        }
      else
        {
          yystackp->yytops.yystates[yyj] = yystackp->yytops.yystates[yyi];
          /* In the current implementation, it's unnecessary to copy
             yystackp->yytops.yylookaheadNeeds[yyi] since, after
             yyremoveDeletes returns, the parser immediately either enters
             deterministic operation or shifts a token.  However, it doesn't
             hurt, and the code might evolve to need it.  */
          yystackp->yytops.yylookaheadNeeds[yyj] =
            yystackp->yytops.yylookaheadNeeds[yyi];
          if (yyj != yyi)
            {
              YYDPRINTF ((stderr, "Rename stack %lu -> %lu.\n",
                          (unsigned long int) yyi, (unsigned long int) yyj));
            }
          yyj += 1;
        }
      yyi += 1;
    }
}

/** Shift to a new state on stack #YYK of *YYSTACKP, corresponding to LR
 * state YYLRSTATE, at input position YYPOSN, with (resolved) semantic
 * value *YYVALP and source location *YYLOCP.  */
static inline void
yyglrShift (yyGLRStack* yystackp, size_t yyk, yyStateNum yylrState,
            size_t yyposn,
            YYSTYPE* yyvalp, YYLTYPE* yylocp)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yytrue;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yysval = *yyvalp;
  yynewState->yyloc = *yylocp;
  yystackp->yytops.yystates[yyk] = yynewState;

  YY_RESERVE_GLRSTACK (yystackp);
}

/** Shift stack #YYK of *YYSTACKP, to a new state corresponding to LR
 *  state YYLRSTATE, at input position YYPOSN, with the (unresolved)
 *  semantic value of YYRHS under the action for YYRULE.  */
static inline void
yyglrShiftDefer (yyGLRStack* yystackp, size_t yyk, yyStateNum yylrState,
                 size_t yyposn, yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;
  YYASSERT (yynewState->yyisState);

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yyfalse;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yyfirstVal = YY_NULLPTR;
  yystackp->yytops.yystates[yyk] = yynewState;

  /* Invokes YY_RESERVE_GLRSTACK.  */
  yyaddDeferredAction (yystackp, yyk, yynewState, yyrhs, yyrule);
}

#if !YYDEBUG
# define YY_REDUCE_PRINT(Args)
#else
# define YY_REDUCE_PRINT(Args)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print Args;               \
} while (0)

/*----------------------------------------------------------------------.
| Report that stack #YYK of *YYSTACKP is going to be reduced by YYRULE. |
`----------------------------------------------------------------------*/

static inline void
yy_reduce_print (int yynormal, yyGLRStackItem* yyvsp, size_t yyk,
                 yyRuleNum yyrule, Source* sourcePtr, ParserNode* parseTreePtr, Vector* errVectPtr)
{
  int yynrhs = yyrhsLength (yyrule);
  int yylow = 1;
  int yyi;
  YYFPRINTF (stderr, "Reducing stack %lu by rule %d (line %lu):\n",
             (unsigned long int) yyk, yyrule - 1,
             (unsigned long int) yyrline[yyrule]);
  if (! yynormal)
    yyfillin (yyvsp, 1, -yynrhs);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyvsp[yyi - yynrhs + 1].yystate.yylrState],
                       &yyvsp[yyi - yynrhs + 1].yystate.yysemantics.yysval
                       , &(((yyGLRStackItem const *)yyvsp)[YYFILL ((yyi + 1) - (yynrhs))].yystate.yyloc)                       , sourcePtr, parseTreePtr, errVectPtr);
      if (!yyvsp[yyi - yynrhs + 1].yystate.yyresolved)
        YYFPRINTF (stderr, " (unresolved)");
      YYFPRINTF (stderr, "\n");
    }
}
#endif

/** Pop the symbols consumed by reduction #YYRULE from the top of stack
 *  #YYK of *YYSTACKP, and perform the appropriate semantic action on their
 *  semantic values.  Assumes that all ambiguities in semantic values
 *  have been previously resolved.  Set *YYVALP to the resulting value,
 *  and *YYLOCP to the computed location (if any).  Return value is as
 *  for userAction.  */
static inline YYRESULTTAG
yydoAction (yyGLRStack* yystackp, size_t yyk, yyRuleNum yyrule,
            YYSTYPE* yyvalp, YYLTYPE *yylocp, Source* sourcePtr, ParserNode* parseTreePtr, Vector* errVectPtr)
{
  int yynrhs = yyrhsLength (yyrule);

  if (yystackp->yysplitPoint == YY_NULLPTR)
    {
      /* Standard special case: single stack.  */
      yyGLRStackItem* yyrhs = (yyGLRStackItem*) yystackp->yytops.yystates[yyk];
      YYASSERT (yyk == 0);
      yystackp->yynextFree -= yynrhs;
      yystackp->yyspaceLeft += yynrhs;
      yystackp->yytops.yystates[0] = & yystackp->yynextFree[-1].yystate;
      YY_REDUCE_PRINT ((1, yyrhs, yyk, yyrule, sourcePtr, parseTreePtr, errVectPtr));
      return yyuserAction (yyrule, yynrhs, yyrhs, yystackp,
                           yyvalp, yylocp, sourcePtr, parseTreePtr, errVectPtr);
    }
  else
    {
      int yyi;
      yyGLRState* yys;
      yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
      yys = yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred
        = yystackp->yytops.yystates[yyk];
      if (yynrhs == 0)
        /* Set default location.  */
        yyrhsVals[YYMAXRHS + YYMAXLEFT - 1].yystate.yyloc = yys->yyloc;
      for (yyi = 0; yyi < yynrhs; yyi += 1)
        {
          yys = yys->yypred;
          YYASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yystackp->yytops.yystates[yyk] = yys;
      YY_REDUCE_PRINT ((0, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1, yyk, yyrule, sourcePtr, parseTreePtr, errVectPtr));
      return yyuserAction (yyrule, yynrhs, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, yyvalp, yylocp, sourcePtr, parseTreePtr, errVectPtr);
    }
}

/** Pop items off stack #YYK of *YYSTACKP according to grammar rule YYRULE,
 *  and push back on the resulting nonterminal symbol.  Perform the
 *  semantic action associated with YYRULE and store its value with the
 *  newly pushed state, if YYFORCEEVAL or if *YYSTACKP is currently
 *  unambiguous.  Otherwise, store the deferred semantic action with
 *  the new state.  If the new state would have an identical input
 *  position, LR state, and predecessor to an existing state on the stack,
 *  it is identified with that existing state, eliminating stack #YYK from
 *  *YYSTACKP.  In this case, the semantic value is
 *  added to the options for the existing state's semantic value.
 */
static inline YYRESULTTAG
yyglrReduce (yyGLRStack* yystackp, size_t yyk, yyRuleNum yyrule,
             yybool yyforceEval, Source* sourcePtr, ParserNode* parseTreePtr, Vector* errVectPtr)
{
  size_t yyposn = yystackp->yytops.yystates[yyk]->yyposn;

  if (yyforceEval || yystackp->yysplitPoint == YY_NULLPTR)
    {
      YYSTYPE yysval;
      YYLTYPE yyloc;

      YYRESULTTAG yyflag = yydoAction (yystackp, yyk, yyrule, &yysval, &yyloc, sourcePtr, parseTreePtr, errVectPtr);
      if (yyflag == yyerr && yystackp->yysplitPoint != YY_NULLPTR)
        {
          YYDPRINTF ((stderr, "Parse on stack %lu rejected by rule #%d.\n",
                     (unsigned long int) yyk, yyrule - 1));
        }
      if (yyflag != yyok)
        return yyflag;
      YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyrule], &yysval, &yyloc);
      yyglrShift (yystackp, yyk,
                  yyLRgotoState (yystackp->yytops.yystates[yyk]->yylrState,
                                 yylhsNonterm (yyrule)),
                  yyposn, &yysval, &yyloc);
    }
  else
    {
      size_t yyi;
      int yyn;
      yyGLRState* yys, *yys0 = yystackp->yytops.yystates[yyk];
      yyStateNum yynewLRState;

      for (yys = yystackp->yytops.yystates[yyk], yyn = yyrhsLength (yyrule);
           0 < yyn; yyn -= 1)
        {
          yys = yys->yypred;
          YYASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yynewLRState = yyLRgotoState (yys->yylrState, yylhsNonterm (yyrule));
      YYDPRINTF ((stderr,
                  "Reduced stack %lu by rule #%d; action deferred.  "
                  "Now in state %d.\n",
                  (unsigned long int) yyk, yyrule - 1, yynewLRState));
      for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
        if (yyi != yyk && yystackp->yytops.yystates[yyi] != YY_NULLPTR)
          {
            yyGLRState *yysplit = yystackp->yysplitPoint;
            yyGLRState *yyp = yystackp->yytops.yystates[yyi];
            while (yyp != yys && yyp != yysplit && yyp->yyposn >= yyposn)
              {
                if (yyp->yylrState == yynewLRState && yyp->yypred == yys)
                  {
                    yyaddDeferredAction (yystackp, yyk, yyp, yys0, yyrule);
                    yymarkStackDeleted (yystackp, yyk);
                    YYDPRINTF ((stderr, "Merging stack %lu into stack %lu.\n",
                                (unsigned long int) yyk,
                                (unsigned long int) yyi));
                    return yyok;
                  }
                yyp = yyp->yypred;
              }
          }
      yystackp->yytops.yystates[yyk] = yys;
      yyglrShiftDefer (yystackp, yyk, yynewLRState, yyposn, yys0, yyrule);
    }
  return yyok;
}

static size_t
yysplitStack (yyGLRStack* yystackp, size_t yyk)
{
  if (yystackp->yysplitPoint == YY_NULLPTR)
    {
      YYASSERT (yyk == 0);
      yystackp->yysplitPoint = yystackp->yytops.yystates[yyk];
    }
  if (yystackp->yytops.yysize >= yystackp->yytops.yycapacity)
    {
      yyGLRState** yynewStates;
      yybool* yynewLookaheadNeeds;

      yynewStates = YY_NULLPTR;

      if (yystackp->yytops.yycapacity
          > (YYSIZEMAX / (2 * sizeof yynewStates[0])))
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yycapacity *= 2;

      yynewStates =
        (yyGLRState**) YYREALLOC (yystackp->yytops.yystates,
                                  (yystackp->yytops.yycapacity
                                   * sizeof yynewStates[0]));
      if (yynewStates == YY_NULLPTR)
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yystates = yynewStates;

      yynewLookaheadNeeds =
        (yybool*) YYREALLOC (yystackp->yytops.yylookaheadNeeds,
                             (yystackp->yytops.yycapacity
                              * sizeof yynewLookaheadNeeds[0]));
      if (yynewLookaheadNeeds == YY_NULLPTR)
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yylookaheadNeeds = yynewLookaheadNeeds;
    }
  yystackp->yytops.yystates[yystackp->yytops.yysize]
    = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yylookaheadNeeds[yystackp->yytops.yysize]
    = yystackp->yytops.yylookaheadNeeds[yyk];
  yystackp->yytops.yysize += 1;
  return yystackp->yytops.yysize-1;
}

/** True iff YYY0 and YYY1 represent identical options at the top level.
 *  That is, they represent the same rule applied to RHS symbols
 *  that produce the same terminal symbols.  */
static yybool
yyidenticalOptions (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  if (yyy0->yyrule == yyy1->yyrule)
    {
      yyGLRState *yys0, *yys1;
      int yyn;
      for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
           yyn = yyrhsLength (yyy0->yyrule);
           yyn > 0;
           yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
        if (yys0->yyposn != yys1->yyposn)
          return yyfalse;
      return yytrue;
    }
  else
    return yyfalse;
}

/** Assuming identicalOptions (YYY0,YYY1), destructively merge the
 *  alternative semantic values for the RHS-symbols of YYY1 and YYY0.  */
static void
yymergeOptionSets (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  yyGLRState *yys0, *yys1;
  int yyn;
  for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
       yyn = yyrhsLength (yyy0->yyrule);
       yyn > 0;
       yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
    {
      if (yys0 == yys1)
        break;
      else if (yys0->yyresolved)
        {
          yys1->yyresolved = yytrue;
          yys1->yysemantics.yysval = yys0->yysemantics.yysval;
        }
      else if (yys1->yyresolved)
        {
          yys0->yyresolved = yytrue;
          yys0->yysemantics.yysval = yys1->yysemantics.yysval;
        }
      else
        {
          yySemanticOption** yyz0p = &yys0->yysemantics.yyfirstVal;
          yySemanticOption* yyz1 = yys1->yysemantics.yyfirstVal;
          while (yytrue)
            {
              if (yyz1 == *yyz0p || yyz1 == YY_NULLPTR)
                break;
              else if (*yyz0p == YY_NULLPTR)
                {
                  *yyz0p = yyz1;
                  break;
                }
              else if (*yyz0p < yyz1)
                {
                  yySemanticOption* yyz = *yyz0p;
                  *yyz0p = yyz1;
                  yyz1 = yyz1->yynext;
                  (*yyz0p)->yynext = yyz;
                }
              yyz0p = &(*yyz0p)->yynext;
            }
          yys1->yysemantics.yyfirstVal = yys0->yysemantics.yyfirstVal;
        }
    }
}

/** Y0 and Y1 represent two possible actions to take in a given
 *  parsing state; return 0 if no combination is possible,
 *  1 if user-mergeable, 2 if Y0 is preferred, 3 if Y1 is preferred.  */
static int
yypreference (yySemanticOption* y0, yySemanticOption* y1)
{
  yyRuleNum r0 = y0->yyrule, r1 = y1->yyrule;
  int p0 = yydprec[r0], p1 = yydprec[r1];

  if (p0 == p1)
    {
      if (yymerger[r0] == 0 || yymerger[r0] != yymerger[r1])
        return 0;
      else
        return 1;
    }
  if (p0 == 0 || p1 == 0)
    return 0;
  if (p0 < p1)
    return 3;
  if (p1 < p0)
    return 2;
  return 0;
}

static YYRESULTTAG yyresolveValue (yyGLRState* yys,
                                   yyGLRStack* yystackp, Source* sourcePtr, ParserNode* parseTreePtr, Vector* errVectPtr);


/** Resolve the previous YYN states starting at and including state YYS
 *  on *YYSTACKP. If result != yyok, some states may have been left
 *  unresolved possibly with empty semantic option chains.  Regardless
 *  of whether result = yyok, each state has been left with consistent
 *  data so that yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveStates (yyGLRState* yys, int yyn,
                 yyGLRStack* yystackp, Source* sourcePtr, ParserNode* parseTreePtr, Vector* errVectPtr)
{
  if (0 < yyn)
    {
      YYASSERT (yys->yypred);
      YYCHK (yyresolveStates (yys->yypred, yyn-1, yystackp, sourcePtr, parseTreePtr, errVectPtr));
      if (! yys->yyresolved)
        YYCHK (yyresolveValue (yys, yystackp, sourcePtr, parseTreePtr, errVectPtr));
    }
  return yyok;
}

/** Resolve the states for the RHS of YYOPT on *YYSTACKP, perform its
 *  user action, and return the semantic value and location in *YYVALP
 *  and *YYLOCP.  Regardless of whether result = yyok, all RHS states
 *  have been destroyed (assuming the user action destroys all RHS
 *  semantic values if invoked).  */
static YYRESULTTAG
yyresolveAction (yySemanticOption* yyopt, yyGLRStack* yystackp,
                 YYSTYPE* yyvalp, YYLTYPE *yylocp, Source* sourcePtr, ParserNode* parseTreePtr, Vector* errVectPtr)
{
  yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
  int yynrhs = yyrhsLength (yyopt->yyrule);
  YYRESULTTAG yyflag =
    yyresolveStates (yyopt->yystate, yynrhs, yystackp, sourcePtr, parseTreePtr, errVectPtr);
  if (yyflag != yyok)
    {
      yyGLRState *yys;
      for (yys = yyopt->yystate; yynrhs > 0; yys = yys->yypred, yynrhs -= 1)
        yydestroyGLRState ("Cleanup: popping", yys, sourcePtr, parseTreePtr, errVectPtr);
      return yyflag;
    }

  yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred = yyopt->yystate;
  if (yynrhs == 0)
    /* Set default location.  */
    yyrhsVals[YYMAXRHS + YYMAXLEFT - 1].yystate.yyloc = yyopt->yystate->yyloc;
  {
    int yychar_current = yychar;
    YYSTYPE yylval_current = yylval;
    YYLTYPE yylloc_current = yylloc;
    yychar = yyopt->yyrawchar;
    yylval = yyopt->yyval;
    yylloc = yyopt->yyloc;
    yyflag = yyuserAction (yyopt->yyrule, yynrhs,
                           yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, yyvalp, yylocp, sourcePtr, parseTreePtr, errVectPtr);
    yychar = yychar_current;
    yylval = yylval_current;
    yylloc = yylloc_current;
  }
  return yyflag;
}

#if YYDEBUG
static void
yyreportTree (yySemanticOption* yyx, int yyindent)
{
  int yynrhs = yyrhsLength (yyx->yyrule);
  int yyi;
  yyGLRState* yys;
  yyGLRState* yystates[1 + YYMAXRHS];
  yyGLRState yyleftmost_state;

  for (yyi = yynrhs, yys = yyx->yystate; 0 < yyi; yyi -= 1, yys = yys->yypred)
    yystates[yyi] = yys;
  if (yys == YY_NULLPTR)
    {
      yyleftmost_state.yyposn = 0;
      yystates[0] = &yyleftmost_state;
    }
  else
    yystates[0] = yys;

  if (yyx->yystate->yyposn < yys->yyposn + 1)
    YYFPRINTF (stderr, "%*s%s -> <Rule %d, empty>\n",
               yyindent, "", yytokenName (yylhsNonterm (yyx->yyrule)),
               yyx->yyrule - 1);
  else
    YYFPRINTF (stderr, "%*s%s -> <Rule %d, tokens %lu .. %lu>\n",
               yyindent, "", yytokenName (yylhsNonterm (yyx->yyrule)),
               yyx->yyrule - 1, (unsigned long int) (yys->yyposn + 1),
               (unsigned long int) yyx->yystate->yyposn);
  for (yyi = 1; yyi <= yynrhs; yyi += 1)
    {
      if (yystates[yyi]->yyresolved)
        {
          if (yystates[yyi-1]->yyposn+1 > yystates[yyi]->yyposn)
            YYFPRINTF (stderr, "%*s%s <empty>\n", yyindent+2, "",
                       yytokenName (yystos[yystates[yyi]->yylrState]));
          else
            YYFPRINTF (stderr, "%*s%s <tokens %lu .. %lu>\n", yyindent+2, "",
                       yytokenName (yystos[yystates[yyi]->yylrState]),
                       (unsigned long int) (yystates[yyi-1]->yyposn + 1),
                       (unsigned long int) yystates[yyi]->yyposn);
        }
      else
        yyreportTree (yystates[yyi]->yysemantics.yyfirstVal, yyindent+2);
    }
}
#endif

static YYRESULTTAG
yyreportAmbiguity (yySemanticOption* yyx0,
                   yySemanticOption* yyx1, Source* sourcePtr, ParserNode* parseTreePtr, Vector* errVectPtr)
{
  YYUSE (yyx0);
  YYUSE (yyx1);

#if YYDEBUG
  YYFPRINTF (stderr, "Ambiguity detected.\n");
  YYFPRINTF (stderr, "Option 1,\n");
  yyreportTree (yyx0, 2);
  YYFPRINTF (stderr, "\nOption 2,\n");
  yyreportTree (yyx1, 2);
  YYFPRINTF (stderr, "\n");
#endif

  yyerror (sourcePtr, parseTreePtr, errVectPtr, YY_("syntax is ambiguous"));
  return yyabort;
}

/** Resolve the locations for each of the YYN1 states in *YYSTACKP,
 *  ending at YYS1.  Has no effect on previously resolved states.
 *  The first semantic option of a state is always chosen.  */
static void
yyresolveLocations (yyGLRState* yys1, int yyn1,
                    yyGLRStack *yystackp, Source* sourcePtr, ParserNode* parseTreePtr, Vector* errVectPtr)
{
  if (0 < yyn1)
    {
      yyresolveLocations (yys1->yypred, yyn1 - 1, yystackp, sourcePtr, parseTreePtr, errVectPtr);
      if (!yys1->yyresolved)
        {
          yyGLRStackItem yyrhsloc[1 + YYMAXRHS];
          int yynrhs;
          yySemanticOption *yyoption = yys1->yysemantics.yyfirstVal;
          YYASSERT (yyoption != YY_NULLPTR);
          yynrhs = yyrhsLength (yyoption->yyrule);
          if (yynrhs > 0)
            {
              yyGLRState *yys;
              int yyn;
              yyresolveLocations (yyoption->yystate, yynrhs,
                                  yystackp, sourcePtr, parseTreePtr, errVectPtr);
              for (yys = yyoption->yystate, yyn = yynrhs;
                   yyn > 0;
                   yys = yys->yypred, yyn -= 1)
                yyrhsloc[yyn].yystate.yyloc = yys->yyloc;
            }
          else
            {
              /* Both yyresolveAction and yyresolveLocations traverse the GSS
                 in reverse rightmost order.  It is only necessary to invoke
                 yyresolveLocations on a subforest for which yyresolveAction
                 would have been invoked next had an ambiguity not been
                 detected.  Thus the location of the previous state (but not
                 necessarily the previous state itself) is guaranteed to be
                 resolved already.  */
              yyGLRState *yyprevious = yyoption->yystate;
              yyrhsloc[0].yystate.yyloc = yyprevious->yyloc;
            }
          {
            int yychar_current = yychar;
            YYSTYPE yylval_current = yylval;
            YYLTYPE yylloc_current = yylloc;
            yychar = yyoption->yyrawchar;
            yylval = yyoption->yyval;
            yylloc = yyoption->yyloc;
            YYLLOC_DEFAULT ((yys1->yyloc), yyrhsloc, yynrhs);
            yychar = yychar_current;
            yylval = yylval_current;
            yylloc = yylloc_current;
          }
        }
    }
}

/** Resolve the ambiguity represented in state YYS in *YYSTACKP,
 *  perform the indicated actions, and set the semantic value of YYS.
 *  If result != yyok, the chain of semantic options in YYS has been
 *  cleared instead or it has been left unmodified except that
 *  redundant options may have been removed.  Regardless of whether
 *  result = yyok, YYS has been left with consistent data so that
 *  yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveValue (yyGLRState* yys, yyGLRStack* yystackp, Source* sourcePtr, ParserNode* parseTreePtr, Vector* errVectPtr)
{
  yySemanticOption* yyoptionList = yys->yysemantics.yyfirstVal;
  yySemanticOption* yybest = yyoptionList;
  yySemanticOption** yypp;
  yybool yymerge = yyfalse;
  YYSTYPE yysval;
  YYRESULTTAG yyflag;
  YYLTYPE *yylocp = &yys->yyloc;

  for (yypp = &yyoptionList->yynext; *yypp != YY_NULLPTR; )
    {
      yySemanticOption* yyp = *yypp;

      if (yyidenticalOptions (yybest, yyp))
        {
          yymergeOptionSets (yybest, yyp);
          *yypp = yyp->yynext;
        }
      else
        {
          switch (yypreference (yybest, yyp))
            {
            case 0:
              yyresolveLocations (yys, 1, yystackp, sourcePtr, parseTreePtr, errVectPtr);
              return yyreportAmbiguity (yybest, yyp, sourcePtr, parseTreePtr, errVectPtr);
              break;
            case 1:
              yymerge = yytrue;
              break;
            case 2:
              break;
            case 3:
              yybest = yyp;
              yymerge = yyfalse;
              break;
            default:
              /* This cannot happen so it is not worth a YYASSERT (yyfalse),
                 but some compilers complain if the default case is
                 omitted.  */
              break;
            }
          yypp = &yyp->yynext;
        }
    }

  if (yymerge)
    {
      yySemanticOption* yyp;
      int yyprec = yydprec[yybest->yyrule];
      yyflag = yyresolveAction (yybest, yystackp, &yysval, yylocp, sourcePtr, parseTreePtr, errVectPtr);
      if (yyflag == yyok)
        for (yyp = yybest->yynext; yyp != YY_NULLPTR; yyp = yyp->yynext)
          {
            if (yyprec == yydprec[yyp->yyrule])
              {
                YYSTYPE yysval_other;
                YYLTYPE yydummy;
                yyflag = yyresolveAction (yyp, yystackp, &yysval_other, &yydummy, sourcePtr, parseTreePtr, errVectPtr);
                if (yyflag != yyok)
                  {
                    yydestruct ("Cleanup: discarding incompletely merged value for",
                                yystos[yys->yylrState],
                                &yysval, yylocp, sourcePtr, parseTreePtr, errVectPtr);
                    break;
                  }
                yyuserMerge (yymerger[yyp->yyrule], &yysval, &yysval_other);
              }
          }
    }
  else
    yyflag = yyresolveAction (yybest, yystackp, &yysval, yylocp, sourcePtr, parseTreePtr, errVectPtr);

  if (yyflag == yyok)
    {
      yys->yyresolved = yytrue;
      yys->yysemantics.yysval = yysval;
    }
  else
    yys->yysemantics.yyfirstVal = YY_NULLPTR;
  return yyflag;
}

static YYRESULTTAG
yyresolveStack (yyGLRStack* yystackp, Source* sourcePtr, ParserNode* parseTreePtr, Vector* errVectPtr)
{
  if (yystackp->yysplitPoint != YY_NULLPTR)
    {
      yyGLRState* yys;
      int yyn;

      for (yyn = 0, yys = yystackp->yytops.yystates[0];
           yys != yystackp->yysplitPoint;
           yys = yys->yypred, yyn += 1)
        continue;
      YYCHK (yyresolveStates (yystackp->yytops.yystates[0], yyn, yystackp
                             , sourcePtr, parseTreePtr, errVectPtr));
    }
  return yyok;
}

static void
yycompressStack (yyGLRStack* yystackp)
{
  yyGLRState* yyp, *yyq, *yyr;

  if (yystackp->yytops.yysize != 1 || yystackp->yysplitPoint == YY_NULLPTR)
    return;

  for (yyp = yystackp->yytops.yystates[0], yyq = yyp->yypred, yyr = YY_NULLPTR;
       yyp != yystackp->yysplitPoint;
       yyr = yyp, yyp = yyq, yyq = yyp->yypred)
    yyp->yypred = yyr;

  yystackp->yyspaceLeft += yystackp->yynextFree - yystackp->yyitems;
  yystackp->yynextFree = ((yyGLRStackItem*) yystackp->yysplitPoint) + 1;
  yystackp->yyspaceLeft -= yystackp->yynextFree - yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULLPTR;
  yystackp->yylastDeleted = YY_NULLPTR;

  while (yyr != YY_NULLPTR)
    {
      yystackp->yynextFree->yystate = *yyr;
      yyr = yyr->yypred;
      yystackp->yynextFree->yystate.yypred = &yystackp->yynextFree[-1].yystate;
      yystackp->yytops.yystates[0] = &yystackp->yynextFree->yystate;
      yystackp->yynextFree += 1;
      yystackp->yyspaceLeft -= 1;
    }
}

static YYRESULTTAG
yyprocessOneStack (yyGLRStack* yystackp, size_t yyk,
                   size_t yyposn, Source* sourcePtr, ParserNode* parseTreePtr, Vector* errVectPtr)
{
  while (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
    {
      yyStateNum yystate = yystackp->yytops.yystates[yyk]->yylrState;
      YYDPRINTF ((stderr, "Stack %lu Entering state %d\n",
                  (unsigned long int) yyk, yystate));

      YYASSERT (yystate != YYFINAL);

      if (yyisDefaultedState (yystate))
        {
          YYRESULTTAG yyflag;
          yyRuleNum yyrule = yydefaultAction (yystate);
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, "Stack %lu dies.\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          yyflag = yyglrReduce (yystackp, yyk, yyrule, yyimmediate[yyrule], sourcePtr, parseTreePtr, errVectPtr);
          if (yyflag == yyerr)
            {
              YYDPRINTF ((stderr,
                          "Stack %lu dies "
                          "(predicate failure or explicit user error).\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          if (yyflag != yyok)
            return yyflag;
        }
      else
        {
          yySymbol yytoken;
          int yyaction;
          const short int* yyconflicts;

          yystackp->yytops.yylookaheadNeeds[yyk] = yytrue;
          if (yychar == YYEMPTY)
            {
              YYDPRINTF ((stderr, "Reading a token: "));
              yychar = yylex (sourcePtr);
            }

          if (yychar <= YYEOF)
            {
              yychar = yytoken = YYEOF;
              YYDPRINTF ((stderr, "Now at end of input.\n"));
            }
          else
            {
              yytoken = YYTRANSLATE (yychar);
              YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
            }

          yygetLRActions (yystate, yytoken, &yyaction, &yyconflicts);

          while (*yyconflicts != 0)
            {
              YYRESULTTAG yyflag;
              size_t yynewStack = yysplitStack (yystackp, yyk);
              YYDPRINTF ((stderr, "Splitting off stack %lu from %lu.\n",
                          (unsigned long int) yynewStack,
                          (unsigned long int) yyk));
              yyflag = yyglrReduce (yystackp, yynewStack,
                                    *yyconflicts,
                                    yyimmediate[*yyconflicts], sourcePtr, parseTreePtr, errVectPtr);
              if (yyflag == yyok)
                YYCHK (yyprocessOneStack (yystackp, yynewStack,
                                          yyposn, sourcePtr, parseTreePtr, errVectPtr));
              else if (yyflag == yyerr)
                {
                  YYDPRINTF ((stderr, "Stack %lu dies.\n",
                              (unsigned long int) yynewStack));
                  yymarkStackDeleted (yystackp, yynewStack);
                }
              else
                return yyflag;
              yyconflicts += 1;
            }

          if (yyisShiftAction (yyaction))
            break;
          else if (yyisErrorAction (yyaction))
            {
              YYDPRINTF ((stderr, "Stack %lu dies.\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yystackp, yyk);
              break;
            }
          else
            {
              YYRESULTTAG yyflag = yyglrReduce (yystackp, yyk, -yyaction,
                                                yyimmediate[-yyaction], sourcePtr, parseTreePtr, errVectPtr);
              if (yyflag == yyerr)
                {
                  YYDPRINTF ((stderr,
                              "Stack %lu dies "
                              "(predicate failure or explicit user error).\n",
                              (unsigned long int) yyk));
                  yymarkStackDeleted (yystackp, yyk);
                  break;
                }
              else if (yyflag != yyok)
                return yyflag;
            }
        }
    }
  return yyok;
}

static void
yyreportSyntaxError (yyGLRStack* yystackp, Source* sourcePtr, ParserNode* parseTreePtr, Vector* errVectPtr)
{
  if (yystackp->yyerrState != 0)
    return;
#if ! YYERROR_VERBOSE
  yyerror (sourcePtr, parseTreePtr, errVectPtr, YY_("syntax error"));
#else
  {
  yySymbol yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);
  size_t yysize0 = yytnamerr (YY_NULLPTR, yytokenName (yytoken));
  size_t yysize = yysize0;
  yybool yysize_overflow = yyfalse;
  char* yymsg = YY_NULLPTR;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected").  */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[yystackp->yytops.yystates[0]->yylrState];
      yyarg[yycount++] = yytokenName (yytoken);
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for this
             state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;
          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytokenName (yyx);
                {
                  size_t yysz = yysize + yytnamerr (YY_NULLPTR, yytokenName (yyx));
                  yysize_overflow |= yysz < yysize;
                  yysize = yysz;
                }
              }
        }
    }

  switch (yycount)
    {
#define YYCASE_(N, S)                   \
      case N:                           \
        yyformat = S;                   \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  {
    size_t yysz = yysize + strlen (yyformat);
    yysize_overflow |= yysz < yysize;
    yysize = yysz;
  }

  if (!yysize_overflow)
    yymsg = (char *) YYMALLOC (yysize);

  if (yymsg)
    {
      char *yyp = yymsg;
      int yyi = 0;
      while ((*yyp = *yyformat))
        {
          if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
            {
              yyp += yytnamerr (yyp, yyarg[yyi++]);
              yyformat += 2;
            }
          else
            {
              yyp++;
              yyformat++;
            }
        }
      yyerror (sourcePtr, parseTreePtr, errVectPtr, yymsg);
      YYFREE (yymsg);
    }
  else
    {
      yyerror (sourcePtr, parseTreePtr, errVectPtr, YY_("syntax error"));
      yyMemoryExhausted (yystackp);
    }
  }
#endif /* YYERROR_VERBOSE */
  yynerrs += 1;
}

/* Recover from a syntax error on *YYSTACKP, assuming that *YYSTACKP->YYTOKENP,
   yylval, and yylloc are the syntactic category, semantic value, and location
   of the lookahead.  */
static void
yyrecoverSyntaxError (yyGLRStack* yystackp, Source* sourcePtr, ParserNode* parseTreePtr, Vector* errVectPtr)
{
  size_t yyk;
  int yyj;

  if (yystackp->yyerrState == 3)
    /* We just shifted the error token and (perhaps) took some
       reductions.  Skip tokens until we can proceed.  */
    while (yytrue)
      {
        yySymbol yytoken;
        if (yychar == YYEOF)
          yyFail (yystackp, sourcePtr, parseTreePtr, errVectPtr, YY_NULLPTR);
        if (yychar != YYEMPTY)
          {
            /* We throw away the lookahead, but the error range
               of the shifted error token must take it into account.  */
            yyGLRState *yys = yystackp->yytops.yystates[0];
            yyGLRStackItem yyerror_range[3];
            yyerror_range[1].yystate.yyloc = yys->yyloc;
            yyerror_range[2].yystate.yyloc = yylloc;
            YYLLOC_DEFAULT ((yys->yyloc), yyerror_range, 2);
            yytoken = YYTRANSLATE (yychar);
            yydestruct ("Error: discarding",
                        yytoken, &yylval, &yylloc, sourcePtr, parseTreePtr, errVectPtr);
          }
        YYDPRINTF ((stderr, "Reading a token: "));
        yychar = yylex (sourcePtr);
        if (yychar <= YYEOF)
          {
            yychar = yytoken = YYEOF;
            YYDPRINTF ((stderr, "Now at end of input.\n"));
          }
        else
          {
            yytoken = YYTRANSLATE (yychar);
            YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
          }
        yyj = yypact[yystackp->yytops.yystates[0]->yylrState];
        if (yypact_value_is_default (yyj))
          return;
        yyj += yytoken;
        if (yyj < 0 || YYLAST < yyj || yycheck[yyj] != yytoken)
          {
            if (yydefact[yystackp->yytops.yystates[0]->yylrState] != 0)
              return;
          }
        else if (! yytable_value_is_error (yytable[yyj]))
          return;
      }

  /* Reduce to one stack.  */
  for (yyk = 0; yyk < yystackp->yytops.yysize; yyk += 1)
    if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
      break;
  if (yyk >= yystackp->yytops.yysize)
    yyFail (yystackp, sourcePtr, parseTreePtr, errVectPtr, YY_NULLPTR);
  for (yyk += 1; yyk < yystackp->yytops.yysize; yyk += 1)
    yymarkStackDeleted (yystackp, yyk);
  yyremoveDeletes (yystackp);
  yycompressStack (yystackp);

  /* Now pop stack until we find a state that shifts the error token.  */
  yystackp->yyerrState = 3;
  while (yystackp->yytops.yystates[0] != YY_NULLPTR)
    {
      yyGLRState *yys = yystackp->yytops.yystates[0];
      yyj = yypact[yys->yylrState];
      if (! yypact_value_is_default (yyj))
        {
          yyj += YYTERROR;
          if (0 <= yyj && yyj <= YYLAST && yycheck[yyj] == YYTERROR
              && yyisShiftAction (yytable[yyj]))
            {
              /* Shift the error token.  */
              /* First adjust its location.*/
              YYLTYPE yyerrloc;
              yystackp->yyerror_range[2].yystate.yyloc = yylloc;
              YYLLOC_DEFAULT (yyerrloc, (yystackp->yyerror_range), 2);
              YY_SYMBOL_PRINT ("Shifting", yystos[yytable[yyj]],
                               &yylval, &yyerrloc);
              yyglrShift (yystackp, 0, yytable[yyj],
                          yys->yyposn, &yylval, &yyerrloc);
              yys = yystackp->yytops.yystates[0];
              break;
            }
        }
      yystackp->yyerror_range[1].yystate.yyloc = yys->yyloc;
      if (yys->yypred != YY_NULLPTR)
        yydestroyGLRState ("Error: popping", yys, sourcePtr, parseTreePtr, errVectPtr);
      yystackp->yytops.yystates[0] = yys->yypred;
      yystackp->yynextFree -= 1;
      yystackp->yyspaceLeft += 1;
    }
  if (yystackp->yytops.yystates[0] == YY_NULLPTR)
    yyFail (yystackp, sourcePtr, parseTreePtr, errVectPtr, YY_NULLPTR);
}

#define YYCHK1(YYE)                                                          \
  do {                                                                       \
    switch (YYE) {                                                           \
    case yyok:                                                               \
      break;                                                                 \
    case yyabort:                                                            \
      goto yyabortlab;                                                       \
    case yyaccept:                                                           \
      goto yyacceptlab;                                                      \
    case yyerr:                                                              \
      goto yyuser_error;                                                     \
    default:                                                                 \
      goto yybuglab;                                                         \
    }                                                                        \
  } while (0)

/*----------.
| yyparse.  |
`----------*/

int
yyparse (Source* sourcePtr, ParserNode* parseTreePtr, Vector* errVectPtr)
{
  int yyresult;
  yyGLRStack yystack;
  yyGLRStack* const yystackp = &yystack;
  size_t yyposn;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY;
  yylval = yyval_default;
  yylloc = yyloc_default;

  if (! yyinitGLRStack (yystackp, YYINITDEPTH))
    goto yyexhaustedlab;
  switch (YYSETJMP (yystack.yyexception_buffer))
    {
    case 0: break;
    case 1: goto yyabortlab;
    case 2: goto yyexhaustedlab;
    default: goto yybuglab;
    }
  yyglrShift (&yystack, 0, 0, 0, &yylval, &yylloc);
  yyposn = 0;

  while (yytrue)
    {
      /* For efficiency, we have two loops, the first of which is
         specialized to deterministic operation (single stack, no
         potential ambiguity).  */
      /* Standard mode */
      while (yytrue)
        {
          yyRuleNum yyrule;
          int yyaction;
          const short int* yyconflicts;

          yyStateNum yystate = yystack.yytops.yystates[0]->yylrState;
          YYDPRINTF ((stderr, "Entering state %d\n", yystate));
          if (yystate == YYFINAL)
            goto yyacceptlab;
          if (yyisDefaultedState (yystate))
            {
              yyrule = yydefaultAction (yystate);
              if (yyrule == 0)
                {
               yystack.yyerror_range[1].yystate.yyloc = yylloc;
                  yyreportSyntaxError (&yystack, sourcePtr, parseTreePtr, errVectPtr);
                  goto yyuser_error;
                }
              YYCHK1 (yyglrReduce (&yystack, 0, yyrule, yytrue, sourcePtr, parseTreePtr, errVectPtr));
            }
          else
            {
              yySymbol yytoken;
              if (yychar == YYEMPTY)
                {
                  YYDPRINTF ((stderr, "Reading a token: "));
                  yychar = yylex (sourcePtr);
                }

              if (yychar <= YYEOF)
                {
                  yychar = yytoken = YYEOF;
                  YYDPRINTF ((stderr, "Now at end of input.\n"));
                }
              else
                {
                  yytoken = YYTRANSLATE (yychar);
                  YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
                }

              yygetLRActions (yystate, yytoken, &yyaction, &yyconflicts);
              if (*yyconflicts != 0)
                break;
              if (yyisShiftAction (yyaction))
                {
                  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
                  yychar = YYEMPTY;
                  yyposn += 1;
                  yyglrShift (&yystack, 0, yyaction, yyposn, &yylval, &yylloc);
                  if (0 < yystack.yyerrState)
                    yystack.yyerrState -= 1;
                }
              else if (yyisErrorAction (yyaction))
                {
               yystack.yyerror_range[1].yystate.yyloc = yylloc;
                  yyreportSyntaxError (&yystack, sourcePtr, parseTreePtr, errVectPtr);
                  goto yyuser_error;
                }
              else
                YYCHK1 (yyglrReduce (&yystack, 0, -yyaction, yytrue, sourcePtr, parseTreePtr, errVectPtr));
            }
        }

      while (yytrue)
        {
          yySymbol yytoken_to_shift;
          size_t yys;

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            yystackp->yytops.yylookaheadNeeds[yys] = yychar != YYEMPTY;

          /* yyprocessOneStack returns one of three things:

              - An error flag.  If the caller is yyprocessOneStack, it
                immediately returns as well.  When the caller is finally
                yyparse, it jumps to an error label via YYCHK1.

              - yyok, but yyprocessOneStack has invoked yymarkStackDeleted
                (&yystack, yys), which sets the top state of yys to NULL.  Thus,
                yyparse's following invocation of yyremoveDeletes will remove
                the stack.

              - yyok, when ready to shift a token.

             Except in the first case, yyparse will invoke yyremoveDeletes and
             then shift the next token onto all remaining stacks.  This
             synchronization of the shift (that is, after all preceding
             reductions on all stacks) helps prevent double destructor calls
             on yylval in the event of memory exhaustion.  */

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            YYCHK1 (yyprocessOneStack (&yystack, yys, yyposn, sourcePtr, parseTreePtr, errVectPtr));
          yyremoveDeletes (&yystack);
          if (yystack.yytops.yysize == 0)
            {
              yyundeleteLastStack (&yystack);
              if (yystack.yytops.yysize == 0)
                yyFail (&yystack, sourcePtr, parseTreePtr, errVectPtr, YY_("syntax error"));
              YYCHK1 (yyresolveStack (&yystack, sourcePtr, parseTreePtr, errVectPtr));
              YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));
           yystack.yyerror_range[1].yystate.yyloc = yylloc;
              yyreportSyntaxError (&yystack, sourcePtr, parseTreePtr, errVectPtr);
              goto yyuser_error;
            }

          /* If any yyglrShift call fails, it will fail after shifting.  Thus,
             a copy of yylval will already be on stack 0 in the event of a
             failure in the following loop.  Thus, yychar is set to YYEMPTY
             before the loop to make sure the user destructor for yylval isn't
             called twice.  */
          yytoken_to_shift = YYTRANSLATE (yychar);
          yychar = YYEMPTY;
          yyposn += 1;
          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            {
              int yyaction;
              const short int* yyconflicts;
              yyStateNum yystate = yystack.yytops.yystates[yys]->yylrState;
              yygetLRActions (yystate, yytoken_to_shift, &yyaction,
                              &yyconflicts);
              /* Note that yyconflicts were handled by yyprocessOneStack.  */
              YYDPRINTF ((stderr, "On stack %lu, ", (unsigned long int) yys));
              YY_SYMBOL_PRINT ("shifting", yytoken_to_shift, &yylval, &yylloc);
              yyglrShift (&yystack, yys, yyaction, yyposn,
                          &yylval, &yylloc);
              YYDPRINTF ((stderr, "Stack %lu now in state #%d\n",
                          (unsigned long int) yys,
                          yystack.yytops.yystates[yys]->yylrState));
            }

          if (yystack.yytops.yysize == 1)
            {
              YYCHK1 (yyresolveStack (&yystack, sourcePtr, parseTreePtr, errVectPtr));
              YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));
              yycompressStack (&yystack);
              break;
            }
        }
      continue;
    yyuser_error:
      yyrecoverSyntaxError (&yystack, sourcePtr, parseTreePtr, errVectPtr);
      yyposn = yystack.yytops.yystates[0]->yyposn;
    }

 yyacceptlab:
  yyresult = 0;
  goto yyreturn;

 yybuglab:
  YYASSERT (yyfalse);
  goto yyabortlab;

 yyabortlab:
  yyresult = 1;
  goto yyreturn;

 yyexhaustedlab:
  yyerror (sourcePtr, parseTreePtr, errVectPtr, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;

 yyreturn:
  if (yychar != YYEMPTY)
    yydestruct ("Cleanup: discarding lookahead",
                YYTRANSLATE (yychar), &yylval, &yylloc, sourcePtr, parseTreePtr, errVectPtr);

  /* If the stack is well-formed, pop the stack until it is empty,
     destroying its entries as we go.  But free the stack regardless
     of whether it is well-formed.  */
  if (yystack.yyitems)
    {
      yyGLRState** yystates = yystack.yytops.yystates;
      if (yystates)
        {
          size_t yysize = yystack.yytops.yysize;
          size_t yyk;
          for (yyk = 0; yyk < yysize; yyk += 1)
            if (yystates[yyk])
              {
                while (yystates[yyk])
                  {
                    yyGLRState *yys = yystates[yyk];
                 yystack.yyerror_range[1].yystate.yyloc = yys->yyloc;
                  if (yys->yypred != YY_NULLPTR)
                      yydestroyGLRState ("Cleanup: popping", yys, sourcePtr, parseTreePtr, errVectPtr);
                    yystates[yyk] = yys->yypred;
                    yystack.yynextFree -= 1;
                    yystack.yyspaceLeft += 1;
                  }
                break;
              }
        }
      yyfreeGLRStack (&yystack);
    }

  return yyresult;
}

/* DEBUGGING ONLY */
#if YYDEBUG
static void
yy_yypstack (yyGLRState* yys)
{
  if (yys->yypred)
    {
      yy_yypstack (yys->yypred);
      YYFPRINTF (stderr, " -> ");
    }
  YYFPRINTF (stderr, "%d@%lu", yys->yylrState,
             (unsigned long int) yys->yyposn);
}

static void
yypstates (yyGLRState* yyst)
{
  if (yyst == YY_NULLPTR)
    YYFPRINTF (stderr, "<null>");
  else
    yy_yypstack (yyst);
  YYFPRINTF (stderr, "\n");
}

static void
yypstack (yyGLRStack* yystackp, size_t yyk)
{
  yypstates (yystackp->yytops.yystates[yyk]);
}

#define YYINDEX(YYX)                                                         \
    ((YYX) == YY_NULLPTR ? -1 : (yyGLRStackItem*) (YYX) - yystackp->yyitems)


static void
yypdumpstack (yyGLRStack* yystackp)
{
  yyGLRStackItem* yyp;
  size_t yyi;
  for (yyp = yystackp->yyitems; yyp < yystackp->yynextFree; yyp += 1)
    {
      YYFPRINTF (stderr, "%3lu. ",
                 (unsigned long int) (yyp - yystackp->yyitems));
      if (*(yybool *) yyp)
        {
          YYASSERT (yyp->yystate.yyisState);
          YYASSERT (yyp->yyoption.yyisState);
          YYFPRINTF (stderr, "Res: %d, LR State: %d, posn: %lu, pred: %ld",
                     yyp->yystate.yyresolved, yyp->yystate.yylrState,
                     (unsigned long int) yyp->yystate.yyposn,
                     (long int) YYINDEX (yyp->yystate.yypred));
          if (! yyp->yystate.yyresolved)
            YYFPRINTF (stderr, ", firstVal: %ld",
                       (long int) YYINDEX (yyp->yystate
                                             .yysemantics.yyfirstVal));
        }
      else
        {
          YYASSERT (!yyp->yystate.yyisState);
          YYASSERT (!yyp->yyoption.yyisState);
          YYFPRINTF (stderr, "Option. rule: %d, state: %ld, next: %ld",
                     yyp->yyoption.yyrule - 1,
                     (long int) YYINDEX (yyp->yyoption.yystate),
                     (long int) YYINDEX (yyp->yyoption.yynext));
        }
      YYFPRINTF (stderr, "\n");
    }
  YYFPRINTF (stderr, "Tops:");
  for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
    YYFPRINTF (stderr, "%lu: %ld; ", (unsigned long int) yyi,
               (long int) YYINDEX (yystackp->yytops.yystates[yyi]));
  YYFPRINTF (stderr, "\n");
}
#endif

#undef yylval
#undef yychar
#undef yynerrs
#undef yylloc



#line 737 "grammar.y" /* glr.c:2584  */




void yyerror(Source* sourcePtr, ParserNode* programPtr, Vector* errVectPtr,
			char const *msg)
{
	/* Empty */
}


/* LEXER */


typedef struct {
	char* word;
	int code;
} Keyword;

static const Keyword keywords_g[] = {
	{"DECLARATIONS",	DECLARATIONS_TITLE},
	{"FACTS", 			FACTS_TITLE},
	{"RESTRICTIONS",	RESTRICTIONS_TITLE},
	{"All",				ALL},
	{"Ext", 			EXT},
	{"declaration", 	SINGLE_DECLARATION},
	{"fact", 			SINGLE_FACT},
	{"axiom", 			SINGLE_AXIOM},
	{"restriction", 	SINGLE_RESTRICTION},
	//~ {"abs",				TOKEN_ABS},
	//~ {"max",				TOKEN_MAX},
	//~ {"min",				TOKEN_MIN},
	//~ {"sin",				SIN},
	//~ {"cos",				COS},
	//~ {"tan",				TAN},
	//~ {"asin",			ASIN},
	//~ {"acos",			ACOS},
	//~ {"atan",			ATAN},
	//~ {"log",				LOG}
};


int getKeywordCode(char word[])
{
	size_t wordCt = sizeof(keywords_g) / sizeof(Keyword);
	size_t wordNum;
	
	for (wordNum = 0; wordNum < wordCt; wordNum++)
		if (strcmp(word, keywords_g[wordNum].word) == 0)
			return keywords_g[wordNum].code;
	
	return 0;
}


const size_t maxStrLen_g = 256;
size_t strLen_g = 0;
char* str_g = NULL;

//~ #define _MAX(x, y) (x < y) ? (y) : (x)
//~ #define _MIN(x, y) (x < y) ? (x) : (y)


int yylex(Source* sourcePtr)
{
	if (str_g == NULL)
	{
		strLen_g = 10;
		str_g = (char*)malloc(strLen_g * sizeof(char));
	}
	
	yylval = NULL;
	int ch = getChar(sourcePtr);

	/* ignore spaces and comments */
	while (!isEmpty(sourcePtr) && (isspace(ch) || ch == '#'))
	{
		while (!isEmpty(sourcePtr) && isspace(ch))
		{
			if (ch == '\n')
			{
				yylloc.last_line++;
				yylloc.last_column = 1;
			}
			else
				yylloc.last_column++;
				
			ch = getChar(sourcePtr);
		}
		
		if (ch == '#')
			while (!isEmpty(sourcePtr) && (ch = getChar(sourcePtr)) != '\n')
				yylloc.last_column++;
	}
	
	if (isEmpty(sourcePtr)) return 0;
	
	yylloc.first_line = yylloc.last_line;
	yylloc.first_column = yylloc.last_column;
	
	/* get cpecial character */
	if (ch == '-')	/* -> */
	{
		if (getChar(sourcePtr) == '>') return yylloc.last_column += 2, ARROW;
		else comeBack(sourcePtr);
	}
	if (ch == '=')	/* => */
	{
		if (getChar(sourcePtr) == '>')
			return yylloc.last_column += 2, ARROW_IMP;
		else comeBack(sourcePtr);
	}
	if (ch == '<')	/* <=> */
	{
		int ch1 = getChar(sourcePtr);
		int ch2 = getChar(sourcePtr);
		
		if (ch1 == '=' && ch2 == '>') return yylloc.last_column += 3, ARROW_EQ;
		else { comeBack(sourcePtr); comeBack(sourcePtr); }
	}
	if (ch == '<')	/* <= */
	{
		if (getChar(sourcePtr) == '=')
			return yylloc.last_column += 2, LES_OR_EQ;
		else comeBack(sourcePtr);
	}
	if (ch == '>')	/* <= */
	{
		if (getChar(sourcePtr) == '=')
			return yylloc.last_column += 2, MORE_OR_EQ;
		else comeBack(sourcePtr);
	}
	
	/* get number */
	if (ch == '-' || ch == '.' || isdigit(ch))
	{
		size_t pos = 0;
		Boolean hasPoint = false;
		
		while (isdigit(ch) || (ch == '.' && !hasPoint)
			|| (ch == '-' && pos == 0))
		{
			hasPoint |= (ch == '.');
			
			/* If buffer is full, make it bigger. */
			if (pos >= (ssize_t)strLen_g - 1)
			{
				strLen_g = _MIN(strLen_g + 10, maxStrLen_g);
				str_g = (char*) realloc(str_g, strLen_g);
			}

			if (pos < maxStrLen_g)
			{
				/* Add this character to the buffer. */
				str_g[pos++] = ch;
				ch = getChar(sourcePtr);
			}
		}

		comeBack(sourcePtr);

		if (pos == 1 && str_g[0] == '-')
		{
			ch = '-';
		}
		else
		{
			str_g[_MIN(pos, maxStrLen_g - 1)] = '\0';
			yylloc.last_column += pos;
			
			if (hasPoint)
			{
				yylval = createNode(ND_REAL, str_g,
					yylloc.first_line, yylloc.first_column);
				return REAL;
			}
			else
			{
				yylval = createNode(ND_INTEGER, str_g,
					yylloc.first_line, yylloc.first_column);
				return INTEGER;
			}
		}
	}

	/* get name or keyword */
	if (isalpha(ch) || ch == '_')
	{
		size_t pos = 0;
		
		while (isalnum(ch) || ch == '_')
		{
			/* If buffer is full, make it bigger. */
			if (pos >= (ssize_t)strLen_g - 1)
			{
				strLen_g = _MIN(strLen_g + 10, maxStrLen_g);
				str_g = (char*) realloc(str_g, strLen_g);
			}

			/* Add this character to the buffer. */
			if (pos < maxStrLen_g)
			{
				/* Add this character to the buffer. */
				str_g[pos++] = ch;
				ch = getChar(sourcePtr);
			}
		}

		comeBack(sourcePtr);
		str_g[_MIN(pos, maxStrLen_g - 1)] = '\0';
		yylloc.last_column += pos;
		
		/* check for keywords */
		int keywordCode = getKeywordCode(str_g);

		if (keywordCode > 0)
		{
			return keywordCode;
		}
		else
		{
			yylval = createNode(ND_NAME, str_g,
				yylloc.first_line, yylloc.first_column);
			return NAME;
		}
    }
	
	yylloc.last_column++;
	return ch;
}
