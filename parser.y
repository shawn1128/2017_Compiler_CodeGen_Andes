%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "SymbolTable.h"
	extern int num_lines;
	extern char *yytext;
	extern char str[300];
	int functionNum = 0;
	int yyerror(char *msg);
 
  FILE *f_asm;

%}


%start Program

%token <ident> IDENTIFIER
%token INT_P DOUBLE_P SCIEN_P CHAR_P STR_P
%token <token> VOID INT DOUBLE BOOL CHAR NUL FOR WHILE DO IF ELSE SWITCH RETURN
%token <token> BREAK CONTINUE CONST STRUCT TRUE FALSE CASE DEFAULT

%token <charVal> ':' ';' '?' '=' '(' ')' '[' ']' '{' '}' '&'

%left <token> PLUS2 MINUS2 MUL DIV MOD PLUS MINUS
%left <token> AND2 OR2 N NEQ SLT BLT SLTE BLTE EE

%union {
         int token;
         int intVal;
         double doubleVal;
         char charVal;
         char *ident;
        }



%%

Program: Pre_Dec
		| Program Pre_Dec
		;

Pre_Dec:	Func_Def {functionNum++;}
		|	Dec
			;
Func_Def: Re_Type_Spec IDENTIFIER '(' ')' Main_Content_Func
		| Re_Type_Spec IDENTIFIER '(' Para_List ')' Main_Content_Func
		;
Dec: Func_Dec
	| Normal_Dec
	;
	
Func_Dec: Re_Type_Spec IDENTIFIER '(' ')' ';' 
	| Re_Type_Spec IDENTIFIER '(' Para_List ')' ';' 
	;


Normal_Dec: Re_Type_Spec Normal_Dec_List ';'
	;
	
Normal_Dec_List:  Normal_Dec_One
				| Normal_Dec_List ',' Normal_Dec_One
				;
Normal_Dec_One: IDENTIFIER { install_symbol($1); }
				| Array { //install_symbol($1); 
                }
				| IDENTIFIER '=' Exp
          {
            install_symbol($1);
            int index = look_up_symbol($1);
            table[index].offset = LocalOffset++;
            
            fprintf(f_asm, "    pop.s { $r0 }\n");
            fprintf(f_asm, "    swi $r0, [$sp+%d]\n", table[index].offset*4);
          
          
          
          }
				| Array '=' Array_Cont { //install_symbol($1); 
                                }
				;
				
Para_List: Para
		| Para_List ',' Para
		;
		
Para: Re_Type_Spec IDENTIFIER { install_symbol($2); }
	| Re_Type_Spec Array        { //install_symbol($2); 
                               }
	;
	
Array: IDENTIFIER Array_P { //$$ = $1; 
                            }
	;
	
Array_P: '[' INT_P ']'
		| Array_P '[' INT_P ']'
		;

Array_Cont: '{' '}'
			| '{' Exp_List '}'
			;
Exp_List: Exp
		| Exp_List ',' Exp
		;

Re_Type_Spec: INT | CHAR | BOOL | DOUBLE | VOID ;

Main_Content_Func: '{' '}'
				| '{' Main_Block_List '}'
				;
				
Main_Block_List: Main_Block
				| Main_Block_List Main_Block
				;
				
Main_Block: Dec
			| Statement
			;
			
Statement: Simple_S
		| Switch_S
		| While_S
		| For_S
		| IF_S
		| End_S
		;
		
Simple_S: Var '=' Exp ';'
		;
		
Var: IDENTIFIER { $$ = $1; }
	| IDENTIFIER Array_Exp { //$$ = $1; 
                          }
	;
Array_Exp: '[' Exp ']'
		| Array_Exp '[' Exp ']'
		;
		
Switch_S: SWITCH '(' IDENTIFIER ')' '{' Switch_Cont '}'
		;
Switch_Cont: Case_L
			| Case_L Default_Cont
			;
Case_L: Case_One
		| Case_L Case_One
		;
		
Case_One: CASE INT_P ':' Statement_Many
		| CASE CHAR_P ':' Statement_Many
		| CASE INT_P ':'
		| CASE CHAR_P ':'
		;

Statement_Many: Statement
				| Statement_Many Statement
				;
Default_Cont: DEFAULT ':' Statement_Many
			| DEFAULT ':'
			;
			
While_S: WHILE '(' Exp ')' Main_Content_Func
		| DO Main_Content_Func WHILE '(' Exp ')' ';'
		;
