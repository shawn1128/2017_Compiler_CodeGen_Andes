%{

	#define paragraphComment 1
	#define lineComment 2
	#define SOURCEON 1
	#define SOURCEOFF 0
	#define TOKENON 1
	#define TOKENOFF 0

	#define KEYWORD_L 0
	#define IDENTIFIER_L 1
	#define OPERATOR_L 2
	#define PUNCTUATION_L 3
	#define INTEGER_L 4
	#define DOUBLE_L 5
	#define CHAR_L 6
	#define SCIENTIFIC_L 7
	#define STRING_L 8

	#include <stdio.h>
	#include "y.tab.h"

	FILE *fp;
	int num_lines = 0, num_chars = 0;
	char str[300];
	char tmp_str[300];
	char keyName[9][10] = {"key", "id", "op", "punc", "integer", "double",
			     "char", "sci", "string"};
	int commentType, sourceon = 1, tokenon = 1;
	int tokenType;

	int yywrap();
	void print_line();
	void store_text();
	void print_token();
	void error_handling();
%}

%x COMMENT PRAGMA
%x DIGITALWRITE DELAY

SPACE [ \r\t\f\v]+
DIGIT [0-9]
DIGITS {DIGIT}+
ID [a-zA-Z_][a-zA-Z0-9_]*

D_NUM ({DIGITS}?"."{DIGITS})|({DIGITS}".")
D_CHAR (f|F|l|L)
DOUBLE {D_NUM}{D_CHAR}?

L l|ll|L|LL
U u|U
INT_CHAR ({L}|{U}|{U}{L}|{L}{U})
INT {DIGIT}|([1-9]{DIGIT}*){INT_CHAR}?
SCIEN ({D_NUM}|{DIGITS})[Ee][+-]?{DIGITS}{L}?


KEY void|int|double|bool|char|null|for|while|do|if|else|switch|return|break|continue|const|true|false|struct|case|default|fclose|clearerr|feof|ferror|fflush|fgetpos|fopen|fread|freopen|fseek|fsetpos|ftell|fwrite|remove|rename|rewind|setbuf|setvbuf|tmpfile|tmpnam|fprintf|printf|sprintf|vfprintf|vprintf|vsprintf|fscanf|scanf|sscanf|fgetc|fgets|fputc|fputs|getc|getchar|gets|putc|putchar|puts|ungetc|perror 

OP "&"|"+"|"-"|"*"|"/"|"%"|"++"|"--"|"<"|"<="|">"|">="|"=="|"!="|"="|"&&"|"||"|"!" 
PUNC ":"|";"|","|"."|"["|"("|"{"|"]"|")"|"}"
CHAR "'"[0-9a-zA-Z \!\"\#\$\%\&\'\(\)\*\+\,\-\.\/\:\;\<\=\>\?\@\[\]\^\\\_\`\{\|\}\~]"'"
STR \"((\\(n|t|\\|\"))|[^"\n])*\"

%%

"/*" {  store_text();
	commentType = paragraphComment;
	BEGIN(COMMENT);}
"//" {  store_text();
	commentType = lineComment;
	BEGIN(COMMENT);}

<COMMENT>[^*\n]*        {store_text();}/* eat anything that's not a '*' */
<COMMENT>"*"+[^*/\n]*   {store_text();}/* eat up '*'s not followed by '/'s */
<COMMENT>\n             { ++num_lines;
			  print_line();
			  if(commentType == lineComment){
				BEGIN(INITIAL);}
			}
<COMMENT>"*"+"/"        {if(commentType == paragraphComment){
				store_text();
				BEGIN(INITIAL);
			 }else{store_text();}
			}

#{SPACE}?pragma {store_text();
	   BEGIN(PRAGMA);}

<PRAGMA>{SPACE}source{SPACE}on {sourceon = SOURCEON;
				      store_text();
				      BEGIN(INITIAL);}
<PRAGMA>{SPACE}source{SPACE}off {sourceon = SOURCEOFF;
				        store_text();
				        BEGIN(INITIAL);}
<PRAGMA>{SPACE}token{SPACE}on {tokenon = TOKENON;
				     store_text();
				     BEGIN(INITIAL);}
<PRAGMA>{SPACE}token{SPACE}off {tokenon = TOKENOFF;
				     store_text();
				     BEGIN(INITIAL);}
<PRAGMA>. {store_text();
	   error_handling();}

"digitalWrite(" {
	BEGIN(DIGITALWRITE);
	}

<DIGITALWRITE>{INT} {
	int n = atoi(yytext);
	fprintf(f_asm, "    movi $r0, %d\n, n");
	}

<DIGITALWRITE>"LOW" {
	fprintf(f_asm, "    movi $r1, 0\n");
	}

<DIGITALWRITE>"HIGH" {
	fprintf(f_asm, "    movi $r1, 1\n");
	}
<DIGITALWRITE>");" {
	fprintf(f_asm, "    bal digitalWrite\n");
	BEGIN(INITIAL);
	}

"delay(" {
  BEGIN(DELAY);
  }
  
<DELAY>{INT} {
  int n = atoi(yytext);
  fprintf(f_asm, "    movi $r0, %d\n", n);
  }
  
<DELAY>");" {
  fprintf(f_asm, "    bal delay\n");
  BEGIN(INITIAL);
  }


\n {    ++num_lines; 
	print_line();}

{SPACE} {store_text();}



{INT} {tokenType = INTEGER_L;
		 store_text();
     print_token();
     yylval.intVal = atoi(yytext);
		 return INT_P;
		}

