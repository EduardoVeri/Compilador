#ifndef _BIN_H_ 
#define _BIN_H_ 1

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

#endif