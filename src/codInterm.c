#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"
#include "tabelaSimb.h"
#include "codInterm.h"

INSTRUCAO** codigoIntermediario = NULL;
int numReg = 1; // Numero do registrador
int indiceVetor = 0; // Indice do vetor de codigo intermediario
int numLabel = 0; // Numero do label
int vetorIndice = 0; 

INSTRUCAO* funcLabel = NULL;
char funcName[MAXLEXEMA] = "global"; 

// Cria um novo endereco
ENDERECO* criaEndereco(tipoEndereco tipo, int val, char* nome, int boolReg){
    ENDERECO* endereco = (ENDERECO*) malloc(sizeof(ENDERECO));
    
    if(tipo == IntConst){
        endereco->tipo = IntConst;
        endereco->val = val;
        endereco->boolReg = boolReg;
        endereco->nome = NULL;
    }
    else if(tipo == String){
        endereco->tipo = String;
        endereco->val = 0;
        endereco->nome = strdup(nome);
    }
    else{
        endereco->tipo = Vazio;
        endereco->val = 0;
        endereco->nome = NULL;
    }

    return endereco;
}

//Cria uma nova instrucao
INSTRUCAO* criaInstrucao(char* op){
    INSTRUCAO* instrucao = (INSTRUCAO*) malloc(sizeof(INSTRUCAO));
    instrucao->op = op;
    instrucao->arg1 = NULL;
    instrucao->arg2 = NULL;
    instrucao->arg3 = NULL;
    return instrucao;
}

//Desaloca o vetor de codigo intermediario
void desalocaVetor(){
    for(int i = 0; i < MAX_INSTRUCTION && (codigoIntermediario[i] != NULL); i++){
        if(codigoIntermediario[i]->arg1 != NULL)
            free(codigoIntermediario[i]->arg1);
        if(codigoIntermediario[i]->arg2 != NULL)
            free(codigoIntermediario[i]->arg2);
        if(codigoIntermediario[i]->arg3 != NULL)
            free(codigoIntermediario[i]->arg3);
        free(codigoIntermediario[i]);
    }
    free(codigoIntermediario);
}

//Cria o vetor de codigo intermediario
void inicializaVetor(){
    codigoIntermediario = (INSTRUCAO**) malloc(sizeof(INSTRUCAO*) * MAX_INSTRUCTION); // TODO Change to dinamic allocation
    
    for(int i = 0; i < MAX_INSTRUCTION; i++){
        codigoIntermediario[i] = NULL;
    }

    inicializaReg();
}

