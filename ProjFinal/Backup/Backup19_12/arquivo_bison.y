%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"

#define YYSTYPE PONTEIRONO
int yylex();
void yyerror(char* s);
int yyparse(void);


PONTEIRONO arvoreSintatica;


char auxLexema[26];

%}

%token NUM SOMA SUB MULT DIV INT
%token ID VOID WHILE ELSE IF ABREPARENTESES FECHAPARENTESES
%token OPRELACIONAL RETURN COMMA ABRECHAVES FECHACHAVES SEMICOLON
%token ATRIB ABRECOLCHETES FECHACOLCHETES

%%

programa			: declaracao_lista {arvoreSintatica = $1;}
					;
			
declaracao_lista	: declaracao_lista declaracao 
					| declaracao
					;

declaracao			: var_declaracao
					| fun_declaracao
					;

var_declaracao		: tipo_especificador ID SEMICOLON
					| tipo_especificador ID ABRECOLCHETES NUM FECHACOLCHETES SEMICOLON
					;

tipo_especificador 	: INT {$$ = NULL;}
					| VOID {$$ = NULL;}
					;

fun_declaracao		: tipo_especificador ID ABREPARENTESES params FECHAPARENTESES composto_decl
					;

params				: param_lista
					| VOID {$$ = NULL;}
					;

param_lista			: param_lista COMMA param
					| param
					;

param				: tipo_especificador ID
					| tipo_especificador ID ABRECOLCHETES FECHACOLCHETES
					;

composto_decl		: ABRECHAVES local_declaracoes statement_lista FECHACHAVES {$$ = NULL;}
					;

local_declaracoes 	: local_declaracoes var_declaracao
					| %empty {$$ = NULL;}
					;

statement_lista 	: statement_lista statement 
					| %empty {$$ = NULL;}
					;
			
statement			: expressao_decl
					| composto_decl
					| selecao_decl
					| iteracao_decl
					| retorno_decl
					;

expressao_decl		: expressao SEMICOLON
					| SEMICOLON {$$ = NULL;}
					;
			
selecao_decl		: IF ABREPARENTESES expressao FECHAPARENTESES statement {
						strcpy(auxLexema, "IF");
						$$ = criaNo(auxLexema, qntLinhas, 0, 1);
						adicionaFilho($$, $3);
						adicionaFilho($$, $5);
						
						}
					| IF ABREPARENTESES expressao FECHAPARENTESES statement ELSE statement {$$ = NULL;}
					;
			
iteracao_decl		: WHILE ABREPARENTESES expressao FECHAPARENTESES statement {$$ = NULL;}
					;
			
retorno_decl		: RETURN SEMICOLON {$$ = NULL;}
					| RETURN expressao SEMICOLON {$$ = NULL;}
					;

expressao			: var ATRIB expressao
					| simples_expressao
					;

var 				: ID {$$ = NULL;}
					| ID ABRECOLCHETES expressao FECHACOLCHETES {$$ = NULL;}
					;
			
simples_expressao	: soma_expressao relacional soma_expressao
					| soma_expressao
					;
			
relacional			: OPRELACIONAL {$$ = NULL;}
					;
			
soma_expressao		: soma_expressao soma termo 
					| termo
					;
			
soma				: SOMA {$$ = NULL;}
					| SUB {$$ = NULL;} 
					;
			
termo				: termo mult fator
					| fator
					;
			
mult				: MULT {$$ = NULL;}
					| DIV {$$ = NULL;}
					;
			
fator				: ABREPARENTESES expressao FECHAPARENTESES  {$$ = NULL;}
					| var
					| ativacao
					| NUM {$$ = NULL;}
					;

ativacao 			: ID ABREPARENTESES args FECHAPARENTESES {$$ = NULL;}
					;
			
args 				: arg_lista
					| %empty {$$ = NULL;}
					;
			
arg_lista			: arg_lista COMMA expressao 
					| expressao
					;			


%%

void yyerror (char *s){
	printf ("ERRO SINTATICO: LINHA %d\n", qntLinhas);
}







/*
TreeNode * parse(void)
{ yyparse();
  return savedTree;
}*/

