#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "codInterm.h"
#include "assembly.h" // Ja inclui label.h dentro dela
#include "binario.h"

unsigned int get_opcode(char* nome, tipoInstrucao tipo){
    int opcode = -1;

    if(tipo == typeR) return 0b000000;
    
    if(!strcmp(nome, "lw")) opcode = 0b100011;
    else if(!strcmp(nome, "sw")) opcode = 0b101011;
    else if(!strcmp(nome, "addi")) opcode = 0b001000;
	else if(!strcmp(nome, "subi")) opcode = 0b001001;
	else if(!strcmp(nome, "andi")) opcode = 0b001100;
	else if(!strcmp(nome, "ori")) opcode = 0b001101;
	else if(!strcmp(nome, "beq")) opcode = 0b000100;
	else if(!strcmp(nome, "bne")) opcode = 0b000101;
	else if(!strcmp(nome, "slti")) opcode = 0b001010;
	else if(!strcmp(nome, "in")) opcode = 0b011111;
	else if(!strcmp(nome, "out")) opcode = 0b011110;
	else if(!strcmp(nome, "j")) opcode = 0b000010;
	else if(!strcmp(nome, "jal")) opcode = 0b000011;
	else if(!strcmp(nome, "halt")) opcode = 0b111111;
	else if(!strcmp(nome, "xori")) opcode = 0b101101;
    
    return opcode;
}

unsigned int get_funct(char* nome){
	int funct = -1;

	if(!strcmp(nome, "add")) funct = 0b100000;
	else if(!strcmp(nome, "sub")) funct = 0b100010;
	else if(!strcmp(nome, "and")) funct = 0b100100;
	else if(!strcmp(nome, "or")) funct = 0b100101;
	else if(!strcmp(nome, "jr")) funct = 0b001000;
	else if(!strcmp(nome, "jalr")) funct = 0b001001;
	else if(!strcmp(nome, "slt")) funct = 0b101010;
	else if(!strcmp(nome, "nor")) funct = 0b100111;
	else if(!strcmp(nome, "sll")) funct = 0b000000;
	else if(!strcmp(nome, "srl")) funct = 0b000010;
	else if(!strcmp(nome, "div")) funct = 0b011010;
	else if(!strcmp(nome, "mult")) funct = 0b011000;
	else if(!strcmp(nome, "xor")) funct = 0b101101;
	
	return funct;
}

unsigned int get_register(int reg){
	return reg;
}

unsigned int get_shamt(int shamt){
	return shamt;
}

unsigned int get_immediate(int imediato){
	return imediato;
}	

unsigned int get_address(char* label){
	printf("get_address: %s", label);
	int endereco = getEnderecoLabel(label);
	printf("\tendereco: %d\n", endereco);
	return endereco;
}

BIN_R* binarioNop(){
	BIN_R* bin = (BIN_R*)malloc(sizeof(BIN_R));
	bin->opcode = 0;
	bin->rs = $zero;
	bin->rt = $zero;
	bin->rd = $zero;
	bin->shamt = 0;
	bin->funct = 0b100000;
	return bin;
}

BIN_R* binarioR(ASSEMBLY* instrucao){
	BIN_R* bin = (BIN_R*)malloc(sizeof(BIN_R));
	bin->opcode = get_opcode(instrucao->tipoR->nome, instrucao->tipo);
	bin->rs = get_register(instrucao->tipoR->rs);
	bin->rt = get_register(instrucao->tipoR->rt);
	bin->rd = get_register(instrucao->tipoR->rd);
	bin->shamt = get_shamt(0);
	bin->funct = get_funct(instrucao->tipoR->nome);
	return bin;
	
}

BIN_I* binarioI(ASSEMBLY* instrucao){
	BIN_I* bin = (BIN_I*)malloc(sizeof(BIN_I));
	bin->opcode = get_opcode(instrucao->tipoI->nome, instrucao->tipo);
	bin->rs = get_register(instrucao->tipoI->rs);
	bin->rt = get_register(instrucao->tipoI->rt);
	
	if(!strcmp(instrucao->tipoI->nome, "bne") || !strcmp(instrucao->tipoI->nome, "beq")){
		// Converte numero para string
		char label[26];
		sprintf(label, "Label %d", instrucao->tipoI->label);
		bin->immediate = get_address(label);
	}
	else{
		bin->immediate = get_immediate(instrucao->tipoI->imediato);
	}

	return bin;
}

