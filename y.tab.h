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
extern YYSTYPE yylval;
