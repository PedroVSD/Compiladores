
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

clean:
	rm y.tab.c
	rm y.tab.h
	rm lex.yy.c
	rm glf
