#ifndef _MEMORIA_H_
#define _MEMORIA_H_ 1

#define MEM_PARAM 1000;

typedef enum tipo{
    inteiro,
    vetor,
    inteiroArg,
    vetorArg,
    controle,
    retorno,
    temp
} TIPO_VAR;

typedef struct variavel{
    TIPO_VAR tipo;
    int indice;
    int bool_global;
    char *nome;
    struct variavel *prox;
} VARIAVEL;

typedef struct memoria_funcoes{
    int tamanho;
    char* nome;
    struct memoria_funcoes *prox;
    VARIAVEL *tabelaVar;
} MEMORIA_FUNCOES;

typedef struct{
    int tamanho;
    MEMORIA_FUNCOES *funcoes;
} MEMORIA;

// Funcoes para a manipulacao da memoria

void inicializa_memoria(MEMORIA* memoria);
MEMORIA_FUNCOES* insere_funcao(MEMORIA *memoria, char * nome_funcao);
void insere_variavel(MEMORIA_FUNCOES* funcao, char * nome_variavel, TIPO_VAR tipo);
VARIAVEL* get_variavel(MEMORIA_FUNCOES* funcao, char * nome_variavel);
void imprime_memoria();
MEMORIA_FUNCOES* buscar_funcao(MEMORIA* memoria, char* nome_funcao);
int get_sp_relation(MEMORIA_FUNCOES* funcao, VARIAVEL* var);
int get_fp_relation(MEMORIA_FUNCOES* funcao, VARIAVEL* var);
int get_sp(MEMORIA_FUNCOES* funcao);
int get_fp(MEMORIA_FUNCOES* funcao);
void apagar_temp(MEMORIA_FUNCOES* funcao);
void liberarTabMemoria();

extern MEMORIA vetorMemoria;
extern MEMORIA_FUNCOES* funcaoAtual;
extern MEMORIA_FUNCOES* global;

#endif