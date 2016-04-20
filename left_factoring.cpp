#include <bits/stdc++.h>
using namespace std;

#define mapvec map<string, vector <string> >

mapvec prods, new_prods;
vector<string> alpha, beta;
int non_terms = 75;

void factor (string key) {
	mapvec::iterator mit = prods.find(key);
	if (mit == prods.end() || mit->second.size() <= 1) {
		new_prods.insert(make_pair(mit->first, mit->second));
		return;  // No need of factoring NonTerm having one or less production
	}

	std::vector<string> v = mit->second;
	int match=0, index, max, total; string prefix;
	
	for (int i = 0; i < v.size(); ++i)
	{
		for (int j = i+1; j < v.size(); ++j)
		{
			index = 0; max = min(v[i].size(), v[j].size());
			while (index <= max && v[i][index] == v[j][index]) {
				index++;
			}
			if(index > match) {
				prefix = v[i].substr(0, index);
				match = index;
			}
		}
	}
	
	if (match == 0) {
		// cout << "No prefix, no factoring.\n";
		new_prods.insert(make_pair(mit->first, mit->second));
		return;
	} else {
		alpha.clear();
		beta.clear();
		// cout << " Prefix " << prefix << "\n";
		beta.push_back(prefix+string(1,(char)non_terms)); // factored to one
		for (int i = 0; i < v.size(); ++i) {
			if (v[i].compare(0, match, prefix) != 0) {
				beta.push_back(v[i]);
			} else {
				if(v[i].size()  != prefix.size())
					alpha.push_back(v[i].substr(match));
			}
		}
		alpha.push_back("~"); // for epsilon production
	}

	new_prods.insert(make_pair(mit->first, beta));
	new_prods.insert(make_pair(string(1, (char)non_terms), alpha));
	non_terms++;
}

void print_map(mapvec m) {
	mapvec::iterator mit;
	for ( mit = m.begin(); mit != m.end(); ++mit)
	{
		for (vector<string>::iterator i = mit->second.begin(); i != mit->second.end(); ++i)
		{
			cout << mit->first << "->" << *i << "\n";			
		}
	}
}

bool map_compare(mapvec & lhs, mapvec & rhs) {
	if(lhs.size() != rhs.size())
		return false;
	mapvec::iterator mit, mit1;
	for ( mit = lhs.begin(); mit != lhs.end(); ++mit)
	{
		
		mit1 = rhs.find(mit->first);
		if (mit1 == rhs.end() || mit->second.size() != mit1->second.size())
			return false;

		for (vector<string>::iterator i = mit->second.begin(); i != mit->second.end(); ++i) {
			if (find(mit1->second.begin(), mit1->second.end(), *i) == mit1->second.end())
				return false;
		}
	}
	return true;
}

int main(int argc, char const *argv[])
{
	string _str, _key;
	mapvec::iterator mit;
	fstream fin("factor.txt", ios::in);
	while(getline(fin, _str)) {
		ssize_t pos = _str.find("-");
		_key = _str.substr(0, pos);
		_str = _str.substr(pos+1);
		if ( (mit = prods.find(_key)) == prods.end()) {
			std::vector<string> v;
			v.push_back(_str);
			prods.insert(make_pair(_key, v));
		} else {
			mit->second.push_back(_str);
		}
	}
	fin.close();

	print_map(prods);

	while(1) {
		for ( mit = prods.begin(); mit != prods.end(); ++mit) {
			factor(mit->first);
		}
		if (map_compare(prods, new_prods))
			break;
		prods.clear();
		prods = new_prods;
		new_prods.clear();
	}
	cout << "\nLeft factored grammar \n";
	print_map(new_prods);

	return 0;
}

/** 
 * --- factor.txt ----
 * S-iEtS
 * S-iEtSeS
 * S-ab
 * S-abcd
 * E-b
 */
