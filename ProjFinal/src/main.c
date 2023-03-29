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

//Funcao Principal do Compilador 
int main(int argc, char *argv[]){
    qntLinhas = 1;
    arquivoEntrada = NULL;
    copiaArquivo = NULL;

    //Verifica se o numero de argumentos passados é valido
    if(argc == 1){
        //Caso nao seja passado nenhum argumento, o arquivo de entrada é o stdin
        arquivoEntrada = stdin;
    }
    else if (argc == 2){
        //Caso seja passado um argumento, o arquivo de entrada é o arquivo passado como argumento
        arquivoEntrada = fopen(argv[1], "r");
        if(arquivoEntrada == NULL){
            printf("Erro: Arquivo não encontrado.\n");
            return 0;
        }
    }
    else {
        //Caso seja passado mais de um argumento, o numero de argumentos é invalido
        printf("Erro: Numero de argumentos invalidos.\n");
        return 0;
    }
    
    //Chama a funcao do parser, para iniciar a analise do codigo
	PONTEIRONO arvoreSintatica = parse();

    //Verifica se a arvore sintatica foi criada corretamente
    if(arvoreSintatica == NULL){
		printf(ANSI_COLOR_RED);
		printf("\nNao foi possivel realizar a analise semantica.\n");
		printf("Existem erros sintaticos ou lexicos no codigo.\n");
		printf(ANSI_COLOR_RESET);

		if(arquivoEntrada != stdin)
			fclose(arquivoEntrada);
		if(copiaArquivo != NULL){
			fclose(copiaArquivo);
		}
        
		return 0;
	}

	//Imprime a arvore sintatica
	mostraArvore(arvoreSintatica, 0);
	printf("\n\n");
    
	//Inicializa a tabela de simbolos
	PONTEIROITEM* tabelaHash = inicializaTabela();

	//Adiciona as funções input e output na tabela de simbolos
	inserirTabela(tabelaHash, FunDeclK, Type_Int, "input", "global", 0);
	inserirTabela(tabelaHash, FunDeclK, Type_Void, "output", "global", 0);

	//Percorre a arvore sintatica e adiciona os itens de declaracao na tabela de simbolos
	percorrerArvore(arvoreSintatica, tabelaHash, "global");

	//Verifica se a funcao main foi declarada
	if(procuraTabelaExp(tabelaHash, "main", "global", AtivK) == NULL){
		mostrarErroSemantico(FuncMainNaoDeclarada, "main", qntLinhas);
	}

	//imprime a tabela de simbolos
	imprimirTabela(tabelaHash);

	/* Caso tenha algum erro semantico, nao criar e mostrar o codigo intermediario*/
    
	if(teveErroSemantico == 0){    
		//Cria o codigo intermediario
		codigoIntermediario = inicializaVetor();
		criarCodigoIntermediario(arvoreSintatica, tabelaHash, 1);
        
		//Adiciona o HALT no final do codigo intermediario
		codigoIntermediario[indiceVetor] = criaInstrucao("HALT"); 
        
		//Imprime o codigo intermediario
		imprimeCodigoIntermediario();
		
		//Mostra os registradores em uso
		mostrarReg();

		//assembly();

		//Libera a memoria alocada para o codigo intermediario
		desalocaVetor();
	}
	else{
		//Mostrar uma mensagem de erro sobre os erros semanticos
		printf(ANSI_COLOR_RED);
		//Verifica se teve apenas um erro semantico para a escrita no singular ou plural
		if(teveErroSemantico == 1)
			printf("Nao foi possivel gerar o codigo intermediario, pois o codigo fonte possui %d erro semantico.\n", teveErroSemantico);
		else if(teveErroSemantico > 1)
			printf("Nao foi possivel gerar o codigo intermediario, pois o codigo fonte possui %d erros semanticos.\n", teveErroSemantico);
		printf(ANSI_COLOR_RESET);
	}

	//libera a memória alocada para a arvore sintatica
	desalocaArvore(arvoreSintatica);

	//libera a memoria alocada para a tabela de simbolos
	apagarTabela(tabelaHash);


    //Fecha os arquivos abertos
	if(arquivoEntrada != stdin)
		fclose(arquivoEntrada);
		
	if(copiaArquivo != NULL)
		fclose(copiaArquivo);

	// Remove o arquivo de copia
	remove("src/copia.txt");

	return 0;
}
