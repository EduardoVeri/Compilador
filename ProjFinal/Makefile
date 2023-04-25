

all:
	flex --header-file=src/scan.h --outfile=src/scan.c src/scan.l
	bison -d src/parser.y -o src/parser.tab.c
	gcc src/*.c -o bin/compilador.exe -lfl -Iinclude 

run:
	./obj/main.o exemplos/exemplo.c