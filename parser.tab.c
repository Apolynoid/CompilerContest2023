/* A Bison parser, made by GNU Bison 3.7.5.  */

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
#define YYBISON 30705

/* Bison version string.  */
#define YYBISON_VERSION "3.7.5"

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
    #include <stdlib.h>
    #include <string.h>
    #include <errno.h>

    #include "AllNodes.h"

    Node* root;

    extern FILE *yyin;
    extern int line_cnt;
    extern int yylineno;
    extern char *yytext;
    extern int yylex();
    extern int yyparse();
    //extern void yyerror(char *msg);
    void yyerror(const char* fmt, ...);
    int syntax_error = 0;
    char filename[100];

#line 93 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CONST = 3,                      /* CONST  */
  YYSYMBOL_COMMA = 4,                      /* COMMA  */
  YYSYMBOL_LC = 5,                         /* LC  */
  YYSYMBOL_RC = 6,                         /* RC  */
  YYSYMBOL_LB = 7,                         /* LB  */
  YYSYMBOL_RB = 8,                         /* RB  */
  YYSYMBOL_AND = 9,                        /* AND  */
  YYSYMBOL_MINUS = 10,                     /* MINUS  */
  YYSYMBOL_MUL = 11,                       /* MUL  */
  YYSYMBOL_DIV = 12,                       /* DIV  */
  YYSYMBOL_MOD = 13,                       /* MOD  */
  YYSYMBOL_LP = 14,                        /* LP  */
  YYSYMBOL_RP = 15,                        /* RP  */
  YYSYMBOL_NOT = 16,                       /* NOT  */
  YYSYMBOL_SEMICOLON = 17,                 /* SEMICOLON  */
  YYSYMBOL_INT = 18,                       /* INT  */
  YYSYMBOL_FLOAT = 19,                     /* FLOAT  */
  YYSYMBOL_VOID = 20,                      /* VOID  */
  YYSYMBOL_RETURN = 21,                    /* RETURN  */
  YYSYMBOL_IF = 22,                        /* IF  */
  YYSYMBOL_ELSE = 23,                      /* ELSE  */
  YYSYMBOL_WHILE = 24,                     /* WHILE  */
  YYSYMBOL_BREAK = 25,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 26,                  /* CONTINUE  */
  YYSYMBOL_ASSIGN = 27,                    /* ASSIGN  */
  YYSYMBOL_ADD = 28,                       /* ADD  */
  YYSYMBOL_OR = 29,                        /* OR  */
  YYSYMBOL_EQ = 30,                        /* EQ  */
  YYSYMBOL_NE = 31,                        /* NE  */
  YYSYMBOL_LT = 32,                        /* LT  */
  YYSYMBOL_LE = 33,                        /* LE  */
  YYSYMBOL_GT = 34,                        /* GT  */
  YYSYMBOL_GE = 35,                        /* GE  */
  YYSYMBOL_LEX_ERR = 36,                   /* LEX_ERR  */
  YYSYMBOL_FOR = 37,                       /* FOR  */
  YYSYMBOL_INC = 38,                       /* INC  */
  YYSYMBOL_DEC = 39,                       /* DEC  */
  YYSYMBOL_THEN = 40,                      /* THEN  */
  YYSYMBOL_ID = 41,                        /* ID  */
  YYSYMBOL_INT_LIT = 42,                   /* INT_LIT  */
  YYSYMBOL_FLOAT_LIT = 43,                 /* FLOAT_LIT  */
  YYSYMBOL_YYACCEPT = 44,                  /* $accept  */
  YYSYMBOL_Root = 45,                      /* Root  */
  YYSYMBOL_CompUnit = 46,                  /* CompUnit  */
  YYSYMBOL_Decl = 47,                      /* Decl  */
  YYSYMBOL_ConstDecl = 48,                 /* ConstDecl  */
  YYSYMBOL_ConstDefs = 49,                 /* ConstDefs  */
  YYSYMBOL_ConstDef = 50,                  /* ConstDef  */
  YYSYMBOL_ConstInitVal = 51,              /* ConstInitVal  */
  YYSYMBOL_ConstInitVals = 52,             /* ConstInitVals  */
  YYSYMBOL_ConstArrayList = 53,            /* ConstArrayList  */
  YYSYMBOL_ConstExp = 54,                  /* ConstExp  */
  YYSYMBOL_AddExp = 55,                    /* AddExp  */
  YYSYMBOL_MulExp = 56,                    /* MulExp  */
  YYSYMBOL_UnaryExp = 57,                  /* UnaryExp  */
  YYSYMBOL_PrimaryExp = 58,                /* PrimaryExp  */
  YYSYMBOL_FuncRParams = 59,               /* FuncRParams  */
  YYSYMBOL_Exp = 60,                       /* Exp  */
  YYSYMBOL_LVal = 61,                      /* LVal  */
  YYSYMBOL_ArrayList = 62,                 /* ArrayList  */
  YYSYMBOL_VarDecl = 63,                   /* VarDecl  */
  YYSYMBOL_VarDefs = 64,                   /* VarDefs  */
  YYSYMBOL_VarDef = 65,                    /* VarDef  */
  YYSYMBOL_InitVal = 66,                   /* InitVal  */
  YYSYMBOL_InitVals = 67,                  /* InitVals  */
  YYSYMBOL_FuncDef = 68,                   /* FuncDef  */
  YYSYMBOL_FuncFParams = 69,               /* FuncFParams  */
  YYSYMBOL_FuncFParam = 70,                /* FuncFParam  */
  YYSYMBOL_Block = 71,                     /* Block  */
  YYSYMBOL_BlockItems = 72,                /* BlockItems  */
  YYSYMBOL_BlockItem = 73,                 /* BlockItem  */
  YYSYMBOL_Stmt = 74,                      /* Stmt  */
  YYSYMBOL_Cond = 75,                      /* Cond  */
  YYSYMBOL_LOrExp = 76,                    /* LOrExp  */
  YYSYMBOL_LAndExp = 77,                   /* LAndExp  */
  YYSYMBOL_EqExp = 78,                     /* EqExp  */
  YYSYMBOL_RelExp = 79                     /* RelExp  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  19
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   278

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  103
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  195

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   298


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    48,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149
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
  "\"end of file\"", "error", "\"invalid token\"", "CONST", "COMMA", "LC",
  "RC", "LB", "RB", "AND", "MINUS", "MUL", "DIV", "MOD", "LP", "RP", "NOT",
  "SEMICOLON", "INT", "FLOAT", "VOID", "RETURN", "IF", "ELSE", "WHILE",
  "BREAK", "CONTINUE", "ASSIGN", "ADD", "OR", "EQ", "NE", "LT", "LE", "GT",
  "GE", "LEX_ERR", "FOR", "INC", "DEC", "THEN", "ID", "INT_LIT",
  "FLOAT_LIT", "$accept", "Root", "CompUnit", "Decl", "ConstDecl",
  "ConstDefs", "ConstDef", "ConstInitVal", "ConstInitVals",
  "ConstArrayList", "ConstExp", "AddExp", "MulExp", "UnaryExp",
  "PrimaryExp", "FuncRParams", "Exp", "LVal", "ArrayList", "VarDecl",
  "VarDefs", "VarDef", "InitVal", "InitVals", "FuncDef", "FuncFParams",
  "FuncFParam", "Block", "BlockItems", "BlockItem", "Stmt", "Cond",
  "LOrExp", "LAndExp", "EqExp", "RelExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298
};
#endif

#define YYPACT_NINF (-162)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      76,    52,   -22,   -12,    -3,    56,  -162,    76,  -162,  -162,
      76,    17,    17,     9,    49,    68,    14,    57,    72,  -162,
    -162,  -162,    18,    65,    95,    80,   235,    73,   195,    63,
    -162,    83,    88,  -162,    93,   211,   102,  -162,    17,  -162,
     235,   235,   235,   235,    20,  -162,  -162,   105,    16,   125,
    -162,  -162,  -162,   126,    89,    92,   130,   137,   176,    16,
    -162,  -162,   195,    26,  -162,   126,   141,   126,   148,   192,
    -162,  -162,   211,  -162,  -162,   149,  -162,  -162,   235,   214,
    -162,   158,   235,   235,   235,   235,   235,   152,  -162,   160,
     165,   126,    86,  -162,   171,   173,  -162,  -162,   126,  -162,
     126,  -162,   179,   178,  -162,  -162,   177,  -162,   172,   184,
    -162,   125,   125,  -162,  -162,  -162,  -162,  -162,    83,    83,
     230,   175,   182,   174,   186,  -162,   190,   183,  -162,   193,
      59,  -162,   218,   223,  -162,  -162,   195,  -162,  -162,  -162,
     211,  -162,   194,  -162,   235,  -162,   205,   235,   235,  -162,
    -162,  -162,   235,  -162,  -162,   194,   194,  -162,  -162,  -162,
    -162,  -162,    16,   217,   212,   234,    85,   180,   233,   242,
    -162,  -162,   118,   235,   235,   235,   235,   235,   235,   235,
     235,   118,  -162,   227,   234,    85,   180,   180,    16,    16,
      16,    16,  -162,   118,  -162
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     2,     3,     7,     8,
       4,     0,     0,    51,     0,    49,    51,     0,     0,     1,
       5,     6,     0,     0,    11,     0,     0,     0,     0,    52,
      47,     0,     0,    48,     0,     0,     0,     9,     0,    10,
       0,     0,     0,     0,    43,    38,    39,     0,    22,    23,
      26,    30,    37,     0,     0,     0,     0,    66,     0,    42,
      55,    53,     0,    51,    50,     0,     0,     0,     0,     0,
      13,    15,     0,    12,    34,     0,    35,    33,     0,     0,
      44,    20,     0,     0,     0,     0,     0,     0,    61,    68,
      69,     0,     0,    56,    58,     0,    54,    62,     0,    60,
       0,    16,    18,     0,    14,    36,     0,    31,     0,    40,
      21,    25,    24,    27,    28,    29,    74,    81,     0,     0,
       0,     0,     0,     0,     0,    78,     0,    37,    83,     0,
      76,    79,     0,     0,    64,    67,     0,    57,    65,    63,
       0,    17,    45,    32,     0,    89,     0,     0,     0,    87,
      88,    82,     0,    75,    77,    70,    71,    59,    19,    46,
      41,    90,    99,     0,    91,    92,    94,    96,     0,     0,
      72,    73,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    80,    84,    93,    95,    97,    98,   102,   103,
     100,   101,    86,     0,    85
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -162,  -162,    30,   -80,  -162,     1,  -162,   -23,   120,   -16,
     236,   -26,    37,   -25,  -162,   117,   -27,   -83,   -88,  -162,
      -1,  -162,   -20,   128,  -162,   -29,  -162,   -43,   135,  -162,
    -161,   119,  -162,    96,    94,   -49
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,     7,     8,    23,    24,   102,   103,    29,
      71,    59,    49,    50,    51,   108,   126,    52,    80,     9,
      14,    15,    94,    95,    10,    56,    57,   128,   129,   130,
     131,   163,   164,   165,   166,   167
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      48,    60,    17,    66,   127,    68,    36,   125,    61,    48,
      88,   183,    70,    25,    75,    74,    26,    76,    77,    13,
     192,    26,    97,    27,    99,    26,    82,    78,    32,    16,
      64,    60,   194,    26,    79,    60,    28,    20,    18,    73,
      21,    28,    96,    48,    83,    35,    48,   127,   134,   104,
     125,   106,   109,    28,   159,   138,    19,   139,    22,   113,
     114,   115,     1,   135,    87,   110,    30,   170,   171,    40,
      11,    12,    31,    41,    33,    42,   117,   118,   119,     1,
     120,   121,    37,   122,   123,   124,    34,    43,    53,   127,
      62,    54,    55,   146,     2,     3,     4,    39,   127,    38,
      44,    45,    46,    65,    54,    55,    54,    55,    67,    60,
     127,    54,    55,    81,    48,   175,   176,   109,    17,   111,
     112,   162,   162,    87,    63,   169,   186,   187,    40,    72,
      89,    87,    41,    90,    42,   117,    84,    85,    86,   120,
     121,    92,   122,   123,   124,    91,    43,   162,   162,   162,
     162,   188,   189,   190,   191,     1,    98,    87,   116,    44,
      45,    46,    40,   100,   105,    26,    41,   132,    42,   117,
     118,   119,   133,   120,   121,   136,   122,   123,   124,   137,
      43,    58,    93,   140,   141,   142,    40,   143,   144,   147,
      41,   149,    42,    44,    45,    46,   148,    69,   101,   153,
      58,    78,    40,   150,    43,    40,    41,   151,    42,    41,
     152,    42,   177,   178,   179,   180,    69,    44,    45,    46,
      43,    40,   161,    43,    40,    41,   155,    42,    41,   107,
      42,   156,   172,    44,    45,    46,    44,    45,    46,    43,
      40,   173,    43,   174,    41,    40,    42,   145,   181,    41,
     193,    42,    44,    45,    46,    44,    45,    46,    43,   182,
     158,   160,    47,    43,   157,   154,     0,   168,   185,   184,
       0,    44,    45,    46,     0,     0,    44,    45,    46
};

static const yytype_int16 yycheck[] =
{
      26,    28,     3,    32,    87,    34,    22,    87,    28,    35,
      53,   172,    35,    12,    41,    40,     7,    42,    43,    41,
     181,     7,    65,    14,    67,     7,    10,     7,    14,    41,
      31,    58,   193,     7,    14,    62,    27,     7,    41,    38,
      10,    27,    62,    69,    28,    27,    72,   130,    91,    72,
     130,    78,    79,    27,   142,    98,     0,   100,    41,    84,
      85,    86,     3,    92,     5,    81,    17,   155,   156,    10,
      18,    19,     4,    14,    17,    16,    17,    18,    19,     3,
      21,    22,    17,    24,    25,    26,    14,    28,    15,   172,
      27,    18,    19,   120,    18,    19,    20,    17,   181,     4,
      41,    42,    43,    15,    18,    19,    18,    19,    15,   136,
     193,    18,    19,     8,   140,    30,    31,   144,   119,    82,
      83,   147,   148,     5,    41,   152,   175,   176,    10,    27,
      41,     5,    14,    41,    16,    17,    11,    12,    13,    21,
      22,     4,    24,    25,    26,    15,    28,   173,   174,   175,
     176,   177,   178,   179,   180,     3,    15,     5,     6,    41,
      42,    43,    10,    15,    15,     7,    14,     7,    16,    17,
      18,    19,     7,    21,    22,     4,    24,    25,    26,     6,
      28,     5,     6,     4,     6,     8,    10,    15,     4,    14,
      14,    17,    16,    41,    42,    43,    14,     5,     6,     6,
       5,     7,    10,    17,    28,    10,    14,    17,    16,    14,
      27,    16,    32,    33,    34,    35,     5,    41,    42,    43,
      28,    10,    17,    28,    10,    14,     8,    16,    14,    15,
      16,     8,    15,    41,    42,    43,    41,    42,    43,    28,
      10,    29,    28,     9,    14,    10,    16,    17,    15,    14,
      23,    16,    41,    42,    43,    41,    42,    43,    28,    17,
     140,   144,    26,    28,   136,   130,    -1,   148,   174,   173,
      -1,    41,    42,    43,    -1,    -1,    41,    42,    43
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    18,    19,    20,    45,    46,    47,    48,    63,
      68,    18,    19,    41,    64,    65,    41,    64,    41,     0,
      46,    46,    41,    49,    50,    49,     7,    14,    27,    53,
      17,     4,    14,    17,    14,    27,    53,    17,     4,    17,
      10,    14,    16,    28,    41,    42,    43,    54,    55,    56,
      57,    58,    61,    15,    18,    19,    69,    70,     5,    55,
      60,    66,    27,    41,    64,    15,    69,    15,    69,     5,
      51,    54,    27,    49,    57,    60,    57,    57,     7,    14,
      62,     8,    10,    28,    11,    12,    13,     5,    71,    41,
      41,    15,     4,     6,    66,    67,    66,    71,    15,    71,
      15,     6,    51,    52,    51,    15,    60,    15,    59,    60,
      53,    56,    56,    57,    57,    57,     6,    17,    18,    19,
      21,    22,    24,    25,    26,    47,    60,    61,    71,    72,
      73,    74,     7,     7,    71,    69,     4,     6,    71,    71,
       4,     6,     8,    15,     4,    17,    60,    14,    14,    17,
      17,    17,    27,     6,    72,     8,     8,    67,    52,    62,
      59,    17,    55,    75,    76,    77,    78,    79,    75,    60,
      62,    62,    15,    29,     9,    30,    31,    32,    33,    34,
      35,    15,    17,    74,    77,    78,    79,    79,    55,    55,
      55,    55,    74,    23,    74
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    44,    45,    46,    46,    46,    46,    47,    47,    48,
      48,    49,    49,    50,    50,    51,    51,    51,    52,    52,
      53,    53,    54,    55,    55,    55,    56,    56,    56,    56,
      57,    57,    57,    57,    57,    57,    58,    58,    58,    58,
      59,    59,    60,    61,    61,    62,    62,    63,    63,    64,
      64,    65,    65,    65,    65,    66,    66,    66,    67,    67,
      68,    68,    68,    68,    68,    68,    69,    69,    70,    70,
      70,    70,    70,    70,    71,    71,    72,    72,    73,    73,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    75,    76,    76,    77,    77,    78,    78,    78,    79,
      79,    79,    79,    79
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     2,     1,     1,     4,
       4,     1,     3,     3,     4,     1,     2,     3,     1,     3,
       3,     4,     1,     1,     3,     3,     1,     3,     3,     3,
       1,     3,     4,     2,     2,     2,     3,     1,     1,     1,
       1,     3,     1,     1,     2,     3,     4,     3,     3,     1,
       3,     1,     2,     3,     4,     1,     2,     3,     1,     3,
       5,     5,     5,     6,     6,     6,     1,     3,     2,     2,
       4,     4,     5,     5,     2,     3,     1,     2,     1,     1,
       4,     1,     2,     1,     5,     7,     5,     2,     2,     2,
       3,     1,     1,     3,     1,     3,     1,     3,     3,     1,
       3,     3,     3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


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
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
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
  case 2: /* Root: CompUnit  */
