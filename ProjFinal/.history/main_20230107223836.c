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

char nomeFunc[100] = "global";
int numReg = 1; //Numero do registrador
int indiceVetor = 0; //Indice do vetor de codigo intermediario

void criarCodigoIntermediario(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]);


typedef enum {Vazio, IntConst, String} tipoEndereco;

typedef struct endereco{
    tipoEndereco tipo;
    int val;
    char* nome;
} ENDERECO;

typedef struct instrucao{
    char* op;
    ENDERECO* arg1;
    ENDERECO* arg2;
    ENDERECO* arg3;
} INSTRUCAO;

INSTRUCAO* codigoIntermediario[1000];

ENDERECO* criaEndereco(tipoEndereco tipo, int val, char* nome){
    ENDERECO* endereco = (ENDERECO*) malloc(sizeof(ENDERECO));
    
    if(tipo == IntConst){
        endereco->tipo = IntConst;
        endereco->val = val;
        endereco->nome = NULL;
    }
    else if(tipo == String){
        endereco->tipo = String;
        endereco->val = 0;
        endereco->nome = nome;
    }
    else{
        endereco->tipo = Vazio;
        endereco->val = 0;
        endereco->nome = NULL;
    }

    return endereco;
}

INSTRUCAO* criaInstrucao(char* op){
    INSTRUCAO* instrucao = (INSTRUCAO*) malloc(sizeof(INSTRUCAO));
    instrucao->op = op;
    instrucao->arg1 = NULL;
    instrucao->arg2 = NULL;
    instrucao->arg3 = NULL;
    return instrucao;
}

void desalocaVetor(){
    for(int i = 0; i < 1000 && (codigoIntermediario[i] != NULL); i++){
        if(codigoIntermediario[i]->arg1 != NULL)
            free(codigoIntermediario[i]->arg1);
        if(codigoIntermediario[i]->arg2 != NULL)
            free(codigoIntermediario[i]->arg2);
        if(codigoIntermediario[i]->arg3 != NULL)
            free(codigoIntermediario[i]->arg3);
        
        free(codigoIntermediario[i]);
    }
}

void inicializaVetor(){
    for(int i = 0; i < 1000; i++){
        codigoIntermediario[i] = NULL;
    }
}

void imprimeCodigoIntermediario(){
    for(int i = 0; i < 1000; i++){
        if(codigoIntermediario[i] != NULL){
            printf("%s, ", codigoIntermediario[i]->op);
            if(codigoIntermediario[i]->arg1 != NULL){
                if(codigoIntermediario[i]->arg1->tipo == IntConst){
                    printf("%d, ", codigoIntermediario[i]->arg1->val);
                }
                else if(codigoIntermediario[i]->arg1->tipo == String){
                    printf("%s, ", codigoIntermediario[i]->arg1->nome);
                }
                else{
                    printf("-, ");
                }
            }
            else{
                printf("-, ");
            }
            if(codigoIntermediario[i]->arg2 != NULL){
                if(codigoIntermediario[i]->arg2->tipo == IntConst){
                    printf("%d, ", codigoIntermediario[i]->arg2->val);
                }
                else if(codigoIntermediario[i]->arg2->tipo == String){
                    printf("%s, ", codigoIntermediario[i]->arg2->nome);
                }
                else{
                    printf("-, ");
                }
            }
            else{
                printf("-, ");
            }
            if(codigoIntermediario[i]->arg3 != NULL){
                if(codigoIntermediario[i]->arg3->tipo == IntConst){
                    printf("%d\n", codigoIntermediario[i]->arg3->val);
                }
                else if(codigoIntermediario[i]->arg3->tipo == String){
                    printf("%s\n", codigoIntermediario[i]->arg3->nome);
                }
                else{
                    printf("-\n");
                }
            }
            else{
                printf("-\n");
            }
        }
    }
}

void codIntDeclIF(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]){
    INSTRUCAO* instrucaoOp = NULL;
    INSTRUCAO* instrucaoGoto = NULL;
    INSTRUCAO* instrucaoLabel = NULL;
    INSTRUCAO* instrucaoLabel2 = NULL;
    INSTRUCAO* instrucaoIF = NULL;
    printf("codIntDeclIF");
    PONTEIRONO operacao = arvoreSintatica->filho[0];

    if(strcpy(arvoreSintatica->filho[0]->lexema, "==") == 0){
        instrucaoOp = criaInstrucao("EQ");

        criarCodigoIntermediario(arvoreSintatica->filho[0]->filho[0], tabelaHash);
        instrucaoOp->arg1 = criaEndereco(IntConst, numReg, NULL);
        numReg++;
        
        
        criarCodigoIntermediario(arvoreSintatica->filho[0]->filho[1], tabelaHash);
        instrucaoOp->arg2 = criaEndereco(IntConst, numReg, NULL);
        numReg++;

        instrucaoOp->arg3 = criaEndereco(IntConst, numReg, NULL);
        numReg++;

        codigoIntermediario[indiceVetor] = instrucaoOp;
        indiceVetor++;

    }
    
}

