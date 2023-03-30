

all:
	flex --header-file=src/scan.h --outfile=src/scan.c src/scan.l
	bison -d src/parser.y -o src/parser.tab.c
	gcc src/main.c src/scan.c src/util.c src/parser.tab.c -o obj/main.o

run:
	./obj/main.o exemplos/exemplo.c