#line 48 "parser.y"
               {root = new RootNode((yyvsp[0].node_val));}
#line 1317 "parser.tab.c"
    break;

  case 3: /* CompUnit: Decl  */
#line 49 "parser.y"
               {(yyval.node_val) = new CompUnitNode((yyvsp[0].node_val), nullptr, nullptr);}
#line 1323 "parser.tab.c"
    break;

  case 4: /* CompUnit: FuncDef  */
#line 50 "parser.y"
                  {(yyval.node_val) = new CompUnitNode(nullptr, (yyvsp[0].node_val), nullptr);}
#line 1329 "parser.tab.c"
    break;

  case 5: /* CompUnit: Decl CompUnit  */
#line 51 "parser.y"
                        {(yyval.node_val) = new CompUnitNode((yyvsp[-1].node_val), nullptr, (yyvsp[0].node_val));}
#line 1335 "parser.tab.c"
    break;

  case 6: /* CompUnit: FuncDef CompUnit  */
#line 52 "parser.y"
                           {(yyval.node_val) = new CompUnitNode(nullptr, (yyvsp[-1].node_val), (yyvsp[0].node_val));}
#line 1341 "parser.tab.c"
    break;

  case 7: /* Decl: ConstDecl  */
#line 53 "parser.y"
                {(yyval.node_val) = new DeclNode((yyvsp[0].node_val), nullptr);}
