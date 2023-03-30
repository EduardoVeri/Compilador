#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codInterm.h"
#include "assembly.h"

// TODO: Onde tiver Label, adicionar um NOP, com o endereço dele sendo o da Label

ASSEMBLY ** instrucoesAssembly = NULL;
int indiceAssembly = 0;


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

// Mostrar as instrucoes em assembly
void mostraAssembly(){
	int i = 0;
	while(i < indiceAssembly){
		if(instrucoesAssembly[i]->tipo == typeI){
			TIPO_I * tipoI = instrucoesAssembly[i]->tipoI;
			printf("%s %d %d %d", tipoI->nome, tipoI->rt, tipoI->rs, tipoI->imediato);
		}
		else if(instrucoesAssembly[i]->tipo == typeR){
			TIPO_R * tipoR = instrucoesAssembly[i]->tipoR;
			printf("%s %d %d %d", tipoR->nome, tipoR->rd, tipoR->rs, tipoR->rt);
		}
		else if(instrucoesAssembly[i]->tipo == typeJ){
			TIPO_J * tipoJ = instrucoesAssembly[i]->tipoJ;
			printf("%s %d", tipoJ->nome, tipoJ->imediato);
		}
		i++;
	}
}

void assembly(){
	int i = 0;
	while(i < indiceVetor){
		geraAssembly(codigoIntermediario[i]);
		i++;
	}
}

void geraAssembly(INSTRUCAO* instrucao){
	ASSEMBLY* novaInstrucao = NULL;
	
	if(strcmp(instrucao->op, "LOAD") == 0){
		novaInstrucao = criarNoAssembly(typeI, "lw");
		novaInstrucao->tipoI->rt = instrucao->arg2->val;
		
		// Calcular qual sera o imediato
	}
	else if(strcmp(instrucao->op, "LOADI") == 0){
		novaInstrucao = criarNoAssembly(typeR, "ori");
		novaInstrucao->tipoI->rt = instrucao->arg1->val;
		novaInstrucao->tipoI->rs = 31; // Registrador 0;
		novaInstrucao->tipoI->imediato = instrucao->arg2->val;
	}
	else if(strcmp(instrucao->op, "STORE") == 0){
		//printf("STORE R%d, %d\n", instrucao->arg1->val, instrucao->arg2->val);
	}
	else if(strcmp(instrucao->op, "READ") == 0){
		//printf("READ R%d\n", instrucao->arg1->val);
	}
	else if(strcmp(instrucao->op, "WRITE") == 0){
		//printf("WRITE R%d\n", instrucao->arg1->val);
	}
	else if(strcmp(instrucao->op, "ADD") == 0){
		novaInstrucao = criarNoAssembly(typeR, "add");
		novaInstrucao->tipoR->rd = instrucao->arg3->val;
		novaInstrucao->tipoR->rs = instrucao->arg1->val;
		novaInstrucao->tipoR->rt = instrucao->arg2->val;
	}
	else if(strcmp(instrucao->op, "SUB") == 0){
		novaInstrucao = criarNoAssembly(typeR, "sub");
		novaInstrucao->tipoR->rd = instrucao->arg3->val;
		novaInstrucao->tipoR->rs = instrucao->arg1->val;
		novaInstrucao->tipoR->rt = instrucao->arg2->val;
	}
	else if(strcmp(instrucao->op, "MULT") == 0){
		novaInstrucao = criarNoAssembly(typeR, "mult");
		novaInstrucao->tipoR->rd = instrucao->arg3->val;
		novaInstrucao->tipoR->rs = instrucao->arg1->val;
		novaInstrucao->tipoR->rt = instrucao->arg2->val;
	}
	else if(strcmp(instrucao->op, "DIV") == 0){
		novaInstrucao = criarNoAssembly(typeR, "div");
		novaInstrucao->tipoR->rd = instrucao->arg3->val;
		novaInstrucao->tipoR->rs = instrucao->arg1->val;
		novaInstrucao->tipoR->rt = instrucao->arg2->val;
	}
	else if(strcmp(instrucao->op, "AND") == 0){
		novaInstrucao = criarNoAssembly(typeR, "and");
		novaInstrucao->tipoR->rd = instrucao->arg3->val;
		novaInstrucao->tipoR->rs = instrucao->arg1->val;
		novaInstrucao->tipoR->rt = instrucao->arg2->val;
	}
	else if(strcmp(instrucao->op, "EQ")){
		novaInstrucao = criarNoAssembly(typeR, "slt");
		novaInstrucao->tipoR->rd = instrucao->arg3->val;
		novaInstrucao->tipoR->rs = instrucao->arg1->val;
		novaInstrucao->tipoR->rt = instrucao->arg2->val;

		instrucoesAssembly[indiceAssembly] = novaInstrucao;
		indiceAssembly++;

		novaInstrucao = criarNoAssembly(typeR, "slt");
		novaInstrucao->tipoR->rd = instrucao->arg3->val;
		novaInstrucao->tipoR->rs = instrucao->arg2->val;
		novaInstrucao->tipoR->rt = instrucao->arg1->val;
	}
	else if(strcmp(instrucao->op, "OR") == 0){
		novaInstrucao = criarNoAssembly(typeR, "and");
		novaInstrucao->tipoR->rd = instrucao->arg3->val;
		novaInstrucao->tipoR->rs = instrucao->arg1->val;
		novaInstrucao->tipoR->rt = instrucao->arg2->val;
	}
	else if(strcmp(instrucao->op, "IFF") == 0){
		//printf("BNQ R%d, L%d\n", instrucao->arg1->val, getLabel(instrucao->arg2->val));
	}
	else if(strcmp(instrucao->op, "LABEL")){
		//criaLabel()
	}
	else{
		return;
	}

	instrucoesAssembly[indiceAssembly] = novaInstrucao;
}