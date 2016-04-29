#include<stdio.h>
#include<ctype.h>
#include<string.h>

#define KEYWORD_COUNT 8
#define OPERATOR_COUNT 6
#define PUNCTUATOR_COUNT 2
#define REP(i,n) for( i=0;i<n  ;i++)
int keyw=0,opt=0,punct=0,ident=0,constants=0;
char keyword[100][100]={"include","int","float","char","double","goto","for","while"};
char operators[100]={'+','-','*','/','%','='};
char punctuators[100]={',',';'};
int is_punctuator(char ch){
	int i;
	REP(i,PUNCTUATOR_COUNT)
	{
		if(ch==punctuators[i])
		{
			printf("%c\n",ch);
			punct++;
			return 1;
		}
	}
	return 0;
}	
int is_operator(char ch){
	int i;
        REP(i,OPERATOR_COUNT)
        {
                if(ch==operators[i])
                {
                       printf("%c\n",ch);
			opt++;
                        return 1;
                }
        }
        return 0;
}
int is_keyword(char text[]){
	int i;
	printf("text is %s\n",text);
	REP(i,KEYWORD_COUNT)
        {
                if(strcmp(text,keyword[i])==0)
                {
		        printf("identifier recognized as %s\n",text);	
                        keyw++;
                        return 1;
                }
        }
        return 0;

}

int main(){
       
        int size=100,count=0,i;
	printf("enter string\n");
        /*getline(&string,&size,stdin);
        printf("%s\n",string);
	*/
	char string[100];
        read(0,string,100);
        printf("%s\n",string);

       	int is_possible_string=0;
	char text[100];
	strcpy(text,"");
	for( i=0;i<strlen(string);i++){
//		printf("text is %s\n",text);
		int flag=0;
//identify that nothing has till been determined
		//possibility of a 
/*		if(strlen(text)==0 && ((string[i]>=48 && string[i]<=57) || string[i]==46))  
			is_possible_constant;	
		if(!is_possible_string && string[i]==34)
*/
//               	if(!is_possible_string){ 
			
			if( is_punctuator(string[i]) || is_operator(string[i])|| isspace(string[i])) {
				//checking for keyword
				text[count]='\0';
				if( strlen(text)!=0 && !is_keyword(text)){
					if(isalpha(text[0])){
						printf("identifier is %s\n",text);
						ident++;
					}
					else{
						printf("invalid identifier\n");
						return 0;
					}
				}	
				strcpy(text,"");
				count=0;	
			}
		
			else if(isalnum(string[i]) ||string[i]=='_'){
				text[count++]=string[i];
			}
	}
	printf("keywords are   %d \n",keyw);
 	printf("operators are  %d \n",opt);
	printf("identifiers  are %d \n",ident);
	printf("punctuators  are %d \n",punct);
	printf("constants are %d \n",constants);
 }
	







/*               		if(string[i]>=97 && string[i]<=122)
                      		text[count++]=string[i];
			else{
				text[count+1]='\0';
				REP(j,KEYWORD_COUNT){
					if(strcmp(text,keyword[i])==0){
						keyw++;
						flag=1;
						printf("keyword is %s ",text);
						count=0;
						text="";
					}
				}
				
				if(flag==0 && (  (string[i] >=65 && string[i]<=90) || (string[i]>=48 && string[i]<=57) ||string[i]==95 ) )
			}
                
  */              
            




                
