typedef struct nolinha{
    int numlinha;
    struct nolinha *proximo, *anterior;
} NOLINHA;

typedef struct item{
    int tipoIdentificador; //Trocar para enum depois
    int tipoDado;
    char nomeIdentificador[26]; //Um identificador deve ter no máximo 25 caracteres
    char escopo[26];
    NOLINHA *linhas;
    struct item *proximo, *anterior; //Lista encadeada
} ITEM;

typedef ITEM* PONTEIROITEM;
typedef NOLINHA* PONTEIROLINHA;

PONTEIROITEM* inicializaTabela();
void inserir(PONTEIROITEM tabelaHash[], int tamanho, int tipoIdentificador, int tipoDado, char nomeIdentificador[26], char escopo[26], int linha);
void remover(PONTEIROITEM tabelaHash[], PONTEIROITEM num, int tamanho);
PONTEIROITEM procura(PONTEIROITEM tabelaHash[], char identificador[26], int tamanho);
void apagarTabela(PONTEIROITEM tabelaHash[]);
void adicionaLinha(PONTEIROITEM num, int valorLinha);
unsigned longhash(char *str);
void imprimirTabela(PONTEIROITEM tabelaHash[]);