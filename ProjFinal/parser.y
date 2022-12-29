%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"

#define YYSTYPE PONTEIRONO
static int yylex(void);
void yyerror(char* s);
int yyparse(void);
char auxNome[26];
char id[26];
int qntLinhas;

PONTEIRONO arvoreSintatica;

void mostraArvore(PONTEIRONO raiz, int num);
enum yytokentype getToken(void);
PONTEIRONO parse(void);

char auxLexema[26];

%}
/*
Declaracao dos tokens que serao utilizados durante o processo de analise
sintatica. 
*/


%token NUM SOMA SUB MULT DIV INT
%token ID VOID WHILE ELSE IF ABREPARENTESES FECHAPARENTESES
%token RETURN COMMA ABRECHAVES FECHACHAVES SEMICOLON
%token ATRIB ABRECOLCHETES FECHACOLCHETES
%token EQ NEQ LT LET GT GET ERRO

%%

programa			: declaracao_lista {
						arvoreSintatica = $1;
					}

					;
			
declaracao_lista	: declaracao_lista declaracao {  
						if($1 != NULL){
							$$ = $1;
							adicionaIrmao($$, $2);
						}
						else{
							$$ = $2;
						}
					  }
					| declaracao {$$ = $1;}
					;

declaracao			: var_declaracao {$$ = $1;}
					| fun_declaracao {$$ = $1;}				
					;

var_declaracao		: tipo_especificador ID SEMICOLON {
						$$ = $1;
						$$->tipo = DECLARACAO;
						$$->tipoDeclaracao = VarDeclK;
						$$->numLinha = qntLinhas;
					
						PONTEIRONO aux = novoNo();
						strcpy(aux->lexema, id);
						adicionaFilho($$, aux);

						}
					| tipo_especificador ID ABRECOLCHETES NUM FECHACOLCHETES SEMICOLON {
						$$ = $1;
						$$->tipo = DECLARACAO;
						$$->tipoDeclaracao = VetDeclK;
						$$->numLinha = qntLinhas;

						PONTEIRONO aux = novoNo();
						strcpy(aux->lexema, id);
						adicionaFilho($$, aux);
						
						aux = novoNo();
						strcpy(aux->lexema, auxNome);
						adicionaFilho($$, aux);
					
					}
					;

tipo_especificador 	: INT {
						$$ = novoNo();
						strcpy($$->lexema, "INT");
						$$->numLinha = qntLinhas;
					}
					| VOID {
						$$ = novoNo();
						strcpy($$->lexema, "VOID");
						$$->numLinha = qntLinhas;
					}
					;
					
					/* Trocar o ID da funcao por um IDFUNC */
fun_declaracao		: tipo_especificador fun_id ABREPARENTESES params FECHAPARENTESES composto_decl { 
						//strcpy(auxLexema, "")
						$$ = $1;

						adicionaFilho($$, $4);
						adicionaFilho($$, $2);
						adicionaFilho($2, $6);
						
						$$->tipo = DECLARACAO;
						$$->tipoDeclaracao = FunDeclK;
					}
					;

fun_id				: ID {
						$$ = novoNo();
						strcpy($$->lexema, auxNome);
						$$->numLinha = qntLinhas;
					}
					;	

params				: param_lista {$$ = $1;}
					| VOID {
						$$ = novoNo();
						$$->tipo = DECLARACAO;
						$$->numLinha = qntLinhas;
						$$->tipoDeclaracao = ParamVoid;
						strcpy($$->lexema, "VOID");
					}
					;

param_lista			: param_lista COMMA param {
						if($1 != NULL){
							$$ = $1;
							adicionaIrmao($$, $3);
						}
						else{
							$$ = $3;
						}						
					}
					| param {$$ = $1;}
					;

