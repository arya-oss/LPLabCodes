#include <bits/stdc++.h>
#define MAX_CODE_LENGTH 1024

using namespace std;

char keys[25][10] = {"main","int","float","char","double","if","else","for","while","do","goto","return","break",
    "continue","switch","case","default","long","struct","typedef","static","register","unsigned","void","sizeof"};
char ops[11] = { '-', '+', '*', '/', '%', '=', '!', '&', '|', '<', '>' };
    

class LexicalAnalyser {
private:
    char * code;
    set<char *> keywords, numbers, identifiers;
    set<char> operators, delimeters;

    bool is_blank(int in);
    int skip_blank(int index);
    bool is_keyword(char * word);
    bool is_operator(char opr);
    bool is_delimeter(char ch);
    void init();
public:
    LexicalAnalyser(char code[]){
        this->code = code;
    }
    void do_lex();
    void print_keys(){
    	set<char *>::iterator it;
    	cout << "keywords : ";
    	for (it = keywords.begin(); it != keywords.end(); ++it)
    	{
    		cout << *it << ", ";
    	}
    	cout << "\n";
    }
    void print_ops() {
    	set<char>::iterator it;
    	cout << "operators : ";
    	for (it = operators.begin(); it != operators.end(); ++it)
    	{
    		cout << *it << ", ";
    	}
    	cout << "\n";
    }
    void print_dels() {
    	set<char>::iterator it;
    	cout << "delimeters : ";
    	for (it = delimeters.begin(); it != delimeters.end(); ++it)
    	{
    		cout << *it << ", ";
    	}
    	cout << "\n";
    }
    void print_nums() {
    	set<char *>::iterator it;
    	cout << "numbers : ";
    	for (it = numbers.begin(); it != numbers.end(); ++it)
    	{
    		cout << *it << ", ";
    	}
    	cout << "\n";
    }
    void print_ids() {
    	set<char *>::iterator it;
    	cout << "identifiers : ";
    	for (it = identifiers.begin(); it != identifiers.end(); ++it)
    	{
    		cout << *it << ", ";
    	}
    	cout << "\n";
    }
};

bool LexicalAnalyser::is_blank(int in){
    return code[in] == ' ' or code[in] == '\n' or code[in] == '\r' or code[in] == '\t';
}

int LexicalAnalyser::skip_blank(int index) {
    while(index < strlen(code) && is_blank(index))
        index++;
    return index;
}

bool LexicalAnalyser::is_keyword(char * word){
	for (int i = 0; i < 25; ++i)
	{
		if(strcmp(word, keys[i]) == 0)
			return true;
	}
	return false;
}

bool LexicalAnalyser::is_operator(char opr) {
	for(int i=0; i<11; i++){
		if(ops[i] == opr)
			return true;
	}
	return false;
}

bool LexicalAnalyser::is_delimeter(char ch) {
    return ch == ',' or ch == ';' or ch == '{' or ch == '[' or ch == ']' or ch == '\''
        or ch == '}' or ch == '(' or ch == ')' or ch == '"' or ch == '#';
}

void LexicalAnalyser::do_lex(){
    char tok[128]; int t=0; char ch;
    for(int i=0; i<strlen(code); i++) {
        i = skip_blank(i);
        if(code[i] == '#'){
            delimeters.insert('#');
            i=skip_blank(i);
            if(is_delimeter(i)){
            	ch = code[i];
            	delimeters.insert(code[i]);
            }
            if(ch == '"') {
            	t=0;
            	while(code[i] != '"')
            		tok[t++] = code[i++];
            	tok[t] = '\0';
            	identifiers.insert(tok);
            	cout << "Identifiers: " << tok << "\n";
            } else if( ch == '<') {
            	t=0;
            	while(code[i] != '>')
            		tok[t++] = code[i++];
            	tok[t] = '\0';
            	identifiers.insert(tok);
            	cout << "Identifiers: " << tok << "\n";
            }
            if(is_delimeter(i)){
            	delimeters.insert(code[i++]);
            }
        }
        if(isalpha(code[i]) || code[i] == '_') {
        	t=0;
        	while(isalpha(code[i]) || isdigit(code[i]) || code[i] == '_') {
        		tok[t++] = code[i++];
        	}
        	tok[t] = '\0';
        	if(is_keyword(tok)) {
        		cout << "keywords : " << tok << "\n";
        		keywords.insert(tok);
        	} else {
        		cout << "Identifiers: " << tok << "\n";
        		identifiers.insert(tok);
        	}
        	//cout << tok << "i\n";
        }
        if(isdigit(code[i])) {
        	t=0;
        	while(isdigit(code[i]) || code[i] == '.'){
        		tok[t++] = code[i++];
        	}
        	tok[t] = '\0';
        	numbers.insert(tok);
        	cout <<"Numbers : " << tok << "\n";
        }
        if(is_delimeter(code[i])) {
        	delimeters.insert(code[i]);
        }
        if(is_operator(code[i])) {
        	operators.insert(code[i]);
        }
    }
}

int main(int argc, char const *argv[])
{
	fstream fin; char buf[MAX_CODE_LENGTH];
	memset(buf, MAX_CODE_LENGTH, '\0');
	char tmp[128];
	fin.open("code.c", ios::in);
	fin.getline(buf, 128);
	while(fin.getline(tmp, 128)) {
		strcat(buf, tmp);
	}
	//printf("%s\n", buf);
	fin.close();
	LexicalAnalyser lex(buf);
	lex.do_lex();
	//lex.print_keys();
	//lex.print_ids();
	//lex.print_nums();
	lex.print_ops();
	lex.print_dels();
	return 0;
}