#include <bits/stdc++.h>
#define MAX 128
using namespace std;
/**
 * @author Rajmani Arya
 * roll no. 137146, CSE SEC 'A'
 * Title - CYK algorithm implementation
 * @see https://en.wikipedia.org/wiki/CYK_algorithm
 * -------input format-----
 * S-AB|BC
 * A-BA|a
 * B-CC|b
 * C-AB|a
 */

int findIndex(vector<string> vec, const char c) {
	string str="";
	str += c;
	for(int i=0; i<vec.size(); i++) {
		if(str.compare(vec[i]) == 0)
			return i;
	}
	return -1;
}

int main(int argc, char * argv[]) {
	map<string, vector<string> > terminals;
	map<string, vector<string> > productions;
	vector<string> variables;
	fstream file("input.txt", ios::in);
	string buf;
	while(getline(file, buf)) {
		int x = buf.find("-");
		vector<string> term, prod;
		string _var = buf.substr(0,x);
		buf = buf.substr(x+1);
		stringstream ss(buf);
		while(getline(ss, buf, '|')) {
			if( buf[0] >= 'a' && buf[0] <= 'z')
				term.push_back(buf);
			else
				prod.push_back(buf);
		}
		terminals.insert(pair<string, vector<string> > (_var, term));
		productions.insert(pair<string, vector<string> > (_var, prod));
		variables.push_back(_var);
	}
	map<string, vector<string> >::iterator it;

	file.close();
	//string word = "baaba";
	string word;
    getline(cin,word);
    int n = word.size();
	int p = variables.size();

	bool P[n][n][p];
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			for(int k=0; k<p; k++)
				P[i][j][k] = false;

	for(int i=0; i<n; i++) {
		for(int j=0; j<p; j++) {
			if(findIndex(terminals.find(variables[j])->second, word[i]) != -1) {
				P[0][i][j] = true;
			}
		}
	}

	for(int i=1; i<n; i++) {
		for(int j=0; j<n-i; j++) {
			for(int k=0; k<i; k++) {
				for(it = productions.begin(); it != productions.end(); it++) {
					int indexA = findIndex(variables, it->first[0]);
					for (vector<string>::iterator itr = it->second.begin(); itr != it->second.end(); ++itr) {
						int indexB = findIndex(variables, (*itr)[0]);
						int indexC = findIndex(variables, (*itr)[1]);
						if(P[k][j][indexB] && P[i-k-1][j+k+1][indexC]) {
							P[i][j][indexA] = true;
						}
					}
				}
			}
		}
	}
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			for(int k=0; k<p; k++) {
				if(P[i][j][k])
					cout << variables[k];
				else
					cout << "*";
			}
			cout <<"  ";
		}
		cout <<"\n";
	}
	if (P[n-1][0][0] ){
		cout << word <<" is member of grammar\n";
	} else {
		cout << word << " is NOT a member of grammar\n";
	}
	return 0;
}
