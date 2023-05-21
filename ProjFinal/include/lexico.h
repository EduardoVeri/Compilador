#ifndef _Lexico_H_
#define _Lexico_H_ 1

#include "global.h"


extern int indPilha;
extern int qntLinhas; // Contador de linhas
extern char* yytext; // Texto do lexema
extern char pilha[4][MAXLEXEMA]; 
#endif