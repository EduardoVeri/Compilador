#ifndef Assembly_H
#define Assembly_H 1

// Capacidade maxima para o vetor dos nomes das instrucoes
#define MAX_CHAR_NOME 5
#define MAX_ASSEMBLY 1000

typedef enum{
	typeR, // Instrucoes do tipo R
	typeI, // Instrucoes do tipo I
	typeJ // Instrucoes do tipo J
} tipoInstrucao;

/* Struct para armazenar as informacoes
de instrucoes do tipo R */
typedef struct tipoR{
	char *nome; // Nome da instrucao
	int rd; // Registrador destino
	int rt; // Registrador fonte
	int rs; // Registrador fonte
} TIPO_R;

/* Struct para armazenar as informacoes
de instrucoes do tipo I */
typedef struct tipoI{
	char *nome; // Nome da instrucao
	int rs; // Registrador fonte
	int rt; // Registrador destino
	int imediato; // Valor imediato
} TIPO_I;

/* Struct para armazenar as informacoes 
de instrucoes do tipo J */
typedef struct tipoJ{
	char *nome; // Nome da instrucao
	int imediato; // Valor imediato
} TIPO_J;

typedef struct assembly{
	tipoInstrucao tipo; // Tipo da instrucao
	TIPO_I * tipoI; // Ponteiro para a struct do tipo I
	TIPO_R * tipoR; // Ponteiro para a struct do tipo R
	TIPO_J * tipoJ; // Ponteiro para a struct do tipo J
} ASSEMBLY;

// Vetor para armazenar as instrucoes em assembly
extern ASSEMBLY ** instrucoesAssembly;

// Funcoes para a geracao do codigo assembly
void assembly();
void geraAssembly(INSTRUCAO* instrucao);
void mostraAssembly();
void liberarAssembly();

#endif