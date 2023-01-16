#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tabelaSimb.h"
#include "global.h"
#include "codInterm.h"

int numReg = 1; //Numero do registrador
int indiceVetor = 0; //Indice do vetor de codigo intermediario
int numLabel = 0; //Numero do label

INSTRUCAO* funcLabel = NULL;
char funcName[MAXLEXEMA] = "global"; 

//Cria um novo endereco
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
        endereco->nome = nome;
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
}

//Cria o vetor de codigo intermediario
INSTRUCAO** inicializaVetor(){
    INSTRUCAO** codigoIntermediario = (INSTRUCAO**) malloc(sizeof(INSTRUCAO*) * MAX_INSTRUCTION);
    
    for(int i = 0; i < MAX_INSTRUCTION; i++){
        codigoIntermediario[i] = NULL;
    }

    return codigoIntermediario;
}

//Imprime o vetor de codigo intermediario
void imprimeCodigoIntermediario(){
    printf("============== Codigo Intermediario ===============\n");
    for(int i = 0; i < MAX_INSTRUCTION && codigoIntermediario[i] != NULL; i++){
        printf("%s, ", codigoIntermediario[i]->op);
        if(codigoIntermediario[i]->arg1 != NULL){
            if(codigoIntermediario[i]->arg1->tipo == IntConst){
                if(codigoIntermediario[i]->arg1->boolReg == 1){
                    printf("$t%d, ", codigoIntermediario[i]->arg1->val);
                }
                else if(codigoIntermediario[i]->arg1->boolReg == 2){
                    printf("L%d, ", codigoIntermediario[i]->arg1->val);
                }
                else{
                    printf("%d, ", codigoIntermediario[i]->arg1->val);
                }
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
                if(codigoIntermediario[i]->arg2->boolReg == 1){
                    printf("$t%d, ", codigoIntermediario[i]->arg2->val);
                }
                else if(codigoIntermediario[i]->arg2->boolReg == 2){
                    printf("L%d, ", codigoIntermediario[i]->arg2->val);
                }
                else{
                    printf("%d, ", codigoIntermediario[i]->arg2->val);
                }
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
                if(codigoIntermediario[i]->arg3->boolReg == 1)
                    printf("$t%d\n", codigoIntermediario[i]->arg3->val);
                else
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


void codIntDeclIF(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]){
    INSTRUCAO* instrucaoOp = NULL;
    INSTRUCAO* instrucaoGoto = NULL;
    INSTRUCAO* instrucaoLabel = NULL;
    INSTRUCAO* instrucaoIF = NULL;

    criarCodigoIntermediario(arvoreSintatica->filho[0], tabelaHash, 1);

    /* Cria a instrucao para o IF false */
    instrucaoIF = criaInstrucao("IFF");
    instrucaoIF->arg1 = criaEndereco(IntConst, numReg - 1, NULL, 1);
    instrucaoIF->arg2 = criaEndereco(IntConst, numLabel, NULL, 2);
    instrucaoIF->arg3 = criaEndereco(Vazio, 0, NULL, 0);
    codigoIntermediario[indiceVetor] = instrucaoIF;
    indiceVetor++;

    /* Cria a instrucao para o label */
    instrucaoLabel = criaInstrucao("LABEL");
    instrucaoLabel->arg1 = criaEndereco(IntConst, numLabel, NULL, 2);
    instrucaoLabel->arg2 = criaEndereco(Vazio, 0, NULL, 0);
    instrucaoLabel->arg3 = criaEndereco(Vazio, 0, NULL, 0);

    numLabel++;

    /* Avanca para o filho do IF caso a operacao seja verdadeira */
    criarCodigoIntermediario(arvoreSintatica->filho[1], tabelaHash, 1);

    codigoIntermediario[indiceVetor] = instrucaoLabel;
    indiceVetor++;

    /*  Avanca para o filho do ELSE caso a operacao seja falsa (Else) 
        Se nao tiver nenhum Else, ela logo ira dar um return de volta para 
        essa funcao */
    criarCodigoIntermediario(arvoreSintatica->filho[2], tabelaHash, 1);

}

void codIntDeclFunc(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]){
    PONTEIRONO noParam = arvoreSintatica->filho[0];
    INSTRUCAO* func = NULL;
    INSTRUCAO* param = NULL;

    strcpy(funcName, arvoreSintatica->filho[1]->lexema);

    func = criaInstrucao("FUN");
    func->arg1 = criaEndereco(String, 0, arvoreSintatica->lexema, 0);
    func->arg2 = criaEndereco(String, 0, arvoreSintatica->filho[1]->lexema, 0);
    func->arg3 = criaEndereco(Vazio, 0, NULL, 0);
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
        return;
    }

    while(noParam != NULL){
        param = criaInstrucao("ARG");
        param->arg1 = criaEndereco(String, 0, noParam->lexema, 0);
        param->arg2 = criaEndereco(String, 0, noParam->filho[0]->lexema, 0);
        param->arg3 = criaEndereco(String, 0, arvoreSintatica->filho[1]->lexema, 0);
        codigoIntermediario[indiceVetor] = param;
        indiceVetor++;
        
        noParam = noParam->irmao;
    }

    noParam = arvoreSintatica->filho[0];
    while(noParam != NULL){
        param = criaInstrucao("LOAD");
        param->arg1 = criaEndereco(IntConst, numReg, NULL, 1);
        numReg++;
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
        var->arg2 = criaEndereco(String, 0, itemFunc->escopo, 0);
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
        ret->arg1 = criaEndereco(IntConst, numReg-1, NULL, 1);
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
    op->arg1 = criaEndereco(IntConst, numReg - 1, NULL, 1);

    criarCodigoIntermediario(arvoreSintatica->filho[1], tabelaHash, 1);
    op->arg2 = criaEndereco(IntConst, numReg - 1, NULL, 1);

    op->arg3 = criaEndereco(IntConst, numReg, NULL, 1);
    numReg++;

    codigoIntermediario[indiceVetor] = op;
    indiceVetor++;

}

void codIntExpConst(PONTEIRONO arvoreSintativa, PONTEIROITEM tabelaHash[]){
    INSTRUCAO* constante = NULL;
    constante = criaInstrucao("LOADI");
    constante->arg1 = criaEndereco(IntConst, numReg, NULL, 1);
    numReg++;
    constante->arg2 = criaEndereco(IntConst, atoi(arvoreSintativa->lexema), NULL, 0);
    constante->arg3 = criaEndereco(Vazio, 0, NULL, 0);

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
    instrucaoOp->arg1 = criaEndereco(IntConst, numReg-1, NULL, 1);
    
    criarCodigoIntermediario(arvoreSintatica->filho[1], tabelaHash, 1);
    instrucaoOp->arg2 = criaEndereco(IntConst, numReg-1, NULL, 1);

    instrucaoOp->arg3 = criaEndereco(IntConst, numReg, NULL, 1);
    numReg++;

    codigoIntermediario[indiceVetor] = instrucaoOp;
    indiceVetor++;
}

void codIntExpId(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]){
    INSTRUCAO* instrucaoId = NULL;
    
    if(arvoreSintatica->tipoExpressao == VetorK){
        instrucaoId = criaInstrucao("LOADVET");
        instrucaoId->arg1 = criaEndereco(IntConst, numReg, NULL, 1);
        numReg++;
        instrucaoId->arg2 = criaEndereco(String, 0, arvoreSintatica->lexema, 0);
        instrucaoId->arg3 = criaEndereco(IntConst, atoi(arvoreSintatica->filho[0]->lexema), NULL, 0);
    }
    else if(arvoreSintatica->tipoExpressao == IdK){
        instrucaoId = criaInstrucao("LOAD");
        instrucaoId->arg1 = criaEndereco(IntConst, numReg, NULL, 1);
        numReg++;
        instrucaoId->arg2 = criaEndereco(String, 0, arvoreSintatica->lexema, 0);
        instrucaoId->arg3 = criaEndereco(Vazio, 0, NULL, 0);
    }

    codigoIntermediario[indiceVetor] = instrucaoId;
    indiceVetor++;
}

void codIntExpCall(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]){
    INSTRUCAO* instrucaoCall = NULL;
    INSTRUCAO* instrucaoParam = NULL;
    PONTEIRONO noAux = arvoreSintatica->filho[0];   

    int numParam = 0; 

    instrucaoCall = criaInstrucao("CALL");
    instrucaoCall->arg1 = criaEndereco(String, 0, arvoreSintatica->lexema, 0);

    while(noAux !=  NULL){
        criarCodigoIntermediario(noAux, tabelaHash, 0);   
        instrucaoParam = criaInstrucao("PARAM");
        instrucaoParam->arg1 = criaEndereco(IntConst, numReg - 1, NULL, 1);
        instrucaoParam->arg2 = criaEndereco(Vazio, 0, NULL, 0);
        instrucaoParam->arg3 = criaEndereco(Vazio, 0, NULL, 0);

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
        instrucaoCall->arg3 = criaEndereco(IntConst, numReg, NULL, 1);
        numReg++;
    }

    codigoIntermediario[indiceVetor] = instrucaoCall;
    indiceVetor++;
}

