CC = gcc
CFLAGS = -lfl
INCLUDES = -Iinclude

all: compilador

compilador: main.o arquivo_lex.o arvore.o assembly.o binario.o codInterm.o funcoes_assembly.o label.o memoria.o parser.tab.o registradores.o semantica.o tabelaSimb.o
	$(CC) $(CFLAGS) -o bin/compilador main.o arquivo_lex.o arvore.o assembly.o binario.o codInterm.o funcoes_assembly.o label.o memoria.o parser.tab.o registradores.o semantica.o tabelaSimb.o 

main.o: src/main.c include/*
	$(CC) $(CFLAGS) $(INCLUDES) -c src/main.c

arquivo_lex.o: src/arquivo_lex.c include/*
	$(CC) $(CFLAGS) $(INCLUDES) -c src/arquivo_lex.c 

assembly.o: src/assembly.c include/*
	$(CC) $(CFLAGS) $(INCLUDES) -c src/assembly.c

arvore.o: src/arvore.c include/*
	$(CC) $(CFLAGS) $(INCLUDES) -c src/arvore.c

binario.o: src/binario.c include/*
	$(CC) $(CFLAGS) $(INCLUDES) -c src/binario.c

codInterm.o: src/codInterm.c include/*
	$(CC) $(CFLAGS) $(INCLUDES) -c src/codInterm.c

funcoes_assembly.o: src/funcoes_assembly.c include/*
	$(CC) $(CFLAGS) $(INCLUDES) -c src/funcoes_assembly.c

label.o: src/label.c include/*
	$(CC) $(CFLAGS) $(INCLUDES) -c src/label.c

memoria.o: src/memoria.c include/*
	$(CC) $(CFLAGS) $(INCLUDES) -c src/memoria.c

parser.tab.o: src/parser.tab.c include/*
	$(CC) $(CFLAGS) $(INCLUDES) -c src/parser.tab.c

registradores.o: src/registradores.c include/*
	$(CC) $(CFLAGS) $(INCLUDES) -c src/registradores.c

semantica.o: src/semantica.c include/*
	$(CC) $(CFLAGS) $(INCLUDES) -c src/semantica.c

tabelaSimb.o: src/tabelaSimb.c include/*
	$(CC) $(CFLAGS) $(INCLUDES) -c src/tabelaSimb.c

run: compilador
	clear
	./bin/compilador ./testes/assembly/soma.cm -o ./bin/codigoBinario.txt -v -ci -ca 

clean:
	rm -f program *.o