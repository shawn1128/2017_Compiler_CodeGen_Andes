
/*
   This is a very simple c compiler written by Prof. Jenq Kuen Lee,
   Department of Computer Science, National Tsing-Hua Univ., Taiwan,
   Fall 1995.

   This is used in compiler class.
   This file contains Symbol Table Handling.

*/

#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include "SymbolTable.h"

extern FILE *f_asm;
int cur_counter = 0;
int cur_scope   = 1;
char *copys();

int stackOffset = 4 * 5 - 4;
void PushReg(int reg)
{
    stackOffset += 4;
    fprintf(f_asm, "    swi $r%d, [$sp+%d]\n", reg, stackOffset);
}

void PopReg(int reg)
{
    fprintf(f_asm, "    lwi $r%d, [$sp+%d]\n", reg, stackOffset);
    stackOffset -= 4;
}
/*

  init_symbol_table();

*/
init_symbol_table()
{

  bzero(&table[0], sizeof(struct symbol_entry)*MAX_TABLE_SIZE);

}

/*
   To install a symbol in the symbol table 

*/
char  *
install_symbol(s)
char *s;
{

   if (cur_counter >= MAX_TABLE_SIZE)
     err("Symbol Table Full");
   else {
    table[cur_counter].scope = cur_scope;
    table[cur_counter].name = copys(s);
    printf("scope = %d, name = %s, cur_counter = %d, offset = %d\n", table[cur_counter].scope, table[cur_counter].name, cur_counter, table[cur_counter].offset);
    cur_counter++;
    
  }
   return(s);
}



/*
   To return an integer as an index of the symbol table

*/
int
look_up_symbol(s)
char *s;
{
   int i;

   if (cur_counter==0) return(-1);
   for (i=cur_counter-1;i>=0; i--)
     {
       if (!strcmp(s,table[i].name))
	 return(i);
     }
   return(-1);
 }


/*
   Pop up symbols of the given scope from the symbol table upon the
   exit of a given scope.

*/
void
pop_up_symbol(scope)
int scope;
{
   int i;
   if (cur_counter==0) return;
   for (i=cur_counter-1;i>=0; i--)
     {
       if (table[i].scope !=scope) break;
     }
   if (i<0) cur_counter = 0;
   cur_counter = i+1;
   printf("cur_counter = %d\n", cur_counter);
  
}



/*
   Set up parameter scope and offset

*/
set_scope_and_offset_of_param(s)
char *s;
{

  int i,j,index;
  int total_args;
  printf("FUCK\n");
   index = look_up_symbol(s);
   if (index<0) err("Error in function header");
   else {
      table[index].type = T_FUNCTION;
      total_args = cur_counter -index -1;
      table[index].total_args=total_args;
      for (j=total_args, i=cur_counter-1;i>index; i--,j--)
        {
          table[i].scope= cur_scope;
          table[i].offset= j;
          table[i].mode  = ARGUMENT_MODE;
        }
   }

}



/*
   Set up local var offset

*/
set_local_vars(functor)
char *functor;
{

  int i,j,index,index1;
  int total_locals;

  index = look_up_symbol(functor);
  index1 = index + table[index].total_args;
  total_locals= cur_counter -index1 -1;
  if (total_locals <0)
     err("Error in number of local variables");
  table[index].total_locals=total_locals;
  for (j=total_locals, i=cur_counter-1;j>0; i--,j--)
        {
          table[i].scope= cur_scope;
          //table[i].offset= j;
          table[i].mode  = LOCAL_MODE;
        }

}



/*
  Set GLOBAL_MODE to global variables

*/

set_global_vars(s)
char *s;
{
  int index;
  index =look_up_symbol(s);
  table[index].mode = GLOBAL_MODE;
  table[index].scope =1;
}



/*******************Utility Functions ********************/
/*
 * copyn -- makes a copy of a string with known length
 *
 * input:
 *	  n - lenght of the string "s"
 *	  s - the string to be copied
 *
 * output:
 *	  pointer to the new string
 */

char   *
copyn(n, s)
	register int n;
	register char *s;
{
	register char *p, *q;
	//char   *calloc();

	p = q = calloc(1,n);
	while (--n >= 0)
		*q++ = *s++;
	return (p);
}


/*
 * copys -- makes a copy of a string
 *
 * input:
 *	  s - string to be copied
 *
 * output:
 *	  pointer to the new string
 */
char   *
copys(s)
	char   *s;
{
	return (copyn(strlen(s) + 1, s));
}


void printTable()
{
  int i;
  puts("\n----");
  printf("cur_counter = %d\n", cur_counter);
  for(i = 0; i < cur_counter; i++){
    printf("% -10s    scope:% -5d     offset:% -5d    total_args:% -5d    total_locals:% -5d\n",table[i].name, table[i].scope, table[i].offset, table[i].total_args, table[i].total_locals);

  }

}
