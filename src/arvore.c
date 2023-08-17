#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include <strings.h>

//Cria um novo nó para a árvore, mas com os campos vazios.
PONTEIRONO novoNo(){
    PONTEIRONO novoNo = (PONTEIRONO)malloc(sizeof(NoArvore));

    novoNo->filho[0] = NULL;
    novoNo->filho[1] = NULL;
    novoNo->filho[2] = NULL;

    novoNo->irmao = NULL;

    bzero(novoNo->lexema, MAXLEXEMA);

    novoNo->numLinha = 0;

    novoNo->tipoDeclaracao = NuloDecl;

    novoNo->tipo= NENHUM;

    novoNo->tipoExpressao = NuloExp;

    return novoNo;
}

//Cria um nó para a árvore, com os campos preenchidos.
PONTEIRONO criaNo(char lexema[MAXLEXEMA], int numLinha, tipoNo tipoNo, tipoDECL tipoDeclaracao, tipoEXP tipoExpressao){
    PONTEIRONO novoNo = (PONTEIRONO)malloc(sizeof(NoArvore));

    novoNo->filho[0] = NULL;
    novoNo->filho[1] = NULL;
    novoNo->filho[2] = NULL;

    novoNo->irmao = NULL;

    strcpy(novoNo->lexema, lexema);

    novoNo->numLinha = numLinha;

    novoNo->tipoDeclaracao = tipoDeclaracao;

    novoNo->tipo = tipoNo;

    novoNo->tipoExpressao = tipoExpressao;

    return novoNo;
}

//Adiciona um irmão ao nó raiz.
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

//Adiciona um filho ao nó raiz.
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

//Desalocar Arvore
void desalocaArvore(PONTEIRONO raiz){
    if(raiz == NULL){
        return;
    }

    for(int i = 0; i < 3; i++){
        desalocaArvore(raiz->filho[i]);
    }
    desalocaArvore(raiz->irmao);

    free(raiz);
}

//Mostra a árvore
int flagMA = 0; //Flag para mostrar o primeiro print apenas uma vez.
void mostraArvore(PONTEIRONO raiz, int num){
    if(flagMA == 0){
        flagMA = 1;
        fprintf(arquivoSaida, "\n========== Arvore de Analise Sintatica ========== \n");
    }
    
    if(raiz == NULL){
        return;
    }

    for(int i = 0; i < num; i++){
        fprintf(arquivoSaida, "\t");
    }
    fprintf(arquivoSaida, "%s\n", raiz->lexema);
    
    for(int i = 0; i < 3; i++){
        mostraArvore(raiz->filho[i], num + 1);
    }
    mostraArvore(raiz->irmao, num);

    
}
