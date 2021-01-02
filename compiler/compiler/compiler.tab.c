/* A Bison parser, made by GNU Bison 3.7.3.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "compiler.y"

    #define YYDEBUG 1

    #include <stdio.h>
    #include <stdlib.h>
    #include "debugger/debugger.h"
    #include "debugger/errors.h"
    #include "code_generator/instr_generator.h"
    #include "code_generator/code_generator.h"
    #include "code_generator/registers_machine.h"

    extern int yylineno;
    extern char* yytext;
    int yylex();
    void yyerror( char *str );

#line 88 "compiler.tab.c"

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

#include "compiler.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUMBER = 3,                     /* NUMBER  */
  YYSYMBOL_ID = 4,                         /* ID  */
  YYSYMBOL_DECLARE = 5,                    /* DECLARE  */
  YYSYMBOL_T_BEGIN = 6,                    /* T_BEGIN  */
  YYSYMBOL_END = 7,                        /* END  */
  YYSYMBOL_IF = 8,                         /* IF  */
  YYSYMBOL_WHILE = 9,                      /* WHILE  */
  YYSYMBOL_REPEAT = 10,                    /* REPEAT  */
  YYSYMBOL_FOR = 11,                       /* FOR  */
  YYSYMBOL_THEN = 12,                      /* THEN  */
  YYSYMBOL_ELSE = 13,                      /* ELSE  */
  YYSYMBOL_ENDIF = 14,                     /* ENDIF  */
  YYSYMBOL_DO = 15,                        /* DO  */
  YYSYMBOL_ENDWHILE = 16,                  /* ENDWHILE  */
  YYSYMBOL_UNTIL = 17,                     /* UNTIL  */
  YYSYMBOL_FROM = 18,                      /* FROM  */
  YYSYMBOL_TO = 19,                        /* TO  */
  YYSYMBOL_ENDFOR = 20,                    /* ENDFOR  */
  YYSYMBOL_DOWNTO = 21,                    /* DOWNTO  */
  YYSYMBOL_READ = 22,                      /* READ  */
  YYSYMBOL_WRITE = 23,                     /* WRITE  */
  YYSYMBOL_24_ = 24,                       /* '-'  */
  YYSYMBOL_25_ = 25,                       /* '+'  */
  YYSYMBOL_26_ = 26,                       /* '*'  */
  YYSYMBOL_27_ = 27,                       /* '/'  */
  YYSYMBOL_28_ = 28,                       /* '%'  */
  YYSYMBOL_EQ = 29,                        /* EQ  */
  YYSYMBOL_NE = 30,                        /* NE  */
  YYSYMBOL_LT = 31,                        /* LT  */
  YYSYMBOL_LE = 32,                        /* LE  */
  YYSYMBOL_GT = 33,                        /* GT  */
  YYSYMBOL_GE = 34,                        /* GE  */
  YYSYMBOL_ASSIGN = 35,                    /* ASSIGN  */
  YYSYMBOL_36_ = 36,                       /* ','  */
  YYSYMBOL_37_ = 37,                       /* '('  */
  YYSYMBOL_38_ = 38,                       /* ':'  */
  YYSYMBOL_39_ = 39,                       /* ')'  */
  YYSYMBOL_40_ = 40,                       /* ';'  */
  YYSYMBOL_YYACCEPT = 41,                  /* $accept  */
  YYSYMBOL_program = 42,                   /* program  */
  YYSYMBOL_declarations = 43,              /* declarations  */
  YYSYMBOL_commands = 44,                  /* commands  */
  YYSYMBOL_command = 45,                   /* command  */
  YYSYMBOL_46_1 = 46,                      /* $@1  */
  YYSYMBOL_47_2 = 47,                      /* $@2  */
  YYSYMBOL_48_3 = 48,                      /* $@3  */
  YYSYMBOL_49_4 = 49,                      /* $@4  */
  YYSYMBOL_50_5 = 50,                      /* $@5  */
  YYSYMBOL_51_6 = 51,                      /* $@6  */
  YYSYMBOL_52_7 = 52,                      /* $@7  */
  YYSYMBOL_53_8 = 53,                      /* $@8  */
  YYSYMBOL_54_9 = 54,                      /* $@9  */
  YYSYMBOL_55_10 = 55,                     /* $@10  */
  YYSYMBOL_56_11 = 56,                     /* $@11  */
  YYSYMBOL_57_12 = 57,                     /* $@12  */
  YYSYMBOL_58_13 = 58,                     /* $@13  */
  YYSYMBOL_59_14 = 59,                     /* $@14  */
  YYSYMBOL_60_15 = 60,                     /* $@15  */
  YYSYMBOL_to_downto = 61,                 /* to_downto  */
  YYSYMBOL_expression = 62,                /* expression  */
  YYSYMBOL_condition = 63,                 /* condition  */
  YYSYMBOL_value = 64,                     /* value  */
  YYSYMBOL_valueloc = 65,                  /* valueloc  */
  YYSYMBOL_ridentifier = 66,               /* ridentifier  */
  YYSYMBOL_lidentifier = 67                /* lidentifier  */
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
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   128

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  57
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  122

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
       2,     2,     2,     2,     2,     2,     2,    28,     2,     2,
      37,    39,    26,    25,    36,    24,     2,    27,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    38,    40,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    29,
      30,    31,    32,    33,    34,    35
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    57,    57,    58,    61,    62,    63,    64,    67,    68,
      71,    73,    74,    76,    73,    84,    86,    88,    89,    84,
      97,   101,    97,   109,   110,   112,   114,   115,   119,   109,
     128,   129,   132,   133,   135,   136,   137,   138,   139,   140,
     143,   144,   145,   146,   147,   148,   151,   152,   155,   156,
     157,   158,   161,   162,   163,   166,   167,   168
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
  "\"end of file\"", "error", "\"invalid token\"", "NUMBER", "ID",
  "DECLARE", "T_BEGIN", "END", "IF", "WHILE", "REPEAT", "FOR", "THEN",
  "ELSE", "ENDIF", "DO", "ENDWHILE", "UNTIL", "FROM", "TO", "ENDFOR",
  "DOWNTO", "READ", "WRITE", "'-'", "'+'", "'*'", "'/'", "'%'", "EQ", "NE",
  "LT", "LE", "GT", "GE", "ASSIGN", "','", "'('", "':'", "')'", "';'",
  "$accept", "program", "declarations", "commands", "command", "$@1",
  "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11",
  "$@12", "$@13", "$@14", "$@15", "to_downto", "expression", "condition",
  "value", "valueloc", "ridentifier", "lidentifier", YY_NULLPTR
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
     275,   276,   277,   278,    45,    43,    42,    47,    37,   279,
     280,   281,   282,   283,   284,   285,    44,    40,    58,    41,
      59
};
#endif

