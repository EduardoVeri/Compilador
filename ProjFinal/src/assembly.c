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

	inicializaLabels();
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

// Mostrar as instrucoes em assembly
void imprimirAssembly(){
	int i = 0;
	TIPO_I * tipoI = NULL;
	TIPO_R * tipoR = NULL;
	TIPO_J * tipoJ = NULL;
	TIPO_LABEL * tipoLabel = NULL;

	printf("============== Assembly ==============\n");
	while(i < indiceAssembly){
		if(instrucoesAssembly[i]->tipo == typeI){
			tipoI = instrucoesAssembly[i]->tipoI;		
			printf("\t%s t%d t%d ", tipoI->nome, tipoI->rt, tipoI->rs);
			
			if(tipoI->label != -1) printf("Label %d\n", tipoI->label);
			else printf("%d\n", tipoI->imediato);
			
		}
		else if(instrucoesAssembly[i]->tipo == typeR){
			tipoR = instrucoesAssembly[i]->tipoR;
			printf("\t%s t%d t%d t%d\n", tipoR->nome, tipoR->rd, tipoR->rs, tipoR->rt);
		}
		else if(instrucoesAssembly[i]->tipo == typeJ){
			tipoJ = instrucoesAssembly[i]->tipoJ;
			printf("\t%s %s\n", tipoJ->nome, tipoJ->labelImediato);
		}
		else if(instrucoesAssembly[i]->tipo == typeLabel){
			tipoLabel = instrucoesAssembly[i]->tipoLabel;
			printf("%s:\n", tipoLabel->nome);
		}
		i++;
	}	
}


// ======================== Gerar Codigo Assembly ========================

void assembly(){
	inicializaAssembly();
	for(int i = 0; i < indiceVetor; i++)
		geraAssembly(codigoIntermediario[i]);
}

