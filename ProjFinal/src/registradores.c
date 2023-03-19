#include <stdio.h>
#include <string.h>
#include "global.h"
#include "codInterm.h"

#define MAX_REG 30 // Numero maximo de registradores
#define MAX_REG_DESCARTE 10000000 // Numero maximo de registradores que podem ser descartados

char stringTemp[MAXLEXEMA] = "Temporario"; // Nome para identificar variaveis temporarias

/* Essa variavel sera importante para o discarte dos registradores, ja
que registradores usados pela ultima vez a algum tempo serao eliminados primeiro
do que os usados recentemente, para tentar evitar conflitos em instrucoes */
int totalReg = 1;

int totalRegEmUso = 0; 

typedef struct reg{
	int numReg;
	char* nomeVar;
	char escopo[MAXLEXEMA];
	int descarte; //Diz se o registrador pode ser descartado (1, 2, ..., n) ou nao (0)
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

			totalRegEmUso++;
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
			listaReg[i].descarte = totalReg;
			totalReg++;
			totalRegEmUso++;
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
			printf("t%d: %s, %s, %d\n", listaReg[i].numReg, listaReg[i].nomeVar, listaReg[i].escopo, listaReg[i].descarte);
		}
	}
	printf("%d Registradores Livres\n\n", MAX_REG - totalRegEmUso);
}

//Funcao para descartar registradores
int descartarReg(){
	int maior = 1000000; // Marca se houve descarte de registrador
	
	for(int i = 0; i < MAX_REG; i++){
		if(listaReg[i].descarte > 0){
			listaReg[i].nomeVar = NULL;
			strcpy(listaReg[i].escopo, "");
			listaReg[i].descarte = 0;
			
			if(maior > i)
				maior = i;
		}
	}

	if(maior == MAX_REG_DESCARTE){
		printf(ANSI_COLOR_RED);
		printf("ERRO: Nao foi possivel descartar nenhum registrador\n");
		printf(ANSI_COLOR_RESET);

		return -1;
	}

	return maior;

}

int totalRegistradores(){
	return totalRegEmUso;
}