#define YYPACT_NINF (-27)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -3,     0,    94,    18,    13,     2,    31,   -27,   -27,   -27,
     -27,    25,     7,     5,   -27,    34,   -27,    67,    94,    33,
      36,    38,    38,    94,    68,    35,   -27,    37,    39,   -27,
     -27,    38,    40,    44,    43,    42,    45,   -27,    48,   -27,
      -8,   -27,   -27,    54,   -27,   -27,    53,   -27,    46,    86,
      70,   -27,    87,   -27,   -27,    56,    76,    38,    38,    38,
      38,    38,    38,    82,    38,    91,    61,    79,   -27,    38,
      38,    38,    38,    38,    80,    77,    81,    83,   -27,   -27,
     -27,   -27,   -27,   -27,   -27,   -27,   -27,    38,   -27,   -27,
     -27,   -27,   -27,   -27,   -27,   -27,   118,   -27,   -27,    94,
      94,    84,   -27,    88,    85,    94,   -27,    -2,   -27,   -27,
     107,   -27,   -27,    38,   -27,   -27,   110,   -27,    94,    94,
     106,   -27
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     6,     0,    55,    11,    15,    20,
      23,     0,     0,     0,     9,     0,     1,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    48,    49,     0,     3,
       8,     0,     0,     0,     4,     0,     0,    46,    52,    12,
       0,    47,    16,     0,    24,    30,     0,    31,     0,    34,
       0,     2,     0,    57,    56,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    10,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    13,    40,
      41,    42,    44,    43,    45,    17,    21,     0,    51,    50,
      36,    35,    37,    38,    39,     7,     0,    54,    53,     0,
       0,     0,    25,     0,     0,    18,    22,     0,     5,    14,
       0,    32,    33,     0,    19,    26,     0,    27,     0,    28,
       0,    29
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -27,   -27,   -27,   -17,   -13,   -27,   -27,   -27,   -27,   -27,
     -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,
     -27,   -27,   -15,   -26,   -27,   -27,   117
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     5,    13,    14,    21,    56,    99,    22,    63,
     100,   110,    23,   101,    24,    65,   107,   116,   118,   120,
     113,    48,    39,    40,    28,    41,    15
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      30,    33,     1,     2,     4,    49,    43,    42,    18,     6,
      26,    27,    29,     7,     8,     9,    10,   111,    16,   112,
      30,    57,    58,    59,    60,    61,    62,    11,    12,     6,
      30,    79,    80,    81,    82,    83,    84,    34,    19,    35,
      36,    37,    38,    90,    91,    92,    93,    94,     6,    86,
      17,    51,     7,     8,     9,    10,    66,    67,     6,    76,
      77,   102,     7,     8,     9,    10,    11,    12,    20,    31,
      32,    64,    44,    74,    46,    45,    11,    12,    50,    47,
      52,    53,   104,   105,    54,    55,    68,   115,    78,     6,
      75,    30,    30,     7,     8,     9,    10,    85,     6,   109,
      88,   119,     7,     8,     9,    10,    30,    11,    12,    87,
      69,    70,    71,    72,    73,    96,    11,    12,    89,    95,
      97,   103,    98,   114,   106,   117,   121,   108,    25
};

