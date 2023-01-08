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
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tabelaSimb.h"
#include "parser.tab.h"
#include "global.h"
#include "semantica.h"
#include "codInterm.h"


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
        if(arquivoEntrada != stdin)
            fclose(arquivoEntrada);
        fclose(copiaArquivo);
        return 0;
        //TODO - Desalocar a memoria alocada para os nos da arvore sintatica no parser
    }

    //Imprime a arvore sintatica
    mostraArvore(arvoreSintatica, 0);
	printf("\n\n");
    
    //Inicializa a tabela de simbolos
	PONTEIROITEM* tabelaHash = inicializaTabela();

    //Adiciona as funções input e output na tabela de simbolos
	inserirTabela(tabelaHash, FunDeclK, Type_Int, "input", "global", 0);
	inserirTabela(tabelaHash, FunDeclK, Type_Void, "output", "global", 0);

	char escopo[26] = "global"; 

	//Percorre a arvore sintatica e adiciona os itens de declaracao na tabela de simbolos
	percorrerArvore(arvoreSintatica, tabelaHash, escopo);

    //Verifica se a funcao main foi declarada
	if(procuraTabelaExp(tabelaHash, "main", "global", AtivK) == NULL){
		mostrarErroSemantico(FuncMainNaoDeclarada, "main", qntLinhas);
	}

    printf("============== Tabela de Simbolos ===============\n");
	//imprime a tabela de simbolos
	imprimirTabela(tabelaHash);

    /* TODO: Caso tenha algum erro semantico, nao mostrar o codigo intermediario*/
    
    printf("============== Codigo Intermediario ===============\n");
    
    //Cria o codigo intermediario
    codigoIntermediario = inicializaVetor();
    criarCodigoIntermediario(arvoreSintatica, tabelaHash, 1);
    //Adiciona o HALT no final do codigo intermediario
    codigoIntermediario[indiceVetor] = criaInstrucao("HALT"); 

    //Imprime o codigo intermediario
    imprimeCodigoIntermediario();

	//libera a memória alocada para a arvore sintatica
	desalocaArvore(arvoreSintatica);

	//libera a memoria alocada para a tabela de simbolos
	apagarTabela(tabelaHash);

    //Libera a memoria alocada para o codigo intermediario
    desalocaVetor();

    //Fecha os arquivos abertos
    if(arquivoEntrada != stdin)
        fclose(arquivoEntrada);
    
    if(copiaArquivo != NULL)
        fclose(copiaArquivo);

    return 0;
}
