/* Arquivo para armazenar as funcoes para a estrutura
de dados que armazena as labels e seus enederecos de memoria */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "label.h"

// Vetor de labels
VETOR_LABEL * vetorLabel = NULL;

// Inicializa o vetor de labels
void inicializaLabels(){
	vetorLabel = (VETOR_LABEL *)malloc(sizeof(VETOR_LABEL));
	vetorLabel->tamanho = -1;
	vetorLabel->vetor = NULL;
}

// Cria um novo no de label
LABEL * criarNoLabel(char *nome, int endereco){
	LABEL * novoNoLabel = (LABEL *)malloc(sizeof(LABEL));
	novoNoLabel->nome = nome;
	novoNoLabel->endereco = endereco;
	novoNoLabel->prox = NULL;
	return novoNoLabel;
}

// Adiciona uma label ao vetor de labels
void adicionarLabel(char *nome, int endereco){
	LABEL * novoNoLabel = criarNoLabel(nome, endereco);
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
int getEnderecoLabel(char *nome){
	LABEL * aux = vetorLabel->vetor;
	while(aux != NULL){
		if(strcmp(aux->nome, nome) == 0){
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