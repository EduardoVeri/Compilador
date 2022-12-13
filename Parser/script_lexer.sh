#!/bin/bash

flex scanner.l
gcc -o programa_lexer lex.yy.c -lfl
./programa_lexer mdc.cm
