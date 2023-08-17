/* Arquivo para armazenar as funcoes para a estrutura
de dados que armazena as labels e seus enederecos de memoria */

// TODO: Modificar o vetor de labels para armazenar um char ao inves de int

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "label.h"

/* Lista para armazenar os valores das linhas em que 
uma label precisa ser adicionada depois quando o codigo assembly
tiver finalizado */
/* FILA_LINHAS filaLinhas;

void inicializaFilaLinhas(){
    filaLinhas.qntd = -1;
    for(int i = 0; i < 20; i++){
        filaLinhas.linhas[i].linha = -1;
        filaLinhas.linhas[i].numLabel = -1;
    }
}

void adicionaListaLinhas(int linha, int label){
    if(filaLinhas.qntd == -1){
        filaLinhas.qntd = 0;
        filaLinhas.linhas[0].linha = linha;
        filaLinhas.linhas[0].numLabel = label;
        return;
    }
    filaLinhas.qntd++;
    filaLinhas.linhas[filaLinhas.qntd].linha = linha;
    filaLinhas.linhas[filaLinhas.qntd].numLabel = label;
}

int buscarLinha(int label){
    for(int i = 0; i < filaLinhas.qntd; i++){
        if(filaLinhas.linhas[i].numLabel == label){
            return filaLinhas.linhas[i].linha;
        }
    }
    return -1;
}

void removeLinha(int linha){
    if(filaLinhas.qntd == -1){
        return;
    }

} */


// Vetor de labels
VETOR_LABEL * vetorLabel = NULL;

// Inicializa o vetor de labels
void inicializaLabels(){
    vetorLabel = (VETOR_LABEL *)malloc(sizeof(VETOR_LABEL));
    vetorLabel->tamanho = -1;
    vetorLabel->vetor = NULL;
}

// Cria um novo no de label
LABEL * criarNoLabel(char* id, int endereco){
    LABEL * novoNoLabel = (LABEL *)malloc(sizeof(LABEL));
    novoNoLabel->id = strdup(id);
    novoNoLabel->endereco = endereco;
    novoNoLabel->prox = NULL;
    return novoNoLabel;
}

// Adiciona uma label ao vetor de labels
void adicionarLabel(char* id, int endereco){
    LABEL * novoNoLabel = criarNoLabel(id, endereco);
    if(vetorLabel->tamanho == -1){
        vetorLabel->vetor = novoNoLabel;
        vetorLabel->tamanho = 0;
        return;
    }

    LABEL * aux = vetorLabel->vetor;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    aux->prox = novoNoLabel;
    vetorLabel->tamanho++;
}

// Retorna o endereco de uma label
int getEnderecoLabel(char* id){
    LABEL * aux = vetorLabel->vetor;
    while(aux != NULL){
        if(!strcmp(aux->id, id)){
            return aux->endereco;
        }
        aux = aux->prox;
    }
    return -1;
}

// Libera o vetor de labels
void liberarLabels(){
    LABEL * aux = vetorLabel->vetor;
    while(aux != NULL){
        LABEL * aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }
    free(vetorLabel);
}

// Imprime o vetor de labels
void imprimirLabels(){
    LABEL * aux = vetorLabel->vetor;

    printf("\n============= Vetor de labels =============\n");
    while(aux != NULL){
        printf("%s, Endereco: %d\n", aux->id, aux->endereco);
        aux = aux->prox;
    }
}