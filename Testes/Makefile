all: 	
	flex teste_lexico.l

	bison -d teste_sintatico.y

	gcc -o calc yacc.tab.c lex.yy.c -lfl

