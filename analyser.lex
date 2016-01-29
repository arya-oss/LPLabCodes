Num [0-9]
Int [+-]?{Num}{Num}*
%{
#include <stdio.h>
%}

%%
{Int} printf("got a int number");
\n\t printf("\n");
%%

int main(){
    yylex();
}
