#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codInterm.h"
#include "assembly.h"
#include "memoria.h"

// TODO: Onde adicionar uma variavel ou param na tabela, aumentar o valor real de $sp e armazenar o seu valor
// TODO: Arrumar o $sp e $fp para ficarem com o valor referencia mesmo

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

int opRelacionais(INSTRUCAO* instrucao, ASSEMBLY** novaInstrucao){

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

int opAritmeticos(INSTRUCAO* instrucao, ASSEMBLY** novaInstrucao){
	
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

	if(opAritmeticos(instrucao, &novaInstrucao)){
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;
	}
	else if(opRelacionais(instrucao, &novaInstrucao)){
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;
	}
	else if(!strcmp(instrucao->op, "ASSIGN")){
		novaInstrucao = criarNoAssembly(typeR, "add");
		novaInstrucao->tipoR->rd = instrucao->arg1->val;
		novaInstrucao->tipoR->rs = $zero;
		novaInstrucao->tipoR->rt = instrucao->arg2->val;
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;
	}
	else if(!strcmp(instrucao->op, "LOADI")){
		novaInstrucao = criarNoAssembly(typeI, "ori");
		novaInstrucao->tipoI->rt = instrucao->arg1->val;
		novaInstrucao->tipoI->rs = $zero;
		novaInstrucao->tipoI->imediato = instrucao->arg2->val;
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
	else if(!strcmp(instrucao->op, "ARG")){
		MEMORIA_FUNCOES* funcao = buscar_funcao(&vetorMemoria, instrucao->arg3->nome);
		
		if(!strcmp(instrucao->arg1->nome, "INT")) 
			insere_variavel(funcao, instrucao->arg2->nome, inteiroArg);
		else insere_variavel(funcao, instrucao->arg2->nome, vetorArg);
		
		novaInstrucao = criarNoAssembly(typeI, "addi");
		novaInstrucao->tipoI->rt = $sp;
		novaInstrucao->tipoI->rs = $sp;
		novaInstrucao->tipoI->imediato = 1;
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;
	}	
	else if(!strcmp(instrucao->op, "IFF")){
		novaInstrucao = criarNoAssembly(typeI, "bne");
		novaInstrucao->tipoI->rs = $zero;
		novaInstrucao->tipoI->rt = instrucao->arg1->val;
		novaInstrucao->tipoI->label = instrucao->arg2->val;


		instrucoesAssembly[indiceAssembly++] = novaInstrucao;
	}
	else if(!strcmp(instrucao->op, "LABEL")){
		char* auxLabel = (char*) malloc(sizeof(char) * 10);
		sprintf(auxLabel, "Label %d", instrucao->arg1->val);
		novaInstrucao = criarNoAssembly(typeLabel, auxLabel); 
		novaInstrucao->tipoLabel->endereco = instrucao->arg1->val;
		novaInstrucao->tipoLabel->boolean = 1;

		adicionarLabel(instrucao->arg1->val, indiceAssembly);

		instrucoesAssembly[indiceAssembly++] = novaInstrucao;

	}
	else if(!strcmp(instrucao->op, "FUN")){
		novaInstrucao = criarNoAssembly(typeLabel, instrucao->arg2->nome); 
		novaInstrucao->tipoLabel->boolean = 0;

		adicionarLabel(instrucao->arg2->val, indiceAssembly);
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;

		funcaoAtual = insere_funcao(&vetorMemoria, instrucao->arg2->nome);

		/* Carrega os registradores $fp e $sp com seus valores iniciais */
		if(!strcmp(instrucao->arg2->nome, "main")){
			novaInstrucao = criarNoAssembly(typeI, "ori");
			novaInstrucao->tipoI->rt = $fp;
			novaInstrucao->tipoI->rs = $zero; 
			novaInstrucao->tipoI->imediato = get_sp(buscar_funcao(&vetorMemoria, "global")) + 1;
			instrucoesAssembly[indiceAssembly++] = novaInstrucao;

			novaInstrucao = criarNoAssembly(typeI, "ori");
			novaInstrucao->tipoI->rt = $sp;
			novaInstrucao->tipoI->rs = $zero;
			novaInstrucao->tipoI->imediato = get_sp(buscar_funcao(&vetorMemoria, "global")) + 1;
			instrucoesAssembly[indiceAssembly++] = novaInstrucao;
		}
	}
	else if(!strcmp(instrucao->op, "RET")){
		novaInstrucao = criarNoAssembly(typeI, "sw");
		novaInstrucao->tipoI->rs = $fp;
		novaInstrucao->tipoI->rt = instrucao->arg1->val;
		novaInstrucao->tipoI->imediato = get_fp_relation(vetorMemoria.funcoes, get_variavel(vetorMemoria.funcoes, "Endereco Retorno"));

		instrucoesAssembly[indiceAssembly++] = novaInstrucao;
	}
	else if(!strcmp(instrucao->op, "PARAM")){

		novaInstrucao = criarNoAssembly(typeI, "sw");
		novaInstrucao->tipoI->rs = $sp;
		novaInstrucao->tipoI->rt = instrucao->arg1->val;
		novaInstrucao->tipoI->imediato = 3; // (1+2) 1 para avancar para a proxima memoria e 2 para pular o endereco de retorno e controle

		instrucoesAssembly[indiceAssembly++] = novaInstrucao;

		insere_variavel(funcaoAtual, "Param", temp); // Apenas para incrementar o sp

	} 
	else if(!strcmp(instrucao->op, "LOAD")){

		if(instrucao->arg3->tipo != Vazio || instrucao->arg3 != NULL){
			// Load de um indice de um vetor
			novaInstrucao = criarNoAssembly(typeI, "addi");
			novaInstrucao->tipoI->rt = $temp;
			novaInstrucao->tipoI->rs = $fp;
			novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, get_variavel(funcaoAtual, instrucao->arg2->nome));
			instrucoesAssembly[indiceAssembly++] = novaInstrucao;

			novaInstrucao = criarNoAssembly(typeR, "add");
			novaInstrucao->tipoR->rd = $temp;
			novaInstrucao->tipoR->rs = $temp;
			novaInstrucao->tipoR->rt = instrucao->arg3->val;
			instrucoesAssembly[indiceAssembly++] = novaInstrucao;

			novaInstrucao = criarNoAssembly(typeI, "lw");
			novaInstrucao->tipoI->rt = instrucao->arg1->val;
			novaInstrucao->tipoI->rs = $temp;
			novaInstrucao->tipoI->imediato = 0;
			instrucoesAssembly[indiceAssembly++] = novaInstrucao;
		}
		else{
			// Load de um inteiro
			novaInstrucao = criarNoAssembly(typeI, "lw");
			novaInstrucao->tipoI->rt = instrucao->arg1->val;
			novaInstrucao->tipoI->rs = $fp;
			novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, get_variavel(funcaoAtual, instrucao->arg2->nome));
		}
	}
	else if(!strcmp(instrucao->op, "STORE")){

		if(instrucao->arg3->tipo != Vazio || instrucao->arg3 != NULL){
			// Store de um valor em um vetor
			novaInstrucao = criarNoAssembly(typeI, "addi");
			novaInstrucao->tipoI->rt = $temp;
			novaInstrucao->tipoI->rs = $fp;
			novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, get_variavel(funcaoAtual, instrucao->arg1->nome));
			instrucoesAssembly[indiceAssembly++] = novaInstrucao;

			novaInstrucao = criarNoAssembly(typeR, "add");
			novaInstrucao->tipoR->rd = $temp;
			novaInstrucao->tipoR->rs = $temp;
			novaInstrucao->tipoR->rt = instrucao->arg3->val;
			instrucoesAssembly[indiceAssembly++] = novaInstrucao;

			novaInstrucao = criarNoAssembly(typeI, "sw");
			novaInstrucao->tipoI->rt = instrucao->arg2->val;
			novaInstrucao->tipoI->rs = $temp;
			novaInstrucao->tipoI->imediato = 0;
			instrucoesAssembly[indiceAssembly++] = novaInstrucao;
		}
		else{
			novaInstrucao = criarNoAssembly(typeI, "sw");
			novaInstrucao->tipoI->rt = instrucao->arg2->val;
			novaInstrucao->tipoI->rs = $fp;
			novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, get_variavel(funcaoAtual, instrucao->arg1->nome));
			instrucoesAssembly[indiceAssembly++] = novaInstrucao;
		}
	}
	else if(!strcmp(instrucao->op, "GOTO")){
		novaInstrucao = criarNoAssembly(typeJ, "j");
		novaInstrucao->tipoJ->labelImediato = strdup("Label ########");
		sprintf(novaInstrucao->tipoJ->labelImediato, "Label %d", instrucao->arg1->val);
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;
	}
	else if(!strcmp(instrucao->op, "HALT")){
		novaInstrucao = criarNoAssembly(typeJ, "halt");
		novaInstrucao->tipoJ->labelImediato = strdup("$zero");
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;
	}
	else if(!strcmp(instrucao->op, "CALL")){
		// Armarzena os valores de $fp, $sp e $ra
		novaInstrucao = criarNoAssembly(typeI, "sw");
		novaInstrucao->tipoI->rs = $fp;
		novaInstrucao->tipoI->rt = $fp;
		novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, get_variavel(funcaoAtual, "Registrador $fp"));

		novaInstrucao = criarNoAssembly(typeI, "sw");
		novaInstrucao->tipoI->rs = $fp;
		novaInstrucao->tipoI->rt = $sp;
		novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, get_variavel(funcaoAtual, "Registrador $sp"));

		novaInstrucao = criarNoAssembly(typeJ, "jal");
		novaInstrucao->tipoJ->labelImediato = strdup(instrucao->arg1->nome);

		novaInstrucao = criarNoAssembly(typeI, "sw");
		novaInstrucao->tipoI->rt = $ra;
		novaInstrucao->tipoI->rs = $sp;
		novaInstrucao->tipoI->imediato = get_sp(funcaoAtual) + 1; 
	} 
	else{
		printf(ANSI_COLOR_RED);
		printf("Erro: ");
		printf(ANSI_COLOR_RESET);
		printf("Instrucao nao reconhecida (%s)\n", instrucao->op);
		return;
	}

}