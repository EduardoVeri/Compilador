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
int flagMA = 0;

PONTEIRONO arvoreSintatica;

void mostraArvore(PONTEIRONO raiz, int num);
enum yytokentype getToken(void);

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
						mostraArvore(arvoreSintatica, 0);
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
						/*						
						YYSTYPE t = $1;
						if (t != NULL){
							while (t->sibling != NULL)
							t = t->sibling;
							t->sibling = $2;
							$$ = $1;
						}
						else $$ = $2;
						*/}
					| declaracao {$$ = $1;}
					;

declaracao			: var_declaracao {$$ = $1;}
					| fun_declaracao {$$ = $1;}				
					;

var_declaracao		: tipo_especificador ID SEMICOLON {
						$$ = novoNo();
						strcpy($$->lexema, $1->lexema);
						PONTEIRONO aux = novoNo();
						strcpy(aux->lexema, id);
						adicionaFilho($$, aux);

						/*
						$$ = newExpNode(VarDeclK);
						$$->attr.name = copyString(id);
						$$->child[0] = $1;
						$$->type = $1->type;
						$$->scope= scope;
						$$->kind.exp = VarDeclK;
						$$->lineno = lineno;
					*/}
					| tipo_especificador ID ABRECOLCHETES NUM FECHACOLCHETES SEMICOLON {
						$$ = novoNo();
						strcpy($$->lexema, $1->lexema);
						
						PONTEIRONO aux = novoNo();
						strcpy(aux->lexema, id);
						adicionaFilho($$, aux);
						
						adicionaFilho($$, $4);
						
						
						/*            
						$$ = newExpNode(VetorK);
						$$->attr.name = copyString(id);
						$$->child[0] = $1;
						$$->child[1] = $4;
						$$->type = $1->type;
						$$->scope= scope;
						$$->kind.exp = VetorK;
						$$->lineno = lineno;*/}
					;

tipo_especificador 	: INT {
						$$ = novoNo();
						strcpy($$->lexema, "INT");

						/*$$ = newExpNode(TypeK);
						$$->attr.name = "INT";
						$$->type = INTTYPE;
						$$->kind.exp = TypeK; */}
					| VOID {
						$$ = novoNo();
						strcpy($$->lexema, "VOID");

						/*$ = newExpNode(TypeK);
						$$->attr.name = "VOID";
						$$->type = VOIDTYPE;
						$$->kind.exp = TypeK;*/}
					;
					
					/* Trocar o ID da funcao por um IDFUNC */
fun_declaracao		: tipo_especificador fun_id ABREPARENTESES params FECHAPARENTESES composto_decl { 
						//strcpy(auxLexema, "")
						$$ = novoNo();
						strcpy($$->lexema, $1->lexema);
						adicionaFilho($$, $4);
						adicionaFilho($$, $2);
						adicionaFilho($2, $6);

						/*
            			$$ = newExpNode(FunDeclK);
						$$->kind.exp = FunDeclK;
						$$->attr.name = $2->attr.name;
						$$->child[0] = $1;
						$$->type = $1->type;
						$$->child[1] = $4;
						$$->child[2] = $6;
						$$->lineno = $2->lineno;*/}
					;

fun_id				: ID {
						$$ = novoNo();
						strcpy($$->lexema, auxNome);
						}
					;	

params				: param_lista {$$ = $1;}
					| VOID {
						$$ = novoNo();
						strcpy($$->lexema, "VOID");
						
						
						/*
						$$ = newExpNode(TypeK);
						$$->attr.name = "VOID";
						$$->size = 0;
						$$->child[0] = NULL;
						$$->lineno = lineno;*/}
					;

param_lista			: param_lista COMMA param {
						if($1 != NULL){
							$$ = $1;
							adicionaIrmao($$, $3);
						}
						else{
							$$ = $3;
						}						
						
						/*
						YYSTYPE t = $1;
						if (t != NULL){
						while (t->sibling != NULL)
							t = t->sibling;
						t->sibling = $3;
						$$ = $1;
						}
						else $$ = $3;
						*/}

					| param {$$ = $1;}
					;

param				: tipo_especificador ID {
						$$ = $1;
						PONTEIRONO aux = novoNo();
						strcpy(aux->lexema, id);
						adicionaFilho($$, aux);
						
					/*
						$$ = newExpNode(VarParamK);
						$$->attr.name = copyString(id);
						$$->kind.exp = VarParamK;
						$$->size = 0;
						$$->lineno = lineno;
						$$->type = $1->type;
						$$->child[0] = $1;
					*/}
					| tipo_especificador ID ABRECOLCHETES FECHACOLCHETES {
						$$ = $1;
						PONTEIRONO aux = novoNo();
						strcpy(aux->lexema, id);
						adicionaFilho($$, aux);
						
						/*
						$$ = newExpNode(VetParamK);
						$$->child[0] = $1;
						$$->attr.name = copyString(id);
						$$->kind.exp = VetParamK;
						$$->size = 0;
						$$->lineno = lineno;
						$$->type = $1->type;
						$$->child[0] = $1;
					*/}
					;

