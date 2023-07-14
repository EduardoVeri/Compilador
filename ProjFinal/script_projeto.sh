#!/bin/bash

clear
cd ./src
bison -d -oparser.c parser.y
flex -olexer.c lexer.l
mv parser.h ../include
cd ..
gcc src/*.c -o bin/compilador -lfl -Iinclude 
#./bin/compilador ./testes/assembly/fatorial_recursivo_vetor.cm -o ./bin/codigoBinario.txt -v -ci -ca 
./bin/compilador ./testes/sort.cm -o ./bin/codigoBinario.txt -v -ci -ca 
#./bin/compilador ./testes/assembly/vetor.cm -o ./bin/codigoBinario.txt -v -ci -ca 
#./bin/compilador ./testes/mdc.cm -o ./bin/codigoBinario.txt -v -ci -ca 
#./bin/compilador ./testes/assembly/fatorial_recursivo.cm -o ./bin/codigoBinario.txt -v -ci -ca 