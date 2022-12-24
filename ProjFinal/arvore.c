#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"


PONTEIRONO novoNo(){
    PONTEIRONO novoNo = (PONTEIRONO)malloc(sizeof(NoArvore));

    novoNo->filho[0] = NULL;
    novoNo->filho[1] = NULL;
    novoNo->filho[2] = NULL;

    novoNo->irmao = NULL;

    strcpy(novoNo->lexema, "");

    novoNo->numLinha = 0;

    novoNo->tipoDecl = 0;

    novoNo->tipoNo = 0;

    return novoNo;
}


PONTEIRONO criaNo(char lexema[26], int numLinha, int tipoDecl, int tipoNo){
    PONTEIRONO novoNo = (PONTEIRONO)malloc(sizeof(NoArvore));

    novoNo->filho[0] = NULL;
    novoNo->filho[1] = NULL;
    novoNo->filho[2] = NULL;

    novoNo->irmao = NULL;

    strcpy(novoNo->lexema, lexema);

    novoNo->numLinha = numLinha;

    novoNo->tipoDecl = tipoDecl;

    novoNo->tipoNo = tipoNo;

    return novoNo;
}


PONTEIRONO adicionaIrmao(PONTEIRONO raiz, PONTEIRONO no){
    PONTEIRONO aux = raiz;

    if(aux == NULL){
        return NULL;
    }

    while(aux->irmao != NULL){
        aux = aux->irmao;
    }

    aux->irmao = no;

    return raiz;
}

PONTEIRONO adicionaFilho(PONTEIRONO raiz, PONTEIRONO no){
    PONTEIRONO aux = raiz;
    int i;

    if(aux == NULL){
        return NULL;
    }

    for(i = 0; i < 3 && aux->filho[i] != NULL; i++);

    aux->filho[i] = no;

    return raiz;
}

int flagMA = 0;
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