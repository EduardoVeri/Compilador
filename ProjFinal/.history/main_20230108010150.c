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
#include <math.h>

char nomeFunc[100] = "global";
int numReg = 1; //Numero do registrador
int indiceVetor = 0; //Indice do vetor de codigo intermediario
int numLabel = 0; //Numero do label


void criarCodigoIntermediario(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]);

//ENUM com os tipos de enderecos
typedef enum {Vazio, IntConst, String} tipoEndereco;

//Estrutura de enderecos
typedef struct endereco{
    tipoEndereco tipo;
    int val;
    char* nome;
} ENDERECO;

//Estrutura de instrucoes
typedef struct instrucao{
    char* op; //Operador
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
    for(int i = 0; i < 1000 && codigoIntermediario[i] != NULL; i++){
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
    INSTRUCAO* instrucaoIF = NULL;

    criarCodigoIntermediario(arvoreSintatica->filho[0], tabelaHash);

    /*TODO: Arrumar o numero dos registradores em variaveis ja salvas*/

    /* Cria a instrucao para o IF false */
    instrucaoIF = criaInstrucao("IFF");
    instrucaoIF->arg1 = criaEndereco(IntConst, numReg - 1, NULL);
    instrucaoIF->arg2 = criaEndereco(IntConst, numLabel, NULL);
    instrucaoIF->arg3 = criaEndereco(Vazio, 0, NULL);
    codigoIntermediario[indiceVetor] = instrucaoIF;
    indiceVetor++;

    /* Cria a instrucao para o label */
    instrucaoLabel = criaInstrucao("LABEL");
    instrucaoLabel->arg1 = criaEndereco(IntConst, numLabel, NULL);
    instrucaoLabel->arg2 = criaEndereco(Vazio, 0, NULL);
    instrucaoLabel->arg3 = criaEndereco(Vazio, 0, NULL);

    numLabel++;

    /* Cria a instrucao para o GOTO */
    instrucaoGoto = criaInstrucao("GOTO");
    instrucaoGoto->arg1 = criaEndereco(IntConst, numLabel, NULL);
    instrucaoGoto->arg2 = criaEndereco(Vazio, 0, NULL);
    instrucaoGoto->arg3 = criaEndereco(Vazio, 0, NULL);

    /* Avanca para o filho do IF caso a operacao seja verdadeira */
    criarCodigoIntermediario(arvoreSintatica->filho[1], tabelaHash);

    codigoIntermediario[indiceVetor] = instrucaoGoto;
    indiceVetor++;

    codigoIntermediario[indiceVetor] = instrucaoLabel;
    indiceVetor++;

    /*  Avanca para o filho do ELSE caso a operacao seja falsa (Else) 
        Se nao tiver nenhum Else, ela logo ira dar um return de volta para 
        essa funcao */
    criarCodigoIntermediario(arvoreSintatica->filho[2], tabelaHash);

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

void codIntDeclVarDecl(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]){
    INSTRUCAO* var = NULL;
    INSTRUCAO* param = NULL;
    
    var = criaInstrucao("ALLOC");
    var->arg1 = criaEndereco(String, 0, arvoreSintatica->filho[0]->lexema);
    var->arg2 = criaEndereco(String, 0, "Escopo"); //TODO: Adicionar o nome do escopo
    var->arg3 = criaEndereco(Vazio, 0, NULL);

    if(arvoreSintatica->tipoDeclaracao == VetDeclK){
        var->arg3->tipo = IntConst;
        var->arg3->val = atoi(arvoreSintatica->filho[1]->lexema); 
    }

    codigoIntermediario[indiceVetor] = var;
    indiceVetor++;

}

void codIntDeclReturn(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]){
    INSTRUCAO* ret = NULL;
    
    ret = criaInstrucao("RET");
    criarCodigoIntermediario(arvoreSintatica->filho[0], tabelaHash);
    ret->arg1 = criaEndereco(IntConst, numReg, NULL);
    numReg++;

    ret->arg2 = criaEndereco(Vazio, 0, NULL);
    ret->arg3 = criaEndereco(Vazio, 0, NULL);

    codigoIntermediario[indiceVetor] = ret;
    indiceVetor++;

}

