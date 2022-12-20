#!/bin/bash

bison -d arquivo_bison.y
flex -oarquivo_lex.c entrada.l
gcc -c arquivo_lex.c 
gcc -c arvore.c 
gcc arquivo_bison.tab.c arquivo_lex.o arvore.o -o programa_parser.o -lfl
./programa_parser.o mdc.cm
