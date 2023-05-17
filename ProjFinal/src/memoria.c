/* Arquivo .c para poder gerenciar a memoria de cada funcao
As divisoes devem ser: parametros, vinculo de controle, endereco de retorno e
as variaveis estaticas */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "memoria.h"

void inicializa_memoria(MEMORIA memoria){
	memoria.tamanho = 0;
	memoria.funcoes = NULL;
}

void insere_funcao(MEMORIA *memoria, char * nome_funcao){
	MEMORIA_FUNCOES* funcao = (MEMORIA_FUNCOES *) malloc(sizeof(MEMORIA_FUNCOES));
	funcao->tamanho = 0;
	funcao->nome = nome_funcao;
	funcao->prox = NULL;
	funcao->tabelaVar = NULL;

	MEMORIA_FUNCOES* aux = NULL;

	if(memoria->tamanho == 0){
		memoria->funcoes = funcao;
		memoria->tamanho++;
		return;
	}
	
	aux = memoria->funcoes;
	while(aux->prox != NULL){
		aux = aux->prox;
	}
	aux->prox = funcao;
	
	memoria->funcoes = funcao;
	memoria->tamanho++;
}

void insere_variavel(MEMORIA *memoria, char * nome_variavel, TIPO_VAR tipo){
	VARIAVEL* variavel = (VARIAVEL *) malloc(sizeof(VARIAVEL));
	variavel->tipo = tipo;
	variavel->nome = nome_variavel;
	variavel->prox = NULL;

	VARIAVEL* aux = NULL;

	if(memoria->funcoes->tabelaVar == NULL){
		memoria->funcoes->tabelaVar = variavel;
		memoria->funcoes->tamanho++;
		return;
	}
	
	aux = memoria->funcoes->tabelaVar;
	while(aux->prox != NULL){
		aux = aux->prox;
	}
	aux->prox = variavel;
	
	memoria->funcoes->tamanho++;
}

VARIAVEL* get_variavel(MEMORIA memoria, char * nome_variavel){
	MEMORIA_FUNCOES* aux = memoria.funcoes;
	VARIAVEL* aux2 = NULL;
	while(aux != NULL){
		aux2 = aux->tabelaVar;
		while(aux2 != NULL){
			if(strcmp(aux2->nome, nome_variavel) == 0){
				return aux2;
			}
			aux2 = aux2->prox;
		}
		aux = aux->prox;
	}
	return NULL;
}

void imprime_memoria(MEMORIA memoria){
	MEMORIA_FUNCOES* aux = memoria.funcoes;
	VARIAVEL* aux2 = NULL;
	while(aux != NULL){
		printf("Funcao: %s\n", aux->nome);
		printf("Tamanho: %d\n", aux->tamanho);
		aux2 = aux->tabelaVar;
		while(aux2 != NULL){
			printf("Variavel: %s\n", aux2->nome);
			printf("Tipo: %d\n", aux2->tipo);
			aux2 = aux2->prox;
		}
		aux = aux->prox;
	}
}



int get_sp(MEMORIA memoria, char * nome_funcao){
	MEMORIA_FUNCOES* aux = memoria.funcoes;
	while(aux != NULL){
		if(strcmp(aux->nome, nome_funcao) == 0){
			return aux->tamanho;
		}
		aux = aux->prox;
	}
	return -1;
}

int get_fp(MEMORIA memoria, char* nome_funcao){
	return 0;
}