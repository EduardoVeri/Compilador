#ifndef _GLOBALS_H_
#define _GLOBALS_H_ 1

#define DEBUG_MODE 0 // Ativa o modo debug
#define MAXLEXEMA 21 // Tamanho máximo do lexema

extern int flagVerbose; // Flag para ativar o modo verbose
extern int indPilha; // Índice da pilha de lexemas
extern int qntLinhas; // Contador de linhas
extern char* yytext; // Texto do lexema
extern char pilha[4][MAXLEXEMA]; // Pilha de lexemas
extern FILE * arquivoEntrada; // Arquivo de entrada
extern FILE * copiaArquivo; // Cópia do arquivo de entrada
extern FILE * arquivoSaida; // Arquivo de saída
extern FILE * arquivoSaida_Intermediario; // Arquivo de saída do código intermediário
extern FILE * arquivoSaida_Assembly; // Arquivo de saída do código assembly

typedef enum {
    DeclVoidVar, //Quando uma variavel é declarada como void.
    DeclFuncExiste, //Quando uma função é declarada mais de uma vez.
    DeclVarExiste, //Quando uma variável é declarada mais de uma vez.
    DeclFuncVar, //Quando uma função é declarada com o mesmo nome de uma variável.
    DeclVarFunc, //Quando uma variável é declarada com o mesmo nome de uma função.
    VarNaoDeclarada, //Quando uma variável é usada sem ser declarada.
    FuncaoNaoDeclarada, //Quando uma função é usada sem ser declarada.
    AtribFuncVoid, //Quando uma função do tipo void é atribuída a uma variável.
    FuncMainNaoDeclarada, //Quando a função main não é declarada.
    VetorNaoDeclarado, //Quando um vetor é usado sem ser declarado.
    ChamadaFuncao //Quando uma funcao gostaria de ser chamada, porem faltou os ()
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
    VetParamK, // Declaração de vetor parâmetro.
    ParamVoid // Declaração de função com parâmetro void.
} tipoDECL;

typedef enum {
    OpK, // Operando.
    OpRel, // Operador relacional.
    ConstK, // Valor numérico constante.
    IdK, // Uso de variável.
    AtivK, // Chamada de função.
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
    char lexema[MAXLEXEMA]; // Tamanho máximo lexema é de 25
    struct NoArvore * filho[3]; // Ponteiro para os filhos. No maximo três filhos
    struct NoArvore * irmao; // Ponteiro para o irmão
} NoArvore;

typedef NoArvore * PONTEIRONO;

//Cria um no para a arvore. Recebe os valores como parametro.
PONTEIRONO criaNo(char lexema[MAXLEXEMA], int numLinha, tipoNo tipoNo, tipoDECL tipoDeclaracao, tipoEXP tipoExpressao);

//Funcoes para adicionar filhos e irmaos na arvore
PONTEIRONO adicionaIrmao(PONTEIRONO raiz, PONTEIRONO no);
PONTEIRONO adicionaFilho(PONTEIRONO raiz, PONTEIRONO no);

//Cria um no na arvore, com valores default
PONTEIRONO novoNo();

//Funcao para imprimir a arvore
void mostraArvore(PONTEIRONO raiz, int num);

//Funcao para desalocar a arvore
void desalocaArvore(PONTEIRONO raiz);

//Funcao yylex adapatada para o parser
enum yytokentype getToken(void);

//Funcao yyparse adaptada para a main
PONTEIRONO parse(void);

// Cores em ANSI
#define ANSI_COLOR_RED      "\x1b[31m" 
#define ANSI_COLOR_GRAY     "\e[0;37m"
#define ANSI_COLOR_WHITE    "\e[1;37m" 
#define ANSI_COLOR_RESET    "\e[0m"	
#define ANSI_COLOR_PURPLE   "\e[0;35m"
#define ANSI_COLOR_GREEN    "\e[0;32m"



#endif
