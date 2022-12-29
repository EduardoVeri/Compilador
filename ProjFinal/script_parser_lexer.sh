#!/bin/bash

clear
bison -d parser.y
flex -oarquivo_lex.c lexer.l
gcc -c arquivo_lex.c 
gcc -c arvore.c 
gcc -c tabelaSimb.c 
gcc -c main.c
gcc -c semantica.c
gcc parser.tab.c arquivo_lex.o arvore.o tabelaSimb.o main.o semantica.o -o programa_parser.o -lfl
./programa_parser.o ./Arquivos_Testes/sort.cm
