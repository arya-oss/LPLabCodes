#include <bits/stdc++.h>
using namespace std;

/**
 * Title - Lef factoring a grammar
 * Author: Rajmani Arya
 * Date: 30 Jan, 2016
 * ---------------------------------
 * Input format
 * =================================
 *  S-iE+S|iE+SeS|a
 *  E-b
 * ---------------------------------
 */

bool isLowerCase(const string str) {
	for(int i=0; i<str.length(); i++)
		if(!islower(str[i]))
			return false;
	return true;
}

int main(){
	map<char, vector<string> > term, prods;
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
			if(isLowerCase(_tok))
				_vec2.push_back(_tok);
			else
				_vec1.push_back(_tok);
		}
		if(isLowerCase(_tmp))
			_vec2.push_back(_tmp);
		else
			_vec1.push_back(_tmp);

		term.insert(make_pair(sym, _vec2));
		prods.insert(make_pair(sym, _vec1));
		_vec1.clear();
		_vec2.clear();
	}
	fin.close();
	int v_size = var.size();
	map<char, vector<string> >::iterator it;
	vector<string> tvec;
	vector<char>::iterator i;
	vector<string>::iterator i1,i2;
	char new_var = 'K';
	for(i = var.begin(); i != var.end(); i++) {
		tvec = prods[*i];
		if(tvec.size() <= 1) continue;
		int flag=0,k=0; string _prefix="";
		while(1) {
			_prefix += tvec[0][k];
			for(i2 = tvec.begin()+1; i2 != tvec.end(); i2++) {
				if((*i2)[k] != _prefix[k]){
					flag = 1;
					break;
				}
			}
			if(flag) {
				_prefix = _prefix.substr(0, _prefix.length()-1);
				break;
			}
			k++;
		}
		prods[*i].clear();
		_prefix+=new_var;
		prods[*i].push_back(_prefix);
		for(int j=0; j<tvec.size(); j++) {
			if(tvec[j].length() != k)
				tvec[j].replace(0, 4, "");
			else
				tvec[j]="~";
		}
		prods.insert(make_pair(new_var, tvec));
		tvec.clear();
		new_var = new_var+1;
		//cout << "k = " << k << " " << _prefix << "\n";
	}
	for(it=prods.begin(); it != prods.end(); it++) {
		cout << it->first << "-";
		for (i1 = it->second.begin(); i1 != it->second.end(); ++i1)
		{
			cout << *i1 <<"|";
		}
		cout << endl;
	}
	return 0;
}
