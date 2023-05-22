/*
 *  Projeto compilador desenvolvido para o trabalho final de disciplinas
 *  do curso de Engenharia da Computacao na Universidade Federal de Sao Paulo (UNIFESP)
 * 
 * 	Fase de Analise desenvolvida na disciplina de Compiladores
 *  Fase de Montagem desenvolvida na disciplina de Lab. de Compiladores
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

#define MAX_ARG 5 // Numero maximo de argumentos que podem ser passados para o compilador

int flagVerbose = 0;
FILE * arquivoEntrada = NULL; // Arquivo de entrada
FILE * copiaArquivo = NULL; // Cópia do arquivo de entrada
FILE * arquivoSaida = NULL; // Arquivo de saída
FILE * arquivoSaida_Intermediario = NULL; // Arquivo de saída do código intermediário

void desaloca_estruturas_analise(PONTEIRONO arvoreSintatica, PONTEIROITEM* tabelaHash);

// Funcao Principal do Compilador 
int main(int argc, char *argv[]){	
	int flagCI = 0;
	int flagCA = 0;
	arquivoSaida = stdout;
	arquivoSaida_Intermediario = stdout;
	qntLinhas = 1;
    arquivoEntrada = NULL;
    copiaArquivo = NULL;
	
    // Verifica se o numero de argumentos passados é valido
    if (argc >= 2 && argc < MAX_ARG + 1){
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
			else if((!strcmp(argv[i], "-CA")) || (!strcmp(argv[i], "-ca"))){
				flagCA = 1;
				copiaArquivo = fopen("bin/codigoAssembly.txt", "w");
				if(copiaArquivo == NULL){
					printf(ANSI_COLOR_RED "Erro: " ANSI_COLOR_RESET);
					printf("Nao foi possivel criar o arquivo para o codigo assembly.\n");
					flagCA = 0;
				}
			}
			else{
				arquivoEntrada = fopen(argv[i], "r");
				if(arquivoEntrada == NULL){
					printf("Erro: Arquivo não encontrado.\n");
					return 1;
				}
			}
		}
		if (arquivoEntrada == NULL){
			printf("Erro: Arquivo não fornecido.\n");
			printf("./compilador <-ni> --> Sem arquivos de entrada\n./compilador <arquivo.cm> <-v> <-ci> --> Com arquivos de entrada\n");
			return 1;
		}
    }
    else {
        // Caso seja passado mais de um argumento, o numero de argumentos é invalido
       	printf("./compilador <-ni> --> Sem arquivos de entrada\n./compilador <arquivo.cm> <-v> <-ci> --> Com arquivos de entrada\n");
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

		if(arquivoEntrada != stdin) fclose(arquivoEntrada);
		if(copiaArquivo != NULL) fclose(copiaArquivo);
		if(flagCI) fclose(arquivoSaida_Intermediario);
		if(flagVerbose) fclose(arquivoSaida);
        
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
		// Mostrar uma mensagem de erro sobre os erros semanticos
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
	
	// Mostra os registradores em uso
	mostrarReg();

	// Desaloca as estruturas de analise
	desaloca_estruturas_analise(arvoreSintatica, tabelaHash);

	assembly(); // Inicia o processo de montagem do codigo assembly

	// Imprime o codigo assembly e os labels
	imprimirAssembly();
	imprimirLabels();

	liberarAssembly(); // Libera a memoria alocada para o codigo assembly
	liberarLabels(); // Libera a memoria alocada para os labels
	desalocaVetor(); // Libera a memoria alocada para o codigo intermediario
	
	return 0;
}

void desaloca_estruturas_analise(PONTEIRONO arvoreSintatica, PONTEIROITEM* tabelaHash){
	desalocaArvore(arvoreSintatica);
	apagarTabela(tabelaHash);
}