generate:
	@echo "Generating parser and lexer..."
	cd src && \
	bison -d -oparser.c parser.y && \
	flex -olexer.c lexer.l && \
	mv parser.h ../include
	@echo "Done!"