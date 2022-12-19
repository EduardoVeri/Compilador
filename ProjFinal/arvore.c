#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"


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

    while(aux->irmao != NULL){
        aux = aux->irmao;
    }

    aux->irmao = no;

    return raiz;
}

PONTEIRONO adicionaFilho(PONTEIRONO raiz, PONTEIRONO no){
    PONTEIRONO aux = raiz;
    int i;

    for(i = 0; i < 3 && aux->filho[i] != NULL; i++);

    aux->filho[i] = no;

    return raiz;
}

int main(){
    printf("Hello");
    return 0;
}
