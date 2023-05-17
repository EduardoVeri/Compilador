#ifndef _MEMORIA_H_
#define _MEMORIA_H_ 1


typedef enum tipo{
	inteiro,
	vetor
} TIPO_VAR;

typedef struct variavel{
	TIPO_VAR tipo;
	int endereco;
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

void inicializa_memoria(MEMORIA memoria);
void insere_funcao(MEMORIA *memoria, char * nome_funcao);
void insere_variavel(MEMORIA *memoria, char * nome_variavel, TIPO_VAR tipo);
VARIAVEL* get_variavel(MEMORIA memoria, char * nome_variavel);
void imprime_memoria(MEMORIA memoria);

#endif