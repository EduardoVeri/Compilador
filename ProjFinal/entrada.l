%{

#include <string.h>
#include "arquivo_bison.tab.h"
#include "global.h"

int tabelaNomes(enum yytokentype *token);
void copiar(FILE* velho);
void mostrarTela(char palavra[]);
char stringAux[1000];


FILE* copiaArquivo = NULL;
FILE *f_in = NULL;

%}

DIGIT [0-9]
LETRA [a-zA-Z]
SIMBCOMPOSTOSLOGICOS ==|<=|>=|!=
SIMBSIMPLESLOGICOS <|>

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
		if(feof(copiaArquivo) != EOF)
			mostrarTela(stringAux);
	}
	
   }
   
   
   
{DIGIT}{DIGIT}* {
			printf("\t%d: { NUM, %s }\n", qntLinhas, yytext);
		  	return NUM; 
		 }
		  
{LETRA}{LETRA}* {	
			enum yytokentype token;
			if((tabelaNomes(&token)) == 0){
				printf("\t%d: { ID, %s }\n", qntLinhas, yytext);
				token = ID;
			}
			return token;
		 }
		
	      
\( {
	printf("\t%d: { ABREPARENTESES, %s }\n", qntLinhas, yytext);
	return ABREPARENTESES;
   }

\) {
	printf("\t%d: { FECHAPARENTESES, %s }\n", qntLinhas, yytext);
	return FECHAPARENTESES;
   } 

\[ {
	printf("\t%d: { ABRECOLCHETES, %s }\n", qntLinhas, yytext);
	return ABRECOLCHETES;
   }	      
	      
	      
\] {
	printf("\t%d: { FECHACOLCHETES, %s }\n", qntLinhas, yytext);
	return FECHACOLCHETES;
   }	      

	      
\{ {
	printf("\t%d: { ABRECHAVES, %s }\n", qntLinhas, yytext);
	return ABRECHAVES;
   }
	      
\} {
	printf("\t%d: { FECHACHAVES, %s }\n", qntLinhas, yytext);
	return FECHACHAVES;	
   }

	      
= {
	printf("\t%d: { ATRIB, %s }\n", qntLinhas, yytext);
	return ATRIB;
  }	
	
, {
	printf("\t%d: { COMMA, %s }\n", qntLinhas, yytext);
	return COMMA;
  }	
  
; {
	printf("\t%d: { SEMICOLON, %s }\n", qntLinhas, yytext);	
	return SEMICOLON;
  }
  
\+ {
	printf("\t%d: { SOMA, %s }\n", qntLinhas, yytext);
	return SOMA;
   }	
   
\- {
	printf("\t%d: { SUB, %s }\n", qntLinhas, yytext);
	return SUB;
   }  
   
\* {
	printf("\t%d: { MULT, %s }\n", qntLinhas, yytext);
	return MULT;
   }	
   
\/ {
	printf("\t%d: { DIV, %s }\n", qntLinhas, yytext);
	return DIV;
   } 
      
{SIMBCOMPOSTOSLOGICOS} {
				printf("\t%d: {OPLOG, %s}\n", qntLinhas, yytext);
				return OPRELACIONAL;
			}
			
{SIMBSIMPLESLOGICOS} {
				printf("\t%d: {OPLOG, %s}\n", qntLinhas, yytext);
				return OPRELACIONAL;
		      }

<<EOF>> {
		printf("\t%d: EOF\n", qntLinhas);
		return 0;
	}
	
!N  {if(f_in == NULL) return 0;} //Encerra o programa quando digitado pelo usuário

. {printf("\t%d: Erro, problema no lexema = %s\n", qntLinhas, yytext);}

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
	
	yyparse();
		
	return(0);
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
	
	if(flag == 1) printf("\t%d: { reserved word , %s }\n", qntLinhas, aux);
	
	return flag;
}

void mostrarTela(char palavra[]){
	int i;
	char ch;
	printf("%d: ", qntLinhas);
	for (i = 0; i < strlen(palavra); i++){
		ch = palavra[i];
		if(ch != '\n' && ch != '\t') printf("%c", palavra[i]);
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