BIN_J* binarioJ(ASSEMBLY* instrucao){
	BIN_J* bin = (BIN_J*)malloc(sizeof(BIN_J));
	bin->opcode = get_opcode(instrucao->tipoJ->nome, instrucao->tipo);
	bin->address = get_address(instrucao->tipoJ->labelImediato);
	return bin;
}		


void printBits(size_t const size, void const * const ptr, FILE* arquivo)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            fprintf(arquivo, "%u", byte);
        }
    }
}

void mostrar_binario(tipoInstrucao tipo, void* binario, FILE* arquivo){
	
	if(tipo == typeR){
		BIN_R* bin = (BIN_R*)binario;
		printBits(sizeof(*bin), &(*bin), arquivo);
	}
	else if(tipo == typeI){
		BIN_I* bin = (BIN_I*)binario;
		printBits(sizeof(*bin), &(*bin), arquivo);
	}
	else if(tipo == typeJ){
		BIN_J* bin = (BIN_J*)binario;
		printBits(sizeof(*bin), &(*bin), arquivo);
	}
}

void binario(FILE* arquivo){
	BIN_I* binI;
	BIN_J* binJ;
	BIN_R* binR;
	
	for(int i = 0; i < indiceAssembly; i++){
		switch (instrucoesAssembly[i]->tipo)
		{
		case typeR:
			binR = binarioR(instrucoesAssembly[i]);
			mostrar_binario(instrucoesAssembly[i]->tipo, binR, arquivo);
			//fprintf(arquivo, " : %s", instrucoesAssembly[i]->tipoR->nome);
			fprintf(arquivo, "\n");
			free(binR);
			break;
		case typeI:
			if(!strcmp(instrucoesAssembly[i]->tipoI->nome, "bne")) printf("%d: bne -> \t", i);
			binI = binarioI(instrucoesAssembly[i]);
			mostrar_binario(instrucoesAssembly[i]->tipo, binI, arquivo);
			//fprintf(arquivo, " : %s", instrucoesAssembly[i]->tipoI->nome);
			fprintf(arquivo, "\n");
			free(binI);
			break;
		case typeJ:
			binJ = binarioJ(instrucoesAssembly[i]);
			mostrar_binario(instrucoesAssembly[i]->tipo, binJ, arquivo);
			//fprintf(arquivo, " : %s", instrucoesAssembly[i]->tipoJ->nome);
			fprintf(arquivo, "\n");
			free(binJ);
			break;
		case typeLabel:
			binR = binarioNop();
			mostrar_binario(typeR, binR, arquivo);
			//fprintf(arquivo, " : nop");
			fprintf(arquivo, "\n");
			break;
		}
	}
}

void binario_debug(FILE* arquivo){
	BIN_I* binI;
	BIN_J* binJ;
	BIN_R* binR;
	
	for(int i = 0; i < indiceAssembly; i++){
		fprintf(arquivo, "%d:\t", i);
		switch (instrucoesAssembly[i]->tipo)
		{
		case typeR:
			binR = binarioR(instrucoesAssembly[i]);
			mostrar_binario(instrucoesAssembly[i]->tipo, binR, arquivo);
			fprintf(arquivo, " : %s", instrucoesAssembly[i]->tipoR->nome);
			fprintf(arquivo, "\n");
			free(binR);
			break;
		case typeI:
			binI = binarioI(instrucoesAssembly[i]);
			mostrar_binario(instrucoesAssembly[i]->tipo, binI, arquivo);
			fprintf(arquivo, " : %s", instrucoesAssembly[i]->tipoI->nome);
			fprintf(arquivo, "\n");
			free(binI);
			break;
		case typeJ:
			binJ = binarioJ(instrucoesAssembly[i]);
			mostrar_binario(instrucoesAssembly[i]->tipo, binJ, arquivo);
			fprintf(arquivo, " : %s", instrucoesAssembly[i]->tipoJ->nome);
			fprintf(arquivo, "\n");
			free(binJ);
			break;
		case typeLabel:
			binR = binarioNop();
			mostrar_binario(typeR, binR, arquivo);
			fprintf(arquivo, " : nop");
			fprintf(arquivo, "\n");
			break;
		}
	}
}