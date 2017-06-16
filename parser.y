%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "SymbolTable.h"
	extern int num_lines;
	extern char *yytext;
	extern char str[300];
	int functionNum = 0;
  int LocalOffset = 0;
	int yyerror(char *msg);
  int LabelNum = 2;
  FILE *f_asm;

%}


%start Program

%token <ident> IDENTIFIER
%token <intVal> INT_P
%token DOUBLE_P SCIEN_P CHAR_P STR_P
%token <token> VOID INT DOUBLE BOOL CHAR NUL FOR WHILE DO IF ELSE SWITCH RETURN
%token <token> BREAK CONTINUE CONST STRUCT TRUE FALSE CASE DEFAULT



%token <charVal> ':' ';' '?' '=' '(' ')' '[' ']' '{' '}' '&'

%left <token> PLUS2 MINUS2 MUL DIV MOD PLUS MINUS
%left <token> AND2 OR2 N NEQ SLT BLT SLTE BLTE EE

%type <ident> Var Func_Dec Func_Def Dec Left_Exp Array Func_Dec1
%type <ident> Init_Left_Exp

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

   
Func_Def: Func_Dec '{'
          {
            cur_scope++;
            set_scope_and_offset_of_param($1);
            LocalOffset = 0;
          }
          Dec_List
          {
            set_local_vars($1);
          }
          Statement_List '}'
          {
            cur_scope--;
          }

Func_Dec: Re_Type_Spec IDENTIFIER { install_symbol($2); }
          '(' Para_List ')' { $$ = $2; }
  ;   

Dec: Func_Dec1 { $$ = $1; }
	| Normal_Dec { $$ = NULL; }
	;
	


Func_Dec1: Func_Dec ';'
  ;



Normal_Dec: Re_Type_Spec Normal_Dec_List ';'
	;
	
Normal_Dec_List:  Normal_Dec_One
				| Normal_Dec_List ',' Normal_Dec_One
				;
Normal_Dec_One: IDENTIFIER { install_symbol($1); }
				| Array { install_symbol($1); }
				| IDENTIFIER '=' Init_Exp
          {
            install_symbol($1);
            int index = look_up_symbol($1);
            table[index].offset = LocalOffset++;
            table[index].mode = LOCAL_MODE;
            
            PopReg(0);
            fprintf(f_asm, "    swi $r0, [$sp+%d]\n", table[index].offset*4);
          
          
          
          }
				| Array '=' Array_Cont { install_symbol($1); }
				;
				
Para_List: Para
		| Para_List ',' Para
		;
		
Para: Re_Type_Spec IDENTIFIER { install_symbol($2); }
	| Re_Type_Spec Array        { install_symbol($2); }
  |
	;
	
Array: IDENTIFIER Array_P { $$ = $1; }
	;
	
Array_P: '[' INT_P ']'
		| Array_P '[' INT_P ']'
		;

Array_Cont: '{' '}'
			| '{' Init_Exp_List '}'
			;
      
Var: IDENTIFIER { $$ = $1; }
	| IDENTIFIER Array_Exp { $$ = $1; }
	;
 


Re_Type_Spec: INT | CHAR | BOOL | DOUBLE | VOID ;





        
Main_Content_Func: '{'
                    {
                      cur_scope++;
                    }
                    Dec_List
                    {
                    }
                    Statement_List '}'
                    {
                      cur_scope--;
                    }
                ;
Dec_List: 
          | Dec_List Dec
          ;

Statement: Simple_S
		| Switch_S
		| While_S
		| For_S
		| IF_S
		| End_S
		;

		
