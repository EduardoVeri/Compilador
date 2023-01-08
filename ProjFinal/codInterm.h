#ifndef CodInterm_H
#define CodInterm_H 1

#define MAX_INSTRUCTION 1000

#include "tabelaSimb.h"
#include "global.h"

//ENUM com os tipos de enderecos
typedef enum {Vazio, IntConst, String} tipoEndereco;

typedef struct endereco{
    tipoEndereco tipo;
    int val;
    int boolReg; //Diz se o endereco eh um registrador
    char* nome;
} ENDERECO;

//Estrutura de instrucoes
typedef struct instrucao{
    char* op; //Operador
    ENDERECO* arg1; 
    ENDERECO* arg2; 
    ENDERECO* arg3; 
} INSTRUCAO;

INSTRUCAO** codigoIntermediario;

extern int numReg; //Numero do registrador
extern int indiceVetor; //Indice do vetor de codigo intermediario
extern int numLabel; //Numero do label

void criarCodigoIntermediario(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[], int boolean);
INSTRUCAO** inicializaVetor();
void desalocaVetor();
INSTRUCAO* criaInstrucao(char* op);
void imprimeCodigoIntermediario();

#endif