#line 1347 "parser.tab.c"
    break;

  case 8: /* Decl: VarDecl  */
#line 54 "parser.y"
              {(yyval.node_val) = new DeclNode(nullptr, (yyvsp[0].node_val));}
#line 1353 "parser.tab.c"
    break;

  case 9: /* ConstDecl: CONST INT ConstDefs SEMICOLON  */
#line 55 "parser.y"
                                            {(yyval.node_val) = new ConstDeclNode((yyvsp[-1].node_val), INTTYPE);}
#line 1359 "parser.tab.c"
    break;

  case 10: /* ConstDecl: CONST FLOAT ConstDefs SEMICOLON  */
#line 56 "parser.y"
                                              {(yyval.node_val) = new ConstDeclNode((yyvsp[-1].node_val), FLOATTYPE);}
#line 1365 "parser.tab.c"
    break;

  case 11: /* ConstDefs: ConstDef  */
#line 57 "parser.y"
                       {(yyval.node_val) = new ConstDefsNode((yyvsp[0].node_val), nullptr);}
#line 1371 "parser.tab.c"
    break;

  case 12: /* ConstDefs: ConstDef COMMA ConstDefs  */
#line 58 "parser.y"
                                       {(yyval.node_val) = new ConstDefsNode((yyvsp[-2].node_val), (yyvsp[0].node_val));}
