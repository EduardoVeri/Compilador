/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"

#define YYSTYPE PONTEIRONO
#define MAX_NOS 1000

static int yylex(void);
void yyerror(char* s);
int yyparse(void);

char auxNome[MAXLEXEMA];
char id[MAXLEXEMA];
enum yytokentype auxErro;

int teste = 0;

//No raiz da arvore sintatica
PONTEIRONO arvoreSintatica;


void mostraArvore(PONTEIRONO raiz, int num);
enum yytokentype getToken(void);
PONTEIRONO parse(void);

char auxLexema[MAXLEXEMA];
PONTEIRONO nos[MAX_NOS];
int qntNos = 0;


#line 104 "parser.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
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
    NUM = 258,
    SOMA = 259,
    SUB = 260,
    MULT = 261,
    DIV = 262,
    INT = 263,
    ID = 264,
    VOID = 265,
    WHILE = 266,
    ELSE = 267,
    IF = 268,
    ABREPARENTESES = 269,
    FECHAPARENTESES = 270,
    RETURN = 271,
    COMMA = 272,
    ABRECHAVES = 273,
    FECHACHAVES = 274,
    SEMICOLON = 275,
    ATRIB = 276,
    ABRECOLCHETES = 277,
    FECHACOLCHETES = 278,
    EQ = 279,
    NEQ = 280,
    LT = 281,
    LET = 282,
    GT = 283,
    GET = 284,
    ERRO = 285
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   99

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  106

#define YYUNDEFTOK  2
#define YYMAXUTOK   285


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    50,    50,    56,    65,    68,    69,    72,    90,   116,
     124,   135,   148,   162,   163,   175,   184,   187,   205,   224,
     235,   245,   248,   257,   260,   261,   262,   263,   264,   267,
     268,   271,   289,   290,   293,   309,   320,   334,   348,   351,
     371,   390,   400,   403,   408,   417,   426,   435,   444,   453,
     463,   472,   475,   482,   491,   501,   504,   511,   520,   521,
     522,   523,   539,   548,   549,   552,   558
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "SOMA", "SUB", "MULT", "DIV",
  "INT", "ID", "VOID", "WHILE", "ELSE", "IF", "ABREPARENTESES",
  "FECHAPARENTESES", "RETURN", "COMMA", "ABRECHAVES", "FECHACHAVES",
  "SEMICOLON", "ATRIB", "ABRECOLCHETES", "FECHACOLCHETES", "EQ", "NEQ",
  "LT", "LET", "GT", "GET", "ERRO", "$accept", "programa",
  "declaracao_lista", "declaracao", "var_declaracao", "tipo_especificador",
  "fun_declaracao", "fun_id", "params", "param_lista", "param",
  "composto_decl", "local_declaracoes", "statement_lista", "statement",
  "expressao_decl", "selecao_decl", "fatoracao", "iteracao_decl",
  "retorno_decl", "expressao", "var", "simples_expressao", "relacional",
  "operador_relacional", "soma_expressao", "soma", "termo", "mult",
  "fator", "ativacao", "args", "arg_lista", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285
};
# endif