static const yytype_int8 yycheck[] =
{
      13,    18,     5,     6,     4,    31,    23,    22,     6,     4,
       3,     4,     7,     8,     9,    10,    11,    19,     0,    21,
      33,    29,    30,    31,    32,    33,    34,    22,    23,     4,
      43,    57,    58,    59,    60,    61,    62,     4,    36,     3,
       4,     3,     4,    69,    70,    71,    72,    73,     4,    64,
      37,     7,     8,     9,    10,    11,     3,     4,     4,     3,
       4,    87,     8,     9,    10,    11,    22,    23,    37,    35,
       3,    17,     4,     3,    37,    40,    22,    23,    38,    40,
      37,    39,    99,   100,    39,    37,    40,   113,    12,     4,
       3,   104,   105,     8,     9,    10,    11,    15,     4,    14,
      39,   118,     8,     9,    10,    11,   119,    22,    23,    18,
      24,    25,    26,    27,    28,    38,    22,    23,    39,    39,
      39,     3,    39,    16,    40,    15,    20,    39,    11
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     5,     6,    42,     4,    43,     4,     8,     9,    10,
      11,    22,    23,    44,    45,    67,     0,    37,     6,    36,
      37,    46,    49,    53,    55,    67,     3,     4,    65,     7,
      45,    35,     3,    44,     4,     3,     4,     3,     4,    63,
      64,    66,    63,    44,     4,    40,    37,    40,    62,    64,
      38,     7,    37,    39,    39,    37,    47,    29,    30,    31,
      32,    33,    34,    50,    17,    56,     3,     4,    40,    24,
      25,    26,    27,    28,     3,     3,     3,     4,    12,    64,
      64,    64,    64,    64,    64,    15,    63,    18,    39,    39,
      64,    64,    64,    64,    64,    39,    38,    39,    39,    48,
      51,    54,    64,     3,    44,    44,    40,    57,    39,    14,
      52,    19,    21,    61,    16,    64,    58,    15,    59,    44,
      60,    20
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    42,    43,    43,    43,    43,    44,    44,
      45,    46,    47,    48,    45,    49,    50,    51,    52,    45,
      53,    54,    45,    55,    56,    57,    58,    59,    60,    45,
      45,    45,    61,    61,    62,    62,    62,    62,    62,    62,
      63,    63,    63,    63,    63,    63,    64,    64,    65,    65,
      65,    65,    66,    66,    66,    67,    67,    67
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     3,     3,     8,     1,     6,     2,     1,
       4,     0,     0,     0,     8,     0,     0,     0,     0,     9,
       0,     0,     7,     0,     0,     0,     0,     0,     0,    15,
       3,     3,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     1,     1,     1,
       4,     4,     1,     4,     4,     1,     4,     4
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
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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
  case 2: /* program: DECLARE declarations T_BEGIN commands END  */
#line 57 "compiler.y"
                                                   { halt(); YYACCEPT; }
#line 1216 "compiler.tab.c"
    break;

  case 3: /* program: T_BEGIN commands END  */
#line 58 "compiler.y"
                                                   { halt(); YYACCEPT; }
#line 1222 "compiler.tab.c"
    break;

  case 4: /* declarations: declarations ',' ID  */
#line 61 "compiler.y"
                                                   { add_variable((yyvsp[0].id));      }
#line 1228 "compiler.tab.c"
    break;

  case 5: /* declarations: declarations ',' ID '(' NUMBER ':' NUMBER ')'  */
#line 62 "compiler.y"
                                                   { add_array((yyvsp[-5].id), (yyvsp[-3].val), (yyvsp[-1].val)); }
#line 1234 "compiler.tab.c"
    break;

  case 6: /* declarations: ID  */
#line 63 "compiler.y"
                                                   { add_variable((yyvsp[0].id));      }
#line 1240 "compiler.tab.c"
    break;

  case 7: /* declarations: ID '(' NUMBER ':' NUMBER ')'  */
#line 64 "compiler.y"
                                                   { add_array((yyvsp[-5].id), (yyvsp[-3].val), (yyvsp[-1].val)); }
#line 1246 "compiler.tab.c"
    break;

  case 10: /* command: lidentifier ASSIGN expression ';'  */
#line 71 "compiler.y"
                                                        { assign((yyvsp[-3].unit), (yyvsp[-1].unit)); }
#line 1252 "compiler.tab.c"
    break;

  case 11: /* $@1: %empty  */
#line 73 "compiler.y"
                    {   (yyvsp[0].cond) = cond_alloc();                  }
#line 1258 "compiler.tab.c"
    break;

  case 12: /* $@2: %empty  */
#line 74 "compiler.y"
                    {   jump_true_false((yyvsp[-2].cond), (yyvsp[0].unit), INIT);
                        jump_end((yyvsp[-2].cond), (yyvsp[0].unit), INIT);             }
#line 1265 "compiler.tab.c"
    break;

  case 13: /* $@3: %empty  */
#line 76 "compiler.y"
                    {   (yyvsp[-4].cond)->label_cmd = code_get_label();   }
#line 1271 "compiler.tab.c"
    break;

  case 14: /* command: IF $@1 condition $@2 THEN $@3 commands ENDIF  */
#line 78 "compiler.y"
                    {   (yyvsp[-7].cond)->label_end = code_get_label();
                        jump_true_false((yyvsp[-7].cond), (yyvsp[-5].unit), FINISH);
                        jump_end((yyvsp[-7].cond), (yyvsp[-5].unit), FINISH);
                        DBG_JUMPS((yyvsp[-7].cond));
                        jumps_free((yyvsp[-7].cond), (yyvsp[-5].unit));                 }
#line 1281 "compiler.tab.c"
    break;

  case 15: /* $@4: %empty  */
#line 84 "compiler.y"
                    {   (yyvsp[0].cond) = cond_alloc();                    
                        (yyvsp[0].cond)->label_cond = code_get_label();  }
#line 1288 "compiler.tab.c"
    break;

  case 16: /* $@5: %empty  */
#line 86 "compiler.y"
                    {   jump_true_false((yyvsp[-2].cond), (yyvsp[0].unit), INIT);
                        jump_end((yyvsp[-2].cond), (yyvsp[0].unit), INIT);             }
#line 1295 "compiler.tab.c"
    break;

  case 17: /* $@6: %empty  */
#line 88 "compiler.y"
                    {   (yyvsp[-4].cond)->label_cmd = code_get_label();   }
#line 1301 "compiler.tab.c"
    break;

  case 18: /* $@7: %empty  */
#line 89 "compiler.y"
                    {   jump_cond((yyvsp[-6].cond), (yyvsp[-4].unit), INIT);            }
#line 1307 "compiler.tab.c"
    break;

  case 19: /* command: WHILE $@4 condition $@5 DO $@6 commands $@7 ENDWHILE  */
#line 90 "compiler.y"
                    {   (yyvsp[-8].cond)->label_end = code_get_label();
                        jump_true_false((yyvsp[-8].cond), (yyvsp[-6].unit), FINISH);
                        jump_end((yyvsp[-8].cond), (yyvsp[-6].unit), FINISH);
                        jump_cond((yyvsp[-8].cond), (yyvsp[-6].unit), FINISH);
                        DBG_JUMPS((yyvsp[-8].cond));
                        jumps_free((yyvsp[-8].cond), (yyvsp[-6].unit));                 }
#line 1318 "compiler.tab.c"
    break;

  case 20: /* $@8: %empty  */
#line 97 "compiler.y"
                    {   (yyvsp[0].cond) = cond_alloc();                 
                        (yyvsp[0].cond)->label_cmd = code_get_label();   }
#line 1325 "compiler.tab.c"
    break;

  case 21: /* $@9: %empty  */
#line 101 "compiler.y"
                    {   jump_true_false((yyvsp[-4].cond), (yyvsp[0].unit), INIT);
                        jump_cmd((yyvsp[-4].cond), (yyvsp[0].unit), INIT);             }
#line 1332 "compiler.tab.c"
    break;

  case 22: /* command: REPEAT $@8 commands UNTIL condition $@9 ';'  */
#line 103 "compiler.y"
                    {   (yyvsp[-6].cond)->label_end = code_get_label();
                        jump_true_false((yyvsp[-6].cond), (yyvsp[-2].unit), FINISH);
                        jump_cmd((yyvsp[-6].cond), (yyvsp[-2].unit), FINISH);
                        DBG_JUMPS((yyvsp[-6].cond));
                        jumps_free((yyvsp[-6].cond), (yyvsp[-2].unit));                 }
#line 1342 "compiler.tab.c"
    break;

  case 23: /* $@10: %empty  */
#line 109 "compiler.y"
                    {   (yyvsp[0].cond) = cond_alloc();                  }
#line 1348 "compiler.tab.c"
    break;

  case 24: /* $@11: %empty  */
#line 110 "compiler.y"
                    {   (yyvsp[-2].cond)->iter = add_iterator((yyvsp[0].id));        }
#line 1354 "compiler.tab.c"
    break;

  case 25: /* $@12: %empty  */
#line 112 "compiler.y"
                    {   for_init((yyvsp[-5].cond), (yyvsp[0].unit));                   }
#line 1360 "compiler.tab.c"
    break;

  case 26: /* $@13: %empty  */
#line 114 "compiler.y"
                    {   for_cond((yyvsp[-3].unit), (yyvsp[0].unit), (yyvsp[-1].type));               }
#line 1366 "compiler.tab.c"
    break;

  case 27: /* $@14: %empty  */
#line 115 "compiler.y"
                    {   (yyvsp[-10].cond)->label_cond = code_get_label();
                        jump_true_false((yyvsp[-10].cond), (yyvsp[-2].unit), INIT);
                        jump_end((yyvsp[-10].cond), (yyvsp[-2].unit), INIT);        
                        (yyvsp[-10].cond)->label_cmd = code_get_label();   }
#line 1375 "compiler.tab.c"
    break;

  case 28: /* $@15: %empty  */
#line 119 "compiler.y"
                    {   for_step((yyvsp[-12].cond), (yyvsp[-7].unit), (yyvsp[-4].unit), (yyvsp[-5].type));
                        jump_cond((yyvsp[-12].cond), (yyvsp[-4].unit), INIT);            }
#line 1382 "compiler.tab.c"
    break;

  case 29: /* command: FOR $@10 ID $@11 FROM value $@12 to_downto value $@13 DO $@14 commands $@15 ENDFOR  */
#line 121 "compiler.y"
                    {   (yyvsp[-14].cond)->label_end = code_get_label();
                        jump_true_false((yyvsp[-14].cond), (yyvsp[-6].unit), FINISH);
                        jump_end((yyvsp[-14].cond), (yyvsp[-6].unit), FINISH);
                        jump_cond((yyvsp[-14].cond), (yyvsp[-6].unit), FINISH);
                        for_free((yyvsp[-14].cond), (yyvsp[-9].unit), (yyvsp[-6].unit));
                        remove_iterator((yyvsp[-12].id));                }
#line 1393 "compiler.tab.c"
    break;

  case 30: /* command: READ lidentifier ';'  */
#line 128 "compiler.y"
                               { read((yyvsp[-1].unit));         }
#line 1399 "compiler.tab.c"
    break;

  case 31: /* command: WRITE valueloc ';'  */
#line 129 "compiler.y"
                               { write((yyvsp[-1].unit));        }
#line 1405 "compiler.tab.c"
    break;

  case 32: /* to_downto: TO  */
#line 132 "compiler.y"
                               { (yyval.type) = FOR_TO;      }
#line 1411 "compiler.tab.c"
    break;

  case 33: /* to_downto: DOWNTO  */
#line 133 "compiler.y"
                               { (yyval.type) = FOR_DOWNTO;  }
#line 1417 "compiler.tab.c"
    break;

  case 34: /* expression: value  */
#line 135 "compiler.y"
                               { (yyval.unit) = (yyvsp[0].unit);          }
#line 1423 "compiler.tab.c"
    break;

  case 35: /* expression: value '+' value  */
#line 136 "compiler.y"
                               { (yyval.unit) = sum((yyvsp[-2].unit), (yyvsp[0].unit)); }
#line 1429 "compiler.tab.c"
    break;

  case 36: /* expression: value '-' value  */
#line 137 "compiler.y"
                               { (yyval.unit) = dif((yyvsp[-2].unit), (yyvsp[0].unit)); }
#line 1435 "compiler.tab.c"
    break;

  case 37: /* expression: value '*' value  */
#line 138 "compiler.y"
                               { (yyval.unit) = mul((yyvsp[-2].unit), (yyvsp[0].unit)); }
#line 1441 "compiler.tab.c"
    break;

  case 40: /* condition: value EQ value  */
#line 143 "compiler.y"
                                     { (yyval.unit) = eq_ne((yyvsp[-2].unit), (yyvsp[0].unit), EQUAL);         }
#line 1447 "compiler.tab.c"
    break;

  case 41: /* condition: value NE value  */
#line 144 "compiler.y"
                                     { (yyval.unit) = eq_ne((yyvsp[-2].unit), (yyvsp[0].unit), NOT_EQUAL);     }
#line 1453 "compiler.tab.c"
    break;

  case 42: /* condition: value LT value  */
#line 145 "compiler.y"
                                     { (yyval.unit) = lt_ge((yyvsp[-2].unit), (yyvsp[0].unit), LESS);          }
#line 1459 "compiler.tab.c"
    break;

  case 43: /* condition: value GT value  */
#line 146 "compiler.y"
                                     { (yyval.unit) = gt_le((yyvsp[-2].unit), (yyvsp[0].unit), GREATER);       }
#line 1465 "compiler.tab.c"
    break;

  case 44: /* condition: value LE value  */
#line 147 "compiler.y"
                                     { (yyval.unit) = gt_le((yyvsp[-2].unit), (yyvsp[0].unit), LESS_EQUAL);    }
#line 1471 "compiler.tab.c"
    break;

  case 45: /* condition: value GE value  */
#line 148 "compiler.y"
                                     { (yyval.unit) = lt_ge((yyvsp[-2].unit), (yyvsp[0].unit), GREATER_EQUAL); }
#line 1477 "compiler.tab.c"
    break;

  case 46: /* value: NUMBER  */
#line 151 "compiler.y"
                                     { (yyval.unit) = get_const((yyvsp[0].val),         VALUE); }
#line 1483 "compiler.tab.c"
    break;

  case 47: /* value: ridentifier  */
#line 152 "compiler.y"
                                     { (yyval.unit) = (yyvsp[0].unit);                           }
#line 1489 "compiler.tab.c"
    break;

  case 48: /* valueloc: NUMBER  */
#line 155 "compiler.y"
                                     { (yyval.unit) = get_const((yyvsp[0].val),         LOCATION);         }
#line 1495 "compiler.tab.c"
    break;

  case 49: /* valueloc: ID  */
#line 156 "compiler.y"
                                     { (yyval.unit) = get_variable((yyvsp[0].id),      LOCATION, INIT);   }
#line 1501 "compiler.tab.c"
    break;

  case 50: /* valueloc: ID '(' ID ')'  */
#line 157 "compiler.y"
                                     { (yyval.unit) = get_array_var((yyvsp[-3].id), (yyvsp[-1].id), LOCATION, INIT);   }
#line 1507 "compiler.tab.c"
    break;

  case 51: /* valueloc: ID '(' NUMBER ')'  */
#line 158 "compiler.y"
                                     { (yyval.unit) = get_array_num((yyvsp[-3].id), (yyvsp[-1].val), LOCATION, INIT);   }
#line 1513 "compiler.tab.c"
    break;

  case 52: /* ridentifier: ID  */
#line 161 "compiler.y"
                                     { (yyval.unit) = get_variable((yyvsp[0].id),      VALUE, INIT);      }
#line 1519 "compiler.tab.c"
    break;

  case 53: /* ridentifier: ID '(' ID ')'  */
#line 162 "compiler.y"
                                     { (yyval.unit) = get_array_var((yyvsp[-3].id), (yyvsp[-1].id), VALUE, INIT);      }
#line 1525 "compiler.tab.c"
    break;

  case 54: /* ridentifier: ID '(' NUMBER ')'  */
#line 163 "compiler.y"
                                     { (yyval.unit) = get_array_num((yyvsp[-3].id), (yyvsp[-1].val), VALUE, INIT);      }
#line 1531 "compiler.tab.c"
    break;

  case 55: /* lidentifier: ID  */
#line 166 "compiler.y"
                                     { (yyval.unit) = get_variable((yyvsp[0].id),      LOCATION, NOINIT); }
#line 1537 "compiler.tab.c"
    break;

  case 56: /* lidentifier: ID '(' ID ')'  */
#line 167 "compiler.y"
                                     { (yyval.unit) = get_array_var((yyvsp[-3].id), (yyvsp[-1].id), LOCATION, NOINIT); }
#line 1543 "compiler.tab.c"
    break;

  case 57: /* lidentifier: ID '(' NUMBER ')'  */
#line 168 "compiler.y"
                                     { (yyval.unit) = get_array_num((yyvsp[-3].id), (yyvsp[-1].val), LOCATION, NOINIT); }
#line 1549 "compiler.tab.c"
    break;


#line 1553 "compiler.tab.c"

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

#line 169 "compiler.y"


/* Metoda startowa.
 * ERR1 - nieprawidlowa liczba argumentow
 * ERR2 - problem z otwarciem argv[1]
 * ERR3 - problem z otwarciem argv[2]
 */
int main( int argc, char** argv )
{ 
    extern FILE *yyin;
    FILE* output;

    if (argc != 3) {
        ERR_BAD_CALL(argv[0]);
        ERR_ADD();
    }
    else if ((yyin = fopen(argv[1], "r")) == NULL) {
        ERR_BAD_FILENAME(argv[1]);
        ERR_ADD();
    }

    DBG_PARSER_BEGIN();
    reg_init();
    yyparse();
    DBG_PARSER_END();
    DBG_REGISTER_PRINT();

    if ((output = fopen(argv[2], "w")) == NULL) {
        ERR_BAD_FILENAME(argv[2]);
        ERR_ADD();
    }

    code_print_all(output);
    return 0;
}

void yyerror (char* str)
{
    ERR_SYNTAX();
    ERR_ADD();
}
