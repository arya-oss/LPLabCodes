#include <bits/stdc++.h>
using namespace std;
/**
 * Title- Removal of Left Recursion from a grammar (immediate only)
 * Author: Rajmani Arya 
 */
void print_vector(vector<string> vec) {
	vector<string>::iterator it;
	for ( it = vec.begin(); it != vec.end(); ++it)
	{
		cout << *it << " ";		
	}
	cout << endl;
}

int main() {
    map<string, vector<string> > productions, new_prods; string _str, _key;
    int _start = 75; // 'K'
    fstream fin("grammar.txt", ios::in); size_t pos;
    vector<string> _tmp, _alpha, _beta;
    while(getline(fin, _str)) {
        pos = _str.find("-");
        _key = _str.substr(0, pos);
        _str = _str.substr(pos+1);
        while((pos=_str.find("|")) != string::npos) {
            _tmp.push_back(_str.substr(0, pos));
            _str = _str.substr(pos+1);
        }
        _tmp.push_back(_str);
        productions.insert(make_pair(_key, _tmp));
        _tmp.clear();
    }
    fin.close();
    map<string, vector<string> >::iterator m_it; string _prod;
    vector<string>::iterator v_it;
	for(m_it = productions.begin(); m_it != productions.end(); m_it++) {
	    for(v_it = m_it->second.begin(); v_it != m_it->second.end(); v_it++) {
	    	_prod = *v_it;
	        // cout << _prod << "\n";
	        if(_prod[0] == m_it->first[0]){
	        	_alpha.push_back(_prod.substr(1).append(1u,_start));
	        } else {
	        	_beta.push_back(_prod.append(1u,_start));
	        }

	    }
	    // print_vector(_alpha);
	    // print_vector(_beta);
	    // break;
	    if(_alpha.size() != 0) {
	    	_alpha.push_back(string(1u, '~'));
	    	new_prods.insert(make_pair(m_it->first, _beta));
	    	new_prods.insert(make_pair(string(1u, _start), _alpha));
	    }
	    else
	    	new_prods.insert(make_pair(m_it->first, m_it->second));
	    _start = _start+1;

	    _alpha.clear();
	    _beta.clear();
	}
    // cout << productions.size() << " " << new_prods.size() << "\n";
	for(m_it = new_prods.begin(); m_it != new_prods.end(); m_it++) {
	    cout << m_it->first << "-";
	    for(v_it = m_it->second.begin(); v_it != m_it->second.end(); v_it++) {
	        cout << *v_it << "|";
	    }
	    cout << "\n";
	}

    return 0;
}
/* grammar.txt
S-SAB|BA|abb
A-AB|a
B-CB|b
C-AC|c
*/
