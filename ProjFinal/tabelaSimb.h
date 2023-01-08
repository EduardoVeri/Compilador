#ifndef _TABELA_SIMB_H_
#define _TABELA_SIMB_H_ 1

#include "global.h"

typedef struct nolinha{
    int numlinha; //Valor da linha
    struct nolinha *proximo, *anterior;
} NOLINHA;

typedef struct item{
    tipoDECL tipoIdentificador; //Variavel ou funcao 
    tipoTipo tipoDado; //Inteiro ou void
    char nomeIdentificador[26]; //Um identificador deve ter no maximo 25 caracteres
    char escopo[26]; //Nome do escopo em que a var se encontra
    NOLINHA *linhas; //Lista encadeada para o valor das linhas
    struct item *proximo, *anterior; //Lista encadeada para o tratamento de colisoes
} ITEM;

typedef ITEM* PONTEIROITEM;
typedef NOLINHA* PONTEIROLINHA;

//Inicializa a tabela com valores default
PONTEIROITEM* inicializaTabela();

//Insere um item na tabela de simbolos
void inserirTabela(PONTEIROITEM tabelaHash[], tipoDECL tipoIdentificador, tipoTipo tipoDado, char nomeIdentificador[26], char escopo[26], int linha);

//Remove um item da tabela de simbolos
void remover(PONTEIROITEM tabelaHash[], PONTEIROITEM num);

//Procura um item na tabela de simbolos, especifico para a analise semantica de declaracoes
PONTEIROITEM procuraTabela(PONTEIROITEM tabelaHash[], char identificador[], char escopo[], tipoDECL tipoIdentificador);

//Libera a memoria alocada para a tabela de simbolos
void apagarTabela(PONTEIROITEM tabelaHash[]);

//Adiciona uma linha na lista encadeada de linhas
void adicionaLinha(PONTEIROITEM num, int valorLinha);

//Obtem o valor do indice da tabela de simbolos
unsigned longhash(char *str);

//Imprime a tabela de simbolos
void imprimirTabela(PONTEIROITEM tabelaHash[]);

//Procura um item na tabela de simbolos, especifico para a analise semantica de expressoes
PONTEIROITEM procuraTabelaExp(PONTEIROITEM tabelaHash[], char identificador[], char escopo[], tipoEXP tipoIdentificador);

PONTEIROITEM buscarItemTabelaFunc(PONTEIROITEM tabelaHash[], char* lexema);

PONTEIROITEM buscarItemTabelaId(PONTEIROITEM tabelaHash[], char* nomeIdentificador);

#endif