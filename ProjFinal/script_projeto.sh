#!/bin/bash

clear
cd ./src
bison -d parser.y
flex -oarquivo_lex.c lexer.l
mv parser.tab.h ../include
cd ..
gcc src/*.c -o bin/compilador.exe -lfl -Iinclude 
./bin/compilador.exe ./testes/assembly/soma.cm -v -ci -ca