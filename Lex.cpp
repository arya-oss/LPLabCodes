#include <bits/stdc++.h>
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
}