#line 1377 "parser.tab.c"
    break;

  case 13: /* ConstDef: ID ASSIGN ConstInitVal  */
#line 59 "parser.y"
                                 {(yyval.node_val) = new ConstDefNode((yyvsp[-2].str_val), nullptr, (yyvsp[0].node_val));}
#line 1383 "parser.tab.c"
    break;

  case 14: /* ConstDef: ID ConstArrayList ASSIGN ConstInitVal  */
#line 60 "parser.y"
                                                {(yyval.node_val) = new ConstDefNode((yyvsp[-3].str_val), (yyvsp[-2].node_val), (yyvsp[0].node_val));}
#line 1389 "parser.tab.c"
    break;

  case 15: /* ConstInitVal: ConstExp  */
#line 61 "parser.y"
                       {(yyval.node_val) = new ConstInitValNode((yyvsp[0].node_val), nullptr);}
#line 1395 "parser.tab.c"
    break;

  case 16: /* ConstInitVal: LC RC  */
#line 62 "parser.y"
                    {(yyval.node_val) = new ConstInitValNode(nullptr, nullptr);}
#line 1401 "parser.tab.c"
    break;

  case 17: /* ConstInitVal: LC ConstInitVals RC  */
#line 63 "parser.y"
                                  {(yyval.node_val) = new ConstInitValNode(nullptr, (yyvsp[-1].node_val));}
#line 1407 "parser.tab.c"
    break;

  case 18: /* ConstInitVals: ConstInitVal  */
#line 64 "parser.y"
                               {(yyval.node_val) = new ConstInitValsNode((yyvsp[0].node_val), nullptr);}
#line 1413 "parser.tab.c"
    break;

  case 19: /* ConstInitVals: ConstInitVal COMMA ConstInitVals  */
#line 65 "parser.y"
                                                   {(yyval.node_val) = new ConstInitValsNode((yyvsp[-2].node_val), (yyvsp[0].node_val));}
#line 1419 "parser.tab.c"
    break;

  case 20: /* ConstArrayList: LB ConstExp RB  */
#line 66 "parser.y"
                                 {(yyval.node_val) = new ConstArrayListNode((yyvsp[-1].node_val), nullptr);}
