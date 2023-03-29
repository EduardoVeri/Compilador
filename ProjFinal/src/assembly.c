#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codInterm.h"

// TODO: Onde tiver Label, adicionar um NOP, com o endereço dele sendo o da Label





void geraAssembly(INSTRUCAO* instrucao);

void assembly(){
	int i = 0;
	while(i < indiceVetor){
		geraAssembly(codigoIntermediario[i]);
		i++;
	}
}

void geraAssembly(INSTRUCAO* instrucao){
	if(strcmp(instrucao->op, "ADD") == 0){
		printf("ADD R%d, R%d, R%d\n", instrucao->arg3->val, instrucao->arg1->val, instrucao->arg2->val);
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