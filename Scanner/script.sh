#!/bin/bash

flex entrada.l
gcc -o exec lex.yy.c -lfl
./exec mdc.cm