#line 1425 "parser.tab.c"
    break;

  case 21: /* ConstArrayList: LB ConstExp RB ConstArrayList  */
#line 67 "parser.y"
                                                {(yyval.node_val) = new ConstArrayListNode((yyvsp[-2].node_val), (yyvsp[0].node_val));}
#line 1431 "parser.tab.c"
    break;

  case 22: /* ConstExp: AddExp  */
#line 68 "parser.y"
                 {(yyval.node_val) = new ConstExpNode((yyvsp[0].node_val));}
#line 1437 "parser.tab.c"
    break;

  case 23: /* AddExp: MulExp  */
#line 69 "parser.y"
                 {(yyval.node_val) = new AddExpNode(nullptr, NULLOP, (yyvsp[0].node_val));}
#line 1443 "parser.tab.c"
    break;

  case 24: /* AddExp: AddExp ADD MulExp  */
#line 70 "parser.y"
                            {(yyval.node_val) = new AddExpNode((yyvsp[-2].node_val), ADDOP, (yyvsp[0].node_val));}
#line 1449 "parser.tab.c"
    break;

  case 25: /* AddExp: AddExp MINUS MulExp  */
#line 71 "parser.y"
                              {(yyval.node_val) = new AddExpNode((yyvsp[-2].node_val), MINUSOP, (yyvsp[0].node_val));}
#line 1455 "parser.tab.c"
    break;

  case 26: /* MulExp: UnaryExp  */
#line 72 "parser.y"
                   {(yyval.node_val) = new MulExpNode(nullptr, NULLOP, (yyvsp[0].node_val));}
#line 1461 "parser.tab.c"
    break;

  case 27: /* MulExp: MulExp MUL UnaryExp  */
#line 73 "parser.y"
                              {(yyval.node_val) = new MulExpNode((yyvsp[-2].node_val), MULOP, (yyvsp[0].node_val));}
#line 1467 "parser.tab.c"
    break;

  case 28: /* MulExp: MulExp DIV UnaryExp  */
#line 74 "parser.y"
                              {(yyval.node_val) = new MulExpNode((yyvsp[-2].node_val), DIVOP, (yyvsp[0].node_val));}
#line 1473 "parser.tab.c"
    break;

  case 29: /* MulExp: MulExp MOD UnaryExp  */
#line 75 "parser.y"
                              {(yyval.node_val) = new MulExpNode((yyvsp[-2].node_val), MODOP, (yyvsp[0].node_val));}
#line 1479 "parser.tab.c"
    break;

  case 30: /* UnaryExp: PrimaryExp  */
#line 76 "parser.y"
                     {(yyval.node_val) = new UnaryExpNode((yyvsp[0].node_val), "", nullptr, NULLOP, nullptr);}
#line 1485 "parser.tab.c"
    break;

  case 31: /* UnaryExp: ID LP RP  */
#line 77 "parser.y"
                   {(yyval.node_val) = new UnaryExpNode(nullptr, (yyvsp[-2].str_val), nullptr, NULLOP, nullptr);}
#line 1491 "parser.tab.c"
    break;

  case 32: /* UnaryExp: ID LP FuncRParams RP  */
#line 78 "parser.y"
                               {(yyval.node_val) = new UnaryExpNode(nullptr, (yyvsp[-3].str_val), (yyvsp[-1].node_val), NULLOP, nullptr);}
#line 1497 "parser.tab.c"
    break;

  case 33: /* UnaryExp: ADD UnaryExp  */
#line 79 "parser.y"
                       {(yyval.node_val) = new UnaryExpNode(nullptr, "", nullptr, ADDOP, (yyvsp[0].node_val));}
#line 1503 "parser.tab.c"
    break;

  case 34: /* UnaryExp: MINUS UnaryExp  */
#line 80 "parser.y"
                         {(yyval.node_val) = new UnaryExpNode(nullptr, "", nullptr, MINUSOP, (yyvsp[0].node_val));}
#line 1509 "parser.tab.c"
    break;

  case 35: /* UnaryExp: NOT UnaryExp  */
#line 81 "parser.y"
                       {(yyval.node_val) = new UnaryExpNode(nullptr, "", nullptr, NOTOP, (yyvsp[0].node_val));}
#line 1515 "parser.tab.c"
    break;

  case 36: /* PrimaryExp: LP Exp RP  */
#line 82 "parser.y"
                        {(yyval.node_val) = new PrimaryExpNode((yyvsp[-1].node_val), nullptr, 0, 0.0, VOIDTYPE);}
#line 1521 "parser.tab.c"
    break;

  case 37: /* PrimaryExp: LVal  */
#line 83 "parser.y"
                   {(yyval.node_val) = new PrimaryExpNode(nullptr, (yyvsp[0].node_val), 0, 0.0, VOIDTYPE);}
#line 1527 "parser.tab.c"
    break;

  case 38: /* PrimaryExp: INT_LIT  */
#line 84 "parser.y"
                      {(yyval.node_val) = new PrimaryExpNode(nullptr, nullptr, (yyvsp[0].int_val), 0.0, INTTYPE);}
#line 1533 "parser.tab.c"
    break;

  case 39: /* PrimaryExp: FLOAT_LIT  */
#line 85 "parser.y"
                        {(yyval.node_val) = new PrimaryExpNode(nullptr, nullptr, 0, (yyvsp[0].float_val), FLOATTYPE);}
#line 1539 "parser.tab.c"
    break;

  case 40: /* FuncRParams: Exp  */
#line 86 "parser.y"
                  {(yyval.node_val) = new FuncRParamsNode((yyvsp[0].node_val), nullptr);}
#line 1545 "parser.tab.c"
    break;

  case 41: /* FuncRParams: Exp COMMA FuncRParams  */
#line 87 "parser.y"
                                    {(yyval.node_val) = new FuncRParamsNode((yyvsp[-2].node_val), (yyvsp[0].node_val));}
