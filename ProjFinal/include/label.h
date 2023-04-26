#ifndef _LABEL_H_ 
#define _LABEL_H_ 1

/* 
typedef struct linhas{
	int numLabel;
	int linha;
} LINHAS;

typedef struct filaLinhas{
	int qntd;
	LINHAS linhas[20];
} FILA_LINHAS; */

typedef struct label{
	int id;
	int endereco;
	struct label *prox;
} LABEL;

typedef struct vetorLabel{
	LABEL *vetor;
	int tamanho;
} VETOR_LABEL;

// extern FILA_LINHAS filaLinhas;
extern VETOR_LABEL *vetorLabel;

void inicializaLabels();
LABEL * criarNoLabel(int id, int endereco);
void adicionarLabel(int id, int endereco);
int getEnderecoLabel(int id);
void liberarLabels();
void imprimirLabels();

#endif