void codIntExpAtrib(PONTEIRONO arvoreSintatica, PONTEIROITEM tabelaHash[]){
    INSTRUCAO* instrucaoAtrib = NULL;
    INSTRUCAO* instrucaoStore = NULL;

    instrucaoAtrib = criaInstrucao("ASSIGN");

    criarCodigoIntermediario(arvoreSintatica->filho[0], tabelaHash, 1);
    instrucaoAtrib->arg1 = criaEndereco(IntConst, numReg - 1, NULL, 1);

    criarCodigoIntermediario(arvoreSintatica->filho[1], tabelaHash, 1);
    instrucaoAtrib->arg2 = criaEndereco(IntConst, numReg - 1, NULL, 1);

    codigoIntermediario[indiceVetor] = instrucaoAtrib;
    indiceVetor++;

    instrucaoStore = criaInstrucao("STORE");
    instrucaoStore->arg1 = criaEndereco(String, 0, arvoreSintatica->filho[0]->lexema, 0);
    instrucaoStore->arg2 = criaEndereco(IntConst, instrucaoAtrib->arg1->val, NULL, 1);
    instrucaoStore->arg3 = criaEndereco(Vazio, 0, NULL, 0);

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

    instrucaoIFF->arg1 = criaEndereco(IntConst, numReg - 1, NULL, 1);

    codigoIntermediario[indiceVetor] = instrucaoIFF;
    indiceVetor++;

    criarCodigoIntermediario(arvoreSintatica->filho[1], tabelaHash, 0);

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