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
#line 1 "syntax.y"

	#include <stdio.h>
	#include <stdlib.h>
    #include <ctype.h>
    #include <assert.h>
	// #include "ir.h"
    #include "asm.h"
    // #include "RBTtest.c"

	#define YYSTYPE struct node*
    #include "lex.yy.c"

    #define UNDEFINED_VARIABLE 1
    #define UNDEFINED_FUNCTION 2
    #define REDEFINED_VARIABLE 3
    #define REDEFINED_FUNCTION 4
    #define TYPE_MISMATCH_ASSIGNMENT 5
    #define NEED_VARIABLE 6
    #define TYPE_MISMATCH_OPERAND 7
    #define TYPE_MISMATCH_RETURN 8
    #define FUNCTION_MISMATCH 9
    #define NOT_ARRAY 10
    #define NOT_FUNCTION 11
    #define ARRAY_ACCESS_OPERATEOR_NOT_INTEGER 12
    #define DOT_ILLEGAL_USE 13
    #define NOT_EXISTENT_FIELD 14
    #define REDEFINED_FIELD 15
    #define REDEFINED_STRUCT 16
    #define UNDEFINED_STRUCT 17
    #define DECLARED_BUT_NOT_DEFINED 18
    #define AMBIGUOUS_FUNCTION_DECLARATION 19

    #define MIN(i, j) (((i) < (j)) ? (i) : (j))
    #define MAX(i, j) (((i) > (j)) ? (i) : (j))


	void yyerror(char*);
	void myerror(char*);
	int yylex();
	extern int yylineno;
	extern int last_row;
    extern int CompstCNT;
	int errors = 0;
    int yydebug = 1;
    int flgStruct = 0, flgArr = 0, func_cnt = 0;
    int Regcnt = 0;
    char VarReg[10][10];
    char Compst_return_type[20] = "null";
    char func_list[20][20];
    struct rb_root mytree = RB_ROOT;
    // MyType tmp; // 从全局变量改用局部变量
    VariLink this_scope;
    VariLink variList;

    char *strlwr(char *str) {
        char *ptr = str;

        while (*ptr != '\0') {
            if (isupper(*ptr))
                *ptr = tolower(*ptr);
                ptr++;
        }

        return str;
    }

#line 137 "syntax.tab.c"

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
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
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
    INT = 258,
    FLOAT = 259,
    TYPE = 260,
    NEWLINE = 261,
    ID = 262,
    SEMI = 263,
    COMMA = 264,
    DOT = 265,
    ASSIGNOP = 266,
    RELOP = 267,
    PLUS = 268,
    MINUS = 269,
    STAR = 270,
    DIV = 271,
    AND = 272,
    OR = 273,
    NOT = 274,
    LP = 275,
    RP = 276,
    LB = 277,
    RB = 278,
    LC = 279,
    RC = 280,
    STRUCT = 281,
    RETURN = 282,
    IF = 283,
    ELSE = 284,
    WHILE = 285,
    NAGATE = 286,
    LOWER_THAN_RB = 287,
    LOWER_THAN_ELSE = 288
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
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
int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */



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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   300

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  132

#define YYUNDEFTOK  2
#define YYMAXUTOK   288


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
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    97,    97,   102,   106,   111,   174,   180,   282,   340,
     343,   355,   371,   378,   445,   466,   469,   474,   479,   558,
     579,   586,   591,   596,   613,   621,   625,   629,   649,   741,
     746,   751,   760,   764,   769,   772,   782,   789,   798,   816,
     819,   826,   833,   844,   847,   853,   859,   864,   871,   999,
    1004,  1088,  1174,  1265,  1355,  1445,  1535,  1625,  1632,  1638,
    1644,  1788,  1853,  1911,  1956,  1979,  1984,  1989,  1994,  2000,
    2007,  2012
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "TYPE", "NEWLINE", "ID",
  "SEMI", "COMMA", "DOT", "ASSIGNOP", "RELOP", "PLUS", "MINUS", "STAR",
  "DIV", "AND", "OR", "NOT", "LP", "RP", "LB", "RB", "LC", "RC", "STRUCT",
  "RETURN", "IF", "ELSE", "WHILE", "NAGATE", "LOWER_THAN_RB",
  "LOWER_THAN_ELSE", "$accept", "Program", "ExtDefList", "ExtDef",
  "ExtDecList", "Specifier", "StructSpecifier", "OptTag", "Tag", "FunDec",
  "VarList", "ParamDec", "CompSt", "Mid", "Def", "Stmt", "DecList", "Dec",
  "VarDec", "Exp", "Args", YY_NULLPTR
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
     285,   286,   287,   288
};
# endif

#define YYPACT_NINF (-35)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-28)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       3,   -35,    32,    38,   -35,     3,    29,   -35,    33,    35,
     -35,   -35,   -35,    41,   -35,    55,    10,    18,    51,     9,
     -35,   -35,    51,   -35,    57,    13,    57,   -35,   -35,    46,
     164,   164,   128,   164,    47,    49,    14,   -35,    59,    51,
      51,   100,    64,   -35,    57,    66,    63,    67,   -35,   -35,
      71,    72,     5,    89,    91,     0,   120,    58,    31,    81,
     218,   177,   164,   164,    96,    11,   -35,   -35,   -35,   -35,
     -35,    98,   142,   164,   164,   164,   164,   164,   164,   164,
     150,   -35,    97,   -35,     3,   -35,   -35,   -35,   -35,   -35,
     -35,    57,   164,    99,   -35,   191,   104,   -35,   -35,   -35,
     231,   244,   -35,   -35,   -35,   -35,   -35,   257,   278,    58,
      58,    31,    31,   268,   268,   103,   204,   -35,   -35,   257,
     -35,   164,   -35,    79,    79,   -35,   -35,   -35,   101,   -35,
      79,   -35
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,    11,    16,     0,     2,     4,     0,    12,    17,     0,
      14,     1,     3,    43,     6,     0,     0,     9,     0,     0,
       5,     8,     0,     7,     0,     0,     0,    65,    66,    64,
       0,     0,     0,     0,     0,     0,     0,    34,     0,     0,
       0,     0,     0,    19,     0,     0,    22,     0,    43,    10,
       0,     0,     0,     0,    39,    41,     0,    58,    59,     0,
       0,     0,     0,     0,     0,     0,    13,    25,    26,    33,
      32,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    20,    23,    18,     0,    24,    44,    47,    46,    45,
      30,     0,     0,     0,    61,    71,     0,    67,    57,    35,
       0,     0,    31,    29,    28,    63,    49,    48,    52,    53,
      54,    55,    56,    50,    51,     0,     0,    21,    40,    42,
      68,     0,    60,     0,     0,    69,    62,    70,    36,    38,
       0,    37
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -35,   -35,   123,   -35,   109,     4,   -35,   -35,   -35,   -35,
      52,   -35,   121,   -15,   -35,   -34,   -31,   -35,     7,   -30,
      17
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,    15,    36,     7,     9,    10,    16,
      45,    46,    37,    38,    39,    40,    53,    54,    55,    41,
      96
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      57,    58,    60,    61,     6,    65,    88,    47,     1,     6,
      42,    92,   103,    17,     1,    64,    50,    51,    21,   104,
      52,    48,    25,    44,    67,    68,    95,    24,    89,     2,
      43,    17,   100,   101,    22,     2,    13,    14,    11,     8,
      25,    71,   107,   108,   109,   110,   111,   112,   113,   114,
     116,    82,    26,    80,    27,    28,     1,   -15,    29,    18,
     118,    19,   119,    20,    48,    30,    56,    62,    71,    63,
      31,    32,    84,    76,    77,    22,   -27,     2,    33,    34,
      80,    35,    27,    28,    66,    81,    29,    83,    44,   128,
     129,    95,    85,    30,    86,    87,   131,    90,    31,    32,
      91,    69,    97,    22,   102,   105,    33,    34,    70,    35,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    25,
     120,    93,    80,    27,    28,   122,   125,    29,    12,    59,
     130,    27,    28,    49,    30,    29,   117,    23,   127,    31,
      32,    94,    30,   106,     0,    27,    28,    31,    32,    29,
       0,   115,     0,    27,    28,     0,    30,    29,     0,     0,
       0,    31,    32,     0,    30,     0,     0,    27,    28,    31,
      32,    29,     0,     0,     0,     0,     0,     0,    30,     0,
       0,     0,     0,    31,    32,    99,     0,    71,    72,    73,
      74,    75,    76,    77,    78,    79,     0,     0,     0,    80,
     121,    71,    72,    73,    74,    75,    76,    77,    78,    79,
       0,     0,     0,    80,    71,    72,    73,    74,    75,    76,
      77,    78,    79,     0,     0,     0,    80,   126,    71,    72,
      73,    74,    75,    76,    77,    78,    79,     0,     0,    98,
      80,    71,    72,    73,    74,    75,    76,    77,    78,    79,
       0,     0,   123,    80,    71,    72,    73,    74,    75,    76,
      77,    78,    79,     0,     0,   124,    80,    71,    72,    73,
      74,    75,    76,    77,    78,    79,     0,     0,    71,    80,
      73,    74,    75,    76,    77,     0,     0,     0,    71,     0,
      80,    74,    75,    76,    77,     0,     0,     0,     0,     0,
      80
};

