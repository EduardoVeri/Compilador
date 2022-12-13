%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int yylex();
void yyerror(char* s);
int yyparse(void);



%}

%token NUM SOMA SUB MULT DIV INT
%token ID VOID WHILE ELSE IF ABREPARENTESES FECHAPARENTESES
%token OPRELACIONAL RETURN COMMA ABRECHAVES FECHACHAVES SEMICOLON
%token ATRIB ABRECOLCHETES FECHACOLCHETES

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

var_declaracao		: tipo_especificador ID SEMICOLON
			| tipo_especificador ID ABRECOLCHETES NUM FECHACOLCHETES SEMICOLON
			;

tipo_especificador 	: INT 
			| VOID
			;

fun_declaracao		: tipo_especificador ID ABREPARENTESES params FECHAPARENTESES composto_decl
			;

params			: param_lista
			| VOID
			;

param_lista		: param_lista COMMA param
			| param
			;

param			: tipo_especificador ID
			| tipo_especificador ID ABRECOLCHETES FECHACOLCHETES
			;

composto_decl		: ABRECHAVES local_declaracoes statement_lista FECHACHAVES
			;

local_declaracoes 	: local_declaracoes var_declaracao
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

expressao_decl		: expressao SEMICOLON
			| SEMICOLON
			;
			
selecao_decl		: IF ABREPARENTESES expressao FECHAPARENTESES statement
			| IF ABREPARENTESES expressao FECHAPARENTESES statement ELSE statement
			;
			
iteracao_decl		: WHILE ABREPARENTESES expressao FECHAPARENTESES statement
			;
			
retorno_decl		: RETURN SEMICOLON
			| RETURN expressao SEMICOLON
			;

expressao		: var ATRIB expressao
			| simples_expressao
			;

var 			: ID
			| ID ABRECOLCHETES expressao FECHACOLCHETES
			;
			
simples_expressao	: soma_expressao relacional soma_expressao
			| soma_expressao
			;
			
relacional		: OPRELACIONAL
			;
			
soma_expressao		: soma_expressao soma termo 
			| termo
			;
			
soma			: SOMA
			| SUB
			;
			
termo			: termo mult fator
			| fator
			;
			
mult			: MULT
			| DIV
			;
			
fator			: ABREPARENTESES expressao FECHAPARENTESES 
			| var
			| ativacao
			| NUM
			;

ativacao 		: ID ABREPARENTESES args FECHAPARENTESES
			;
			
args 			: arg_lista
			| %empty
			;
			
arg_lista		: arg_lista COMMA expressao 
			| expressao
			;			


%%

void yyerror (char *s){
	printf ("ERRO SINTATICO: %s LINHA:", s);
}



