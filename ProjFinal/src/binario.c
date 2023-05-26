#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "assembly.h"

typedef struct {
	unsigned int opcode:6;
	unsigned int rs:5;
	unsigned int rt:5;
	unsigned int rd:5;
	unsigned int shamt:5;
	unsigned int funct:6;
} BIN_R;

typedef struct {
	unsigned int opcode:6;
	unsigned int rs:5;
	unsigned int rt:5;
	unsigned int immediate:16;
} BIN_I;

typedef struct {
	unsigned int opcode:6;
	unsigned int address:26;
} BIN_J;

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
	
	return funct;
}

unsigned int get_register(int reg){
	return reg;
}

unsigned int shamt(int shamt){
	return shamt;
}

unsigned int get_immediate(int imediato){
	return imediato;
}	

/* unsigned int get_address(char* label){
	return address;
} */


/*
BIN_R* binarioR(ASSEMBLY* instrucao){

	return NULL;
}

BIN_I* binarioI()

BIN_J* binarioJ(ASSEMBLY* instrucao){
	BIN_J* bin = malloc(sizeof(BIN_J));
	bin->opcode = 2;
	bin->address = instrucao->tipoJ->labelImediato;
	return bin;
}
*/

void binario(){
	for(int i = 0; i < indiceAssembly; i++){

	}
}
