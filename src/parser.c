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


#line 103 "parser.c"

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

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUM = 3,                        /* NUM  */
  YYSYMBOL_SOMA = 4,                       /* SOMA  */
  YYSYMBOL_SUB = 5,                        /* SUB  */
  YYSYMBOL_MULT = 6,                       /* MULT  */
  YYSYMBOL_DIV = 7,                        /* DIV  */
  YYSYMBOL_INT = 8,                        /* INT  */
  YYSYMBOL_ID = 9,                         /* ID  */
  YYSYMBOL_VOID = 10,                      /* VOID  */
  YYSYMBOL_WHILE = 11,                     /* WHILE  */
  YYSYMBOL_ELSE = 12,                      /* ELSE  */
  YYSYMBOL_IF = 13,                        /* IF  */
  YYSYMBOL_ABREPARENTESES = 14,            /* ABREPARENTESES  */
  YYSYMBOL_FECHAPARENTESES = 15,           /* FECHAPARENTESES  */
  YYSYMBOL_RETURN = 16,                    /* RETURN  */
  YYSYMBOL_COMMA = 17,                     /* COMMA  */
  YYSYMBOL_ABRECHAVES = 18,                /* ABRECHAVES  */
  YYSYMBOL_FECHACHAVES = 19,               /* FECHACHAVES  */
  YYSYMBOL_SEMICOLON = 20,                 /* SEMICOLON  */
  YYSYMBOL_ATRIB = 21,                     /* ATRIB  */
  YYSYMBOL_ABRECOLCHETES = 22,             /* ABRECOLCHETES  */
  YYSYMBOL_FECHACOLCHETES = 23,            /* FECHACOLCHETES  */
  YYSYMBOL_EQ = 24,                        /* EQ  */
  YYSYMBOL_NEQ = 25,                       /* NEQ  */
  YYSYMBOL_LT = 26,                        /* LT  */
  YYSYMBOL_LET = 27,                       /* LET  */
  YYSYMBOL_GT = 28,                        /* GT  */
  YYSYMBOL_GET = 29,                       /* GET  */
  YYSYMBOL_ERRO = 30,                      /* ERRO  */
  YYSYMBOL_YYACCEPT = 31,                  /* $accept  */
  YYSYMBOL_programa = 32,                  /* programa  */
  YYSYMBOL_declaracao_lista = 33,          /* declaracao_lista  */
  YYSYMBOL_declaracao = 34,                /* declaracao  */
  YYSYMBOL_var_declaracao = 35,            /* var_declaracao  */
  YYSYMBOL_tipo_especificador = 36,        /* tipo_especificador  */
  YYSYMBOL_fun_declaracao = 37,            /* fun_declaracao  */
  YYSYMBOL_fun_id = 38,                    /* fun_id  */
  YYSYMBOL_params = 39,                    /* params  */
  YYSYMBOL_param_lista = 40,               /* param_lista  */
  YYSYMBOL_param = 41,                     /* param  */
  YYSYMBOL_composto_decl = 42,             /* composto_decl  */
  YYSYMBOL_local_declaracoes = 43,         /* local_declaracoes  */
  YYSYMBOL_statement_lista = 44,           /* statement_lista  */
  YYSYMBOL_statement = 45,                 /* statement  */
  YYSYMBOL_expressao_decl = 46,            /* expressao_decl  */
  YYSYMBOL_selecao_decl = 47,              /* selecao_decl  */
  YYSYMBOL_fatoracao = 48,                 /* fatoracao  */
  YYSYMBOL_iteracao_decl = 49,             /* iteracao_decl  */
  YYSYMBOL_retorno_decl = 50,              /* retorno_decl  */
  YYSYMBOL_expressao = 51,                 /* expressao  */
  YYSYMBOL_var = 52,                       /* var  */
  YYSYMBOL_simples_expressao = 53,         /* simples_expressao  */
  YYSYMBOL_relacional = 54,                /* relacional  */
  YYSYMBOL_operador_relacional = 55,       /* operador_relacional  */
  YYSYMBOL_soma_expressao = 56,            /* soma_expressao  */
  YYSYMBOL_soma = 57,                      /* soma  */
  YYSYMBOL_termo = 58,                     /* termo  */
  YYSYMBOL_mult = 59,                      /* mult  */
  YYSYMBOL_fator = 60,                     /* fator  */
  YYSYMBOL_ativacao = 61,                  /* ativacao  */
  YYSYMBOL_args = 62,                      /* args  */
  YYSYMBOL_arg_lista = 63                  /* arg_lista  */
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

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   285


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
       0,    48,    48,    54,    63,    66,    67,    70,    88,   114,
     122,   133,   146,   160,   161,   173,   182,   185,   203,   222,
     233,   243,   246,   255,   258,   259,   260,   261,   262,   265,
     266,   269,   287,   288,   291,   307,   318,   332,   346,   349,
     369,   388,   398,   401,   406,   415,   424,   433,   442,   451,
     461,   470,   473,   480,   489,   499,   502,   509,   518,   519,
     520,   521,   537,   546,   547,   550,   556
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
  "\"end of file\"", "error", "\"invalid token\"", "NUM", "SOMA", "SUB",
  "MULT", "DIV", "INT", "ID", "VOID", "WHILE", "ELSE", "IF",
  "ABREPARENTESES", "FECHAPARENTESES", "RETURN", "COMMA", "ABRECHAVES",
  "FECHACHAVES", "SEMICOLON", "ATRIB", "ABRECOLCHETES", "FECHACOLCHETES",
  "EQ", "NEQ", "LT", "LET", "GT", "GET", "ERRO", "$accept", "programa",
  "declaracao_lista", "declaracao", "var_declaracao", "tipo_especificador",
  "fun_declaracao", "fun_id", "params", "param_lista", "param",
  "composto_decl", "local_declaracoes", "statement_lista", "statement",
  "expressao_decl", "selecao_decl", "fatoracao", "iteracao_decl",
  "retorno_decl", "expressao", "var", "simples_expressao", "relacional",
  "operador_relacional", "soma_expressao", "soma", "termo", "mult",
  "fator", "ativacao", "args", "arg_lista", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

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
       0,     3,     4,     5,     6,     7,     8,    45,    19,    20,
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

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
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

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
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

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
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
  case 2: /* programa: declaracao_lista  */
