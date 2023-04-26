all:
	rm ./lex ./lex.yy.c
	
	flex analise/lexico.l
	
	gcc -std=c99 lex.yy.c -o lex
	
	./lex

clean:
	rm ./lex ./lex.yy.c