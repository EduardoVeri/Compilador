#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tabelaSimb.h"
#include "parser.tab.h"
#include "global.h"
#include "semantica.h"

int main(int argc, char *argv[]){
    qntLinhas = 1;
    arquivoEntrada = NULL;
    copiaArquivo = NULL;

    if(argc == 1){
        arquivoEntrada = stdin;
    }
    else if (argc == 2){
        arquivoEntrada = fopen(argv[1], "r");
        if(arquivoEntrada == NULL){
            printf("Erro: Arquivo não encontrado.\n");
            return 0;
        }
    }
    else {
        printf("Erro: Numero de argumentos invalidos.\n");
        return 0;
    }
    
    PONTEIRONO arvoreSintatica = parse();

    if(arvoreSintatica == NULL){
        printf("Erro: Arvore sintatica nula.\n");
        return 0;
    }

    mostraArvore(arvoreSintatica, 0);
	printf("\n\n");

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

	//imprime a tabela de simbolos
	imprimirTabela(tabelaHash);

	//libera a memória alocada para a arvore sintatica
	desalocaArvore(arvoreSintatica);

	//libera a memoria alocada para a tabela de simbolos
	apagarTabela(tabelaHash);

    fclose(arquivoEntrada);
    fclose(copiaArquivo);

    return 0;
}
