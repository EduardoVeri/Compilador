#ifndef _GLOBALS_H_
#define _GLOBALS_H_

extern int qntLinhas; // Contador de linhas
extern char auxNome[26]; // Variável auxiliar para guardar o nome de um identificador
extern char id[26]; // Variável auxiliar para guardar o nome de um identificador


typedef enum {
    DeclVoidVar, //Quando uma variavel é declarada como void.
    DeclFuncExiste, //Quando uma função é declarada mais de uma vez.
    DeclVarExiste, //Quando uma variável é declarada mais de uma vez.
    DeclFuncVar, //Quando uma função é declarada com o mesmo nome de uma variável.
    DeclVarFunc //Quando uma variável é declarada com o mesmo nome de uma função.

} erroSemantico;

typedef enum {DECLARACAO, EXPRESSAO, NENHUM} tipoNo; // Tipo de nó.

typedef enum {Type_Int, Type_Void} tipoTipo; // Tipo de dado.

typedef enum {
    IfK, // If.
    WhileK, // While.
    ReturnINT, // Retorno de função inteira.
    ReturnVOID, // Retorno de função void.
	NuloDecl, // Nulo
    VarDeclK, // Declaração de variável.
    VetDeclK, // Declaração de vetor.
    FunDeclK, // Declaração de função.
    VarParamK, // Declaração de variável parâmetro.
    VetParamK, // Declaração de vetro parâmetro.
    ParamVoid // Declaração de função com parâmetro void.
} tipoDECL;

typedef enum {
    OpK, // Operando.
    OpRel, // Operador relacional.
    ConstK, // Valor numérico constante.
    IdK, // Uso de variável.
    AtivK, // Chamada de função.
    TypeK, // Palavra reservada de tipo.
    VetorK, // Uso de parâmetro vetor.
    AssignK, // Atribuição.
	NuloExp // Nulo.
} tipoEXP;


/* Declaracao da arvore de analise sintatica */

typedef struct NoArvore{
	int numLinha; // Numero da linha
	tipoNo tipo; // Declaracao ou Expressao
	tipoDECL tipoDeclaracao; // Tipo da declaracao
	tipoEXP tipoExpressao; // Tipo da Expressão
	char lexema[26]; // Tamanho máximo lexema é de 25
	struct NoArvore * filho[3]; // Ponteiro para os filhos. No maximo três filhos
	struct NoArvore * irmao; // Ponteiro para o irmão
} NoArvore;

typedef NoArvore * PONTEIRONO;

// Funcoes da arvore de analise sintatica
PONTEIRONO criaNo(char lexema[26], int numLinha, tipoNo tipoNo, tipoDECL tipoDeclaracao, tipoEXP tipoExpressao);
PONTEIRONO adicionaIrmao(PONTEIRONO raiz, PONTEIRONO no);
PONTEIRONO adicionaFilho(PONTEIRONO raiz, PONTEIRONO no);
PONTEIRONO novoNo();
void mostraArvore(PONTEIRONO raiz, int num);
void desalocaArvore(PONTEIRONO raiz);

enum yytokentype getToken(void);

// Função do parser
PONTEIRONO parse(void);

// Cores em ANSI
#define ANSI_COLOR_RED      "\x1b[31m" 
#define ANSI_COLOR_GRAY     "\e[0;37m"
#define ANSI_COLOR_WHITE    "\e[1;37m" 
#define ANSI_COLOR_RESET    "\e[0m"	
#endif