void codIntExpOp(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]){
    INSTRUCAO* op = NULL;
    char NomeOp[MAXLEXEMA];

    strcpy(NomeOp, arvoreSintatica->lexema);

    if(strcmp(NomeOp, "+") == 0){
        op = criaInstrucao("ADD");
    }
    else if(strcmp(NomeOp, "-") == 0){
        op = criaInstrucao("SUB");
    }
    else if(strcmp(NomeOp, "*") == 0){
        op = criaInstrucao("MULT");
    }
    else if(strcmp(NomeOp, "/") == 0){
        op = criaInstrucao("DIV");
    }

    criarCodigoIntermediario(arvoreSintatica->filho[0], tabelaHash);
    op->arg1 = criaEndereco(IntConst, numReg - 1, NULL);

    criarCodigoIntermediario(arvoreSintatica->filho[1], tabelaHash);
    op->arg2 = criaEndereco(IntConst, numReg - 1, NULL);

    op->arg3 = criaEndereco(IntConst, numReg, NULL);
    numReg++;

    codigoIntermediario[indiceVetor] = op;
    indiceVetor++;

}

void codIntExpConst(PONTEIRONO arvoreSintativa, PONTEIROITEM tabelaHash[]){
    INSTRUCAO* constante = NULL;
    constante = criaInstrucao("LOADI");
    constante->arg1 = criaEndereco(IntConst, numReg, NULL);
    numReg++;
    constante->arg2 = criaEndereco(IntConst, atoi(arvoreSintativa->lexema), NULL);
    constante->arg3 = criaEndereco(Vazio, 0, NULL);

    codigoIntermediario[indiceVetor] = constante;
    indiceVetor++;
}

void codIntExpOpRel(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]){
    INSTRUCAO* instrucaoOp = NULL;
    
    //Verifica a operacao e cria a instrucao correspondente
    if(strcmp(arvoreSintatica->lexema, "==") == 0){
        instrucaoOp = criaInstrucao("EQ");
    }
    else if(strcmp(arvoreSintatica->lexema, "!=") == 0){
        instrucaoOp = criaInstrucao("NE");
    }
    else if(strcmp(arvoreSintatica->lexema, ">") == 0){
        instrucaoOp = criaInstrucao("GT");
    }
    else if(strcmp(arvoreSintatica->lexema, "<") == 0){
        instrucaoOp = criaInstrucao("LT");
    } /*TODO: Adicionar as demais operacoes.*/

    criarCodigoIntermediario(arvoreSintatica->filho[0], tabelaHash);
    instrucaoOp->arg1 = criaEndereco(IntConst, numReg - 1, NULL);
    
    
    criarCodigoIntermediario(arvoreSintatica->filho[1], tabelaHash);
    instrucaoOp->arg2 = criaEndereco(IntConst, numReg - 1, NULL);

    instrucaoOp->arg3 = criaEndereco(IntConst, numReg, NULL);
    numReg++;

    codigoIntermediario[indiceVetor] = instrucaoOp;
    indiceVetor++;
}

void codIntExpId(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]){
    INSTRUCAO* instrucaoId = NULL;
    
    if(arvoreSintatica->tipoExpressao == VetorK){
        instrucaoId = criaInstrucao("LOADVET");
        instrucaoId->arg1 = criaEndereco(IntConst, numReg, NULL);
        numReg++;
        instrucaoId->arg2 = criaEndereco(String, 0, arvoreSintatica->lexema);
        instrucaoId->arg3 = criaEndereco(IntConst, atoi(arvoreSintatica->filho[0]->lexema), NULL);
    }
    else if(arvoreSintatica->tipoExpressao == IdK){
        instrucaoId = criaInstrucao("LOAD");
        instrucaoId->arg1 = criaEndereco(IntConst, numReg, NULL);
        numReg++;
        instrucaoId->arg2 = criaEndereco(String, 0, arvoreSintatica->lexema);
        instrucaoId->arg3 = criaEndereco(Vazio, 0, NULL);
    }

    codigoIntermediario[indiceVetor] = instrucaoId;
    indiceVetor++;
}

