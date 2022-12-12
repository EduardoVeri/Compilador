#!/bin/bash

bison -d arquivo_bison.y
flex -oarquivo_lex.c arquivo_lex.l
gcc -c arquivo_lex.c 
gcc arquivo_bison.tab.c arquivo_lex.o -o exec.o -lfl
./exec.o