param				: tipo_especificador ID {
						$$ = $1;
						$$->tipo = DECLARACAO;
						$$->numLinha = qntLinhas;
						$$->tipoDeclaracao = VarParamK;

						PONTEIRONO aux = novoNo();
						strcpy(aux->lexema, id);
						adicionaFilho($$, aux);

					}
					| tipo_especificador ID ABRECOLCHETES FECHACOLCHETES {
						$$ = $1;
						$$->tipo = DECLARACAO;
						$$->numLinha = qntLinhas;
						$$->tipoDeclaracao = VetParamK;
						PONTEIRONO aux = novoNo();
						strcpy(aux->lexema, id);
						adicionaFilho($$, aux);
						
					}
					;

composto_decl		: ABRECHAVES local_declaracoes statement_lista FECHACHAVES { 
						if($2 != NULL){
							$$ = $2;
							adicionaIrmao($$, $3);
						}
						else{
							$$ = $3;
						}
					}
					;

local_declaracoes 	: local_declaracoes var_declaracao {
						if($1 != NULL){
							$$ = $1;
							adicionaIrmao($$, $2);
						}
						else{
							$$ = $2;
						}

					}
					| %empty {$$ = NULL;}
					;

statement_lista 	: statement_lista statement {
						if($1 != NULL){
							$$ = $1;
							adicionaIrmao($$, $2);
						}
						else{
							$$ = $2;
						}
					}
					| %empty {$$ = NULL;}
					;
			
statement			: expressao_decl {$$ = $1;}
					| composto_decl {$$ = $1;}
					| selecao_decl {$$ = $1;}
					| iteracao_decl {$$ = $1;}
					| retorno_decl {$$ = $1;}
					;

expressao_decl		: expressao SEMICOLON {$$ = $1;}
					| SEMICOLON {$$ = NULL;} //Deixar vazio talvez
					;
			
selecao_decl		: IF ABREPARENTESES expressao FECHAPARENTESES statement {
						$$ = novoNo();
						strcpy($$->lexema, "IF");
						$$->tipo = DECLARACAO;
						$$->numLinha = qntLinhas;
						$$->tipoDeclaracao = IfK;

						adicionaFilho($$, $3);
						adicionaFilho($$, $5);		
					}
					| IF ABREPARENTESES expressao FECHAPARENTESES statement ELSE statement {
						$$ = novoNo();
						strcpy($$->lexema, "IF");
						$$->tipo = DECLARACAO;
						$$->numLinha = qntLinhas;
						$$->tipoDeclaracao = IfK;

						adicionaFilho($$, $3);
						adicionaFilho($$, $5);
						adicionaFilho($$, $7);
						
					}
					;
			
iteracao_decl		: WHILE ABREPARENTESES expressao FECHAPARENTESES statement {
						$$ = novoNo();
						strcpy($$->lexema, "WHILE");
						$$->tipo = DECLARACAO;
						$$->numLinha = qntLinhas;
						$$->tipoDeclaracao = WhileK;

						adicionaFilho($$, $3);
						adicionaFilho($$, $5);

					}
					;
			
retorno_decl		: RETURN SEMICOLON { 
						$$ = novoNo();
						$$->tipo = DECLARACAO;
						$$->numLinha = qntLinhas;
						$$->tipoDeclaracao = ReturnVOID;
						strcpy($$->lexema, "ReturnVOID");
						
					}
					| RETURN expressao SEMICOLON {
						$$ = novoNo();
						$$->tipo = DECLARACAO;
						$$->numLinha = qntLinhas;
						$$->tipoDeclaracao = ReturnINT;
						strcpy($$->lexema, "ReturnINT");

						adicionaFilho($$, $2);
					}
					;

expressao			: var ATRIB expressao {
						$$ = novoNo();
						strcpy($$->lexema, "=");
						$$->tipo = EXPRESSAO;
						$$->numLinha = qntLinhas;
						$$->tipoExpressao = AssignK;

						adicionaFilho($$, $1);
						adicionaFilho($$, $3);

					}
					| simples_expressao {$$ = $1;}
					;

