/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "gram.y" /* yacc.c:339  */

#include "root.h"
#include "lex.h"
#include "ast.h"
#define YYSTYPE ast_t *

extern int yylex();
void yyerror(lex_t *lex, ast_t **module, char *message);

#line 76 "gram.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "gram.tab.h".  */
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

/* Copy the second part of user declarations.  */

#line 181 "gram.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   636

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  77
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  146
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  255

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   309

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      66,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    64,    50,     2,
      69,    70,    62,    60,    71,    61,    74,    63,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    68,     2,
      53,    67,    55,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    72,     2,    73,    49,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    75,    48,    76,    65,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    51,    52,    54,    56,    57,    58,    59
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    45,    45,    51,    52,    53,    58,    59,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      78,    80,    85,    90,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   109,   114,   119,   124,   129,
     134,   139,   144,   149,   151,   156,   157,   158,   159,   160,
     161,   162,   163,   167,   172,   176,   178,   180,   185,   190,
     195,   197,   201,   206,   208,   210,   215,   220,   222,   224,
     229,   234,   239,   244,   246,   251,   253,   258,   264,   265,
     267,   272,   273,   278,   279,   281,   283,   285,   287,   289,
     291,   293,   295,   297,   299,   301,   303,   305,   307,   309,
     311,   313,   318,   319,   324,   325,   326,   327,   331,   332,
     334,   336,   338,   343,   345,   351,   352,   356,   358,   364,
     365,   370,   372,   377,   378,   379,   380,   381,   382,   383,
     385,   386,   387,   391,   393,   398,   400,   405,   407,   412,
     414,   419,   424,   426,   428,   433,   435
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_BEGIN", "TOKEN_END",
  "TOKEN_GLOBAL", "TOKEN_FROM", "TOKEN_IMPORT", "TOKEN_DEL", "TOKEN_PASS",
  "TOKEN_PRINT", "TOKEN_ASSERT", "TOKEN_IF", "TOKEN_ELIF", "TOKEN_ELSE",
  "TOKEN_FOR", "TOKEN_WHILE", "TOKEN_IN", "TOKEN_CONTINUE", "TOKEN_BREAK",
  "TOKEN_RETURN", "TOKEN_TRY", "TOKEN_EXCEPT", "TOKEN_AS", "TOKEN_FINALLY",
  "TOKEN_RAISE", "TOKEN_CLASS", "TOKEN_DEF", "TOKEN_LAMBDA",
  "TOKEN_DOUBLE_CONST", "TOKEN_STRING_CONST", "TOKEN_ID", "TOKEN_NONE",
  "TOKEN_TRUE", "TOKEN_FALSE", "TOKEN_MUL_ASSIGN", "TOKEN_DIV_ASSIGN",
  "TOKEN_MOD_ASSIGN", "TOKEN_ADD_ASSIGN", "TOKEN_SUB_ASSIGN",
  "TOKEN_LSH_ASSIGN", "TOKEN_RSH_ASSIGN", "TOKEN_AND_ASSIGN",
  "TOKEN_XOR_ASSIGN", "TOKEN_OR_ASSIGN", "TOKEN_OR", "TOKEN_AND",
  "TOKEN_IS", "'|'", "'^'", "'&'", "TOKEN_EQ", "TOKEN_NE", "'<'",
  "TOKEN_LE", "'>'", "TOKEN_GE", "TOKEN_LSH", "TOKEN_RSH", "TOKEN_NOT",
  "'+'", "'-'", "'*'", "'/'", "'%'", "'~'", "'\\n'", "'='", "':'", "'('",
  "')'", "','", "'['", "']'", "'.'", "'{'", "'}'", "$accept", "start",
  "clause_list", "clause", "simple_clause", "print_clause",
  "express_clause", "assign_clause", "assign_operator", "del_clause",
  "pass_clause", "import_clause", "from_clause", "global_clause",
  "assert_clause", "break_clause", "continue_clause", "return_clause",
  "compound_clause", "group_clause", "colon", "if_clause", "elif_clause",
  "else_clause", "while_clause", "for_clause", "try_clause", "try_body",
  "except_clause", "finally_clause", "raise_clause", "def_clause",
  "signature", "param_list", "class_clause", "parent", "express",
  "binary_express", "unary_express", "unary_operator", "postfix_express",
  "slice_express", "id_list", "id_list0", "arg_list", "arg_list0",
  "primary_express", "list_express", "list_item_list", "dict_express",
  "dict_item_list", "dict_item", "tuple_express", "tuple_item_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   124,    94,
      38,   303,   304,    60,   305,    62,   306,   307,   308,   309,
      43,    45,    42,    47,    37,   126,    10,    61,    58,    40,
      41,    44,    91,    93,    46,   123,   125
};
# endif

