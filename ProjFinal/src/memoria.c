/* Arquivo .c para poder gerenciar a memoria de cada funcao
As divisoes devem ser: parametros, vinculo de controle, endereco de retorno e
as variaveis estaticas */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "memoria.h"
#include "global.h"


MEMORIA_FUNCOES* global = NULL;

void inicializa_memoria(MEMORIA *memoria){
	MEMORIA_FUNCOES* func_global = (MEMORIA_FUNCOES *) malloc(sizeof(MEMORIA_FUNCOES));
	func_global->tamanho = 0;
	func_global->nome = strdup("global");
	func_global->prox = NULL;
	func_global->tabelaVar = NULL;
	
	global = func_global; // Variavel global para a funcao get_variavel

	memoria->tamanho = 1;
	memoria->funcoes = func_global;
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
	insere_variavel(funcao, "Registrador Temporario", inteiro);
	insere_variavel(funcao, "Registrador $fp", inteiro);
	insere_variavel(funcao, "Registrador $sp", inteiro);


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
	if(funcao == NULL){
		printf(ANSI_COLOR_RED); printf("ERRO: "); printf(ANSI_COLOR_RESET);
		printf("NULL passado como argumento em insere_variavel\n");
		return;
	}
	
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

	if(tipo == inteiroArg || tipo == vetorArg){
		aux = funcao->tabelaVar;
		funcao->tabelaVar = variavel;
		variavel->prox = aux;
		variavel->indice = 0;
		funcao->tamanho++;

		for(int i = 1; aux != NULL; i++){
			aux->indice = i;
			aux = aux->prox;
		}

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
	if(funcao == NULL){
		printf(ANSI_COLOR_RED); printf("ERRO: "); printf(ANSI_COLOR_RESET);
		printf("NULL passado como argumento em get_variavel\n");
		return NULL;
	}
	
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

	// Se nao estiver na funcao, procurar na tabela de globais
	aux = global;
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

	printf(ANSI_COLOR_RED); printf("Erro: "); printf(ANSI_COLOR_RESET);
	printf("Variavel %s nao encontrada\n", nome_variavel);

	return NULL;
}

void apagar_temp(MEMORIA_FUNCOES* funcao, int total_temp){
	VARIAVEL* aux = funcao->tabelaVar;
	VARIAVEL* aux2 = NULL;

	for(int i = funcao->tamanho - 1; i >= 0 && total_temp != 0; i--){
		for(int j = 0; i < funcao->tamanho; i++){
			aux2 = aux;
			aux = aux->prox;
		}
		if(aux->tipo == temp){
			total_temp--;
			aux2->prox == NULL;
			free(aux);

		}
	}
	
	printf(ANSI_COLOR_RED); printf("Erro: "); printf(ANSI_COLOR_RESET);
	printf("Param's nao apagados! %d\n", total_temp);
}


void imprime_memoria(MEMORIA memoria){
	MEMORIA_FUNCOES* aux = memoria.funcoes;
	VARIAVEL* aux2 = NULL;

	for(int i = 0; i < memoria.tamanho; i++, aux = aux->prox){

		printf("===============================================\n");
		printf("\t\t%s: %d\n", aux->nome, aux->tamanho);
		printf("===============================================\n");

		int fp = get_fp(aux);
		int sp = get_sp(aux);

		aux2 = aux->tabelaVar;
		for (int j = 0; j < aux->tamanho; j++, aux2 = aux2->prox){
			if(j == sp){
				printf("$sp -> ");
			}
			if(j == fp){
				printf("$fp -> ");
			}
			printf("\t%d: %s [$fp + %d] [$sp - %d]\n",
				aux2->indice, aux2->nome, get_fp_relation(aux, aux2), get_sp_relation(aux, aux2));
		}
	}
			
		

/* 		printf("$fp ->");
		while(aux2 != NULL){
			if(aux2->prox == NULL) printf("$sp -> ");
			printf("\t%d: %s [$fp + %d] [$sp - %d]\n",
					aux2->indice, aux2->nome, get_fp_relation(aux, aux2), get_sp_relation(aux, aux2));
			aux2 = aux2->prox;
		}
		aux = aux->prox;
		printf("\n"); */
	//}
}

MEMORIA_FUNCOES* buscar_funcao(MEMORIA* memoria, char* nome_funcao){
	if(memoria == NULL || nome_funcao == NULL){
		printf(ANSI_COLOR_RED); printf("Erro: "); printf(ANSI_COLOR_RESET);
		printf("NULL passado como argumento em buscar_funcao\n");
		return NULL;
	}
	
	MEMORIA_FUNCOES* aux = memoria->funcoes;
	while(aux != NULL){
		if(strcmp(aux->nome, nome_funcao) == 0){
			return aux;
		}
		aux = aux->prox;
	}

	printf(ANSI_COLOR_RED); printf("Erro: "); printf(ANSI_COLOR_RESET);
	printf("Funcao %s nao encontrada\n", nome_funcao);

	return NULL;
}


int get_sp_relation(MEMORIA_FUNCOES* funcao, VARIAVEL* var){
	if(funcao == NULL || var == NULL){
		printf(ANSI_COLOR_RED); printf("Erro: "); printf(ANSI_COLOR_RESET);
		printf("NULL passado como argumento em get_sp_relation\n");
		return -1;
	}
	
	return funcao->tamanho - var->indice - 1;
}

int get_fp_relation(MEMORIA_FUNCOES* funcao, VARIAVEL* var){
	if(funcao == NULL || var == NULL){
		printf(ANSI_COLOR_RED);
		printf("Erro: ");
		printf(ANSI_COLOR_RESET);
		printf("NULL passado como argumento em get_fp_relation\n");
		return -1;
	}

	if(funcao == global) return var->indice;
	
	return var->indice - get_fp(funcao);
}

int get_sp(MEMORIA_FUNCOES* funcao){
	if(funcao == NULL){
		printf(ANSI_COLOR_RED); printf("Erro: "); printf(ANSI_COLOR_RESET);
		printf("NULL passado como argumento em get_sp\n");
		return -1;
	}
	
	return funcao->tamanho-1;
}

int get_fp(MEMORIA_FUNCOES* funcao){
	if(funcao == NULL){
		printf(ANSI_COLOR_RED); printf("Erro: "); printf(ANSI_COLOR_RESET);
		printf("NULL passado como argumento em get_fp\n");
		return -1;
	}
	if (funcao == global) return 0;
	//return (get_variavel(funcao, "Vinculo Controle")->indice);
	return 0;
}
