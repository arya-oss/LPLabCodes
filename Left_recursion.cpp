#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

int main()
{
	map<char, vector<string> > term, non_term;
	vector<string> _vec1, _vec2; char sym;
	vector<char> var; string _tmp, _tok; size_t pos;
	fstream fin;
	fin.open("input.txt", ios::in);
	while(getline(fin, _tmp)) {
		pos = _tmp.find("-");
		_tok = _tmp.substr(0, pos);
		_tmp = _tmp.substr(pos+1);
		sym = _tok[0];
		var.push_back(sym);
		while((pos = _tmp.find("|")) != string::npos) {
			_tok = _tmp.substr(0, pos);
			_tmp = _tmp.substr(pos+1);
			if(islower(_tok[0]))
				_vec2.push_back(_tok);
			else
				_vec1.push_back(_tok);
		}
		if(islower(_tmp[0]))
			_vec2.push_back(_tmp);
		else
			_vec1.push_back(_tmp);

		term.insert(make_pair(sym, _vec2));
		non_term.insert(make_pair(sym, _vec1));
		_vec1.clear();
		_vec2.clear();
	}
	fin.close();
	int v_size = var.size();
	map<char, vector<string> >::iterator it;
	vector<string> tvec;
	vector<string>::iterator i1,i2;
	for(i1=var.begin(); i1!=var.end(); i1++) {
		tvec = non_term[i1];
//		for(i2 = tvec.begin(); i2 != tvec.end(); i2++) {
//
//		}
		while(tvec[0] != *it && v_size != 0) {

		}
	}
	return 0;
}
