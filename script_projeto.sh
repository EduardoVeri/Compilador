#!/bin/bash

clear

## Using Cmake ##
make generate
rm -r ./build
mkdir build
cmake -B ./build 
cmake --build ./build

## Using Command Line ##
# cd ./src
# bison -d -oparser.c parser.y
# flex -olexer.c lexer.l
# mv parser.h ../include
# cd ..
# gcc src/*.c -o bin/compilador -Iinclude 

## Some Tests ## 

#./bin/compilador ./test_files/assembly/fatorial_recursivo_vetor.cm -o ./bin/codigoBinario.txt -v -ci -ca 
#./bin/compilador ./test_files/sort.cm -o ./bin/codigoBinario.txt -v -ci -ca 
#./bin/compilador ./test_files/assembly/vetor.cm -o ./bin/codigoBinario.txt -v -ci -ca 
#./bin/compilador ./test_files/mdc.cm -o ./bin/codigoBinario.txt -v -ci -ca 
#./bin/compilador ./test_files/assembly/fatorial_recursivo.cm -o ./bin/codigoBinario.txt -v -ci -ca 

./bin/compilador ./test_files/SO/calculo_media.cm -o ./bin/testes_SO/calculo_media.txt
./bin/compilador ./test_files/SO/num_primo.cm -o ./bin/testes_SO/num_primo.txt 
./bin/compilador ./test_files/SO/potencia.cm -o ./bin/testes_SO/potencia.txt
./bin/compilador ./test_files/SO/mdc.cm -o ./bin/testes_SO/mdc.txt 
./bin/compilador ./test_files/SO/sort.cm -o ./bin/testes_SO/sort.txt
./bin/compilador ./test_files/SO/fatorial_recursivo.cm -o ./bin/testes_SO/fatorial_recursivo.txt
./bin/compilador ./test_files/SO/fatorial_iterativo.cm -o ./bin/testes_SO/fatorial_iterativo.txt
./bin/compilador ./test_files/SO/fibonacci.cm -o ./bin/testes_SO/fibonacci.txt 
./bin/compilador ./test_files/SO/soma_funcao.cm -o ./bin/testes_SO/soma_funcao.txt
./bin/compilador ./test_files/SO/modulo.cm -o ./bin/testes_SO/modulo.txt