#define MAX 211

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabelaSimb.h"

PONTEIROITEM* inicializaTabela(){
    int i;
    PONTEIROITEM* tabelaHash = (PONTEIROITEM*)malloc(MAX*sizeof(ITEM*));
    for(i=0; i<MAX; i++){
        tabelaHash[i] = NULL;
    }
    return tabelaHash;
}

void inserir(PONTEIROITEM tabelaHash[], int tamanho, int tipoIdentificador, int tipoDado, char nomeIdentificador[26], char escopo[26], int linha){
    PONTEIROITEM aux;

    int indice = longhash(nomeIdentificador);
    int flag = 1;

    if(tabelaHash[indice] == NULL){
        PONTEIROITEM novoItem = (PONTEIROITEM)malloc(sizeof(ITEM));
        novoItem->proximo = NULL;
        novoItem->linhas = NULL;
        strcpy(novoItem->escopo, escopo);
        strcpy(novoItem->nomeIdentificador, nomeIdentificador);
        novoItem->tipoDado = tipoDado;
        novoItem->tipoIdentificador = tipoIdentificador;
        
        adicionaLinha(novoItem, linha);

        tabelaHash[indice] = novoItem;
        novoItem->anterior = NULL;
    }
    else{
        aux = tabelaHash[indice];

        do{
            if(strcmp(aux->nomeIdentificador, nomeIdentificador) == 0){
                adicionaLinha(aux, linha);
                flag = 0;
            }
            else{
                aux = aux->proximo;
            }
            
        }while(aux != NULL && flag == 1);

        if(flag != 0){
            PONTEIROITEM novoItem = (PONTEIROITEM)malloc(sizeof(ITEM));
            novoItem->proximo = NULL;
            novoItem->linhas = NULL;
            strcpy(novoItem->escopo, escopo);
            strcpy(novoItem->nomeIdentificador, nomeIdentificador);
            novoItem->tipoDado = tipoDado;
            novoItem->tipoIdentificador = tipoIdentificador;
            adicionaLinha(novoItem, linha);

            aux->proximo = novoItem;
            novoItem->anterior = aux;
        }

    }
}

void remover(PONTEIROITEM tabelaHash[], PONTEIROITEM num, int tamanho){
    unsigned int indice = longhash(num->nomeIdentificador);

    if(tabelaHash[indice] == num){
        if(num->proximo == NULL){
            tabelaHash[indice] = NULL;
        }
        else{
            tabelaHash[indice] = num->proximo;
            num->proximo->anterior = NULL;
        }
    }
    else{
        if(num->proximo == NULL){
            num->anterior->proximo = NULL;
        }
        else{
            num->proximo->anterior = num->anterior;
            num->anterior->proximo = num->proximo;
        }
    }
    free(num);
}

PONTEIROITEM procura(PONTEIROITEM tabelaHash[], char identificador[26], int tamanho){
    unsigned int indice = longhash(identificador);

    PONTEIROITEM aux = tabelaHash[indice];

    while(aux != NULL && strcmp(identificador, aux->nomeIdentificador) != 0){
        aux = aux->proximo;
    }

    if(aux == NULL){
        printf("Identificador nao encontrado\n");
    }

    return aux;
}

void apagarTabela(PONTEIROITEM tabelaHash[]){
    PONTEIROITEM aux1 = NULL;
    PONTEIROLINHA auxLinhas = NULL;

    for(int i = 0; i < MAX; i++){
        if(tabelaHash[i] != NULL){
            aux1 = tabelaHash[i];
            while(aux1->proximo != NULL){
                auxLinhas = aux1->linhas;

                while(auxLinhas->proximo != NULL){
                    auxLinhas = auxLinhas->proximo;
                    free(auxLinhas->anterior);
                }
                free(auxLinhas);

                aux1 = aux1->proximo;

                free(aux1->anterior);
            }
            free(aux1);
            tabelaHash[i] = NULL;
        }
    }
}

void adicionaLinha(PONTEIROITEM num, int valorLinha){
    NOLINHA* novaLinha = (NOLINHA*)malloc(sizeof(NOLINHA));
    novaLinha->numlinha = valorLinha;
    novaLinha->proximo = NULL;
    novaLinha->anterior = NULL;

    PONTEIROLINHA aux = num->linhas;

    if(aux == NULL){
        num->linhas = novaLinha;
        return;
    }

    while(aux->proximo != NULL){
        aux = aux->proximo;
    }

    aux->proximo = novaLinha;
    novaLinha->anterior = aux;

    return;
}

unsigned longhash(char *str){
    unsigned long hash = 0, alpha = 1;
    char c;

    for(int i = strlen(str)-1; i >= 0; i--){
        c = str[i];
        hash += alpha*c;
        alpha = ((alpha << 4));
    }

    hash = hash % MAX;

    return hash;
}




//Função para imprimir a tabela hash
void imprimirTabela(PONTEIROITEM tabelaHash[]){
    PONTEIROITEM aux = NULL;
    PONTEIROLINHA auxLinhas = NULL;

    for(int i = 0; i < MAX; i++){
        if(tabelaHash[i] != NULL){
            aux = tabelaHash[i];
            while(aux != NULL){
                printf("Nome: %s\n", aux->nomeIdentificador);
                printf("Escopo: %s\n", aux->escopo);
                printf("Tipo de dado: %d\n", aux->tipoDado);
                printf("Tipo de identificador: %d\n", aux->tipoIdentificador);
                printf("Linhas: ");
                auxLinhas = aux->linhas;
                while(auxLinhas != NULL){
                    printf("%d ", auxLinhas->numlinha);
                    auxLinhas = auxLinhas->proximo;
                }
                printf("\n\n");
                aux = aux->proximo;
            }
        }
    }
}

int main(){
    char n[26], escopo[50];
    int linha;
    char paragrafo[1000];
    
    PONTEIROITEM* tabelaHash = inicializa();

    for(int i = 0; i < 3; i++){
        printf("Digite o nome do identificador, o escopo e a linha: ");
        fgets(paragrafo, 1000, stdin);
        if(sscanf(paragrafo, "%s %s %d", n, escopo, &linha) == 3){
            inserir(tabelaHash, MAX, 1, 1, n, escopo, linha);
        }
        else{
            printf("Erro na leitura\n");
        }
    }

    imprimirTabela(tabelaHash);

    return 0;
}