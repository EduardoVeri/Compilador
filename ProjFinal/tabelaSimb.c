#define MAX 211

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nolinha{
    int numlinha;
    struct nolinha *proximo, *anterior;
} NOLINHA;

typedef struct item{
    int tipoIdentificador; //Trocar para enum depois
    int tipoDado;
    char nomeIdentificador[26]; //Um identificador deve ter no máximo 25 caracteres
    char escopo[26];
    NOLINHA *linhas;
    struct item *proximo, *anterior; //Lista encadeada
} ITEM;

typedef ITEM* PONTEIROITEM;
typedef NOLINHA* PONTEIROLINHA;


void inicializa(PONTEIROITEM tabelaHash[], int tamanho);
void inserir(PONTEIROITEM tabelaHash[], int tamanho, int tipoIdentificador, int tipoDado, char nomeIdentificador[26], char escopo[26], int linha);
void remover(PONTEIROITEM tabelaHash[], PONTEIROITEM num, int tamanho);
PONTEIROITEM procura(PONTEIROITEM tabelaHash[], char identificador[26], int tamanho);
void apagarTabela(PONTEIROITEM tabelaHash[]);
void adicionaLinha(PONTEIROITEM num, int valorLinha);
unsigned longhash(char *str);


void inicializa(PONTEIROITEM tabelaHash[], int tamanho){
    int i;
    for(i=0; i<tamanho; i++){
        tabelaHash[i] = NULL;
    }
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

        }while(aux->proximo != NULL || flag == 0);

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

    PONTEIROITEM aux = num;

    while(num->linhas->proximo != NULL){
        aux->linhas = aux->linhas->proximo;
    }

    aux->linhas->proximo = novaLinha;
    novaLinha->anterior = aux->linhas;

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

    printf("%lu\n", hash);
    return hash;
}

int main(){
    char n[26];
    scanf("%s", n);

    printf("%u\n",longhash(n));

    /*
    PONTEIROITEM tabelaHash[MAX];
    inicializa(tabelaHash, MAX);

    inserir(tabelaHash, MAX, 1, 1, n, "global", 1);

    PONTEIROITEM aux = procura(tabelaHash, n, MAX);

    printf("%s", aux->nomeIdentificador);
    */

    return 0;
}

