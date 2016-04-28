%{
#include <stdlib.h>
#include "y.tab.h"
extern int yylval;
void yyerror(char *);
%}

%%

[a-b]+		{ yylval = yytext[0]-'a'; return VARIABLE; }

[0-9]+		{ yylval = atoi(yytext); return INTEGER; }

[-+*/=()\n]		{ return yytext[0]; }

[ \t]		;

.			{ yyerror("unrecognized character"); }
%%

int yywrap(void) {
	return 1;
}