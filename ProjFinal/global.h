
extern int qntLinhas; //Depois trocar para um valor global para utilizar no parser
extern char auxNome[26];

/* Declaracao da arvore de analise sintatica */

typedef struct NoArvore{
	struct NoArvore * filho[3]; //No maximo três filhos
	struct NoArvore * irmao;
	int numLinha;
	int tipoNo; //decl(0)  exp(1)
	int tipoDecl; //if(0) repeat(1) assign(2) read(3) write(4)
	int nometoken; 
	char lexema[26]; //Tamanho máximo lexema é de 25
} NoArvore;


typedef NoArvore * PONTEIRONO;

PONTEIRONO criaNo(char lexema[26], int numLinha, int tipoDecl, int tipoNo);

PONTEIRONO adicionaIrmao(PONTEIRONO raiz, PONTEIRONO no);

PONTEIRONO adicionaFilho(PONTEIRONO raiz, PONTEIRONO no);

PONTEIRONO novoNo();

