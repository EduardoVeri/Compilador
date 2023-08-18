#!/bin/bash

clear
cd ./src
bison -d -oparser.c parser.y
flex -olexer.c lexer.l
mv parser.h ../include
cd ..
gcc src/*.c -o bin/compilador -lfl -Iinclude 
#./bin/compilador ./testes/assembly/fatorial_recursivo_vetor.cm -o ./bin/codigoBinario.txt -v -ci -ca 
#./bin/compilador ./testes/sort.cm -o ./bin/codigoBinario.txt -v -ci -ca 
#./bin/compilador ./testes/assembly/vetor.cm -o ./bin/codigoBinario.txt -v -ci -ca 
#./bin/compilador ./testes/mdc.cm -o ./bin/codigoBinario.txt -v -ci -ca 
#./bin/compilador ./testes/assembly/fatorial_recursivo.cm -o ./bin/codigoBinario.txt -v -ci -ca 

./bin/compilador ./testes/SO/calculo_media.cm -o ./bin/testes_SO/calculo_media.txt
./bin/compilador ./testes/SO/num_primo.cm -o ./bin/testes_SO/num_primo.txt 
./bin/compilador ./testes/SO/potencia.cm -o ./bin/testes_SO/potencia.txt
./bin/compilador ./testes/SO/mdc.cm -o ./bin/testes_SO/mdc.txt 
./bin/compilador ./testes/SO/sort.cm -o ./bin/testes_SO/sort.txt
./bin/compilador ./testes/SO/fatorial_recursivo.cm -o ./bin/testes_SO/fatorial_recursivo.txt
./bin/compilador ./testes/SO/fatorial_iterativo.cm -o ./bin/testes_SO/fatorial_iterativo.txt
./bin/compilador ./testes/SO/fibonacci.cm -o ./bin/testes_SO/fibonacci.txt 
./bin/compilador ./testes/SO/soma_funcao.cm -o ./bin/testes_SO/soma_funcao.txt 
