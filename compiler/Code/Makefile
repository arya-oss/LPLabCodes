project:	lexfile.l yaccfile.y
		yacc -d yaccfile.y
		lex lexfile.l
		gcc -o $@ y.tab.c lex.yy.c -ll -ly
