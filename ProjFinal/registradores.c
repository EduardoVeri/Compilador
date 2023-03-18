#include <stdio.h>
#include <string.h>
#include "global.h"
#include "codInterm.h"

#define MAX_REG 30 //Numero maximo de registradores

char stringTemp[MAXLEXEMA] = "Temporario"; //Nome da funcao

typedef struct reg{
	int numReg;
	char* nomeVar;
	char escopo[MAXLEXEMA];
	int descarte; //Diz se o registrador pode ser descartado (1) ou nao (0)
}REG;

REG listaReg[MAX_REG]; //Lista encadeada com os registradores

//Funcao para inicializar o vetor de registradores
void inicializaReg(){
	for(int i = 0; i < MAX_REG; i++){
		listaReg[i].numReg = i;
		listaReg[i].nomeVar = NULL;
		strcpy(listaReg[i].escopo, "");
		listaReg[i].descarte = 0;
	}
}

//Adiciona uma variavel em um registrador
int adicionarVarReg(char* nomeVar, char* escopo){
	for(int i = 0; i < MAX_REG; i++){
		if(listaReg[i].nomeVar == NULL){
			listaReg[i].nomeVar = nomeVar;
			strcpy(listaReg[i].escopo, escopo);
			listaReg[i].descarte = 0;
			return i;
		}
	}
	return -1; //Nao foi possivel adicionar a variavel em nenhum registrador
}

//Adiciona uma variavel temporaria em um registrador, normalmente utilizada em operacoes
int adicionaTempReg(){
	for(int i = 0; i < MAX_REG; i++){
		if(listaReg[i].nomeVar == NULL){
			listaReg[i].nomeVar = stringTemp;
			strcpy(listaReg[i].escopo, funcName);
			listaReg[i].descarte = 1;
			return i;
		}
	}
	return -1; //Nao foi possivel adicionar a variavel em nenhum registrador
}

int buscarVarReg(char* nomeVar, char* escopo){
	for(int i = 0; i < MAX_REG; i++){
		if(listaReg[i].nomeVar != NULL){
			if(strcmp(listaReg[i].nomeVar, nomeVar) == 0 && strcmp(listaReg[i].escopo, escopo) == 0){
				return i;
			}
		}
	}
	return -1; //Nao foi possivel encontrar a variavel em nenhum registrador
}

void mostrarReg(){
	int cont = 0;
	printf("\n============== Registradores ===============\n");
	for(int i = 0; i < MAX_REG; i++){
		if(listaReg[i].nomeVar != NULL){
			printf("t%d: %s, %s\n", listaReg[i].numReg, listaReg[i].nomeVar, listaReg[i].escopo);
			cont++;
		}
	}
	printf("%d Registradores Livres\n\n", MAX_REG - cont);
}