Simple_S: Var '=' Exp ';'
		{
			int index = look_up_symbol($1);

                        /* Pop Expression to $r0 */
                         PopReg(0);

                         /* Store it to var */
                         fprintf(f_asm, "    swi $r0, [$sp+%d]\n",table[index].offset*4);
		
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
		;

Statement_Many: 
				| Statement_Many Statement
				;
Default_Cont: DEFAULT ':' Statement_Many
			;
			
Statement_List: 
                | Statement_List Statement
                ;      
      
While_S: WHILE 
        {
          fprintf(f_asm, ".L%d:\n", LabelNum);
        }
        '(' Exp ')' 
        {
          PopReg(0);
          fprintf(f_asm, "    beqz $r0, .L%d\n", LabelNum+1);
        }
        Main_Content_Func
        {
          /* Jump back to check expression */
          fprintf(f_asm, "    j .L%d\n", LabelNum);

          /* End , if false , branch to here */
          fprintf(f_asm, ".L%d:\n", LabelNum+1);
          LabelNum += 2;
        }
		|   DO 
        {
            fprintf(f_asm, ".L%d:\n", LabelNum);
        } 
        Main_Content_Func WHILE '(' Exp ')' ';'
        {
           PopReg(0);
           fprintf(f_asm, "    bnez $r0, .L%d\n", LabelNum);
           LabelNum++;
        }
		;
For_S: FOR '(' For_Exp For_Exp Exp')' Main_Content_Func
		;

For_Exp: ';'
		| Exp ';'
		;
IF_S: IF '(' Exp ')' 
    {
      PopReg(0);
      fprintf(f_asm, "    beqz $r0, .L%d\n", LabelNum);
    }
    Main_Content_Func Main_Sec
    ;

Main_Sec: 

    {
      fprintf(f_asm, ".L%d:\n", LabelNum);
      LabelNum++;
    }
	| ELSE 
    {
      fprintf(f_asm, "    j .L%d\n", LabelNum+1);
      fprintf(f_asm, ".L%d:\n", LabelNum);
    }
    Main_Content_Func
    {
      fprintf(f_asm, ".L%d:\n", LabelNum+1);
      LabelNum += 2;
    }
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
     {
       PopReg(0);
       PopReg(1);
       fprintf(f_asm, "    or $r0, $r0, $r1\n");
       PushReg(0);
     }
	;
	
Log_And_Exp: Log_Not_Exp
			| Log_And_Exp AND2 Log_Not_Exp
        {
          PopReg(0);
          PopReg(1);
          fprintf(f_asm, "    and $r0, $r0, $r1\n");
          PushReg(0);
        }
			;
Log_Not_Exp: Com_Exp
			| N Com_Exp
        {
          PopReg(0);
          fprintf(f_asm, "    addi $r0, $r0, 0\n"); /* ??? */
          fprintf(f_asm, "    slti $r0, $r0, 1\n");
          fprintf(f_asm, "    zeb $r0, $r0\n");
          PushReg(0);
        }
			;
			
Com_Exp: Add_Min_Exp
		| Com_Exp SLT Add_Min_Exp
       {
          PopReg(0);
          PopReg(1);
          fprintf(f_asm, "    slts $r0, $r1, $r0\n");
          fprintf(f_asm, "    zeb $r0, $r0\n");
          PushReg(0);
       }
		| Com_Exp SLTE Add_Min_Exp
       {
         PopReg(0);
         PopReg(1);
         fprintf(f_asm, "    slts $r0, $r0, $r1\n"); /* $r1 > $r0 ? */
         fprintf(f_asm, "    xori $r0, $r0, 1\n"); /* if $r0 == 1, $r0 = 0 */
         fprintf(f_asm, "    zeb $r0, $r0\n");
         PushReg(0);
       }
		| Com_Exp EE Add_Min_Exp
       {
         PopReg(0);
         PopReg(1);
         fprintf(f_asm, "    xor $r0, $r0, $r1\n"); /* If $r0 == $r1 , then result of xor will be 0 --> < 1 */
         fprintf(f_asm, "    slti $r0, $r0, 1\n");
         fprintf(f_asm, "    zeb $r0, $r0\n");
         PushReg(0);
       }
		| Com_Exp BLTE Add_Min_Exp
       {
         PopReg(0);
         PopReg(1);
         fprintf(f_asm, "    slts $r0, $r1, $r0\n"); /* $r1 < $r0 ? */
         fprintf(f_asm, "    xori $r0, $r0, 1\n"); /* if $r0 == 1, $r0 = 0 */
         fprintf(f_asm, "    zeb $r0, $r0\n");
         PushReg(0);
       }
		| Com_Exp BLT Add_Min_Exp
       {
         PopReg(0);
         PopReg(1);
         fprintf(f_asm, "    slts $r0, $r0, $r1\n");
         fprintf(f_asm, "    zeb $r0, $r0\n");
         PushReg(0);
       }
		| Com_Exp NEQ Add_Min_Exp
       {
         PopReg(0);
         PopReg(1);
         fprintf(f_asm, "    xor $r0, $r0, $r1\n"); /* If $r0 != $r1 , then result of xor will be > 0 */
         fprintf(f_asm, "    movi $r1, 0\n");
         fprintf(f_asm, "    slt $r0, $r1, $r0\n");
         fprintf(f_asm, "    zeb $r0, $r0\n");
         PushReg(0);
       }
		;
		
Add_Min_Exp: Mul_Exp
			| Add_Min_Exp PLUS Mul_Exp
      {

        PopReg(0);
        PopReg(1);

        fprintf(f_asm, "    add $r0, $r1, $r0\n");
        PushReg(0);

      }
			| Add_Min_Exp MINUS Mul_Exp
      {

        PopReg(0);
        PopReg(1);

        fprintf(f_asm, "    sub $r0, $r1, $r0\n");
        PushReg(0);

      }
			;
			
Mul_Exp: Unary_Exp
		| Mul_Exp MUL Unary_Exp
      {
        PopReg(0);
        PopReg(1);
        fprintf(f_asm, "    mul $r0, $r1, $r0\n");

        PushReg(0);       
      }
		| Mul_Exp DIV Unary_Exp
      {
      
        PopReg(2);
        PopReg(3);
        fprintf(f_asm, "    divsr $r0, $r1, $r3, $r2\n");

        PushReg(0);
      }
		| Mul_Exp MOD Unary_Exp
      {
      
        PopReg(2);
        PopReg(3);
        fprintf(f_asm, "    divsr $r0, $r1, $r3, $r2\n");

        PushReg(1);
      }
		;
		
Unary_Exp: Postfix_Exp
		| MINUS Postfix_Exp
       {
         PopReg(0);

         fprintf(f_asm, "    subri $r0, $r0, 0\n");

         PushReg(0);
       
       
       }
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
             PushReg(0);
          }
		| INT_P
     {
       $$ = NULL;
       
       
       fprintf(f_asm, "    movi $r0, %d\n",$1);
       PushReg(0);
     }
		| DOUBLE_P { $$ = NULL; }
		| CHAR_P     { $$ = NULL; }
		| SCIEN_P    { $$ = NULL; }
		| STR_P     { $$ = NULL; }
		| TRUE      { $$ = NULL; }
		| FALSE      { $$ = NULL; }
		| '(' Exp ')'  { $$ = NULL; }
		| IDENTIFIER '(' ')'
		| IDENTIFIER '(' Exp_List ')';
		;