#line 1551 "parser.tab.c"
    break;

  case 42: /* Exp: AddExp  */
#line 88 "parser.y"
             {(yyval.node_val) = new ExpNode((yyvsp[0].node_val));}
#line 1557 "parser.tab.c"
    break;

  case 43: /* LVal: ID  */
#line 89 "parser.y"
         {(yyval.node_val) = new LValNode((yyvsp[0].str_val), nullptr);}
#line 1563 "parser.tab.c"
    break;

  case 44: /* LVal: ID ArrayList  */
#line 90 "parser.y"
                   {(yyval.node_val) = new LValNode((yyvsp[-1].str_val), (yyvsp[0].node_val));}
#line 1569 "parser.tab.c"
    break;

  case 45: /* ArrayList: LB Exp RB  */
#line 91 "parser.y"
                        {(yyval.node_val) = new ArrayListNode((yyvsp[-1].node_val), nullptr);}
#line 1575 "parser.tab.c"
    break;

  case 46: /* ArrayList: LB Exp RB ArrayList  */
#line 92 "parser.y"
                                  {(yyval.node_val) = new ArrayListNode((yyvsp[-2].node_val), (yyvsp[0].node_val));}
#line 1581 "parser.tab.c"
    break;

  case 47: /* VarDecl: INT VarDefs SEMICOLON  */
#line 93 "parser.y"
                                {(yyval.node_val) = new VarDeclNode((yyvsp[-1].node_val), INTTYPE);}
#line 1587 "parser.tab.c"
    break;

  case 48: /* VarDecl: FLOAT VarDefs SEMICOLON  */
#line 94 "parser.y"
                                  {(yyval.node_val) = new VarDeclNode((yyvsp[-1].node_val), FLOATTYPE);}
#line 1593 "parser.tab.c"
    break;

  case 49: /* VarDefs: VarDef  */
#line 95 "parser.y"
                 {(yyval.node_val) = new VarDefsNode((yyvsp[0].node_val), nullptr);}
#line 1599 "parser.tab.c"
    break;

  case 50: /* VarDefs: VarDef COMMA VarDefs  */
#line 96 "parser.y"
                               {(yyval.node_val) = new VarDefsNode((yyvsp[-2].node_val), (yyvsp[0].node_val));}
#line 1605 "parser.tab.c"
    break;

  case 51: /* VarDef: ID  */
#line 97 "parser.y"
             {(yyval.node_val) = new VarDefNode((yyvsp[0].str_val), nullptr, nullptr);}
#line 1611 "parser.tab.c"
    break;

  case 52: /* VarDef: ID ConstArrayList  */
#line 98 "parser.y"
                            {(yyval.node_val) = new VarDefNode((yyvsp[-1].str_val), (yyvsp[0].node_val), nullptr);}
#line 1617 "parser.tab.c"
    break;

  case 53: /* VarDef: ID ASSIGN InitVal  */
#line 99 "parser.y"
                            {(yyval.node_val) = new VarDefNode((yyvsp[-2].str_val), nullptr, (yyvsp[0].node_val));}
#line 1623 "parser.tab.c"
    break;

  case 54: /* VarDef: ID ConstArrayList ASSIGN InitVal  */
#line 100 "parser.y"
                                           {(yyval.node_val) = new VarDefNode((yyvsp[-3].str_val), (yyvsp[-2].node_val), (yyvsp[0].node_val));}
#line 1629 "parser.tab.c"
    break;

  case 55: /* InitVal: Exp  */
#line 101 "parser.y"
              {(yyval.node_val) = new InitValNode((yyvsp[0].node_val), nullptr);}
#line 1635 "parser.tab.c"
    break;

  case 56: /* InitVal: LC RC  */
#line 102 "parser.y"
                {(yyval.node_val) = new InitValNode(nullptr, nullptr);}
#line 1641 "parser.tab.c"
    break;

  case 57: /* InitVal: LC InitVals RC  */
#line 103 "parser.y"
                         {(yyval.node_val) = new InitValNode(nullptr, (yyvsp[-1].node_val));}
#line 1647 "parser.tab.c"
    break;

  case 58: /* InitVals: InitVal  */
#line 104 "parser.y"
                  {(yyval.node_val) = new InitValsNode((yyvsp[0].node_val), nullptr);}
#line 1653 "parser.tab.c"
    break;

  case 59: /* InitVals: InitVal COMMA InitVals  */
#line 105 "parser.y"
                                 {(yyval.node_val) = new InitValsNode((yyvsp[-2].node_val), (yyvsp[0].node_val));}
#line 1659 "parser.tab.c"
    break;

  case 60: /* FuncDef: VOID ID LP RP Block  */
#line 106 "parser.y"
                              {(yyval.node_val) = new FuncDefNode(VOIDTYPE, (yyvsp[-3].str_val), nullptr, (yyvsp[0].node_val));}
#line 1665 "parser.tab.c"
    break;

  case 61: /* FuncDef: INT ID LP RP Block  */
#line 107 "parser.y"
                             {(yyval.node_val) = new FuncDefNode(INTTYPE, (yyvsp[-3].str_val), nullptr, (yyvsp[0].node_val));}
#line 1671 "parser.tab.c"
    break;

  case 62: /* FuncDef: FLOAT ID LP RP Block  */
#line 108 "parser.y"
                               {(yyval.node_val) = new FuncDefNode(FLOATTYPE, (yyvsp[-3].str_val), nullptr, (yyvsp[0].node_val));}
#line 1677 "parser.tab.c"
    break;

  case 63: /* FuncDef: VOID ID LP FuncFParams RP Block  */
#line 109 "parser.y"
                                          {(yyval.node_val) = new FuncDefNode(VOIDTYPE, (yyvsp[-4].str_val), (yyvsp[-2].node_val), (yyvsp[0].node_val));}
#line 1683 "parser.tab.c"
    break;

  case 64: /* FuncDef: INT ID LP FuncFParams RP Block  */
