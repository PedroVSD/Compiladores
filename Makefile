
SCANNER := lex
SCANNER_PARAMS := lexica.l
PARSER := yacc
PARSER_PARAMS := -d sintatica.y

all: compile translate clean

compile:
		clear
		$(SCANNER) $(SCANNER_PARAMS)
		$(PARSER) $(PARSER_PARAMS)
		g++ -o glf y.tab.c -ll

run: 	glf
		clear
		compile
		translate

debug:	PARSER_PARAMS += -Wcounterexamples
debug: 	all

translate: glf
		./glf < Teste.dhp
		./glf < Teste.dhp > resultado.c

clean:
	rm y.tab.c
	rm y.tab.h
	rm lex.yy.c
	rm glf


#CC = gcc
#CFLAGS = -Wall -Wextra -std=c99 -g

# Arquivos objetos
#OBJS = y.tab.o lex.yy.o quicksort.o

# Target principal
#compile: $(OBJS)
#    $(CC) -o glf $(OBJS) -ll

# Dependências
#quicksort.o: algoritmos/quicksort.c algoritmos/quicksort.h
#    $(CC) $(CFLAGS) -c algoritmos/quicksort.c

#y.tab.o: y.tab.c
#    $(CC) $(CFLAGS) -c y.tab.c

#lex.yy.o: lex.yy.c
#    $(CC) $(CFLAGS) -c lex.yy.c

#clean:
#    rm -f *.o glf y.tab.c y.tab.h lex.yy.c

#.PHONY: clean