int opRelacionais(INSTRUCAO* instrucao, ASSEMBLY** novaInstrucao, int flag){
	if (flag == 1) return 0; // Se flag esta em 1, operacao ja foi feita

	if(strcmp(instrucao->op, "EQ") == 0){
		(*novaInstrucao) = criarNoAssembly(typeR, "slt");
		(*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
		(*novaInstrucao)->tipoR->rs = instrucao->arg1->val;
		(*novaInstrucao)->tipoR->rt = instrucao->arg2->val;

		instrucoesAssembly[indiceAssembly++] = *novaInstrucao;

		(*novaInstrucao) = criarNoAssembly(typeR, "slt");
		(*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
		(*novaInstrucao)->tipoR->rs = instrucao->arg2->val;
		(*novaInstrucao)->tipoR->rt = instrucao->arg1->val;
	}
	else if(strcmp(instrucao->op, "LT") == 0){
		(*novaInstrucao) = criarNoAssembly(typeR, "slt");
		(*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
		(*novaInstrucao)->tipoR->rs = instrucao->arg1->val;
		(*novaInstrucao)->tipoR->rt = instrucao->arg2->val;
	}
	else if(strcmp(instrucao->op, "NEQ") == 0){
		(*novaInstrucao) = criarNoAssembly(typeR, "slt");
		(*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
		(*novaInstrucao)->tipoR->rs = instrucao->arg1->val;
		(*novaInstrucao)->tipoR->rt = instrucao->arg2->val;

		instrucoesAssembly[indiceAssembly++] = *novaInstrucao;

		(*novaInstrucao) = criarNoAssembly(typeR, "slt");
		(*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
		(*novaInstrucao)->tipoR->rs = instrucao->arg2->val;
		(*novaInstrucao)->tipoR->rt = instrucao->arg1->val;
		
		int rd = (*novaInstrucao)->tipoR->rd;

		instrucoesAssembly[indiceAssembly++] = *novaInstrucao;

		(*novaInstrucao) = criarNoAssembly(typeR, "nor");
		(*novaInstrucao)->tipoR->rd = rd;
		(*novaInstrucao)->tipoR->rs = instrucao->arg1->val;
		(*novaInstrucao)->tipoR->rt = 31;

	}
	else if(strcmp(instrucao->op, "GT") == 0){
		(*novaInstrucao) = criarNoAssembly(typeR, "slt");
		(*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
		(*novaInstrucao)->tipoR->rs = instrucao->arg2->val;
		(*novaInstrucao)->tipoR->rt = instrucao->arg1->val;
	}
	else if(strcmp(instrucao->op, "GET") == 0){
		(*novaInstrucao) = criarNoAssembly(typeR, "slt");
		(*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
		(*novaInstrucao)->tipoR->rs = instrucao->arg1->val;
		(*novaInstrucao)->tipoR->rt = instrucao->arg2->val;

		instrucoesAssembly[indiceAssembly++] = *novaInstrucao;

		int rd = (*novaInstrucao)->tipoR->rd;

		(*novaInstrucao) = criarNoAssembly(typeR, "nor");
		(*novaInstrucao)->tipoR->rd = rd;
		(*novaInstrucao)->tipoR->rs = rd;
		(*novaInstrucao)->tipoR->rt = 31;
	}
	else if(strcmp(instrucao->op, "LET") == 0){
		(*novaInstrucao) = criarNoAssembly(typeR, "slt");
		(*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
		(*novaInstrucao)->tipoR->rs = instrucao->arg2->val;
		(*novaInstrucao)->tipoR->rt = instrucao->arg1->val;

		instrucoesAssembly[indiceAssembly++] = *novaInstrucao;

		int rd = (*novaInstrucao)->tipoR->rd;

		(*novaInstrucao) = criarNoAssembly(typeR, "nor");
		(*novaInstrucao)->tipoR->rd = rd;
		(*novaInstrucao)->tipoR->rs = rd;
		(*novaInstrucao)->tipoR->rt = 31;
	}
	else{
		return 0;
	}

	return 1;

}

int opAritmeticos(INSTRUCAO* instrucao, ASSEMBLY** novaInstrucao, int flag){
	if (flag == 1) return 0;
	
	if(strcmp(instrucao->op, "ADD") == 0){
		*novaInstrucao = criarNoAssembly(typeR, "add");
		(*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
		(*novaInstrucao)->tipoR->rs = instrucao->arg1->val;
		(*novaInstrucao)->tipoR->rt = instrucao->arg2->val;
	}
	else if(strcmp(instrucao->op, "SUB") == 0){
		(*novaInstrucao) = criarNoAssembly(typeR, "sub");
		(*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
		(*novaInstrucao)->tipoR->rs = instrucao->arg1->val;
		(*novaInstrucao)->tipoR->rt = instrucao->arg2->val;
	}
	else if(strcmp(instrucao->op, "MULT") == 0){
		(*novaInstrucao) = criarNoAssembly(typeR, "mult");
		(*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
		(*novaInstrucao)->tipoR->rs = instrucao->arg1->val;
		(*novaInstrucao)->tipoR->rt = instrucao->arg2->val;
	}
	else if(strcmp(instrucao->op, "DIV") == 0){
		(*novaInstrucao) = criarNoAssembly(typeR, "div");
		(*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
		(*novaInstrucao)->tipoR->rs = instrucao->arg1->val;
		(*novaInstrucao)->tipoR->rt = instrucao->arg2->val;
	}
	else if(strcmp(instrucao->op, "AND") == 0){
		(*novaInstrucao) = criarNoAssembly(typeR, "and");
		(*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
		(*novaInstrucao)->tipoR->rs = instrucao->arg1->val;
		(*novaInstrucao)->tipoR->rt = instrucao->arg2->val;
	}
	else if(strcmp(instrucao->op, "OR") == 0){
		(*novaInstrucao) = criarNoAssembly(typeR, "or");
		(*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
		(*novaInstrucao)->tipoR->rs = instrucao->arg1->val;
		(*novaInstrucao)->tipoR->rt = instrucao->arg2->val;
	}
	else{
		return 0;
	}
	return 1;
}


void geraAssembly(INSTRUCAO* instrucao){
	ASSEMBLY* novaInstrucao = NULL;
	int flag = 0;
/* 	if(strcmp(instrucao->op, "LOAD") == 0){
		//novaInstrucao = criarNoAssembly(typeI, "lw");
		//novaInstrucao->tipoI->rt = instrucao->arg1->val;
		
		// Calcular qual sera o imediato
		return;
	} */
	if(strcmp(instrucao->op, "ASSIGN") == 0){
		novaInstrucao = criarNoAssembly(typeR, "add");
		novaInstrucao->tipoR->rd = instrucao->arg1->val;
		novaInstrucao->tipoR->rs = 31; // Registrador 0;
		novaInstrucao->tipoR->rt = instrucao->arg2->val;

		flag = 1;

		instrucoesAssembly[indiceAssembly++] = novaInstrucao;
	}
	else if(strcmp(instrucao->op, "LOADI") == 0){
		novaInstrucao = criarNoAssembly(typeI, "ori");
		novaInstrucao->tipoI->rt = instrucao->arg1->val;
		novaInstrucao->tipoI->rs = 31; // Registrador 0;
		novaInstrucao->tipoI->imediato = instrucao->arg2->val;

		flag = 1;

		instrucoesAssembly[indiceAssembly++] = novaInstrucao;

	}
	/* else if(strcmp(instrucao->op, "STORE") == 0){
		return;
		//printf("STORE R%d, %d\n", instrucao->arg1->val, instrucao->arg2->val);
	} */
	/* else if(strcmp(instrucao->op, "READ") == 0){
		return;
		//printf("READ R%d\n", instrucao->arg1->val);
	} */
	/* else if(strcmp(instrucao->op, "WRITE") == 0){
		return;
		//printf("WRITE R%d\n", instrucao->arg1->val);
	} */
	else if(strcmp(instrucao->op, "IFF") == 0){
		novaInstrucao = criarNoAssembly(typeI, "bne");
		novaInstrucao->tipoI->rs = 31;
		novaInstrucao->tipoI->rt = instrucao->arg1->val;
		novaInstrucao->tipoI->label = instrucao->arg2->val;

		flag = 1;

		instrucoesAssembly[indiceAssembly++] = novaInstrucao;
	}
	else if(strcmp(instrucao->op, "LABEL") == 0){
		char* auxLabel = (char*) malloc(sizeof(char) * 10);
		sprintf(auxLabel, "Label %d", instrucao->arg1->val);
		novaInstrucao = criarNoAssembly(typeLabel, auxLabel); 
		novaInstrucao->tipoLabel->endereco = instrucao->arg1->val;
		novaInstrucao->tipoLabel->boolean = 1;

		adicionarLabel(instrucao->arg1->val, indiceAssembly);
		flag = 1;

		instrucoesAssembly[indiceAssembly++] = novaInstrucao;

	}
	else if(strcmp(instrucao->op, "FUN") == 0){
		novaInstrucao = criarNoAssembly(typeLabel, instrucao->arg2->nome); 
		novaInstrucao->tipoLabel->boolean = 0;

		adicionarLabel(instrucao->arg2->val, indiceAssembly);
		flag = 1;
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;

	}
	else if(strcmp(instrucao->op, "RET") == 0){
		novaInstrucao = criarNoAssembly(typeR, "jr");
		novaInstrucao->tipoR->rd = 31;
		novaInstrucao->tipoR->rs = 30;
		novaInstrucao->tipoR->rt = 31;
		flag = 1;
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;
	}
	else if(strcmp(instrucao->op, "CALL") == 0){
		novaInstrucao = criarNoAssembly(typeJ, "jal");
		novaInstrucao->tipoJ->labelImediato = instrucao->arg1->nome;
		flag = 1;
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;
	}
	else if(strcmp(instrucao->op, "GOTO") == 0){
		novaInstrucao = criarNoAssembly(typeJ, "j");
		novaInstrucao->tipoJ->labelImediato = strdup("Label ########");
		sprintf(novaInstrucao->tipoJ->labelImediato, "Label %d", instrucao->arg1->val);
		flag = 1;
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;
	}
	else if(strcmp(instrucao->op, "HALT") == 0){
		novaInstrucao = criarNoAssembly(typeJ, "halt");
		flag = 1;
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;
	}
	else if(opAritmeticos(instrucao, &novaInstrucao, flag)){
		flag = 1; 
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;
	}
	else if(opRelacionais(instrucao, &novaInstrucao, flag)){
		flag = 1;
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;
	}
	else{
		printf(ANSI_COLOR_PURPLE);
		printf("Erro: Instrucao nao reconhecida (%s)\n", instrucao->op);
		printf(ANSI_COLOR_RESET);
		return;
	}
	

	//mostrarUmaInstrucao(novaInstrucao);

}