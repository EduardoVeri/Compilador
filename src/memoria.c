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

    MEMORIA_FUNCOES* parametros = (MEMORIA_FUNCOES*)malloc(sizeof(MEMORIA_FUNCOES));

    parametros->tamanho = 0;
    parametros->nome = strdup("parametros");
    parametros->prox = NULL;
    parametros->tabelaVar = NULL;

    global->prox = parametros;

    memoria->tamanho = 2;
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
    insere_variavel(funcao, "Valor Retorno", retorno);
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
        printf(ANSI_COLOR_RED); printf("Erro: "); printf(ANSI_COLOR_RESET);
        printf("NULL passado como argumento em insere_variavel\n");
        return;
    }
    
    VARIAVEL* variavel = (VARIAVEL *) malloc(sizeof(VARIAVEL));
    variavel->tipo = tipo;
    variavel->nome = nome_variavel;
    variavel->prox = NULL;
    variavel->bool_global = (!strcmp(funcao->nome, "global") ? 1 : 0);

    VARIAVEL* aux = NULL;
        if(funcao->tabelaVar == NULL){
        funcao->tabelaVar = variavel;
        variavel->indice = funcao->tamanho;
        funcao->tamanho++;
        return;
    }

    if(tipo == inteiroArg || tipo == vetorArg){
        aux = funcao->tabelaVar;

        // Se for o primeiro argumento
        if(aux->tipo != inteiroArg && aux->tipo != vetorArg){
            variavel->prox = aux;
            funcao->tabelaVar = variavel;
        }
        else{
            while(aux->prox != NULL && (aux->prox->tipo == inteiroArg || aux->prox->tipo == vetorArg)){
                aux = aux->prox;
            }

            VARIAVEL* aux2 = aux->prox;

            aux->prox = variavel;
            variavel->prox = aux2;
        }

        funcao->tamanho++;
        
        // Atualizar os indices
        aux = funcao->tabelaVar;
        for(int i = 0; aux != NULL; i++){
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
        printf(ANSI_COLOR_RED); printf("Erro: "); printf(ANSI_COLOR_RESET);
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

void apagar_temp(MEMORIA_FUNCOES* funcao){
    if(!funcao){
        printf(ANSI_COLOR_RED); printf("Erro: "); printf(ANSI_COLOR_RESET);	
        printf("NULL passado como argumento em apagar_temp!\n");
        return;
    }

    VARIAVEL* aux = funcao->tabelaVar;
    VARIAVEL* aux2 = aux;
    
    // Caso nao tenha parametros
    if(funcao->tamanho == 0){
        printf("Nao ha temporarios a serem apagados!\n");
        return;
    }

    // Caso so tenha um parametro
    if(funcao->tamanho == 1){
        if(!strcmp(aux->nome, "Param")){
            free(aux);
            funcao->tamanho--;
            funcao->tabelaVar = NULL;
            return;
        }
    }

    // Caso tenha mais de um parametro
    while(aux->prox != NULL){
        aux2 = aux;
        aux = aux->prox;
    }

    if(!strcmp(aux->nome, "Param")){
        free(aux);
        aux2->prox = NULL;
        funcao->tamanho--;
        return;
    }

    printf(ANSI_COLOR_RED); printf("Erro: "); printf(ANSI_COLOR_RESET);
    printf("Param's nao apagados!\n");
}

void imprime_tipo(VARIAVEL* var){
    switch(var->tipo){
        case inteiro:
            printf("inteiro");
            break;
        case inteiroArg:
            printf("inteiroArg");
            break;
        case vetor:
            printf("vetor");
            break;
        case vetorArg:
            printf("vetorArg");
            break;
        case controle:
            printf("controle");
            break;
        case temp:
            printf("temp");
            break;
        case retorno:
            printf("retorno");
            break;
        default:
            printf("Erro: tipo nao reconhecido\n");
            break;
    }
}

void imprime_memoria(){
    MEMORIA_FUNCOES* aux = vetorMemoria.funcoes;
    VARIAVEL* aux2 = NULL;

    for(int i = 0; i < vetorMemoria.tamanho; i++, aux = aux->prox){

        printf("===============================================\n");
        printf("\t\t%s: %d\n", aux->nome, aux->tamanho);
        printf("===============================================\n");

        int fp = get_fp(aux);
        int sp = get_sp(aux);
        int flag_sp = 0;
        aux2 = aux->tabelaVar;
        for (int j = 0; j < aux->tamanho; j++, aux2 = aux2->prox){
            if(j == sp){
                printf("$sp -> ");
                flag_sp = 1;
            }
            if(j == fp){
                printf("$fp -> ");
            }
            printf("\t%d: %s [$fp + %d] [$sp - %d] : ",
                aux2->indice, aux2->nome, get_fp_relation(aux, aux2), get_sp_relation(aux, aux2));
            imprime_tipo(aux2); 
            aux2->bool_global ? printf(" global") : printf(" local");
            printf("\n");
        }
        if(!flag_sp && strcmp(aux->nome, "global")){
            printf("$sp -> \t%d:\n", sp);
        }
        flag_sp = 0;
    }
    printf("\n");
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


int get_sp(MEMORIA_FUNCOES* funcao){
    if(funcao == NULL){
        printf(ANSI_COLOR_RED); printf("Erro: "); printf(ANSI_COLOR_RESET);
        printf("NULL passado como argumento em get_sp\n");
        return -1;
    }
    
    return 24;
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

int get_sp_relation(MEMORIA_FUNCOES* funcao, VARIAVEL* var){
    if(funcao == NULL || var == NULL){
        printf(ANSI_COLOR_RED); printf("Erro: "); printf(ANSI_COLOR_RESET);
        printf("NULL passado como argumento em get_sp_relation\n");
        return -1;
    }
    
    return get_sp(funcao) - var->indice;
}

int get_fp_relation(MEMORIA_FUNCOES* funcao, VARIAVEL* var){
    if(funcao == NULL || var == NULL){
        printf(ANSI_COLOR_RED);
        printf("Erro: ");
        printf(ANSI_COLOR_RESET);
        printf("NULL passado como argumento em get_fp_relation\n");
        return -1;
    }

    if(funcao == global){
        //printf(ANSI_COLOR_RED "Erro: " ANSI_COLOR_RESET);
        //printf("%s - Funcao global nao tem fp\n", var->nome);
        return var->indice;
    } 
    
    return var->indice - get_fp(funcao);
}


void liberarTabMemoria(){
    MEMORIA_FUNCOES* aux = vetorMemoria.funcoes;
    MEMORIA_FUNCOES* aux2 = aux;
    VARIAVEL* aux3 = NULL;
    VARIAVEL* aux4 = NULL;

    while(aux != NULL){
        aux3 = aux->tabelaVar;
        while(aux3 != NULL){
            aux4 = aux3;
            aux3 = aux3->prox;
            free(aux4);
        }
        aux2 = aux;
        aux = aux->prox;
        free(aux2);
    }
}