Exp_List: Exp
		| Exp_List ',' Exp
		;

Init_Exp_List: Init_Exp
		| Init_Exp_List ',' Init_Exp
		;

Init_Exp: Init_Log_Or_Exp
	;
	
Init_Log_Or_Exp: Init_Log_And_Exp
	| Init_Log_Or_Exp OR2 Init_Log_And_Exp
     {
       PopReg(0);
       PopReg(1);
       fprintf(f_asm, "    or $r0, $r0, $r1\n");
       PushReg(0);
     }
     ;
	;
	
Init_Log_And_Exp: Init_Log_Not_Exp
			| Init_Log_And_Exp AND2 Init_Log_Not_Exp
        {
          PopReg(0);
          PopReg(1);
          fprintf(f_asm, "    and $r0, $r0, $r1\n");
          PushReg(0);
        }
        ;
			;
Init_Log_Not_Exp: Init_Com_Exp
			| N Init_Com_Exp
        {
          PopReg(0);
          fprintf(f_asm, "    addi $r0, $r0, 0\n"); /* ??? */
          fprintf(f_asm, "    slti $r0, $r0, 1\n");
          fprintf(f_asm, "    zeb $r0, $r0\n");
         PushReg(0);
         }
			;
			
Init_Com_Exp: Init_Add_Min_Exp
		| Init_Com_Exp SLT Add_Min_Exp
       {
          PopReg(0);
          PopReg(1);
          fprintf(f_asm, "    slts $r0, $r1, $r0\n");
          fprintf(f_asm, "    zeb $r0, $r0\n");
          PushReg(0);
       }
		| Init_Com_Exp SLTE Add_Min_Exp
       {
         PopReg(0);
         PopReg(1);
         fprintf(f_asm, "    slts $r0, $r0, $r1\n"); /* $r1 > $r0 ? */
         fprintf(f_asm, "    xori $r0, $r0, 1\n"); /* if $r0 == 1, $r0 = 0 */
         fprintf(f_asm, "    zeb $r0, $r0\n");
         PushReg(0);
       }
		| Init_Com_Exp EE Add_Min_Exp
       {
         PopReg(0);
         PopReg(1);
         fprintf(f_asm, "    xor $r0, $r0, $r1\n"); /* If $r0 == $r1 , then result of xor will be 0 --> < 1 */
         fprintf(f_asm, "    slti $r0, $r0, 1\n");
         fprintf(f_asm, "    zeb $r0, $r0\n");
         PushReg(0);
       }
		| Init_Com_Exp BLTE Add_Min_Exp
       {
         PopReg(0);
         PopReg(1);
         fprintf(f_asm, "    slts $r0, $r1, $r0\n"); /* $r1 < $r0 ? */
         fprintf(f_asm, "    xori $r0, $r0, 1\n"); /* if $r0 == 1, $r0 = 0 */
         fprintf(f_asm, "    zeb $r0, $r0\n");
         PushReg(0);
       }
		| Init_Com_Exp BLT Add_Min_Exp
       {
         PopReg(0);
         PopReg(1);
         fprintf(f_asm, "    slts $r0, $r0, $r1\n");
         fprintf(f_asm, "    zeb $r0, $r0\n");
         PushReg(0);
       }
		| Init_Com_Exp NEQ Add_Min_Exp
       {
         PopReg(0);
         PopReg(1);
         fprintf(f_asm, "    xor $r0, $r0, $r1\n"); /* If $r0 != $r1 , then result of xor will be > 0 */
         fprintf(f_asm, "    movi $r1, 0\n");
         fprintf(f_asm, "    slt $r0, $r1, $r0\n");
         fprintf(f_asm, "    zeb $r0, $r0\n");
         PushReg(0);
       }
		;