#line 48 "parser.y"
                                                   {
                        arvoreSintatica = yyvsp[0];
                    }
#line 1226 "parser.c"
    break;

  case 3: /* declaracao_lista: declaracao_lista declaracao  */
#line 54 "parser.y"
                                                      {  
                        if(yyvsp[-1] != NULL){
                            yyval = yyvsp[-1];
                            adicionaIrmao(yyval, yyvsp[0]);
                        }
                        else{
                            yyval = yyvsp[0];
                        }
                      }
#line 1240 "parser.c"
    break;

  case 4: /* declaracao_lista: declaracao  */
#line 63 "parser.y"
                                 {yyval = yyvsp[0];}
#line 1246 "parser.c"
    break;

  case 5: /* declaracao: var_declaracao  */
#line 66 "parser.y"
                                                 {yyval = yyvsp[0];}
#line 1252 "parser.c"
    break;

  case 6: /* declaracao: fun_declaracao  */
#line 67 "parser.y"
                                     {yyval = yyvsp[0];}
#line 1258 "parser.c"
    break;

  case 7: /* var_declaracao: tipo_especificador ID SEMICOLON  */
#line 70 "parser.y"
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
#line 1281 "parser.c"
    break;

  case 8: /* var_declaracao: tipo_especificador ID ABRECOLCHETES NUM FECHACOLCHETES SEMICOLON  */
#line 88 "parser.y"
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
#line 1310 "parser.c"
    break;

  case 9: /* tipo_especificador: INT  */
#line 114 "parser.y"
                              {
                        yyval = novoNo();
                        strcpy(yyval->lexema, "INT");
                        yyval->numLinha = qntLinhas;

                        nos[qntNos] = yyval;
                        qntNos++;
                    }
#line 1323 "parser.c"
    break;

  case 10: /* tipo_especificador: VOID  */
#line 122 "parser.y"
                           {
                        yyval = novoNo();
                        strcpy(yyval->lexema, "VOID");
                        yyval->numLinha = qntLinhas;

                        nos[qntNos] = yyval;
                        qntNos++;
                    }
#line 1336 "parser.c"
    break;

  case 11: /* fun_declaracao: tipo_especificador fun_id ABREPARENTESES params FECHAPARENTESES composto_decl  */
#line 133 "parser.y"
                                                                                                        { 
                        //strcpy(auxLexema, "")
                        yyval = yyvsp[-5];

                        adicionaFilho(yyval, yyvsp[-2]);
                        adicionaFilho(yyval, yyvsp[-4]);
                        adicionaFilho(yyvsp[-4], yyvsp[0]);
                        
                        yyval->tipo = DECLARACAO;
                        yyval->tipoDeclaracao = FunDeclK;
                    }
