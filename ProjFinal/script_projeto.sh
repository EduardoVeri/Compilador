#!/bin/bash

clear
cd ./src
bison -d parser.y
flex -oarquivo_lex.c lexer.l
mv parser.tab.h ../include
cd ..
gcc src/*.c -o bin/compilador -lfl -Iinclude 
./bin/compilador ./testes/assembly/soma_funcao.cm -o ./bin/codigoBinario.txt -v -ci -ca 