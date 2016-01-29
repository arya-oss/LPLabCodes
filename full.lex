ID [a-zA-Z]*.[a-zA-Z]*
Include {#include[ ]*<ID>}|{#include[ ]*"ID"}

%{
{Include} printf("got a header %s\n", yytext);
%}

int main(){
    yylex();
}