#line 1352 "parser.c"
    break;

  case 12: /* fun_id: ID  */
#line 146 "parser.y"
                                     {
                        yyval = novoNo();
                        
                        strcpy(yyval->lexema, pilha[indPilha]);
                        indPilha--;

                        //strcpy($$->lexema, auxNome);
                        yyval->numLinha = qntLinhas;

                        nos[qntNos] = yyval;
                        qntNos++;
                    }
#line 1369 "parser.c"
    break;

  case 13: /* params: param_lista  */
#line 160 "parser.y"
                                              {yyval = yyvsp[0];}
#line 1375 "parser.c"
    break;

  case 14: /* params: VOID  */
#line 161 "parser.y"
                           {
                        yyval = novoNo();
                        yyval->tipo = DECLARACAO;
                        yyval->numLinha = qntLinhas;
                        yyval->tipoDeclaracao = ParamVoid;
                        strcpy(yyval->lexema, "VOID");

                        nos[qntNos] = yyval;
                        qntNos++;
                    }
#line 1390 "parser.c"
    break;

  case 15: /* param_lista: param_lista COMMA param  */
#line 173 "parser.y"
                                                          {
                        if(yyvsp[-2] != NULL){
                            yyval = yyvsp[-2];
                            adicionaIrmao(yyval, yyvsp[0]);
                        }
                        else{
                            yyval = yyvsp[0];
                        }						
                    }
#line 1404 "parser.c"
    break;

  case 16: /* param_lista: param  */
#line 182 "parser.y"
                            {yyval = yyvsp[0];}
#line 1410 "parser.c"
    break;

  case 17: /* param: tipo_especificador ID  */
#line 185 "parser.y"
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
#line 1433 "parser.c"
    break;

  case 18: /* param: tipo_especificador ID ABRECOLCHETES FECHACOLCHETES  */
#line 203 "parser.y"
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
#line 1455 "parser.c"
    break;

  case 19: /* composto_decl: ABRECHAVES local_declaracoes statement_lista FECHACHAVES  */
#line 222 "parser.y"
                                                                                   { 
                        if(yyvsp[-2] != NULL){
                            yyval = yyvsp[-2];
                            adicionaIrmao(yyval, yyvsp[-1]);
                        }
                        else{
                            yyval = yyvsp[-1];
                        }
                    }
#line 1469 "parser.c"
    break;

  case 20: /* local_declaracoes: local_declaracoes var_declaracao  */
#line 233 "parser.y"
                                                           {
                        if(yyvsp[-1] != NULL){
                            yyval = yyvsp[-1];
                            adicionaIrmao(yyval, yyvsp[0]);
                        }
                        else{
                            yyval = yyvsp[0];
                        }

                    }
#line 1484 "parser.c"
    break;

  case 21: /* local_declaracoes: %empty  */
#line 243 "parser.y"
                             {yyval = NULL;}
#line 1490 "parser.c"
    break;

  case 22: /* statement_lista: statement_lista statement  */
#line 246 "parser.y"
                                                    {
                        if(yyvsp[-1] != NULL){
                            yyval = yyvsp[-1];
                            adicionaIrmao(yyval, yyvsp[0]);
                        }
                        else{
                            yyval = yyvsp[0];
                        }
                    }
#line 1504 "parser.c"
    break;

  case 23: /* statement_lista: %empty  */
#line 255 "parser.y"
                             {yyval = NULL;}
#line 1510 "parser.c"
    break;

  case 24: /* statement: expressao_decl  */
#line 258 "parser.y"
                                                 {yyval = yyvsp[0];}
#line 1516 "parser.c"
    break;

  case 25: /* statement: composto_decl  */
#line 259 "parser.y"
                                    {yyval = yyvsp[0];}
#line 1522 "parser.c"
    break;

  case 26: /* statement: selecao_decl  */
#line 260 "parser.y"
                                   {yyval = yyvsp[0];}
#line 1528 "parser.c"
    break;

  case 27: /* statement: iteracao_decl  */
#line 261 "parser.y"
                                    {yyval = yyvsp[0];}
#line 1534 "parser.c"
    break;

  case 28: /* statement: retorno_decl  */
#line 262 "parser.y"
                                   {yyval = yyvsp[0];}
#line 1540 "parser.c"
    break;

  case 29: /* expressao_decl: expressao SEMICOLON  */
#line 265 "parser.y"
                                              {yyval = yyvsp[-1];}
#line 1546 "parser.c"
    break;

  case 30: /* expressao_decl: SEMICOLON  */
