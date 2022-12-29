#!/bin/bash

clear
bison -d parser.y
flex -oarquivo_lex.c lexer.l
gcc parser.tab.c arquivo_lex.c arvore.c tabelaSimb.c main.c semantica.c -o compilador.exe -lfl
./compilador.exe ./Arquivos_Testes/Testes_Semantica/Teste_9.cm
