#ifndef _BIN_H_ 
#define _BIN_H_ 1

/* Ao declarar as structs e suas variaveis da forma como mostrada
eh possivel utilizar a memoria de forma mais eficiente, pois
o compilador nao ira adicionar bytes de padding entre as variaveis.
Isso vai facilitar na hora de escrever os dados binarios no arquivo
ja que o tamanho da struct sera exatamente o tamanho dos dados */

typedef struct {
    unsigned int funct:6;
    unsigned int shamt:5;
    unsigned int rd:5;
    unsigned int rt:5;
    unsigned int rs:5;
    unsigned int opcode:6;
} BIN_R;

typedef struct {
    unsigned int immediate:16;
    unsigned int rt:5;
    unsigned int rs:5;
    unsigned int opcode:6;
} BIN_I;

typedef struct {
    unsigned int address:26;
    unsigned int opcode:6;
} BIN_J;

void binario(FILE* arquivo);
void binario_debug(FILE* arquivo);
#endif