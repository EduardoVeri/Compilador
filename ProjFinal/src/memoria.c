/* Arquivo .c para poder gerenciar a memoria de cada funcao
As divisoes devem ser: parametros, vinculo de controle, endereco de retorno e
as variaveis estaticas */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "memoria.h"
#include "global.h"

void inicializa_memoria(MEMORIA *memoria){
	MEMORIA_FUNCOES* global = (MEMORIA_FUNCOES *) malloc(sizeof(MEMORIA_FUNCOES));
	global->tamanho = 0;
	global->nome = strdup("global");
	global->prox = NULL;
	global->tabelaVar = NULL;
	
	memoria->tamanho = 1;
	memoria->funcoes = global;
}

MEMORIA_FUNCOES* insere_funcao(MEMORIA *memoria, char * nome_funcao){
	MEMORIA_FUNCOES* funcao = (MEMORIA_FUNCOES *) malloc(sizeof(MEMORIA_FUNCOES));
	funcao->tamanho = 0;
	funcao->nome = nome_funcao;
	funcao->prox = NULL;
	funcao->tabelaVar = NULL;
	MEMORIA_FUNCOES* aux = NULL;

	insere_variavel(funcao, "Vinculo Controle", controle);
	insere_variavel(funcao, "Endereco Retorno", retorno);


	if(memoria->tamanho == 0){
		memoria->funcoes = funcao;
		memoria->tamanho++;
		return funcao;
	}

	aux = memoria->funcoes;
	while(aux->prox != NULL){
		aux = aux->prox;
	}

	aux->prox = funcao;
	memoria->tamanho++;

	return funcao;

}

void insere_variavel(MEMORIA_FUNCOES* funcao, char * nome_variavel, TIPO_VAR tipo){
	VARIAVEL* variavel = (VARIAVEL *) malloc(sizeof(VARIAVEL));
	variavel->tipo = tipo;
	variavel->nome = nome_variavel;
	variavel->prox = NULL;

	VARIAVEL* aux = NULL;

	if(funcao->tabelaVar == NULL){
		funcao->tabelaVar = variavel;
		variavel->indice = funcao->tamanho;
		funcao->tamanho++;
		return;
	}
	
	aux = funcao->tabelaVar;
	while(aux->prox != NULL){
		aux = aux->prox;
	}
	aux->prox = variavel;
    variavel->indice = funcao->tamanho;
	funcao->tamanho++;
}

VARIAVEL* get_variavel(MEMORIA_FUNCOES* funcao, char * nome_variavel){
	MEMORIA_FUNCOES* aux = funcao;
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
		printf("===============================================\n");
		printf("\t\t%s\n", aux->nome);
		printf("===============================================\n");
		aux2 = aux->tabelaVar;
		printf("$fp ->");
		while(aux2 != NULL){
			if(aux2->prox == NULL)
				printf("$sp -> ");
			printf("\t%d: %s [$fp + %d] [$sp - %d]\n",
					aux2->indice, aux2->nome, get_fp_relation(aux, aux2), get_sp_relation(aux, aux2));
			aux2 = aux2->prox;
		}
		aux = aux->prox;
		printf("\n");
	}
}

MEMORIA_FUNCOES* buscar_funcao(MEMORIA* memoria, char* nome_funcao){
	MEMORIA_FUNCOES* aux = memoria->funcoes;
	while(aux != NULL){
		if(strcmp(aux->nome, nome_funcao) == 0){
			return aux;
		}
		aux = aux->prox;
	}
	printf(ANSI_COLOR_RED);
	printf("ERRO: ");
	printf(ANSI_COLOR_RESET);
	printf("Funcao %s nao encontrada\n", nome_funcao);

	return NULL;
}


int get_sp_relation(MEMORIA_FUNCOES* funcao, VARIAVEL* var){
	return funcao->tamanho - var->indice - 1;
}

int get_fp_relation(MEMORIA_FUNCOES* funcao, VARIAVEL* var){
	return var->indice;
}

int get_sp(MEMORIA_FUNCOES* funcao){
	return funcao->tamanho-1;
}

int get_fp(MEMORIA_FUNCOES* funcao){
	return 0;
}
