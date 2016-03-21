%{
	#include <stdio.h>
	#include <string.h>
	void printConst(char str[]);
%}
/*
Title - Lex program to detect consonant and vowels
Author: Rajmani Arya
Date: 15th March 2016
Problem Stmt-
write a lex prog. to translate the content of a file (having multiple English words)
a. If word begins with string of consonants, move the initial consonant string to end of word
and add suffix word NIT.
a.1 'O' at begining of word is a consonant if it is followed by a vowel.
b. If word begins with vowel, add suffix WARANGAL to the word.
b.1 'Y' at begining of word is a vowel if it is not followed by a vowel.
Compile:
lex lex_word.l
gcc lex.yy.c -ll
./a.out input.txt
----------------input.txt----------------------
this hello yeabc ykabc oeabc okabc go
 */
VOWEL [aeiouAEIOU]
CONS [bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ]
AL [a-zA-Z]*
%%
(y|Y){VOWEL}{AL}	printConst(yytext);
(o|O){VOWEL}{AL}	printConst(yytext);
{VOWEL}{AL}		printf("%sWARANGAL", yytext);
(y|Y){AL}		printf("%sWARANGAL", yytext);
{CONS}{AL}		printConst(yytext);
%%

void printConst(char str[]) {
	int i,j=0,k=0,len = strlen(str);
	char ch, _tmp[128], _str[128];
	_tmp[j++] = str[0];
	for(i=1; i<len; i++) {
		if(str[i] >='a' && str[i] <='z')
			ch = str[i];
		else ch = str[i]-32;
		if(!(ch=='a'||ch=='e'||ch=='i'||ch=='o'||ch=='u')) {
			_tmp[j++] = str[i];
		} else break;
	}
	_tmp[j] = '\0';
	for (i = j; i < len; ++i){
		_str[k++] = str[i];
	}
	_str[k] = '\0';
	strcat(_str, _tmp);
	printf("%sNIT", _str);
}

int main(int argc, char const * argv[]) {
	if(argc < 2) {
		printf("Usage: ./a.out <filename>");
		exit(1);
	}
	yyin = fopen(argv[1], "r");
	yylex();
	fclose(yyin);
	return 0;
}
