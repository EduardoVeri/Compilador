#!/bin/bash

flex scanner.l
gcc -o exec lex.yy.c -lfl
./exec mdc.cm
