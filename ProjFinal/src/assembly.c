#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codInterm.h"
#include "assembly.h"

// TODO: Onde tiver Label, adicionar um NOP, com o endereço dele sendo o da Label

ASSEMBLY ** instrucoesAssembly = NULL;

void inicializaAssembly(){
	instrucoesAssembly = (ASSEMBLY **)malloc(sizeof(ASSEMBLY*)*MAX_ASSEMBLY);

	for(int i = 0; i < MAX_INSTRUCTION; i++){
        instrucoesAssembly[i] = NULL;
    }
}

ASSEMBLY * criarNoAssembly(tipoInstrucao tipo, char* nome){
	ASSEMBLY * novoNoAssembly = (ASSEMBLY *)malloc(sizeof(ASSEMBLY));
	TIPO_R * novoTipoR = NULL;
	TIPO_I * novoTipoI = NULL;
	TIPO_J * novoTipoJ = NULL;
	
	switch (tipo){
	case typeR:
		novoTipoR = (TIPO_R *)malloc(sizeof(TIPO_R));
		novoNoAssembly->tipoR = novoTipoR;
		break;

	case typeI:
		novoTipoI = (TIPO_I *)malloc(sizeof(TIPO_I));
		novoNoAssembly->tipoI = novoTipoI;
		break;

	case typeJ:
		novoTipoJ = (TIPO_J *)malloc(sizeof(TIPO_J));
		novoNoAssembly->tipoJ = novoTipoJ;
		break;
	}
	
	novoNoAssembly->tipo = tipo;
	return novoNoAssembly;
}


void assembly(){
	int i = 0;
	while(i < indiceVetor){
		geraAssembly(codigoIntermediario[i]);
		i++;
	}
}

void geraAssembly(INSTRUCAO* instrucao){
	if(strcmp(instrucao->op, "ADD") == 0){
		

	}
	else if(strcmp(instrucao->op, "SUB") == 0){
		printf("ADD R%d, R%d, R%d\n", instrucao->arg3->val, instrucao->arg1->val, instrucao->arg2->val);
	}
	else if(strcmp(instrucao->op, "MULT") == 0){
		printf("MULT R%d, R%d, R%d\n", instrucao->arg3->val, instrucao->arg1->val, instrucao->arg2->val);
	}
	else if(strcmp(instrucao->op, "DIV") == 0){
		printf("DIV R%d, R%d, R%d\n", instrucao->arg3->val, instrucao->arg1->val, instrucao->arg2->val);
	}
	else if(strcmp(instrucao->op, "IFF") == 0){
		//printf("BNQ R%d, L%d\n", instrucao->arg1->val, getLabel(instrucao->arg2->val));
	}
	else if(strcmp(instrucao->op, "LABEL")){
		//criaLabel()
	}
}