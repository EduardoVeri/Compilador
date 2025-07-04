#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codInterm.h"
#include "assembly.h"
#include "memoria.h"


MEMORIA vetorMemoria; // Variavel global que guarda a memoria
MEMORIA_FUNCOES *funcaoAtual = NULL; // Ponteiro para a funcao atual

// ======================== Gerar Codigo Assembly ========================

void geraAssembly(INSTRUCAO* instrucao);

void assembly(){
    inicializaAssembly();

    /* Criar uma funcao Jump para a main */
    ASSEMBLY *novaInstrucao = criarNoAssembly(typeJ, "j");
    novaInstrucao->tipoJ->labelImediato = strdup("main");
    instrucoesAssembly[indiceAssembly++] = novaInstrucao;

    for(int i = 0; i < indiceVetor; i++){
        geraAssembly(codigoIntermediario[i]);
    }
}

int opRelacionais(INSTRUCAO* instrucao, ASSEMBLY** novaInstrucao){

    if(strcmp(instrucao->op, "EQ") == 0){
        (*novaInstrucao) = criarNoAssembly(typeR, "xor");
        (*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
        (*novaInstrucao)->tipoR->rs = instrucao->arg1->val;
        (*novaInstrucao)->tipoR->rt = instrucao->arg2->val;

        instrucoesAssembly[indiceAssembly++] = *novaInstrucao;

        (*novaInstrucao) = criarNoAssembly(typeI, "slti");
        (*novaInstrucao)->tipoI->rt = instrucao->arg3->val;
        (*novaInstrucao)->tipoI->rs = instrucao->arg3->val;
        (*novaInstrucao)->tipoI->imediato = 1;
    }
    else if(strcmp(instrucao->op, "LT") == 0){
        (*novaInstrucao) = criarNoAssembly(typeR, "slt");
        (*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
        (*novaInstrucao)->tipoR->rs = instrucao->arg1->val;
        (*novaInstrucao)->tipoR->rt = instrucao->arg2->val;
    }
    else if(strcmp(instrucao->op, "NEQ") == 0){
        (*novaInstrucao) = criarNoAssembly(typeR, "slt");
        (*novaInstrucao)->tipoR->rd = $temp;
        (*novaInstrucao)->tipoR->rs = instrucao->arg1->val;
        (*novaInstrucao)->tipoR->rt = instrucao->arg2->val;

        instrucoesAssembly[indiceAssembly++] = *novaInstrucao;

        (*novaInstrucao) = criarNoAssembly(typeR, "slt");
        (*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
        (*novaInstrucao)->tipoR->rs = instrucao->arg2->val;
        (*novaInstrucao)->tipoR->rt = instrucao->arg1->val;

        instrucoesAssembly[indiceAssembly++] = *novaInstrucao;

        (*novaInstrucao) = criarNoAssembly(typeR, "or");
        (*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
        (*novaInstrucao)->tipoR->rs = $temp;
        (*novaInstrucao)->tipoR->rt = instrucao->arg3->val;
        

    }
    else if(strcmp(instrucao->op, "GT") == 0){
        (*novaInstrucao) = criarNoAssembly(typeR, "slt");
        (*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
        (*novaInstrucao)->tipoR->rs = instrucao->arg2->val;
        (*novaInstrucao)->tipoR->rt = instrucao->arg1->val;
    }
    else if(strcmp(instrucao->op, "GET") == 0){
        (*novaInstrucao) = criarNoAssembly(typeR, "slt");
        (*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
        (*novaInstrucao)->tipoR->rs = instrucao->arg1->val;
        (*novaInstrucao)->tipoR->rt = instrucao->arg2->val;

        instrucoesAssembly[indiceAssembly++] = *novaInstrucao;

        int rd = (*novaInstrucao)->tipoR->rd;

        (*novaInstrucao) = criarNoAssembly(typeI, "xori");
        (*novaInstrucao)->tipoI->rt = rd;
        (*novaInstrucao)->tipoI->rs = rd;
        (*novaInstrucao)->tipoI->imediato = 1;
    }
    else if(strcmp(instrucao->op, "LET") == 0){
        (*novaInstrucao) = criarNoAssembly(typeR, "slt");
        (*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
        (*novaInstrucao)->tipoR->rs = instrucao->arg2->val;
        (*novaInstrucao)->tipoR->rt = instrucao->arg1->val;

        instrucoesAssembly[indiceAssembly++] = *novaInstrucao;

        int rd = (*novaInstrucao)->tipoR->rd;

        (*novaInstrucao) = criarNoAssembly(typeI, "xori");
        (*novaInstrucao)->tipoI->rt = rd;
        (*novaInstrucao)->tipoI->rs = rd;
        (*novaInstrucao)->tipoI->imediato = 1;
    }
    else{
        return 0;
    }

    return 1;

}

int opAritmeticos(INSTRUCAO* instrucao, ASSEMBLY** novaInstrucao){
    
    if(strcmp(instrucao->op, "ADD") == 0){
        *novaInstrucao = criarNoAssembly(typeR, "add");
        (*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
        (*novaInstrucao)->tipoR->rs = instrucao->arg1->val;
        (*novaInstrucao)->tipoR->rt = instrucao->arg2->val;
    }
    else if(strcmp(instrucao->op, "SUB") == 0){
        (*novaInstrucao) = criarNoAssembly(typeR, "sub");
        (*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
        (*novaInstrucao)->tipoR->rs = instrucao->arg1->val;
        (*novaInstrucao)->tipoR->rt = instrucao->arg2->val;
    }
    else if(strcmp(instrucao->op, "MULT") == 0){
        (*novaInstrucao) = criarNoAssembly(typeR, "mult");
        (*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
        (*novaInstrucao)->tipoR->rs = instrucao->arg1->val;
        (*novaInstrucao)->tipoR->rt = instrucao->arg2->val;
    }
    else if(strcmp(instrucao->op, "DIV") == 0){
        (*novaInstrucao) = criarNoAssembly(typeR, "div");
        (*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
        (*novaInstrucao)->tipoR->rs = instrucao->arg1->val;
        (*novaInstrucao)->tipoR->rt = instrucao->arg2->val;
    }
    else if(strcmp(instrucao->op, "AND") == 0){
        (*novaInstrucao) = criarNoAssembly(typeR, "and");
        (*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
        (*novaInstrucao)->tipoR->rs = instrucao->arg1->val;
        (*novaInstrucao)->tipoR->rt = instrucao->arg2->val;
    }
    else if(strcmp(instrucao->op, "OR") == 0){
        (*novaInstrucao) = criarNoAssembly(typeR, "or");
        (*novaInstrucao)->tipoR->rd = instrucao->arg3->val;
        (*novaInstrucao)->tipoR->rs = instrucao->arg1->val;
        (*novaInstrucao)->tipoR->rt = instrucao->arg2->val;
    }
    else{
        return 0;
    }
    return 1;
}


void geraAssembly(INSTRUCAO* instrucao){
    ASSEMBLY* novaInstrucao = NULL;

    if(opAritmeticos(instrucao, &novaInstrucao)){
        instrucoesAssembly[indiceAssembly++] = novaInstrucao;
    }
    else if(opRelacionais(instrucao, &novaInstrucao)){
        instrucoesAssembly[indiceAssembly++] = novaInstrucao;
    }
    else if(!strcmp(instrucao->op, "ASSIGN")){
        novaInstrucao = criarNoAssembly(typeR, "add");
        novaInstrucao->tipoR->rd = instrucao->arg1->val;
        novaInstrucao->tipoR->rs = $zero;
        novaInstrucao->tipoR->rt = instrucao->arg2->val;
        instrucoesAssembly[indiceAssembly++] = novaInstrucao;
    }
    else if(!strcmp(instrucao->op, "LOADI")){
        int aux_register = $zero;
        
        if (instrucao->arg2->val > 0xFFFF) {
            // Se o valor for maior que 16bits, precisamos adicionar o valor
            // em dois passos: primeiro o valor alto, depois o valor baixo.
            // Usar um ori para carregar primeiramente o valor alto, shiftar os bits
            // e depois adicionar o valor baixo
            
            aux_register = instrucao->arg1->val; // Guardar o registrador de destino
            
            novaInstrucao = criarNoAssembly(typeI, "ori");
            novaInstrucao->tipoI->rt = instrucao->arg1->val; 
            novaInstrucao->tipoI->rs = $zero; 
            novaInstrucao->tipoI->imediato = (instrucao->arg2->val >> 16) & 0xFFFF; // Pega os 16 bits mais altos
            instrucoesAssembly[indiceAssembly++] = novaInstrucao;

            novaInstrucao = criarNoAssembly(typeR, "sll");
            novaInstrucao->tipoR->rd = instrucao->arg1->val; 
            novaInstrucao->tipoR->rs = instrucao->arg1->val; 
            novaInstrucao->tipoR->rt = $zero; // Qualquer registrador
            novaInstrucao->tipoR->shamt = 16; // Shiftar 16 bits
            instrucoesAssembly[indiceAssembly++] = novaInstrucao;

        }

        novaInstrucao = criarNoAssembly(typeI, "ori");
        novaInstrucao->tipoI->rt = instrucao->arg1->val;
        novaInstrucao->tipoI->rs = aux_register;
        novaInstrucao->tipoI->imediato = instrucao->arg2->val;
        instrucoesAssembly[indiceAssembly++] = novaInstrucao;

    }
    else if(!strcmp(instrucao->op, "ALLOC")){
        MEMORIA_FUNCOES* funcao = buscar_funcao(&vetorMemoria, instrucao->arg2->nome);
        int count = 0;

        if(!instrucao->arg3){
            printf(ANSI_COLOR_RED "Erro: " ANSI_COLOR_RESET);
            printf("NULL no argumento 3\n");
            return;
        }
        
        if(instrucao->arg3->tipo == Vazio){
            insere_variavel(funcao, instrucao->arg1->nome, inteiro);
            count = 1;
        }
        else{
            for(int i = 0; i < instrucao->arg3->val; i++){
                insere_variavel(funcao, instrucao->arg1->nome, vetor);	
            }
            count = instrucao->arg3->val;
        }

        if (strcmp(funcaoAtual->nome, "main") == 0) {
            novaInstrucao = criarNoAssembly(typeI, "addi");
            novaInstrucao->tipoI->rt = $sp;
            novaInstrucao->tipoI->rs = $sp;
            novaInstrucao->tipoI->imediato = instrucao->arg3->tipo == Vazio ? 1 : instrucao->arg3->val;
            instrucoesAssembly[indiceAssembly++] = novaInstrucao;
        }

    }
    else if(!strcmp(instrucao->op, "ARG")){
        MEMORIA_FUNCOES* funcao = buscar_funcao(&vetorMemoria, instrucao->arg3->nome);
        
        if(!strcmp(instrucao->arg1->nome, "INT")) 
            insere_variavel(funcao, instrucao->arg2->nome, inteiroArg);
        else insere_variavel(funcao, instrucao->arg2->nome, vetorArg);

        if (strcmp(funcaoAtual->nome, "main") == 0) {
            novaInstrucao = criarNoAssembly(typeI, "addi");
            novaInstrucao->tipoI->rt = $sp;
            novaInstrucao->tipoI->rs = $sp;
            novaInstrucao->tipoI->imediato = 1;
            instrucoesAssembly[indiceAssembly++] = novaInstrucao;
        }
        
    }	
    else if(!strcmp(instrucao->op, "IFF")){
        novaInstrucao = criarNoAssembly(typeI, "beq");
        novaInstrucao->tipoI->rs = $zero;
        novaInstrucao->tipoI->rt = instrucao->arg1->val;
        novaInstrucao->tipoI->label = instrucao->arg2->val;


        instrucoesAssembly[indiceAssembly++] = novaInstrucao;
    }
    else if(!strcmp(instrucao->op, "LABEL")){
        char* auxLabel = (char*) malloc(sizeof(char) * 12);
        sprintf(auxLabel, "Label %d", instrucao->arg1->val);
        novaInstrucao = criarNoAssembly(typeLabel, auxLabel); 
        novaInstrucao->tipoLabel->endereco = instrucao->arg1->val;
        novaInstrucao->tipoLabel->boolean = 1;

        char label[26];
        sprintf(label, "Label %d", instrucao->arg1->val);
        adicionarLabel(label, indiceAssembly);

        instrucoesAssembly[indiceAssembly++] = novaInstrucao;

    }
    else if(!strcmp(instrucao->op, "FUN")){
        novaInstrucao = criarNoAssembly(typeLabel, instrucao->arg2->nome); 
        novaInstrucao->tipoLabel->boolean = 0;

        adicionarLabel(instrucao->arg2->nome, indiceAssembly);
        instrucoesAssembly[indiceAssembly++] = novaInstrucao;

        funcaoAtual = insere_funcao(&vetorMemoria, instrucao->arg2->nome);
    
        if(!strcmp(instrucao->arg2->nome, "main")){
            /* Carrega os registradores $fp e $sp com seus valores iniciais */
            novaInstrucao = criarNoAssembly(typeI, "ori");
            novaInstrucao->tipoI->rt = $fp;
            novaInstrucao->tipoI->rs = $zero; // TODO: Verificar se eh isso mesmo
            novaInstrucao->tipoI->imediato = buscar_funcao(&vetorMemoria, "global")->tamanho + get_fp(funcaoAtual);
            instrucoesAssembly[indiceAssembly++] = novaInstrucao;
            //printf("fp: %d\n", novaInstrucao->tipoI->imediato);

            novaInstrucao = criarNoAssembly(typeR, "add");
            novaInstrucao->tipoR->rd = $fp;
            novaInstrucao->tipoR->rs = $fp;
            novaInstrucao->tipoR->rt = $s0;
            instrucoesAssembly[indiceAssembly++] = novaInstrucao;

            novaInstrucao = criarNoAssembly(typeI, "ori");
            novaInstrucao->tipoI->rt = $sp;
            novaInstrucao->tipoI->rs = $zero;
            novaInstrucao->tipoI->imediato = buscar_funcao(&vetorMemoria, "global")->tamanho + get_sp(funcaoAtual);
            instrucoesAssembly[indiceAssembly++] = novaInstrucao;
            //printf("sp: %d\n", novaInstrucao->tipoI->imediato);

            novaInstrucao = criarNoAssembly(typeR, "add");
            novaInstrucao->tipoR->rd = $sp;
            novaInstrucao->tipoR->rs = $sp;
            novaInstrucao->tipoR->rt = $s0;
            instrucoesAssembly[indiceAssembly++] = novaInstrucao;

            // Inicia o ponteiro de memoria para os parametros
            // novaInstrucao = criarNoAssembly(typeR, "add");
            // novaInstrucao->tipoR->rd = $pilha;
            // novaInstrucao->tipoR->rs = $zero;
            // novaInstrucao->tipoR->rt = $s0; // Valor fixo para a localizacao dos parametros
            // instrucoesAssembly[indiceAssembly++] = novaInstrucao;

            novaInstrucao = criarNoAssembly(typeI, "addi");
            novaInstrucao->tipoI->rt = $pilha;
            novaInstrucao->tipoI->rs = $zero;
            novaInstrucao->tipoI->imediato = 4000;
            instrucoesAssembly[indiceAssembly++] = novaInstrucao;
        }
        else{
            // Guarda o valor de controle para a funcao anterior
            novaInstrucao = criarNoAssembly(typeI, "sw");
            novaInstrucao->tipoI->rt = $ra;
            novaInstrucao->tipoI->rs = $fp;
            novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, get_variavel(funcaoAtual, "Endereco Retorno")) + instrucao->arg3->val;
            instrucoesAssembly[indiceAssembly++] = novaInstrucao;
        }
    }
    else if(!strcmp(instrucao->op, "RET")){
        if(!strcmp(funcaoAtual->nome, "main")) return;
        
        // Acessa o valor de controle da funcao anterior
        novaInstrucao = criarNoAssembly(typeI, "lw");
        novaInstrucao->tipoI->rt = $temp;
        novaInstrucao->tipoI->rs = $fp;
        novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, get_variavel(funcaoAtual, "Vinculo Controle"));
        instrucoesAssembly[indiceAssembly++] = novaInstrucao;

        // Salva o valor do retorno no frame da funcao anterior
        novaInstrucao = criarNoAssembly(typeI, "sw");
        novaInstrucao->tipoI->rs = $temp;
        novaInstrucao->tipoI->rt = instrucao->arg1->val;
        novaInstrucao->tipoI->imediato = 2; // 2 para avancar para "Valor de Retorno"
        instrucoesAssembly[indiceAssembly++] = novaInstrucao;

    }
    else if(!strcmp(instrucao->op, "PARAM")){
        
        if(!strcmp(instrucao->arg2->nome, "VET")){

            VARIAVEL* var = get_variavel(funcaoAtual, instrucao->arg3->nome);

            if(var->tipo == vetorArg){
                novaInstrucao = criarNoAssembly(typeI, "lw");
                novaInstrucao->tipoI->rt = instrucao->arg1->val;
                novaInstrucao->tipoI->rs = (var->bool_global) ? $s0 : $fp; // Mas teoricamnete ele eh so $fp <- Mante so para ter certeza
                novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, var);
                instrucoesAssembly[indiceAssembly++] = novaInstrucao;

                novaInstrucao = criarNoAssembly(typeI, "sw");
                novaInstrucao->tipoI->rs = $pilha;
                novaInstrucao->tipoI->rt = instrucao->arg1->val;
                novaInstrucao->tipoI->imediato = buscar_funcao(&vetorMemoria, "parametros")->tamanho;
                instrucoesAssembly[indiceAssembly++] = novaInstrucao;
            }
            else{
                novaInstrucao = criarNoAssembly(typeI, "addi");
                novaInstrucao->tipoI->rt = instrucao->arg1->val;
                novaInstrucao->tipoI->rs = (var->bool_global) ? $s0 : $fp;
                novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, var);
                instrucoesAssembly[indiceAssembly++] = novaInstrucao;

                novaInstrucao = criarNoAssembly(typeI, "sw");
                novaInstrucao->tipoI->rs = $pilha;
                novaInstrucao->tipoI->rt = instrucao->arg1->val;
                novaInstrucao->tipoI->imediato = buscar_funcao(&vetorMemoria, "parametros")->tamanho;
                instrucoesAssembly[indiceAssembly++] = novaInstrucao;
            }

        }
        else{
            novaInstrucao = criarNoAssembly(typeI, "sw");
            novaInstrucao->tipoI->rs = $pilha;
            novaInstrucao->tipoI->rt = instrucao->arg1->val;
            novaInstrucao->tipoI->imediato = buscar_funcao(&vetorMemoria, "parametros")->tamanho;
            instrucoesAssembly[indiceAssembly++] = novaInstrucao;
        }

        insere_variavel(buscar_funcao(&vetorMemoria, "parametros"), "Param", inteiro);
        
    } 
    else if(!strcmp(instrucao->op, "LOAD")){
        if(!instrucao->arg3){
            printf(ANSI_COLOR_RED "Erro: " ANSI_COLOR_RESET);
            printf("NULL no argumento 3\n");
            return;
        }

        VARIAVEL* var = get_variavel(funcaoAtual, instrucao->arg2->nome);

        if(instrucao->arg3->tipo != Vazio){
            // Load de um indice de um vetor

            if(var->tipo == vetor){
                // Vetor alocado no escopo dessa funcao
                novaInstrucao = criarNoAssembly(typeI, "addi");
                novaInstrucao->tipoI->rt = $temp;
                novaInstrucao->tipoI->rs = (var->bool_global) ? $s0 : $fp;
                novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, var);
                instrucoesAssembly[indiceAssembly++] = novaInstrucao;

                novaInstrucao = criarNoAssembly(typeR, "add");
                novaInstrucao->tipoR->rd = $temp;
                novaInstrucao->tipoR->rs = $temp;
                novaInstrucao->tipoR->rt = instrucao->arg3->val;
                instrucoesAssembly[indiceAssembly++] = novaInstrucao;

                novaInstrucao = criarNoAssembly(typeI, "lw");
                novaInstrucao->tipoI->rt = instrucao->arg1->val;
                novaInstrucao->tipoI->rs = $temp;
                novaInstrucao->tipoI->imediato = 0;
                instrucoesAssembly[indiceAssembly++] = novaInstrucao;
            } /* Continua ... */
            else{
                // Vetor passado como parametro
                novaInstrucao = criarNoAssembly(typeI, "lw");
                novaInstrucao->tipoI->rt = $temp;
                novaInstrucao->tipoI->rs = (var->bool_global) ? $s0 : $fp;
                novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, var);
                instrucoesAssembly[indiceAssembly++] = novaInstrucao;

                novaInstrucao = criarNoAssembly(typeR, "add");
                novaInstrucao->tipoR->rd = $temp;
                novaInstrucao->tipoR->rs = $temp;
                novaInstrucao->tipoR->rt = instrucao->arg3->val;
                instrucoesAssembly[indiceAssembly++] = novaInstrucao;

                novaInstrucao = criarNoAssembly(typeI, "lw");
                novaInstrucao->tipoI->rt = instrucao->arg1->val;
                novaInstrucao->tipoI->rs = $temp;
                novaInstrucao->tipoI->imediato = 0;
                instrucoesAssembly[indiceAssembly++] = novaInstrucao;
            }

        }
        else{
            // Load de um inteiro
            novaInstrucao = criarNoAssembly(typeI, "lw");
            novaInstrucao->tipoI->rt = instrucao->arg1->val;
            novaInstrucao->tipoI->rs = (var->bool_global) ? $s0 : $fp;
            novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, var);
            instrucoesAssembly[indiceAssembly++] = novaInstrucao;
        }
    }
    else if(!strcmp(instrucao->op, "STORE")){
        if(!instrucao->arg3){
            printf(ANSI_COLOR_RED "Erro: " ANSI_COLOR_RESET);
            printf("NULL no argumento 3\n");
            return;
        }
        
        VARIAVEL* var = get_variavel(funcaoAtual, instrucao->arg1->nome);

        if(instrucao->arg3->tipo != Vazio){
            // Store de um valor em um vetor

            if(var->tipo == vetor){
                novaInstrucao = criarNoAssembly(typeI, "addi");
                novaInstrucao->tipoI->rt = $temp;
                novaInstrucao->tipoI->rs = (var->bool_global) ? $s0 : $fp;
                novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, var);
                instrucoesAssembly[indiceAssembly++] = novaInstrucao;

                novaInstrucao = criarNoAssembly(typeR, "add");
                novaInstrucao->tipoR->rd = $temp;
                novaInstrucao->tipoR->rs = $temp;
                novaInstrucao->tipoR->rt = instrucao->arg3->val;
                instrucoesAssembly[indiceAssembly++] = novaInstrucao;

                novaInstrucao = criarNoAssembly(typeI, "sw");
                novaInstrucao->tipoI->rt = instrucao->arg2->val;
                novaInstrucao->tipoI->rs = $temp;
                novaInstrucao->tipoI->imediato = 0;
                instrucoesAssembly[indiceAssembly++] = novaInstrucao;
            }
            else{
                novaInstrucao = criarNoAssembly(typeI, "lw");
                novaInstrucao->tipoI->rt = $temp;
                novaInstrucao->tipoI->rs = (var->bool_global) ? $s0 : $fp; // Provavelmente nao vai ser preciso verificar aqui
                novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, var);
                instrucoesAssembly[indiceAssembly++] = novaInstrucao;

                novaInstrucao = criarNoAssembly(typeR, "add");
                novaInstrucao->tipoR->rd = $temp;
                novaInstrucao->tipoR->rs = $temp;
                novaInstrucao->tipoR->rt = instrucao->arg3->val;
                instrucoesAssembly[indiceAssembly++] = novaInstrucao;

                novaInstrucao = criarNoAssembly(typeI, "sw");
                novaInstrucao->tipoI->rt = instrucao->arg2->val;
                novaInstrucao->tipoI->rs = $temp;
                novaInstrucao->tipoI->imediato = 0;
                instrucoesAssembly[indiceAssembly++] = novaInstrucao;
            }
        }
        else{
            novaInstrucao = criarNoAssembly(typeI, "sw");
            novaInstrucao->tipoI->rt = instrucao->arg2->val;
            novaInstrucao->tipoI->rs = (var->bool_global) ? $s0 : $fp;
            novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, var);
            instrucoesAssembly[indiceAssembly++] = novaInstrucao;
        }
    }
    else if(!strcmp(instrucao->op, "GOTO")){
        novaInstrucao = criarNoAssembly(typeJ, "j");
        novaInstrucao->tipoJ->labelImediato = strdup("Label ########");
        sprintf(novaInstrucao->tipoJ->labelImediato, "Label %d", instrucao->arg1->val);
        instrucoesAssembly[indiceAssembly++] = novaInstrucao;
    }
    else if(!strcmp(instrucao->op, "HALT")){
        novaInstrucao = criarNoAssembly(typeJ, "halt");
        novaInstrucao->tipoJ->labelImediato = strdup("$zero");
        instrucoesAssembly[indiceAssembly++] = novaInstrucao;
    }
    else if(!strcmp(instrucao->op, "CALL")){
        if(!instrucao->arg3){
            printf(ANSI_COLOR_RED "Erro: " ANSI_COLOR_RESET);
            printf("NULL no argumento 3\n");
            return;
        }
                
        if(!strcmp(instrucao->arg1->nome, "output")){
            
            apagar_temp(buscar_funcao(&vetorMemoria, "parametros")); // Apaga os temporarios usados na chamada

            novaInstrucao = criarNoAssembly(typeI, "lw");
            novaInstrucao->tipoI->rt = $temp;
            novaInstrucao->tipoI->rs = $pilha;
            novaInstrucao->tipoI->imediato = buscar_funcao(&vetorMemoria, "parametros")->tamanho;
            instrucoesAssembly[indiceAssembly++] = novaInstrucao;

            // Mostra o valor do $temp para o usuario
            novaInstrucao = criarNoAssembly(typeI, "out");
            novaInstrucao->tipoI->rs = $temp;
            novaInstrucao->tipoI->rt = $zero;
            novaInstrucao->tipoI->imediato = 0;
            instrucoesAssembly[indiceAssembly++] = novaInstrucao;

            return; // Nao precisa fazer mais nada
        }
        if(!strcmp(instrucao->arg1->nome, "drawpixel")){
            
            apagar_temp(buscar_funcao(&vetorMemoria, "parametros")); // Apaga os temporarios usados na chamada

            novaInstrucao = criarNoAssembly(typeI, "lw");
            novaInstrucao->tipoI->rt = $temp2;
            novaInstrucao->tipoI->rs = $pilha;
            novaInstrucao->tipoI->imediato = buscar_funcao(&vetorMemoria, "parametros")->tamanho;
            instrucoesAssembly[indiceAssembly++] = novaInstrucao;
            
            apagar_temp(buscar_funcao(&vetorMemoria, "parametros")); // Apaga os temporarios usados na chamada
            
            novaInstrucao = criarNoAssembly(typeI, "lw");
            novaInstrucao->tipoI->rt = $temp;
            novaInstrucao->tipoI->rs = $pilha;
            novaInstrucao->tipoI->imediato = buscar_funcao(&vetorMemoria, "parametros")->tamanho;
            instrucoesAssembly[indiceAssembly++] = novaInstrucao;

            // Mostra o valor do $temp para o usuario
            novaInstrucao = criarNoAssembly(typeI, "drawpixel");
            novaInstrucao->tipoI->rt = $temp2;
            novaInstrucao->tipoI->rs = $temp;
            novaInstrucao->tipoI->imediato = 0;
            instrucoesAssembly[indiceAssembly++] = novaInstrucao;

            return; // Nao precisa fazer mais nada
        }
        else if(!strcmp(instrucao->arg1->nome, "input")){
            // Como essa funcao nao tem param, basta colocar o input no registrador
            novaInstrucao = criarNoAssembly(typeI, "in");
            novaInstrucao->tipoI->rt = instrucao->arg3->val;
            novaInstrucao->tipoI->rs = $zero;
            novaInstrucao->tipoI->imediato = 0;
            instrucoesAssembly[indiceAssembly++] = novaInstrucao;
            return; // Nao precisa fazer mais nada
        }
        else if (!strcmp(instrucao->arg1->nome, "keyboardinput")){
            novaInstrucao = criarNoAssembly(typeI, "inkey");
            novaInstrucao->tipoI->rt = instrucao->arg3->val;
            novaInstrucao->tipoI->rs = $zero;
            novaInstrucao->tipoI->imediato = 0;
            instrucoesAssembly[indiceAssembly++] = novaInstrucao;

            return; // Nao precisa fazer mais nada
        }

        /* Continua */

        for(int i = instrucao->arg2->val; i > 0; i--) {
            // Salva o valor do param no $temp para ser usado no output			
            apagar_temp(buscar_funcao(&vetorMemoria, "parametros")); // Apaga os temporarios usados na chamada

            novaInstrucao = criarNoAssembly(typeI, "lw");
            novaInstrucao->tipoI->rt = $temp;
            novaInstrucao->tipoI->rs = $pilha;
            novaInstrucao->tipoI->imediato = buscar_funcao(&vetorMemoria, "parametros")->tamanho;
            instrucoesAssembly[indiceAssembly++] = novaInstrucao;

            /*
            novaInstrucao = criarNoAssembly(typeI, "out");
            novaInstrucao->tipoI->rs = $temp;
            novaInstrucao->tipoI->rt = $zero;
            novaInstrucao->tipoI->imediato = 0;
            instrucoesAssembly[indiceAssembly++] = novaInstrucao; */

            novaInstrucao = criarNoAssembly(typeI, "sw");
            novaInstrucao->tipoI->rs = $sp;
            novaInstrucao->tipoI->rt = $temp;
            novaInstrucao->tipoI->imediato = i;
            instrucoesAssembly[indiceAssembly++] = novaInstrucao;
        }

        // Armazena o valor de $fp dessa funcao em $temp para poder ser armazenado no novo frame
        novaInstrucao = criarNoAssembly(typeR, "add");
        novaInstrucao->tipoR->rt = $zero;
        novaInstrucao->tipoR->rs = $fp;
        novaInstrucao->tipoR->rd = $temp;
        instrucoesAssembly[indiceAssembly++] = novaInstrucao;

        // Faz com que $temp aponte para "Vinculo Controle" para poder ser armazenado no novo frame
        novaInstrucao = criarNoAssembly(typeI, "addi");
        novaInstrucao->tipoI->rt = $temp;
        novaInstrucao->tipoI->rs = $temp;
        novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, get_variavel(funcaoAtual, "Vinculo Controle"));
        instrucoesAssembly[indiceAssembly++] = novaInstrucao;

        // Armazena o valor de controle no seu respectivo local no novo frame
        novaInstrucao = criarNoAssembly(typeI, "sw");
        novaInstrucao->tipoI->rt = $temp;
        novaInstrucao->tipoI->rs = $sp;
        novaInstrucao->tipoI->imediato = instrucao->arg2->val + 1;
        instrucoesAssembly[indiceAssembly++] = novaInstrucao;

        // Incrementa o valor de $fp e $sp para o novo frame da funcao
        novaInstrucao = criarNoAssembly(typeI, "addi");
        novaInstrucao->tipoI->rt = $fp;
        novaInstrucao->tipoI->rs = $fp;
        novaInstrucao->tipoI->imediato = get_sp(funcaoAtual) + 1;
        instrucoesAssembly[indiceAssembly++] = novaInstrucao;

        MEMORIA_FUNCOES* funcaoChamada = buscar_funcao(&vetorMemoria, instrucao->arg1->nome);

        novaInstrucao = criarNoAssembly(typeI, "addi");
        novaInstrucao->tipoI->rt = $sp;
        novaInstrucao->tipoI->rs = $sp;
        novaInstrucao->tipoI->imediato = get_sp(funcaoChamada) + 1;
        instrucoesAssembly[indiceAssembly++] = novaInstrucao;

        // Pulando para a funcao chamada
        novaInstrucao = criarNoAssembly(typeJ, "jal");
        novaInstrucao->tipoJ->labelImediato = strdup(instrucao->arg1->nome);
        instrucoesAssembly[indiceAssembly++] = novaInstrucao;

        // Volta os valores de $fp
        novaInstrucao = criarNoAssembly(typeI, "subi");
        novaInstrucao->tipoI->rt = $fp;
        novaInstrucao->tipoI->rs = $fp;
        novaInstrucao->tipoI->imediato = get_sp(funcaoAtual) + 1;
        instrucoesAssembly[indiceAssembly++] = novaInstrucao;

        // Volta os valores de $sp
        novaInstrucao = criarNoAssembly(typeI, "subi");
        novaInstrucao->tipoI->rt = $sp;
        novaInstrucao->tipoI->rs = $sp;
        novaInstrucao->tipoI->imediato = get_sp(funcaoChamada) + 1;
        instrucoesAssembly[indiceAssembly++] = novaInstrucao;

        if(instrucao->arg3->tipo != Vazio){
            // Armazena o valor do retorno da funcao anterior no registrador passado como argumento
            novaInstrucao = criarNoAssembly(typeI, "lw");
            novaInstrucao->tipoI->rt = instrucao->arg3->val;
            novaInstrucao->tipoI->rs = $fp;
            novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, get_variavel(funcaoAtual, "Valor Retorno"));
            instrucoesAssembly[indiceAssembly++] = novaInstrucao;
        }
    } 
    else if(!strcmp(instrucao->op, "END")){
        if(!strcmp(instrucao->arg1->nome, "main")){
            return; // Nao precisa fazer mais nada, ja que a proxima instrucao eh o HALT
        }
        
        // Restaura o valor de $ra da funcao anterior
        novaInstrucao = criarNoAssembly(typeI, "lw");
        novaInstrucao->tipoI->rs = $fp;
        novaInstrucao->tipoI->rt = $ra;
        novaInstrucao->tipoI->imediato = get_fp_relation(funcaoAtual, get_variavel(funcaoAtual, "Endereco Retorno"));
        instrucoesAssembly[indiceAssembly++] = novaInstrucao;
    
        // Pula para a instrucao que fez a chamada da funcao
        novaInstrucao = criarNoAssembly(typeR, "jr");
        novaInstrucao->tipoR->rs = $ra;
        novaInstrucao->tipoR->rd = $zero;
        novaInstrucao->tipoR->rt = $zero;
        instrucoesAssembly[indiceAssembly++] = novaInstrucao;

    }
    else{
        printf(ANSI_COLOR_RED);
        printf("Erro: ");
        printf(ANSI_COLOR_RESET);
        printf("Instrucao nao reconhecida (%s)\n", instrucao->op);
    }

}