#define YYPACT_NINF -74

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-74)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -74,    17,   252,   -74,   -74,    -2,    15,    -2,   399,    -1,
       8,   399,   399,   399,   399,     6,    12,    89,   -10,   399,
      24,    54,    -2,   -74,   -74,   -74,   -74,   -74,   -74,   -74,
     -74,   -74,   -74,   -74,   269,   317,    18,   -74,   -74,   -74,
     -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,
     -74,   -74,   -74,    57,   -74,   -74,   -74,    40,   -74,   -74,
     -74,   488,   489,   -74,   446,   -13,   -74,   -74,   -74,   -74,
     181,   -74,    13,    21,    81,    32,    35,   -74,   -74,    36,
      47,   -10,    97,   -10,   -74,   -74,   -74,    50,    60,   103,
      66,    64,    68,    70,   -74,     5,   -74,   -74,   -41,   -74,
      71,   -58,   -74,   399,   -10,   -74,   -74,   334,   -10,   116,
     -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,
     -74,   -74,   -74,   399,   446,   446,   446,   446,   446,   446,
     446,   446,   446,   446,   446,   446,   446,   446,   446,   446,
     446,   446,   -74,   399,   399,   113,   -74,   -74,   115,    -2,
     -74,   -74,   -74,   -74,   103,   399,   103,   -74,   -74,   -74,
     -74,   -17,   -10,   -16,   -10,   446,   -74,   382,   399,   -74,
     399,    -9,   -74,   -10,   103,   103,   -11,   103,   -74,    85,
     510,   527,   543,   558,   572,   114,   114,    67,    67,    67,
      67,    48,    48,   -19,   -19,   -74,   -74,   -74,   -74,    82,
      92,   -40,    83,   -74,   -74,    99,   -74,   -10,   165,   110,
     -74,   103,   -74,   -74,    11,   103,   489,   -74,   -74,    26,
     -74,   -74,   -74,   103,   -74,   -74,   150,   103,   -74,   -74,
     -74,   399,   399,   -74,   -74,   -74,   103,   -74,   -74,   -74,
     -74,   151,   -74,   -74,   399,   -74,   -10,   -74,   -74,   -74,
     -74,   -74,   -74,   103,   -74
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,     3,   115,     0,   115,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   115,   127,   128,   126,   123,   124,   125,   107,
     104,   105,   106,     4,     0,     0,     0,     5,     6,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,     7,    45,    46,    47,    48,    51,     0,    52,    49,
      50,     0,    81,    83,     0,   102,   108,   130,   131,   132,
       0,   117,     0,   116,     0,     0,     0,    36,    20,     0,
       0,     0,     0,     0,    42,    41,    43,     0,     0,     0,
       0,    78,     0,     0,   142,     0,   133,   135,     0,   137,
       0,     0,   139,     0,     0,    56,    57,     0,     0,    63,
      64,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   103,   119,     0,     0,    53,    39,     0,   115,
      37,    35,    21,    40,     0,     0,     0,    44,    54,    66,
      71,     0,     0,     0,     0,     0,   129,     0,     0,   134,
       0,     0,   138,     0,     0,     0,     0,     0,    65,     0,
      84,    85,    86,    87,    88,    89,    90,    91,    93,    92,
      94,    95,    96,    97,    98,    99,   100,   101,   121,     0,
     120,     0,     0,   112,   118,     0,    55,     0,    60,     0,
      79,     0,    75,    73,     0,     0,    82,   143,   145,     0,
     136,   141,   140,     0,    59,    67,     0,     0,    70,    23,
     109,     0,   114,   110,   111,    38,     0,    61,    80,    77,
      74,     0,    72,   144,     0,    58,     0,    68,   122,   113,
      62,    76,   146,     0,    69
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -74,   -74,   190,   -74,   -74,   -74,   -74,   -74,   -74,   -74,
     -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,   -70,
     -73,   -74,   -74,    -5,   -74,   -74,   -74,   -74,   -74,    86,
     -74,   -74,   -74,   -74,   -74,   -74,    -8,   357,   134,   -74,
     -74,   -74,    -6,   -74,   -74,   -74,   -29,   -74,   -74,   -74,
     -74,    33,   -74,   -74
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    37,    38,    39,    40,    41,   123,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      89,    53,   105,   106,    54,    55,    56,    57,   109,   110,
      58,    59,   164,   214,    60,   162,    61,    62,    63,    64,
      65,   202,    72,    73,   199,   200,    66,    67,    98,    68,
     101,   102,    69,   219
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      76,    75,    79,    80,    81,    82,    83,   100,   154,    87,
     156,    90,   226,   171,   209,   212,    93,     3,   172,   159,
      23,    24,    25,    26,    27,    28,    95,    97,   232,    71,
     168,   174,   169,   233,   175,   177,    22,    23,    24,    25,
      26,    27,    28,   139,   140,   141,    74,    23,    24,    25,
      26,    27,    28,   210,   213,    91,   143,    88,    88,   144,
      34,   145,   107,    35,   108,    77,    36,    29,    30,    31,
     103,   104,    84,    32,    78,   166,   167,    34,    85,   147,
      35,   240,   241,    36,   206,    92,   208,    34,   149,   211,
      35,   215,   148,    36,    99,   173,   243,   244,   150,   176,
     223,   151,   152,   227,   224,   225,     4,   228,   137,   138,
     139,   140,   141,   153,   155,   179,   157,    22,    23,    24,
      25,    26,    27,    28,   135,   136,   158,   137,   138,   139,
     140,   141,   160,   161,   236,   198,   201,   163,   165,   170,
     108,   239,   100,   205,   203,   242,   204,   207,    29,    30,
      31,   229,   230,   245,    32,    86,   234,   247,    34,   218,
     220,    35,   221,   231,    36,   235,   250,   131,   132,   133,
     134,   135,   136,   253,   137,   138,   139,   140,   141,   104,
     238,   246,   251,   254,     4,   146,     5,     6,     7,     8,
       9,    10,    11,    12,    70,   178,    13,    14,   142,    15,
      16,    17,    18,   237,   222,     0,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
       0,     0,     0,   248,   249,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   252,     0,     0,     0,
      29,    30,    31,     0,     0,     0,    32,    33,     0,     0,
      34,     0,     0,    35,     0,     4,    36,     5,     6,     7,
       8,     9,    10,    11,    12,     0,     0,    13,    14,     0,
      15,    16,    17,    18,     0,     0,     0,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    22,    23,    24,
      25,    26,    27,    28,     0,     0,     0,     0,     0,     0,
       0,    29,    30,    31,     0,     0,     0,    32,    33,     0,
       0,    34,     0,     0,    35,     0,     0,    36,    29,    30,
      31,     0,     0,     0,    32,     0,     0,     0,    34,    94,
       0,    35,     0,     0,    36,    22,    23,    24,    25,    26,
      27,    28,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    22,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,     0,     0,     0,    29,    30,    31,     0,
       0,     0,    32,     0,     0,     0,    34,     0,     0,    35,
      96,     0,    36,    29,    30,    31,     0,     0,     0,    32,
       0,     0,    88,    34,     0,     0,    35,     0,     0,    36,
      22,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    22,    23,    24,
      25,    26,    27,    28,     0,     0,     0,     0,     0,     0,
       0,    29,    30,    31,     0,     0,     0,    32,     0,     0,
       0,    34,   217,     0,    35,     0,     0,    36,    29,    30,
      31,     0,     0,     0,    32,     0,     0,     0,    34,     0,
       0,    35,     0,     0,    36,    23,    24,    25,    26,    27,
      28,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,     0,
       0,     0,     0,     0,     0,    29,    30,    31,     0,     0,
       0,    32,     0,     0,     0,    34,     0,     0,    35,     0,
       0,    36,   216,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,     0,   124,   125,     0,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,     0,   137,
     138,   139,   140,   141,   121,   122,   125,     0,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,     0,
     137,   138,   139,   140,   141,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,     0,   137,   138,   139,
     140,   141,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,     0,   137,   138,   139,   140,   141,   128,   129,
     130,   131,   132,   133,   134,   135,   136,     0,   137,   138,
     139,   140,   141,   129,   130,   131,   132,   133,   134,   135,
     136,     0,   137,   138,   139,   140,   141
};