var 				: ID {
						$$ = novoNo();
						$$->tipo = EXPRESSAO;
						$$->numLinha = qntLinhas;
						$$->tipoExpressao = IdK;
						strcpy($$->lexema, id);

					}
					| ID ABRECOLCHETES expressao FECHACOLCHETES {
						$$ = novoNo();
						$$->tipo = EXPRESSAO;
						$$->numLinha = qntLinhas;
						$$->tipoExpressao = VetorK;
						
						strcpy($$->lexema, id);
						adicionaFilho($$, $3);
						
					}
					;
			
simples_expressao	: soma_expressao relacional soma_expressao {
						$$ = $2;
						$$->tipo = EXPRESSAO;
						$$->numLinha = qntLinhas;
						$$->tipoExpressao = OpRel;

						adicionaFilho($$, $1);
						adicionaFilho($$, $3);	
						
					}
					| soma_expressao {$$ = $1;}
					;
		
relacional			: operador_relacional {
						$$ = $1;
					}
					;

operador_relacional	: EQ {
						$$ = novoNo();
						strcpy($$->lexema, "==");
						
					}

					| NEQ {
						$$ = novoNo();
						strcpy($$->lexema, "!=");
						
					}

					| LT {
						$$ = novoNo();
						strcpy($$->lexema, "<");
						
					}
					
					| GT {
						$$ = novoNo();
						strcpy($$->lexema, ">");
						
					}
					
					| LET {
						$$ = novoNo();
						strcpy($$->lexema, "<=");
						
					}

					| GET {
						$$ = novoNo();
						strcpy($$->lexema, ">=");
					}
					;


soma_expressao		: soma_expressao soma termo {
						$$ = $2;
						$$->tipo = EXPRESSAO;
						$$->numLinha = qntLinhas;
						$$->tipoExpressao = OpK;

						adicionaFilho($$, $1);
						adicionaFilho($$, $3);
					}
					| termo {$$ = $1;}
					;
			
soma				: SOMA {
						$$ = novoNo();
						strcpy($$->lexema, "+");
					}
					| SUB {
						$$ = novoNo();
						strcpy($$->lexema, "-");
					} 
					;
			
termo				: termo mult fator {
						$$ = $2;
						$$->tipo = EXPRESSAO;
						$$->numLinha = qntLinhas;
						$$->tipoExpressao = OpK;

						adicionaFilho($$, $1);
						adicionaFilho($$, $3);
						
					}
					| fator {$$ = $1;}
					;
			
mult				: MULT {
						$$ = novoNo();
						strcpy($$->lexema, "*");
					}
					| DIV {
						$$ = novoNo();
						strcpy($$->lexema, "/");
					}
					;
			
fator				: ABREPARENTESES expressao FECHAPARENTESES  {$$ = $2;}
					| var {$$ = $1;}
					| ativacao {$$ = $1;}
					| NUM { 
						$$ = novoNo();
						$$->tipo = EXPRESSAO;
						$$->numLinha = qntLinhas;
						$$->tipoExpressao = ConstK;
						strcpy($$->lexema, auxNome);
					}
					;

ativacao 			: fun_id ABREPARENTESES args FECHAPARENTESES {
						$$ = $1;
						$$->tipo = EXPRESSAO;
						$$->numLinha = qntLinhas;
						$$->tipoExpressao = AtivK;
						adicionaFilho($$, $3);
					}
					;
			
args 				: arg_lista {$$ = $1;}
					| %empty {$$ = NULL;}
					;
			
arg_lista			: arg_lista COMMA expressao {
						if($1 != NULL){
							$$ = $1;
							adicionaIrmao($$, $3);
						} else $$ = $3;
					}
					| expressao {
						$$ = $1;
					}
					;			


%%

void yyerror (char *s){
	printf(ANSI_COLOR_RED "ERRO SINTATICO, LINHA: %d", qntLinhas);
	//printf(ANSI_COLOR_RESET "");
}

int yylex(void)
{ return getToken(); }

PONTEIRONO parse(void)
{ 
	yyparse();
	return arvoreSintatica;
}

