#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140101

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 1 "parser.y"

	#include <stdio.h>
	#include <stdlib.h>
	#include "SymbolTable.h"
	extern int num_lines;
	extern char *yytext;
	extern char str[300];
	int functionNum = 0;
  int LocalOffset = 0;
	int yyerror(char *msg);
 
  FILE *f_asm;

#line 35 "parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
         int token;
         int intVal;
         double doubleVal;
         char charVal;
         char *ident;
        } YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 48 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define IDENTIFIER 257
#define INT_P 258
#define DOUBLE_P 259
#define SCIEN_P 260
#define CHAR_P 261
#define STR_P 262
#define VOID 263
#define INT 264
#define DOUBLE 265
#define BOOL 266
#define CHAR 267
#define NUL 268
#define FOR 269
#define WHILE 270
#define DO 271
#define IF 272
#define ELSE 273
#define SWITCH 274
#define RETURN 275
#define BREAK 276
#define CONTINUE 277
#define CONST 278
#define STRUCT 279
#define TRUE 280
#define FALSE 281
#define CASE 282
#define DEFAULT 283
#define PLUS2 284
#define MINUS2 285
#define MUL 286
#define DIV 287
#define MOD 288
#define PLUS 289
#define MINUS 290
#define AND2 291
#define OR2 292
#define N 293
#define NEQ 294
#define SLT 295
#define BLT 296
#define SLTE 297
#define BLTE 298
#define EE 299
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    0,    9,    9,   11,   13,    3,   15,    2,    4,
    4,    7,   17,   18,   18,   19,   19,   19,   19,   16,
   16,   22,   22,   22,    6,   23,   23,   21,   21,    1,
    1,   14,   14,   14,   14,   14,   27,   28,   26,   10,
   10,   29,   29,   29,   29,   29,   29,   30,   25,   25,
   31,   37,   37,   38,   38,   40,   40,   41,   41,   39,
   12,   12,   32,   32,   33,   42,   42,   34,   34,   35,
   35,   35,   35,   36,   43,   43,   44,   44,   45,   45,
   46,   46,   46,   46,   46,   46,   46,   47,   47,   47,
   48,   48,   48,   48,   49,   49,   50,   50,   50,    5,
    5,    5,    5,    5,    5,    5,    5,    5,    5,    5,
   51,   51,   24,   24,   20,   52,   52,   53,   53,   54,
   54,   55,   55,   55,   55,   55,   55,   55,   56,   56,
   56,   57,   57,   57,   57,   58,   58,   59,   59,   59,
    8,    8,    8,    8,    8,    8,    8,    8,    8,
};
static const short yylen[] = {                            2,
    1,    2,    1,    1,    0,    0,    7,    0,    6,    1,
    1,    2,    3,    1,    3,    1,    1,    3,    3,    1,
    3,    2,    2,    0,    2,    3,    4,    2,    3,    1,
    2,    1,    1,    1,    1,    1,    0,    0,    6,    0,
    2,    1,    1,    1,    1,    1,    1,    4,    3,    4,
    7,    1,    2,    1,    2,    4,    4,    0,    2,    3,
    0,    2,    5,    7,    7,    1,    2,    5,    7,    2,
    2,    2,    3,    1,    1,    3,    1,    3,    1,    2,
    1,    3,    3,    3,    3,    3,    3,    1,    3,    3,
    1,    3,    3,    3,    1,    2,    1,    2,    2,    1,
    1,    1,    1,    1,    1,    1,    1,    3,    3,    4,
    1,    3,    1,    3,    1,    1,    3,    1,    3,    1,
    2,    1,    3,    3,    3,    3,    3,    3,    1,    3,
    3,    1,    3,    3,    3,    1,    2,    1,    2,    2,
    1,    1,    1,    1,    1,    1,    1,    1,    3,
};
static const short yydefred[] = {                         0,
   36,   32,   35,   34,   33,    0,    0,    3,    4,   10,
    1,    0,   11,    2,   12,    5,    0,    0,    0,   14,
   40,    0,    0,    0,    0,    0,   13,    0,    0,    0,
  142,  143,  145,  144,  146,  147,  148,    0,    0,    0,
  141,    0,   18,    0,    0,  118,    0,    0,    0,  132,
  136,    0,    0,    0,    0,   19,    0,   15,    0,   41,
   61,    0,    0,    0,    0,  101,  102,  104,  103,  105,
  106,  107,    0,  100,    0,  137,    0,  139,  140,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   26,    0,    0,   20,    0,   28,  113,    0,
    0,    0,    0,    0,    0,    0,   77,    0,    0,    0,
   91,   95,    0,  149,    0,    0,   98,   99,    0,  119,
    0,    0,    0,    0,    0,    0,    0,    0,  133,  134,
  135,    0,   23,    9,    0,   27,   29,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    7,    0,   62,   42,
   43,   44,   45,   46,   47,   96,    0,   49,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  109,  111,    0,  108,   21,  114,    0,    0,
   37,    0,    0,    0,   72,    0,   71,   70,    0,    0,
   78,    0,    0,    0,    0,    0,    0,    0,    0,   92,
   93,   94,   50,  110,    0,   66,    0,    0,    0,   40,
    0,    0,    0,   73,    0,  112,   67,    0,    0,    0,
    0,    0,    0,   48,    0,   63,   61,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   54,   65,   39,
   64,   69,    0,    0,   51,    0,   53,   55,   58,   58,
   58,    0,    0,    0,   59,
};
static const short yydgoto[] = {                          6,
   74,    7,    8,    9,   75,   18,   10,   42,   11,   29,
   21,  101,   61,   12,   24,   95,   13,   19,   20,   43,
   56,   96,   25,  100,   63,  182,  210,  227,  255,  150,
  151,  152,  153,  154,  155,  207,  236,  237,  247,  238,
  252,  208,  105,  106,  107,  108,  109,  110,  111,  112,
  175,   44,   45,   46,   47,   48,   49,   50,   51,
};
static const short yysindex[] = {                       219,
    0,    0,    0,    0,    0,  219,  -57,    0,    0,    0,
    0, -246,    0,    0,    0,    0,  -51,  -46,  -20,    0,
    0,  340, -227,   -3,  -42,  -60,    0, -177,  219,   -1,
    0,    0,    0,    0,    0,    0,    0,  340,  377,  564,
    0, -187,    0, -219, -190,    0,  -66, -174, -161,    0,
    0,   11,  219, -150,  295,    0,  -51,    0,   53,    0,
    0,  527,   27,   79,  -27,    0,    0,    0,    0,    0,
    0,    0,  527,    0, -162,    0,  -66,    0,    0,  340,
  340,  564,  564,  564,  564,  564,  564,  564,  564,  564,
  564,  564,    0, -123,  -12,    0,   44,    0,    0,  -30,
  434,  377,  570,   49, -142, -132,    0,  223, -145, -156,
    0,    0,  527,    0,  510,  122,    0,    0, -190,    0,
 -174, -174, -174, -174, -174, -174, -161, -161,    0,    0,
    0,   75,    0,    0,  219,    0,    0,  340,  129,  132,
   68,  141,  160,  333,  142,  146,    0,  147,    0,    0,
    0,    0,    0,    0,    0,    0,  223,    0,  527,  527,
  570,  570,  570,  570,  570,  570,  570,  570,  570,  570,
  570,  114,    0,    0,   15,    0,    0,    0,  521,  527,
    0,  -61,  527,  -47,    0,  153,    0,    0,  527, -132,
    0, -145, -145, -145, -145, -145, -145, -156, -156,    0,
    0,    0,    0,    0,  527,    0,  154,  521,  174,    0,
  177,  179,  182,    0,  159,    0,    0,  527,   68,  219,
  527,   68,  101,    0,  184,    0,    0,  185,  -39,  -44,
   68,  596,  176,   68, -184,  115, -135,    0,    0,    0,
    0,    0,  181,  183,    0,  259,    0,    0,    0,    0,
    0,  371,  371,  371,    0,
};
static const short yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    2,    1,    0,    0,
    0,    0,    0,    0,  -11,    0,    0,    0,  667,  -25,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   24,    0,  -32,   70,    0,  -16,  102,   35,    0,
    0,    0,   37,    0,    0,    0,   13,    0,    0,    0,
    0,    0,  -41,    0,   -6,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   10,    0,  482,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -18,   48,    0,    3,  111,   47,
    0,    0,    0,    0,    0,    0,    0,    0,  457,    0,
  127,  143,  152,  162,  178,  370,   58,   69,    0,    0,
    0,   41,    0,    0,   37,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  121,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  123,
    0,  386,  421,  437,  446,  456,  465,   80,   92,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  688,
    0,    0,    0,    0,    0,    0,    0,    0,  633,    0,
    0,    0,    0,    0,    0,    0,  117,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -108, -104,  203,    0,
};
static const short yygindex[] = {                         0,
  797,  -28,    0,  -23,    0,  257,    0,    0,  230,  175,
    0,  168,    0,  -49,    0,    0,    0,    0,  376,  -33,
    0,  281,    0,    0,    0, -164,    0,    0,  -94,    0,
    0,    0,    0,    0,    0,  471,    0,    0,    0,  191,
  -97,  224,    0,  272,  273,  349,  407,    9,  -13,  -31,
    0,    0,  356,  374,  423,  588,  110,   98,    0,
};
#define YYTABLESIZE 1051
static const short yytable[] = {                         31,
   59,   15,   31,   94,   64,   60,  149,   76,  115,   22,
   17,  115,  115,  138,   26,   30,   56,   31,   30,   31,
   57,   99,   74,   28,  120,   74,  115,  120,  134,   25,
   52,  135,   25,   30,   30,   30,   53,   30,   27,   23,
   74,    8,  120,   79,   17,   16,   79,   25,   54,   25,
   97,   31,   30,   97,  226,  204,   16,  229,  205,   17,
   16,   79,   55,   62,  138,   16,  239,  138,   97,  242,
  156,   16,   80,  243,   74,  129,  244,   24,  129,   57,
   24,   22,  138,   31,   22,   94,   30,   88,   75,   62,
   88,   75,  115,  129,  137,   79,   78,   79,  130,   30,
   81,  130,   97,   93,  178,   88,   75,   97,  120,  131,
  116,   15,  131,  116,   88,   89,  130,  113,   30,  114,
   89,  117,  118,   89,   90,   91,   92,  131,  116,  169,
  170,  171,   90,  132,   97,   90,  136,  149,   89,   88,
   75,  158,  122,  167,  168,  122,  235,  246,  138,  159,
   90,   81,  253,  254,   81,  200,  201,  202,  160,  129,
  122,   80,  176,   76,   80,   23,   76,  128,  179,   81,
  128,  180,   89,   56,   56,  198,  199,   57,   57,   80,
  183,   76,  130,  123,   90,  128,  123,  129,  130,  131,
  181,   59,  127,  131,  116,  127,   60,  127,  128,  184,
  187,  123,  124,   81,  188,  124,  203,  189,  211,  213,
  127,  214,  217,   80,  219,   76,  221,  224,  126,  222,
  124,  126,  223,  230,  231,  233,  122,   82,   83,   84,
   85,   86,   87,  234,  241,   14,  126,  235,  249,  245,
  250,   52,   31,   31,   31,   31,   31,   31,   31,   31,
   31,  128,   31,   31,   31,   31,   31,   31,   30,   30,
   30,   30,   30,   30,   30,   30,   30,  123,   30,   30,
   30,   30,   30,   30,  120,  120,  127,   30,   30,   30,
   30,   30,   30,   30,   30,   30,  124,   30,   30,   30,
   30,   30,   30,   79,   79,   97,   97,   97,   97,   97,
   97,   97,  126,   97,   97,   97,   97,   97,   97,  138,
  138,  138,  138,  138,  138,  138,  251,  138,  138,  138,
  138,  138,  138,  129,  129,  129,  129,   60,  129,  129,
  129,  129,  129,  129,   38,   88,   88,   88,   88,   75,
   88,   88,   88,   88,   88,   88,  130,  130,  130,  130,
  133,  130,  130,  130,  130,  130,  130,  131,  131,  131,
  131,  116,  131,  131,  131,  131,  131,  131,   89,   89,
   89,   89,   73,   89,   89,   89,   89,   89,   89,   38,
   90,   90,   90,   90,  220,   90,   90,   90,   90,   90,
   90,  185,  122,  122,  232,  122,  122,  122,  122,  122,
  122,   81,   81,   58,   81,   81,   81,   81,   81,   81,
  125,   80,   80,  125,   76,  177,   73,  128,  128,   98,
  128,  128,  128,  128,  128,  128,   87,  248,  125,   87,
  190,  218,  191,  123,  123,  119,  123,  123,  123,  123,
  123,  123,  127,  127,   87,  127,  127,  127,  127,  127,
  127,  157,  124,  124,  120,  124,  124,  124,  124,  124,
  124,   82,   77,    0,   82,    0,    0,    0,  126,  126,
    0,  126,  126,  126,  126,  126,  126,   86,   87,   82,
   86,    1,    2,    3,    4,    5,   83,    0,    0,   83,
    0,    0,    0,    0,  125,   86,   85,  117,    0,   85,
  117,    0,    0,    0,   83,   84,    0,    0,   84,    0,
    0,    0,    0,   82,   85,  117,  161,  162,  163,  164,
  165,  166,  121,   84,    0,  121,    0,    0,    0,   86,
    0,    0,  104,    0,    0,    0,    0,    0,   83,    0,
  121,    0,    0,  116,    0,    0,    0,    0,   85,   73,
  173,   30,   31,   32,   33,   34,   35,   84,  147,    0,
   73,    0,    0,    0,    0,    0,   73,  192,  193,  194,
  195,  196,  197,    0,   36,   37,    0,    0,    0,  206,
    0,  117,    0,  172,   39,  174,    0,   40,    0,   65,
   66,   67,   68,   69,   70,    0,   30,   31,   32,   33,
   34,   35,    0,   38,    0,    0,  121,    0,    0,   73,
    0,    0,   71,   72,  186,    0,    0,    0,    0,   36,
   37,    0,  102,    0,    0,  103,    0,   30,    0,   39,
    0,    0,   40,   65,   66,   67,   68,   69,   70,  139,
  140,  141,  142,    0,  143,  144,  145,  146,    0,    0,
  209,    0,    0,  212,    0,    0,   71,   72,    0,  215,
  125,  125,    0,  125,  125,  125,  125,  125,  125,  121,
  122,  123,  124,  125,  126,  216,   87,   87,    0,   87,
   87,   87,   87,   87,   87,    0,    0,    0,  225,    0,
   30,  228,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  139,  140,  141,  142,    0,  143,  144,  145,
  146,   82,   82,    0,   82,   82,   82,   82,   82,   82,
  240,    0,    0,    0,    0,    0,    0,   86,   86,    0,
   86,   86,   86,   86,   86,   86,   83,   83,    0,   83,
   83,   83,   83,   83,   83,    0,   85,   85,  117,   85,
   85,   85,   85,   85,   85,   84,   84,   68,   84,   84,
   84,   84,   84,   84,    0,    0,   65,   66,   67,   68,
   69,   70,  121,  121,    0,    0,    0,   65,   66,   67,
   68,   69,   70,   65,   66,   67,   68,   69,   70,   71,
   72,    6,    0,    0,    0,    0,    0,    0,    0,  102,
   71,   72,  103,    0,    0,    0,   71,   72,    0,    0,
  102,    0,   38,  103,    0,    0,  102,    0,   41,  103,
   30,   31,   32,   33,   34,   35,   65,   66,   67,   68,
   69,   70,    0,    0,   41,    0,   41,    0,    0,    0,
    0,    0,    0,   36,   37,    0,    0,    0,    0,   71,
   72,   41,   30,   39,    0,    0,    0,    0,    0,  102,
    0,    0,    0,    0,  139,  140,  141,  142,    0,  143,
  144,  145,  146,    0,    0,    0,   41,   41,   41,   41,
   41,   41,   41,   41,   41,   41,   41,   41,   41,   68,
    0,    0,    0,    0,    0,    0,    0,  148,    0,    0,
    0,   68,   68,   68,   68,    0,   68,   68,   68,   68,
    0,    0,    0,    0,   68,   68,    0,    0,    0,    0,
    0,    0,    0,    6,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   41,    6,    6,    6,    6,    0,
    6,    6,    6,    6,   38,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   38,   38,   38,   38,
    0,   38,   38,   38,   38,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  148,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  148,  148,
  148,
};
static const short yycheck[] = {                         41,
   29,   59,   44,   53,   38,   29,  101,   39,   41,   61,
  257,   44,   40,   44,   61,   41,  125,   59,   44,   61,
  125,   55,   41,   44,   41,   44,   59,   44,   41,   41,
  258,   44,   44,   59,   41,   61,   40,   44,   59,   91,
   59,   40,   59,   41,   44,   44,   44,   59,   91,   61,
   41,   93,   59,   44,  219,   41,   44,  222,   44,   59,
   59,   59,  123,   91,   41,  123,  231,   44,   59,  234,
  102,   59,  292,  258,   93,   41,  261,   41,   44,  257,
   44,   41,   59,  125,   44,  135,   93,   41,   41,   91,
   44,   44,  125,   59,  125,   93,  284,  285,   41,  125,
  291,   44,   93,   93,  138,   59,   59,  258,  125,   41,
   41,   59,   44,   44,  289,  290,   59,   91,  125,   41,
   41,  284,  285,   44,  286,  287,  288,   59,   59,  286,
  287,  288,   41,  257,  125,   44,   93,  232,   59,   93,
   93,   93,   41,  289,  290,   44,  282,  283,  125,  292,
   59,   41,  250,  251,   44,  169,  170,  171,  291,  125,
   59,   41,   41,   41,   44,   91,   44,   41,   40,   59,
   44,   40,   93,  282,  283,  167,  168,  282,  283,   59,
   40,   59,  125,   41,   93,   59,   44,   90,   91,   92,
  123,  220,   41,  125,  125,   44,  220,   88,   89,   40,
   59,   59,   41,   93,   59,   44,   93,   61,  270,  257,
   59,   59,   59,   93,   41,   93,   40,   59,   41,   41,
   59,   44,   41,  123,   41,   41,  125,  294,  295,  296,
  297,  298,  299,  273,   59,    6,   59,  282,   58,  125,
   58,  125,  284,  285,  286,  287,  288,  289,  290,  291,
  292,  125,  294,  295,  296,  297,  298,  299,  284,  285,
  286,  287,  288,  289,  290,  291,  292,  125,  294,  295,
  296,  297,  298,  299,  291,  292,  125,  284,  285,  286,
  287,  288,  289,  290,  291,  292,  125,  294,  295,  296,
  297,  298,  299,  291,  292,  286,  287,  288,  289,  290,
  291,  292,  125,  294,  295,  296,  297,  298,  299,  286,
  287,  288,  289,  290,  291,  292,   58,  294,  295,  296,
  297,  298,  299,  289,  290,  291,  292,  125,  294,  295,
  296,  297,  298,  299,   40,  289,  290,  291,  292,  292,
  294,  295,  296,  297,  298,  299,  289,  290,  291,  292,
   94,  294,  295,  296,  297,  298,  299,  289,  290,  291,
  292,  292,  294,  295,  296,  297,  298,  299,  289,  290,
  291,  292,   40,  294,  295,  296,  297,  298,  299,   40,
  289,  290,  291,  292,  210,  294,  295,  296,  297,  298,
  299,   59,  291,  292,  227,  294,  295,  296,  297,  298,
  299,  291,  292,   28,  294,  295,  296,  297,  298,  299,
   41,  291,  292,   44,  292,  135,   40,  291,  292,  125,
  294,  295,  296,  297,  298,  299,   41,  237,   59,   44,
  159,  208,  160,  291,  292,   80,  294,  295,  296,  297,
  298,  299,  291,  292,   59,  294,  295,  296,  297,  298,
  299,  103,  291,  292,   81,  294,  295,  296,  297,  298,
  299,   41,   40,   -1,   44,   -1,   -1,   -1,  291,  292,
   -1,  294,  295,  296,  297,  298,  299,   41,   93,   59,
   44,  263,  264,  265,  266,  267,   41,   -1,   -1,   44,
   -1,   -1,   -1,   -1,  125,   59,   41,   41,   -1,   44,
   44,   -1,   -1,   -1,   59,   41,   -1,   -1,   44,   -1,
   -1,   -1,   -1,   93,   59,   59,  294,  295,  296,  297,
  298,  299,   41,   59,   -1,   44,   -1,   -1,   -1,   93,
   -1,   -1,   62,   -1,   -1,   -1,   -1,   -1,   93,   -1,
   59,   -1,   -1,   73,   -1,   -1,   -1,   -1,   93,   40,
   41,  257,  258,  259,  260,  261,  262,   93,  125,   -1,
   40,   -1,   -1,   -1,   -1,   -1,   40,  161,  162,  163,
  164,  165,  166,   -1,  280,  281,   -1,   -1,   -1,   59,
   -1,  125,   -1,  113,  290,  115,   -1,  293,   -1,  257,
  258,  259,  260,  261,  262,   -1,  257,  258,  259,  260,
  261,  262,   -1,   40,   -1,   -1,  125,   -1,   -1,   40,
   -1,   -1,  280,  281,  144,   -1,   -1,   -1,   -1,  280,
  281,   -1,  290,   -1,   -1,  293,   -1,  257,   -1,  290,
   -1,   -1,  293,  257,  258,  259,  260,  261,  262,  269,
  270,  271,  272,   -1,  274,  275,  276,  277,   -1,   -1,
  180,   -1,   -1,  183,   -1,   -1,  280,  281,   -1,  189,
  291,  292,   -1,  294,  295,  296,  297,  298,  299,   82,
   83,   84,   85,   86,   87,  205,  291,  292,   -1,  294,
  295,  296,  297,  298,  299,   -1,   -1,   -1,  218,   -1,
  257,  221,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  269,  270,  271,  272,   -1,  274,  275,  276,
  277,  291,  292,   -1,  294,  295,  296,  297,  298,  299,
  125,   -1,   -1,   -1,   -1,   -1,   -1,  291,  292,   -1,
  294,  295,  296,  297,  298,  299,  291,  292,   -1,  294,
  295,  296,  297,  298,  299,   -1,  291,  292,  292,  294,
  295,  296,  297,  298,  299,  291,  292,  125,  294,  295,
  296,  297,  298,  299,   -1,   -1,  257,  258,  259,  260,
  261,  262,  291,  292,   -1,   -1,   -1,  257,  258,  259,
  260,  261,  262,  257,  258,  259,  260,  261,  262,  280,
  281,  125,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  290,
  280,  281,  293,   -1,   -1,   -1,  280,  281,   -1,   -1,
  290,   -1,  125,  293,   -1,   -1,  290,   -1,   22,  293,
  257,  258,  259,  260,  261,  262,  257,  258,  259,  260,
  261,  262,   -1,   -1,   38,   -1,   40,   -1,   -1,   -1,
   -1,   -1,   -1,  280,  281,   -1,   -1,   -1,   -1,  280,
  281,   55,  257,  290,   -1,   -1,   -1,   -1,   -1,  290,
   -1,   -1,   -1,   -1,  269,  270,  271,  272,   -1,  274,
  275,  276,  277,   -1,   -1,   -1,   80,   81,   82,   83,
   84,   85,   86,   87,   88,   89,   90,   91,   92,  257,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  101,   -1,   -1,
   -1,  269,  270,  271,  272,   -1,  274,  275,  276,  277,
   -1,   -1,   -1,   -1,  282,  283,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  257,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  138,  269,  270,  271,  272,   -1,
  274,  275,  276,  277,  257,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  269,  270,  271,  272,
   -1,  274,  275,  276,  277,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  232,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  252,  253,
  254,
};
#define YYFINAL 6
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 299
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? (YYMAXTOKEN + 1) : (a))
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,"'&'",0,"'('","')'",0,0,"','",0,0,0,0,0,0,0,0,0,0,0,0,0,"':'","';'",0,
"'='",0,"'?'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,
"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,"IDENTIFIER","INT_P","DOUBLE_P","SCIEN_P","CHAR_P","STR_P",
"VOID","INT","DOUBLE","BOOL","CHAR","NUL","FOR","WHILE","DO","IF","ELSE",
"SWITCH","RETURN","BREAK","CONTINUE","CONST","STRUCT","TRUE","FALSE","CASE",
"DEFAULT","PLUS2","MINUS2","MUL","DIV","MOD","PLUS","MINUS","AND2","OR2","N",
"NEQ","SLT","BLT","SLTE","BLTE","EE","illegal-symbol",
};
static const char *yyrule[] = {
"$accept : Program",
"Program : Pre_Dec",
"Program : Program Pre_Dec",
"Pre_Dec : Func_Def",
"Pre_Dec : Dec",
"$$1 :",
"$$2 :",
"Func_Def : Func_Dec '{' $$1 Dec_List $$2 Statement_List '}'",
"$$3 :",
"Func_Dec : Re_Type_Spec IDENTIFIER $$3 '(' Para_List ')'",
"Dec : Func_Dec1",
"Dec : Normal_Dec",
"Func_Dec1 : Func_Dec ';'",
"Normal_Dec : Re_Type_Spec Normal_Dec_List ';'",
"Normal_Dec_List : Normal_Dec_One",
"Normal_Dec_List : Normal_Dec_List ',' Normal_Dec_One",
"Normal_Dec_One : IDENTIFIER",
"Normal_Dec_One : Array",
"Normal_Dec_One : IDENTIFIER '=' Init_Exp",
"Normal_Dec_One : Array '=' Array_Cont",
"Para_List : Para",
"Para_List : Para_List ',' Para",
"Para : Re_Type_Spec IDENTIFIER",
"Para : Re_Type_Spec Array",
"Para :",
"Array : IDENTIFIER Array_P",
"Array_P : '[' INT_P ']'",
"Array_P : Array_P '[' INT_P ']'",
"Array_Cont : '{' '}'",
"Array_Cont : '{' Init_Exp_List '}'",
"Var : IDENTIFIER",
"Var : IDENTIFIER Array_Exp",
"Re_Type_Spec : INT",
"Re_Type_Spec : CHAR",
"Re_Type_Spec : BOOL",
"Re_Type_Spec : DOUBLE",
"Re_Type_Spec : VOID",
"$$4 :",
"$$5 :",
"Main_Content_Func : '{' $$4 Dec_List $$5 Statement_List '}'",
"Dec_List :",
"Dec_List : Dec_List Dec",
"Statement : Simple_S",
"Statement : Switch_S",
"Statement : While_S",
"Statement : For_S",
"Statement : IF_S",
"Statement : End_S",
"Simple_S : Var '=' Exp ';'",
"Array_Exp : '[' Exp ']'",
"Array_Exp : Array_Exp '[' Exp ']'",
"Switch_S : SWITCH '(' IDENTIFIER ')' '{' Switch_Cont '}'",
"Switch_Cont : Case_L",
"Switch_Cont : Case_L Default_Cont",
"Case_L : Case_One",
"Case_L : Case_L Case_One",
"Case_One : CASE INT_P ':' Statement_Many",
"Case_One : CASE CHAR_P ':' Statement_Many",
"Statement_Many :",
"Statement_Many : Statement_Many Statement",
"Default_Cont : DEFAULT ':' Statement_Many",
"Statement_List :",
"Statement_List : Statement_List Statement",
"While_S : WHILE '(' Exp ')' Main_Content_Func",
"While_S : DO Main_Content_Func WHILE '(' Exp ')' ';'",
"For_S : FOR '(' For_Exp For_Exp Exp ')' Main_Content_Func",
"For_Exp : ';'",
"For_Exp : Exp ';'",
"IF_S : IF '(' Exp ')' Main_Content_Func",
"IF_S : IF '(' Exp ')' Main_Content_Func ELSE Main_Content_Func",
"End_S : CONTINUE ';'",
"End_S : BREAK ';'",
"End_S : RETURN ';'",
"End_S : RETURN Exp ';'",
"Exp : Log_Or_Exp",
"Log_Or_Exp : Log_And_Exp",
"Log_Or_Exp : Log_Or_Exp OR2 Log_And_Exp",
"Log_And_Exp : Log_Not_Exp",
"Log_And_Exp : Log_And_Exp AND2 Log_Not_Exp",
"Log_Not_Exp : Com_Exp",
"Log_Not_Exp : N Com_Exp",
"Com_Exp : Add_Min_Exp",
"Com_Exp : Com_Exp SLT Add_Min_Exp",
"Com_Exp : Com_Exp SLTE Add_Min_Exp",
"Com_Exp : Com_Exp EE Add_Min_Exp",
"Com_Exp : Com_Exp BLTE Add_Min_Exp",
"Com_Exp : Com_Exp BLT Add_Min_Exp",
"Com_Exp : Com_Exp NEQ Add_Min_Exp",
"Add_Min_Exp : Mul_Exp",
"Add_Min_Exp : Add_Min_Exp PLUS Mul_Exp",
"Add_Min_Exp : Add_Min_Exp MINUS Mul_Exp",
"Mul_Exp : Unary_Exp",
"Mul_Exp : Mul_Exp MUL Unary_Exp",
"Mul_Exp : Mul_Exp DIV Unary_Exp",
"Mul_Exp : Mul_Exp MOD Unary_Exp",
"Unary_Exp : Postfix_Exp",
"Unary_Exp : MINUS Postfix_Exp",
"Postfix_Exp : Left_Exp",
"Postfix_Exp : Left_Exp PLUS2",
"Postfix_Exp : Left_Exp MINUS2",
"Left_Exp : Var",
"Left_Exp : INT_P",
"Left_Exp : DOUBLE_P",
"Left_Exp : CHAR_P",
"Left_Exp : SCIEN_P",
"Left_Exp : STR_P",
"Left_Exp : TRUE",
"Left_Exp : FALSE",
"Left_Exp : '(' Exp ')'",
"Left_Exp : IDENTIFIER '(' ')'",
"Left_Exp : IDENTIFIER '(' Exp_List ')'",
"Exp_List : Exp",
"Exp_List : Exp_List ',' Exp",
"Init_Exp_List : Init_Exp",
"Init_Exp_List : Init_Exp_List ',' Init_Exp",
"Init_Exp : Init_Log_Or_Exp",
"Init_Log_Or_Exp : Init_Log_And_Exp",
"Init_Log_Or_Exp : Init_Log_Or_Exp OR2 Init_Log_And_Exp",
"Init_Log_And_Exp : Init_Log_Not_Exp",
"Init_Log_And_Exp : Init_Log_And_Exp AND2 Init_Log_Not_Exp",
"Init_Log_Not_Exp : Init_Com_Exp",
"Init_Log_Not_Exp : N Init_Com_Exp",
"Init_Com_Exp : Init_Add_Min_Exp",
"Init_Com_Exp : Init_Com_Exp SLT Init_Add_Min_Exp",
"Init_Com_Exp : Init_Com_Exp SLTE Init_Add_Min_Exp",
"Init_Com_Exp : Init_Com_Exp EE Init_Add_Min_Exp",
"Init_Com_Exp : Init_Com_Exp BLTE Init_Add_Min_Exp",
"Init_Com_Exp : Init_Com_Exp BLT Init_Add_Min_Exp",
"Init_Com_Exp : Init_Com_Exp NEQ Init_Add_Min_Exp",
"Init_Add_Min_Exp : Init_Mul_Exp",
"Init_Add_Min_Exp : Init_Add_Min_Exp PLUS Init_Mul_Exp",
"Init_Add_Min_Exp : Init_Add_Min_Exp MINUS Init_Mul_Exp",
"Init_Mul_Exp : Init_Unary_Exp",
"Init_Mul_Exp : Init_Mul_Exp MUL Init_Unary_Exp",
"Init_Mul_Exp : Init_Mul_Exp DIV Init_Unary_Exp",
"Init_Mul_Exp : Init_Mul_Exp MOD Init_Unary_Exp",
"Init_Unary_Exp : Init_Postfix_Exp",
"Init_Unary_Exp : MINUS Postfix_Exp",
"Init_Postfix_Exp : Init_Left_Exp",
"Init_Postfix_Exp : Init_Left_Exp PLUS2",
"Init_Postfix_Exp : Init_Left_Exp MINUS2",
"Init_Left_Exp : Var",
"Init_Left_Exp : INT_P",
"Init_Left_Exp : DOUBLE_P",
"Init_Left_Exp : CHAR_P",
"Init_Left_Exp : SCIEN_P",
"Init_Left_Exp : STR_P",
"Init_Left_Exp : TRUE",
"Init_Left_Exp : FALSE",
"Init_Left_Exp : '(' Init_Exp ')'",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 454 "parser.y"


int main(){

  init_symbol_table();
  
  if( (f_asm = fopen("assembly", "w")) == NULL){
    fprintf(stderr, "Can not open the file %s for writing.\n", "assembly");
  }
  
	yyparse();
  printTable();
	if(functionNum == 0){
		num_lines++;
		yyerror(NULL);
	}
	printf("No syntax error!\n");
  fclose(f_asm);
	return 0;
}

int yyerror(char *msg){
	fprintf( stderr, "*** Error at line %d: %s\n", num_lines, str );
	fprintf( stderr, "\n" );
	fprintf( stderr, "Unmatched token: %s\n", yytext );
	fprintf( stderr, "*** syntax error\n");
	exit(-1);

}
#line 715 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 3:
#line 51 "parser.y"
	{functionNum++;}
break;
case 5:
#line 57 "parser.y"
	{
            cur_scope++;
            set_scope_and_offset_of_param(yystack.l_mark[-1].ident);
            LocalOffset = 0;
          }
break;
case 6:
#line 63 "parser.y"
	{
            set_local_vars(yystack.l_mark[-3].ident);
          }
break;
case 7:
#line 67 "parser.y"
	{
            /*pop_up_symbol(cur_scope);*/
            cur_scope--;
          }
break;
case 8:
#line 72 "parser.y"
	{ install_symbol(yystack.l_mark[0].ident); }
break;
case 9:
#line 73 "parser.y"
	{ yyval.ident = yystack.l_mark[-4].ident; }
break;
case 10:
#line 76 "parser.y"
	{ yyval.ident = yystack.l_mark[0].ident; }
break;
case 11:
#line 77 "parser.y"
	{ yyval.ident = NULL; }
break;
case 16:
#line 93 "parser.y"
	{ install_symbol(yystack.l_mark[0].ident); }
break;
case 17:
#line 94 "parser.y"
	{ install_symbol(yystack.l_mark[0].ident); }
break;
case 18:
#line 96 "parser.y"
	{
            install_symbol(yystack.l_mark[-2].ident);
            int index = look_up_symbol(yystack.l_mark[-2].ident);
            table[index].offset = LocalOffset++;
            printf("ID = Init_Exp scope = %d, name = %s, cur_counter = %d, offset = %d\n", table[index].scope, table[index].name, cur_counter, table[index].offset);
            
            fprintf(f_asm, "    pop.s { $r0 }\n");
            fprintf(f_asm, "    swi $r0, [$sp+%d]\n", table[index].offset*4);
          
          
          
          }
break;
case 19:
#line 108 "parser.y"
	{ install_symbol(yystack.l_mark[-2].ident); }
break;
case 22:
#line 115 "parser.y"
	{ install_symbol(yystack.l_mark[0].ident); }
break;
case 23:
#line 116 "parser.y"
	{ install_symbol(yystack.l_mark[0].ident); }
break;
case 25:
#line 120 "parser.y"
	{ yyval.ident = yystack.l_mark[-1].ident; }
break;
case 30:
#line 131 "parser.y"
	{ yyval.ident = yystack.l_mark[0].ident; }
break;
case 31:
#line 132 "parser.y"
	{ yyval.ident = yystack.l_mark[-1].ident; }
break;
case 37:
#line 145 "parser.y"
	{
                      cur_scope++;
                      LocalOffset = 0;
                    }
break;
case 38:
#line 150 "parser.y"
	{
                      set_local_vars(yystack.l_mark[-2].charVal);
                    }
break;
case 39:
#line 154 "parser.y"
	{
                      /*pop_up_symbol(cur_scope);*/
                      cur_scope--;
                    }
break;
case 48:
#line 173 "parser.y"
	{
			int index = look_up_symbol(yystack.l_mark[-3].ident);

                         /* Load Expression to $r0 */
                         fprintf(f_asm, "    pop.s { $r0 }\n");
                         /* Store it to var */
                         fprintf(f_asm, "    swi $r0, [$sp+%d]\n",table[index].offset*4);
		
		}
break;
case 89:
#line 256 "parser.y"
	{
        fprintf(f_asm, "    pop.s { $r0 }\n");
        fprintf(f_asm, "    pop.s { $r1 }\n");
        fprintf(f_asm, "    add $r0, $r1, $r0\n");
        fprintf(f_asm, "    push.s { $r0 }\n");
      }
break;
case 90:
#line 263 "parser.y"
	{
        fprintf(f_asm, "    pop.s { $r0 }\n");
        fprintf(f_asm, "    pop.s { $r1 }\n");
        fprintf(f_asm, "    sub $r0, $r1, $r0\n");
        fprintf(f_asm, "    push.s { $r0 }\n");
      }
break;
case 92:
#line 273 "parser.y"
	{
        fprintf(f_asm, "    pop.s { $r0 }\n");
        fprintf(f_asm, "    pop.s { $r1 }\n");
        fprintf(f_asm, "    mul $r0, $r1, $r0\n");
        fprintf(f_asm, "    push.s { $r0 }\n");
      }
break;
case 93:
#line 280 "parser.y"
	{
        fprintf(f_asm, "    pop.s { $r2 }\n");
        fprintf(f_asm, "    pop.s { $r3 }\n");
        fprintf(f_asm, "    divsr $r0, $r1, $r3, $r2\n");
        fprintf(f_asm, "    push.s { $r0 }\n");
      }
break;
case 94:
#line 287 "parser.y"
	{
        fprintf(f_asm, "    pop.s { $r2 }\n");
        fprintf(f_asm, "    pop.s { $r3 }\n");
        fprintf(f_asm, "    divsr $r0, $r1, $r3, $r2\n");
        fprintf(f_asm, "    push.s { $r1 }\n");
      }
break;
case 100:
#line 304 "parser.y"
	{
            int index = look_up_symbol(yystack.l_mark[0].ident);
            
            switch(table[index].mode)
            {
              case ARGUMENT_MODE:
                fprintf(f_asm, "    lwi $r0, [$sp+%d]\n",table[index].offset*4);
               printf("ID = ARGU LLeft_Exp scope = %d, name = %s, cur_counter = %d, offset = %d\n", table[index].scope, table[index].name, cur_counter, table[index].offset);
                break;
              case LOCAL_MODE:
                fprintf(f_asm, "    lwi $r0, [$sp+%d]\n",table[index].offset*4);
               printf("ID = LOCAL LLeft_Exp scope = %d, name = %s, cur_counter = %d, offset = %d\n", table[index].scope, table[index].name, cur_counter, table[index].offset);
                break;
                               
              }
              fprintf(f_asm, "    push.s { $r0 }\n");
          }
break;
case 101:
#line 322 "parser.y"
	{
       yyval.ident = NULL;
       fprintf(f_asm, "    movi $r0, %d\n", yystack.l_mark[0].intVal);
       fprintf(f_asm, "    push.s { $r0 }\n");
     }
break;
case 102:
#line 327 "parser.y"
	{ yyval.ident = NULL; }
break;
case 103:
#line 328 "parser.y"
	{ yyval.ident = NULL; }
break;
case 104:
#line 329 "parser.y"
	{ yyval.ident = NULL; }
break;
case 105:
#line 330 "parser.y"
	{ yyval.ident = NULL; }
break;
case 106:
#line 331 "parser.y"
	{ yyval.ident = NULL; }
break;
case 107:
#line 332 "parser.y"
	{ yyval.ident = NULL; }
break;
case 108:
#line 333 "parser.y"
	{ yyval.ident = NULL; }
break;
case 130:
#line 371 "parser.y"
	{
        fprintf(f_asm, "    pop.s { $r0 }\n");
        fprintf(f_asm, "    pop.s { $r1 }\n");
        fprintf(f_asm, "    add $r0, $r1, $r0\n");
        fprintf(f_asm, "    push.s { $r0 }\n");
      }
break;
case 131:
#line 378 "parser.y"
	{
        fprintf(f_asm, "    pop.s { $r0 }\n");
        fprintf(f_asm, "    pop.s { $r1 }\n");
        fprintf(f_asm, "    sub $r0, $r1, $r0\n");
        fprintf(f_asm, "    push.s { $r0 }\n");
      }
break;
case 133:
#line 388 "parser.y"
	{
        fprintf(f_asm, "    pop.s { $r0 }\n");
        fprintf(f_asm, "    pop.s { $r1 }\n");
        fprintf(f_asm, "    mul $r0, $r1, $r0\n");
        fprintf(f_asm, "    push.s { $r0 }\n");
      }
break;
case 134:
#line 395 "parser.y"
	{
        fprintf(f_asm, "    pop.s { $r2 }\n");
        fprintf(f_asm, "    pop.s { $r3 }\n");
        fprintf(f_asm, "    divsr $r0, $r1, $r3, $r2\n");
        fprintf(f_asm, "    push.s { $r0 }\n");
      }
break;
case 135:
#line 402 "parser.y"
	{
        fprintf(f_asm, "    pop.s { $r2 }\n");
        fprintf(f_asm, "    pop.s { $r3 }\n");
        fprintf(f_asm, "    divsr $r0, $r1, $r3, $r2\n");
        fprintf(f_asm, "    push.s { $r1 }\n");
      }
break;
case 141:
#line 419 "parser.y"
	{
            int index = look_up_symbol(yystack.l_mark[0].ident);
            
            switch(table[index].mode)
            {
              case ARGUMENT_MODE:
                fprintf(f_asm, "    lwi $r0, [$sp+%d]\n",table[index].offset*4);
                printf("Init_Left ARGU scope = %d, name = %s, cur_counter = %d, offset = %d\n", table[index].scope, table[index].name, cur_counter, table[index].offset);
                break;
              case LOCAL_MODE:
                fprintf(f_asm, "    lwi $r0, [$sp+%d]\n",table[index].offset*4);
               printf("Init_Left LOCAL scope = %d, name = %s, cur_counter = %d, offset = %d\n", table[index].scope, table[index].name, cur_counter, table[index].offset);
                break;
                               
              }
              fprintf(f_asm, "    push.s { $r0 }\n");
          }
break;
case 142:
#line 437 "parser.y"
	{
       yyval.ident = NULL;
       fprintf(f_asm, "    movi $r0, %d\n", yystack.l_mark[0].intVal);
       fprintf(f_asm, "    push.s { $r0 }\n");
     }
break;
case 143:
#line 442 "parser.y"
	{ yyval.ident = NULL; }
break;
case 144:
#line 443 "parser.y"
	{ yyval.ident = NULL; }
break;
case 145:
#line 444 "parser.y"
	{ yyval.ident = NULL; }
break;
case 146:
#line 445 "parser.y"
	{ yyval.ident = NULL; }
break;
case 147:
#line 446 "parser.y"
	{ yyval.ident = NULL; }
break;
case 148:
#line 447 "parser.y"
	{ yyval.ident = NULL; }
break;
case 149:
#line 448 "parser.y"
	{ yyval.ident = NULL; }
break;
#line 1239 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