#line 266 "parser.y"
                                {yyval = NULL;}
#line 1552 "parser.c"
    break;

  case 31: /* selecao_decl: IF ABREPARENTESES expressao FECHAPARENTESES statement fatoracao  */
#line 269 "parser.y"
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
#line 1573 "parser.c"
    break;

  case 32: /* fatoracao: ELSE statement  */
#line 287 "parser.y"
                                                 {yyval = yyvsp[0];}
#line 1579 "parser.c"
    break;

  case 33: /* fatoracao: %empty  */
#line 288 "parser.y"
                             {yyval = NULL;}
#line 1585 "parser.c"
    break;

  case 34: /* iteracao_decl: WHILE ABREPARENTESES expressao FECHAPARENTESES statement  */
#line 291 "parser.y"
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
#line 1604 "parser.c"
    break;

  case 35: /* retorno_decl: RETURN SEMICOLON  */
#line 307 "parser.y"
                                           { 
                        yyval = novoNo();
                        yyval->tipo = DECLARACAO;
                        yyval->numLinha = qntLinhas;
                        yyval->tipoDeclaracao = ReturnVOID;
                        strcpy(yyval->lexema, "ReturnVOID");

                        nos[qntNos] = yyval;
                        qntNos++;
                        
                    }
#line 1620 "parser.c"
    break;

  case 36: /* retorno_decl: RETURN expressao SEMICOLON  */
#line 318 "parser.y"
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
#line 1637 "parser.c"
    break;

  case 37: /* expressao: var ATRIB expressao  */
#line 332 "parser.y"
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
#line 1656 "parser.c"
    break;

  case 38: /* expressao: simples_expressao  */
#line 346 "parser.y"
                                        {yyval = yyvsp[0];}
#line 1662 "parser.c"
    break;

  case 39: /* var: ID  */
#line 349 "parser.y"
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
#line 1687 "parser.c"
    break;

  case 40: /* var: ID ABRECOLCHETES expressao FECHACOLCHETES  */
#line 369 "parser.y"
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
#line 1709 "parser.c"
    break;

  case 41: /* simples_expressao: soma_expressao relacional soma_expressao  */
#line 388 "parser.y"
                                                                   {
                        yyval = yyvsp[-1];
                        yyval->tipo = EXPRESSAO;
                        yyval->numLinha = qntLinhas;
                        yyval->tipoExpressao = OpRel;

                        adicionaFilho(yyval, yyvsp[-2]);
                        adicionaFilho(yyval, yyvsp[0]);	
                        
                    }
#line 1724 "parser.c"
    break;

  case 42: /* simples_expressao: soma_expressao  */
#line 398 "parser.y"
                                     {yyval = yyvsp[0];}
#line 1730 "parser.c"
    break;

  case 43: /* relacional: operador_relacional  */
#line 401 "parser.y"
                                                      {
                        yyval = yyvsp[0];
                    }
#line 1738 "parser.c"
    break;

  case 44: /* operador_relacional: EQ  */
#line 406 "parser.y"
                             {
                        yyval = novoNo();
                        strcpy(yyval->lexema, "==");

                        nos[qntNos] = yyval;
                        qntNos++;
                        
                    }
#line 1751 "parser.c"
    break;

  case 45: /* operador_relacional: NEQ  */
#line 415 "parser.y"
                          {
                        yyval = novoNo();
                        strcpy(yyval->lexema, "!=");

                        nos[qntNos] = yyval;
                        qntNos++;
                        
                    }
#line 1764 "parser.c"
    break;

  case 46: /* operador_relacional: LT  */
#line 424 "parser.y"
                         {
                        yyval = novoNo();
                        strcpy(yyval->lexema, "<");

                        nos[qntNos] = yyval;
                        qntNos++;
                        
                    }
#line 1777 "parser.c"
    break;

  case 47: /* operador_relacional: GT  */
#line 433 "parser.y"
                         {
                        yyval = novoNo();
                        strcpy(yyval->lexema, ">");

                        nos[qntNos] = yyval;
                        qntNos++;
                        
                    }
#line 1790 "parser.c"
    break;

  case 48: /* operador_relacional: LET  */
#line 442 "parser.y"
                          {
                        yyval = novoNo();
                        strcpy(yyval->lexema, "<=");

                        nos[qntNos] = yyval;
                        qntNos++;
                        
                    }
#line 1803 "parser.c"
    break;

  case 49: /* operador_relacional: GET  */
