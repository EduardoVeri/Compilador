#!/bin/bash

clear
cd ./src
bison -d parser.y
flex -oarquivo_lex.c lexer.l
mv parser.tab.h ../include
cd ..
gcc src/*.c -o bin/compilador -lfl -Iinclude 
#./bin/compilador ./testes/assembly/fatorial_recursivo_vetor.cm -o ./bin/codigoBinario.txt -v -ci -ca 
#./bin/compilador ./testes/sort.cm -o ./bin/codigoBinario.txt -v -ci -ca 
#./bin/compilador ./testes/assembly/vetor.cm -o ./bin/codigoBinario.txt -v -ci -ca 
./bin/compilador ./testes/mdc.cm -o ./bin/codigoBinario.txt -v -ci -ca 