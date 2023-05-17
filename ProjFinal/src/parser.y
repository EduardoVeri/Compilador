%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"

#define YYSTYPE PONTEIRONO
#define MAX_NOS 1000

static int yylex(void);
void yyerror(char* s);
int yyparse(void);

char auxNome[MAXLEXEMA];
char id[MAXLEXEMA];
enum yytokentype auxErro;

int teste = 0;

//No raiz da arvore sintatica
PONTEIRONO arvoreSintatica;

/* Vetor com os nos alocados da arvore, que sera utilizado
caso um erro aconteca durante a criacao da mesma.
Apos ocorrer um erro, o parser interrompe seu funcionamento
voltando para a main() sem adicionar o seu no raiz ao ponteiro acima.
Isso faz com que os nos alocados sejam perdidos e esse vetor fara
com que eles possam ser apagados mesmo assim. */
PONTEIRONO nos[MAX_NOS];
int qntNos = 0;

void mostraArvore(PONTEIRONO raiz, int num);
enum yytokentype getToken(void);
PONTEIRONO parse(void);

char auxLexema[MAXLEXEMA];

%}
/*
Declaracao dos tokens que serao utilizados durante o processo de analise
sintatica. 
*/

%expect 1

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

						strcpy(aux->lexema, pilha[indPilha]);
						indPilha--;

						//strcpy(aux->lexema, id);
						adicionaFilho($$, aux);

						nos[qntNos] = aux;
						qntNos++;

						}
					| tipo_especificador ID ABRECOLCHETES NUM FECHACOLCHETES SEMICOLON {
						$$ = $1;
						$$->tipo = DECLARACAO;
						$$->tipoDeclaracao = VetDeclK;
						$$->numLinha = qntLinhas;

						PONTEIRONO aux = novoNo();
						PONTEIRONO aux2 = novoNo();

						strcpy(aux->lexema, pilha[indPilha--]);

						nos[qntNos] = aux;
						qntNos++;

						strcpy(aux2->lexema, pilha[indPilha--]);
						
						adicionaFilho($$, aux2);
						adicionaFilho($$, aux);

						nos[qntNos] = aux2;
						qntNos++;
					}
					;

tipo_especificador 	: INT {
						$$ = novoNo();
						strcpy($$->lexema, "INT");
						$$->numLinha = qntLinhas;

						nos[qntNos] = $$;
						qntNos++;
					}
					| VOID {
						$$ = novoNo();
						strcpy($$->lexema, "VOID");
						$$->numLinha = qntLinhas;

						nos[qntNos] = $$;
						qntNos++;
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

						strcpy($$->lexema, pilha[indPilha]);
						indPilha--;

						//strcpy($$->lexema, auxNome);
						$$->numLinha = qntLinhas;

						nos[qntNos] = $$;
						qntNos++;
					}
					;	

