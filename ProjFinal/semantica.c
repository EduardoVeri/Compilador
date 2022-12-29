#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabelaSimb.h"
#include "semantica.h"
#include "global.h"

/*
Funcao para percorrer todos os nns da arvore sintatica e adicionar os itens de declaracao, como variaveis e funcoes,
na tabela de simbolos 
*/

void percorrerDecl(PONTEIRONO arvoreSintatica, PONTEIROITEM* tabelaHash, char* auxEscopo){
	tipoTipo tipo;
	PONTEIRONO auxNo = NULL;
	PONTEIROITEM auxItem = NULL;

	if(arvoreSintatica->tipoDeclaracao == FunDeclK){
		tipo = strcmp(arvoreSintatica->lexema, "INT") == 0 ? Type_Int : Type_Void;
		strcpy(auxEscopo, arvoreSintatica->filho[1]->lexema);

		if(buscaIgual(tabelaHash, arvoreSintatica, 1, auxEscopo) == 1){
			inserirTabela(tabelaHash, arvoreSintatica->tipoDeclaracao, tipo, arvoreSintatica->filho[1]->lexema, auxEscopo, arvoreSintatica->numLinha);
		}

		if(arvoreSintatica->filho[0]->tipoDeclaracao != ParamVoid){
			auxNo = arvoreSintatica->filho[0];
			while(auxNo != NULL){
				if(buscaIgual(tabelaHash, arvoreSintatica, 0, auxEscopo) == 1){
					if(strcmp(auxNo->lexema, "INT") == 0){
						strcpy(auxEscopo, arvoreSintatica->filho[1]->lexema);
						inserirTabela(tabelaHash, auxNo->tipoDeclaracao, Type_Int, auxNo->filho[0]->lexema, auxEscopo, arvoreSintatica->numLinha);
					}
					else{
						mostrarErroSemantico(DeclVoidVar, auxNo->filho[0]->lexema, auxNo->numLinha);
					}
				}
				auxNo = auxNo->irmao;
			}
		}
	}
	else if((arvoreSintatica->tipoDeclaracao == VarDeclK) || (arvoreSintatica->tipoDeclaracao == VetDeclK)){
		if(buscaIgual(tabelaHash, arvoreSintatica, 0, auxEscopo) == 1){
			if(strcmp(arvoreSintatica->lexema, "INT") == 0){
				inserirTabela(tabelaHash, arvoreSintatica->tipoDeclaracao, Type_Int, arvoreSintatica->filho[0]->lexema, auxEscopo, arvoreSintatica->numLinha);
			}
			else{
				mostrarErroSemantico(DeclVoidVar, arvoreSintatica->filho[0]->lexema, arvoreSintatica->numLinha);
			}
		}
	}
}

void percorrerExp(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[], char escopo[]){
	PONTEIRONO auxNo = NULL;
	PONTEIROITEM auxItem = NULL;
	tipoEXP tipo = arvoreSintatica->tipoExpressao;

	if(tipo == IdK){
		if((auxItem = procuraTabelaExp(tabelaHash, arvoreSintatica->lexema, escopo, arvoreSintatica->tipoExpressao)) == NULL){
			mostrarErroSemantico(VarNaoDeclarada, arvoreSintatica->lexema, arvoreSintatica->numLinha);
		}
		else{
			adicionaLinha(auxItem, arvoreSintatica->numLinha);
		}
	}
	else if(tipo == AtivK){
		if((auxItem = procuraTabelaExp(tabelaHash, arvoreSintatica->lexema, escopo, arvoreSintatica->tipoExpressao)) == NULL){
			mostrarErroSemantico(FuncaoNaoDeclarada, arvoreSintatica->lexema, arvoreSintatica->numLinha);
		}
		else{
			adicionaLinha(auxItem, arvoreSintatica->numLinha);
		}
	}
	else if(tipo == AssignK){
		if(arvoreSintatica->filho[1]->tipoExpressao == AtivK){
			auxItem = procuraTabelaExp(tabelaHash, arvoreSintatica->filho[1]->lexema, escopo, arvoreSintatica->filho[1]->tipoExpressao);
			if(auxItem != NULL){
				if(auxItem->tipoDado == Type_Void){
					mostrarErroSemantico(AtribFuncVoid, arvoreSintatica->filho[1]->lexema, arvoreSintatica->filho[1]->numLinha);
				}
			}
		}
	}
}