//Imprime o vetor de codigo intermediario
void imprimeCodigoIntermediario(){
    fprintf(arquivoSaida_Intermediario, "============== Codigo Intermediario ===============\n");
    for(int i = 0; i < MAX_INSTRUCTION && codigoIntermediario[i] != NULL; i++){
        fprintf(arquivoSaida_Intermediario, "%s, ", codigoIntermediario[i]->op);
        if(codigoIntermediario[i]->arg1 != NULL){
            if(codigoIntermediario[i]->arg1->tipo == IntConst){
                if(codigoIntermediario[i]->arg1->boolReg == 1){
                    fprintf(arquivoSaida_Intermediario, "$t%d, ", codigoIntermediario[i]->arg1->val);
                }
                else if(codigoIntermediario[i]->arg1->boolReg == 2){
                    fprintf(arquivoSaida_Intermediario, "L%d, ", codigoIntermediario[i]->arg1->val);
                }
                else{
                    fprintf(arquivoSaida_Intermediario, "%d, ", codigoIntermediario[i]->arg1->val);
                }
            }
            else if(codigoIntermediario[i]->arg1->tipo == String){
                fprintf(arquivoSaida_Intermediario, "%s, ", codigoIntermediario[i]->arg1->nome);
            }
            else{
                fprintf(arquivoSaida_Intermediario, "-, ");
            }
        }
        else{
            fprintf(arquivoSaida_Intermediario, "-, ");
        }
        if(codigoIntermediario[i]->arg2 != NULL){
            if(codigoIntermediario[i]->arg2->tipo == IntConst){
                if(codigoIntermediario[i]->arg2->boolReg == 1){
                    fprintf(arquivoSaida_Intermediario, "$t%d, ", codigoIntermediario[i]->arg2->val);
                }
                else if(codigoIntermediario[i]->arg2->boolReg == 2){
                    fprintf(arquivoSaida_Intermediario, "L%d, ", codigoIntermediario[i]->arg2->val);
                }
                else{
                    fprintf(arquivoSaida_Intermediario, "%d, ", codigoIntermediario[i]->arg2->val);
                }
            }
            else if(codigoIntermediario[i]->arg2->tipo == String){
                fprintf(arquivoSaida_Intermediario, "%s, ", codigoIntermediario[i]->arg2->nome);
            }
            else{
                fprintf(arquivoSaida_Intermediario, "-, ");
            }
        }
        else{
            fprintf(arquivoSaida_Intermediario, "-, ");
        }
        if(codigoIntermediario[i]->arg3 != NULL){
            if(codigoIntermediario[i]->arg3->tipo == IntConst){
                if(codigoIntermediario[i]->arg3->boolReg == 1)
                    fprintf(arquivoSaida_Intermediario, "$t%d\n", codigoIntermediario[i]->arg3->val);
                else
                    fprintf(arquivoSaida_Intermediario, "%d\n", codigoIntermediario[i]->arg3->val);
            }
            else if(codigoIntermediario[i]->arg3->tipo == String){
                fprintf(arquivoSaida_Intermediario, "%s\n", codigoIntermediario[i]->arg3->nome);
            }
            else{
                fprintf(arquivoSaida_Intermediario, "-\n");
            }
        }
        else{
            fprintf(arquivoSaida_Intermediario, "-\n");
        }
    }
}

void codIntDeclIF(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]){
    INSTRUCAO* instrucaoOp = NULL;
    INSTRUCAO* instrucaoGoto = NULL;
    INSTRUCAO* instrucaoLabel1 = NULL;
    INSTRUCAO* instrucaoLabel2 = NULL;
    INSTRUCAO* instrucaoLabel3 = NULL;
    INSTRUCAO* instrucaoIF = NULL;

    criarCodigoIntermediario(arvoreSintatica->filho[0], tabelaHash, 1);

    /* Cria a instrucao para o IF false */
    instrucaoIF = criaInstrucao("IFF");
    instrucaoIF->arg1 = criaEndereco(IntConst, numReg, NULL, 1);
    instrucaoIF->arg2 = criaEndereco(IntConst, numLabel, NULL, 2);
    instrucaoIF->arg3 = criaEndereco(Vazio, 0, NULL, 0);
    codigoIntermediario[indiceVetor] = instrucaoIF;
    indiceVetor++;

    /* Cria a instrucao para o label */
    instrucaoLabel1 = criaInstrucao("LABEL");
    instrucaoLabel1->arg1 = criaEndereco(IntConst, numLabel, NULL, 2);
    instrucaoLabel1->arg2 = criaEndereco(Vazio, 0, NULL, 0);
    instrucaoLabel1->arg3 = criaEndereco(Vazio, 0, NULL, 0);
    numLabel++;

    instrucaoGoto = criaInstrucao("GOTO");
    instrucaoGoto->arg1 = criaEndereco(IntConst, numLabel, NULL, 2);
    instrucaoGoto->arg2 = criaEndereco(Vazio, 0, NULL, 0);
    instrucaoGoto->arg3 = criaEndereco(Vazio, 0, NULL, 0);

    instrucaoLabel2 = criaInstrucao("LABEL");
    instrucaoLabel2->arg1 = criaEndereco(IntConst, numLabel, NULL, 2);
    instrucaoLabel2->arg2 = criaEndereco(Vazio, 0, NULL, 0);
    instrucaoLabel2->arg3 = criaEndereco(Vazio, 0, NULL, 0);
    
    numLabel++;

    /* Avanca para o filho do IF caso a operacao seja verdadeira */
    criarCodigoIntermediario(arvoreSintatica->filho[1], tabelaHash, 1);

    if(arvoreSintatica->filho[2] != NULL){

        codigoIntermediario[indiceVetor++] = instrucaoGoto;
        codigoIntermediario[indiceVetor++] = instrucaoLabel1;

        /*  Avanca para o filho do ELSE caso a operacao seja falsa (Else) 
            Se nao tiver nenhum Else, ela logo ira dar um return de volta para 
            essa funcao */
        criarCodigoIntermediario(arvoreSintatica->filho[2], tabelaHash, 1);

        codigoIntermediario[indiceVetor++] = instrucaoLabel2;
    }
    else{
        codigoIntermediario[indiceVetor++] = instrucaoLabel1;
    }
}