#line 110 "parser.y"
                                         {(yyval.node_val) = new FuncDefNode(INTTYPE, (yyvsp[-4].str_val), (yyvsp[-2].node_val), (yyvsp[0].node_val));}
#line 1689 "parser.tab.c"
    break;

  case 65: /* FuncDef: FLOAT ID LP FuncFParams RP Block  */
#line 111 "parser.y"
                                           {(yyval.node_val) = new FuncDefNode(FLOATTYPE, (yyvsp[-4].str_val), (yyvsp[-2].node_val), (yyvsp[0].node_val));}
#line 1695 "parser.tab.c"
    break;

  case 66: /* FuncFParams: FuncFParam  */
#line 112 "parser.y"
                         {(yyval.node_val) = new FuncFParamsNode((yyvsp[0].node_val), nullptr);}
#line 1701 "parser.tab.c"
    break;

  case 67: /* FuncFParams: FuncFParam COMMA FuncFParams  */
#line 113 "parser.y"
                                           {(yyval.node_val) = new FuncFParamsNode((yyvsp[-2].node_val), (yyvsp[0].node_val));}
#line 1707 "parser.tab.c"
    break;

  case 68: /* FuncFParam: INT ID  */
#line 114 "parser.y"
                     {(yyval.node_val) = new FuncFParamNode(INTTYPE, (yyvsp[0].str_val), nullptr, false);}
#line 1713 "parser.tab.c"
    break;

  case 69: /* FuncFParam: FLOAT ID  */
#line 115 "parser.y"
                       {(yyval.node_val) = new FuncFParamNode(FLOATTYPE, (yyvsp[0].str_val), nullptr, false);}
#line 1719 "parser.tab.c"
    break;

  case 70: /* FuncFParam: INT ID LB RB  */
#line 116 "parser.y"
                           {(yyval.node_val) = new FuncFParamNode(INTTYPE, (yyvsp[-2].str_val), nullptr, true);}
#line 1725 "parser.tab.c"
    break;

  case 71: /* FuncFParam: FLOAT ID LB RB  */
#line 117 "parser.y"
                             {(yyval.node_val) = new FuncFParamNode(FLOATTYPE, (yyvsp[-2].str_val), nullptr, true);}
#line 1731 "parser.tab.c"
    break;

  case 72: /* FuncFParam: INT ID LB RB ArrayList  */
#line 118 "parser.y"
                                     {(yyval.node_val) = new FuncFParamNode(INTTYPE, (yyvsp[-3].str_val), (yyvsp[0].node_val), true);}
#line 1737 "parser.tab.c"
    break;

  case 73: /* FuncFParam: FLOAT ID LB RB ArrayList  */
#line 119 "parser.y"
                                       {(yyval.node_val) = new FuncFParamNode(FLOATTYPE, (yyvsp[-3].str_val), (yyvsp[0].node_val), true);}
#line 1743 "parser.tab.c"
    break;

  case 74: /* Block: LC RC  */
#line 120 "parser.y"
                {(yyval.node_val) = new BlockNode(nullptr);}
#line 1749 "parser.tab.c"
    break;

  case 75: /* Block: LC BlockItems RC  */
#line 121 "parser.y"
                           {(yyval.node_val) = new BlockNode((yyvsp[-1].node_val));}
#line 1755 "parser.tab.c"
    break;

  case 76: /* BlockItems: BlockItem  */
#line 122 "parser.y"
                        {(yyval.node_val) = new BlockItemsNode((yyvsp[0].node_val), nullptr);}
#line 1761 "parser.tab.c"
    break;

  case 77: /* BlockItems: BlockItem BlockItems  */
#line 123 "parser.y"
                                   {(yyval.node_val) = new BlockItemsNode((yyvsp[-1].node_val), (yyvsp[0].node_val));}
#line 1767 "parser.tab.c"
    break;

  case 78: /* BlockItem: Decl  */
#line 124 "parser.y"
                   {(yyval.node_val) = new BlockItemNode((yyvsp[0].node_val), nullptr);}
#line 1773 "parser.tab.c"
    break;

  case 79: /* BlockItem: Stmt  */
#line 125 "parser.y"
                   {(yyval.node_val) = new BlockItemNode(nullptr, (yyvsp[0].node_val));}
#line 1779 "parser.tab.c"
    break;

  case 80: /* Stmt: LVal ASSIGN Exp SEMICOLON  */
#line 126 "parser.y"
                                {(yyval.node_val) = new StmtNode((yyvsp[-3].node_val), (yyvsp[-1].node_val), nullptr, nullptr, nullptr, nullptr, ASSIGNSTMT);}
#line 1785 "parser.tab.c"
    break;

  case 81: /* Stmt: SEMICOLON  */
#line 127 "parser.y"
                {(yyval.node_val) = new StmtNode(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, NULLSTMT);}
#line 1791 "parser.tab.c"
    break;

  case 82: /* Stmt: Exp SEMICOLON  */
#line 128 "parser.y"
                   {(yyval.node_val) = new StmtNode(nullptr, (yyvsp[-1].node_val), nullptr, nullptr, nullptr, nullptr, EXPSTMT);}
#line 1797 "parser.tab.c"
    break;

  case 83: /* Stmt: Block  */
#line 129 "parser.y"
            {(yyval.node_val) = new StmtNode(nullptr, nullptr, (yyvsp[0].node_val), nullptr, nullptr, nullptr, BLOCKSTMT);}
#line 1803 "parser.tab.c"
    break;

  case 84: /* Stmt: IF LP Cond RP Stmt  */
#line 130 "parser.y"
                                    {(yyval.node_val) = new StmtNode(nullptr, nullptr, nullptr, (yyvsp[-2].node_val), (yyvsp[0].node_val), nullptr, IFSTMT);}
#line 1809 "parser.tab.c"
    break;

  case 85: /* Stmt: IF LP Cond RP Stmt ELSE Stmt  */
