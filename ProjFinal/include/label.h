#ifndef _LABEL_H_ 
#define _LABEL_H_ 1

typedef struct label{
	int id;
	int endereco;
	struct label *prox;
} LABEL;

typedef struct vetorLabel{
	LABEL *vetor;
	int tamanho;
} VETOR_LABEL;

extern VETOR_LABEL *vetorLabel;

void inicializaLabels();
LABEL * criarNoLabel(int id, int endereco);
void adicionarLabel(int id, int endereco);
int getEnderecoLabel(int id);
void liberarLabels();
void imprimirLabels();

#endif