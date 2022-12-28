%{

#include <string.h>
#include "arquivo_bison.tab.h"
#include "global.h"
#include "tabelaSimb.h"


char stringAux[1000];
char auxNome[26];
char id[26];

FILE* copiaArquivo = NULL;
FILE* f_in = NULL;


int tabelaNomes(enum yytokentype *token);
void copiar(FILE* velho);
void mostrarTela(char palavra[]);
PONTEIRONO parse(void);
void percorrerArvore(PONTEIRONO arvoreSintatica, PONTEIROITEM* tabelaHash, char* escopo);
void mostrarErroSemantico(erroSemantico erro, char* nome, int linha);


%}

DIGIT [0-9]
LETRA [a-zA-Z]

%%

(" "|\t) {/*Ignora as entradas com espaços e tabulacoes*/}

\/\*		{
		  char c, aux = 'x'; 
		  do
		  { c = input();
		    if (c == EOF) break;
		    if (c == '\n') {
		    	qntLinhas++;
		    	if (copiaArquivo != NULL){
		    		fgets(stringAux, 1000, copiaArquivo);
				mostrarTela(stringAux);
		    	}
		    }
		    if (c == '*'){
		    	aux = input();
		    }
		  } while (aux != '/');
		}

\n {
	qntLinhas++;
	if (copiaArquivo != NULL){
		fgets(stringAux, 1000, copiaArquivo);
		if(feof(copiaArquivo) == 0)
			mostrarTela(stringAux);
	}
	
   }
   
   
{DIGIT}{DIGIT}* {
			printf("\t%d: NUM, %s\n", qntLinhas, yytext);
			strcpy(auxNome, yytext);
		  	return NUM; 
		 }
		  
{LETRA}{LETRA}* {	
			enum yytokentype token;
			if((tabelaNomes(&token)) == 0){
				printf("\t%d: ID, %s\n", qntLinhas, yytext);
				token = ID;
			}
			strcpy(auxNome, yytext);
			return token;
		 }
		
	      
\( {
	printf("\t%d: ABREPARENTESES, %s\n", qntLinhas, yytext);
	return ABREPARENTESES;
   }

\) {
	printf("\t%d: FECHAPARENTESES, %s\n", qntLinhas, yytext);
	return FECHAPARENTESES;
   } 

\[ {
	printf("\t%d: ABRECOLCHETES, %s\n", qntLinhas, yytext);
	return ABRECOLCHETES;
   }	      
	      
	      
\] {
	printf("\t%d: FECHACOLCHETES, %s\n", qntLinhas, yytext);
	return FECHACOLCHETES;
   }	      

	      
\{ {
	printf("\t%d: ABRECHAVES, %s\n", qntLinhas, yytext);
	return ABRECHAVES;
   }
	      
\} {
	printf("\t%d: FECHACHAVES, %s\n", qntLinhas, yytext);
	return FECHACHAVES;	
   }

	      
= {
	printf("\t%d: ATRIB, %s\n", qntLinhas, yytext);
	return ATRIB;
  }	
	
, {
	printf("\t%d: COMMA, %s\n", qntLinhas, yytext);
	return COMMA;
  }	
  
; {
	printf("\t%d: SEMICOLON, %s\n", qntLinhas, yytext);	
	return SEMICOLON;
  }
  
\+ {
	printf("\t%d: SOMA, %s\n", qntLinhas, yytext);
	return SOMA;
   }	
   
\- {
	printf("\t%d: SUB, %s\n", qntLinhas, yytext);
	return SUB;
   }  
   
\* {
	printf("\t%d: MULT, %s\n", qntLinhas, yytext);
	return MULT;
   }	
   
\/ {
	printf("\t%d: DIV, %s\n", qntLinhas, yytext);
	return DIV;
   } 

\=\= {
	printf("\t%d: EQ, %s\n", qntLinhas, yytext);
	return EQ;
   }

\!\= {
	printf("\t%d: NEQ, %s\n", qntLinhas, yytext);
	return NEQ;
	}

\< {
	printf("\t%d: LT, %s\n", qntLinhas, yytext);
	return LT;
  }

\> {
	printf("\t%d: GT, %s\n", qntLinhas, yytext);
	return GT;
  }

\<\= {
		printf("\t%d: LET, %s\n", qntLinhas, yytext);
		return LET;
  	}

\>\= {
		printf("\t%d: GET, %s\n", qntLinhas, yytext);
		return GET;
  	}
	
<<EOF>> {
		printf("\t%d: EOF\n", qntLinhas);
		return 0;
	}
	
!N  {if(f_in == NULL) return 0;} //Encerra o programa quando digitado pelo usuário

. {
	printf("ERRO LEXICO: '%s' LINHA %d\n", yytext, qntLinhas);
	return ERRO;
  }

%%

int main(int argc, char *argv[]){
	qntLinhas = 1;
	
	if (argc == 2){
		if(f_in = fopen(argv[1],"r")) yyin = f_in;
		else perror(argv[0]);
		
		copiar(f_in);
		
		rewind(f_in);
		copiaArquivo = fopen("copia.txt", "r");
		
		fgets(stringAux, 1000, copiaArquivo);
		mostrarTela(stringAux);
		
	}
	else { 
		yyin = stdin;
		printf("Bem vindo ao analisador Lexico!\nDigite \"!N\" para sair\n");
	}
	
	PONTEIRONO arvoreSintatica = parse();
	mostraArvore(arvoreSintatica, 0);
	printf("\n\n");
	PONTEIROITEM* tabelaHash = inicializaTabela();

	char escopo[26] = "global"; 

	percorrerArvore(arvoreSintatica, tabelaHash, escopo);

	imprimirTabela(tabelaHash);

	return(0);
}

