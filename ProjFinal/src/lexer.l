%{

#include <string.h>
#include "parser.tab.h"
#include "global.h"
#include "tabelaSimb.h"

char stringAux[1000];
char auxNome[MAXLEXEMA];
char id[MAXLEXEMA];
FILE * copiaArquivo = NULL;
int firstTime = 1;

int tabelaNomes(enum yytokentype *token);
void copiar(FILE* velho);
void mostrarTela(char palavra[]);


int indPilha = -1;
char pilha[10][MAXLEXEMA];

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
			
			/* Caso o NUM possua um tamanho maior do que o valor trabalhado,
			seu conteudo sera cortado para poder ser utilizado na linguagem */
			if(strlen(yytext) >= MAXLEXEMA){
				printf(ANSI_COLOR_PURPLE "\tWARNING: Digito muito grande - " ANSI_COLOR_RESET ); 
				yytext[MAXLEXEMA-1] = '\0';
				printf("valor reduzido para apenas %s\n", yytext);
			}
			
			//strcpy(auxNome, yytext);
			
			indPilha++;
			strcpy(pilha[indPilha], yytext);
			

		  	return NUM; 
		 }
		  
{LETRA}({LETRA}|{DIGIT})* {	
			enum yytokentype token;
			if((tabelaNomes(&token)) == 0){
				printf("\t%d: ID, %s\n", qntLinhas, yytext);
				token = ID;
			}
			
			/* Caso o ID possua um tamanho maior do que o trabalhado,
			seu conteudo sera cortado para poder ser utilizado na linguagem */
			if(strlen(yytext) >= MAXLEXEMA){
				printf(ANSI_COLOR_PURPLE "\tWARNING: ID muito grande - " ANSI_COLOR_RESET ); 
				yytext[MAXLEXEMA-1] = '\0';
				printf("nome reduzido para '%s'\n", yytext);
			}

			//strcpy(auxNome, yytext);

			indPilha++;
			strcpy(pilha[indPilha], yytext);

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

!N {if(arquivoEntrada == stdin) return 0;}

. {
	printf(ANSI_COLOR_RED "\nERRO LEXICO, LINHA: %d" ANSI_COLOR_RESET, qntLinhas);
	printf(": %s não identificado na linguagem\n", yytext);
	return ERRO;
  }

%%

//Funcao que verifica se o id eh uma palavra reservada
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

//Mostra a linha inteira na tela
void mostrarTela(char palavra[]){
	int i = 0;
	char ch;
	printf(ANSI_COLOR_RESET "%d: ", qntLinhas);
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

//Funcao que copia o arquivo de entrada para um arquivo de saida extra
void copiar(FILE* velho){
	FILE *novo;
	novo=fopen("src/copia.txt","w");
	if (novo==NULL){
		printf("Erro de abertura\n");
		exit(1);
	}

	char letra;
	while((letra = fgetc(velho)) != EOF) fprintf(novo, "%c", letra);

	fclose(novo);
	return;
}

//Funcao que retorna o proximo token
enum yytokentype getToken(void)
{ 	
	if(firstTime == 1){
		firstTime = 0;
		yyin = arquivoEntrada;

		if(arquivoEntrada == stdin){
			printf("Bem vindo ao compilador de C-!\n");
			printf("Para sair, digite !N e aperte enter\n(O valor sera identificado como um token para finalizar as entradas)\n");
			printf("Digite o codigo fonte:\n\n");
			copiaArquivo = NULL;
		}
		else{
			copiar(arquivoEntrada);
			rewind(arquivoEntrada);
			copiaArquivo = fopen("src/copia.txt", "r");
			
			fgets(stringAux, 1000, copiaArquivo);
			mostrarTela(stringAux);
		}	
	}

	enum yytokentype currentToken;

	currentToken = yylex();
	if(currentToken == ID) strcpy(id, yytext);
	return currentToken;
}