void codIntDeclFunc(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]){
    PONTEIRONO noParam = arvoreSintatica->filho[0];
    INSTRUCAO* func = NULL;
    INSTRUCAO* param = NULL;

    int numParam = 0;

    strcpy(funcName, arvoreSintatica->filho[1]->lexema);

    func = criaInstrucao("FUN");
    func->arg1 = criaEndereco(String, 0, arvoreSintatica->lexema, 0);
    func->arg2 = criaEndereco(String, 0, arvoreSintatica->filho[1]->lexema, 0);
    //func->arg3 = criaEndereco(Vazio, 0, NULL, 0);
    codigoIntermediario[indiceVetor] = func;
    indiceVetor++;
    
    funcLabel = criaInstrucao("LABEL");
    funcLabel->arg1 = criaEndereco(IntConst, numLabel, NULL, 2);
    funcLabel->arg2 = criaEndereco(Vazio, 0, NULL, 0);
    funcLabel->arg3 = criaEndereco(Vazio, 0, NULL, 0);

    numLabel++;


    if(arvoreSintatica->filho[0]->tipoDeclaracao == ParamVoid){
        criarCodigoIntermediario(arvoreSintatica->filho[1]->filho[0], tabelaHash, 1);

        codigoIntermediario[indiceVetor] = funcLabel;
        indiceVetor++;

        codigoIntermediario[indiceVetor] = criaInstrucao("END");
        codigoIntermediario[indiceVetor]->arg1 = criaEndereco(String, 0, arvoreSintatica->filho[1]->lexema, 0);
        indiceVetor++;

        func->arg3 = criaEndereco(IntConst, numParam, NULL, 0);
        return;
    }

    while(noParam != NULL){
        numParam++;
        param = criaInstrucao("ARG");

        if(noParam->tipoDeclaracao == VarParamK)
            param->arg1 = criaEndereco(String, 0, "INT", 0);
        else 
            param->arg1 = criaEndereco(String, 0, "VET", 0);

        param->arg2 = criaEndereco(String, 0, noParam->filho[0]->lexema, 0);
        param->arg3 = criaEndereco(String, 0, arvoreSintatica->filho[1]->lexema, 0);

        codigoIntermediario[indiceVetor] = param;
        indiceVetor++;
        
        noParam = noParam->irmao;
    }

    func->arg3 = criaEndereco(IntConst, numParam, NULL, numParam);

    noParam = arvoreSintatica->filho[0];
    while(noParam != NULL){
        param = criaInstrucao("LOAD");
        
        //param->arg1 = criaEndereco(IntConst, numReg, NULL, 1);
        
        //Otimizacao: Adicionando variavel no vetor de variaveis de registradores
        /* Primeiro busca se a variavel ja esta no vetor de registradores, se nao estiver, deve ser adicionada
        Caso de algum erro ao adicionar, mostrar um erro */

        numReg = verificacaoRegistradores(noParam->filho[0]->lexema, arvoreSintatica->filho[1]->lexema, 1);
    
        param->arg1 = criaEndereco(IntConst, numReg, NULL, 1);
        param->arg2 = criaEndereco(String, 0, noParam->filho[0]->lexema, 0);
        param->arg3 = criaEndereco(Vazio, 0, NULL, 0);
        codigoIntermediario[indiceVetor] = param;
        indiceVetor++;
        

        noParam = noParam->irmao;
    }

    criarCodigoIntermediario(arvoreSintatica->filho[1]->filho[0], tabelaHash, 1);

    codigoIntermediario[indiceVetor] = funcLabel;
    indiceVetor++;

    codigoIntermediario[indiceVetor] = criaInstrucao("END");
    codigoIntermediario[indiceVetor]->arg1 = criaEndereco(String, 0, arvoreSintatica->filho[1]->lexema, 0);
    indiceVetor++;
}

