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
	#include "SyntaxTree.h"
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
    
    #define REDEFINED_FIELD 15
    #define REDEFINED_STRUCT 16
    #define UNDEFINED_STRUCT 17


	void yyerror(char*);
	void myerror(char*);
	int yylex();
	extern int yylineno;
	extern int last_row;
	int errors = 0;
    int yydebug = 1;
    int flgStruct = 0, flgArr = 0;
    struct rb_root mytree = RB_ROOT;
    MyType tmp;
    VariLink this_scope;

#line 106 "syntax.tab.c"

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
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  131

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
       0,    66,    66,    71,    75,    80,   132,   136,   165,   168,
     180,   183,   190,   217,   243,   246,   251,   256,   262,   267,
     274,   279,   284,   301,   309,   313,   317,   337,   396,   401,
     406,   415,   419,   424,   427,   432,   439,   448,   466,   469,
     476,   479,   486,   489,   518,   524,   529,   536,   541,   548,
     553,   558,   563,   568,   573,   578,   583,   588,   592,   596,
     616,   635,   641,   646,   663,   666,   669,   676,   683,   692,
     697
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

#define YYPACT_NINF (-112)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-27)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       3,  -112,     6,    36,  -112,     3,    56,  -112,    15,    17,
    -112,  -112,  -112,    37,  -112,    53,    42,    12,    51,    14,
    -112,    51,  -112,    60,    13,    60,  -112,  -112,    49,   164,
     164,   128,   164,    64,    65,    52,  -112,    47,    51,    51,
     100,    67,  -112,    60,    68,    81,    69,  -112,  -112,    72,
      73,     5,    84,    88,    16,   120,    58,     0,    83,   218,
     177,   164,   164,    92,    29,  -112,  -112,  -112,  -112,  -112,
      95,   142,   164,   164,   164,   164,   164,   164,   164,   150,
    -112,    97,  -112,     3,  -112,  -112,  -112,  -112,  -112,  -112,
      60,   164,    99,  -112,   191,   104,  -112,  -112,  -112,   231,
     244,  -112,  -112,  -112,  -112,  -112,   257,   278,    58,    58,
       0,     0,   268,   268,    82,   204,  -112,  -112,   257,  -112,
     164,  -112,    79,    79,  -112,  -112,  -112,   101,  -112,    79,
    -112
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,    10,    15,     0,     2,     4,     0,    11,    16,     0,
      13,     1,     3,    42,     6,     0,     0,     8,     0,     0,
       5,     0,     7,     0,     0,     0,    64,    65,    63,     0,
       0,     0,     0,     0,     0,     0,    33,     0,     0,     0,
       0,     0,    18,     0,     0,    21,     0,    42,     9,     0,
       0,     0,     0,    38,    40,     0,    57,    58,     0,     0,
       0,     0,     0,     0,     0,    12,    24,    25,    32,    31,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      19,    22,    17,     0,    23,    43,    46,    45,    44,    29,
       0,     0,     0,    60,    70,     0,    66,    56,    34,     0,
       0,    30,    28,    27,    62,    48,    47,    51,    52,    53,
      54,    55,    49,    50,     0,     0,    20,    39,    41,    67,
       0,    59,     0,     0,    68,    61,    69,    35,    37,     0,
      36
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -112,  -112,   121,  -112,   105,     4,  -112,  -112,  -112,  -112,
      50,  -112,   122,   -14,  -112,  -111,   -30,  -112,     8,   -29,
      24
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,    15,    35,     7,     9,    10,    16,
      44,    45,    36,    37,    38,    39,    52,    53,    54,    40,
      95
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      56,    57,    59,    60,     6,    64,    87,    46,     1,     6,
      70,   127,   128,     8,    17,    41,    49,    50,   130,     1,
      51,    23,    79,    43,    66,    67,    94,    91,    88,     2,
     102,    17,    99,   100,    24,    42,    11,   103,    24,   -14,
       2,    18,   106,   107,   108,   109,   110,   111,   112,   113,
     115,    81,    25,    63,    26,    27,     1,    19,    28,    47,
     117,    20,   118,    13,    14,    29,    21,    47,    70,    55,
      30,    31,    65,    75,    76,    21,   -26,     2,    32,    33,
      79,    34,    26,    27,    61,    62,    28,    43,    80,    82,
      83,    94,    89,    29,    84,    85,    86,    90,    30,    31,
     101,    68,   104,    21,    96,   124,    32,    33,    69,    34,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    24,
     119,    92,    79,    26,    27,   121,    12,    28,    48,    58,
     129,    26,    27,   116,    29,    28,     0,     0,    22,    30,
      31,    93,    29,   105,   126,    26,    27,    30,    31,    28,
       0,   114,     0,    26,    27,     0,    29,    28,     0,     0,
       0,    30,    31,     0,    29,     0,     0,    26,    27,    30,
      31,    28,     0,     0,     0,     0,     0,     0,    29,     0,
       0,     0,     0,    30,    31,    98,     0,    70,    71,    72,
      73,    74,    75,    76,    77,    78,     0,     0,     0,    79,
     120,    70,    71,    72,    73,    74,    75,    76,    77,    78,
       0,     0,     0,    79,    70,    71,    72,    73,    74,    75,
      76,    77,    78,     0,     0,     0,    79,   125,    70,    71,
      72,    73,    74,    75,    76,    77,    78,     0,     0,    97,
      79,    70,    71,    72,    73,    74,    75,    76,    77,    78,
       0,     0,   122,    79,    70,    71,    72,    73,    74,    75,
      76,    77,    78,     0,     0,   123,    79,    70,    71,    72,
      73,    74,    75,    76,    77,    78,     0,     0,    70,    79,
      72,    73,    74,    75,    76,     0,     0,     0,    70,     0,
      79,    73,    74,    75,    76,     0,     0,     0,     0,     0,
      79
};

