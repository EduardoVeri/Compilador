#ifndef _LABEL_H_ 
#define _LABEL_H_ 1

typedef struct label{
    char* id;
    int endereco;
    struct label *prox;
} LABEL;

typedef struct vetorLabel{
    LABEL *vetor;
    int tamanho;
} VETOR_LABEL;

extern VETOR_LABEL *vetorLabel;

void inicializaLabels();
LABEL * criarNoLabel(char* id, int endereco);
void adicionarLabel(char* id, int endereco);
int getEnderecoLabel(char* id);
void liberarLabels();
void imprimirLabels();

#endif