void codIntDeclVarDecl(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]){
    INSTRUCAO* var = NULL;
    INSTRUCAO* param = NULL;
    
    var = criaInstrucao("ALLOC");
    var->arg1 = criaEndereco(String, 0, arvoreSintatica->filho[0]->lexema, 0);

    PONTEIROITEM itemFunc = buscarItemTabelaId(tabelaHash, arvoreSintatica->filho[0]->lexema);

    if(itemFunc == NULL){
        var->arg2 = criaEndereco(String, 0, "escopo", 0);
    }
    else if(strcmp(itemFunc->escopo, "global") == 0){
        var->arg2 = criaEndereco(String, 0, "global", 0);
    }
    else{
        var->arg2 = criaEndereco(String, 0, funcName, 0);
    }
    
    var->arg3 = criaEndereco(Vazio, 0, NULL, 0);

    if(arvoreSintatica->tipoDeclaracao == VetDeclK){
        var->arg3->tipo = IntConst;
        var->arg3->val = atoi(arvoreSintatica->filho[1]->lexema); 
    }

    codigoIntermediario[indiceVetor] = var;
    indiceVetor++;

}

void codIntDeclReturn(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]){
    INSTRUCAO* ret = NULL;
    INSTRUCAO* GOTO = NULL;

    ret = criaInstrucao("RET");
    if(arvoreSintatica->tipoDeclaracao == ReturnINT){
        criarCodigoIntermediario(arvoreSintatica->filho[0], tabelaHash, 1);
        ret->arg1 = criaEndereco(IntConst, numReg, NULL, 1);
    }
    else{
        ret->arg1 = criaEndereco(Vazio, 0, NULL, 0);
    }
    ret->arg2 = criaEndereco(Vazio, 0, NULL, 0);
    ret->arg3 = criaEndereco(Vazio, 0, NULL, 0);

    codigoIntermediario[indiceVetor] = ret;
    indiceVetor++;

    GOTO = criaInstrucao("GOTO");
    GOTO->arg1 = criaEndereco(IntConst, funcLabel->arg1->val, NULL, 2);
    GOTO->arg2 = criaEndereco(Vazio, 0, NULL, 0);
    GOTO->arg3 = criaEndereco(Vazio, 0, NULL, 0);

    codigoIntermediario[indiceVetor] = GOTO;
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

    criarCodigoIntermediario(arvoreSintatica->filho[0], tabelaHash, 1);
    op->arg1 = criaEndereco(IntConst, numReg, NULL, 1);

    criarCodigoIntermediario(arvoreSintatica->filho[1], tabelaHash, 1);
    op->arg2 = criaEndereco(IntConst, numReg, NULL, 1);

    numReg = verificacaoRegistradores(NULL, NULL, 1);

    op->arg3 = criaEndereco(IntConst, numReg, NULL, 1);

    codigoIntermediario[indiceVetor] = op;
    indiceVetor++;

}

