#include <bits/stdc++.h>

using namespace std;

int main() {
    map<string, vector<string> > G; vector<string> vec;
    fstream file("inputG.txt", ios::in);
    string str, tmp; size_t pos;
    while(getline(file, str)){
        pos = str.find("-");
        tmp = str.substr(0,pos);
        str = str.substr(pos+1);
        
        while((pos = str.find("|")) != string::npos) {
            tmp = str.substr(0,pos);
            //cout << tmp << ",";
            vec.push_back(tmp);
            str = str.substr(pos+1);
        }
        if(str.length()!=0) {
            vec.push_back(str);
        }
        G.insert(make_pair(tmp, vec));
        vec.clear();
    }
    file.close();
    map<string, vector<string> > :: iterator im;
    for(im = G.begin(); im != G.end(); im++) {
        cout << im->first << "\n";
    }
    return 0;
}
