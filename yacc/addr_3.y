%{

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void ThreeAddressCode();

char AddToTable(char, char, char);

int ind=0;
char temp='A';
struct incod
{
    char opd1;
    char opd2;
    char opr;
};

%}

%union
{
	char sym;
}

%token <sym> LETTER NUMBER
%type <sym> expr
%left '-' '+'
%right '*' '/'

%%

statement: LETTER '=' expr ';' {AddToTable((char)$1,(char)$3,'=');}
           | expr ';'
           ;

expr: expr '+' expr {$$ = AddToTable((char)$1,(char)$3,'+');}
      | expr '-' expr {$$ = AddToTable((char)$1,(char)$3,'-');}
      | expr '*' expr {$$ = AddToTable((char)$1,(char)$3,'*');}
      | expr '/' expr {$$ = AddToTable((char)$1,(char)$3,'/');}
      | '(' expr ')' {$$ = (char)$2;}
      | NUMBER {$$ = (char)$1;}
      | LETTER {$$ = (char)$1;}
      ;

%%
yyerror(char *s)
{
  printf("%s",s);
}

struct incod code[20];

int id=0;

char AddToTable(char opd1,char opd2,char opr)
{
code[ind].opd1=opd1;
code[ind].opd2=opd2;
code[ind].opr=opr;
ind++;
temp++;
return temp;
}

void ThreeAddressCode()
{
	int cnt=0;
	temp++;
	printf("\n THREE ADDRESS CODE \n");
	while(cnt<ind)
	{
        printf("%c : = ",temp);


        if(isalpha(code[cnt].opd1))
                printf("%c  ",code[cnt].opd1);
        else
                {printf("%c ",temp);}

        printf("%c\t",code[cnt].opr);

        if(isalpha(code[cnt].opd2))
                printf("%c  ",code[cnt].opd2);
        else
                {printf("%c  ",temp);}

        printf("\n");
        cnt++;
  		temp++;
	}
}


void main()
{
 	printf("\nEnter the Expression: ");
 	yyparse();
	temp='A';
	ThreeAddressCode();
}

yywrap(void)
{
  	return 1;
}

