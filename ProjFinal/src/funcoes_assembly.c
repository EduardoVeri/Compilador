#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "assembly.h"
#include "codInterm.h"
#include "memoria.h"

ASSEMBLY ** instrucoesAssembly = NULL; // Vetor de instrucoes assembly
int indiceAssembly = 0; // Indice para o vetor de instrucoes assembly

void inicializaAssembly(){
	instrucoesAssembly = (ASSEMBLY **)malloc(sizeof(ASSEMBLY*)*MAX_ASSEMBLY);

	for(int i = 0; i < MAX_INSTRUCTION; i++){
        instrucoesAssembly[i] = NULL;
    }

	inicializaLabels();
	inicializa_memoria(&vetorMemoria);
	funcaoAtual = vetorMemoria.funcoes;
}

ASSEMBLY * criarNoAssembly(tipoInstrucao tipo, char *nome){
	ASSEMBLY * novoNoAssembly = (ASSEMBLY *)malloc(sizeof(ASSEMBLY));
	novoNoAssembly->tipo = tipo;

	switch (tipo){
	case typeR:
		novoNoAssembly->tipoR = (TIPO_R *)malloc(sizeof(TIPO_R));
		novoNoAssembly->tipoR->nome = nome;
		novoNoAssembly->tipoR->rd = -1;
		novoNoAssembly->tipoR->rs = -1;
		novoNoAssembly->tipoR->rt = -1;
		break;

	case typeI:
		novoNoAssembly->tipoI = (TIPO_I *)malloc(sizeof(TIPO_I));
		novoNoAssembly->tipoI->nome = nome;
		novoNoAssembly->tipoI->rs = -1;
		novoNoAssembly->tipoI->rt = -1;
		novoNoAssembly->tipoI->imediato = -1;
		novoNoAssembly->tipoI->label = -1;
		break;

	case typeJ:
		novoNoAssembly->tipoJ = (TIPO_J *)malloc(sizeof(TIPO_J));
		novoNoAssembly->tipoJ->nome = nome;
		novoNoAssembly->tipoJ->labelImediato = NULL;
		break;
	
	case typeLabel:
		novoNoAssembly->tipoLabel = (TIPO_LABEL *)malloc(sizeof(TIPO_LABEL));
		novoNoAssembly->tipoLabel->nome = nome;
		novoNoAssembly->tipoLabel->endereco = -1;
		novoNoAssembly->tipoLabel->boolean = -1;
		break;
	}

	return novoNoAssembly;
}

// Liberar vetor de instrucoes assembly
void liberarAssembly(){
	for(int i = 0; i < indiceAssembly; i++){
		if(instrucoesAssembly[i]->tipo == typeR)
			free(instrucoesAssembly[i]->tipoR);
		else if(instrucoesAssembly[i]->tipo == typeI)
			free(instrucoesAssembly[i]->tipoI);
		else if(instrucoesAssembly[i]->tipo == typeJ)
			free(instrucoesAssembly[i]->tipoJ);
		else if(instrucoesAssembly[i]->tipo == typeLabel){
			free(instrucoesAssembly[i]->tipoLabel);
			if(instrucoesAssembly[i]->tipoLabel->boolean == 1)
				free(instrucoesAssembly[i]->tipoLabel->nome);
		}
		free(instrucoesAssembly[i]);
	}
	free(instrucoesAssembly);
}

void tipo_reg(int reg){
	switch (reg){
	case $zero:
		printf("$zero ");
		break;
	
	case $fp:
		printf("$fp ");
		break;

	case $sp:
		printf("$sp ");
		break;

	case $ra:
		printf("$ra ");
		break;

	default:
		printf("$t%d ", reg);
		break;
	}
}


// Mostrar as instrucoes em assembly
void imprimirAssembly(){
	int i = 0;
	TIPO_I * tipoI = NULL;
	TIPO_R * tipoR = NULL;
	TIPO_J * tipoJ = NULL;
	TIPO_LABEL * tipoLabel = NULL;

	printf("============== Assembly ==============\n");
	for(int i = 0; i < indiceAssembly; i++){
		if(instrucoesAssembly[i]->tipo == typeI){
			tipoI = instrucoesAssembly[i]->tipoI;		
			printf("\t%s ", tipoI->nome);
			tipo_reg(tipoI->rt);
			tipo_reg(tipoI->rs);
			
			if(tipoI->label != -1) printf("Label %d\n", tipoI->label);
			else printf("%d\n", tipoI->imediato);
			
		}
		else if(instrucoesAssembly[i]->tipo == typeR){
			tipoR = instrucoesAssembly[i]->tipoR;
			printf("\t%s ", tipoR->nome);
			tipo_reg(tipoR->rd);
			tipo_reg(tipoR->rs);
			tipo_reg(tipoR->rt);
			printf("\n");
		}
		else if(instrucoesAssembly[i]->tipo == typeJ){
			tipoJ = instrucoesAssembly[i]->tipoJ;
			printf("\t%s %s\n", tipoJ->nome, tipoJ->labelImediato);
		}
		else if(instrucoesAssembly[i]->tipo == typeLabel){
			tipoLabel = instrucoesAssembly[i]->tipoLabel;
			printf("%s:\n", tipoLabel->nome);
		}
	}	
}