PONTEIROITEM buscarItemTabelaFunc(PONTEIROITEM tabelaHash[], char* lexema){
    int indice = longhash(lexema);
    PONTEIROITEM item = tabelaHash[indice];

    while(item != NULL){
        if(item->tipoIdentificador == FunDeclK && (item->nomeIdentificador, lexema) == 0){
            return item;
        }
        item = item->proximo;
    }

    return item;
}

void codIntExpCall(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]){
    INSTRUCAO* instrucaoCall = NULL;
    INSTRUCAO* instrucaoParam = NULL;
    
    int numParam = 0; 

    instrucaoCall = criaInstrucao("CALL");
    instrucaoCall->arg1 = criaEndereco(String, 0, arvoreSintatica->lexema);
    printf("Numero de parametros: %d", numParam);
    PONTEIRONO noAux = arvoreSintatica->filho[0];    
    printf("Numero de parametros: %d", numParam);
    while(noAux !=  NULL){
        criarCodigoIntermediario(noAux, tabelaHash);   
        instrucaoParam = criaInstrucao("PARAM");
        instrucaoParam->arg1 = criaEndereco(IntConst, numReg - 1, NULL);
        instrucaoParam->arg2 = criaEndereco(Vazio, 0, NULL);
        instrucaoParam->arg3 = criaEndereco(Vazio, 0, NULL);

        codigoIntermediario[indiceVetor] = instrucaoParam;
        indiceVetor++;

        noAux = noAux->irmao;

        numParam++;
    }
    
    
    instrucaoCall->arg2 = criaEndereco(IntConst, numParam, NULL);
    
    PONTEIROITEM itemAux = buscarItemTabelaFunc(tabelaHash, arvoreSintatica->lexema);
    if(itemAux->tipoDado == Type_Void){
        instrucaoCall->arg3 = criaEndereco(Vazio, 0, NULL);
    }
    else{
        instrucaoCall->arg3 = criaEndereco(IntConst, numReg, NULL);
        numReg++;
    }
    codigoIntermediario[indiceVetor] = instrucaoCall;
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
        else if(arvoreSintatica->tipoDeclaracao == VarDeclK || arvoreSintatica->tipoDeclaracao == VetDeclK){
            codIntDeclVarDecl(arvoreSintatica, tabelaHash);
        }
        else if(arvoreSintatica->tipoDeclaracao == IfK){
            codIntDeclIF(arvoreSintatica, tabelaHash);
        }
        else if(arvoreSintatica->tipoDeclaracao == WhileK){
         //   codIntDeclWhile(arvoreSintatica, tabelaHash);
        }
        else if(arvoreSintatica->tipoDeclaracao == ReturnINT || arvoreSintatica->tipoDeclaracao == ReturnVOID){
          codIntDeclReturn(arvoreSintatica, tabelaHash);
        }
    }
    else if (arvoreSintatica->tipo == EXPRESSAO){
        if(arvoreSintatica->tipoExpressao == OpK){
            codIntExpOp(arvoreSintatica, tabelaHash);
        }
        else if(arvoreSintatica->tipoExpressao == ConstK){
            codIntExpConst(arvoreSintatica, tabelaHash);
        }
        else if(arvoreSintatica->tipoExpressao == OpRel){
            codIntExpOpRel(arvoreSintatica, tabelaHash);
        }
        else if(arvoreSintatica->tipoExpressao == IdK || arvoreSintatica->tipoExpressao == VetorK){
            codIntExpId(arvoreSintatica, tabelaHash);
        }
        else if(arvoreSintatica->tipoExpressao == AtivK){
            printf("%s\n", arvoreSintatica->lexema);
            codIntExpCall(arvoreSintatica, tabelaHash);
        }
    }

    criarCodigoIntermediario(arvoreSintatica->irmao, tabelaHash);

}


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
    inicializaVetor();
    criarCodigoIntermediario(arvoreSintatica, tabelaHash);
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