static const yytype_int16 yycheck[] =
{
      29,    30,    31,    32,     0,    35,     1,    21,     5,     5,
      10,   122,   123,     7,     6,     1,     3,     4,   129,     5,
       7,     9,    22,    19,    38,    39,    55,    11,    23,    26,
       1,    23,    61,    62,    22,    21,     0,     8,    22,    24,
      26,    24,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    43,     1,     1,     3,     4,     5,    20,     7,     7,
      90,     8,    91,     7,     8,    14,    24,     7,    10,    20,
      19,    20,    25,    15,    16,    24,    25,    26,    27,    28,
      22,    30,     3,     4,    20,    20,     7,    83,    21,    21,
       9,   120,     8,    14,    25,    23,    23,     9,    19,    20,
       8,     1,     7,    24,    21,    23,    27,    28,     8,    30,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    22,
      21,     1,    22,     3,     4,    21,     5,     7,    23,     1,
      29,     3,     4,    83,    14,     7,    -1,    -1,    16,    19,
      20,    21,    14,     1,   120,     3,     4,    19,    20,     7,
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
       8,    24,    46,     9,    22,     1,     3,     4,     7,    14,
      19,    20,    27,    28,    30,    39,    46,    47,    48,    49,
      53,     1,    21,    39,    44,    45,    47,     7,    38,     3,
       4,     7,    50,    51,    52,    20,    53,    53,     1,    53,
      53,    20,    20,     1,    50,    25,    47,    47,     1,     8,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    22,
      21,    52,    21,     9,    25,    23,    23,     1,    23,     8,
       9,    11,     1,    21,    53,    54,    21,    21,     8,    53,
      53,     8,     1,     8,     7,     1,    53,    53,    53,    53,
      53,    53,    53,    53,     1,    53,    44,    50,    53,    21,
       9,    21,    21,    21,    23,    23,    54,    49,    49,    29,
      49
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    34,    35,    36,    36,    37,    37,    37,    38,    38,
      39,    39,    40,    40,    41,    41,    42,    43,    43,    43,
      44,    44,    45,    46,    47,    47,    47,    48,    48,    48,
      48,    49,    49,    49,    49,    49,    49,    49,    50,    50,
      51,    51,    52,    52,    52,    52,    52,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    54,
      54
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     1,     3,
       1,     1,     5,     2,     1,     0,     1,     4,     3,     4,
       3,     1,     2,     3,     2,     2,     0,     3,     3,     3,
       3,     2,     2,     1,     3,     5,     7,     5,     1,     3,
       1,     3,     1,     4,     4,     4,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     4,
       3,     4,     3,     1,     1,     1,     3,     4,     4,     3,
       1
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
#line 66 "syntax.y"
                     {
        yyval = insNode(yyvsp[0], "Program", yyvsp[0]->lines, NON_TERMINAL);
    }
#line 1599 "syntax.tab.c"
    break;

  case 3:
#line 71 "syntax.y"
                               {
        yyval = insNode(yyvsp[-1], "ExtDefList", (yylsp[-1]).first_line, NON_TERMINAL);
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 1608 "syntax.tab.c"
    break;

  case 4:
#line 75 "syntax.y"
      {
        yyval = insNode(NULL, "ExtDefList", yylineno, NON_TERMINAL);
    }
#line 1616 "syntax.tab.c"
    break;

  case 5:
#line 80 "syntax.y"
                                   {
        yyval = insNode(yyvsp[-2], "ExtDef", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
        // printf("%s\n", $2->child->child->id);
        // printf("%s\n", $2->name);
        // tmp.isvariable = 1;
        tmp.name = (char*)malloc(sizeof(yyvsp[-1]->child->child->id));
        strcpy(tmp.name, yyvsp[-1]->child->child->id); // 不要怀疑这个就是变量名
        if(!flgStruct) { // 不是结构体，是普通的变量声明 
            if(search(this_scope, tmp)) {
                char msg[100];
                sprintf(msg, "Error %d at line %d : Redefined variable \'%s\'", REDEFINED_VARIABLE, last_row, tmp.name);
                myerror(msg);
            }
            else {
                printf("insert variable \'%s\'\n", tmp.name);
                tmp.def = 1;
                tmp.type = (char*)malloc(sizeof(yyvsp[-2]->child->id));
                strcpy(tmp.type, yyvsp[-2]->child->id);
                tmp.isvariable = 1;
                this_scope = insert(this_scope, tmp);

                free(tmp.type);
                tmp.def = 0;
                tmp.isvariable = 0;
            }
        }
        else { // 是结构体，且有变量 tmp.name
            if(search(this_scope, tmp)) {
                char msg[100];
                sprintf(msg, "Error %d at line %d : Redefined variable \'%s\'", REDEFINED_VARIABLE, last_row, tmp.name);
                myerror(msg);
            }
            else {
                printf("insert variable \'%s\'\n", tmp.name);
                tmp.def = 1;
                // printf("!!!\n");
                tmp.type = (char*)malloc(sizeof(yyvsp[-2]->child->child->id));
                // printf("%s\n", $1->child->child->id);
                strcpy(tmp.type, yyvsp[-2]->child->child->id);
                // printf("!!!\n");
                tmp.isstruct = 1;
                this_scope = insert(this_scope, tmp);

                free(tmp.type);
                tmp.def = 0;
                tmp.isstruct = 0;
            }
        }
        free(tmp.name);
    }
#line 1673 "syntax.tab.c"
    break;

  case 6:
#line 132 "syntax.y"
                     {
        yyval = insNode(yyvsp[-1], "ExtDef", (yylsp[-1]).first_line, NON_TERMINAL);
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 1682 "syntax.tab.c"
    break;

  case 7:
#line 136 "syntax.y"
                              {
        yyval = insNode(yyvsp[-2], "ExtDef", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];

        tmp.name = (char*)malloc(sizeof(yyvsp[-1]->child->id));
        // tmp.isfunc = 1;
        strcpy(tmp.name, yyvsp[-1]->child->id);
        if(search(this_scope, tmp)) { // 函数重定义
            char msg[100];
            sprintf(msg, "Error %d at line %d : Redefined function \'%s\'", REDEFINED_FUNCTION, last_row, tmp.name);
            myerror(msg);
        }
        else {
            printf("insert function \'%s\'\n", tmp.name);
            tmp.def = 1;
            tmp.return_type = (char*)malloc(sizeof(yyvsp[-2]->child->id));
            strcpy(tmp.type, yyvsp[-2]->child->id);
            tmp.isfunc = 1;
            this_scope = insert(this_scope, tmp);

            free(tmp.type);
            tmp.def = 0;
            tmp.isfunc = 0;
        }
        free(tmp.name);
    }
#line 1714 "syntax.tab.c"
    break;

  case 8:
#line 165 "syntax.y"
                    {
        yyval = insNode(yyvsp[0], "ExtDecList", (yylsp[0]).first_line, NON_TERMINAL);
    }
#line 1722 "syntax.tab.c"
    break;

  case 9:
#line 168 "syntax.y"
                              {
        yyval = insNode(yyvsp[-2], "ExtDecList", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 1732 "syntax.tab.c"
    break;

  case 10:
#line 180 "syntax.y"
                 {
        yyval = insNode(yyvsp[0], "Specifier", (yylsp[0]).first_line, NON_TERMINAL);
    }
#line 1740 "syntax.tab.c"
    break;

  case 11:
#line 183 "syntax.y"
                      {
        yyval = insNode(yyvsp[0], "Specifier", (yylsp[0]).first_line, NON_TERMINAL);
    }
#line 1748 "syntax.tab.c"
    break;

  case 12:
#line 190 "syntax.y"
                                          {
// StructSpecifier : STRUCT OptTag LC DefList RC {
        yyval = insNode(yyvsp[-4], "StructSpecifier", (yylsp[-4]).first_line, NON_TERMINAL);
        yyvsp[-4]->bro = yyvsp[-3];
        yyvsp[-3]->bro = yyvsp[-2];
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];

        tmp.name = (char*)malloc(sizeof(yyvsp[-3]->child->id));
        strcpy(tmp.name, yyvsp[-3]->child->id);
        if(search(this_scope, tmp)) { // 结构体名字重复
            char msg[100];
            sprintf(msg, "Error %d at line %d : Duplicate name \'%s\'", REDEFINED_STRUCT, last_row, tmp.name);
            myerror(msg);
        }
        else {
            printf("insert struct \'%s\'\n", tmp.name);
            tmp.def = 1;
            tmp.isstruct = 1;
            this_scope = insert(this_scope, tmp);

            tmp.def = 0;
            tmp.isstruct = 0;
            // flgStruct = 1;
        }
        free(tmp.name);
    }
#line 1780 "syntax.tab.c"
    break;

  case 13:
#line 217 "syntax.y"
                 {
        yyval = insNode(yyvsp[-1], "StructSpecifier", (yylsp[-1]).first_line, NON_TERMINAL);
        yyvsp[-1]->bro = yyvsp[0];

        tmp.name = (char*)malloc(sizeof(yyvsp[0]->child->id));
        strcpy(tmp.name, yyvsp[0]->child->id);
        if(!search(this_scope, tmp)) {
            char msg[100];
            sprintf(msg, "Error %d at line %d : Undefined struct \'%s\'", UNDEFINED_STRUCT, last_row, tmp.name);
            myerror(msg);
        }
        else {
            printf("insert struct \'%s\'\n", tmp.name);
            tmp.def = 1;
            tmp.isstruct = 1;
            this_scope = insert(this_scope, tmp);
            
            tmp.def = 0;
            tmp.isstruct = 0;
            // flgStruct = 1;
        }
        free(tmp.name);
        flgStruct = 2;
    }
#line 1809 "syntax.tab.c"
    break;

  case 14:
#line 243 "syntax.y"
            {
        yyval = insNode(yyvsp[0], "OptTag", (yylsp[0]).first_line, NON_TERMINAL);
    }
#line 1817 "syntax.tab.c"
    break;

  case 15:
#line 246 "syntax.y"
      {
        yyval = insNode(NULL, "OptTag", yylineno, NON_TERMINAL);
    }
#line 1825 "syntax.tab.c"
    break;

  case 16:
#line 251 "syntax.y"
         {
        yyval = insNode(yyvsp[0], "Tag", (yylsp[0]).first_line, NON_TERMINAL);
    }
#line 1833 "syntax.tab.c"
    break;

  case 17:
#line 256 "syntax.y"
                          {
        yyval = insNode(yyvsp[-3], "FunDec", (yylsp[-3]).first_line, NON_TERMINAL);
        yyvsp[-3]->bro = yyvsp[-2];
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 1844 "syntax.tab.c"
    break;

  case 18:
#line 262 "syntax.y"
               {
        yyval = insNode(yyvsp[-2], "FunDec", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 1854 "syntax.tab.c"
    break;

  case 19:
#line 267 "syntax.y"
                         {
		char msg[100];
		sprintf(msg, "VarList.");
		myerror(msg);
	}
#line 1864 "syntax.tab.c"
    break;

  case 20:
#line 274 "syntax.y"
                                 {
        yyval = insNode(yyvsp[-2], "VarList", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 1874 "syntax.tab.c"
    break;

  case 21:
#line 279 "syntax.y"
               {
        yyval = insNode(yyvsp[0], "VarList", (yylsp[0]).first_line, NON_TERMINAL);
    }
#line 1882 "syntax.tab.c"
    break;

  case 22:
#line 284 "syntax.y"
                            {
        yyval = insNode(yyvsp[-1], "ParamDec", (yylsp[-1]).first_line, NON_TERMINAL);
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 1891 "syntax.tab.c"
    break;

  case 23:
#line 301 "syntax.y"
                   {
        yyval = insNode(yyvsp[-2], "CompSt", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 1901 "syntax.tab.c"
    break;

  case 24:
#line 309 "syntax.y"
              {
        yyval = insNode(yyvsp[-1], "Mid", (yylsp[-1]).first_line, NON_TERMINAL);
        yyvsp[-1]->bro = yyvsp[0];
	}
#line 1910 "syntax.tab.c"
    break;

  case 25:
#line 313 "syntax.y"
                   {
        yyval = insNode(yyvsp[-1], "Mid", (yylsp[-1]).first_line, NON_TERMINAL);
        yyvsp[-1]->bro = yyvsp[0];
	}
#line 1919 "syntax.tab.c"
    break;

  case 26:
#line 317 "syntax.y"
          {
        yyval = insNode(NULL, "Mid", yylineno, NON_TERMINAL);
	}
#line 1927 "syntax.tab.c"
    break;

  case 27:
#line 337 "syntax.y"
                             {
        yyval = insNode(yyvsp[-2], "Def", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];

        // printf("variable name: %s\n", $2->child->child->child->id);
        if(!flgArr) {
            tmp.name = (char*)malloc(sizeof(yyvsp[-1]->child->child->child->id));
            strcpy(tmp.name, yyvsp[-1]->child->child->child->id);
        }
        else {
            tmp.name = (char*)malloc(sizeof(yyvsp[-1]->child->child->child->child->id));
            strcpy(tmp.name, yyvsp[-1]->child->child->child->child->id);
        }
        // tmp.name = (char*)malloc(sizeof($2->child->child->child->id));
        // strcpy(tmp.name, $2->child->child->child->id);
        if(search(this_scope, tmp)) { // 两种可能：struct xx {...} yy; 或 int a;
            char msg[100];
            if(!flgStruct) // 普通变量声明
                // printf("%s\n", tmp.name);
                sprintf(msg, "Error %d at line %d : Redefined variable \'%s\'", REDEFINED_VARIABLE, last_row, tmp.name);
            else // 结构体变量声明
                sprintf(msg, "Error %d at line %d : Redefined field \'%s\'", REDEFINED_FIELD, last_row, tmp.name);
            myerror(msg);
        }
        else {
            printf("insert variable \'%s\'\n", tmp.name);
            tmp.def = 1;
            printf("%d\n", flgStruct);
            if(flgStruct == 2) { // 是struct tag的情况，如struct sa nn;
                tmp.type = (char*)malloc(sizeof(yyvsp[-2]->child->child->id));
                // printf("%s\n", $1->child->child->id); // 应该是struct
                strcpy(tmp.type, yyvsp[-2]->child->child->id);
            }
            else if(flgStruct == 1) { // 一般变量，如int a;

                tmp.type = (char*)malloc(sizeof(yyvsp[-2]->child->id));
                // printf("%s\n", $1->child->name);
                strcpy(tmp.type, yyvsp[-2]->child->id);

                // printf("%d\n", flgArr);

                if(flgArr) { // 是数组
                    tmp.isarr = 1;
                    tmp.dimension = yyvsp[-1]->child->child->bro->bro->intValue;
                    flgArr = 0;
                }
            }
            tmp.isvariable = 1;
            this_scope = insert(this_scope, tmp);

            free(tmp.type);
            tmp.def = 0;
            tmp.isvariable = 0;
            tmp.isarr = 0;
            tmp.dimension = 0;
        }
        free(tmp.name);
    }
#line 1991 "syntax.tab.c"
    break;

  case 28:
#line 396 "syntax.y"
                                 {
		char msg[100];
		sprintf(msg, "error: Missing \";\"");	//necessary
		myerror(msg);
	}
#line 2001 "syntax.tab.c"
    break;

  case 29:
#line 401 "syntax.y"
                         {
    	char msg[100];
		sprintf(msg, "Syntax error.");
		myerror(msg);
    }
#line 2011 "syntax.tab.c"
    break;

  case 30:
#line 406 "syntax.y"
                               {
		char msg[100];
		sprintf(msg, "Syntax error.");
		myerror(msg);
	}
#line 2021 "syntax.tab.c"
    break;

  case 31:
#line 415 "syntax.y"
             {
        yyval = insNode(yyvsp[-1], "Stmt", (yylsp[-1]).first_line, NON_TERMINAL);
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2030 "syntax.tab.c"
    break;

  case 32:
#line 419 "syntax.y"
                {
		char msg[100];
		sprintf(msg, "error: Missing \";\"");
		myerror(msg);
	}
#line 2040 "syntax.tab.c"
    break;

  case 33:
#line 424 "syntax.y"
             {
        yyval = insNode(yyvsp[0], "Stmt", (yylsp[0]).first_line, NON_TERMINAL);
    }
#line 2048 "syntax.tab.c"
    break;

  case 34:
#line 427 "syntax.y"
                      {
        yyval = insNode(yyvsp[-2], "Stmt", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2058 "syntax.tab.c"
    break;

  case 35:
#line 432 "syntax.y"
                                              {
        yyval = insNode(yyvsp[-4], "Stmt", (yylsp[-4]).first_line, NON_TERMINAL);
        yyvsp[-4]->bro = yyvsp[-3];
        yyvsp[-3]->bro = yyvsp[-2];
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2070 "syntax.tab.c"
    break;

  case 36:
#line 439 "syntax.y"
                                  {
        yyval = insNode(yyvsp[-6], "Stmt", (yylsp[-6]).first_line, NON_TERMINAL);
        yyvsp[-6]->bro = yyvsp[-5];
        yyvsp[-5]->bro = yyvsp[-4];
        yyvsp[-4]->bro = yyvsp[-3];
        yyvsp[-3]->bro = yyvsp[-2];
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2084 "syntax.tab.c"
    break;

  case 37:
#line 448 "syntax.y"
                           {
        yyval = insNode(yyvsp[-4], "Stmt", (yylsp[-4]).first_line, NON_TERMINAL);
        yyvsp[-4]->bro = yyvsp[-3];
        yyvsp[-3]->bro = yyvsp[-2];
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2096 "syntax.tab.c"
    break;

  case 38:
#line 466 "syntax.y"
              {
        yyval = insNode(yyvsp[0], "DecList", (yylsp[0]).first_line, NON_TERMINAL);
    }
#line 2104 "syntax.tab.c"
    break;

  case 39:
#line 469 "syntax.y"
                        {
        yyval = insNode(yyvsp[-2], "DecList", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2114 "syntax.tab.c"
    break;

  case 40:
#line 476 "syntax.y"
             {
        yyval = insNode(yyvsp[0], "Dec", (yylsp[0]).first_line, NON_TERMINAL);
    }
#line 2122 "syntax.tab.c"
    break;

  case 41:
#line 479 "syntax.y"
                          {
        yyval = insNode(yyvsp[-2], "Dec", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2132 "syntax.tab.c"
    break;

  case 42:
#line 486 "syntax.y"
            {
        yyval = insNode(yyvsp[0], "VarDec", (yylsp[0]).first_line, NON_TERMINAL);
    }
#line 2140 "syntax.tab.c"
    break;

  case 43:
#line 489 "syntax.y"
                       {
        yyval = insNode(yyvsp[-3], "VarDec", (yylsp[-3]).first_line, NON_TERMINAL);
        yyvsp[-3]->bro = yyvsp[-2];
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];

        // tmp.name = (char*)malloc(sizeof($1->child->id));
        // strcpy(tmp.name, $1->child->id);
        // if(search(this_scope, tmp)) {
        //     char msg[100];
        //     sprintf(msg, "Error %d at line %d : Redefined variable \'%s\'", REDEFINED_VARIABLE, last_row, tmp.name);
        //     myerror(msg);
        // }
        // else {
        //     printf("insert array \'%s\'\n", tmp.name);
        //     tmp.def = 1;
        //     // tmp.type = (char*)malloc(sizeof($1->child->id));
        //     // strcpy(tmp.type, $1->child->id);
        //     tmp.isarr = 1;
        //     tmp.dimension = $1->bro->bro->intValue;
        //     this_scope = insert(this_scope, tmp);

        //     free(tmp.type);
        //     tmp.def = 0;
        //     tmp.isarr = 0;
        //     tmp.dimension = 0;
        // }
        // free(tmp.name);
    }
#line 2174 "syntax.tab.c"
    break;

  case 44:
#line 518 "syntax.y"
                      {
        yyval = insNode(yyvsp[-3], "VarDec", (yylsp[-3]).first_line, NON_TERMINAL);
        yyvsp[-3]->bro = yyvsp[-2];
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2185 "syntax.tab.c"
    break;

  case 45:
#line 524 "syntax.y"
                         {
        char msg[100];
        sprintf(msg, "Missing \"]\".");
		myerror(msg);
    }
#line 2195 "syntax.tab.c"
    break;

  case 46:
#line 529 "syntax.y"
                            {
		char msg[100];
		sprintf(msg, "int.");
		myerror(msg);
	}
#line 2205 "syntax.tab.c"
    break;

  case 47:
#line 536 "syntax.y"
                       {
        yyval = insNode(yyvsp[-2], "Exp", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2215 "syntax.tab.c"
    break;

  case 48:
#line 541 "syntax.y"
                             { 
		char msg[100];
        sprintf(msg, "Syntax error."); // ASSIGNOP not in front of Exp
        // fprintf(stderr, "Error type B at line %d: %s\n", yylineno, msg);
		// errors++;
		myerror(msg);
	}
#line 2227 "syntax.tab.c"
    break;

  case 49:
#line 548 "syntax.y"
                  {
        yyval = insNode(yyvsp[-2], "Exp", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2237 "syntax.tab.c"
    break;

  case 50:
#line 553 "syntax.y"
                 {
        yyval = insNode(yyvsp[-2], "Exp", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2247 "syntax.tab.c"
    break;

  case 51:
#line 558 "syntax.y"
                    {
        yyval = insNode(yyvsp[-2], "Exp", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2257 "syntax.tab.c"
    break;

  case 52:
#line 563 "syntax.y"
                   {
        yyval = insNode(yyvsp[-2], "Exp", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2267 "syntax.tab.c"
    break;

  case 53:
#line 568 "syntax.y"
                    {
        yyval = insNode(yyvsp[-2], "Exp", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2277 "syntax.tab.c"
    break;

  case 54:
#line 573 "syntax.y"
                   {
        yyval = insNode(yyvsp[-2], "Exp", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2287 "syntax.tab.c"
    break;

  case 55:
#line 578 "syntax.y"
                  {
        yyval = insNode(yyvsp[-2], "Exp", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2297 "syntax.tab.c"
    break;

  case 56:
#line 583 "syntax.y"
                {
        yyval = insNode(yyvsp[-2], "Exp", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2307 "syntax.tab.c"
    break;

  case 57:
#line 588 "syntax.y"
                {
        yyval = insNode(yyvsp[-1], "Exp", (yylsp[-1]).first_line, NON_TERMINAL);
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2316 "syntax.tab.c"
    break;

  case 58:
#line 592 "syntax.y"
              {
        yyval = insNode(yyvsp[-1], "Exp", (yylsp[-1]).first_line, NON_TERMINAL);
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2325 "syntax.tab.c"
    break;

  case 59:
#line 596 "syntax.y"
                    {
        yyval = insNode(yyvsp[-3], "Exp", (yylsp[-3]).first_line, NON_TERMINAL);
        yyvsp[-3]->bro = yyvsp[-2];
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];

        tmp.name = (char*)malloc(sizeof(yyvsp[-3]->id));
        strcpy(tmp.name, yyvsp[-3]->id);
        if(search(this_scope, tmp)) { 
            tmp.def = 1;
            // tmp.type = $1->type;
            // my_insert(&mytree, tmp);
            this_scope = insert(this_scope, tmp);
        }
        else { // 函数未定义
            char msg[100];
            sprintf(msg, "Error %d at line %d : Undefined function \'%s\'", UNDEFINED_FUNCTION, last_row, tmp.name);
            myerror(msg);
        }
    }
#line 2350 "syntax.tab.c"
    break;

  case 60:
#line 616 "syntax.y"
               {
        yyval = insNode(yyvsp[-2], "Exp", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];

        tmp.name = (char*)malloc(sizeof(yyvsp[-2]->id));
        strcpy(tmp.name, yyvsp[-2]->id);
        if(search(this_scope, tmp)) { 
            tmp.def = 1;
            // tmp.type = $1->type;
            // my_insert(&mytree, tmp);
            this_scope = insert(this_scope, tmp);
        }
        else { // 函数未定义
            char msg[100];
            sprintf(msg, "Error %d at line %d : Undefined function \'%s\'", UNDEFINED_FUNCTION, last_row, tmp.name);
            myerror(msg);
        }
    }
#line 2374 "syntax.tab.c"
    break;

  case 61:
#line 635 "syntax.y"
                    {
        yyval = insNode(yyvsp[-3], "Exp", (yylsp[-3]).first_line, NON_TERMINAL);
        yyvsp[-3]->bro = yyvsp[-2];
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2385 "syntax.tab.c"
    break;

  case 62:
#line 641 "syntax.y"
                     { // 结构体
		yyval = insNode(yyvsp[-2], "Exp", (yylsp[-2]).first_line, NON_TERMINAL);
		yyvsp[-2]->bro = yyvsp[-1];
		yyvsp[-1]->bro = yyvsp[0];
	}
#line 2395 "syntax.tab.c"
    break;

  case 63:
#line 646 "syntax.y"
             {
		yyval = insNode(yyvsp[0], "Exp", (yylsp[0]).first_line, NON_TERMINAL);
        //print(this_scope);
        tmp.name = (char*)malloc(sizeof(yyvsp[0]->id));
        strcpy(tmp.name, yyvsp[0]->id);
        if(search(this_scope, tmp)) { 
            tmp.def = 1;
            // tmp.type = $1->type;
            // my_insert(&mytree, tmp);
            this_scope = insert(this_scope, tmp);
        }
        else { // 变量未定义
            char msg[100];
            sprintf(msg, "Error %d at line %d : Undefined variable \'%s\'", UNDEFINED_VARIABLE, last_row, tmp.name);
            myerror(msg);
        }
	}
#line 2417 "syntax.tab.c"
    break;

  case 64:
#line 663 "syntax.y"
              {
		yyval = insNode(yyvsp[0], "Exp", (yylsp[0]).first_line, NON_TERMINAL);
	}
#line 2425 "syntax.tab.c"
    break;

  case 65:
#line 666 "syntax.y"
                {
		yyval = insNode(yyvsp[0], "Exp", (yylsp[0]).first_line, NON_TERMINAL);
	}
#line 2433 "syntax.tab.c"
    break;

  case 66:
#line 669 "syntax.y"
                      {
		char msg[100];
        sprintf(msg, "Syntax error.");
        // fprintf(stderr, "Error type B at line %d: %s\n", yylineno, msg);
		// errors++;
		myerror(msg);
	}
#line 2445 "syntax.tab.c"
    break;

  case 67:
#line 676 "syntax.y"
                         {
		char msg[100];
        sprintf(msg, "Syntax error.");
        // fprintf(stderr, "Error type B at line %d: %s\n", yylineno, msg);
		// errors++;
		myerror(msg);
	}
#line 2457 "syntax.tab.c"
    break;

  case 68:
#line 683 "syntax.y"
                         {
		char msg[100];
        sprintf(msg, "Syntax error.");
        // fprintf(stderr, "Error type B at line %d: %s\n", yylineno, msg);
		// errors++;
		myerror(msg);
	}
#line 2469 "syntax.tab.c"
    break;

  case 69:
#line 692 "syntax.y"
                      {
        yyval = insNode(yyvsp[-2], "CompSt", (yylsp[-2]).first_line, NON_TERMINAL);
        yyvsp[-2]->bro = yyvsp[-1];
        yyvsp[-1]->bro = yyvsp[0];
    }
#line 2479 "syntax.tab.c"
    break;

  case 70:
#line 697 "syntax.y"
          {
        yyval = insNode(yyvsp[0], "CompSt", (yylsp[0]).first_line, NON_TERMINAL);
    }
#line 2487 "syntax.tab.c"
    break;


#line 2491 "syntax.tab.c"

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
#line 702 "syntax.y"

// #include "lex.yy.c"

int main(int argc, char** argv) {
    this_scope = init(this_scope);

	if(argc <= 1) return 1;
	FILE* f = fopen(argv[1], "r");
	if(!f) {
		perror(argv[1]);
		return 1;
	}
	yylineno = 1;
	yyrestart(f);
	yyparse();

	FILE *f1 = fopen("output.txt", "w");
	if(!f1) {
		perror(argv[1]);
		return 1;
	}
	if(!errors) {
        printf("None!!!\n");
		f1 = fopen("output.txt", "w");
		printTree(head, 0, f1);
	}
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