void codIntExpConst(PONTEIRONO arvoreSintativa, PONTEIROITEM tabelaHash[]){
    INSTRUCAO* constante = NULL;

    
    if(strcmp(arvoreSintativa->lexema, "0") == 0){
        numReg = $zero;
        return;
    }

    numReg = verificacaoRegistradores(NULL, NULL, 1);
        
    constante = criaInstrucao("LOADI");
    constante->arg1 = criaEndereco(IntConst, numReg, NULL, 1);
    constante->arg2 = criaEndereco(IntConst, atoi(arvoreSintativa->lexema), NULL, 0);
    constante->arg3 = criaEndereco(Vazio, 0, NULL, 0);

    codigoIntermediario[indiceVetor] = constante;
    indiceVetor++;
}

void codIntExpOpRel(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]){
    INSTRUCAO* instrucaoOp = NULL;
    
    // Verifica a operacao e cria a instrucao correspondente
    if(strcmp(arvoreSintatica->lexema, "==") == 0){
        instrucaoOp = criaInstrucao("EQ");
    }
    else if(strcmp(arvoreSintatica->lexema, "!=") == 0){
        instrucaoOp = criaInstrucao("NEQ");
    }
    else if(strcmp(arvoreSintatica->lexema, ">") == 0){
        instrucaoOp = criaInstrucao("GT");
    }
    else if(strcmp(arvoreSintatica->lexema, "<") == 0){
        instrucaoOp = criaInstrucao("LT");
    }
    else if(strcmp(arvoreSintatica->lexema, ">=") == 0){
        instrucaoOp = criaInstrucao("GET");
    }
    else if(strcmp(arvoreSintatica->lexema, "<=") == 0){
        instrucaoOp = criaInstrucao("LET");
    } 
    
    criarCodigoIntermediario(arvoreSintatica->filho[0], tabelaHash, 1);
    instrucaoOp->arg1 = criaEndereco(IntConst, numReg, NULL, 1);
    
    criarCodigoIntermediario(arvoreSintatica->filho[1], tabelaHash, 1);
    instrucaoOp->arg2 = criaEndereco(IntConst, numReg, NULL, 1);

    numReg = verificacaoRegistradores(NULL, NULL, 1);

    instrucaoOp->arg3 = criaEndereco(IntConst, numReg, NULL, 1);
    // numReg++;

    codigoIntermediario[indiceVetor] = instrucaoOp;
    indiceVetor++;
}

void codIntExpId(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]){
    INSTRUCAO* instrucaoId = NULL;
    
    if(arvoreSintatica->tipoExpressao == VetorK){
        instrucaoId = criaInstrucao("LOAD");

        criarCodigoIntermediario(arvoreSintatica->filho[0], tabelaHash, 1);
        instrucaoId->arg3 = criaEndereco(IntConst, numReg, NULL, 1);
        vetorIndice = numReg;

        numReg = verificacaoRegistradores(NULL, NULL, 1);
        
        instrucaoId->arg1 = criaEndereco(IntConst, numReg, NULL, 1); // Valor do registrador alterado
        instrucaoId->arg2 = criaEndereco(String, 0, arvoreSintatica->lexema, 0);

    }
    else if(arvoreSintatica->tipoExpressao == IdK){  
        //Otimizacao: Adicionando variavel no vetor de variaveis de registradores
        /* Primeiro busca se a variavel ja esta no vetor de registradores, se nao estiver, deve ser adicionada
        Caso de algum erro ao adicionar, mostrar um erro */
        PONTEIROITEM varEscopo = NULL;
        if(!(varEscopo = buscarItemTabelaId(tabelaHash, arvoreSintatica->lexema))){
            printf(ANSI_COLOR_RED "ERRO: " ANSI_COLOR_RESET);
            printf("Escopo da variavel '%s' nao encontrada", arvoreSintatica->lexema);
            numReg = -1;
        }
        if(!strcmp(varEscopo->escopo, "global")){
            numReg = verificacaoRegistradores(arvoreSintatica->lexema, "global", 1);
        }
        else{
            numReg = verificacaoRegistradores(arvoreSintatica->lexema, funcName, 1);
        }
        
        instrucaoId = criaInstrucao("LOAD");
        instrucaoId->arg1 = criaEndereco(IntConst, numReg, NULL, 1);
        instrucaoId->arg2 = criaEndereco(String, 0, arvoreSintatica->lexema, 0);
        instrucaoId->arg3 = criaEndereco(Vazio, 0, NULL, 0);
    }

    if(instrucaoId != NULL){
        codigoIntermediario[indiceVetor] = instrucaoId;
        indiceVetor++;
    }
}