#define YYPACT_NINF (-44)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-15)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      27,   -44,   -44,     2,    27,   -44,   -44,    -4,   -44,   -44,
     -44,    16,    -1,   -44,    14,    37,    17,     7,    43,    10,
      46,   -44,    49,    50,    53,    27,   -44,    52,   -44,   -44,
     -44,   -44,    27,   -44,    64,    30,    16,   -44,    20,    60,
      62,     0,     1,   -44,   -44,    63,   -44,   -44,   -44,   -44,
     -44,   -44,    58,    59,   -44,     3,     5,   -44,   -44,     0,
       0,     0,    66,   -44,    65,     0,   -44,     0,   -44,   -44,
     -44,   -44,   -44,   -44,   -44,   -44,     0,   -44,     0,   -44,
     -44,     0,    56,    67,    68,   -44,   -44,   -44,    69,    70,
     -44,   -44,    51,     5,   -44,   -44,    48,    48,   -44,     0,
     -44,    74,   -44,    48,   -44,   -44
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     9,    10,     0,     2,     4,     5,     0,     6,     1,
       3,    12,     0,     7,     0,     0,     0,    10,     0,     0,
      13,    16,     0,    17,     0,     0,     8,     0,    21,    11,
      15,    18,    23,    20,     0,     0,     0,    61,    39,     0,
       0,     0,     0,    19,    30,     0,    25,    22,    24,    26,
      27,    28,     0,    59,    38,    42,    51,    55,    60,     0,
       0,     0,     0,    35,     0,    64,    29,     0,    52,    53,
      44,    45,    46,    48,    47,    49,     0,    43,     0,    56,
      57,     0,     0,     0,     0,    58,    36,    66,     0,    63,
      37,    59,    41,    50,    54,    40,     0,     0,    62,     0,
      34,    33,    65,     0,    31,    32
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -44,   -44,   -44,    84,    57,    -9,   -44,    83,   -44,   -44,
      71,    73,   -44,   -44,   -43,   -44,   -44,   -44,   -44,   -44,
     -41,   -11,   -44,   -44,   -44,    15,   -44,    21,   -44,    11,
     -44,   -44,   -44
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,     8,    45,    19,    20,
      21,    46,    32,    35,    47,    48,    49,   104,    50,    51,
      52,    53,    54,    76,    77,    55,    78,    56,    81,    57,
      58,    88,    89
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      62,    64,     9,    37,    37,    11,    18,    68,    69,    38,
      38,    79,    80,    15,    41,    41,    18,    16,    82,    83,
      84,    63,   -14,    34,    87,    24,    90,    70,    71,    72,
      73,    74,    75,    37,   -12,     1,    13,     2,    14,    38,
      22,    39,    59,    40,    41,     1,    42,    17,    28,    43,
      44,    37,    23,   100,   101,    68,    69,    38,   102,    39,
     105,    40,    41,    25,    42,    91,    28,    91,    44,    26,
      91,    28,    27,    36,    60,    31,    61,    65,    66,    95,
      67,    85,    96,    97,    98,    86,   103,    99,    10,    33,
      12,    92,    94,     0,     0,     0,    30,    29,     0,    93
};

