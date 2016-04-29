%{
#include<stdio.h>
struct Tree
{
        char *data;
        struct Tree *left,*right;
};
%}

%token number
%%
S:E {$$=$1;inorder($$); }
 ;
E:E '+' T { $$=makeNode($1,"+",$3); }
 |T       { $$=$1; }
 ;
T:T '*' F { $$=makeNode($1,"*",$3); }
 |F       { $$=$1;}
 ;
F:number { char *s=(char*)malloc(10);
           sprintf(s,"%d",$1);
           $$=makeNode(NULL,s,NULL);
        }
 |'(' E ')' { $$=$2;}
 ;
%%
int main()
{
        printf("Enter Expression : \n");
        yyparse();
}

yyerror()
{
 printf("Error\n");
}
struct Tree *makeNode(struct Tree *left,char *data,struct Tree *right)
{
        struct  Tree *t=(struct Tree*)malloc(sizeof(struct Tree));
        t->data=data;
        t->left=left;
        t->right=right;
        return t;
}
void inorder(struct Tree *t)
{
        if(t==NULL)
        return;
        inorder(t->left);
        printf("Node : %s\n",t->data);
        inorder(t->right);
 }