void codIntExpCall(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]){
    INSTRUCAO* instrucaoCall = NULL;
    INSTRUCAO* instrucaoParam = NULL;
    PONTEIRONO noAux = arvoreSintatica->filho[0];   

    int numParam = 0; 

    instrucaoCall = criaInstrucao("CALL");
    instrucaoCall->arg1 = criaEndereco(String, 0, arvoreSintatica->lexema, 0);

    while(noAux !=  NULL){
        instrucaoParam = criaInstrucao("PARAM");
        
        /* 
        1) Buscar na tabela para ver se eh um vetor
        2) Ver se ele tem algum filho
        3) Se for um vetor e nao tiver filhos, ele vai ser passado com o valor da memoria
        */

        PONTEIROITEM itemAux = procuraTabelaQualquer(tabelaHash, noAux->lexema, funcName);
        if(itemAux != NULL && (itemAux->tipoIdentificador == VetDeclK || itemAux->tipoIdentificador == VetParamK) && noAux->filho[0] == NULL){
            numReg = verificacaoRegistradores(NULL, NULL, 1);
            instrucaoParam->arg2 = criaEndereco(String, 0, "VET", 0);
            instrucaoParam->arg3 = criaEndereco(String, 0, noAux->lexema, 0);
        }
        else{
            criarCodigoIntermediario(noAux, tabelaHash, 0);   
            instrucaoParam->arg2 = criaEndereco(String, 0, "INT", 0);
            instrucaoParam->arg3 = criaEndereco(Vazio, 0, NULL, 0);
        }
        instrucaoParam->arg1 = criaEndereco(IntConst, numReg, NULL, 1);       

        codigoIntermediario[indiceVetor] = instrucaoParam;
        indiceVetor++;
        
        noAux = noAux->irmao;

        numParam++;
    }
    
    instrucaoCall->arg2 = criaEndereco(IntConst, numParam, NULL, 0);
    
    PONTEIROITEM itemAux = buscarItemTabelaFunc(tabelaHash, arvoreSintatica->lexema);
    if(itemAux != NULL && itemAux->tipoDado == Type_Void){
        instrucaoCall->arg3 = criaEndereco(Vazio, 0, NULL, 0);
    }
    else if(itemAux != NULL && itemAux->tipoDado == Type_Int){
        numReg = verificacaoRegistradores(NULL, NULL, 1);

        instrucaoCall->arg3 = criaEndereco(IntConst, numReg, NULL, 1);
        // numReg++;
    }

    codigoIntermediario[indiceVetor] = instrucaoCall;
    indiceVetor++;
}