static const yytype_int8 yycheck[] =
{
      41,    42,     0,     3,     3,     9,    15,     4,     5,     9,
       9,     6,     7,    14,    14,    14,    25,     3,    59,    60,
      61,    20,    15,    32,    65,    15,    67,    24,    25,    26,
      27,    28,    29,     3,    14,     8,    20,    10,    22,     9,
      23,    11,    22,    13,    14,     8,    16,    10,    18,    19,
      20,     3,     9,    96,    97,     4,     5,     9,    99,    11,
     103,    13,    14,    17,    16,    76,    18,    78,    20,    20,
      81,    18,    22,     9,    14,    23,    14,    14,    20,    23,
      21,    15,    15,    15,    15,    20,    12,    17,     4,    32,
       7,    76,    81,    -1,    -1,    -1,    25,    24,    -1,    78
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     8,    10,    32,    33,    34,    35,    36,    37,     0,
      34,     9,    38,    20,    22,    14,     3,    10,    36,    39,
      40,    41,    23,     9,    15,    17,    20,    22,    18,    42,
      41,    23,    43,    35,    36,    44,     9,     3,     9,    11,
      13,    14,    16,    19,    20,    38,    42,    45,    46,    47,
      49,    50,    51,    52,    53,    56,    58,    60,    61,    22,
      14,    14,    51,    20,    51,    14,    20,    21,     4,     5,
      24,    25,    26,    27,    28,    29,    54,    55,    57,     6,
       7,    59,    51,    51,    51,    15,    20,    51,    62,    63,
      51,    52,    56,    58,    60,    23,    15,    15,    15,    17,
      45,    45,    51,    12,    48,    45
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    35,    35,    36,
      36,    37,    38,    39,    39,    40,    40,    41,    41,    42,
      43,    43,    44,    44,    45,    45,    45,    45,    45,    46,
      46,    47,    48,    48,    49,    50,    50,    51,    51,    52,
      52,    53,    53,    54,    55,    55,    55,    55,    55,    55,
      56,    56,    57,    57,    58,    58,    59,    59,    60,    60,
      60,    60,    61,    62,    62,    63,    63
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     6,     1,
       1,     6,     1,     1,     1,     3,     1,     2,     4,     4,
       2,     0,     2,     0,     1,     1,     1,     1,     1,     2,
       1,     6,     2,     0,     5,     2,     3,     3,     1,     1,
       4,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     3,     1,     1,     1,     3,     1,
       1,     1,     4,     1,     0,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
  case 2:
#line 50 "parser.y"
                                                   {
                        arvoreSintatica = yyvsp[0];
                    }
#line 1434 "parser.c"
    break;

  case 3:
#line 56 "parser.y"
                                                      {  
                        if(yyvsp[-1] != NULL){
                            yyval = yyvsp[-1];
                            adicionaIrmao(yyval, yyvsp[0]);
                        }
                        else{
                            yyval = yyvsp[0];
                        }
                      }
#line 1448 "parser.c"
    break;

  case 4:
#line 65 "parser.y"
                                 {yyval = yyvsp[0];}
#line 1454 "parser.c"
    break;

  case 5:
#line 68 "parser.y"
                                                 {yyval = yyvsp[0];}
#line 1460 "parser.c"
    break;

  case 6:
#line 69 "parser.y"
                                     {yyval = yyvsp[0];}
#line 1466 "parser.c"
    break;

  case 7:
#line 72 "parser.y"
                                                          {
                        yyval = yyvsp[-2];
                        yyval->tipo = DECLARACAO;
                        yyval->tipoDeclaracao = VarDeclK;
                        yyval->numLinha = qntLinhas;
                    
                        PONTEIRONO aux = novoNo();

                        strcpy(aux->lexema, pilha[indPilha]);
                        indPilha--;

                        //strcpy(aux->lexema, id);
                        adicionaFilho(yyval, aux);

                        nos[qntNos] = aux;
                        qntNos++;

                        }
#line 1489 "parser.c"
    break;

  case 8:
#line 90 "parser.y"
                                                                                       {
                        yyval = yyvsp[-5];
                        yyval->tipo = DECLARACAO;
                        yyval->tipoDeclaracao = VetDeclK;
                        yyval->numLinha = qntLinhas;

                        PONTEIRONO aux = novoNo();
                        PONTEIRONO aux2 = novoNo();
                        
                        strcpy(aux->lexema, pilha[indPilha]);
                        indPilha--;

                        nos[qntNos] = aux;
                        qntNos++;

                        strcpy(aux2->lexema, pilha[indPilha]);
                        indPilha--;
                        
                        adicionaFilho(yyval, aux2);
                        adicionaFilho(yyval, aux);

                        nos[qntNos] = aux2;
                        qntNos++;
                    }
#line 1518 "parser.c"
    break;

  case 9:
#line 116 "parser.y"
                              {
                        yyval = novoNo();
                        strcpy(yyval->lexema, "INT");
                        yyval->numLinha = qntLinhas;

                        nos[qntNos] = yyval;
                        qntNos++;
                    }
#line 1531 "parser.c"
    break;

  case 10:
#line 124 "parser.y"
                           {
                        yyval = novoNo();
                        strcpy(yyval->lexema, "VOID");
                        yyval->numLinha = qntLinhas;

                        nos[qntNos] = yyval;
                        qntNos++;
                    }
#line 1544 "parser.c"
    break;

  case 11:
#line 135 "parser.y"
                                                                                                        { 
                        //strcpy(auxLexema, "")
                        yyval = yyvsp[-5];

                        adicionaFilho(yyval, yyvsp[-2]);
                        adicionaFilho(yyval, yyvsp[-4]);
                        adicionaFilho(yyvsp[-4], yyvsp[0]);
                        
                        yyval->tipo = DECLARACAO;
                        yyval->tipoDeclaracao = FunDeclK;
                    }
#line 1560 "parser.c"
    break;

  case 12:
#line 148 "parser.y"
                                     {
                        yyval = novoNo();
                        
                        strcpy(yyval->lexema, pilha[indPilha]);
                        indPilha--;

                        //strcpy($$->lexema, auxNome);
                        yyval->numLinha = qntLinhas;

                        nos[qntNos] = yyval;
                        qntNos++;
                    }
#line 1577 "parser.c"
    break;

  case 13:
#line 162 "parser.y"
                                              {yyval = yyvsp[0];}
#line 1583 "parser.c"
    break;

  case 14:
#line 163 "parser.y"
                           {
                        yyval = novoNo();
                        yyval->tipo = DECLARACAO;
                        yyval->numLinha = qntLinhas;
                        yyval->tipoDeclaracao = ParamVoid;
                        strcpy(yyval->lexema, "VOID");

                        nos[qntNos] = yyval;
                        qntNos++;
                    }
#line 1598 "parser.c"
    break;

  case 15:
#line 175 "parser.y"
                                                          {
                        if(yyvsp[-2] != NULL){
                            yyval = yyvsp[-2];
                            adicionaIrmao(yyval, yyvsp[0]);
                        }
                        else{
                            yyval = yyvsp[0];
                        }						
                    }
#line 1612 "parser.c"
    break;

  case 16:
#line 184 "parser.y"
                            {yyval = yyvsp[0];}
#line 1618 "parser.c"
    break;

  case 17:
#line 187 "parser.y"
                                                        {
                        yyval = yyvsp[-1];
                        yyval->tipo = DECLARACAO;
                        yyval->numLinha = qntLinhas;
                        yyval->tipoDeclaracao = VarParamK;

                        PONTEIRONO aux = novoNo();

                        strcpy(aux->lexema, pilha[indPilha]);
                        indPilha--;
                    
                        //strcpy(aux->lexema, id);
                        adicionaFilho(yyval, aux);

                        nos[qntNos] = aux;
                        qntNos++;

                    }
#line 1641 "parser.c"
    break;

  case 18:
#line 205 "parser.y"
                                                                         {
                        yyval = yyvsp[-3];
                        yyval->tipo = DECLARACAO;
                        yyval->numLinha = qntLinhas;
                        yyval->tipoDeclaracao = VetParamK;
                        PONTEIRONO aux = novoNo();

    
                        strcpy(aux->lexema, pilha[indPilha]);
                        indPilha--;

                        //strcpy(aux->lexema, id);
                        adicionaFilho(yyval, aux);		

                        nos[qntNos] = aux;
                        qntNos++;	
                    }
#line 1663 "parser.c"
    break;

  case 19:
#line 224 "parser.y"
                                                                                   { 
                        if(yyvsp[-2] != NULL){
                            yyval = yyvsp[-2];
                            adicionaIrmao(yyval, yyvsp[-1]);
                        }
                        else{
                            yyval = yyvsp[-1];
                        }
                    }
#line 1677 "parser.c"
    break;

  case 20:
#line 235 "parser.y"
                                                           {
                        if(yyvsp[-1] != NULL){
                            yyval = yyvsp[-1];
                            adicionaIrmao(yyval, yyvsp[0]);
                        }
                        else{
                            yyval = yyvsp[0];
                        }

                    }
#line 1692 "parser.c"
    break;

  case 21:
#line 245 "parser.y"
                             {yyval = NULL;}
#line 1698 "parser.c"
    break;

  case 22:
#line 248 "parser.y"
                                                    {
                        if(yyvsp[-1] != NULL){
                            yyval = yyvsp[-1];
                            adicionaIrmao(yyval, yyvsp[0]);
                        }
                        else{
                            yyval = yyvsp[0];
                        }
                    }
#line 1712 "parser.c"
    break;

  case 23:
#line 257 "parser.y"
                             {yyval = NULL;}
#line 1718 "parser.c"
    break;

  case 24:
#line 260 "parser.y"
                                                 {yyval = yyvsp[0];}
#line 1724 "parser.c"
    break;

  case 25:
#line 261 "parser.y"
                                    {yyval = yyvsp[0];}
#line 1730 "parser.c"
    break;

  case 26:
#line 262 "parser.y"
                                   {yyval = yyvsp[0];}
#line 1736 "parser.c"
    break;

  case 27:
#line 263 "parser.y"
                                    {yyval = yyvsp[0];}
#line 1742 "parser.c"
    break;

  case 28:
#line 264 "parser.y"
                                   {yyval = yyvsp[0];}
#line 1748 "parser.c"
    break;

  case 29:
#line 267 "parser.y"
                                              {yyval = yyvsp[-1];}
#line 1754 "parser.c"
    break;

  case 30:
#line 268 "parser.y"
                                {yyval = NULL;}
#line 1760 "parser.c"
    break;

  case 31:
#line 271 "parser.y"
                                                                                         {
                        yyval = novoNo();
                        strcpy(yyval->lexema, "IF");
                        yyval->tipo = DECLARACAO;
                        yyval->numLinha = qntLinhas;
                        yyval->tipoDeclaracao = IfK;

                        adicionaFilho(yyval, yyvsp[-3]);
                        adicionaFilho(yyval, yyvsp[-1]);		
                        if(yyvsp[0] != NULL){
                            adicionaFilho(yyval, yyvsp[0]);
                        }

                        nos[qntNos] = yyval;
                        qntNos++;
                    }
#line 1781 "parser.c"
    break;

  case 32:
#line 289 "parser.y"
                                                 {yyval = yyvsp[0];}
#line 1787 "parser.c"
    break;

  case 33:
#line 290 "parser.y"
                             {yyval = NULL;}
#line 1793 "parser.c"
    break;

  case 34:
#line 293 "parser.y"
                                                                                   {
                        yyval = novoNo();
                        strcpy(yyval->lexema, "WHILE");
                        yyval->tipo = DECLARACAO;
                        yyval->numLinha = qntLinhas;
                        yyval->tipoDeclaracao = WhileK;

                        adicionaFilho(yyval, yyvsp[-2]);
                        adicionaFilho(yyval, yyvsp[0]);

                        nos[qntNos] = yyval;
                        qntNos++;

                    }
#line 1812 "parser.c"
    break;

  case 35:
#line 309 "parser.y"
                                           { 
                        yyval = novoNo();
                        yyval->tipo = DECLARACAO;
                        yyval->numLinha = qntLinhas;
                        yyval->tipoDeclaracao = ReturnVOID;
                        strcpy(yyval->lexema, "ReturnVOID");

                        nos[qntNos] = yyval;
                        qntNos++;
                        
                    }
#line 1828 "parser.c"
    break;

  case 36:
#line 320 "parser.y"
                                                 {
                        yyval = novoNo();
                        yyval->tipo = DECLARACAO;
                        yyval->numLinha = qntLinhas;
                        yyval->tipoDeclaracao = ReturnINT;
                        strcpy(yyval->lexema, "ReturnINT");

                        adicionaFilho(yyval, yyvsp[-1]);

                        nos[qntNos] = yyval;
                        qntNos++;
                    }
#line 1845 "parser.c"
    break;

  case 37:
#line 334 "parser.y"
                                                      {
                        yyval = novoNo();
                        strcpy(yyval->lexema, "=");
                        yyval->tipo = EXPRESSAO;
                        yyval->numLinha = qntLinhas;
                        yyval->tipoExpressao = AssignK;

                        adicionaFilho(yyval, yyvsp[-2]);
                        adicionaFilho(yyval, yyvsp[0]);

                        nos[qntNos] = yyval;
                        qntNos++;

                    }
#line 1864 "parser.c"
    break;

  case 38:
#line 348 "parser.y"
                                        {yyval = yyvsp[0];}
#line 1870 "parser.c"
    break;

  case 39:
#line 351 "parser.y"
                                     {
                        yyval = novoNo();
                        yyval->tipo = EXPRESSAO;
                        yyval->numLinha = qntLinhas;
                        yyval->tipoExpressao = IdK;
                        

                        strcpy(yyval->lexema, pilha[indPilha]);
                        /*
                        FILE * arquivoAux = fopen("arquivoAux.txt", "a+");
                        fprintf(arquivoAux, "%s\n", $$->lexema);
                        fclose(arquivoAux);
                        */
                        indPilha--;
                        //strcpy($$->lexema, id);

                        nos[qntNos] = yyval;
                        qntNos++;

                    }
#line 1895 "parser.c"
    break;

  case 40:
#line 371 "parser.y"
                                                               {
                        yyval = novoNo();

                        yyval->tipo = EXPRESSAO;
                        yyval->numLinha = qntLinhas;
                        yyval->tipoExpressao = VetorK;
                        
                        //strcpy($$->lexema, id);
                        strcpy(yyval->lexema, pilha[indPilha]);
                        indPilha--;

                        adicionaFilho(yyval, yyvsp[-1]);

                        nos[qntNos] = yyval;
                        qntNos++;
                        
                    }
#line 1917 "parser.c"
    break;

  case 41:
#line 390 "parser.y"
                                                                   {
                        yyval = yyvsp[-1];
                        yyval->tipo = EXPRESSAO;
                        yyval->numLinha = qntLinhas;
                        yyval->tipoExpressao = OpRel;

                        adicionaFilho(yyval, yyvsp[-2]);
                        adicionaFilho(yyval, yyvsp[0]);	
                        
                    }
#line 1932 "parser.c"
    break;

  case 42:
#line 400 "parser.y"
                                     {yyval = yyvsp[0];}
#line 1938 "parser.c"
    break;

  case 43:
#line 403 "parser.y"
                                                      {
                        yyval = yyvsp[0];
                    }
#line 1946 "parser.c"
    break;

  case 44:
#line 408 "parser.y"
                             {
                        yyval = novoNo();
                        strcpy(yyval->lexema, "==");

                        nos[qntNos] = yyval;
                        qntNos++;
                        
                    }
#line 1959 "parser.c"
    break;

  case 45:
#line 417 "parser.y"
                          {
                        yyval = novoNo();
                        strcpy(yyval->lexema, "!=");

                        nos[qntNos] = yyval;
                        qntNos++;
                        
                    }
#line 1972 "parser.c"
    break;

  case 46:
#line 426 "parser.y"
                         {
                        yyval = novoNo();
                        strcpy(yyval->lexema, "<");

                        nos[qntNos] = yyval;
                        qntNos++;
                        
                    }
#line 1985 "parser.c"
    break;

  case 47:
#line 435 "parser.y"
                         {
                        yyval = novoNo();
                        strcpy(yyval->lexema, ">");

                        nos[qntNos] = yyval;
                        qntNos++;
                        
                    }
#line 1998 "parser.c"
    break;

  case 48:
#line 444 "parser.y"
                          {
                        yyval = novoNo();
                        strcpy(yyval->lexema, "<=");

                        nos[qntNos] = yyval;
                        qntNos++;
                        
                    }
#line 2011 "parser.c"
    break;

  case 49:
#line 453 "parser.y"
                          {
                        yyval = novoNo();
                        strcpy(yyval->lexema, ">=");

                        nos[qntNos] = yyval;
                        qntNos++;
                    }
#line 2023 "parser.c"
    break;

  case 50:
#line 463 "parser.y"
                                                    {
                        yyval = yyvsp[-1];
                        yyval->tipo = EXPRESSAO;
                        yyval->numLinha = qntLinhas;
                        yyval->tipoExpressao = OpK;

                        adicionaFilho(yyval, yyvsp[-2]);
                        adicionaFilho(yyval, yyvsp[0]);
                    }
#line 2037 "parser.c"
    break;

  case 51:
#line 472 "parser.y"
                            {yyval = yyvsp[0];}
#line 2043 "parser.c"
    break;

  case 52:
#line 475 "parser.y"
                                       {
                        yyval = novoNo();
                        strcpy(yyval->lexema, "+");

                        nos[qntNos] = yyval;
                        qntNos++;
                    }
#line 2055 "parser.c"
    break;

  case 53:
#line 482 "parser.y"
                          {
                        yyval = novoNo();
                        strcpy(yyval->lexema, "-");

                        nos[qntNos] = yyval;
                        qntNos++;
                    }
#line 2067 "parser.c"
    break;

  case 54:
#line 491 "parser.y"
                                                   {
                        yyval = yyvsp[-1];
                        yyval->tipo = EXPRESSAO;
                        yyval->numLinha = qntLinhas;
                        yyval->tipoExpressao = OpK;

                        adicionaFilho(yyval, yyvsp[-2]);
                        adicionaFilho(yyval, yyvsp[0]);
                        
                    }
#line 2082 "parser.c"
    break;

  case 55:
#line 501 "parser.y"
                            {yyval = yyvsp[0];}
#line 2088 "parser.c"
    break;

  case 56:
#line 504 "parser.y"
                                       {
                        yyval = novoNo();
                        strcpy(yyval->lexema, "*");

                        nos[qntNos] = yyval;
                        qntNos++;
                    }
#line 2100 "parser.c"
    break;

  case 57:
#line 511 "parser.y"
                          {
                        yyval = novoNo();
                        strcpy(yyval->lexema, "/");

                        nos[qntNos] = yyval;
                        qntNos++;
                    }
#line 2112 "parser.c"
    break;

  case 58:
#line 520 "parser.y"
                                                                            {yyval = yyvsp[-1];}
#line 2118 "parser.c"
    break;

  case 59:
#line 521 "parser.y"
                          {yyval = yyvsp[0];}
#line 2124 "parser.c"
    break;

  case 60:
#line 522 "parser.y"
                               {yyval = yyvsp[0];}
#line 2130 "parser.c"
    break;

  case 61:
#line 523 "parser.y"
                          { 
                        yyval = novoNo();
                        yyval->tipo = EXPRESSAO;
                        yyval->numLinha = qntLinhas;
                        yyval->tipoExpressao = ConstK;

                        strcpy(yyval->lexema, pilha[indPilha]);
                        indPilha--;

                        //strcpy($$->lexema, auxNome);

                        nos[qntNos] = yyval;
                        qntNos++;
                    }
#line 2149 "parser.c"
    break;

  case 62:
#line 539 "parser.y"
                                                                             {
                        yyval = yyvsp[-3];
                        yyval->tipo = EXPRESSAO;
                        yyval->numLinha = qntLinhas;
                        yyval->tipoExpressao = AtivK;
                        adicionaFilho(yyval, yyvsp[-1]);
                    }
#line 2161 "parser.c"
    break;

  case 63:
#line 548 "parser.y"
                                            {yyval = yyvsp[0];}
#line 2167 "parser.c"
    break;

  case 64:
#line 549 "parser.y"
                             {yyval = NULL;}
#line 2173 "parser.c"
    break;

  case 65:
#line 552 "parser.y"
                                                            {
                        if(yyvsp[-2] != NULL){
                            yyval = yyvsp[-2];
                            adicionaIrmao(yyval, yyvsp[0]);
                        } else yyval = yyvsp[0];
                    }
#line 2184 "parser.c"
    break;

  case 66:
#line 558 "parser.y"
                                {
                        yyval = yyvsp[0];
                    }
#line 2192 "parser.c"
    break;


#line 2196 "parser.c"

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
        yyerror (yymsgp);
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
                  yystos[yystate], yyvsp);
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
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
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
#line 564 "parser.y"