static const yytype_int16 yycheck[] =
{
       8,     7,    10,    11,    12,    13,    14,    36,    81,    17,
      83,    19,    23,    71,    31,    31,    22,     0,    76,    89,
      29,    30,    31,    32,    33,    34,    34,    35,    68,    31,
      71,   104,    73,    73,   107,   108,    28,    29,    30,    31,
      32,    33,    34,    62,    63,    64,    31,    29,    30,    31,
      32,    33,    34,    70,    70,    31,    69,    68,    68,    72,
      69,    74,    22,    72,    24,    66,    75,    59,    60,    61,
      13,    14,    66,    65,    66,    70,    71,    69,    66,    66,
      72,    70,    71,    75,   154,    31,   156,    69,     7,   162,
      72,   164,    71,    75,    76,   103,    70,    71,    66,   107,
     173,    66,    66,   176,   174,   175,     3,   177,    60,    61,
      62,    63,    64,    66,    17,   123,    66,    28,    29,    30,
      31,    32,    33,    34,    57,    58,    66,    60,    61,    62,
      63,    64,    66,    69,   207,   143,   144,    69,    68,    68,
      24,   211,   171,   149,    31,   215,    31,   155,    59,    60,
      61,    66,    70,   223,    65,    66,    73,   227,    69,   167,
     168,    72,   170,    71,    75,    66,   236,    53,    54,    55,
      56,    57,    58,   246,    60,    61,    62,    63,    64,    14,
      70,    31,    31,   253,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,     4,   109,    15,    16,    64,    18,
      19,    20,    21,   208,   171,    -1,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   231,   232,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   244,    -1,    -1,    -1,
      59,    60,    61,    -1,    -1,    -1,    65,    66,    -1,    -1,
      69,    -1,    -1,    72,    -1,     3,    75,     5,     6,     7,
       8,     9,    10,    11,    12,    -1,    -1,    15,    16,    -1,
      18,    19,    20,    21,    -1,    -1,    -1,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    59,    60,    61,    -1,    -1,    -1,    65,    66,    -1,
      -1,    69,    -1,    -1,    72,    -1,    -1,    75,    59,    60,
      61,    -1,    -1,    -1,    65,    -1,    -1,    -1,    69,    70,
      -1,    72,    -1,    -1,    75,    28,    29,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    29,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    59,    60,    61,    -1,
      -1,    -1,    65,    -1,    -1,    -1,    69,    -1,    -1,    72,
      73,    -1,    75,    59,    60,    61,    -1,    -1,    -1,    65,
      -1,    -1,    68,    69,    -1,    -1,    72,    -1,    -1,    75,
      28,    29,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    59,    60,    61,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    69,    70,    -1,    72,    -1,    -1,    75,    59,    60,
      61,    -1,    -1,    -1,    65,    -1,    -1,    -1,    69,    -1,
      -1,    72,    -1,    -1,    75,    29,    30,    31,    32,    33,
      34,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    60,    61,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    69,    -1,    -1,    72,    -1,
      -1,    75,   165,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    -1,    45,    46,    -1,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    -1,    60,
      61,    62,    63,    64,    66,    67,    46,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    -1,
      60,    61,    62,    63,    64,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    -1,    60,    61,    62,
      63,    64,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    -1,    60,    61,    62,    63,    64,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    -1,    60,    61,
      62,    63,    64,    51,    52,    53,    54,    55,    56,    57,
      58,    -1,    60,    61,    62,    63,    64
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    78,    79,     0,     3,     5,     6,     7,     8,     9,
      10,    11,    12,    15,    16,    18,    19,    20,    21,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    59,
      60,    61,    65,    66,    69,    72,    75,    80,    81,    82,
      83,    84,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    98,   101,   102,   103,   104,   107,   108,
     111,   113,   114,   115,   116,   117,   123,   124,   126,   129,
      79,    31,   119,   120,    31,   119,   113,    66,    66,   113,
     113,   113,   113,   113,    66,    66,    66,   113,    68,    97,
     113,    31,    31,   119,    70,   113,    73,   113,   125,    76,
     123,   127,   128,    13,    14,    99,   100,    22,    24,   105,
     106,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    66,    67,    85,    45,    46,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    60,    61,    62,
      63,    64,   115,    69,    72,    74,     4,    66,    71,     7,
      66,    66,    66,    66,    97,    17,    97,    66,    66,    96,
      66,    69,   112,    69,   109,    68,    70,    71,    71,    73,
      68,    71,    76,   113,    97,    97,   113,    97,   106,   113,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   113,   121,
     122,   113,   118,    31,    31,   119,    96,   113,    96,    31,
      70,    97,    31,    70,   110,    97,   114,    70,   113,   130,
     113,   113,   128,    97,    96,    96,    23,    97,    96,    66,
      70,    71,    68,    73,    73,    66,    97,   100,    70,    96,
      70,    71,    96,    70,    71,    96,    31,    96,   113,   113,
      96,    31,   113,    97,    96
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    77,    78,    79,    79,    79,    80,    80,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      82,    82,    83,    84,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    94,    95,    95,    95,    95,    95,
      95,    95,    95,    96,    97,    98,    98,    98,    99,   100,
     101,   101,   102,   103,   103,   103,   104,   105,   105,   105,
     106,   107,   108,   109,   109,   110,   110,   111,   112,   112,
     112,   113,   113,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   115,   115,   116,   116,   116,   116,   117,   117,
     117,   117,   117,   118,   118,   119,   119,   120,   120,   121,
     121,   122,   122,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   124,   124,   125,   125,   126,   126,   127,
     127,   128,   129,   129,   129,   130,   130
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     3,     2,     4,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     2,     3,     5,     3,
       3,     2,     2,     2,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     2,     4,     2,     2,     4,     3,
       4,     5,     6,     2,     2,     3,     3,     3,     4,     6,
       3,     3,     5,     2,     3,     1,     3,     5,     0,     2,
       3,     1,     4,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     2,     1,     1,     1,     1,     1,     4,
       4,     4,     3,     3,     2,     0,     1,     1,     3,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     2,     3,     1,     3,     2,     3,     1,
       3,     3,     2,     4,     5,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      yyerror (lex, module, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, lex, module); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, lex_t *lex, ast_t **module)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (lex);
  YYUSE (module);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, lex_t *lex, ast_t **module)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, lex, module);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, lex_t *lex, ast_t **module)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              , lex, module);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, lex, module); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
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
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
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
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, lex_t *lex, ast_t **module)
{
  YYUSE (yyvaluep);
  YYUSE (lex);
  YYUSE (module);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (lex_t *lex, ast_t **module)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, lex);
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
        case 2:
#line 46 "gram.y" /* yacc.c:1646  */
    { (yyval) = *module = (yyvsp[0]);                                           }
#line 1544 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 51 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_CLAUSE_LIST, 0);                            }
#line 1550 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 54 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_add_child((yyvsp[-1]), (yyvsp[0]));                                  }
#line 1556 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 79 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_PRINT_CLAUSE, 1, NULL);                     }
#line 1562 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 81 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_PRINT_CLAUSE, 1, (yyvsp[-1]));                       }
#line 1568 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 86 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_EXPRESS_CLAUSE, 1, (yyvsp[-1]));                     }
#line 1574 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 91 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_ASSIGN_CLAUSE, 3, (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]));              }
#line 1580 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 110 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_DEL_CLAUSE, 1, (yyvsp[-1]));                         }
#line 1586 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 115 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_PASS_CLAUSE, 0);                            }
#line 1592 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 120 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_IMPORT_CLAUSE, 1, (yyvsp[-1]));                      }
#line 1598 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 125 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_FROM_CLAUSE, 2, (yyvsp[-3]), (yyvsp[-1]));                    }
#line 1604 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 130 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_GLOBAL_CLAUSE, 1, (yyvsp[-1]));                      }
#line 1610 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 135 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_ASSERT_CLAUSE, 0);                          }
#line 1616 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 140 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_BREAK_CLAUSE, 0);                           }
#line 1622 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 145 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_CONTINUE_CLAUSE, 0);                        }
#line 1628 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 150 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_RETURN_CLAUSE, 1, NULL);                    }
#line 1634 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 152 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_RETURN_CLAUSE, 1, (yyvsp[-1]));                      }
#line 1640 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 168 "gram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]);                                                     }
#line 1646 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 177 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_IF_CLAUSE, 2, (yyvsp[-2]), (yyvsp[0]));                      }
#line 1652 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 179 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_add_child((yyvsp[-1]), (yyvsp[0]));                                  }
#line 1658 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 181 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_add_child((yyvsp[-1]), (yyvsp[0]));                                  }
#line 1664 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 186 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_ELIF_CLAUSE, 2, (yyvsp[-2]), (yyvsp[0]));                    }
#line 1670 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 191 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_ELSE_CLAUSE, 1, (yyvsp[0]));                        }
#line 1676 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 196 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_WHILE_CLAUSE, 2, (yyvsp[-2]), (yyvsp[0]));                   }
#line 1682 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 202 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_FOR_CLAUSE, 3, (yyvsp[-4]), (yyvsp[-2]), (yyvsp[0]));                 }
#line 1688 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 207 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_TRY_CLAUSE, 3, (yyvsp[-1]), (yyvsp[0]), NULL);               }
#line 1694 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 209 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_TRY_CLAUSE, 3, (yyvsp[-1]), NULL, (yyvsp[0]));               }
#line 1700 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 211 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_TRY_CLAUSE, 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]));                 }
#line 1706 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 216 "gram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]);                                                     }
#line 1712 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 221 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_EXCEPT_CLAUSE, 3, NULL, NULL, (yyvsp[0]));          }
#line 1718 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 223 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_EXCEPT_CLAUSE, 3, (yyvsp[-2]), NULL, (yyvsp[0]));            }
#line 1724 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 225 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_EXCEPT_CLAUSE, 3, (yyvsp[-4]), (yyvsp[-2]), (yyvsp[0]));              }
#line 1730 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 230 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_FINALLY_CLAUSE, 1, (yyvsp[0]));                     }
#line 1736 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 235 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_RAISE_CLAUSE, 1, (yyvsp[-1]));                       }
#line 1742 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 240 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_DEF_CLAUSE, 3, (yyvsp[-3]), (yyvsp[-2]), (yyvsp[0]));                 }
#line 1748 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 245 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_PARAM_LIST, 0);                             }
#line 1754 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 247 "gram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]);                                                     }
#line 1760 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 252 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_PARAM_LIST, 1, (yyvsp[0]));                         }
#line 1766 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 254 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_add_child((yyvsp[-2]), (yyvsp[0]));                                  }
#line 1772 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 259 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_CLASS_CLAUSE, 3, (yyvsp[-3]), (yyvsp[-2]), (yyvsp[0]));               }
#line 1778 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 264 "gram.y" /* yacc.c:1646  */
    { (yyval) = NULL;                                                   }