composto_decl		: ABRECHAVES local_declaracoes statement_lista FECHACHAVES { 
						if($2 != NULL){
							$$ = $2;
							adicionaIrmao($$, $3);
						}
						else{
							$$ = $3;
						}
						/*             
						YYSTYPE t = $2;
						if (t != NULL){
							while (t->sibling != NULL)
							t = t->sibling;
							t->sibling = $3;
							$$ = $2;
						}
						else $$ = $3;
						*/}
					;

local_declaracoes 	: local_declaracoes var_declaracao {
						if($1 != NULL){
							$$ = $1;
							adicionaIrmao($$, $2);
						}
						else{
							$$ = $2;
						}

					/*
						YYSTYPE t = $1;
						if (t != NULL){
							while (t->sibling != NULL)
								t = t->sibling;
							t->sibling = $2;
							$$ = $1;
						}
						else $$ = $2;
					*/}
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
						/*
						YYSTYPE t = $1;
						if (t != NULL){
							while (t->sibling != NULL)
								t = t->sibling;
							t->sibling = $2;
							$$ = $1;
						}
						else $$ = $2;
					*/}
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
						adicionaFilho($$, $3);
						adicionaFilho($$, $5);		
						/*
						$$ = newStmtNode(IfK);
						$$->attr.name = "IF";
						$$->child[0] = $3;
						$$->child[1] = $5;
						$$->lineno = lineno;
						$$->kind.stmt = IfK;
						*/
						
						}
					| IF ABREPARENTESES expressao FECHAPARENTESES statement ELSE statement {
						$$ = novoNo();
						strcpy($$->lexema, "IF");
						adicionaFilho($$, $7);
						adicionaFilho($$, $5);
						adicionaFilho($$, $3);

						/*            
						$$ = newStmtNode(IfK);r
						$$->attr.name = "IF";
						$$->child[0] = $3;
						$$->child[1] = $5;
						$$->child[2] = $7;
						$$->scope= $3->scope;
						$$->lineno = lineno;
						$$->kind.stmt = IfK;*/}
					;
			
iteracao_decl		: WHILE ABREPARENTESES expressao FECHAPARENTESES statement {
						$$ = novoNo();
						strcpy($$->lexema, "WHILE");
						adicionaFilho($$, $3);
						adicionaFilho($$, $5);

						/*
						$$ = newStmtNode(WhileK);
						$$->attr.name = "WHILE";
						$$->child[0] = $3;
						$$->child[1] = $5;
						$$->scope = $3->scope;
						$$->lineno = lineno;
						$$->kind.stmt = WhileK; */}
					;
			
retorno_decl		: RETURN SEMICOLON { 
						$$ = novoNo();
						strcpy($$->lexema, "ReturnVOID");
						
						/*              
						$$ = newStmtNode(ReturnINT);
						$$->child[0] = $2;
						$$->lineno = lineno;*/}
					| RETURN expressao SEMICOLON {
						$$ = novoNo();
						strcpy($$->lexema, "ReturnINT");
						adicionaFilho($$, $2);
						
						/*$$ = newStmtNode(ReturnVOID);*/}
					;

expressao			: var ATRIB expressao {
						$$ = novoNo();
						strcpy($$->lexema, "=");
						adicionaFilho($$, $1);
						adicionaFilho($$, $3);

						/*
						$$ = newStmtNode(AssignK);
						$$->kind.stmt = AssignK;
						$$->attr.name= $1->attr.name;
						$$->scope = scope;
						$$->child[0] = $1;
						$$->child[1] = $3;
						$$->lineno = lineno;

					*/}
					| simples_expressao {$$ = $1;}
					;

var 				: ID {
						$$ = novoNo();
						strcpy($$->lexema, id);

						/*
					    $$ = newExpNode(IdK);
						$$->attr.name = copyString(id);
						$$->lineno = lineno;
						$$->child[0] = NULL; */}
					| ID ABRECOLCHETES expressao FECHACOLCHETES {
						$$ = novoNo();
						strcpy($$->lexema, id);
						adicionaFilho($$, $3);
						
						/*
					    $$ = newExpNode(IdK);
						$$->attr.name = $1->attr.name;
						$$->child[0] = $3;
						$$->lineno = lineno; */}
					;
			
simples_expressao	: soma_expressao relacional soma_expressao {
						//$$ = novoNo();
						$$ = $2;
						adicionaFilho($$, $1);
						adicionaFilho($$, $3);	
						
					/*
						$$ = newStmtNode(AssignK);
						$$ = $2;
						$$->child[0] = $1;
						$$->child[1] = $3;
						$$->scope = scope; */}
					| soma_expressao {$$ = $1;}
					;

//Criar novas regras para as demais operações relacionais			
relacional			: operador_relacional {
						$$ = $1;
						

						/*
						$$ = newExpNode(OpK);
						$$->attr.op = IGL;
						$$->lineno = lineno;*/}
					;

