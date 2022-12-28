#ifndef _GLOBALS_H_
#define _GLOBALS_H_

extern int qntLinhas; //Depois trocar para um valor global para utilizar no parser
extern char auxNome[26];
extern char id[26];
/* Declaracao da arvore de analise sintatica */

typedef enum {
    DeclVoidVar, //Quando uma variavel é declarada como void.
    DeclFuncExiste, //Quando uma função é declarada mais de uma vez.
    DeclVarExiste, //Quando uma variável é declarada mais de uma vez.
    DeclFuncVar, //Quando uma função é declarada com o mesmo nome de uma variável.
    DeclVarFunc //Quando uma variável é declarada com o mesmo nome de uma função.

} erroSemantico;

typedef enum {DECLARACAO, EXPRESSAO, NENHUM} tipoNo;

typedef enum {Type_Int, Type_Void} tipoTipo;

typedef enum {
    IfK,
    WhileK,
    AssignK,
    ReturnINT,
    ReturnVOID,
	NuloDecl,
    VarDeclK,
    VetDeclK,
    FunDeclK,
    VarParamK, // Declaração de variável parâmetro.
    VetParamK, // Declaração de vetro parâmetro.
    ParamVoid
} tipoDECL;

typedef enum {
    OpK, // Operando.
    ConstK, // Valor numérico constante.
    IdK, // Uso de variável.
    AtivK, // Chamada de função.
    TypeK, // Palavra reservada de tipo.
    VetorK, // Uso de parâmetro vetor.
	NuloExp
} tipoEXP;

typedef struct NoArvore{
	int numLinha;
	tipoNo tipo; //Declaracao ou Expressao
	tipoDECL tipoDeclaracao; //if(0) repeat(1) assign(2) read(3) write(4)
	tipoEXP tipoExpressao; 
	char lexema[26]; //Tamanho máximo lexema é de 25
	struct NoArvore * filho[3]; //No maximo três filhos
	struct NoArvore * irmao;
} NoArvore;

typedef NoArvore * PONTEIRONO;

PONTEIRONO criaNo(char lexema[26], int numLinha, tipoNo tipoNo, tipoDECL tipoDeclaracao, tipoEXP tipoExpressao);

PONTEIRONO adicionaIrmao(PONTEIRONO raiz, PONTEIRONO no);

PONTEIRONO adicionaFilho(PONTEIRONO raiz, PONTEIRONO no);

PONTEIRONO novoNo();

void mostraArvore(PONTEIRONO raiz, int num);

enum yytokentype getToken(void);

PONTEIRONO parse(void);


#define ANSI_COLOR_RED      "\x1b[31m" //cores em ANSI utilizadas 
#define ANSI_COLOR_GRAY     "\e[0;37m"
#define ANSI_COLOR_WHITE    "\e[1;37m" 
#endif