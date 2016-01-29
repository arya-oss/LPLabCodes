#include <bits/stdc++.h>
<<<<<<< HEAD
#define MAX 1024
using namespace std;

class LexAnalyse{
    private:
        set<string> keywords("main", "int", "float", "double", "if", "else", "continie", "break", "for", 
            "while", "do", "switch", "case", "default", "struct", "typedef", "char", "long", "return");
            set<string> operators("-","+","*","/", "%", "|", "&", "^", "-=", "+=", "*=", "/=", "%=", "--", "++", "==", "!=", "<", ">", ">>", "<<", "<=", ">=");
                set<string> delimeters("(", ")", "{", "}", "[", "]", ";", "\"", "\'", ":", ",");
                    bool is_keyword(string tok) {
                                return find(keywords.begin(), keywords.end(), tok) != keywords.end();
                                    }
                                        bool is_operator(string tok) {
                                                    return find(operators.begin(), operators.end(), tok) != operators.end();
                                                        }
                                                            bool is_delimeter(string tok) {
                                                                        return find(delimeters.begin(), delimeters.end(), tok) != delimeters.end();
                                                                            }
                                                                                bool is_literal(string tok) {
                                                                                            if(tok[0] < 48 || tok[0] > 57)
                                                                                                            return (tok[0] == "\"" && tok[tok.length()-1] == "\"") || (tok[0] == "'" && tok[tok.length()-1] == "'");
                                                                                                                    else {
                                                                                                                                    bool flag=true;
                                                                                                                                                for(int i=0; i<tok.length(); i++) {
                                                                                                                                                                    if(tok[i] < 48 && tok > 57){
                                                                                                                                                                                            if(tok[i] == '.' && flag){
                                                                                                                                                                                                                        flag = false;
                                                                                                                                                                                                                                            } else
                                                                                                                                                                                                                                                                    return false;
                                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                                                            return true;
                                                                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                                                                            set<string> keys, oprs, dels, lits;
                                                                                                                                                                                                                                                                                                                                string code;
                                                                                                                                                                                                                                                                                                                                    public:
                                                                                                                                                                                                                                                                                                                                            LexAnalyse(string code) {
                                                                                                                                                                                                                                                                                                                                                            this->code = code;
                                                                                                                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                                                                                                                            void do_lex(){
                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                                    }
};

int main(int argc, char * argv[]) {

        return 0;
=======
#define MAX_CODE_LENGTH 1024

using namespace std;

/**
 * Title - Lexical Analyser for C language, Implemented in C++
 *
 * Author:  Rajmani Arya, CSE NITW 3rd Year.
 * Date: 22 Jan, 2016
 */


char keys[25][10] = {"main","int","float","char","double","if","else","for","while","do","goto","return","break",
    "continue","switch","case","default","long","struct","typedef","static","register","unsigned","void","sizeof"};
char ops[11] = { '-', '+', '*', '/', '%', '=', '!', '&', '|', '<', '>' };


class LexicalAnalyser {
private:
    char * code;
    set<string> keywords, numbers, identifiers;
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
    	set<string>::iterator it;
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
    	set<string>::iterator it;
    	cout << "Literals : ";
    	for (it = numbers.begin(); it != numbers.end(); ++it)
    	{
    		cout << *it << ", ";
    	}
    	cout << "\n";
    }
    void print_ids() {
    	set<string>::iterator it;
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
            i++;
            i=skip_blank(i);
            t = 0;
            while(!(code[i] == ' ' || code[i] == '"' || code[i]=='<')){
                tok[t++] = code[i++];
            }
            tok[t] = '\0';
            identifiers.insert(string(tok));
            i = skip_blank(i);
            if(is_delimeter(i)){
            	ch = code[i];
            	delimeters.insert(code[i]);
            }
            if(code[i] == '"') {
            	t=0; i++;
            	while(code[i] != '"')
            		tok[t++] = code[i++];
            	tok[t] = '\0';
            	identifiers.insert(string(tok));
            } else if( code[i] == '<') {
            	t=0; i++;
            	while(code[i] != '>')
            		tok[t++] = code[i++];
            	tok[t] = '\0';
            	delimeters.insert('>');
            	identifiers.insert(string(tok));
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
        		keywords.insert(string(tok));
        	} else {
        		identifiers.insert(string(tok));
        	}
        	//cout << tok << "i\n";
        }
        if(isdigit(code[i])) {
        	t=0;
        	while(isdigit(code[i]) || code[i] == '.'){
        		tok[t++] = code[i++];
        	}
        	tok[t] = '\0';
        	numbers.insert(string(tok));
        }
        if(code[i] == '"') {
            t=0;
            tok[t++] = code[i++];
            while(code[i] != '"') {
                tok[t++] = code[i++];
            }
            tok[t++] = code[i++];
            tok[t] = '\0';
            numbers.insert(string(tok));
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

	fin.close();
	LexicalAnalyser lex(buf);
	lex.do_lex();
	lex.print_keys();
	lex.print_ids();
	lex.print_nums();
	lex.print_ops();
	lex.print_dels();
	return 0;
>>>>>>> 937f782647bf434c943b92213eaa9420de5beda4
}