#line 1784 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 266 "gram.y" /* yacc.c:1646  */
    { (yyval) = NULL;                                                   }
#line 1790 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 268 "gram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]);                                                     }
#line 1796 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 274 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_LAMBDA_EXPRESS, 2, (yyvsp[-2]), (yyvsp[0]));                 }
#line 1802 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 280 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_BINARY_EXPRESS, 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]));             }
#line 1808 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 282 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_BINARY_EXPRESS, 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]));             }
#line 1814 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 284 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_BINARY_EXPRESS, 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]));             }
#line 1820 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 286 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_BINARY_EXPRESS, 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]));             }
#line 1826 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 288 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_BINARY_EXPRESS, 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]));             }
#line 1832 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 290 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_BINARY_EXPRESS, 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]));             }
#line 1838 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 292 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_BINARY_EXPRESS, 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]));             }
#line 1844 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 294 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_BINARY_EXPRESS, 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]));             }
#line 1850 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 296 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_BINARY_EXPRESS, 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]));             }
#line 1856 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 298 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_BINARY_EXPRESS, 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]));             }
#line 1862 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 300 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_BINARY_EXPRESS, 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]));             }
#line 1868 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 302 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_BINARY_EXPRESS, 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]));             }
#line 1874 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 304 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_BINARY_EXPRESS, 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]));             }
#line 1880 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 306 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_BINARY_EXPRESS, 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]));             }
#line 1886 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 308 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_BINARY_EXPRESS, 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]));             }
#line 1892 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 310 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_BINARY_EXPRESS, 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]));             }
#line 1898 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 312 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_BINARY_EXPRESS, 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]));             }
#line 1904 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 314 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_BINARY_EXPRESS, 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]));             }
#line 1910 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 320 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_UNARY_EXPRESS, 2, (yyvsp[-1]), (yyvsp[0]));                  }
#line 1916 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 333 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_CALL_EXPRESS, 2, (yyvsp[-3]), (yyvsp[-1]));                   }
#line 1922 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 335 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_ITEM_EXPRESS, 2, (yyvsp[-3]), (yyvsp[-1]));                   }
#line 1928 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 337 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_ITEM_EXPRESS, 2, (yyvsp[-3]), (yyvsp[-1]));                   }
#line 1934 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 339 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_FIELD_EXPRESS, 2, (yyvsp[-2]), (yyvsp[0]));                  }
#line 1940 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 344 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_SLICE_EXPRESS, 2, (yyvsp[-2]), (yyvsp[0]));                  }
#line 1946 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 346 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_SLICE_EXPRESS, 2, (yyvsp[-1]), NULL);                }
#line 1952 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 351 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_ID_LIST, 0);                                }
#line 1958 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 357 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_ID_LIST, 1, (yyvsp[0]));                            }
#line 1964 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 359 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_add_child((yyvsp[-2]), (yyvsp[0]));                                  }
#line 1970 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 364 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_ARG_LIST, 0);                               }
#line 1976 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 366 "gram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]);                                                     }
#line 1982 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 371 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_ARG_LIST, 1, (yyvsp[0]));                           }
#line 1988 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 373 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_add_child((yyvsp[-2]), (yyvsp[0]));                                  }
#line 1994 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 384 "gram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]);                                                     }
#line 2000 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 392 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_LIST_EXPRESS, 0);                           }
#line 2006 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 394 "gram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]);                                                     }
#line 2012 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 399 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_LIST_EXPRESS, 1, (yyvsp[0]));                       }
#line 2018 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 401 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_add_child((yyvsp[-2]), (yyvsp[0]));                                  }
#line 2024 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 406 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_DICT_EXPRESS, 0);                           }
#line 2030 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 408 "gram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]);                                                     }
#line 2036 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 413 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_DICT_EXPRESS, 1, (yyvsp[0]));                       }
#line 2042 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 415 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_add_child((yyvsp[-2]), (yyvsp[0]));                                  }
#line 2048 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 420 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_DICT_ITEM, 2, (yyvsp[-2]), (yyvsp[0]));                      }
#line 2054 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 425 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_TUPLE_EXPRESS, 0);                          }
#line 2060 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 427 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_TUPLE_EXPRESS, 1, (yyvsp[-2]));                      }
#line 2066 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 429 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_prepend_child((yyvsp[-1]), (yyvsp[-3]));                              }
#line 2072 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 434 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_new(AST_TUPLE_EXPRESS, 1, (yyvsp[0]));                      }
#line 2078 "gram.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 436 "gram.y" /* yacc.c:1646  */
    { (yyval) = ast_add_child((yyvsp[-2]), (yyvsp[0]));                                  }
#line 2084 "gram.tab.c" /* yacc.c:1646  */
    break;


#line 2088 "gram.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (lex, module, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (lex, module, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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
                      yytoken, &yylval, lex, module);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, lex, module);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (lex, module, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, lex, module);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, lex, module);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 438 "gram.y" /* yacc.c:1906  */


int yylex(YYSTYPE *yylval, lex_t *lex)
{
    ast_t *token = lex_get_token(lex);
    *yylval = token;
    if (!token)
        return 0;
    return token->token;
}
