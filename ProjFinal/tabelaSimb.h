#ifndef _TABELA_SIMB_H_
#define _TABELA_SIMB_H_

#include "global.h"

typedef struct nolinha{
    int numlinha;
    struct nolinha *proximo, *anterior;
} NOLINHA;

typedef struct item{
    tipoDECL tipoIdentificador; //Variável ou função 
    tipoTipo tipoDado; //Inteiro ou void
    char nomeIdentificador[26]; //Um identificador deve ter no máximo 25 caracteres
    char escopo[26];
    NOLINHA *linhas;
    struct item *proximo, *anterior; //Lista encadeada
} ITEM;

typedef ITEM* PONTEIROITEM;
typedef NOLINHA* PONTEIROLINHA;

PONTEIROITEM* inicializaTabela();
void inserirTabela(PONTEIROITEM tabelaHash[], tipoDECL tipoIdentificador, tipoTipo tipoDado, char nomeIdentificador[26], char escopo[26], int linha);
void remover(PONTEIROITEM tabelaHash[], PONTEIROITEM num);
PONTEIROITEM procuraTabela(PONTEIROITEM tabelaHash[], char identificador[], char escopo[], tipoDECL tipoIdentificador);
void apagarTabela(PONTEIROITEM tabelaHash[]);
void adicionaLinha(PONTEIROITEM num, int valorLinha);
unsigned longhash(char *str);
void imprimirTabela(PONTEIROITEM tabelaHash[]);
PONTEIROITEM procuraTabelaExp(PONTEIROITEM tabelaHash[], char identificador[], char escopo[], tipoEXP tipoIdentificador);

#endif