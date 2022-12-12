%{

#include <stdio.h>
#include <string.h>

int yylex();
void yyerror(char* s);
int yyparse(void);


%}

%token NUM SOMA SUB MULT DIV INT
%token ID VOID WHILE ELSE IF
%token OPRELACIONAL

%left SOMA SUB MULT

%%

programa		: declaracao_lista
			;
			
declaracao_lista	: declaracao_lista declaracao
			| declaracao
			;

declaracao		: var_declaracao
			| fun_declaracao
			;

var_declaracao		: tipo_especificador ID ';'
			| tipo_especificador ID '[' NUM ']' ';'
			;

tipo_especificador 	: INT 
			| VOID
			;

fun_declaracao		: tipo_especificador ID '(' params ')' composto_decl
			;

params			: param_lista
			| VOID
			;

param_lista		: param_lista ',' param
			| param
			;

param			: tipo_especificador ID
			| tipo_especificador ID '['']'
			;

composto_decl		: '{' local_declaracoes statement_lista '}'
			;

local_declaracoes 	: local_declaracoes var_declaracoes
			| %empty
			;

statement_lista 	: statement_lista statement 
			| %empty
			;
			
statement		: expressao_decl
			| composto_decl
			| selecao_decl
			| iteracao_decl
			| retorno_decl
			;

expressao_decl		: expressao ';'
			| ';'
			;
			
selecao_decl		: IF '(' expressao ')' statement
			| IF '(' expressao ')' statement ELSE statement
			;
			
iteracao_decl		: WHILE '(' expressao ')' statement
			;
			



%%


#include <stdlib.h>


void yyerror (char *s){
	printf ("ERRO SINTATICO: %s LINHA:\n", s);
}

int main (void){
	yyparse ();
}