operador_relacional	: EQ {
						$$ = novoNo();
						strcpy($$->lexema, "==");
						
						/*
						$$ = newExpNode(OpK);
						$$->attr.op = EQ;
						$$->lineno = lineno;*/}

					| NEQ {
						$$ = novoNo();
						strcpy($$->lexema, "!=");
						
						/*
						$$ = newExpNode(OpK);
						$$->attr.op = NEQ;
						$$->lineno = lineno;*/}

					| LT {
						$$ = novoNo();
						strcpy($$->lexema, "<");
						
						/*
						$$ = newExpNode(OpK);
						$$->attr.op = LT;
						$$->lineno = lineno;*/}
					
					| GT {
						$$ = novoNo();
						strcpy($$->lexema, ">");
						
						/*
						$$ = newExpNode(OpK);
						$$->attr.op = GT;
						$$->lineno = lineno;*/}
					
					| LET {
						$$ = novoNo();
						strcpy($$->lexema, "<=");
						
						/*
						$$ = newExpNode(OpK);
						$$->attr.op = LET;
						$$->lineno = lineno;*/}

					| GET {
						$$ = novoNo();
						strcpy($$->lexema, ">=");
						
						/*
						$$ = newExpNode(OpK);
						$$->attr.op = GET;
						$$->lineno = lineno;*/}
					;


soma_expressao		: soma_expressao soma termo {
						$$ = $2;
						adicionaFilho($$, $1);
						adicionaFilho($$, $3);
					
					/*
						$$ = $2;
						$$->child[0] = $1;
						$$->child[1] = $3;
						$$->scope = scope;
						$$->lineno = lineno; */}
					| termo {$$ = $1;}
					;
			
soma				: SOMA {
						$$ = novoNo();
						strcpy($$->lexema, "+");

						/*         
						$$ = newExpNode(OpK);
						$$->attr.op = SOM;
						$$->lineno = lineno;*/}
					| SUB {
						$$ = novoNo();
						strcpy($$->lexema, "-");

						/*         
						$$ = newExpNode(OpK);
						$$->attr.op = SUB;
						$$->lineno = lineno;*/} 
					;
			
termo				: termo mult fator {
						$$ = $2;
						adicionaFilho($$, $1);
						adicionaFilho($$, $3);
						
						/*
						$$ = $2;
						$$->scope = scope;
						$$->child[0] = $1;
						$$->child[1] = $3;
						$$->lineno = lineno; */}
					| fator {$$ = $1;}
					;
			
mult				: MULT {
						$$ = novoNo();
						strcpy($$->lexema, "*");
					/*
						$$ = newExpNode(OpK);
						$$->attr.op = MUL;
						$$->lineno = lineno;*/}
					| DIV {
						$$ = novoNo();
						strcpy($$->lexema, "/");
						
						/*
			        	$$ = newExpNode(OpK);
						$$->attr.op = DIV;
						$$->lineno = lineno;*/}
					;
			
fator				: ABREPARENTESES expressao FECHAPARENTESES  {$$ = $2;}
					| var {$$ = $1;}
					| ativacao {$$ = $1;}
					| NUM { 
						$$ = novoNo();
						strcpy($$->lexema, auxNome);
						
						/*
						$$ = newExpNode(ConstK);
						$$->type = INTTYPE;
						$$->attr.name = "teste";
						$$->attr.val = atoi(tokenString);*/}
					;

ativacao 			: fun_id ABREPARENTESES args FECHAPARENTESES {
						$$ = $1;
						adicionaFilho($$, $3);
						/*
						$$ = newExpNode(AtivK);
						$$->kind.exp = AtivK;
						$$->attr.name = $1->attr.name;
						$$->child[0] = $3;
						$$->params = params;
						$$->lineno = lineno;*/}
					;
			
args 				: arg_lista {$$ = $1;}
					| %empty {$$ = NULL;}
					;
			
arg_lista			: arg_lista COMMA expressao {
						if($1 != NULL){
							$$ = $1;
							adicionaIrmao($$, $3);
						} else $$ = $3;
						
						/*
						YYSTYPE t = $1;
						if (t != NULL){
							while (t->sibling != NULL)
								t = t->sibling;
							t->sibling = $3;
							params ++;
						$$ = $1;
						} else $$ = $3;*/}
					| expressao {
						$$ = $1;
						/*
						params ++;
           				$$ = $1;*/}
					;			


%%

void yyerror (char *s){
	printf ("ERRO SINTATICO: LINHA %d\n", qntLinhas);
}

int yylex(void)
{ return getToken(); }

/* TreeNode * parse(void)
{ yyparse();
  return savedTree;
}*/

void mostraArvore(PONTEIRONO raiz, int num){
	if(flagMA == 0){
		flagMA = 1;
		printf("\n========== Arvore de Analise Sintatica ========== \n");
	}
	
	if(raiz == NULL){
		return;
	}

	for(int i = 0; i < num; i++){
		printf("\t");
	}
	printf("%s\n", raiz->lexema);
	
	for(int i = 0; i < 3; i++){
		mostraArvore(raiz->filho[i], num + 1);
	}
	mostraArvore(raiz->irmao, num);

	
}