params				: param_lista {$$ = $1;}
					| VOID {
						$$ = novoNo();
						$$->tipo = DECLARACAO;
						$$->numLinha = qntLinhas;
						$$->tipoDeclaracao = ParamVoid;
						strcpy($$->lexema, "VOID");

						nos[qntNos] = $$;
						qntNos++;
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

						strcpy(aux->lexema, pilha[indPilha]);
						indPilha--;
					
						//strcpy(aux->lexema, id);
						adicionaFilho($$, aux);

						nos[qntNos] = aux;
						qntNos++;

					}
					| tipo_especificador ID ABRECOLCHETES FECHACOLCHETES {
						$$ = $1;
						$$->tipo = DECLARACAO;
						$$->numLinha = qntLinhas;
						$$->tipoDeclaracao = VetParamK;
						PONTEIRONO aux = novoNo();

						strcpy(aux->lexema, pilha[indPilha]);
						indPilha--;

						//strcpy(aux->lexema, id);
						adicionaFilho($$, aux);		

						nos[qntNos] = aux;
						qntNos++;	
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
			
selecao_decl		: IF ABREPARENTESES expressao FECHAPARENTESES statement fatoracao{
						$$ = novoNo();
						strcpy($$->lexema, "IF");
						$$->tipo = DECLARACAO;
						$$->numLinha = qntLinhas;
						$$->tipoDeclaracao = IfK;

						adicionaFilho($$, $3);
						adicionaFilho($$, $5);		
						if($6 != NULL){
							adicionaFilho($$, $6);
						}

						nos[qntNos] = $$;
						qntNos++;
					}
					;

fatoracao			: ELSE statement {$$ = $2;}
					| %empty {$$ = NULL;}
					;
			
iteracao_decl		: WHILE ABREPARENTESES expressao FECHAPARENTESES statement {
						$$ = novoNo();
						strcpy($$->lexema, "WHILE");
						$$->tipo = DECLARACAO;
						$$->numLinha = qntLinhas;
						$$->tipoDeclaracao = WhileK;

						adicionaFilho($$, $3);
						adicionaFilho($$, $5);

						nos[qntNos] = $$;
						qntNos++;

					}
					;
			
retorno_decl		: RETURN SEMICOLON { 
						$$ = novoNo();
						$$->tipo = DECLARACAO;
						$$->numLinha = qntLinhas;
						$$->tipoDeclaracao = ReturnVOID;
						strcpy($$->lexema, "ReturnVOID");

						nos[qntNos] = $$;
						qntNos++;
						
					}
					| RETURN expressao SEMICOLON {
						$$ = novoNo();
						$$->tipo = DECLARACAO;
						$$->numLinha = qntLinhas;
						$$->tipoDeclaracao = ReturnINT;
						strcpy($$->lexema, "ReturnINT");

						adicionaFilho($$, $2);

						nos[qntNos] = $$;
						qntNos++;
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

						nos[qntNos] = $$;
						qntNos++;

					}
					| simples_expressao {$$ = $1;}
					;

var 				: ID {
						$$ = novoNo();
						$$->tipo = EXPRESSAO;
						$$->numLinha = qntLinhas;
						$$->tipoExpressao = IdK;
						
						
						strcpy($$->lexema, pilha[indPilha]);
						/*
						FILE * arquivoAux = fopen("arquivoAux.txt", "a+");
						fprintf(arquivoAux, "%s\n", $$->lexema);
						fclose(arquivoAux);
						*/
						indPilha--;
						//strcpy($$->lexema, id);

						nos[qntNos] = $$;
						qntNos++;

					}
					| ID ABRECOLCHETES expressao FECHACOLCHETES{
						$$ = novoNo();

						$$->tipo = EXPRESSAO;
						$$->numLinha = qntLinhas;
						$$->tipoExpressao = VetorK;
						
						//strcpy($$->lexema, id);
						strcpy($$->lexema, pilha[indPilha]);
						indPilha--;

						adicionaFilho($$, $3);

						nos[qntNos] = $$;
						qntNos++;
						
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

						nos[qntNos] = $$;
						qntNos++;
						
					}

					| NEQ {
						$$ = novoNo();
						strcpy($$->lexema, "!=");

						nos[qntNos] = $$;
						qntNos++;
						
					}

					| LT {
						$$ = novoNo();
						strcpy($$->lexema, "<");

						nos[qntNos] = $$;
						qntNos++;
						
					}
					
					| GT {
						$$ = novoNo();
						strcpy($$->lexema, ">");

						nos[qntNos] = $$;
						qntNos++;
						
					}
					
					| LET {
						$$ = novoNo();
						strcpy($$->lexema, "<=");

						nos[qntNos] = $$;
						qntNos++;
						
					}

					| GET {
						$$ = novoNo();
						strcpy($$->lexema, ">=");

						nos[qntNos] = $$;
						qntNos++;
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

						nos[qntNos] = $$;
						qntNos++;
					}
					| SUB {
						$$ = novoNo();
						strcpy($$->lexema, "-");

						nos[qntNos] = $$;
						qntNos++;
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

						nos[qntNos] = $$;
						qntNos++;
					}
					| DIV {
						$$ = novoNo();
						strcpy($$->lexema, "/");

						nos[qntNos] = $$;
						qntNos++;
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

						strcpy($$->lexema, pilha[indPilha]);
						indPilha--;

						//strcpy($$->lexema, auxNome);

						nos[qntNos] = $$;
						qntNos++;
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

//Funcao para mostrar o erro sintatico do codigo
void yyerror (char *s){
	printf("\n" ANSI_COLOR_RED "ERRO SINTATICO, LINHA: %d", qntLinhas);
	printf(ANSI_COLOR_RESET);
	switch(auxErro){
		case NUM:
			printf(": '%s' não era esperado (NUM)", yytext);
			break; 
		case SOMA:
			printf(": '%s' não era esperado (SOMA)", yytext);
			break;
		case SUB:
			printf(": '%s' não era esperado (SUB)", yytext);
			break;
		case MULT:
			printf(": '%s' não era esperado (MULT)", yytext);
			break;
		case DIV:
			printf(": '%s' não era esperado (DIV)", yytext);
			break;
		case INT:
			printf(": '%s' não era esperado (INT)", yytext);
			break;
		case ID:
			printf(": '%s' não era esperado (ID)", yytext);
			break;
		case VOID:
			printf(": '%s' não era esperado (VOID)", yytext);
			break;
		case WHILE:
			printf(": '%s' não era esperado (WHILE)", yytext);
			break;
		case ELSE:
			printf(": '%s' não era esperado (ELSE)", yytext);
			break;
		case IF:
			printf(": '%s' não era esperado (IF)", yytext);
			break;
		case ABREPARENTESES:
			printf(": '%s' não era esperado (ABREPARENTESES)", yytext);
			break;
		case FECHAPARENTESES:
			printf(": '%s' não era esperado (FECHAPARENTESES)", yytext);
			break;
		case RETURN:
			printf(": '%s' não era esperado (RETURN)", yytext);
			break;
		case COMMA:
			printf(": '%s' não era esperado (COMA)", yytext);
			break;
		case ABRECHAVES:
			printf(": '%s' não era esperado (ABRECHAVES)", yytext);
			break;
		case FECHACHAVES:
			printf(": '%s' não era esperado (FECHACHAVES)", yytext);
			break;
		case SEMICOLON:
			printf(": '%s' não era esperado (SEMICOLON)", yytext);
			break;
		case ATRIB:
			printf(": '%s' não era esperado (ATRIB)", yytext);
			break;
		case ABRECOLCHETES:
			printf(": '%s' não era esperado (ABRECOLCHETES)", yytext);
			break;
		case FECHACOLCHETES:
			printf(": '%s' não era esperado (FECHACOLCHETES)", yytext);
			break;
		case EQ:
			printf(": '%s' não era esperado (EQ)", yytext);
			break;
		case NEQ:
			printf(": '%s' não era esperado (NEQ)", yytext);
			break;
		case LT:
			printf(": '%s' não era esperado (LT)", yytext);
			break;
		case LET:
			printf(": '%s' não era esperado (LET)", yytext);
			break;
		case GT:
			printf(": '%s' não era esperado (GT)", yytext);
			break;
		case GET:
			printf(": '%s' não era esperado (GET)", yytext);
			break;
		case ERRO:
			printf(": '%s' não era esperado (ERRO)", yytext);
			break;
	}
	printf("\n");

	//Desaloca os nos ate o momento
	for(int i = 0; i < qntNos; i++){
		free(nos[i]);
	}
	arvoreSintatica = NULL;

}

int yylex(void)
{ return (auxErro = getToken()); }

PONTEIRONO parse(void)
{ 
	yyparse();
	return arvoreSintatica;
}

