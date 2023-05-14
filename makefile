all:
	
	bison -d analise/sintatico.y
	flex analise/lexico.l
	gcc -std=c99 lex.yy.c sintatico.tab.h -o parser
	# ./lex

clean:
	rm ./lex ./lex.yy.c