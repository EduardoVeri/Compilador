#ifndef CodInterm_H
#define CodInterm_H 1

//Define o tamanho maximo do vetor que armazena o codigo intermediario
#define MAX_INSTRUCTION 1000

#include "tabelaSimb.h"
#include "global.h"

//ENUM com os tipos de enderecos
typedef enum {Vazio, IntConst, String} tipoEndereco;

/* Estrutura de enderecos, em que armazena o seu tipo e o
valor determinado pelo mesmo, ou seja, numero ou char* */
typedef struct endereco{
    tipoEndereco tipo;
    int val;
    int boolReg; //Diz se o endereco eh um numero (0), Reg (1) ou label (2)
    char* nome;
} ENDERECO;

/* Estrutura para as intrucoes, armazenado em quadruplas */
typedef struct instrucao{
    char* op; //Operador
    ENDERECO* arg1; 
    ENDERECO* arg2; 
    ENDERECO* arg3; 
} INSTRUCAO;

//Vetor que armazena o codigo intermediario
extern INSTRUCAO** codigoIntermediario;

extern int numReg; //Numero do registrador
extern int indiceVetor; //Indice do vetor de codigo intermediario
extern int numLabel; //Numero do label
extern char funcName[MAXLEXEMA]; //Nome da funcao

//Funcao principal para a criacao do codigo intermediario
void criarCodigoIntermediario(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[], int boolean);

//Funcoes para registradores
void inicializaReg();
int adicionarVarReg(char* nomeVar, char* escopo);
int adicionaTempReg();
int buscarVarReg(char* nomeVar, char* escopo);
void mostrarReg();
int descartarReg();
int totalRegistradores();
int verificacaoRegistradores(char *lexema, char* escopo, int boolTemp);

//Funcoes auxiliares
void inicializaVetor(); 
void desalocaVetor();
INSTRUCAO* criaInstrucao(char* op);
void imprimeCodigoIntermediario();
PONTEIROITEM buscarItemTabelaFunc(PONTEIROITEM tabelaHash[], char* lexema);


#endif