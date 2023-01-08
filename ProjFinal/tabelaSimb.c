#define MAX 211

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabelaSimb.h"

/* Funcao para alocar, inicializar e retornar a tabela de simbolos a 
ser utilizado pelo compilador */
PONTEIROITEM* inicializaTabela(){
    int i;
    PONTEIROITEM* tabelaHash = (PONTEIROITEM*)malloc(MAX*sizeof(ITEM*));
    for(i=0; i<MAX; i++){
        tabelaHash[i] = NULL;
    }
    return tabelaHash;
}

/* Busca um item na tabela de simbolos
Utilizada por funcoes no codigo intermediario */
PONTEIROITEM buscarItemTabelaId(PONTEIROITEM tabelaHash[], char* nomeIdentificador){
    int indice = longhash(nomeIdentificador);
    PONTEIROITEM item = tabelaHash[indice];

    while(item != NULL){
        if(strcmp(item->nomeIdentificador, nomeIdentificador) == 0)
            return item;
        item = item->proximo;
    }

    return NULL;
}

/* Busca uma funcao na tabela de simbolos
Utilizada por funcoes no codigo intermediario */
PONTEIROITEM buscarItemTabelaFunc(PONTEIROITEM tabelaHash[], char* lexema){
    int indice = longhash(lexema);
    PONTEIROITEM item = tabelaHash[indice];

    while(item != NULL){
        if(item->tipoIdentificador == FunDeclK && strcmp(item->nomeIdentificador, lexema) == 0){
            return item;
        }
        item = item->proximo;
    }

    return item;
}

/* Funcao para inserir um item na tabela de simbolos */
void inserirTabela(PONTEIROITEM tabelaHash[], tipoDECL tipoIdentificador, tipoTipo tipoDado, char nomeIdentificador[26], char escopo[26], int linha){
    PONTEIROITEM aux, auxAnterior;

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

        while(aux != NULL && flag == 1){
            if(strcmp(aux->nomeIdentificador, nomeIdentificador) == 0 && (strcmp(aux->escopo, escopo) == 0 || strcmp(aux->escopo, "global") == 0)){
                adicionaLinha(aux, linha);
                flag = 0;
            }
            else{
                auxAnterior = aux;
                aux = aux->proximo;
            }
        }

        if(flag != 0){
            PONTEIROITEM novoItem = (PONTEIROITEM)malloc(sizeof(ITEM));
            novoItem->proximo = NULL;
            novoItem->linhas = NULL;
            strcpy(novoItem->escopo, escopo);
            strcpy(novoItem->nomeIdentificador, nomeIdentificador);
            novoItem->tipoDado = tipoDado;
            novoItem->tipoIdentificador = tipoIdentificador;
            adicionaLinha(novoItem, linha);

            auxAnterior->proximo = novoItem;
            novoItem->anterior = auxAnterior;
        }

    }
}

/* Funcao para remover um item da tabela de simbolos */
void remover(PONTEIROITEM tabelaHash[], PONTEIROITEM num){
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

/*  Uma funcao de busca especifica para ser utilizada durante a 
analise semantica, ao ser encontrado uma declaracao de expressao.
A Ideia dessa funcao eh buscar na tabela de simbolos se aquele
item que foi encontrado na arvore, com o tipo EXPRESSAO, foi declarado
para ser devidademente usado. Isso corresponde a chamadas de funcoes e
uso de parametros ou variaveis. */
PONTEIROITEM procuraTabelaExp(PONTEIROITEM tabelaHash[], char identificador[], char escopo[], tipoEXP tipoIdentificador){
    unsigned int indice = longhash(identificador);

    PONTEIROITEM aux = tabelaHash[indice];

    tipoDECL tipoDeclara = tipoIdentificador == VetorK ? VetDeclK : VarDeclK;

    // Se for uma chamada de funcao, busca apenas declaracoes de funcoes
    if(tipoIdentificador == AtivK){
        // Busca na tabela de simbolos o nome correspondente
        while(aux != NULL){
            if(strcmp(identificador, aux->nomeIdentificador) == 0 && aux->tipoIdentificador == FunDeclK){
                break;
            }
            aux = aux->proximo;
        }
        // Se nao encontrar, retorna NULL e causara um erro semantico
        return aux;
    }

    // Busca na tabela de simbolos o nome correspondente
    while(aux != NULL){
        if(strcmp(identificador, aux->nomeIdentificador) == 0){
            // Se for um vetor, busca apenas declaracoes de vetores
            if(tipoDeclara == VetDeclK){
                if(aux->tipoIdentificador == VetDeclK || aux->tipoIdentificador == VetParamK){
                    if((strcmp(escopo, aux->escopo) == 0 || strcmp(aux->escopo, "global") == 0)){
                        break;
                    }
                }
            }
            // Se for uma variavel, busca apenas declaracoes de variaveis
            else{
                if(aux->tipoIdentificador == VarDeclK || aux->tipoIdentificador == VarParamK){
                    if((strcmp(escopo, aux->escopo) == 0 || strcmp(aux->escopo, "global") == 0)){
                        break;
                    }
                }
            }
        }
        aux = aux->proximo;
    }

    // Se nao encontrar, retorna NULL e causara um erro semantico
    return aux;

}

/* Uma funcao de busca especifica para ser utilizada durante a 
analise semantica, ao ser encontrado uma declaracao de declaracao */
PONTEIROITEM procuraTabela(PONTEIROITEM tabelaHash[], char identificador[], char escopo[], tipoDECL tipoIdentificador){
    unsigned int indice = longhash(identificador);

    PONTEIROITEM aux = tabelaHash[indice];

    //Verificar se o identificador existe na tabela como uma função
    if(tipoIdentificador == FunDeclK){
        while(aux != NULL){
            if(strcmp(identificador, aux->nomeIdentificador) == 0){
                break;
            }
            aux = aux->proximo;
        }
        return aux;
    }
    
    while(aux != NULL){
        if(strcmp(identificador, aux->nomeIdentificador) == 0){
            if((strcmp(escopo, aux->escopo) == 0 || strcmp(aux->escopo, "global") == 0)){
                break;
            }
            if(aux->tipoIdentificador == FunDeclK){
                break;
            }
        }
        aux = aux->proximo;
    }

    return aux;
}

//Desaloca os nos da tabela de simbolos
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

//Adiciona uma nova linha a um item na tabela de simbolos
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

//Calcula o valor do hash para encontrar a posicao do item na tabela
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

    printf("============== Tabela de Simbolos ===============\n");
    
    for(int i = 0; i < MAX; i++){
        if(tabelaHash[i] != NULL){
            aux = tabelaHash[i];
            while(aux != NULL){
                printf("Nome: %s\n", aux->nomeIdentificador);
                
                if(aux->tipoIdentificador != FunDeclK)
                    printf("Escopo: %s\n", aux->escopo);
            
                if(aux->tipoDado == Type_Int){
                    printf("Tipo de dado: INT\n");
                }
                else{
                    printf("Tipo de dado: VOID\n");
                }
                
                if(aux->tipoIdentificador == VarDeclK){
                    printf("Tipo de identificador: VAR\n");
                }
                else if(aux->tipoIdentificador == FunDeclK){
                    printf("Tipo de identificador: FUN\n");
                }
                else if(aux->tipoIdentificador == VetDeclK){
                    printf("Tipo de identificador: VET\n");
                }
                else{
                    printf("Tipo de identificador: PARAM\n");
                }

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