void codIntExpAtrib(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]){
    INSTRUCAO* instrucaoAtrib = NULL;
    INSTRUCAO* instrucaoStore = NULL;

    instrucaoAtrib = criaInstrucao("ASSIGN");


    criarCodigoIntermediario(arvoreSintatica->filho[0], tabelaHash, 1);
    /*if(arvoreSintatica->filho[0]->tipoExpressao == VetorK){
        criarCodigoIntermediario(arvoreSintatica->filho[0]->filho[0], tabelaHash, 1);
    }
    else{
        
    }*/
    
    instrucaoAtrib->arg1 = criaEndereco(IntConst, numReg, NULL, 1);

    instrucaoStore = criaInstrucao("STORE");
    instrucaoStore->arg1 = criaEndereco(String, 0, arvoreSintatica->filho[0]->lexema, 0);
    instrucaoStore->arg2 = criaEndereco(IntConst, instrucaoAtrib->arg1->val, NULL, 1);

    if(arvoreSintatica->filho[0]->tipoExpressao == VetorK){
        instrucaoStore->arg3 = criaEndereco(IntConst, vetorIndice, NULL, 1);
    }
    else{
        instrucaoStore->arg3 = criaEndereco(Vazio, 0, NULL, 0);
    }

    criarCodigoIntermediario(arvoreSintatica->filho[1], tabelaHash, 1);
    
    instrucaoAtrib->arg2 = criaEndereco(IntConst, numReg, NULL, 1);

    codigoIntermediario[indiceVetor] = instrucaoAtrib;
    indiceVetor++;    

    codigoIntermediario[indiceVetor] = instrucaoStore;
    indiceVetor++;
}

void codIntDeclWhile(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]){
    INSTRUCAO* instrucaoIFF = NULL;
    INSTRUCAO* instrucaoGOTO = NULL;
    INSTRUCAO* instrucaoLabel1 = NULL;
    INSTRUCAO* instrucaoLabel2 = NULL;
    
    instrucaoLabel1 = criaInstrucao("LABEL");
    instrucaoLabel1->arg1 = criaEndereco(IntConst, numLabel, NULL, 2);
    instrucaoLabel1->arg2 = criaEndereco(Vazio, 0, NULL, 0);
    instrucaoLabel1->arg3 = criaEndereco(Vazio, 0, NULL, 0);

    codigoIntermediario[indiceVetor] = instrucaoLabel1;
    indiceVetor++;

    instrucaoGOTO = criaInstrucao("GOTO");
    instrucaoGOTO->arg1 = criaEndereco(IntConst, numLabel, NULL, 2);
    instrucaoGOTO->arg2 = criaEndereco(Vazio, 0, NULL, 0);
    instrucaoGOTO->arg3 = criaEndereco(Vazio, 0, NULL, 0);

    numLabel++;

    instrucaoLabel2 = criaInstrucao("LABEL");
    instrucaoLabel2->arg1 = criaEndereco(IntConst, numLabel, NULL, 2);
    instrucaoLabel2->arg2 = criaEndereco(Vazio, 0, NULL, 0);
    instrucaoLabel2->arg3 = criaEndereco(Vazio, 0, NULL, 0);
    numLabel++;

    instrucaoIFF = criaInstrucao("IFF");

    instrucaoIFF->arg2 = criaEndereco(IntConst, numLabel-1, NULL, 2);
    instrucaoIFF->arg3 = criaEndereco(Vazio, 0, NULL, 0);

    criarCodigoIntermediario(arvoreSintatica->filho[0], tabelaHash, 1);

    instrucaoIFF->arg1 = criaEndereco(IntConst, numReg, NULL, 1);

    codigoIntermediario[indiceVetor] = instrucaoIFF;
    indiceVetor++;

    criarCodigoIntermediario(arvoreSintatica->filho[1], tabelaHash, 1);

    codigoIntermediario[indiceVetor] = instrucaoGOTO;
    indiceVetor++;

    codigoIntermediario[indiceVetor] = instrucaoLabel2;
    indiceVetor++;
}


//Funcao que analisa a arvore sintatica e a tabela de simbolos e gera o codigo intermediario de tres enderecos
void criarCodigoIntermediario(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[], int boolean){
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
            codIntDeclWhile(arvoreSintatica, tabelaHash);
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
            codIntExpCall(arvoreSintatica, tabelaHash);
        }
        else if(arvoreSintatica->tipoExpressao == AssignK){
            codIntExpAtrib(arvoreSintatica, tabelaHash);
        }
    }
    
    if(boolean == 1){
        criarCodigoIntermediario(arvoreSintatica->irmao, tabelaHash, 1);
    }
}