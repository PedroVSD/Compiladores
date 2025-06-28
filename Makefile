SCANNER := lex
SCANNER_PARAMS := lexica.l
PARSER := yacc
PARSER_PARAMS := -d sintatica.y
CC := gcc
CFLAGS := -Wall -Wextra -std=c99 -g

all: compile translate clean

compile:
	clear
	$(SCANNER) $(SCANNER_PARAMS)
	$(PARSER) $(PARSER_PARAMS)
	g++ -o glf y.tab.c -ll

run: glf
	clear
	compile
	translate

debug: PARSER_PARAMS += -Wcounterexamples
debug: all

translate: glf
	./glf < Teste.dhp
	./glf < Teste.dhp > resultado.c

# Target para compilar o quicksort
quicksort.o: quicksort.c quicksort.h
	$(CC) $(CFLAGS) -c quicksort.c

# Target para compilar e executar o resultado gerado
run_resultado: resultado.c quicksort.o
	@echo "Compilando resultado.c com quicksort..."
	$(CC) $(CFLAGS) resultado.c quicksort.o -o resultado
	@echo "Executando resultado..."
	./resultado

# Target para apenas compilar o resultado (sem executar)
compile_resultado: resultado.c quicksort.o
	@echo "Compilando resultado.c com quicksort..."
	$(CC) $(CFLAGS) resultado.c quicksort.o -o resultado
	@echo "Resultado compilado com sucesso!"

# Target para workflow completo: compilar linguagem -> traduzir -> compilar resultado -> executar
full_workflow: compile translate run_resultado

# Target para compilar apenas se resultado.c não existir
resultado.c:
	@echo "Arquivo resultado.c não encontrado. Execute 'make translate' primeiro."
	@exit 1

clean:
	rm -f y.tab.c
	rm -f y.tab.h
	rm -f lex.yy.c
	rm -f glf