//Funcao para mostrar o erro sintatico do codigo
void yyerror (char *s){
    printf("\n" ANSI_COLOR_RED "ERRO SINTATICO, LINHA: %d", qntLinhas);
    printf(ANSI_COLOR_RESET);
    switch(auxErro){
        case NUM:
            printf(": '%s' não era esperado (NUM)", yytext);
            break; 
        case SOMA:
            printf(": '%s' não era esperado (SOMA)", yytext);
            break;
        case SUB:
            printf(": '%s' não era esperado (SUB)", yytext);
            break;
        case MULT:
            printf(": '%s' não era esperado (MULT)", yytext);
            break;
        case DIV:
            printf(": '%s' não era esperado (DIV)", yytext);
            break;
        case INT:
            printf(": '%s' não era esperado (INT)", yytext);
            break;
        case ID:
            printf(": '%s' não era esperado (ID)", yytext);
            break;
        case VOID:
            printf(": '%s' não era esperado (VOID)", yytext);
            break;
        case WHILE:
            printf(": '%s' não era esperado (WHILE)", yytext);
            break;
        case ELSE:
            printf(": '%s' não era esperado (ELSE)", yytext);
            break;
        case IF:
            printf(": '%s' não era esperado (IF)", yytext);
            break;
        case ABREPARENTESES:
            printf(": '%s' não era esperado (ABREPARENTESES)", yytext);
            break;
        case FECHAPARENTESES:
            printf(": '%s' não era esperado (FECHAPARENTESES)", yytext);
            break;
        case RETURN:
            printf(": '%s' não era esperado (RETURN)", yytext);
            break;
        case COMMA:
            printf(": '%s' não era esperado (COMA)", yytext);
            break;
        case ABRECHAVES:
            printf(": '%s' não era esperado (ABRECHAVES)", yytext);
            break;
        case FECHACHAVES:
            printf(": '%s' não era esperado (FECHACHAVES)", yytext);
            break;
        case SEMICOLON:
            printf(": '%s' não era esperado (SEMICOLON)", yytext);
            break;
        case ATRIB:
            printf(": '%s' não era esperado (ATRIB)", yytext);
            break;
        case ABRECOLCHETES:
            printf(": '%s' não era esperado (ABRECOLCHETES)", yytext);
            break;
        case FECHACOLCHETES:
            printf(": '%s' não era esperado (FECHACOLCHETES)", yytext);
            break;
        case EQ:
            printf(": '%s' não era esperado (EQ)", yytext);
            break;
        case NEQ:
            printf(": '%s' não era esperado (NEQ)", yytext);
            break;
        case LT:
            printf(": '%s' não era esperado (LT)", yytext);
            break;
        case LET:
            printf(": '%s' não era esperado (LET)", yytext);
            break;
        case GT:
            printf(": '%s' não era esperado (GT)", yytext);
            break;
        case GET:
            printf(": '%s' não era esperado (GET)", yytext);
            break;
        case ERRO:
            printf(": '%s' não era esperado (ERRO)", yytext);
            break;
    }
    printf("\n");


    
    //Desaloca os nos ate o momento
    for(int i = 0; i < qntNos; i++){
        free(nos[i]);
    } 
    arvoreSintatica = NULL;

}

int yylex(void)
{ return (auxErro = getToken()); }

PONTEIRONO parse(void)
{ 
    yyparse();
    return arvoreSintatica;
}

