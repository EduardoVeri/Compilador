#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabelaSimb.h"
#include "semantica.h"
#include "global.h"

int teveErroSemantico = 0;

/*
Funcoes para percorrer todos os nos da arvore sintatica e adicionar os itens de declaracao, como variaveis e funcoes,
na tabela de simbolos 
*/

//Funcao que percorre a arvore sintatica e chama as funcoes para adicionar os itens de declaracao na tabela de simbolos
void percorrerDecl(PONTEIRONO arvoreSintatica, PONTEIROITEM* tabelaHash, char* auxEscopo){
	tipoTipo tipo;
	PONTEIRONO auxNo = NULL;
	PONTEIROITEM auxItem = NULL;

    //Verifica se o no atual e uma declaracao de funcao
	if(arvoreSintatica->tipoDeclaracao == FunDeclK){
		tipo = strcmp(arvoreSintatica->lexema, "INT") == 0 ? Type_Int : Type_Void;
		strcpy(auxEscopo, arvoreSintatica->filho[1]->lexema);
    
        //Verifica se a funcao ja foi declarada
		if(buscaIgual(tabelaHash, arvoreSintatica, 1, auxEscopo) == 1){
			inserirTabela(tabelaHash, arvoreSintatica->tipoDeclaracao, tipo, arvoreSintatica->filho[1]->lexema, auxEscopo, arvoreSintatica->numLinha);
		}

        //Verifica se a funcao tem parametros
		if(arvoreSintatica->filho[0]->tipoDeclaracao != ParamVoid){
			auxNo = arvoreSintatica->filho[0];
			//Se sim, adiciona os parametros na tabela de simbolos
            while(auxNo != NULL){
                //Verifica se o parametro ja foi declarado
				if(buscaIgual(tabelaHash, auxNo, 0, auxEscopo) == 1){
					//Verifica se o parametro eh do tipo inteiro
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
    //Verifica se o no atual e uma declaracao de variavel ou vetor
	else if((arvoreSintatica->tipoDeclaracao == VarDeclK) || (arvoreSintatica->tipoDeclaracao == VetDeclK)){
		if(buscaIgual(tabelaHash, arvoreSintatica, 0, auxEscopo) == 1){
			//Verifica se a variavel eh do tipo inteiro
            if(strcmp(arvoreSintatica->lexema, "INT") == 0){
				inserirTabela(tabelaHash, arvoreSintatica->tipoDeclaracao, Type_Int, arvoreSintatica->filho[0]->lexema, auxEscopo, arvoreSintatica->numLinha);
			}
			else{
				mostrarErroSemantico(DeclVoidVar, arvoreSintatica->filho[0]->lexema, arvoreSintatica->numLinha);
			}
		}
	}
}

//Funcao que percorre a arvore sintatica e chama as funcoes verificar erros com as expressoes
void percorrerExp(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[], char escopo[]){
	PONTEIRONO auxNo = NULL;
	PONTEIROITEM auxItem = NULL;
	tipoEXP tipo = arvoreSintatica->tipoExpressao;


    //Verifica se o no atual eh um uso de variavel
	if(tipo == IdK){
        //Verifica se a variavel foi declarada
		if((auxItem = procuraTabelaExp(tabelaHash, arvoreSintatica->lexema, escopo, arvoreSintatica->tipoExpressao)) == NULL){
			mostrarErroSemantico(VarNaoDeclarada, arvoreSintatica->lexema, arvoreSintatica->numLinha);
		}
		else{
            //Adiciona a linha na lista de linhas do item
			adicionaLinha(auxItem, arvoreSintatica->numLinha);
		}
	}
    //Verifica se o no atual eh uma chamada de funcao
	else if(tipo == AtivK){
        //Verifica se a funcao foi declarada
		if((auxItem = procuraTabelaExp(tabelaHash, arvoreSintatica->lexema, escopo, arvoreSintatica->tipoExpressao)) == NULL){
			mostrarErroSemantico(FuncaoNaoDeclarada, arvoreSintatica->lexema, arvoreSintatica->numLinha);
		}
		else{
            //Adiciona a linha na lista de linhas do item
			adicionaLinha(auxItem, arvoreSintatica->numLinha);
		}
	}
    //Verifica se o no atual eh uma expressao de atribuicao
	else if(tipo == AssignK){
        //Verifica se existe uma funcao sendo atribuida a uma variavel
		if(arvoreSintatica->filho[1]->tipoExpressao == AtivK){
			auxItem = procuraTabelaExp(tabelaHash, arvoreSintatica->filho[1]->lexema, escopo, arvoreSintatica->filho[1]->tipoExpressao);
            /* Se aqui o resultado for nulo, entao a funcao nao foi declarada e ira cair 
            em uma outra verificacao de erro */
            if(auxItem != NULL){
                //Verifica se a funcao eh do tipo void
				if(auxItem->tipoDado == Type_Void){
					mostrarErroSemantico(AtribFuncVoid, arvoreSintatica->filho[1]->lexema, arvoreSintatica->filho[1]->numLinha);
				}
			}
		}
	}
	else if(tipo == VetorK){
		//Verifica se o vetor foi declarado
		if((auxItem = procuraTabelaExp(tabelaHash, arvoreSintatica->lexema, escopo, arvoreSintatica->tipoExpressao)) == NULL){
			mostrarErroSemantico(VetorNaoDeclarado, arvoreSintatica->lexema, arvoreSintatica->numLinha);
		}
		else{
			//Adiciona a linha na lista de linhas do item
			adicionaLinha(auxItem, arvoreSintatica->numLinha);
		}
	}
}

// Funcao que percorre a arvore sintatica
void percorrerArvore(PONTEIRONO arvoreSintatica, PONTEIROITEM* tabelaHash, char* escopo){
	tipoTipo tipo;
	PONTEIRONO auxNo = NULL;
	PONTEIROITEM auxItem = NULL;

	char auxEscopo[250];

	strcpy(auxEscopo, escopo);

	if(arvoreSintatica == NULL){
		return;
	}

    //Verifica se o no atual e uma declaracao de funcao
	if(arvoreSintatica->tipo == DECLARACAO){
		percorrerDecl(arvoreSintatica, tabelaHash, auxEscopo);
	}

    //Verifica se o no atual e uma expressao
	if(arvoreSintatica->tipo == EXPRESSAO){
		percorrerExp(arvoreSintatica, tabelaHash, auxEscopo);
	}

    //Percorre os filhos do no atual
	for(int i = 0; i < 3; i++){
		if(arvoreSintatica->filho[i] != NULL){
			percorrerArvore(arvoreSintatica->filho[i], tabelaHash, auxEscopo);
		}
	}

    //Percorre o irmao do no atual

	if(strcmp(escopo, "global") == 0)
		percorrerArvore(arvoreSintatica->irmao, tabelaHash, escopo);
	else
		percorrerArvore(arvoreSintatica->irmao, tabelaHash, auxEscopo);
}

//Funcao que verifica se a declaracao de uma funcao ou var ja existe
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

//Mostra uma mensagem de erro sobre o determinado erro semantico
void mostrarErroSemantico(erroSemantico erro, char* nome, int linha){
	teveErroSemantico++;
	
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
		case VetorNaoDeclarado:
			printf(": Vetor '%s' nao declarado\n\n", nome);
			break;
	}
}