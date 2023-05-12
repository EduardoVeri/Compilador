/*
 *  Projeto compilador desenvolvido para a disciplina de compiladores
 *  do curso de Bacharelado em Ciencia e Tecnologia na Universidade 
 *  Federal de Sao Paulo (UNIFESP)
 *  
 *  Docente: Prof. Dr. Luis Augusto Martins Pereira
 * 
 *  Desenvolvido por: Eduardo Verissimo Faccio
 *  RA: 148859
 *  Data: 15/01/2023
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

int flagCI = 0;
int flagVerbose = 0;
FILE * arquivoEntrada = NULL; // Arquivo de entrada
FILE * copiaArquivo = NULL; // Cópia do arquivo de entrada
FILE * arquivoSaida = NULL; // Arquivo de saída
FILE * arquivoSaida_Intermediario = NULL; // Arquivo de saída do código intermediário

// Funcao Principal do Compilador 
int main(int argc, char *argv[]){	
	arquivoSaida = stdout;
	arquivoSaida_Intermediario = stdout;
	qntLinhas = 1;
    arquivoEntrada = NULL;
    copiaArquivo = NULL;
	
    // Verifica se o numero de argumentos passados é valido
    if (argc >= 2 && argc <= 5){
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
			}
			// Argumento no input (para não precisar ler arquivo)
			else if((strcmp(argv[i], "-NI") == 0) || (strcmp(argv[i], "-ni") == 0)){
				arquivoEntrada = stdin;
				flagVerbose = 0;
				i = argc; // Para sair do loop
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
    
    // Chama a funcao do parser, para iniciar a analise do codigo
	PONTEIRONO arvoreSintatica = parse();

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

	// Imprime a arvore sintatica
	if(flagVerbose == 1){
		mostraArvore(arvoreSintatica, 0);
		fprintf(arquivoSaida, "\n\n");
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

	// Imprime a tabela de simbolos
	if(flagVerbose == 1) imprimirTabela(tabelaHash);

	/* Caso tenha algum erro semantico, nao criar e mostrar o codigo intermediario*/
    
	if(teveErroSemantico == 0){    
		//Cria o codigo intermediario
		inicializaVetor();
		criarCodigoIntermediario(arvoreSintatica, tabelaHash, 1);
        
		// Adiciona o HALT no final do codigo intermediario
		codigoIntermediario[indiceVetor++] = criaInstrucao("HALT"); 

		imprimeCodigoIntermediario(); // Imprime o codigo intermediario
		
		// Mostra os registradores em uso
		// mostrarReg();

		assembly(); // Inicia o processo de montagem do codigo assembly

		// Imprime o codigo assembly e os labels
		imprimirAssembly();
		imprimirLabels();

		liberarAssembly(); // Libera a memoria alocada para o codigo assembly
		liberarLabels(); // Libera a memoria alocada para os labels
		desalocaVetor(); // Libera a memoria alocada para o codigo intermediario
	}
	else{
		// Mostrar uma mensagem de erro sobre os erros semanticos
		printf(ANSI_COLOR_RED);
		// Verifica se teve apenas um erro semantico para a escrita no singular ou plural
		if(teveErroSemantico == 1)
			printf("Nao foi possivel gerar o codigo intermediario, pois o codigo fonte possui %d erro semantico.\n", teveErroSemantico);
		else if(teveErroSemantico > 1)
			printf("Nao foi possivel gerar o codigo intermediario, pois o codigo fonte possui %d erros semanticos.\n", teveErroSemantico);
		printf(ANSI_COLOR_RESET);
	}
	
	// Libera a memória alocada para a arvore sintatica
	desalocaArvore(arvoreSintatica);

	// Libera a memoria alocada para a tabela de simbolos
	apagarTabela(tabelaHash);

    //Fecha os arquivos abertos
	if(arquivoEntrada != stdin) fclose(arquivoEntrada);
	
	// Fecha e remove o arquivo de copia 
	if(copiaArquivo != NULL) fclose(copiaArquivo);
	remove("src/copia.txt");

	// Remove os arquivos de saida
	if(flagVerbose == 0) remove("bin/results.txt");
	else fclose(arquivoSaida); // Fecha o arquivo de saida
	
	// Remove o arquivo de codigo intermediario
	if(flagCI == 0) remove("bin/codigoIntermediario.txt");
	else fclose(arquivoSaida_Intermediario); // Fecha o arquivo de codigo intermediario

	return 0;
}
