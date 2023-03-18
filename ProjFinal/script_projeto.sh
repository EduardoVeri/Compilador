#!/bin/bash

clear
cd ./src
bison -d parser.y
flex -oarquivo_lex.c lexer.l
mv parser.tab.h ../include
cd ..
gcc src/parser.tab.c src/arquivo_lex.c src/arvore.c src/tabelaSimb.c src/main.c src/semantica.c src/codInterm.c src/registradores.c -o bin/compilador.exe -lfl  -Iinclude
./bin/compilador.exe ./testes/sort.cm