/*
Função para percorrer todos os nós da árvore sintática e adicionar os itens de declaração, como variáveis e funções,
na tabela de símbolos 
*/

void percorrerArvore(PONTEIRONO arvoreSintatica, PONTEIROITEM* tabelaHash, char* escopo){
	tipoTipo tipo;
	PONTEIRONO auxNo = NULL;
	char auxEscopo[26];

	strcpy(auxEscopo, escopo);

	if(arvoreSintatica == NULL){
		return;
	}

	if(arvoreSintatica->tipo == DECLARACAO){
		if(arvoreSintatica->tipoDeclaracao == FunDeclK){
			tipo = strcmp(arvoreSintatica->lexema, "INT") == 0 ? Type_Int : Type_Void;
			strcpy(auxEscopo, "Funcao");
			inserirTabela(tabelaHash, arvoreSintatica->tipoDeclaracao, tipo, arvoreSintatica->filho[1]->lexema, auxEscopo, arvoreSintatica->numLinha);
		
			if(arvoreSintatica->filho[0]->tipoDeclaracao != ParamVoid){
				auxNo = arvoreSintatica->filho[0];
				while(auxNo != NULL){
					if(strcmp(auxNo->lexema, "INT") == 0){
						strcpy(auxEscopo, arvoreSintatica->filho[1]->lexema);
						inserirTabela(tabelaHash, auxNo->tipoDeclaracao, Type_Int, auxNo->filho[0]->lexema, auxEscopo, arvoreSintatica->numLinha);
						auxNo = auxNo->irmao;
					}
					else{
						mostrarErroSemantico(DeclVoidVar, auxNo->filho[0]->lexema, auxNo->numLinha);
						auxNo = auxNo->irmao;
					}
				}
			}
		}
		else if(arvoreSintatica->tipoDeclaracao == VarDeclK){
			if(strcmp(auxNo->lexema, "INT") == 0){
				strcpy(auxEscopo, arvoreSintatica->filho[1]->lexema);
				inserirTabela(tabelaHash, auxNo->tipoDeclaracao, Type_Int, auxNo->filho[0]->lexema, auxEscopo, arvoreSintatica->numLinha);
				auxNo = auxNo->irmao;
			}
			else{
				mostrarErroSemantico(DeclVoidVar, auxNo->filho[0]->lexema, auxNo->numLinha);
				auxNo = auxNo->irmao;
			}
		}


	}

	for(int i = 0; i < 3; i++){
		if(arvoreSintatica->filho[i] != NULL){
			percorrerArvore(arvoreSintatica->filho[i], tabelaHash, auxEscopo);
		}
	}

	percorrerArvore(arvoreSintatica->irmao, tabelaHash, auxEscopo);
}

void mostrarErroSemantico(erroSemantico erro, char* nome, int linha){
	printf(ANSI_COLOR_RED "ERRO SEMANTICO, LINHA: %d" ANSI_COLOR_GRAY, linha);
	switch (erro){
		case DeclVoidVar:
			printf(": Variavel '%s' declarada como void\n\n", nome);
			break;
	}
}

int tabelaNomes(enum yytokentype *token){
	char aux[20];
	int flag = 0;
	
	if(strcmp(yytext, "if") == 0){
		strcpy(aux, "if");
		*token = IF;
		flag =  1;
	}
	else if(strcmp(yytext, "int") == 0){
		strcpy(aux, "int");
		*token = INT;
		flag =  1;
	}
	else if(strcmp(yytext, "else") == 0){
		strcpy(aux, "else");
		*token = ELSE;
		flag =  1;
	}
	else if(strcmp(yytext, "return") == 0){
		strcpy(aux, "return");
		*token = RETURN;
		flag =  1;
	}
	else if(strcmp(yytext, "void") == 0){
		strcpy(aux, "void");
		*token = VOID;
		flag =  1;
	}
	else if(strcmp(yytext, "while") == 0){
		strcpy(aux, "while");
		*token = WHILE;
		flag =  1;
	}
	
	if(flag == 1) printf("\t%d: reserved word , %s\n", qntLinhas, aux);
	
	return flag;
}

void mostrarTela(char palavra[]){
	int i = 0;
	char ch;
	printf(ANSI_COLOR_GRAY "%d: ", qntLinhas);
	ch = palavra[i];
	while(ch == '\t' || ch == ' '){
		i++;
		ch = palavra[i];
	}
	for (; i < strlen(palavra); i++){
		ch = palavra[i];
		if(ch != '\n') printf("%c", palavra[i]);
	}
	printf("\n");
}

void copiar(FILE* velho){
	FILE *novo;
	novo=fopen("copia.txt","w");
	if (novo==NULL){
		printf("Erro de abertura\n");
		exit(1);
	}

	char letra;
	while((letra = fgetc(velho)) != EOF) fprintf(novo, "%c", letra);

	fclose(novo);
	return;
}

enum yytokentype getToken(void)
{ 
	enum yytokentype currentToken;
	currentToken = yylex();
	if(currentToken == ID) strcpy(id, yytext);
	return currentToken;
}