void codIntDeclFunc(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]){
    PONTEIRONO noParam = arvoreSintatica->filho[0];
    INSTRUCAO* func = NULL;
    INSTRUCAO* param = NULL;

    func = criaInstrucao("FUN");
    func->arg1 = criaEndereco(String, 0, arvoreSintatica->lexema);
    func->arg2 = criaEndereco(String, 0, arvoreSintatica->filho[1]->lexema);
    func->arg3 = criaEndereco(Vazio, 0, NULL);
    codigoIntermediario[indiceVetor] = func;
    indiceVetor++;

    if(arvoreSintatica->filho[0]->tipoDeclaracao == ParamVoid){
        criarCodigoIntermediario(arvoreSintatica->filho[1]->filho[0], tabelaHash);
        codigoIntermediario[indiceVetor] = criaInstrucao("END");
        codigoIntermediario[indiceVetor]->arg1 = criaEndereco(String, 0, arvoreSintatica->filho[1]->lexema);
        indiceVetor++;
        return;
    }

    while(noParam != NULL){
        param = criaInstrucao("ARG");
        param->arg1 = criaEndereco(String, 0, noParam->lexema);
        param->arg2 = criaEndereco(String, 0, noParam->filho[0]->lexema);
        param->arg3 = criaEndereco(String, 0, arvoreSintatica->filho[1]->lexema);
        codigoIntermediario[indiceVetor] = param;
        indiceVetor++;
        
        noParam = noParam->irmao;
    }

    noParam = arvoreSintatica->filho[0];
    while(noParam != NULL){
        param = criaInstrucao("LOAD");
        param->arg1 = criaEndereco(IntConst, numReg, NULL);
        numReg++;
        param->arg2 = criaEndereco(String, 0, noParam->filho[0]->lexema);
        param->arg3 = criaEndereco(Vazio, 0, NULL);
        codigoIntermediario[indiceVetor] = param;
        indiceVetor++;

        noParam = noParam->irmao;
    }


    criarCodigoIntermediario(arvoreSintatica->filho[1]->filho[0], tabelaHash);

    codigoIntermediario[indiceVetor] = criaInstrucao("END");
    codigoIntermediario[indiceVetor]->arg1 = criaEndereco(String, 0, arvoreSintatica->filho[1]->lexema);
    indiceVetor++;
}

void coidIntDeclVarDecl(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]){
    INSTRUCAO* var = NULL;
    INSTRUCAO* param = NULL;
    
    var = criaInstrucao("ALLOC");
    var->arg1 = criaEndereco(String, 0, arvoreSintatica->lexema);
    var->arg2 = criaEndereco(String, 0, arvoreSintatica->filho[0]->lexema);
    var->arg3 = criaEndereco(String, 0, "Escopo"); //TODO: Adicionar o nome do escopo
    codigoIntermediario[indiceVetor] = var;
    indiceVetor++;

}

//Funcao que analisa a arvore sintatica e a tabela de simbolos e gera o codigo intermediario de tres enderecos
void criarCodigoIntermediario(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]){
    if(arvoreSintatica == NULL){
        return;
    }

    if(arvoreSintatica->tipo == DECLARACAO){
        if(arvoreSintatica->tipoDeclaracao == FunDeclK){
            codIntDeclFunc(arvoreSintatica, tabelaHash);
        }
        else if(arvoreSintatica->tipoDeclaracao == VarDeclK){
            coidIntDeclVarDecl(arvoreSintatica, tabelaHash);
        }
        else if(arvoreSintatica->tipoDeclaracao == IfK){
            codIntDeclIF(arvoreSintatica, tabelaHash);
        }
    }


    criarCodigoIntermediario(arvoreSintatica->irmao, tabelaHash);

}


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
    
    //Chama a funcao do parser, para iniciar a analise do codigo
    PONTEIRONO arvoreSintatica = parse();

    //Verifica se a arvore sintatica foi criada corretamente
    if(arvoreSintatica == NULL){
        if(arquivoEntrada != stdin)
            fclose(arquivoEntrada);
        fclose(copiaArquivo);
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

    printf("============== Codigo Intermediario ===============\n");
    
    inicializaVetor();
    criarCodigoIntermediario(arvoreSintatica, tabelaHash);
    codigoIntermediario[indiceVetor] = criaInstrucao("HALT");

    imprimeCodigoIntermediario();


	//libera a memória alocada para a arvore sintatica
	desalocaArvore(arvoreSintatica);

	//libera a memoria alocada para a tabela de simbolos
	apagarTabela(tabelaHash);

    desalocaVetor();

    //Fecha os arquivos abertos
    if(arquivoEntrada != stdin)
        fclose(arquivoEntrada);
    
    if(copiaArquivo != NULL)
        fclose(copiaArquivo);

    return 0;
}
