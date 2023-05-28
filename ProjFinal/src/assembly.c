#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codInterm.h"
#include "assembly.h"
#include "memoria.h"

// TODO: Verificar como esta sendo feita a passagem de param de um vetor e seu uso na funcao
// TODO: Onde adicionar uma variavel ou param na tabela, aumentar o valor real de $sp e armazenar o seu valor
// TODO: Arrumar o $sp e $fp para ficarem com o valor referencia mesmo
// TODO: Parar de incrementar $sp apos um parametro. Guardar a quantidade de parametros em um inteiro na struct da funcao

MEMORIA vetorMemoria; // Variavel global que guarda a memoria
MEMORIA_FUNCOES *funcaoAtual = NULL; // Ponteiro para a funcao atual

// ======================== Gerar Codigo Assembly ========================

void geraAssembly(INSTRUCAO* instrucao);

void assembly(){
	inicializaAssembly();

	/* Criar uma funcao Jump para a main */
	ASSEMBLY *novaInstrucao = criarNoAssembly(typeJ, "j");
	novaInstrucao->tipoJ->labelImediato = strdup("main");
	instrucoesAssembly[indiceAssembly++] = novaInstrucao;

	for(int i = 0; i < indiceVetor; i++)
		geraAssembly(codigoIntermediario[i]);
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
		
		if(!instrucao->arg3){
			printf(ANSI_COLOR_RED "Erro: " ANSI_COLOR_RESET);
			printf("NULL no argumento 3\n");
			return;
		}

		if(!instrucao->arg3){
			printf(ANSI_COLOR_RED "Erro: " ANSI_COLOR_RESET);
			printf("NULL no argumento 3\n");
			return;
		}

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

		char label[26];
		sprintf(label, "Label %d", instrucao->arg1->val);
		adicionarLabel(label, indiceAssembly);

		instrucoesAssembly[indiceAssembly++] = novaInstrucao;

	}
	else if(!strcmp(instrucao->op, "FUN")){
		novaInstrucao = criarNoAssembly(typeLabel, instrucao->arg2->nome); 
		novaInstrucao->tipoLabel->boolean = 0;

		adicionarLabel(instrucao->arg2->nome, indiceAssembly);
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
			novaInstrucao->tipoI->imediato = get_sp(buscar_funcao(&vetorMemoria, "global")) + 5;
			instrucoesAssembly[indiceAssembly++] = novaInstrucao;
		}
		else{
			// Guarda o valor de controle para a funcao anterior
			novaInstrucao = criarNoAssembly(typeI, "sw");
			novaInstrucao->tipoI->rt = $ra;
			novaInstrucao->tipoI->rs = $fp;
			novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, get_variavel(funcaoAtual, "Endereco Retorno")) + instrucao->arg3->val;
			instrucoesAssembly[indiceAssembly++] = novaInstrucao;

			// Atualiza o valor de $sp
			novaInstrucao = criarNoAssembly(typeI, "addi");
			novaInstrucao->tipoI->rt = $sp;
			novaInstrucao->tipoI->rs = $fp;
			novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, get_variavel(funcaoAtual, "Registrador $sp")) + 1;
			instrucoesAssembly[indiceAssembly++] = novaInstrucao;
		}
	}
	else if(!strcmp(instrucao->op, "RET")){
		// Acessa o valor de controle da funcao anterior
		novaInstrucao = criarNoAssembly(typeI, "lw");
		novaInstrucao->tipoI->rt = $temp;
		novaInstrucao->tipoI->rs = $fp;
		novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, get_variavel(funcaoAtual, "Vinculo Controle"));
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;

		// Salva o valor do retorno no frame da funcao anterior
		novaInstrucao = criarNoAssembly(typeI, "sw");
		novaInstrucao->tipoI->rs = $temp;
		novaInstrucao->tipoI->rt = instrucao->arg1->val;
		novaInstrucao->tipoI->imediato = 2; // 2 para avancar para "Valor de Retorno"
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;

	}
	else if(!strcmp(instrucao->op, "PARAM")){

		novaInstrucao = criarNoAssembly(typeI, "sw");
		novaInstrucao->tipoI->rs = $sp;
		novaInstrucao->tipoI->rt = instrucao->arg1->val;
		novaInstrucao->tipoI->imediato = 1; // 1 para avancar para a proxima memoria
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;

		insere_variavel(funcaoAtual, "Param", temp); // Apenas para incrementar o sp

		novaInstrucao = criarNoAssembly(typeI, "addi");
		novaInstrucao->tipoI->rt = $sp;
		novaInstrucao->tipoI->rs = $sp;
		novaInstrucao->tipoI->imediato = 1;
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;
		
	} 
	else if(!strcmp(instrucao->op, "LOAD")){
		if(!instrucao->arg3){
			printf(ANSI_COLOR_RED "Erro: " ANSI_COLOR_RESET);
			printf("NULL no argumento 3\n");
			return;
		}

		if(instrucao->arg3->tipo != Vazio){
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
			instrucoesAssembly[indiceAssembly++] = novaInstrucao;
		}
	}
	else if(!strcmp(instrucao->op, "STORE")){
		if(!instrucao->arg3){
			printf(ANSI_COLOR_RED "Erro: " ANSI_COLOR_RESET);
			printf("NULL no argumento 3\n");
			return;
		}

		if(instrucao->arg3->tipo != Vazio){
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
		if(!instrucao->arg3){
			printf(ANSI_COLOR_RED "Erro: " ANSI_COLOR_RESET);
			printf("NULL no argumento 3\n");
			return;
		}
		
		//TODO: Voltar o $sp pelo valor do numero de param no call
		//TODO: Avancar $fp e $sp para seus novos valores

		for(int i = 0; i < instrucao->arg2->val; i++) apagar_temp(funcaoAtual); // Apaga os temporarios usados na chamada

		// Diminui o valor de $sp pelo numero de parametros
		novaInstrucao = criarNoAssembly(typeI, "subi");
		novaInstrucao->tipoI->rt = $sp;
		novaInstrucao->tipoI->rs = $sp;
		novaInstrucao->tipoI->imediato = instrucao->arg2->val;
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;

		if(!strcmp(instrucao->arg1->nome, "output")){
			// Salva o valor do param no $temp para ser usado no output
			novaInstrucao = criarNoAssembly(typeI, "lw");
			novaInstrucao->tipoI->rt = $temp;
			novaInstrucao->tipoI->rs = $sp;
			novaInstrucao->tipoI->imediato = 1;
			instrucoesAssembly[indiceAssembly++] = novaInstrucao;
			
			// Mostra o valor do $temp para o usuario
			novaInstrucao = criarNoAssembly(typeI, "out");
			novaInstrucao->tipoI->rs = $temp;
			novaInstrucao->tipoI->rt = $zero;
			novaInstrucao->tipoI->imediato = 0;
			instrucoesAssembly[indiceAssembly++] = novaInstrucao;
			return; // Nao precisa fazer mais nada
		}
		else if(!strcmp(instrucao->arg1->nome, "input")){
			// Como essa funcao nao tem param, basta colocar o input no registrador
			novaInstrucao = criarNoAssembly(typeI, "in");
			novaInstrucao->tipoI->rt = instrucao->arg3->val;
			novaInstrucao->tipoI->rs = $zero;
			novaInstrucao->tipoI->imediato = 0;
			instrucoesAssembly[indiceAssembly++] = novaInstrucao;
			return; // Nao precisa fazer mais nada
		}

		// Armazena os valores de $fp, $sp
		novaInstrucao = criarNoAssembly(typeI, "sw");
		novaInstrucao->tipoI->rs = $fp;
		novaInstrucao->tipoI->rt = $fp;
		novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, get_variavel(funcaoAtual, "Registrador $fp"));
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;

		novaInstrucao = criarNoAssembly(typeI, "sw");
		novaInstrucao->tipoI->rs = $fp;
		novaInstrucao->tipoI->rt = $sp;
		novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, get_variavel(funcaoAtual, "Registrador $sp"));
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;

		// Armazena o valor de $fp dessa funcao em $temp para poder ser armazenado no novo frame
		novaInstrucao = criarNoAssembly(typeR, "add");
		novaInstrucao->tipoR->rt = $zero;
		novaInstrucao->tipoR->rs = $fp;
		novaInstrucao->tipoR->rd = $temp;
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;

		// Faz com que $temp aponte para "Vinculo Controle" para poder ser armazenado no novo frame
		novaInstrucao = criarNoAssembly(typeI, "addi");
		novaInstrucao->tipoI->rt = $temp;
		novaInstrucao->tipoI->rs = $temp;
		novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, get_variavel(funcaoAtual, "Vinculo Controle"));
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;

		// Incrementa o valor de $fp para o novo frame da funcao
		novaInstrucao = criarNoAssembly(typeI, "addi");
		novaInstrucao->tipoI->rt = $fp;
		novaInstrucao->tipoI->rs = $sp;
		novaInstrucao->tipoI->imediato = 1;
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;

		// Armazena o valor de controle no seu respectivo local no novo frame
		novaInstrucao = criarNoAssembly(typeI, "sw");
		novaInstrucao->tipoI->rt = $temp;
		novaInstrucao->tipoI->rs = $sp;
		novaInstrucao->tipoI->imediato = instrucao->arg2->val + 1;
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;

		novaInstrucao = criarNoAssembly(typeJ, "jal");
		novaInstrucao->tipoJ->labelImediato = strdup(instrucao->arg1->nome);
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;
		
		// TODO: Voltar o valor de $fp antes de voltar para a funcao anterior
		// Volta os valores de $sp
		/* novaInstrucao = criarNoAssembly(typeI, "lw");
		novaInstrucao->tipoI->rt = $fp;
		novaInstrucao->tipoI->rs = $fp;
		novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, get_variavel(funcaoAtual, "Registrador $fp"));
		instrucoesAssembly[indiceAssembly++] = novaInstrucao; */

		novaInstrucao = criarNoAssembly(typeI, "lw");
		novaInstrucao->tipoI->rt = $sp;
		novaInstrucao->tipoI->rs = $fp;
		novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, get_variavel(funcaoAtual, "Registrador $sp"));
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;

		if(instrucao->arg3->tipo != Vazio){
			// Armazena o valor do retorno da funcao anterior no registrador passado como argumento
			novaInstrucao = criarNoAssembly(typeI, "lw");
			novaInstrucao->tipoI->rt = instrucao->arg3->val;
			novaInstrucao->tipoI->rs = $fp;
			novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, get_variavel(funcaoAtual, "Valor Retorno"));
			instrucoesAssembly[indiceAssembly++] = novaInstrucao;
		}
	} 
	else if(!strcmp(instrucao->op, "END")){
		if(!strcmp(instrucao->arg1->nome, "main")){
			return; // Nao precisa fazer mais nada, ja que a proxima instrucao eh o HALT
		}
		
		// Restaura o valor de $ra da funcao anterior
		novaInstrucao = criarNoAssembly(typeI, "lw");
		novaInstrucao->tipoI->rs = $fp;
		novaInstrucao->tipoI->rt = $ra;
		novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, get_variavel(funcaoAtual, "Endereco Retorno"));
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;
		
		// Acessa o valor de controle da funcao anterior
		novaInstrucao = criarNoAssembly(typeI, "lw");
		novaInstrucao->tipoI->rt = $temp;
		novaInstrucao->tipoI->rs = $fp;
		novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, get_variavel(funcaoAtual, "Vinculo Controle"));
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;

		// Restaura o valor de $fp da funcao anterior
		novaInstrucao = criarNoAssembly(typeI, "lw");
		novaInstrucao->tipoI->rs = $temp;
		novaInstrucao->tipoI->rt = $fp;
		novaInstrucao->tipoI->imediato = 4; // 4 para avancar para "Registrador $fp"
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;
	
		// Pula para a instrucao que fez a chamada da funcao
		novaInstrucao = criarNoAssembly(typeR, "jr");
		novaInstrucao->tipoR->rs = $ra;
		novaInstrucao->tipoR->rd = $zero;
		novaInstrucao->tipoR->rt = $zero;
		instrucoesAssembly[indiceAssembly++] = novaInstrucao;

	}
	else{
		printf(ANSI_COLOR_RED);
		printf("Erro: ");
		printf(ANSI_COLOR_RESET);
		printf("Instrucao nao reconhecida (%s)\n", instrucao->op);
	}

}