{DOUBLE} {tokenType = DOUBLE_L;
		     store_text();
		     print_token();
       sscanf(yytext, "%lf", &yylval.doubleVal);
			 return DOUBLE_P;}
{SCIEN} {tokenType = SCIENTIFIC_L;
	 store_text();
	 print_token();
   sscanf(yytext, "%lf", &yylval.doubleVal);
	 return SCIEN_P;}

{KEY}	{tokenType = KEYWORD_L;
	 store_text();
	 print_token();
	 if(strcmp(yytext, "void") == 0) return VOID;
	 if(strcmp(yytext, "int") == 0) return INT;
	 if(strcmp(yytext, "double") == 0) return DOUBLE;
     if(strcmp(yytext, "bool") == 0) return BOOL;
     if(strcmp(yytext, "char") == 0) return CHAR;
     if(strcmp(yytext, "null") == 0) return NUL;
     if(strcmp(yytext, "for") == 0) return FOR;
     if(strcmp(yytext, "while") == 0) return WHILE;
     if(strcmp(yytext, "do") == 0) return DO;
     if(strcmp(yytext, "if") == 0) return IF;
     if(strcmp(yytext, "else") == 0) return ELSE;
     if(strcmp(yytext, "switch") == 0) return SWITCH;
     if(strcmp(yytext, "return") == 0) return RETURN;
     if(strcmp(yytext, "break") == 0) return BREAK;
     if(strcmp(yytext, "continue") == 0) return CONTINUE;
     if(strcmp(yytext, "const") == 0) return CONST;
     if(strcmp(yytext, "struct") == 0) return STRUCT;
     if(strcmp(yytext, "true") == 0) return TRUE;
     if(strcmp(yytext, "false") == 0) return FALSE;
     if(strcmp(yytext, "case") == 0) return CASE;
     if(strcmp(yytext, "default") == 0) return DEFAULT; }

{ID} {tokenType = IDENTIFIER_L;
	store_text();
	print_token();
  yylval.ident = copys(yytext);
	return IDENTIFIER;}

{OP} {tokenType = OPERATOR_L;
	store_text();
	print_token();
	if(strcmp(yytext, "+") == 0) return PLUS;
	if(strcmp(yytext, "-") == 0) return MINUS;
	if(strcmp(yytext, "*") == 0) return MUL;
	if(strcmp(yytext, "/") == 0) return DIV;
	if(strcmp(yytext, "%") == 0) return MOD;
	if(strcmp(yytext, "++") == 0) return PLUS2;
	if(strcmp(yytext, "--") == 0) return MINUS2;
	if(strcmp(yytext, "<") == 0) return SLT;
	if(strcmp(yytext, "<=") == 0) return SLTE;
	if(strcmp(yytext, ">") == 0) return BLT;
	if(strcmp(yytext, ">=") == 0) return BLTE;
	if(strcmp(yytext, "==") == 0) return EE;
	if(strcmp(yytext, "!=") == 0) return NEQ;
	if(strcmp(yytext, "&&") == 0) return AND2;
	if(strcmp(yytext, "||") == 0) return OR2;
	if(strcmp(yytext, "!") == 0) return N;
	if(strcmp(yytext, "&") == 0) return '&';
	if(strcmp(yytext, "=") == 0) return '=';}


{PUNC} {tokenType = PUNCTUATION_L;
		 store_text();
		 print_token();
		 
		if(strcmp(yytext, ":") == 0) return ':';
        if(strcmp(yytext, ";") == 0) return ';';
        if(strcmp(yytext, ",") == 0) return ',';
        if(strcmp(yytext, ".") == 0) return '.';
        if(strcmp(yytext, "[") == 0) return '[';
        if(strcmp(yytext, "]") == 0) return ']';
        if(strcmp(yytext, "(") == 0) return '(';
        if(strcmp(yytext, ")") == 0) return ')';
        if(strcmp(yytext, "{") == 0) return '{';
        if(strcmp(yytext, "}") == 0) return '}';
        if(strcmp(yytext, "?") == 0) return '?';}


{CHAR}  {tokenType = CHAR_L;
	 store_text();
	 print_token();
   
   
   char str[1000];
   strcpy(str,yytext+1);
   str[yyleng-2] = 0;
        
   yylval.ident = copys(str);
	 return CHAR_P;}

{STR} { tokenType = STRING_L;
	store_text();
	print_token();
 
  char str[1000];
  strcpy(str,yytext+1);
  str[yyleng-2] = 0;
  yylval.ident = copys(str);
  
	return STR_P;
	}
. {store_text();
   error_handling();}


0/[0-9a-zA-Z] {store_text();
		error_handling();}


%%

/*int main(int argc, char* argv[]){
        
	yylex();
        return 0;


}*/

int yywrap(){
	return 1; /*end of file*/
}

void print_line(){
    if(sourceon == SOURCEON){
	//fprintf(fp,"%d:%s\n", num_lines, str);
	printf("%d:%s\n", num_lines, str);
    }
	memset(str, 0, strlen(str));
	num_chars = 0;
}

void store_text(){
	strcpy(str+num_chars, yytext);
	num_chars = num_chars + yyleng;
}

void print_token(){
    if(tokenon == TOKENON){
	if(tokenType == STRING_L){
		strcpy(tmp_str, yytext+1);
		tmp_str[yyleng-2] = 0;
		//fprintf(fp,"#%s:%s\n", keyName[tokenType], tmp_str);
        	printf("#%s:%s\n", keyName[tokenType], tmp_str);
	}else{
		//fprintf(fp,"#%s:%s\n", keyName[tokenType], yytext);
		printf("#%s:%s\n", keyName[tokenType], yytext);
	}
    }


}

void error_handling(){

	fprintf(stderr, "Error at line %d: %s\n", num_lines+1, yytext);
	exit(1);

}