#line 451 "parser.y"
                          {
                        yyval = novoNo();
                        strcpy(yyval->lexema, ">=");

                        nos[qntNos] = yyval;
                        qntNos++;
                    }
#line 1815 "parser.c"
    break;

  case 50: /* soma_expressao: soma_expressao soma termo  */
#line 461 "parser.y"
                                                    {
                        yyval = yyvsp[-1];
                        yyval->tipo = EXPRESSAO;
                        yyval->numLinha = qntLinhas;
                        yyval->tipoExpressao = OpK;

                        adicionaFilho(yyval, yyvsp[-2]);
                        adicionaFilho(yyval, yyvsp[0]);
                    }
#line 1829 "parser.c"
    break;

  case 51: /* soma_expressao: termo  */
#line 470 "parser.y"
                            {yyval = yyvsp[0];}
#line 1835 "parser.c"
    break;

  case 52: /* soma: SOMA  */
#line 473 "parser.y"
                                       {
                        yyval = novoNo();
                        strcpy(yyval->lexema, "+");

                        nos[qntNos] = yyval;
                        qntNos++;
                    }
#line 1847 "parser.c"
    break;

  case 53: /* soma: SUB  */
#line 480 "parser.y"
                          {
                        yyval = novoNo();
                        strcpy(yyval->lexema, "-");

                        nos[qntNos] = yyval;
                        qntNos++;
                    }
#line 1859 "parser.c"
    break;

  case 54: /* termo: termo mult fator  */
#line 489 "parser.y"
                                                   {
                        yyval = yyvsp[-1];
                        yyval->tipo = EXPRESSAO;
                        yyval->numLinha = qntLinhas;
                        yyval->tipoExpressao = OpK;

                        adicionaFilho(yyval, yyvsp[-2]);
                        adicionaFilho(yyval, yyvsp[0]);
                        
                    }
#line 1874 "parser.c"
    break;

  case 55: /* termo: fator  */
#line 499 "parser.y"
                            {yyval = yyvsp[0];}
#line 1880 "parser.c"
    break;

  case 56: /* mult: MULT  */
#line 502 "parser.y"
                                       {
                        yyval = novoNo();
                        strcpy(yyval->lexema, "*");

                        nos[qntNos] = yyval;
                        qntNos++;
                    }
#line 1892 "parser.c"
    break;

  case 57: /* mult: DIV  */
#line 509 "parser.y"
                          {
                        yyval = novoNo();
                        strcpy(yyval->lexema, "/");

                        nos[qntNos] = yyval;
                        qntNos++;
                    }
#line 1904 "parser.c"
    break;

  case 58: /* fator: ABREPARENTESES expressao FECHAPARENTESES  */
#line 518 "parser.y"
                                                                            {yyval = yyvsp[-1];}
#line 1910 "parser.c"
    break;

  case 59: /* fator: var  */
#line 519 "parser.y"
                          {yyval = yyvsp[0];}
#line 1916 "parser.c"
    break;

  case 60: /* fator: ativacao  */
#line 520 "parser.y"
                               {yyval = yyvsp[0];}
#line 1922 "parser.c"
    break;

  case 61: /* fator: NUM  */
#line 521 "parser.y"
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
#line 1941 "parser.c"
    break;

  case 62: /* ativacao: fun_id ABREPARENTESES args FECHAPARENTESES  */
#line 537 "parser.y"
                                                                             {
                        yyval = yyvsp[-3];
                        yyval->tipo = EXPRESSAO;
                        yyval->numLinha = qntLinhas;
                        yyval->tipoExpressao = AtivK;
                        adicionaFilho(yyval, yyvsp[-1]);
                    }
#line 1953 "parser.c"
    break;

  case 63: /* args: arg_lista  */
#line 546 "parser.y"
                                            {yyval = yyvsp[0];}
#line 1959 "parser.c"
    break;

  case 64: /* args: %empty  */
#line 547 "parser.y"
                             {yyval = NULL;}
#line 1965 "parser.c"
    break;

  case 65: /* arg_lista: arg_lista COMMA expressao  */
#line 550 "parser.y"
                                                            {
                        if(yyvsp[-2] != NULL){
                            yyval = yyvsp[-2];
                            adicionaIrmao(yyval, yyvsp[0]);
                        } else yyval = yyvsp[0];
                    }
#line 1976 "parser.c"
    break;

  case 66: /* arg_lista: expressao  */
#line 556 "parser.y"
                                {
                        yyval = yyvsp[0];
                    }
#line 1984 "parser.c"
    break;


#line 1988 "parser.c"

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

#line 562 "parser.y"


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