// Função que percorre a árvore sintática
void percorrerArvore(PONTEIRONO arvoreSintatica, PONTEIROITEM* tabelaHash, char* escopo){
	tipoTipo tipo;
	PONTEIRONO auxNo = NULL;
	PONTEIROITEM auxItem = NULL;

	char auxEscopo[250];

	strcpy(auxEscopo, escopo);

	if(arvoreSintatica == NULL){
		return;
	}

	if(arvoreSintatica->tipo == DECLARACAO){
		percorrerDecl(arvoreSintatica, tabelaHash, auxEscopo);
	}

	if(arvoreSintatica->tipo == EXPRESSAO){
		percorrerExp(arvoreSintatica, tabelaHash, auxEscopo);
	}

	for(int i = 0; i < 3; i++){
		if(arvoreSintatica->filho[i] != NULL){
			percorrerArvore(arvoreSintatica->filho[i], tabelaHash, auxEscopo);
		}
	}

	percorrerArvore(arvoreSintatica->irmao, tabelaHash, auxEscopo);
}


int buscaIgual(PONTEIROITEM* tabelaHash, PONTEIRONO arvoreSintatica, int indice, char* escopo){
	PONTEIROITEM auxItem = NULL;
	
	if((auxItem = procuraTabela(tabelaHash, arvoreSintatica->filho[indice]->lexema, escopo, arvoreSintatica->tipoDeclaracao)) == NULL){
		return 1;
	}
	
	tipoDECL tipoItem = auxItem->tipoIdentificador;
	tipoDECL tipoArvore = arvoreSintatica->tipoDeclaracao;

	if(tipoItem == FunDeclK && tipoArvore == FunDeclK){
		mostrarErroSemantico(DeclFuncExiste, arvoreSintatica->filho[indice]->lexema, arvoreSintatica->numLinha);
	}
	//Nessa verificação é preciso analisar o escopo, pois é possível declarar uma variável com o mesmo nome em escopos diferentes
	else if((tipoItem == VetDeclK || tipoItem == VarDeclK || tipoItem == VarParamK || tipoItem == VetParamK) && (tipoArvore == VetDeclK || tipoArvore == VarDeclK || tipoArvore == VarParamK || tipoArvore == VetParamK)){
		if((strcmp(auxItem->escopo, escopo) != 0) && ((strcmp(auxItem->escopo, "global") != 0)))
			return 1;
		
		mostrarErroSemantico(DeclVarExiste, arvoreSintatica->filho[indice]->lexema, arvoreSintatica->numLinha);
	}
	else if((tipoItem == VetDeclK || tipoItem == VarDeclK || tipoItem == VarParamK || tipoItem == VetParamK) && tipoArvore == FunDeclK){
		mostrarErroSemantico(DeclFuncVar, arvoreSintatica->filho[indice]->lexema, arvoreSintatica->numLinha);
	}
	else if ( tipoItem == FunDeclK && (tipoArvore == VetDeclK || tipoArvore == VarDeclK || tipoArvore == VarParamK || tipoArvore == VetParamK)){
		mostrarErroSemantico(DeclVarFunc, arvoreSintatica->filho[indice]->lexema, arvoreSintatica->numLinha);
	}

	return 0;
	
}


void mostrarErroSemantico(erroSemantico erro, char* nome, int linha){
	printf(ANSI_COLOR_RED "ERRO SEMANTICO, LINHA: %d" ANSI_COLOR_RESET, linha);
	switch (erro){
		case DeclVoidVar:
			printf(": Variavel '%s' declarada como void\n\n", nome);
			break;
		case DeclFuncExiste:
			printf(": Funcao '%s' ja declarada\n\n", nome);
			break;
		case DeclVarExiste:
			printf(": Variavel '%s' ja declarada\n\n", nome);
			break;
		case DeclFuncVar:
			printf(": Identificador '%s' ja declarado como variavel\n\n", nome);
			break;
		case DeclVarFunc:
			printf(": Identificador '%s' ja declarado como funcao\n\n", nome);
			break;
		case VarNaoDeclarada:
			printf(": Variavel '%s' nao declarada\n\n", nome);
			break;
		case FuncaoNaoDeclarada:
			printf(": Funcao '%s' nao declarada\n\n", nome);
			break;
		case AtribFuncVoid:
			printf(": Atribuicao invalida: funcao '%s' do tipo void \n\n", nome);
			break;	
		case FuncMainNaoDeclarada:
			printf(": Funcao main nao declarada\n\n");
			break;
	}
}