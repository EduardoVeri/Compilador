/*
 *  Projeto compilador desenvolvido para o trabalho final de disciplinas
 *  do curso de Engenharia da Computacao na Universidade Federal de Sao Paulo (UNIFESP)
 * 
 * 	Fase de Analise desenvolvida na disciplina de Compiladores
 *  Fase de Sintese desenvolvida na disciplina de Lab. de Compiladores
 * 
 *  Docente: Prof. Dr. Luis Augusto Martins Pereira
 *  Docente: Profa. Dra. Taina Aparecida Azevedo Tosta
 * 
 *  Desenvolvido por: Eduardo Verissimo Faccio
 *  RA: 148859
 *  Data: 21/05/2023
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tabelaSimb.h"
#include "parser.tab.h"
#include "global.h"
#include "semantica.h"
#include "codInterm.h"
#include "assembly.h"
#include "binario.h"
#include "memoria.h"

#define MAX_ARG 5 // Numero maximo de argumentos que podem ser passados para o compilador

int flagVerbose = 0;
FILE * arquivoEntrada = NULL; // Arquivo de entrada
FILE * copiaArquivo = NULL; // Cópia do arquivo de entrada
FILE * arquivoSaida = NULL; // Arquivo de saída
FILE * arquivoSaida_Intermediario = NULL; // Arquivo de saída do código intermediário
FILE * arquivoSaida_Assembly = NULL; // Arquivo de saída do código assembly

void desaloca_estruturas_analise(PONTEIRONO arvoreSintatica, PONTEIROITEM* tabelaHash);
void desaloca_estruturas_sintese();

// Funcao Principal do Compilador 
int main(int argc, char *argv[]){	
	int flagCI = 0;
	int flagCA = 0;
	arquivoSaida = stdout;
	arquivoSaida_Intermediario = stdout;
	arquivoSaida_Assembly = stdout;
	qntLinhas = 1;
    arquivoEntrada = NULL;
    copiaArquivo = NULL;
	FILE * arquivoSaida_Binario = NULL; // Arquivo de saída do código binário

    // Verifica se o numero de argumentos passados é valido
	 if (argc < 2){
       	printf("%s <-ni> --> Sem arquivos de entrada\n./compilador <arquivo.cm> <-v> <-ci> --> Com arquivos de entrada\n", argv[0]);
        return 0;
    }

	// Caso seja passado um argumento, o arquivo de entrada é o arquivo passado como argumento
	for(int i=1; i<argc; i++){
		// Para ativar o modo verbose e criar um arquivo de saída "Resultados"
		if((strcmp(argv[i], "-V") == 0) || (strcmp(argv[i], "-v") == 0)){
			flagVerbose = 1;
			arquivoSaida = fopen("bin/results.txt", "w");
		}
		// Para gerar o código intermediário em um arquivo
		else if((strcmp(argv[i], "-CI") == 0) || (strcmp(argv[i], "-ci") == 0)){
			flagCI = 1;
			arquivoSaida_Intermediario = fopen("bin/codigoIntermediario.txt", "w");
			if(arquivoSaida_Intermediario == NULL){
				printf(ANSI_COLOR_RED "Erro: " ANSI_COLOR_RESET);
				printf("Nao foi possivel criar o arquivo de codigo intermediario.\n");
				flagCI = 0;
			}
		}
		// Argumento para não precisar ler arquivo (No Input)
		else if((strcmp(argv[i], "-NI") == 0) || (strcmp(argv[i], "-ni") == 0)){
			arquivoEntrada = stdin;
			arquivoSaida = stdout;
			flagVerbose = 1;
			i = MAX_ARG; // Para sair do loop for, ja que os demais argumentos nao importam
		}
		// Argumento para gerar o código assembly em um arquivo
		else if((!strcmp(argv[i], "-CA")) || (!strcmp(argv[i], "-ca"))){
			flagCA = 1;
			arquivoSaida_Assembly = fopen("bin/codigoAssembly.txt", "w");
			if(arquivoSaida_Assembly == NULL){
				printf(ANSI_COLOR_RED "Erro: " ANSI_COLOR_RESET);
				printf("Nao foi possivel criar o arquivo para o codigo assembly.\n");
				flagCA = 0;
				arquivoSaida_Assembly = stdout;
			}
		}
		else if((!strcmp(argv[i], "-O")) || (!strcmp(argv[i], "-o"))){
			arquivoSaida_Binario = fopen(argv[i+1], "w");
			if(arquivoSaida_Binario == NULL){
				printf(ANSI_COLOR_RED "Erro: " ANSI_COLOR_RESET);
				printf("Nao foi possivel criar o arquivo de saida.\n");
			}
			i++;
		}
		else{
			// Abre o arquivo de entrada
			if(arquivoEntrada){
				printf(ANSI_COLOR_RED "Erro: " ANSI_COLOR_RESET);
				printf("Argumento '%s' desconsiderado.\n", argv[i]);
			}
			else{
				arquivoEntrada = fopen(argv[i], "r");
				if(arquivoEntrada == NULL){
					printf(ANSI_COLOR_RED "Erro: " ANSI_COLOR_RESET);
					printf("Arquivo '%s' não encontrado.\n", argv[i]);
				}
			}
		}
	}
	if (arquivoEntrada == NULL){
		printf("Erro: Arquivo não fornecido.\n");
		printf("%s <-ni> --> Sem arquivos de entrada\n./compilador <arquivo.cm> <-v> <-ci> --> Com arquivos de entrada\n", argv[0]);
		if(flagCI) fclose(arquivoSaida_Intermediario);
		if(flagVerbose) fclose(arquivoSaida);
		if(flagCA) fclose(arquivoSaida_Assembly);
		return 1;
	}
    
	PONTEIRONO arvoreSintatica = parse(); // Chama a funcao do parser, para iniciar a analise do codigo

	if(arquivoEntrada != stdin) fclose(arquivoEntrada); //Fecha os arquivos abertos
	if(copiaArquivo != NULL) fclose(copiaArquivo); // Fecha e remove o arquivo de copia 
	remove("src/copia.txt");

    // Verifica se a arvore sintatica foi criada corretamente
    if(arvoreSintatica == NULL){
		printf(ANSI_COLOR_RED);
		printf("\nNao foi possivel realizar a analise semantica.\n");
		printf("Existem erros sintaticos ou lexicos no codigo.\n");
		printf(ANSI_COLOR_RESET);

		if(flagCI) fclose(arquivoSaida_Intermediario);
		if(flagVerbose) fclose(arquivoSaida);
		if(flagCA) fclose(arquivoSaida_Assembly);

		return 0;
	}

	// Inicializa a tabela de simbolos
	PONTEIROITEM* tabelaHash = inicializaTabela();

	// Adiciona as funções input e output na tabela de simbolos
	inserirTabela(tabelaHash, FunDeclK, Type_Int, "input", "global", 0);
	inserirTabela(tabelaHash, FunDeclK, Type_Void, "output", "global", 0);

	// Percorre a arvore sintatica e adiciona os itens de declaracao na tabela de simbolos
	percorrerArvore(arvoreSintatica, tabelaHash, "global");

	// Verifica se a funcao main foi declarada
	if(procuraTabelaExp(tabelaHash, "main", "global", AtivK) == NULL){
		mostrarErroSemantico(FuncMainNaoDeclarada, "main", qntLinhas);
	}

	// Mostra os resultados obtidos na fase de analise 
	if(flagVerbose){
		mostraArvore(arvoreSintatica, 0); // Imprime a arvore sintatica
		fprintf(arquivoSaida, "\n\n");
		imprimirTabela(tabelaHash); // Imprime a tabela de simbolos
		fclose(arquivoSaida); // Fecha o arquivo de saida
	} 
	else{
		remove("bin/results.txt");
	}

	/* Caso tenha algum erro semantico, nao criar e mostrar o codigo intermediario*/
	if(teveErroSemantico != 0){    
		printf(ANSI_COLOR_RED);
		// Verifica se teve apenas um erro semantico para a escrita no singular ou plural
		if(teveErroSemantico == 1)
			printf("Nao foi possivel gerar o codigo intermediario, pois o codigo fonte possui %d erro semantico.\n", teveErroSemantico);
		else if(teveErroSemantico > 1)
			printf("Nao foi possivel gerar o codigo intermediario, pois o codigo fonte possui %d erros semanticos.\n", teveErroSemantico);
		printf(ANSI_COLOR_RESET);

		desaloca_estruturas_analise(arvoreSintatica, tabelaHash);

		return 0;
	}

	inicializaVetor(); // Inicializa a estrutura de codigo intermediario
	criarCodigoIntermediario(arvoreSintatica, tabelaHash, 1); 
	
	// Adiciona o HALT no final do codigo intermediario
	codigoIntermediario[indiceVetor++] = criaInstrucao("HALT"); 
	
	if(flagCI){ 
		imprimeCodigoIntermediario(); // Imprime o codigo intermediario
		fclose(arquivoSaida_Intermediario); // Fecha o arquivo de codigo intermediario
	} 
	else{
		remove("bin/codigoIntermediario.txt"); // Remove o arquivo de codigo intermediario
	}
	
	//mostrarReg(); // Mostra os registradores em uso

	desaloca_estruturas_analise(arvoreSintatica, tabelaHash); // Desaloca as estruturas de analise

	assembly(); // Inicia o processo de montagem do codigo assembly

	// Imprime o codigo assembly e os labels
	if(flagCA){ 
		imprimirAssembly();
		fclose(arquivoSaida_Assembly); // Fecha o arquivo de codigo assembly
	}
	else{
		remove("bin/codigoAssembly.txt"); // Remove o arquivo de codigo assembly
	}  

	imprime_memoria(); // Imprime a memoria
	imprimirLabels(); // Imprime os labels
	
	if(!arquivoSaida_Binario){
		arquivoSaida_Binario = fopen("bin/codigoBinario.txt", "w");
		if(arquivoSaida == NULL){
			printf(ANSI_COLOR_RED "Erro:" ANSI_COLOR_RESET);
			printf("Nao foi possivel criar o arquivo de saida.\n");
			desaloca_estruturas_sintese();
			return 0;
		}
	}
	
	binario(arquivoSaida_Binario); // Inicia o processo de conversao do codigo assembly para binario
	fclose(arquivoSaida_Binario); // Fecha o arquivo de codigo binario

	FILE* arquivo_debug = fopen("bin/debug.txt", "w");
	binario_debug(arquivo_debug);
	fclose(arquivo_debug);

	desaloca_estruturas_sintese(); 

	printf(ANSI_COLOR_GREEN "Compilacao realizada com sucesso!\n" ANSI_COLOR_RESET);
	
	return 0;
}

void desaloca_estruturas_sintese(){
	desalocaVetor(); // Libera a memoria alocada para o codigo intermediario
	liberarAssembly(); // Libera a memoria alocada para o codigo assembly
	liberarTabMemoria(); // Libera a memoria alocada para a memoria
	liberarLabels(); // Libera a memoria alocada para os labels
}

void desaloca_estruturas_analise(PONTEIRONO arvoreSintatica, PONTEIROITEM* tabelaHash){
	desalocaArvore(arvoreSintatica); // Desaloca a arvore sintatica
	apagarTabela(tabelaHash); // Desaloca a tabela de simbolos
}