static const yytype_int16 yycheck[] =
{
      30,    31,    32,    33,     0,    36,     1,    22,     5,     5,
       1,    11,     1,     6,     5,     1,     3,     4,     8,     8,
       7,     7,    22,    19,    39,    40,    56,     9,    23,    26,
      21,    24,    62,    63,    24,    26,     7,     8,     0,     7,
      22,    10,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    44,     1,    22,     3,     4,     5,    24,     7,    24,
      91,    20,    92,     8,     7,    14,    20,    20,    10,    20,
      19,    20,     9,    15,    16,    24,    25,    26,    27,    28,
      22,    30,     3,     4,    25,    21,     7,    21,    84,   123,
     124,   121,    25,    14,    23,    23,   130,     8,    19,    20,
       9,     1,    21,    24,     8,     7,    27,    28,     8,    30,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    22,
      21,     1,    22,     3,     4,    21,    23,     7,     5,     1,
      29,     3,     4,    24,    14,     7,    84,    16,   121,    19,
      20,    21,    14,     1,    -1,     3,     4,    19,    20,     7,
      -1,     1,    -1,     3,     4,    -1,    14,     7,    -1,    -1,
      -1,    19,    20,    -1,    14,    -1,    -1,     3,     4,    19,
      20,     7,    -1,    -1,    -1,    -1,    -1,    -1,    14,    -1,
      -1,    -1,    -1,    19,    20,     8,    -1,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    -1,    -1,    -1,    22,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      -1,    -1,    -1,    22,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    -1,    -1,    -1,    22,    23,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    -1,    -1,    21,
      22,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      -1,    -1,    21,    22,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    -1,    -1,    21,    22,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    -1,    -1,    10,    22,
      12,    13,    14,    15,    16,    -1,    -1,    -1,    10,    -1,
      22,    13,    14,    15,    16,    -1,    -1,    -1,    -1,    -1,
      22
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     5,    26,    35,    36,    37,    39,    40,     7,    41,
      42,     0,    36,     7,     8,    38,    43,    52,    24,    20,
       8,     8,    24,    46,     9,    22,     1,     3,     4,     7,
      14,    19,    20,    27,    28,    30,    39,    46,    47,    48,
      49,    53,     1,    21,    39,    44,    45,    47,     7,    38,
       3,     4,     7,    50,    51,    52,    20,    53,    53,     1,
      53,    53,    20,    20,     1,    50,    25,    47,    47,     1,
       8,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      22,    21,    52,    21,     9,    25,    23,    23,     1,    23,
       8,     9,    11,     1,    21,    53,    54,    21,    21,     8,
      53,    53,     8,     1,     8,     7,     1,    53,    53,    53,
      53,    53,    53,    53,    53,     1,    53,    44,    50,    53,
      21,     9,    21,    21,    21,    23,    23,    54,    49,    49,
      29,    49
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    34,    35,    36,    36,    37,    37,    37,    37,    38,
      38,    39,    39,    40,    40,    41,    41,    42,    43,    43,
      43,    44,    44,    45,    46,    47,    47,    47,    48,    48,
      48,    48,    49,    49,    49,    49,    49,    49,    49,    50,
      50,    51,    51,    52,    52,    52,    52,    52,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      54,    54
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     3,     1,
       3,     1,     1,     5,     2,     1,     0,     1,     4,     3,
       4,     3,     1,     2,     3,     2,     2,     0,     3,     3,
       3,     3,     2,     2,     1,     3,     5,     7,     5,     1,
       3,     1,     3,     1,     4,     4,     4,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       4,     3,     4,     3,     1,     1,     1,     3,     4,     4,
       3,     1
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

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
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


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 97 "syntax.y"
                     {
        yyval = insNode(yyvsp[0], "Program", yyvsp[0]->lines, NON_TERMINAL);
    }
#line 1630 "syntax.tab.c"
    break;

  case 3:
#line 102 "syntax.y"
                               {
        yyval = insNode(yyvsp[-1], "ExtDefList", (yylsp[-1]).first_line, NON_TERMINAL);
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 1639 "syntax.tab.c"
    break;

  case 4:
#line 106 "syntax.y"
      {
        yyval = insNode(NULL, "ExtDefList", yylineno, NON_TERMINAL);
    }
#line 1647 "syntax.tab.c"
    break;

  case 5:
#line 111 "syntax.y"
                                   {
        yyval = insNode(yyvsp[-2], "ExtDef", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];

        struct node* newnode = yyvsp[-1];          
        do {
            MyType tmp = MyType_default;
            tmp.def = 1;
            // printf("flgArr = %d\n", flgArr);
            if(!flgArr) { // 不是数组
                strcpy(tmp.name, newnode->child->child->id);
            }
            else { // 是数组
                strcpy(tmp.name, newnode->child->child->child->child->id);
            }

            strcpy(Compst_return_type, "null");

            if(search(this_scope, tmp)) { // 两种可能：struct xx {...} yy; 或 int a;
                char msg[100];
                if(!flgStruct) {// 普通变量声明
                    errors++;
                    printf("Error %d at line %d : Redefined variable \'%s\'\n", REDEFINED_VARIABLE, last_row, tmp.name);
                    // sprintf(msg, "Error %d at line %d : Redefined variable \'%s\'", REDEFINED_VARIABLE, last_row, tmp.name);
                }
                else {// 结构体变量声明
                    errors++;
                    printf("Error %d at line %d : Redefined field \'%s\'\n", REDEFINED_FIELD, last_row, tmp.name);
                    // sprintf(msg, "Error %d at line %d : Redefined field \'%s\'", REDEFINED_FIELD, last_row, tmp.name);
                }
                // myerror(msg);
            }

            // printf("flgStruct: %d\n", flgStruct);
            if(flgStruct) { // 是struct tag的情况，如struct sa nn;
                tmp.isstruct = 1;
                
                strcpy(tmp.type, yyvsp[-2]->child->child->bro->child->id);
                flgStruct = 0;
            }
            else { // 一般变量，如int a，结构体内和一般声明均是;
                // printf("%s\n", $1->child->id);
                // tmp.type = (char*)malloc(sizeof($1->child->id));
                strcpy(tmp.type, yyvsp[-2]->child->id);
                if(flgArr) { // 是数组
                    tmp.isarr = 1;
                    tmp.dimension = newnode->child->child->child->bro->bro->intValue;
                    // flgArr = 0;
                }
            }
            // printf("Variable %s has type %s\n", tmp.name, tmp.type);
            tmp.isvariable = 1;
            this_scope = insert(this_scope, tmp);
                
            if(newnode->child->bro != NULL) // 不这么写感觉没办法写循环
                newnode = newnode->child->bro->bro; // 让newnode始终指向DecList
            else break; // 可能为NULL，提前终止，避免报错
        } while(newnode != NULL);

        // flgStruct = 0;
        flgArr = 0;        
    }
#line 1715 "syntax.tab.c"
    break;

  case 6:
#line 174 "syntax.y"
                     {
        yyval = insNode(yyvsp[-1], "ExtDef", (yylsp[-1]).first_line, NON_TERMINAL);
        yyvsp[-1]->bro = yyvsp[0];

        flgStruct = 0;
    }
#line 1726 "syntax.tab.c"
    break;

  case 7:
#line 180 "syntax.y"
                              {
        yyval = insNode(yyvsp[-2], "ExtDef", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];

        MyType tmp = MyType_default;

        strcpy(tmp.name, yyvsp[-1]->child->id);
        tmp.isfunc = 1;
        strcpy(tmp.return_type, Compst_return_type);
        
		strcpy(Compst_return_type, "null");
		// printf("return type: %s\n", tmp.return_type);
        MyType* t = search(this_scope, tmp);
        strcpy(t->return_type, tmp.return_type); // 给上级作用域中的函数声明赋返回值类型
        if(!t->def) t->def = 1;

        struct my_node* mt = my_search(&this_scope->my_root, tmp); // 确认当前的新作用域没有声明
        if(mt) {
            // printf("def %d\n", mt->info.def);
            if(mt->info.def) {
                errors++;
                printf("Error %d at line %d : Redefined function \'%s\'\n", REDEFINED_FUNCTION, last_row, tmp.name);
            }
            else {
                mt->info.def = 1;
                // printf("没啥\n");
            }
        }
		else {
            tmp.isfunc = 1;
            tmp.def = 1;
            if(yyvsp[-1]->child->bro->bro->bro) { // 说明 FunDec -> ID LP VarList RP
                struct node* n = yyvsp[-1]->child->bro->bro; // n始终指向VarList
                char varifunc[12] = {"00_varifunc"};
                do {
                    MyType t = MyType_default;
                    t.def = 1;
                    t.isvariable = 1;
                    
                    if(!strcmp(n->child->child->child->name, "StructSpecifier")) {
                        flgStruct = 2;
                    }
                    if(!flgStruct) {
                        strcpy(t.type, n->child->child->child->id);
                    }
                    else {
                        strcpy(t.type, n->child->child->child->child->bro->child->id);
                    }

                    if(flgArr) {
                        struct node* newnode = n->child->child->bro; // newnode始终指向VarDec
                        // printf("%s\n", newnode->name);
                        while(!strcmp(newnode->name, "VarDec")) {
                            newnode = newnode->child;
                            // printf("name: %s\n", newnode->name);
                        }
                        strcpy(t.name, newnode->id);
                        t.isarr = 1;
                        t.dimension = n->child->child->bro->child->bro->bro->intValue;
                        // printf("array: %s[%d]\n", t.name, t.dimension);
                    }
                    else {
                        strcpy(t.name, n->child->child->bro->child->id);
                    }
                    int result = my_insert(&tmp.varilist, t);
                    
                    t = MyType_default;
                    if(!flgStruct) {
                        strcpy(t.type, n->child->child->child->id);
                    }
                    else {
                        strcpy(t.type, n->child->child->child->child->bro->child->id);
                        flgStruct = 0;
                    }
                    strcpy(t.name, varifunc);
                    varifunc[1] += 1;
                    if(varifunc[1] > '9'){
                        varifunc[0] += 1;
                        varifunc[1] = '0';
                    }
                    result = my_insert(&tmp.varilist, t);

                    if(n->child->bro) {
                        n = n->child->bro->bro;
                    }
                    else break;
                } while(n);
                
            }
            else {
                // printf("没啥\n");
            }
            // this_scope = insert(this_scope, tmp);
            // my_insert(&this_scope->last->my_root, tmp);
        }
		// jcy 8
        flgStruct = 0;
        free(variList);
        variList = (VariLink)malloc(sizeof(VariLink));
        this_scope = pop_scope(this_scope);
    }
#line 1833 "syntax.tab.c"
    break;

  case 8:
#line 282 "syntax.y"
                            {			//不会出现在中间代码生成中
        yyval = insNode(yyvsp[-2], "ExtDef", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];

        MyType tmp = MyType_default;
        tmp.def = 0; // 只是声明，尚未定义
        strcpy(tmp.name, yyvsp[-1]->child->id);
        tmp.isfunc = 1;
        strcpy(tmp.return_type, yyvsp[-2]->child->id);
        if(search(this_scope, tmp)) {
            errors++;
            printf("Error %d at line %d : Incompleted definition of function \'%s\'\n", AMBIGUOUS_FUNCTION_DECLARATION, last_row, tmp.name);
        }
		else {
            tmp.isfunc = 1;
            tmp.dimension = last_row; // 借用存一下函数所在行数
            // tmp.def = 1;
            if(yyvsp[-1]->child->bro->bro->bro) { // 说明 FunDec -> ID LP VarList RP
                struct node* n = yyvsp[-1]->child->bro->bro; // n始终指向VarList
                char varifunc[12] = {"00_varifunc"};
                do {
                    MyType t = MyType_default;
                    t.def = 1;
                    t.isvariable = 1;
                    strcpy(t.type, n->child->child->child->id);
                    strcpy(t.name, n->child->child->bro->child->id);
                    int result = my_insert(&tmp.varilist, t);

                    t = MyType_default;
                    strcpy(t.type, n->child->child->child->id);
                    strcpy(t.name, varifunc);
                    varifunc[1] += 1;
                    if(varifunc[1] > '9'){
                        varifunc[0] += 1;
                        varifunc[1] = '0';
                    }
                    result = my_insert(&tmp.varilist, t);

                    if(n->child->bro) {
                        n = n->child->bro->bro;
                    }
                    else break;
                } while(n);
                
            }
            else {
                // printf("没啥\n");
            }
            // this_scope = insert(this_scope, tmp);
            // my_insert(&this_scope->last->my_root, tmp);
            // printf("%s\n", tmp.name);
            strcpy(func_list[func_cnt], tmp.name);
            func_cnt++;
        }
    }
#line 1894 "syntax.tab.c"
    break;

  case 9:
#line 340 "syntax.y"
                    {
        yyval = insNode(yyvsp[0], "ExtDecList", (yylsp[0]).first_line, NON_TERMINAL);
    }
#line 1902 "syntax.tab.c"
    break;

  case 10:
#line 343 "syntax.y"
                              {
        yyval = insNode(yyvsp[-2], "ExtDecList", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 1912 "syntax.tab.c"
    break;

  case 11:
#line 355 "syntax.y"
                 {
        yyval = insNode(yyvsp[0], "Specifier", (yylsp[0]).first_line, NON_TERMINAL);

        // printf("return_type: %s\n", $1->id);
        if(!CompstCNT) {
            if(!strcmp(yyvsp[0]->id, "int")) { // $2->child->type == INT_TYPE
                strcpy(Compst_return_type, "int");
            }
            else if(!strcmp(yyvsp[0]->id, "float")) { // $2->child->type == FLOAT_TYPE
                strcpy(Compst_return_type, "float");
            }
            else if(yyvsp[0]->type == STRING_TYPE) {
                strcpy(Compst_return_type, yyvsp[0]->id);
            }
        }
    }
#line 1933 "syntax.tab.c"
    break;

  case 12:
#line 371 "syntax.y"
                      {
        yyval = insNode(yyvsp[0], "Specifier", (yylsp[0]).first_line, NON_TERMINAL);
    }
#line 1941 "syntax.tab.c"
    break;

  case 13:
#line 378 "syntax.y"
                                          {
// StructSpecifier : STRUCT OptTag LC DefList RC {
        yyval = insNode(yyvsp[-4], "StructSpecifier", (yylsp[-4]).first_line, NON_TERMINAL);
        yyvsp[-4]->bro = yyvsp[-3];
        yyvsp[-3]->bro = yyvsp[-2];
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];

        MyType tmp = MyType_default;
        
        strcpy(tmp.name, yyvsp[-3]->child->id);
        strcpy(tmp.type, yyvsp[-4]->id);
        // printf("%s is named %s\n", tmp.type, tmp.name);
        if(search(this_scope, tmp)) { // 结构体名字重复
            errors++;
            printf("Error %d at line %d : Duplicate name \'%s\'\n", REDEFINED_STRUCT, last_row, tmp.name);
        }
        else {
            tmp.def = 1;
            tmp.isstruct = 1;
            // printf("%s\n", tmp.name);
            struct node* newnode = yyvsp[-1]; // newnode保持指向Mid
            
            char VariStruct[12] = {"00_varistct"};
            do {
                MyType temp = MyType_default;
                temp.def = 1;
                temp.isvariable = 1;

                strcpy(temp.type, newnode->child->child->child->id);

                struct node* newnew = newnode->child->child->bro; // newnew保持指向DecList
                do {
                    strcpy(temp.name, newnew->child->child->child->id);

                    int result = my_insert(&tmp.varilist, temp);
                    // printf("Whether successful: %d\n", result);
                    strcpy(temp.name, VariStruct);
                    result = my_insert(&tmp.varilist, temp);
                    VariStruct[1] += 1;
                    if(VariStruct[1] > '9'){
                        VariStruct[0] += 1;
                        VariStruct[1] = '0';
                    }

                    if(newnew->child->bro != NULL) {
                        newnew = newnew->child->bro->bro;
                    }
                    else break;
                } while(newnew != NULL);
                // printf("newnode->child->bro: %s\n", newnode->child->bro->name);
                if(newnode->child) { // strcmp(newnode->child->bro->name, "Mid") == 0
                    newnode = newnode->child->bro;
                }
                else break;
            } while(newnode->child);

            this_scope = insert(this_scope, tmp); // 插入当前作用域
            // printf("struct name %s of type %s, %d\n", tmp.name, tmp.type, tmp.isarr);
            int result = my_insert(&this_scope->last->my_root, tmp); // 插入上一级作用域
            // 这里是为了pop结构体的子作用域时不会扔掉结构体这个结点
            tmp.def = 0;
            tmp.isstruct = 0;
        }

        this_scope = pop_scope(this_scope);
    }
#line 2013 "syntax.tab.c"
    break;

  case 14:
#line 445 "syntax.y"
                 {
        yyval = insNode(yyvsp[-1], "StructSpecifier", (yylsp[-1]).first_line, NON_TERMINAL);
        yyvsp[-1]->bro = yyvsp[0];

        MyType tmp = MyType_default;
        strcpy(tmp.name, yyvsp[0]->child->id);
        // printf("Scope: %d\n", this_scope->top);
        if(!search(this_scope, tmp)) {
            errors++;
            printf("Error %d at line %d : Undefined struct \'%s\'\n", UNDEFINED_STRUCT, last_row, tmp.name);
        }
        else {
            tmp.def = 1;
            tmp.isstruct = 1;
            strcpy(tmp.type, yyvsp[0]->child->id);
            // this_scope = insert(this_scope, tmp);
        }
        flgStruct = 2;
    }
#line 2037 "syntax.tab.c"
    break;

  case 15:
#line 466 "syntax.y"
            {
        yyval = insNode(yyvsp[0], "OptTag", (yylsp[0]).first_line, NON_TERMINAL);
    }
#line 2045 "syntax.tab.c"
    break;

  case 16:
#line 469 "syntax.y"
      {
        yyval = insNode(NULL, "OptTag", yylineno, NON_TERMINAL);
    }
#line 2053 "syntax.tab.c"
    break;

  case 17:
#line 474 "syntax.y"
         {
        yyval = insNode(yyvsp[0], "Tag", (yylsp[0]).first_line, NON_TERMINAL);
    }
#line 2061 "syntax.tab.c"
    break;

  case 18:
#line 479 "syntax.y"
                          {
    
        yyval = insNode(yyvsp[-3], "FunDec", (yylsp[-3]).first_line, NON_TERMINAL);
        yyvsp[-3]->bro = yyvsp[-2];
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
       
        // print(this_scope);
        MyType temp = MyType_default;
        variList = (VariLink)malloc(sizeof(VariLink));
        struct node* newnode = yyvsp[-1]; // newnode始终指向VarList
        char varifunc[12] = {"00_varifunc"};
        do {
            MyType tmp = MyType_default;
            tmp.def = 1;
            tmp.isvariable = 1;

            if(flgArr) {
                tmp.isarr = 1;
                struct node* n = newnode->child->child->bro; // n始终指向VarDec
                while(!strcmp(n->name, "VarDec")) {
                    n = n->child;
                }
                strcpy(tmp.name, n->id);
                tmp.isarr = 1;
                tmp.dimension = newnode->child->child->bro->child->bro->bro->intValue;
            }
            else {
                strcpy(tmp.name, newnode->child->child->bro->child->id);
            }

            if(flgStruct) {
                tmp.isstruct = 1;
                strcpy(tmp.type, newnode->child->child->child->child->bro->child->id);
            }
            else {
                strcpy(tmp.type, newnode->child->child->child->id);
            }

            int result = my_insert(&variList->my_root, tmp);
            my_insert(&temp.varilist, tmp);

            tmp = MyType_default;
            tmp.isvariable = 1;
            if(flgStruct) {
                strcpy(tmp.type, newnode->child->child->child->child->bro->child->id);
                flgStruct = 0;
            }
            else {
                strcpy(tmp.type, newnode->child->child->child->id);
            }
            strcpy(tmp.name, varifunc);
            varifunc[1] += 1;
            if(varifunc[1] > '9') {
                varifunc[0] += 1;
                varifunc[1] = '0';
            }
            my_insert(&temp.varilist, tmp);

            if(newnode->child->bro) {
                newnode = newnode->child->bro->bro;
            }
            else break;
        } while(newnode);
        temp.isfunc = 1;
        strcpy(temp.name, yyvsp[-3]->id);
        MyType* mt = search(this_scope, temp);
        if(mt) {
            if(mt->def) { // 被实现过
                errors++;
                printf("Error %d at line %d : Redefined function \'%s\'\n", REDEFINED_FUNCTION, last_row, temp.name);
            }
            else { // 未被实现过
                mt->def = 1;
                // printf("没啥\n");
            }
        } // waiting
        this_scope = insert(this_scope, temp);
    }
#line 2145 "syntax.tab.c"
    break;

  case 19:
#line 558 "syntax.y"
               {
        yyval = insNode(yyvsp[-2], "FunDec", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];

        MyType temp = MyType_default;
        temp.isfunc = 1;
        strcpy(temp.name, yyvsp[-2]->id);
        MyType* mt = search(this_scope, temp);
        if(mt) {
            if(mt->def) { // 被实现过
                errors++;
                printf("Error %d at line %d : Redefined function \'%s\'\n", REDEFINED_FUNCTION, last_row, temp.name);
            }
            else { // 未被实现过
                mt->def = 1;
                // printf("没啥\n");
            }
        } // waiting
        this_scope = insert(this_scope, temp);
    }
#line 2171 "syntax.tab.c"
    break;

  case 20:
#line 579 "syntax.y"
                         {
		char msg[100];
		sprintf(msg, "VarList.");
		myerror(msg);
	}
#line 2181 "syntax.tab.c"
    break;

  case 21:
#line 586 "syntax.y"
                                 {
        yyval = insNode(yyvsp[-2], "VarList", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2191 "syntax.tab.c"
    break;

  case 22:
#line 591 "syntax.y"
               {
        yyval = insNode(yyvsp[0], "VarList", (yylsp[0]).first_line, NON_TERMINAL);
    }
#line 2199 "syntax.tab.c"
    break;

  case 23:
#line 596 "syntax.y"
                            {
        yyval = insNode(yyvsp[-1], "ParamDec", (yylsp[-1]).first_line, NON_TERMINAL);
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2208 "syntax.tab.c"
    break;

  case 24:
#line 613 "syntax.y"
                   {
        yyval = insNode(yyvsp[-2], "CompSt", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2218 "syntax.tab.c"
    break;

  case 25:
#line 621 "syntax.y"
              {
        yyval = insNode(yyvsp[-1], "Mid", (yylsp[-1]).first_line, NON_TERMINAL);
        yyvsp[-1]->bro = yyvsp[0];
	}
#line 2227 "syntax.tab.c"
    break;

  case 26:
#line 625 "syntax.y"
                   {
        yyval = insNode(yyvsp[-1], "Mid", (yylsp[-1]).first_line, NON_TERMINAL);
        yyvsp[-1]->bro = yyvsp[0];
	}
#line 2236 "syntax.tab.c"
    break;

  case 27:
#line 629 "syntax.y"
          {
        yyval = insNode(NULL, "Mid", yylineno, NON_TERMINAL);
	}
#line 2244 "syntax.tab.c"
    break;

  case 28:
#line 649 "syntax.y"
                             {
        yyval = insNode(yyvsp[-2], "Def", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];

        struct node* newnode = yyvsp[-1]; // newnode始终指向DecList
            
        do {
            MyType tmp = MyType_default;
            tmp.def = 1;
            
            if(!flgArr) { // 不是数组
                strcpy(tmp.name, newnode->child->child->child->id);
            }
            else { // 是数组
                struct node* n = newnode->child->child->child->child;
                while(!strcmp(n->name, "VarDec")) {
                    n = n->child;
                    // printf("name: %s\n", n->name);
                }
                strcpy(tmp.name, n->id);
            }

            if(my_search(&this_scope->my_root, tmp) || my_search(&variList->my_root, tmp)) { // 两种可能：struct xx {...} yy; 或 int a;
                char msg[100];
                if(!flgStruct)  {// 普通变量声明
                    errors++;
                    printf("Error %d at line %d : Redefined variable \'%s\'\n", REDEFINED_VARIABLE, last_row, tmp.name);
                }
                else {// 结构体变量声明
                    errors++;
                    printf("Error %d at line %d : Redefined field \'%s\'\n", REDEFINED_FIELD, last_row, tmp.name);
                }
                // myerror(msg);
            }
            else {
                if(flgStruct == 2) { // 是struct tag的情况，如struct sa nn;
                    strcpy(tmp.type, yyvsp[-2]->child->child->bro->child->id);
                    tmp.isstruct = 1;
                    flgStruct = 0;
                }
                // else if(flgStruct == 1) {

                // }
                else { // 一般变量，如int a，结构体内和一般声明均是;
                    // tmp.type = (char*)malloc(sizeof($1->child->id));
                    
                    strcpy(tmp.type, yyvsp[-2]->child->id);
                    if(flgArr) { // 是数组
                        tmp.isarr = 1;
                        tmp.dimension = newnode->child->child->child->bro->bro->intValue;
                        // flgArr = 0;
                    }
                    if(newnode->child->child->bro) {
                        if(!strcmp(newnode->child->child->bro->bro->child->name, "ID")) {
                            MyType t1 = MyType_default;
                            strcpy(t1.name, newnode->child->child->bro->bro->child->id);
                            MyType* t2 = search(this_scope, t1);
                            if(strcmp(t2->type, yyvsp[-2]->child->id)) {
                                errors++;
                                printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                            }
                        }
                        else if(!strcmp(newnode->child->child->bro->bro->child->name, "INT")) {
                            if(strcmp("int", yyvsp[-2]->child->id)) {
                                errors++;
                                printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                            }
                        }
                        else if(!strcmp(newnode->child->child->bro->bro->child->name, "FLOAT")) {
                            if(strcmp("float", yyvsp[-2]->child->id)) {
                                errors++;
                                printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                            }
                        }
                    }
                }
                tmp.isvariable = 1;
                this_scope = insert(this_scope, tmp);
                // print(this_scope);
            }
                
            if(newnode->child->bro) // 不这么写感觉没办法写循环
                newnode = newnode->child->bro->bro; // 让newnode始终指向DecList
            else break; // 可能为NULL，提前终止，避免报错
        } while(newnode);
        
        // print(this_scope);

        // flgStruct = 0;
        flgArr = 0;        
    }
#line 2341 "syntax.tab.c"
    break;

  case 29:
#line 741 "syntax.y"
                                 {
		char msg[100];
		sprintf(msg, "error: Missing \";\"");	//necessary
		myerror(msg);
	}
#line 2351 "syntax.tab.c"
    break;

  case 30:
#line 746 "syntax.y"
                         {
    	char msg[100];
		sprintf(msg, "Syntax error.");
		myerror(msg);
    }
#line 2361 "syntax.tab.c"
    break;

  case 31:
#line 751 "syntax.y"
                               {
		char msg[100];
		sprintf(msg, "Syntax error.");
		myerror(msg);
	}
#line 2371 "syntax.tab.c"
    break;

  case 32:
#line 760 "syntax.y"
             {
        yyval = insNode(yyvsp[-1], "Stmt", (yylsp[-1]).first_line, NON_TERMINAL);
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2380 "syntax.tab.c"
    break;

  case 33:
#line 764 "syntax.y"
                {
		char msg[100];
		sprintf(msg, "error: Missing \";\"");
		myerror(msg);
	}
#line 2390 "syntax.tab.c"
    break;

  case 34:
#line 769 "syntax.y"
             {
        yyval = insNode(yyvsp[0], "Stmt", (yylsp[0]).first_line, NON_TERMINAL);
    }
#line 2398 "syntax.tab.c"
    break;

  case 35:
#line 772 "syntax.y"
                      {
        yyval = insNode(yyvsp[-2], "Stmt", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];

        if(strcmp(Compst_return_type, yyvsp[-1]->property)) {
            errors++;
            printf("Error %d at line %d : Type mismatched for return\n", TYPE_MISMATCH_RETURN, last_row);
        }
    }
#line 2413 "syntax.tab.c"
    break;

  case 36:
#line 782 "syntax.y"
                                              {
        yyval = insNode(yyvsp[-4], "Stmt", (yylsp[-4]).first_line, NON_TERMINAL);
        yyvsp[-4]->bro = yyvsp[-3];
        yyvsp[-3]->bro = yyvsp[-2];
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2425 "syntax.tab.c"
    break;

  case 37:
#line 789 "syntax.y"
                                  {
        yyval = insNode(yyvsp[-6], "Stmt", (yylsp[-6]).first_line, NON_TERMINAL);
        yyvsp[-6]->bro = yyvsp[-5];
        yyvsp[-5]->bro = yyvsp[-4];
        yyvsp[-4]->bro = yyvsp[-3];
        yyvsp[-3]->bro = yyvsp[-2];
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2439 "syntax.tab.c"
    break;

  case 38:
#line 798 "syntax.y"
                           {
        yyval = insNode(yyvsp[-4], "Stmt", (yylsp[-4]).first_line, NON_TERMINAL);
        yyvsp[-4]->bro = yyvsp[-3];
        yyvsp[-3]->bro = yyvsp[-2];
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2451 "syntax.tab.c"
    break;

  case 39:
#line 816 "syntax.y"
              {
        yyval = insNode(yyvsp[0], "DecList", (yylsp[0]).first_line, NON_TERMINAL);
    }
#line 2459 "syntax.tab.c"
    break;

  case 40:
#line 819 "syntax.y"
                        {
        yyval = insNode(yyvsp[-2], "DecList", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2469 "syntax.tab.c"
    break;

  case 41:
#line 826 "syntax.y"
             {
        yyval = insNode(yyvsp[0], "Dec", (yylsp[0]).first_line, NON_TERMINAL);
        Regcnt++;
        if(!strcmp(head->child->name, "ID")) {
            strcpy(VarReg[Regcnt-1], head->child->id);
        }
    }
#line 2481 "syntax.tab.c"
    break;

  case 42:
#line 833 "syntax.y"
                          {
        yyval = insNode(yyvsp[-2], "Dec", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
        Regcnt++;
        if(!strcmp(head->child->name, "ID")) {
            strcpy(VarReg[Regcnt-1], head->child->id);
        }
    }
#line 2495 "syntax.tab.c"
    break;

  case 43:
#line 844 "syntax.y"
            {
        yyval = insNode(yyvsp[0], "VarDec", (yylsp[0]).first_line, NON_TERMINAL);
    }
#line 2503 "syntax.tab.c"
    break;

  case 44:
#line 847 "syntax.y"
                       {
        yyval = insNode(yyvsp[-3], "VarDec", (yylsp[-3]).first_line, NON_TERMINAL);
        yyvsp[-3]->bro = yyvsp[-2];
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2514 "syntax.tab.c"
    break;

  case 45:
#line 853 "syntax.y"
                      {
        yyval = insNode(yyvsp[-3], "VarDec", (yylsp[-3]).first_line, NON_TERMINAL);
        yyvsp[-3]->bro = yyvsp[-2];
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2525 "syntax.tab.c"
    break;

  case 46:
#line 859 "syntax.y"
                         {
        char msg[100];
        sprintf(msg, "Missing \"]\".");
		myerror(msg);
    }
#line 2535 "syntax.tab.c"
    break;

  case 47:
#line 864 "syntax.y"
                            {
		char msg[100];
		sprintf(msg, "int.");
		myerror(msg);
	}
#line 2545 "syntax.tab.c"
    break;

  case 48:
#line 871 "syntax.y"
                       {
        yyval = insNode(yyvsp[-2], "Exp", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];

        // printf("%s vs %s\n", $1->property, $3->property);
        if(yyvsp[-2]->property[0] == '\0' || yyvsp[0]->property[0] == '\0') {
            errors++;
            printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row); 
        }
        else if(!strcmp(yyvsp[0]->property, "read") || !strcmp(yyvsp[0]->property, "write")) {
            // nothing...
        }
        else if(yyvsp[-2]->child->type != STRING_TYPE && yyvsp[-2]->child->type != NON_TERMINAL) {
            errors++;
            printf("Error %d at line %d : The left-hand side of assignment must be a variable\n", NEED_VARIABLE, last_row); 
        }
        else if(!strcmp(yyvsp[-2]->property, yyvsp[0]->property)) {
            strcpy(yyval->property, yyvsp[-2]->property);
        }
        else if(yyvsp[-2]->child->type == NON_TERMINAL) { // 说明可能是数组
            MyType t1 = MyType_default;
            struct node* n = yyvsp[-2]->child->child;
            while(!strcmp(n->name, "Exp")) {
                n = n->child;
            }
            strcpy(t1.name, n->id);

            MyType *t2 = search(this_scope, t1);
            if(t2) {
                if(!strcmp(yyvsp[0]->child->name, "ID")) { // $3->child->type == STRING_TYPE
                    MyType t3 = MyType_default;
                    strcpy(t3.name, yyvsp[0]->child->id);
                    MyType* t4 = search(this_scope, t3);
                    if(t4) {
                        if(t4->isfunc) {
                            if(strcmp(t2->type, t4->return_type)) {
                                errors++;
                                printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row);
                            }
                        }
                        else {
                            if(strcmp(t2->type, t4->type)) {
                                errors++;
                                printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                            }
                        }
                    }
                }
                else if(!strcmp(yyvsp[0]->child->name, "FLOAT")) {
                    if(strcmp(t2->type, "float")) {
                        errors++;
                        printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                    }
                }
                else if(!strcmp(yyvsp[0]->child->name, "INT")) {
                    if(strcmp(t2->type, "int")) {
                        errors++;
                        printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                    }
                }
            }
        }
        else {
            MyType t1 = MyType_default;
            strcpy(t1.name, yyvsp[-2]->child->id);
            MyType *t2 = search(this_scope, t1);
            if(!t2) {
                t2 = &(my_search(&variList->my_root, t1))->info;
            }
            if(t2) {
                if(!strcmp(yyvsp[0]->child->name, "ID")) { // $3->child->type == STRING_TYPE
                    MyType t3 = MyType_default;
                    strcpy(t3.name, yyvsp[0]->child->id);
                    MyType* t4 = search(this_scope, t3);
                    if(t4) {
                        int right = 1;
                        MyType tmp = MyType_default;
                        strcpy(tmp.name, t2->type);
                        Mylink s1 = search(this_scope, tmp);

                        strcpy(tmp.name, t4->type);
                        Mylink s2 = search(this_scope, tmp);
                        if(s1 && s2 && s1->def && s2->def){   // 先判断这俩结构体是否定义过
                            char VariStruct[12] = {"00_varistct"};
                            strcpy(tmp.name, VariStruct);
                            struct my_node* Varis1 = my_search(&(s1->varilist), tmp);
                            struct my_node* Varis2 = my_search(&(s2->varilist), tmp);

                            while(Varis1 || Varis2) {
                                if(Varis1 == NULL||Varis2==NULL){
                                    right = 0;
                                }
                                else if(strcmp(Varis1->info.type, Varis2->info.type)){
                                    right = 0;
                                }
                                VariStruct[1] += 1;
                                if(VariStruct[1] > '9'){
                                    VariStruct[0] += 1;
                                    VariStruct[1] = '0';
                                }
                                strcpy(tmp.name, VariStruct);
                                Varis1 = my_search(&(s1->varilist), tmp);
                                Varis2 = my_search(&(s2->varilist), tmp);
                            }
                        }
                        else right = 0;  // 还是感觉应该写未定义
                        if(right == 0){
                            printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row);
                            errors ++;
                        }
                    }
                }
                else if(!strcmp(yyvsp[0]->child->name, "FLOAT")) {
                    if(strcmp(t2->type, "float")) {
                        errors++;
                        printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                    }
                }
                else if(!strcmp(yyvsp[0]->child->name, "INT")) {
                    if(strcmp(t2->type, "int")) {
                        errors++;
                        printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                    }
                }
            }
        }
    }
#line 2678 "syntax.tab.c"
    break;

  case 49:
#line 999 "syntax.y"
                             { 
		char msg[100];
        sprintf(msg, "Syntax error."); // ASSIGNOP not in front of Exp
		myerror(msg);
	}
#line 2688 "syntax.tab.c"
    break;

  case 50:
#line 1004 "syntax.y"
                  {
        yyval = insNode(yyvsp[-2], "Exp", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];

        char num1[20] = {0};
        MyType t1 = MyType_default;
        MyType* t2;
        // printf("%s vs %s\n", $1->property, $3->property);
        
        if(strcmp(yyvsp[-2]->child->name, "ID")) { // $1->child->type != STRING_TYPE
            if(!strcmp(yyvsp[-2]->child->name, "INT")) {
                sprintf(num1, "%d", yyvsp[-2]->child->intValue);
            }
            else if(!strcmp(yyvsp[-2]->child->name, "FLOAT")) {
                sprintf(num1, "%f", yyvsp[-2]->child->floatValue);
            }
            
            strcpy(t1.name, num1);
        }
        else if(!strcmp(yyvsp[-2]->child->name, "ID")) {
            strcpy(t1.name, yyvsp[-2]->child->id);
        }

        if(!strcmp(yyvsp[-2]->property, yyvsp[0]->property)) {
            strcpy(yyval->property, yyvsp[-2]->property);
        }
        else if(strcmp(t1.name, "") && strcmp(yyvsp[-2]->property, yyvsp[0]->property)) {
            t2 = search(this_scope, t1);
            if(!t2) {
                t2 = &my_search(&variList->my_root, t1)->info;
            }

            if(t2) {
                char num2[20] = {0};
                MyType t3 = MyType_default;
                MyType* t4;
                
                if(strcmp(yyvsp[0]->child->name, "ID")) {
                    if(!strcmp(yyvsp[0]->child->name, "INT")) {
                        sprintf(num2, "%d", yyvsp[0]->child->intValue);
                        if(strcmp(t2->type, "int")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            strcpy(yyval->property, "int");
                        }
                    }
                    else if(!strcmp(yyvsp[0]->child->name, "FLOAT")) {
                        sprintf(num2, "%f", yyvsp[0]->child->floatValue);
                        if(strcmp(t2->type, "float")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            strcpy(yyval->property, "float");
                        }
                    }
                }
                else {
                    strcpy(t3.name, yyvsp[0]->child->id);
                    t4 = search(this_scope, t3);
                    if(t4) {
                        if(strcmp(t2->type, t4->type)) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            strcpy(yyval->property, yyvsp[-2]->property);
                        }
                    }
                    else if(yyvsp[-2]->type != yyvsp[0]->type) {
                        errors++;
                        printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                    }
                    else {
                        strcpy(yyval->property, yyvsp[-2]->property);
                    }
                }
            }
            
        }
    }
#line 2777 "syntax.tab.c"
    break;

  case 51:
#line 1088 "syntax.y"
                 {
        yyval = insNode(yyvsp[-2], "Exp", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];

        char num1[20] = {0};
        MyType t1 = MyType_default;
        MyType* t2;
        // printf("%s vs %s\n", $1->property, $3->property);
        
        if(strcmp(yyvsp[-2]->child->name, "ID")) { // $1->child->type != STRING_TYPE
            if(!strcmp(yyvsp[-2]->child->name, "INT")) {
                sprintf(num1, "%d", yyvsp[-2]->child->intValue);
            }
            else if(!strcmp(yyvsp[-2]->child->name, "FLOAT")) {
                sprintf(num1, "%f", yyvsp[-2]->child->floatValue);
            }
            
            strcpy(t1.name, num1);
        }
        else if(!strcmp(yyvsp[-2]->child->name, "ID")) {
            strcpy(t1.name, yyvsp[-2]->child->id);
        }

        if(!strcmp(yyvsp[-2]->property, yyvsp[0]->property)) {
            strcpy(yyval->property, yyvsp[-2]->property);
        }
        else if(strcmp(t1.name, "") && strcmp(yyvsp[-2]->property, yyvsp[0]->property)) {
            t2 = search(this_scope, t1);
            if(!t2) {
                t2 = &my_search(&variList->my_root, t1)->info;
            }

            if(t2) {
                char num2[20] = {0};
                MyType t3 = MyType_default;
                MyType* t4;
                
                if(strcmp(yyvsp[0]->child->name, "ID")) {
                    if(!strcmp(yyvsp[0]->child->name, "INT")) {
                        sprintf(num2, "%d", yyvsp[0]->child->intValue);
                        if(strcmp(t2->type, "int")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            strcpy(yyval->property, "int");
                        }
                    }
                    else if(!strcmp(yyvsp[0]->child->name, "FLOAT")) {
                        sprintf(num2, "%f", yyvsp[0]->child->floatValue);
                        if(strcmp(t2->type, "float")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            strcpy(yyval->property, "float");
                        }
                    }
                }
                else {
                    strcpy(t3.name, yyvsp[0]->child->id);
                    t4 = search(this_scope, t3);
                    if(t4) {
                        if(strcmp(t2->type, t4->type)) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = $1->type;
                            strcpy(yyval->property, yyvsp[-2]->property);
                        }
                    }
                    else if(yyvsp[-2]->type != yyvsp[0]->type) {
                        errors++;
                        printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                    }
                    else {
                        // $$->type = $1->type;
                        strcpy(yyval->property, yyvsp[-2]->property);
                    }
                }
            }
            
        }
    }
#line 2868 "syntax.tab.c"
    break;

  case 52:
#line 1174 "syntax.y"
                    {
        yyval = insNode(yyvsp[-2], "Exp", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];

        Regcnt++;
        char num1[20] = {0};
        MyType t1 = MyType_default;
        MyType* t2;
        // printf("%s vs %s\n", $1->property, $3->property);
        
        if(strcmp(yyvsp[-2]->child->name, "ID")) { // $1->child->type != STRING_TYPE
            if(!strcmp(yyvsp[-2]->child->name, "INT")) {
                sprintf(num1, "%d", yyvsp[-2]->child->intValue);
            }
            else if(!strcmp(yyvsp[-2]->child->name, "FLOAT")) {
                sprintf(num1, "%f", yyvsp[-2]->child->floatValue);
            }
            
            strcpy(t1.name, num1);
        }
        else if(!strcmp(yyvsp[-2]->child->name, "ID")) {
            strcpy(t1.name, yyvsp[-2]->child->id);
        }

        if(!strcmp(yyvsp[-2]->property, yyvsp[0]->property)) {
            strcpy(yyval->property, yyvsp[-2]->property);
        }
        else if(strcmp(t1.name, "") && strcmp(yyvsp[-2]->property, yyvsp[0]->property)) {
            t2 = search(this_scope, t1);
            if(!t2) {
                t2 = &my_search(&variList->my_root, t1)->info;
            }

            if(t2) {
                char num2[20] = {0};
                MyType t3 = MyType_default;
                MyType* t4;
                
                if(strcmp(yyvsp[0]->child->name, "ID")) {
                    if(!strcmp(yyvsp[0]->child->name, "INT")) {
                        sprintf(num2, "%d", yyvsp[0]->child->intValue);
                        if(strcmp(t2->type, "int")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = 1;
                            strcpy(yyval->property, "int");
                        }
                    }
                    else if(!strcmp(yyvsp[0]->child->name, "FLOAT")) {
                        sprintf(num2, "%f", yyvsp[0]->child->floatValue);
                        if(strcmp(t2->type, "float")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = 2;
                            strcpy(yyval->property, "float");
                        }
                    }
                }
                else {
                    // printf("id: %s\n" $3->child->id);
                    // print(this_scope);,
                    strcpy(t3.name, yyvsp[0]->child->id);
                    t4 = search(this_scope, t3);
                    if(t4) {
                        if(strcmp(t2->type, t4->type)) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = $1->type;
                            strcpy(yyval->property, yyvsp[-2]->property);
                        }
                    }
                    else if(yyvsp[-2]->type != yyvsp[0]->type) {
                        errors++;
                        printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                    }
                    else {
                        // $$->type = $1->type;
                        strcpy(yyval->property, yyvsp[-2]->property);
                    }
                }
            }
            
        }
    }
#line 2964 "syntax.tab.c"
    break;

  case 53:
#line 1265 "syntax.y"
                   {
        yyval = insNode(yyvsp[-2], "Exp", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];

        char num1[20] = {0};
        MyType t1 = MyType_default;
        MyType* t2;
        // printf("%s vs %s\n", $1->property, $3->property);
        
        if(strcmp(yyvsp[-2]->child->name, "ID")) { // $1->child->type != STRING_TYPE
            if(!strcmp(yyvsp[-2]->child->name, "INT")) {
                sprintf(num1, "%d", yyvsp[-2]->child->intValue);
            }
            else if(!strcmp(yyvsp[-2]->child->name, "FLOAT")) {
                sprintf(num1, "%f", yyvsp[-2]->child->floatValue);
            }
            
            strcpy(t1.name, num1);
        }
        else if(!strcmp(yyvsp[-2]->child->name, "ID")) {
            strcpy(t1.name, yyvsp[-2]->child->id);
        }

        if(!strcmp(yyvsp[-2]->property, yyvsp[0]->property)) {
            strcpy(yyval->property, yyvsp[-2]->property);
        }
        else if(strcmp(t1.name, "") && strcmp(yyvsp[-2]->property, yyvsp[0]->property)) {
            t2 = search(this_scope, t1);
            if(!t2) {
                t2 = &my_search(&variList->my_root, t1)->info;
            }

            if(t2) {
                char num2[20] = {0};
                MyType t3 = MyType_default;
                MyType* t4;
                
                if(strcmp(yyvsp[0]->child->name, "ID")) {
                    if(!strcmp(yyvsp[0]->child->name, "INT")) {
                        sprintf(num2, "%d", yyvsp[0]->child->intValue);
                        if(strcmp(t2->type, "int")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = 1;
                            strcpy(yyval->property, "int");
                        }
                    }
                    else if(!strcmp(yyvsp[0]->child->name, "FLOAT")) {
                        sprintf(num2, "%f", yyvsp[0]->child->floatValue);
                        if(strcmp(t2->type, "float")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = 2;
                            strcpy(yyval->property, "float");
                        }
                    }
                }
                else {
                    // printf("id: %s\n" $3->child->id);
                    // print(this_scope);,
                    strcpy(t3.name, yyvsp[0]->child->id);
                    t4 = search(this_scope, t3);
                    if(t4) {
                        if(strcmp(t2->type, t4->type)) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = $1->type;
                            strcpy(yyval->property, yyvsp[-2]->property);
                        }
                    }
                    else if(yyvsp[-2]->type != yyvsp[0]->type) {
                        errors++;
                        printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                    }
                    else {
                        // $$->type = $1->type;
                        strcpy(yyval->property, yyvsp[-2]->property);
                    }
                }
            }
            
        }
    }
#line 3059 "syntax.tab.c"
    break;

  case 54:
#line 1355 "syntax.y"
                    {
        yyval = insNode(yyvsp[-2], "Exp", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];

        char num1[20] = {0};
        MyType t1 = MyType_default;
        MyType* t2;
        // printf("%s vs %s\n", $1->property, $3->property);
        
        if(strcmp(yyvsp[-2]->child->name, "ID")) { // $1->child->type != STRING_TYPE
            if(!strcmp(yyvsp[-2]->child->name, "INT")) {
                sprintf(num1, "%d", yyvsp[-2]->child->intValue);
            }
            else if(!strcmp(yyvsp[-2]->child->name, "FLOAT")) {
                sprintf(num1, "%f", yyvsp[-2]->child->floatValue);
            }
            
            strcpy(t1.name, num1);
        }
        else if(!strcmp(yyvsp[-2]->child->name, "ID")) {
            strcpy(t1.name, yyvsp[-2]->child->id);
        }

        if(!strcmp(yyvsp[-2]->property, yyvsp[0]->property)) {
            strcpy(yyval->property, yyvsp[-2]->property);
        }
        else if(strcmp(t1.name, "") && strcmp(yyvsp[-2]->property, yyvsp[0]->property)) {
            t2 = search(this_scope, t1);
            if(!t2) {
                t2 = &my_search(&variList->my_root, t1)->info;
            }

            if(t2) {
                char num2[20] = {0};
                MyType t3 = MyType_default;
                MyType* t4;
                
                if(strcmp(yyvsp[0]->child->name, "ID")) {
                    if(!strcmp(yyvsp[0]->child->name, "INT")) {
                        sprintf(num2, "%d", yyvsp[0]->child->intValue);
                        if(strcmp(t2->type, "int")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = 1;
                            strcpy(yyval->property, "int");
                        }
                    }
                    else if(!strcmp(yyvsp[0]->child->name, "FLOAT")) {
                        sprintf(num2, "%f", yyvsp[0]->child->floatValue);
                        if(strcmp(t2->type, "float")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = 2;
                            strcpy(yyval->property, "float");
                        }
                    }
                }
                else {
                    // printf("id: %s\n" $3->child->id);
                    // print(this_scope);,
                    strcpy(t3.name, yyvsp[0]->child->id);
                    t4 = search(this_scope, t3);
                    if(t4) {
                        if(strcmp(t2->type, t4->type)) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = $1->type;
                            strcpy(yyval->property, yyvsp[-2]->property);
                        }
                    }
                    else if(yyvsp[-2]->type != yyvsp[0]->type) {
                        errors++;
                        printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                    }
                    else {
                        // $$->type = $1->type;
                        strcpy(yyval->property, yyvsp[-2]->property);
                    }
                }
            }
            
        }
    }
#line 3154 "syntax.tab.c"
    break;

  case 55:
#line 1445 "syntax.y"
                   {
        yyval = insNode(yyvsp[-2], "Exp", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];

        char num1[20] = {0};
        MyType t1 = MyType_default;
        MyType* t2;
        // printf("%s vs %s\n", $1->property, $3->property);
        
        if(strcmp(yyvsp[-2]->child->name, "ID")) { // $1->child->type != STRING_TYPE
            if(!strcmp(yyvsp[-2]->child->name, "INT")) {
                sprintf(num1, "%d", yyvsp[-2]->child->intValue);
            }
            else if(!strcmp(yyvsp[-2]->child->name, "FLOAT")) {
                sprintf(num1, "%f", yyvsp[-2]->child->floatValue);
            }
            
            strcpy(t1.name, num1);
        }
        else if(!strcmp(yyvsp[-2]->child->name, "ID")) {
            strcpy(t1.name, yyvsp[-2]->child->id);
        }

        if(!strcmp(yyvsp[-2]->property, yyvsp[0]->property)) {
            strcpy(yyval->property, yyvsp[-2]->property);
        }
        else if(strcmp(t1.name, "") && strcmp(yyvsp[-2]->property, yyvsp[0]->property)) {
            t2 = search(this_scope, t1);
            if(!t2) {
                t2 = &my_search(&variList->my_root, t1)->info;
            }

            if(t2) {
                char num2[20] = {0};
                MyType t3 = MyType_default;
                MyType* t4;
                
                if(strcmp(yyvsp[0]->child->name, "ID")) {
                    if(!strcmp(yyvsp[0]->child->name, "INT")) {
                        sprintf(num2, "%d", yyvsp[0]->child->intValue);
                        if(strcmp(t2->type, "int")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = 1;
                            strcpy(yyval->property, "int");
                        }
                    }
                    else if(!strcmp(yyvsp[0]->child->name, "FLOAT")) {
                        sprintf(num2, "%f", yyvsp[0]->child->floatValue);
                        if(strcmp(t2->type, "float")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = 2;
                            strcpy(yyval->property, "float");
                        }
                    }
                }
                else {
                    // printf("id: %s\n" $3->child->id);
                    // print(this_scope);,
                    strcpy(t3.name, yyvsp[0]->child->id);
                    t4 = search(this_scope, t3);
                    if(t4) {
                        if(strcmp(t2->type, t4->type)) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = $1->type;
                            strcpy(yyval->property, yyvsp[-2]->property);
                        }
                    }
                    else if(yyvsp[-2]->type != yyvsp[0]->type) {
                        errors++;
                        printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                    }
                    else {
                        // $$->type = $1->type;
                        strcpy(yyval->property, yyvsp[-2]->property);
                    }
                }
            }
            
        }
    }
#line 3249 "syntax.tab.c"
    break;

  case 56:
#line 1535 "syntax.y"
                  {
        yyval = insNode(yyvsp[-2], "Exp", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];

        char num1[20] = {0};
        MyType t1 = MyType_default;
        MyType* t2;
        // printf("%s vs %s\n", $1->property, $3->property);
        
        if(strcmp(yyvsp[-2]->child->name, "ID")) { // $1->child->type != STRING_TYPE
            if(!strcmp(yyvsp[-2]->child->name, "INT")) {
                sprintf(num1, "%d", yyvsp[-2]->child->intValue);
            }
            else if(!strcmp(yyvsp[-2]->child->name, "FLOAT")) {
                sprintf(num1, "%f", yyvsp[-2]->child->floatValue);
            }
            
            strcpy(t1.name, num1);
        }
        else if(!strcmp(yyvsp[-2]->child->name, "ID")) {
            strcpy(t1.name, yyvsp[-2]->child->id);
        }

        if(!strcmp(yyvsp[-2]->property, yyvsp[0]->property)) {
            strcpy(yyval->property, yyvsp[-2]->property);
        }
        else if(strcmp(t1.name, "") && strcmp(yyvsp[-2]->property, yyvsp[0]->property)) {
            t2 = search(this_scope, t1);
            if(!t2) {
                t2 = &my_search(&variList->my_root, t1)->info;
            }

            if(t2) {
                char num2[20] = {0};
                MyType t3 = MyType_default;
                MyType* t4;
                
                if(strcmp(yyvsp[0]->child->name, "ID")) {
                    if(!strcmp(yyvsp[0]->child->name, "INT")) {
                        sprintf(num2, "%d", yyvsp[0]->child->intValue);
                        if(strcmp(t2->type, "int")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = 1;
                            strcpy(yyval->property, "int");
                        }
                    }
                    else if(!strcmp(yyvsp[0]->child->name, "FLOAT")) {
                        sprintf(num2, "%f", yyvsp[0]->child->floatValue);
                        if(strcmp(t2->type, "float")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = 2;
                            strcpy(yyval->property, "float");
                        }
                    }
                }
                else {
                    // printf("id: %s\n" $3->child->id);
                    // print(this_scope);,
                    strcpy(t3.name, yyvsp[0]->child->id);
                    t4 = search(this_scope, t3);
                    if(t4) {
                        if(strcmp(t2->type, t4->type)) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = $1->type;
                            strcpy(yyval->property, yyvsp[-2]->property);
                        }
                    }
                    else if(yyvsp[-2]->type != yyvsp[0]->type) {
                        errors++;
                        printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                    }
                    else {
                        // $$->type = $1->type;
                        strcpy(yyval->property, yyvsp[-2]->property);
                    }
                }
            }
            
        }
    }
#line 3344 "syntax.tab.c"
    break;

  case 57:
#line 1625 "syntax.y"
                {
        yyval = insNode(yyvsp[-2], "Exp", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];

        strcpy(yyval->property, yyvsp[-1]->property);
    }
#line 3356 "syntax.tab.c"
    break;

  case 58:
#line 1632 "syntax.y"
                {
        yyval = insNode(yyvsp[-1], "Exp", (yylsp[-1]).first_line, NON_TERMINAL);
        yyvsp[-1]->bro = yyvsp[0];

        strcpy(yyval->property, yyvsp[0]->property);
    }
#line 3367 "syntax.tab.c"
    break;

  case 59:
#line 1638 "syntax.y"
              {
        yyval = insNode(yyvsp[-1], "Exp", (yylsp[-1]).first_line, NON_TERMINAL);
        yyvsp[-1]->bro = yyvsp[0];

        strcpy(yyval->property, yyvsp[0]->property);
    }
#line 3378 "syntax.tab.c"
    break;

  case 60:
#line 1644 "syntax.y"
                    {
        yyval = insNode(yyvsp[-3], "Exp", (yylsp[-3]).first_line, NON_TERMINAL);
        yyvsp[-3]->bro = yyvsp[-2];
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];

        MyType tmp = MyType_default;
        strcpy(tmp.name, yyvsp[-3]->id);
        MyType* mt = search(this_scope, tmp);
        if(mt != NULL) {
            if(mt->isfunc) {
                if(!strcmp(Compst_return_type, "null")) {
                    // printf("return type: %s\n", mt->return_type);
                    strcpy(yyval->property, mt->return_type);
                }
                else {
                    strcpy(yyval->property, Compst_return_type);
                }
                // dxr to do
                struct node* newnode = yyvsp[-1]; // newnode始终指向Args
                // printf("%d\n", newnode->child->child->intValue);
                char varifunc[12] = {"00_varifunc"};
                char Parameter[10][10];
                char Arguments[10][10];
                int right = 1;
                int vari_num = 0;
                int para_num = 0;
                MyType parameter = MyType_default; // 形参
                do { // 函数的参数列表 实参 
                    strcpy(parameter.name, varifunc);
                    struct my_node* ttp = my_search(&(mt->varilist), parameter);
                    if(ttp != NULL) {
                        parameter = ttp->info;
                        // print_mynode(parameter);
                        // print(this_scope);
                        // printf("%s : %s\n", mt->name, parameter.type);
                    }  // 后面做了
                    if(strcmp(newnode->child->child->name, "ID")){  // 不是变量
                        char argu[20];
                        if(strcmp(newnode->child->child->name, "INT") == 0 || newnode->child->type == 1){
                            strcpy(argu, "int");
                        }
                        else if(strcmp(newnode->child->child->name, "FLOAT") == 0 || newnode->child->type == 2){
                            strcpy(argu, "float");
                        }
                        else if(!strcmp(newnode->child->child->name, "Exp")) {
                            // printf("property: %s\n", newnode->child->child->property);
                            strcpy(argu, newnode->child->child->property);
                        }
                        else {
                            printf("你说你妈呢\n");
                            exit(0);
                        }
                        // printf("%s\n", argu);
                        strcpy(Arguments[vari_num++], argu);
                        if(ttp == NULL || strcmp(parameter.type, argu)){
                            right = 0;
                            // printf("test1: %s test2: %s test3: %s\n", mt->name, parameter.type, argu);
                        }
                        if(ttp != NULL){
                            // printf("type: %s\n", parameter.type);
                            strcpy(Parameter[para_num++], parameter.type);
                        }
                    }
                    else{
                        MyType argu = MyType_default;
                        strcpy(argu.name, newnode->child->child->id);
                        Mylink tttp = search(this_scope, argu); // 据卢爹说一定能搜到，在此就直接拿了用
                        // assert(tttp != NULL);
                        if(tttp != NULL) {
                            argu = *tttp;
                            // print_mynode(argu);
                            // Arguments[vari_num] = (char*)malloc(sizeof(argu.type));
                            strcpy(Arguments[vari_num++], argu.type);
                            if(ttp==NULL || strcmp(parameter.type, argu.type)){
                                right = 0;
                            }
                            if(ttp != NULL){
                                // Parameter[para_num] = (char*)malloc(sizeof(parameter.type));
                                strcpy(Parameter[para_num++], parameter.type);
                            }
                        }
                    }
                    varifunc[1] += 1;
                    if(varifunc[1] > '9'){
                        varifunc[0] += 1;
                        varifunc[1] = '0';
                    }
                    // result = my_insert(&tmp.varilist, temp);
                    if(newnode->child->bro != NULL) {
                        newnode = newnode->child->bro->bro;
                    }
                    else break;
                } while(newnode != NULL);
                strcpy(parameter.name, varifunc);
                // my_print(&(mt->varilist));
                struct my_node* tpp = my_search(&(mt->varilist), parameter);
                while(tpp){
                    parameter = tpp->info;
                    strcpy(Parameter[para_num++], parameter.type);
                    varifunc[1] += 1;
                    if(varifunc[1] > '9'){
                        varifunc[0] += 1;
                        varifunc[1] = '0';
                    }
                    strcpy(parameter.name, varifunc);
                    tpp = my_search(&(mt->varilist), parameter);
                    right = 0;
                }
                if(right == 0) {
                    printf("Error %d at line %d : Function \'%s(", FUNCTION_MISMATCH, last_row, mt->name);
                    for(int i = 0; i < vari_num; i ++){
                        if(i != vari_num - 1)
                            printf("%s,", Arguments[i]);
                        else
                            printf("%s", Arguments[i]);
                    }
                    printf(")\' is not applicable for arguments \'%s(", mt->name);
                    for(int i = 0; i < para_num; i ++){
                        if(i != para_num - 1)
                            printf("%s,", Parameter[i]);
                        else
                            printf("%s", Parameter[i]);
                    }
                    printf(")\'");
                    printf("\n");
                    errors ++;
                }
            }
            else {
                //	\begin{jcy 11}
                errors++;
                printf("Error %d at line %d : \'%s\' is not a function\n", NOT_FUNCTION, last_row, tmp.name);
                // 	\end{jcy 11}
            }
        }
        else if(!strcmp(yyvsp[-3]->id, "write")) {
            strcpy(yyval->property, "write");
        }
        else { // 函数未定义
            errors++;
            printf("Error %d at line %d : Undefined function \'%s\'\n", UNDEFINED_FUNCTION, last_row, tmp.name);
        }
    }
#line 3527 "syntax.tab.c"
    break;

  case 61:
#line 1788 "syntax.y"
               {
        yyval = insNode(yyvsp[-2], "Exp", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];

        MyType tmp = MyType_default;
        strcpy(tmp.name, yyvsp[-2]->id);
        MyType* mt = search(this_scope, tmp);
        if(mt != NULL) { 
            // tmp.def = 1;
            if(mt->isfunc) {
                char varifunc[12] = {"00_varifunc"};
                char Parameter[10][10];
                char Arguments[10][10];
                int right = 1, vari_num = 0, para_num = 0;
                MyType parameter = MyType_default; // 形参
                strcpy(parameter.name, varifunc);
                struct my_node* tpp = my_search(&(mt->varilist), parameter);
                while(tpp){
                    parameter = tpp->info;
                    strcpy(Parameter[para_num++], parameter.type);
                    varifunc[1] += 1;
                    if(varifunc[1] > '9'){
                        varifunc[0] += 1;
                        varifunc[1] = '0';
                    }
                    strcpy(parameter.name, varifunc);
                    tpp = my_search(&(mt->varilist), parameter);
                    right = 0;
                }
                if(right == 0) {
                    printf("Error %d at line %d : Function \'%s(", FUNCTION_MISMATCH, last_row, mt->name);
                    for(int i = 0; i < vari_num; i ++){
                        if(i != vari_num - 1)
                            printf("%s,", Arguments[i]);
                        else
                            printf("%s", Arguments[i]);
                    }
                    printf(")\' is not applicable for arguments \'%s(", mt->name);
                    for(int i = 0; i < para_num; i ++){
                        if(i != para_num - 1)
                            printf("%s,", Parameter[i]);
                        else
                            printf("%s", Parameter[i]);
                    }
                    printf(")\'");
                    printf("\n");
                    errors ++;
                }
            }
            else {
                //	\begin{jcy 11}
                errors++;
                printf("Error %d at line %d : \'%s\' is not a function\n", NOT_FUNCTION, last_row, tmp.name);
                // 	\end{jcy 11}
            }
        }
        else if(!strcmp(yyvsp[-2]->id, "read")) {
            strcpy(yyval->property, "read");
        }
        else { // 函数未定义
            errors++;
            printf("Error %d at line %d : Undefined function \'%s\'\n", UNDEFINED_FUNCTION, last_row, tmp.name);
        }
    }
#line 3597 "syntax.tab.c"
    break;

  case 62:
#line 1853 "syntax.y"
                    {
        yyval = insNode(yyvsp[-3], "Exp", (yylsp[-3]).first_line, NON_TERMINAL);
        yyvsp[-3]->bro = yyvsp[-2];
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
        // \begin{jcy 10}
        
        // printf("type: %s\n", $1->property);
        strcpy(yyval->property, yyvsp[-3]->property);
        MyType tmp = MyType_default;
        if(yyvsp[-3]->child->type == STRING_TYPE) {			//主要是因为直接是数值的话，它没有RBT上的name
		    strcpy(tmp.name, yyvsp[-3]->child->id);
		    MyType* ml = search(this_scope, tmp);
            if(ml) {
                if(ml->isarr) {
		    		// \begin{jcy 12}
		    		if(strcmp(yyvsp[-1]->child->name, "INT")) {
                        if(!strcmp(yyvsp[-1]->child->name, "FLOAT")) {
                            errors++;
                            printf("Error %d at line %d : \'%f\' is not an integer\n", ARRAY_ACCESS_OPERATEOR_NOT_INTEGER, last_row, yyvsp[-1]->child->floatValue);
                        }
		    		}
		    		// \end{jcy 12}
		    	}
		    	else {
                    errors++;
                    printf("Error %d at line %d : \'%s\' is not an array\n", NOT_ARRAY, last_row, tmp.name);
		    	}
            }
            else {
                ml = &my_search(&variList->my_root, tmp)->info;
                if(ml) {
                    if(ml->isarr) {
		    		// \begin{jcy 12}
		    		if(strcmp(yyvsp[-1]->child->name, "INT")) {
                        if(!strcmp(yyvsp[-1]->child->name, "FLOAT")) {
                            errors++;
                            printf("Error %d at line %d : \'%f\' is not an integer\n", ARRAY_ACCESS_OPERATEOR_NOT_INTEGER, last_row, yyvsp[-1]->child->floatValue);
                        }
		    		}
		    		// \end{jcy 12}
                    }
                    else {
                        errors++;
                        printf("Error %d at line %d : \'%s\' is not an array\n", NOT_ARRAY, last_row, tmp.name);
                    }
                }
                else {
                    errors++;
                    printf("Error %d at line %d : Undefined variable \'%s\'\n", UNDEFINED_VARIABLE, last_row, tmp.name);
                }
            }
      
        }
        //一个$1是否为数组变量的检查，一个$3是否为整数的检查（忽略段错误）
        // 类型传递
        // \end{jcy 10}
    }
#line 3660 "syntax.tab.c"
    break;

  case 63:
#line 1911 "syntax.y"
                     { // 结构体
		yyval = insNode(yyvsp[-2], "Exp", (yylsp[-2]).first_line, NON_TERMINAL);
		yyvsp[-2]->bro = yyvsp[-1];
		yyvsp[-1]->bro = yyvsp[0];

        MyType tmp = MyType_default;
        if(yyvsp[-2]->child->type == STRING_TYPE) {
		    // tmp.name = (char*)malloc(sizeof($1->child->id));
		    strcpy(tmp.name, yyvsp[-2]->child->id);
            MyType* ml = search(this_scope, tmp);
            if(!ml) {
                struct my_node* mn = my_search(&variList->my_root, tmp);
                ml = &mn->info;
            }
		    if(ml != NULL) { //先获取这个名字的东西，然后看看它是不是结构体
                // 如果不是结构体，则判为错误13；若是结构体，开始看ID是否存在：如果ID存在，将其属性赋给规约后的结果；若ID不存在，则判为错误14
		        if(ml->isstruct) {
                    MyType t1 = MyType_default;
                    strcpy(t1.name, ml->type);
                    MyType* t2 = search(this_scope, t1); // 找到该结构体类型的定义

                    MyType t3 = MyType_default;
                    strcpy(t3.name, yyvsp[0]->id);

                    struct my_node* tmp = my_search(&t2->varilist, t3);
                    if(tmp) {
                        strcpy(yyval->property, tmp->info.type);
                    }
                    else {
                        errors++;
                        printf("Error %d at line %d : Non-existing field \'%s\'\n", NOT_EXISTENT_FIELD, last_row, yyvsp[0]->id);
                    }
		        }
		        else {
                    errors++;
                    printf("Error %d at line %d : Illegal use of \'.\'\n", DOT_ILLEGAL_USE, last_row);
		        }
		    }
		}
		else {
            errors++;
            printf("Error %d at line %d : Illegal use of \'.\'\n", DOT_ILLEGAL_USE, last_row);
		}
        //	\end{jcy 13}
	}
#line 3710 "syntax.tab.c"
    break;

  case 64:
#line 1956 "syntax.y"
             {
		yyval = insNode(yyvsp[0], "Exp", (yylsp[0]).first_line, NON_TERMINAL);

        MyType tmp = MyType_default;
        // tmp.name = (char*)malloc(sizeof($1->id));
        strcpy(tmp.name, yyvsp[0]->id);
        MyType* mt = search(this_scope, tmp); // 寻找该变量的声明结点
        struct my_node* mn = my_search(&variList->my_root, tmp);
        if(mt) { 
            tmp.def = 1;
            strcpy(yyval->property, mt->type);
            strcpy(yyvsp[0]->property, mt->type);
        }
        else if(mn) {
            tmp.def = 1;
            strcpy(yyval->property, mn->info.type);
            strcpy(yyvsp[0]->property, mn->info.type);
        }
        else { // 变量未定义
            errors++;
            printf("Error %d at line %d : Undefined variable \'%s\'\n", UNDEFINED_VARIABLE, last_row, tmp.name);
        }
	}
#line 3738 "syntax.tab.c"
    break;

  case 65:
#line 1979 "syntax.y"
              {
		yyval = insNode(yyvsp[0], "Exp", (yylsp[0]).first_line, NON_TERMINAL);

        strcpy(yyval->property, yyvsp[0]->property);
	}
#line 3748 "syntax.tab.c"
    break;

  case 66:
#line 1984 "syntax.y"
                {
		yyval = insNode(yyvsp[0], "Exp", (yylsp[0]).first_line, NON_TERMINAL);

        strcpy(yyval->property, yyvsp[0]->property);
	}
#line 3758 "syntax.tab.c"
    break;

  case 67:
#line 1989 "syntax.y"
                      {
		char msg[100];
        sprintf(msg, "Syntax error.");
		myerror(msg);
	}
#line 3768 "syntax.tab.c"
    break;

  case 68:
#line 1994 "syntax.y"
                         {
		char msg[100];
        sprintf(msg, "Syntax error.");

		myerror(msg);
	}
#line 3779 "syntax.tab.c"
    break;

  case 69:
#line 2000 "syntax.y"
                         {
		char msg[100];
        sprintf(msg, "Syntax error.");
		myerror(msg);
	}
#line 3789 "syntax.tab.c"
    break;

  case 70:
#line 2007 "syntax.y"
                      {
        yyval = insNode(yyvsp[-2], "Args", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 3799 "syntax.tab.c"
    break;

  case 71:
#line 2012 "syntax.y"
          {
        yyval = insNode(yyvsp[0], "Args", (yylsp[0]).first_line, NON_TERMINAL);
    }
#line 3807 "syntax.tab.c"
    break;


#line 3811 "syntax.tab.c"

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
  *++yylsp = yyloc;

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

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp);
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
#line 2017 "syntax.y"

// #include "lex.yy.c"

int main(int argc, char** argv) {
	//char foutName[20];
    this_scope = init(this_scope);
    variList = init(variList);
	if(argc <= 1) return 1;
	FILE* f = fopen(argv[1], "r");
	FILE* f2 = fopen("out.ir", "w");
    FILE* f3 = fopen(argv[2], "w");
	if(!f) {
		perror(argv[1]);
		return 1;
	}
	yylineno = 1;
	yyrestart(f);
	yyparse();

    /*----检查Error 18----*/
    MyType tmp = MyType_default;
    for(int i = 0; i < func_cnt; i++) {
        strcpy(tmp.name, func_list[i]);
        MyType* mt = search(this_scope, tmp);
        if(mt) {
            if(!mt->def) {
                errors++;
                printf("Error %d at line %d : Undefined function \'%s\'\n", DECLARED_BUT_NOT_DEFINED, mt->dimension, tmp.name);
            }
        } 
    }
	
	FILE *f1 = fopen("output.txt", "w");
	if(!f1) {
		perror(argv[1]);
		return 1;
	}
	if(!errors) {
        printf("None!!!\n");
		f1 = fopen("output.txt", "w");
		printTree(head, 0, f1);
		
		f2 = fopen("out.ir", "w");
		translate_Program(head, f2);
        
        f3 = fopen(argv[2], "w");
        genAsm(head, f3);
	}
	fclose(f);
	fclose(f1);
	fclose(f2);
	return 0;
}


void yyerror(char *msg) {
    // errors++;
    // fprintf(stderr, "Error type B at Line %d: %s because %s\n", yylineno, msg, yytext);
}

void myerror(char *msg) {
    fprintf(stderr, "Error type B at Line %d: %s\n", last_row, msg); // B
	errors++;
}
