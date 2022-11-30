%{
#include <string.h>
int tabelaNomes();
int qntLinhas = 1;
FILE* copiaArquivo = NULL;
void copiar(FILE* velho);
void mostrarTela(char palavra[]);
char stringAux[1000];
%}

DIGIT [0-9]
LETRA [a-zA-Z]
OPAR \+|\-|\*|\/
PRIORIDADE \(|\)|\[|\]|\\|\{|\}
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
   
{DIGIT}{DIGIT}*  printf("\t%d: {NUM, %s}\n", qntLinhas, yytext);
{LETRA}{LETRA}* {
			if((tabelaNomes()) == 0){
				printf("\t%d: {ID, %s}\n", qntLinhas, yytext);
			}
		}
		
		

{PRIORIDADE} printf("\t%d: {PRIORITY, %s}\n", qntLinhas, yytext);
= printf("\t%d: {ATRIB, %s}\n", qntLinhas, yytext);	
, printf("\t%d: {COMMA, %s}\n", qntLinhas, yytext);	
; printf("\t%d: {SEMICOLON, %s}\n", qntLinhas, yytext);	
{OPAR} printf("\t%d: {OPAR, %s}\n", qntLinhas, yytext);	
{SIMBCOMPOSTOSLOGICOS} printf("\t%d: {OPLOG, %s}\n", qntLinhas, yytext);
{SIMBSIMPLESLOGICOS} printf("\t%d: {OPLOG, %s}\n", qntLinhas, yytext);

<<EOF>> {
		printf("\t%d: EOF\n", qntLinhas);
		return 0;
	}

. {printf("\t%d: Erro, problema em = %s\n", qntLinhas, yytext);}

%%

int main(int argc, char *argv[])
{
	FILE *f_in;
	
	if (argc == 2)
	{
		if(f_in = fopen(argv[1],"r")) yyin = f_in;
		else perror(argv[0]);
		
		copiar(f_in);
		
		rewind(f_in);
		copiaArquivo = fopen("copia.txt", "r");
		
		fgets(stringAux, 1000, copiaArquivo);
		mostrarTela(stringAux);
		
	}
	else yyin = stdin;
	
	yylex();

	return(0);
}

int tabelaNomes(){
	char aux[20];
	int flag = 0;
	
	if(strcmp(yytext, "if") == 0){
		strcpy(aux, "if");
		flag =  1;
	}
	else if(strcmp(yytext, "int") == 0){
		strcpy(aux, "int");
		flag =  1;
	}
	else if(strcmp(yytext, "else") == 0){
		strcpy(aux, "else");
		flag =  1;
	}
	else if(strcmp(yytext, "return") == 0){
		strcpy(aux, "return");
		flag =  1;
	}
	else if(strcmp(yytext, "void") == 0){
		strcpy(aux, "void");
		flag =  1;
	}
	else if(strcmp(yytext, "while") == 0){
		strcpy(aux, "while");
		flag =  1;
	}
	
	if(flag == 1) printf("\t%d: {reserved word, %s}\n", qntLinhas, aux);
	
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

void copiar(FILE* velho)
{
	FILE *novo;
	novo=fopen("copia.txt","w");
	if (novo==NULL){
		printf("Erro de abertura\n");
		exit(1);
	}

	char letra;
	while( (letra = fgetc(velho)) != EOF ) fprintf(novo, "%c", letra);

	fclose(novo);
	return;
}
