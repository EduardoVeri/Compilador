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
			
declaracao_lista	: declaracao_lista declaracao {  /*        
							YYSTYPE t = $1;
							if (t != NULL){
								while (t->sibling != NULL)
								t = t->sibling;
								t->sibling = $2;
								$$ = $1;
							}
							else $$ = $2;;
						*/}
					| declaracao {$$ = $1;}
					;

declaracao			: var_declaracao {$$ = $1;}
					| fun_declaracao {$$ = $1;}
					;

var_declaracao		: tipo_especificador ID SEMICOLON {/* 
						$$ = newExpNode(VarDeclK);
						$$->attr.name = copyString(id);
						$$->child[0] = $1;
						$$->type = $1->type;
						$$->scope= scope;
						$$->kind.exp = VarDeclK;
						$$->lineno = lineno;
					*/}
					| tipo_especificador ID ABRECOLCHETES NUM FECHACOLCHETES SEMICOLON {/*            
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
						/*$$ = newExpNode(TypeK);
						$$->attr.name = "INT";
						$$->type = INTTYPE;
						$$->kind.exp = TypeK; */}
					| VOID {
						/*$ = newExpNode(TypeK);
						$$->attr.name = "VOID";
						$$->type = VOIDTYPE;
						$$->kind.exp = TypeK;*/}
					;
					
					/* Trocar o ID da funcao por um IDFUNC */
fun_declaracao		: tipo_especificador ID ABREPARENTESES params FECHAPARENTESES composto_decl { /*
            			$$ = newExpNode(FunDeclK);
						$$->kind.exp = FunDeclK;
						$$->attr.name = $2->attr.name;
						$$->child[0] = $1;
						$$->type = $1->type;
						$$->child[1] = $4;
						$$->child[2] = $6;
						$$->lineno = $2->lineno;*/}
					;

params				: param_lista {$$ = $1;}
					| VOID {/*
						$$ = newExpNode(TypeK);
						$$->attr.name = "VOID";
						$$->size = 0;
						$$->child[0] = NULL;
						$$->lineno = lineno;*/}
					;

param_lista			: param_lista COMMA param {/*
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

param				: tipo_especificador ID {/*
						$$ = newExpNode(VarParamK);
						$$->attr.name = copyString(id);
						$$->kind.exp = VarParamK;
						$$->size = 0;
						$$->lineno = lineno;
						$$->type = $1->type;
						$$->child[0] = $1;
					*/}
					| tipo_especificador ID ABRECOLCHETES FECHACOLCHETES {/*
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

composto_decl		: ABRECHAVES local_declaracoes statement_lista FECHACHAVES { /*             
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

local_declaracoes 	: local_declaracoes var_declaracao {/*
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

statement_lista 	: statement_lista statement {/*
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
					| SEMICOLON {$$ = $1;} //Deixar vazio talvez
					;
			
selecao_decl		: IF ABREPARENTESES expressao FECHAPARENTESES statement {
						/*
						$$ = newStmtNode(IfK);
						$$->attr.name = "IF";
						$$->child[0] = $3;
						$$->child[1] = $5;
						$$->lineno = lineno;
						$$->kind.stmt = IfK;
						*/
						strcpy(auxLexema, "IF");
						$$ = criaNo(auxLexema, qntLinhas, 0, 1);
						adicionaFilho($$, $3);
						adicionaFilho($$, $5);
						
						}
					| IF ABREPARENTESES expressao FECHAPARENTESES statement ELSE statement {/*            
						$$ = newStmtNode(IfK);
						$$->attr.name = "IF";
						$$->child[0] = $3;
						$$->child[1] = $5;
						$$->child[2] = $7;
						$$->scope= $3->scope;
						$$->lineno = lineno;
						$$->kind.stmt = IfK;*/}
					;
			
iteracao_decl		: WHILE ABREPARENTESES expressao FECHAPARENTESES statement {/*
						$$ = newStmtNode(WhileK);
						$$->attr.name = "WHILE";
						$$->child[0] = $3;
						$$->child[1] = $5;
						$$->scope = $3->scope;
						$$->lineno = lineno;
						$$->kind.stmt = WhileK; */}
					;
			
retorno_decl		: RETURN SEMICOLON { /*              
						$$ = newStmtNode(ReturnINT);
						$$->child[0] = $2;
						$$->lineno = lineno;*/}
					| RETURN expressao SEMICOLON {/*$$ = newStmtNode(ReturnVOID);*/}
					;

expressao			: var ATRIB expressao {/*
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

var 				: ID {/*
					    $$ = newExpNode(IdK);
						$$->attr.name = copyString(id);
						$$->lineno = lineno;
						$$->child[0] = NULL; */}
					| ID ABRECOLCHETES expressao FECHACOLCHETES {/*
					    $$ = newExpNode(IdK);
						$$->attr.name = $1->attr.name;
						$$->child[0] = $3;
						$$->lineno = lineno; */}
					;
			
simples_expressao	: soma_expressao relacional soma_expressao {/*
						$$ = newStmtNode(AssignK);
						$$ = $2;
						$$->child[0] = $1;
						$$->child[1] = $3;
						$$->scope = scope; */}
					| soma_expressao {$$ = $1;}
					;
			
relacional			: OPRELACIONAL {/*
						$$ = newExpNode(OpK);
						$$->attr.op = IGL;
						$$->lineno = lineno;*/}
					;
			
soma_expressao		: soma_expressao soma termo {/*
						$$ = $2;
						$$->child[0] = $1;
						$$->child[1] = $3;
						$$->scope = scope;
						$$->lineno = lineno; */}
					| termo {$$ = $1;}
					;
			
soma				: SOMA {/*         
						$$ = newExpNode(OpK);
						$$->attr.op = SOM;
						$$->lineno = lineno;*/}
					| SUB {/*         
						$$ = newExpNode(OpK);
						$$->attr.op = SUB;
						$$->lineno = lineno;*/} 
					;
			
termo				: termo mult fator {/*
						$$ = $2;
						$$->scope = scope;
						$$->child[0] = $1;
						$$->child[1] = $3;
						$$->lineno = lineno; */}
					| fator {$$ = $1;}
					;
			
mult				: MULT {/*
						$$ = newExpNode(OpK);
						$$->attr.op = MUL;
						$$->lineno = lineno;*/}
					| DIV {/*
			        	$$ = newExpNode(OpK);
						$$->attr.op = DIV;
						$$->lineno = lineno;*/}
					;
			
fator				: ABREPARENTESES expressao FECHAPARENTESES  {$$ = $2;}
					| var {$$ = $1;}
					| ativacao {$$ = $1;}
					| NUM { /*
						$$ = newExpNode(ConstK);
						$$->type = INTTYPE;
						$$->attr.name = "teste";
						$$->attr.val = atoi(tokenString);*/}
					;

ativacao 			: ID ABREPARENTESES args FECHAPARENTESES {/*
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
			
arg_lista			: arg_lista COMMA expressao {/*
						YYSTYPE t = $1;
						if (t != NULL){
							while (t->sibling != NULL)
								t = t->sibling;
							t->sibling = $3;
							params ++;
						$$ = $1;
						} else $$ = $3;*/}
					| expressao {/*
						params ++;
           				$$ = $1;*/}
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