#line 131 "parser.y"
                                   {(yyval.node_val) = new StmtNode(nullptr, nullptr, nullptr, (yyvsp[-4].node_val), (yyvsp[-2].node_val), (yyvsp[0].node_val), IFSTMT);}
#line 1815 "parser.tab.c"
    break;

  case 86: /* Stmt: WHILE LP Cond RP Stmt  */
#line 132 "parser.y"
                            {(yyval.node_val) = new StmtNode(nullptr, nullptr, nullptr, (yyvsp[-2].node_val), (yyvsp[0].node_val), nullptr, WHILESTMT);}
#line 1821 "parser.tab.c"
    break;

  case 87: /* Stmt: BREAK SEMICOLON  */
#line 133 "parser.y"
                      {(yyval.node_val) = new StmtNode(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, BREAKSTMT);}
#line 1827 "parser.tab.c"
    break;

  case 88: /* Stmt: CONTINUE SEMICOLON  */
#line 134 "parser.y"
                         {(yyval.node_val) = new StmtNode(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, CONTSTMT);}
#line 1833 "parser.tab.c"
    break;

  case 89: /* Stmt: RETURN SEMICOLON  */
#line 135 "parser.y"
                       {(yyval.node_val) = new StmtNode(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, RETURNSTMT);}
#line 1839 "parser.tab.c"
    break;

  case 90: /* Stmt: RETURN Exp SEMICOLON  */
#line 136 "parser.y"
                           {(yyval.node_val) = new StmtNode(nullptr, (yyvsp[-1].node_val), nullptr, nullptr, nullptr, nullptr, RETURNSTMT);}
#line 1845 "parser.tab.c"
    break;

  case 91: /* Cond: LOrExp  */
#line 137 "parser.y"
             {(yyval.node_val) = new CondNode((yyvsp[0].node_val));}
#line 1851 "parser.tab.c"
    break;

  case 92: /* LOrExp: LAndExp  */
#line 138 "parser.y"
                  {(yyval.node_val) = new LOrExpNode(nullptr, (yyvsp[0].node_val));}
#line 1857 "parser.tab.c"
    break;

  case 93: /* LOrExp: LOrExp OR LAndExp  */
#line 139 "parser.y"
                            {(yyval.node_val) = new LOrExpNode((yyvsp[-2].node_val), (yyvsp[0].node_val));}
#line 1863 "parser.tab.c"
    break;

  case 94: /* LAndExp: EqExp  */
#line 140 "parser.y"
                {(yyval.node_val) = new LAndExpNode(nullptr, (yyvsp[0].node_val));}
#line 1869 "parser.tab.c"
    break;

  case 95: /* LAndExp: LAndExp AND EqExp  */
#line 141 "parser.y"
                            {(yyval.node_val) = new LAndExpNode((yyvsp[-2].node_val), (yyvsp[0].node_val));}
#line 1875 "parser.tab.c"
    break;

  case 96: /* EqExp: RelExp  */
#line 142 "parser.y"
                 {(yyval.node_val) = new EqExpNode(nullptr, NULLOP, (yyvsp[0].node_val));}
#line 1881 "parser.tab.c"
    break;

  case 97: /* EqExp: EqExp EQ RelExp  */
#line 143 "parser.y"
                          {(yyval.node_val) = new EqExpNode((yyvsp[-2].node_val), EQOP, (yyvsp[0].node_val));}
#line 1887 "parser.tab.c"
    break;

  case 98: /* EqExp: EqExp NE RelExp  */
#line 144 "parser.y"
                          {(yyval.node_val) = new EqExpNode((yyvsp[-2].node_val), NEOP, (yyvsp[0].node_val));}
#line 1893 "parser.tab.c"
    break;

  case 99: /* RelExp: AddExp  */
#line 145 "parser.y"
                 {(yyval.node_val) = new RelExpNode(nullptr, NULLOP, (yyvsp[0].node_val));}
#line 1899 "parser.tab.c"
    break;

  case 100: /* RelExp: RelExp GT AddExp  */
#line 146 "parser.y"
                           {(yyval.node_val) = new RelExpNode((yyvsp[-2].node_val), GTOP, (yyvsp[0].node_val));}
#line 1905 "parser.tab.c"
    break;

  case 101: /* RelExp: RelExp GE AddExp  */
#line 147 "parser.y"
                           {(yyval.node_val) = new RelExpNode((yyvsp[-2].node_val), GEOP, (yyvsp[0].node_val));}
#line 1911 "parser.tab.c"
    break;

  case 102: /* RelExp: RelExp LT AddExp  */
#line 148 "parser.y"
                           {(yyval.node_val) = new RelExpNode((yyvsp[-2].node_val), LTOP, (yyvsp[0].node_val));}
#line 1917 "parser.tab.c"
    break;

  case 103: /* RelExp: RelExp LE AddExp  */
#line 149 "parser.y"
                           {(yyval.node_val) = new RelExpNode((yyvsp[-2].node_val), LEOP, (yyvsp[0].node_val));}
#line 1923 "parser.tab.c"
    break;


#line 1927 "parser.tab.c"

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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 151 "parser.y"


/*
int main(int argc, char *argv[]) {
    int index = strlen(argv[1]) - 1;
    while(index > 0 && argv[1][index - 1] != '/')
        index--;
    strcpy(filename, argv[1] + index);
    freopen(argv[1], "r", stdin);
    yyparse();
    if (syntax_error == 0) 
        printf("finish\n");
        root->show(0);
    return 0;
}
*/

/*
void yyerror(char *msg) {
    printf("%s:%d\n", name, yylineno);
    printf("error text: %s\n", yytext);
    exit(-1);
}
*/
#include<stdarg.h>
void yyerror(const char* fmt, ...)
{
    syntax_error = 1;    
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "%s:%d ", filename, yylineno);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, ".\n");
}
