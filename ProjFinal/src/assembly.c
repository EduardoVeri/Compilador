#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codInterm.h"
#include "assembly.h"
#include "memoria.h"

// TODO: Onde tiver Label, adicionar um NOP, com o endereço dele sendo o da Label
MEMORIA vetorMemoria; // Variavel global que guarda a memoria
MEMORIA_FUNCOES *funcaoAtual = NULL; // Ponteiro para a funcao atual

// ======================== Gerar Codigo Assembly ========================

void geraAssembly(INSTRUCAO* instrucao);

void assembly(){
	inicializaAssembly();

	for(int i = 0; i < indiceVetor; i++)
		geraAssembly(codigoIntermediario[i]);
	imprime_memoria(vetorMemoria);
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
		(*novaInstrucao)->tipoR->rt = $zero;

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
		(*novaInstrucao)->tipoR->rt = $zero;
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
		(*novaInstrucao)->tipoR->rt = $zero;
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


void carregar_fp(){
	ASSEMBLY* novaInstrucao = NULL;

	// Carregar o valor do registrador para o $fp
	novaInstrucao = criarNoAssembly(typeI, "ori");
	novaInstrucao->tipoI->rt = $fp;
	novaInstrucao->tipoI->rs = $zero;
	novaInstrucao->tipoI->imediato = get_fp(funcaoAtual);

	instrucoesAssembly[indiceAssembly++] = novaInstrucao;
}

void carregar_sp(){
	ASSEMBLY* novaInstrucao = NULL;

	// Carregar o valor do registrador para o $sp
	novaInstrucao = criarNoAssembly(typeI, "ori");
	novaInstrucao->tipoI->rt = $sp;
	novaInstrucao->tipoI->rs = $zero;
	novaInstrucao->tipoI->imediato = get_sp(funcaoAtual);

	instrucoesAssembly[indiceAssembly++] = novaInstrucao;
}

void geraAssembly(INSTRUCAO* instrucao){
	ASSEMBLY* novaInstrucao = NULL;
	int flag = 0;

	if(!strcmp(instrucao->op, "ASSIGN")){
		novaInstrucao = criarNoAssembly(typeR, "add");
		novaInstrucao->tipoR->rd = instrucao->arg1->val;
		novaInstrucao->tipoR->rs = $zero; // Registrador 0;
		novaInstrucao->tipoR->rt = instrucao->arg2->val;

		flag = 1;

		instrucoesAssembly[indiceAssembly++] = novaInstrucao;
	}
	else if(!strcmp(instrucao->op, "LOADI")){
		novaInstrucao = criarNoAssembly(typeI, "ori");
		novaInstrucao->tipoI->rt = instrucao->arg1->val;
		novaInstrucao->tipoI->rs = $zero; // Registrador 0;
		novaInstrucao->tipoI->imediato = instrucao->arg2->val;

		flag = 1;

		instrucoesAssembly[indiceAssembly++] = novaInstrucao;

	}
	else if(!strcmp(instrucao->op, "ALLOC")){
		MEMORIA_FUNCOES* funcao = buscar_funcao(&vetorMemoria, instrucao->arg2->nome);
		
		if(instrucao->arg3->tipo == Vazio){
			insere_variavel(funcao, instrucao->arg1->nome, inteiro);
		}
		else{
			for(int i = 0; i < instrucao->arg3->val; i++){
				insere_variavel(funcao, instrucao->arg1->nome, vetor);	
			}
		}
	}
	else if(strcmp(instrucao->op, "STORE") == 0){
		carregar_fp();

		/* if(instrucao->arg3->tipo != Vazio){
			// Somar o valor do offset com o valor do fp para obter o endereço de memoria
			novaInstrucao = criarNoAssembly(typeR, "add");
			novaInstrucao->tipoR->rd = $fp; // Aqui eu uso o registrador $fp apenas para não ter que criar outro registrador reservado
			novaInstrucao->tipoR->rs = instrucao->arg3->val;
			novaInstrucao->tipoR->rt = $fp; 

			instrucoesAssembly[indiceAssembly++] = novaInstrucao;

			// Armazenar o valor no endereço de memoria
			novaInstrucao = criarNoAssembly(typeI, "sw");
			novaInstrucao->tipoI->rt = instrucao->arg1->val;
			instrucoesAssembly[indiceAssembly++] = novaInstrucao;
		} */
		flag = 1;
		
	} 
	/* else if(strcmp(instrucao->op, "READ") == 0){
		return;
		//printf("READ R%d\n", instrucao->arg1->val);
	} */
	/* else if(strcmp(instrucao->op, "WRITE") == 0){
		return;
		//printf("WRITE R%d\n", instrucao->arg1->val);
	} */
	else if(!strcmp(instrucao->op, "ARG")){
		MEMORIA_FUNCOES* funcao = buscar_funcao(&vetorMemoria, instrucao->arg3->nome);
		
		if(!strcmp(instrucao->arg1->nome, "INT")) 
			insere_variavel(funcao, instrucao->arg2->nome, inteiroArg);
		else
			insere_variavel(funcao, instrucao->arg2->nome, vetorArg);
	}	
	else if(!strcmp(instrucao->op, "IFF")){
		novaInstrucao = criarNoAssembly(typeI, "bne");
		novaInstrucao->tipoI->rs = $zero;
		novaInstrucao->tipoI->rt = instrucao->arg1->val;
		novaInstrucao->tipoI->label = instrucao->arg2->val;

		flag = 1;

		instrucoesAssembly[indiceAssembly++] = novaInstrucao;
	}
	else if(!strcmp(instrucao->op, "LABEL")){
		char* auxLabel = (char*) malloc(sizeof(char) * 10);
		sprintf(auxLabel, "Label %d", instrucao->arg1->val);
		novaInstrucao = criarNoAssembly(typeLabel, auxLabel); 
		novaInstrucao->tipoLabel->endereco = instrucao->arg1->val;
		novaInstrucao->tipoLabel->boolean = 1;

		adicionarLabel(instrucao->arg1->val, indiceAssembly);
		flag = 1;

		instrucoesAssembly[indiceAssembly++] = novaInstrucao;

	}
	else if(!strcmp(instrucao->op, "FUN")){
		novaInstrucao = criarNoAssembly(typeLabel, instrucao->arg2->nome); 
		novaInstrucao->tipoLabel->boolean = 0;

		adicionarLabel(instrucao->arg2->val, indiceAssembly);
		flag = 1;
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;

		funcaoAtual = insere_funcao(&vetorMemoria, instrucao->arg2->nome);

	}
	else if(!strcmp(instrucao->op, "RET")){
		carregar_fp();

		novaInstrucao = criarNoAssembly(typeI, "sw");
		novaInstrucao->tipoI->rs = $fp;
		novaInstrucao->tipoI->rt = instrucao->arg1->val;
		novaInstrucao->tipoI->imediato = get_fp_relation(vetorMemoria.funcoes, get_variavel(vetorMemoria.funcoes, "Endereco Retorno"));

		printf("%d\n", novaInstrucao->tipoI->imediato);

		flag = 1;
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;
	}
	else if(!strcmp(instrucao->op, "PARAM")){
		carregar_sp();

		novaInstrucao = criarNoAssembly(typeI, "sw");
		novaInstrucao->tipoI->rs = $sp;
		novaInstrucao->tipoI->rt = instrucao->arg1->val;
		novaInstrucao->tipoI->imediato = 1;

		instrucoesAssembly[indiceAssembly++] = novaInstrucao;

		insere_variavel(funcaoAtual, "Param", temp); // Apenas para incrementar o sp

		flag = 1;

	} 
	else if(!strcmp(instrucao->op, "GOTO")){
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
		printf(ANSI_COLOR_RED);
		printf("Erro: ");
		printf(ANSI_COLOR_RESET);
		printf("Instrucao nao reconhecida (%s)\n", instrucao->op);
		return;
	}

}