Init_Add_Min_Exp: Init_Mul_Exp
			| Init_Add_Min_Exp PLUS Init_Mul_Exp
      {
        PopReg(0);
        PopReg(1);

        fprintf(f_asm, "    add $r0, $r1, $r0\n");

        PushReg(0);
      }
			| Init_Add_Min_Exp MINUS Init_Mul_Exp
      {
        PopReg(0);
        PopReg(1);

        fprintf(f_asm, "    sub $r0, $r1, $r0\n");

        PushReg(0);
      }
			;
			
Init_Mul_Exp: Init_Unary_Exp
		| Init_Mul_Exp MUL Init_Unary_Exp
      {
      
        PopReg(0);
        PopReg(1);

        fprintf(f_asm, "    mul $r0, $r1, $r0\n");

        PushReg(0);
      }
		| Init_Mul_Exp DIV Init_Unary_Exp
      {
        PopReg(2);
        PopReg(3);

        fprintf(f_asm, "    divsr $r0, $r1, $r3, $r2\n");

        PushReg(0);
      }
		| Init_Mul_Exp MOD Init_Unary_Exp
      {
        PopReg(2);
        PopReg(3);

        fprintf(f_asm, "    divsr $r0, $r1, $r3, $r2\n");

        PushReg(1);
      }
		;
		
Init_Unary_Exp: Init_Postfix_Exp
		| MINUS Postfix_Exp
     {
       PopReg(0);

       fprintf(f_asm, "    subri $r0, $r0, 0\n");

       PushReg(0);
     
     
     }
		;
Init_Postfix_Exp: Init_Left_Exp
			| Init_Left_Exp PLUS2
			| Init_Left_Exp MINUS2
			;
			
Init_Left_Exp: Var
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
              PushReg(0);
          }
		| INT_P
     {
       $$ = NULL;
       
       fprintf(f_asm, "    movi $r0, %d\n",$1);
       PushReg(0);
     }
		| DOUBLE_P { $$ = NULL; }
		| CHAR_P     { $$ = NULL; }
		| SCIEN_P    { $$ = NULL; }
		| STR_P     { $$ = NULL; }
		| TRUE      { $$ = NULL; }
		| FALSE      { $$ = NULL; }
		| '(' Init_Exp ')'  { $$ = NULL; }
		;




%%

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
