#include<stdio.h>

int main(){
	char *string;
	int size=100;
	getline(&string,&size,stdin);
	//printf("%s%d",string,strlen(string));
	char keyword[100][100]={"int","float","char","double","goto","for","while"};
	char operators[100][2]={"+","-","*","/","%"};
	printf("operatords are %s%d",operators[3],sizeof(operators[]));
}