For_S: FOR '(' For_Exp For_Exp Exp')' Main_Content_Func
		;

For_Exp: ';'
		| Exp ';'
		;
IF_S: IF '(' Exp ')' Main_Content_Func
	| IF '(' Exp ')' Main_Content_Func ELSE Main_Content_Func
	;
		
End_S: CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN Exp ';'
	;
 
Exp: Log_Or_Exp
	;
	
Log_Or_Exp: Log_And_Exp
	| Log_Or_Exp OR2 Log_And_Exp
	;
	
Log_And_Exp: Log_Not_Exp
			| Log_And_Exp AND2 Log_Not_Exp
			;
Log_Not_Exp: Com_Exp
			| N Com_Exp
			;
			
Com_Exp: Add_Min_Exp
		| Com_Exp SLT Add_Min_Exp
		| Com_Exp SLTE Add_Min_Exp
		| Com_Exp EE Add_Min_Exp
		| Com_Exp BLTE Add_Min_Exp
		| Com_Exp BLT Add_Min_Exp
		| Com_Exp NEQ Add_Min_Exp
		;
		
Add_Min_Exp: Mul_Exp
			| Add_Min_Exp PLUS Mul_Exp
      {
        fprintf(f_asm, "    pop.s { $r0 }\n");
        fprintf(f_asm, "    pop.s { $r1 }\n");
        fprintf(f_asm, "    add $r0, $r1, $r0\n");
        fprintf(f_asm, "    push.s { $r0 }\n");
      }
			| Add_Min_Exp MINUS Mul_Exp
      {
        fprintf(f_asm, "    pop.s { $r0 }\n");
        fprintf(f_asm, "    pop.s { $r1 }\n");
        fprintf(f_asm, "    sub $r0, $r1, $r0\n");
        fprintf(f_asm, "    push.s { $r0 }\n");
      }
			;
			
Mul_Exp: Unary_Exp
		| Mul_Exp MUL Unary_Exp
      {
        fprintf(f_asm, "    pop.s { $r0 }\n");
        fprintf(f_asm, "    pop.s { $r1 }\n");
        fprintf(f_asm, "    mul $r0, $r1, $r0\n");
        fprintf(f_asm, "    push.s { $r0 }\n");
      }
		| Mul_Exp DIV Unary_Exp
      {
        fprintf(f_asm, "    pop.s { $r2 }\n");
        fprintf(f_asm, "    pop.s { $r3 }\n");
        fprintf(f_asm, "    divsr $r0, $r1, $r3, $r2\n");
        fprintf(f_asm, "    push.s { $r0 }\n");
      }
		| Mul_Exp MOD Unary_Exp
      {
        fprintf(f_asm, "    pop.s { $r2 }\n");
        fprintf(f_asm, "    pop.s { $r3 }\n");
        fprintf(f_asm, "    divsr $r0, $r1, $r3, $r2\n");
        fprintf(f_asm, "    push.s { $r1 }\n");
      }
		;
		
Unary_Exp: Postfix_Exp
		| MINUS Postfix_Exp
		;
Postfix_Exp: Left_Exp
			| Left_Exp PLUS2
			| Left_Exp MINUS2
			;
			
Left_Exp: Var
          {
            int index = look_up_symbol($1);
            
            switch(table[index].mode)
            {
              case ARGUMENT_MODE:
                fprintf(f_asm, "    lwi $r0, [$sp+%d]\n",table[index].offset*4);
                break;
              case LOCAL_MODE:
                fprintf(f_asm, "    lwi $r0, [$sp+%d]\n",table[index].offset*4);
                break;
                               
              }
              fprintf(f_asm, "    push.s { $r0 }\n");
          }
		| INT_P
     {
       $$ = NULL;
       fprintf(f_asm, "    movi $r0, %d\n", $1);
       fprintf(f_asm, "    push.s { $r0 }\n");
     }
		| DOUBLE_P { $$ = NULL; }
		| CHAR_P     { $$ = NULL; }
		| SCIEN_P    { $$ = NULL; }
		| STR_P     { $$ = NULL; }
		| TRUE
		| FALSE
		| '(' Exp ')'
		| IDENTIFIER '(' ')'
		| IDENTIFIER '(' Exp_List ')';
		;

%%

int main(){

  init_symbol_table();
  
  if( (f_asm = fopen("assembly", "w")) == NULL){
    fprintf(stderr, "Can not open the file %s for writing.\n", "assembly");
  }
  
	yyparse();
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