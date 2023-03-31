#ifndef _LABEL_H_ 
#define _LABEL_H_ 1

typedef struct label{
	char *nome;
	int endereco;
	struct label *prox;
} LABEL;

typedef struct vetorLabel{
	LABEL *vetor;
	int tamanho;
} VETOR_LABEL;

extern VETOR_LABEL *vetorLabel;


#endif