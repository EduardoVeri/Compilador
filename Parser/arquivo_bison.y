%{

#include <stdio.h>
#include <string.h>

int yylex();
void yyerror(char* s);
int yyparse(void);
//#define YYSTYPE int

%}

%token NUM SOMA SUB MULT
%left SOMA SUB MULT

%%


input	: exp { printf ("%d\n", $1); }
	| 'p' { return 0; }
	;

exp	: exp SOMA exp { $$ = $1 + $3;}
	| exp SUB exp { $$ = $1 - $3;}
	| termo
	;

termo	: termo MULT fator { $$ = $1 * $3; }
	| fator
	;

fator	: '(' exp ')' { $$ = $2; }
	| NUM
	;

%%

#include <ctype.h>
#include <stdlib.h>


void yyerror (char *s){
	printf ("ERRO: %s\n", s);
}

int main (void){
	yyparse ();
}

