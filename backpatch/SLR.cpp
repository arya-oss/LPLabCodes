/*
 *
 * SCcd
 * cd
 * S 3
 * S CC
 * C cC
 * C d
 *
 * */

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define set_item set<pair<char,string> > 

vector<string>V[1001];

set<set_item > C;
map<set_item,int> State;
char start;
set_item start_state;
int vis[100];
vector<char> Sym, nonTerminal;
map<pair<set_item,char>,set_item > gto;
map<char,int> SYM;
map<int,char> IM;
map<pair<char,string>,int> Prod;
map<int,pair<char,string> > Iprod;
set<char> null, Term, Follow[100],First[100];


struct entry{
	int action,state;
}Table[100][100];

char find_dot(string str)
{
    for(int i=0;i<str.length();i++)
    {
        if(str[i]=='.')
        {
            if(i+1==str.length())
                return '\0';
            else if(str[i+1]=='@')
                return '\0';
            else
                return str[i+1];
        }
    }
}

set_item closure(char left,string right)
{

    set_item S;
    char lhs;
    string rhs;
    queue<pair<char,string> >G;
    string temp;
    G.push(mp(left,right));
    char a;
    S.insert(mp(left,right));
    bool flag=true;
        while(!(G.empty()))
        {

            lhs=G.front().first;
            rhs=G.front().second;
            G.pop();
          
            a=find_dot(rhs);
            if(a=='\0')
            {
                continue;
            }
  
            for(int i=0;i<V[SYM[a]].size();i++)
            {
   
                if(S.find(mp(a,"."+V[SYM[a]][i]))==S.end())
                {
                    S.insert(mp(a,"."+V[SYM[a]][i]));
                    G.push(mp(a,"."+V[SYM[a]][i]));
                }
            }
         
        }
       
        return S;
}
set_item Goto(set_item I,char X)
{

    set_item L;
    char lhs;
    string rhs,temp;
    set<pair<char,string > >G;
    set_item res;
    set_item::iterator it=I.begin();
    for(;it!=I.end();it++)
    {
        lhs=it->first;
        rhs=it->second;
        for(int i=0;i<rhs.length();i++)
        {
            if(rhs[i]=='.')
            {
                if(i+1<rhs.length())
                {
                    if(rhs[i+1]=='@')
                        continue;
                    if(rhs[i+1]==X)
                    {
                    
                        temp=rhs.substr(0,i);
                        temp+=X;
                        temp=temp+".";
                        temp=temp+rhs.substr(i+2,rhs.length()-(i+2));
                      
                        res=closure(lhs,temp);
                        G.insert(res.begin(),res.end());
                          
                    }
                }
            }
        }
    }
  gto.insert(mp(mp(I,X),G));
  	return G;
}
void item()
{
    string temp=".";
    temp+=start;
 
    C.clear();
    set_item res;
    res=closure('Z',temp);
    
    start_state=res;
    queue<set<pair<char,string > > >T;
    C.insert(res);
    set_item res1;
    set<set_item >::iterator it1=C.begin();
    for(;it1!=C.end();it1++)
    T.push(*it1);
    while(!(T.empty()))
    {
    	res=T.front();
    	T.pop();
    	
        for(int i=0;i<Sym.size();i++)
        {
            res1=Goto(res,Sym[i]);
            if(res1.empty())
            continue;
            else if(C.find(res1)==C.end()){
            C.insert(res1);
            T.push(res1);
        	}
        }
    }
}
void compute(int a)
{
    vis[a]=1;
    char ch;
    set<char> temp;
    int i,j;
    for(i=0;i<V[a].size();i++)
    {
        for(j=0;j<=V[a][i].length();j++)
        {
            if(j==V[a][i].length())
            {
                First[a].insert('@');
                continue;
            }
            if(Term.find(V[a][i][j])!=Term.end()){
                First[a].insert(V[a][i][j]);
                break;
            }
            else{
                ch=V[a][i][j];
                if(vis[SYM[ch]]==0)
                {
                    compute(SYM[ch]);
                }
                temp.clear();
                temp.insert(First[SYM[ch]].begin(),First[SYM[ch]].end());
                temp.erase('@');
                    First[a].insert(temp.begin(),temp.end());
                    if(null.find(ch)!=null.end())
                        continue;
                    else
                        break;
            }
        }
    }
}
void follow(char ch)
{
    
    vis[SYM[ch]]=2;
    int i,j,l,r,p;
    for(p=0;p<nonTerminal.size();p++)
    {
        i=SYM[nonTerminal[p]];
        for(j=0;j<V[i].size();j++)
        {
            for(l=0;l<V[i][j].length();l++)
            {
                if(V[i][j][l]==ch)
                {
                    if(l+1==V[i][j].length())
                    {
                        if(vis[i]==1)
                        {
                            follow(IM[i]);
                        }
                            Follow[SYM[ch]].insert(Follow[i].begin(),Follow[i].end());
                    }
                    else
                    {
                        for(r=l+1;r<=V[i][j].length();r++)
                        {
                            if(r==V[i][j].length())
                            {
                                if(vis[i]==1)
                                    follow(IM[i]);
                                Follow[SYM[ch]].insert(Follow[i].begin(),Follow[i].end());
                                break;
                            }
                            if(Term.find(V[i][j][r])!=Term.end()){
                                Follow[SYM[ch]].insert(V[i][j][r]);
                                break;
                            }
                            else
                            Follow[SYM[ch]].insert(First[SYM[V[i][j][r]]].begin(),First[SYM[V[i][j][r]]].end());
                            if(null.find(V[i][j][r])!=null.end())
                            {
                                continue;
                            }
                            else
                                break;
                        }
                    }
                }
            }
        }
    }
}

void First_follow()
{
    int i,j,p;
    for(i=0;i<Sym.size();i++)
    {
        if(Term.find(Sym[i])==Term.end())
            nonTerminal.pb(Sym[i]);
    }
    for(i=0;i<nonTerminal.size();i++)
    {
        for(j=0;j<V[SYM[nonTerminal[i]]].size();j++)
        {
            if(Term.find(V[SYM[nonTerminal[i]]][ j][0])!=Term.end())
            {
                First[SYM[nonTerminal[i]]].insert(V[SYM[nonTerminal[i]]][j][0]);
            }
        }
    }
    memset(vis,0,sizeof(vis));
    for(i=0;i<nonTerminal.size();i++)
    {
        if(vis[SYM[nonTerminal[i]]]==0)
        {
            compute(SYM[nonTerminal[i]]);
        }
    }
    map<char,int>::iterator itr=SYM.begin();
    cout<<"First set: \n";
    for(;itr!=SYM.end();itr++)
    {
        cout<<itr->first<<" { ";
        set<char>::iterator it=First[itr->second].begin();
        for(;it!=First[itr->second].end();it++)
            cout<<*it<<",";
        cout<<" }"<<endl;
    }
    cout<<"Follow set: "<<endl;
    Follow[SYM[start]].insert('$');
    follow(start);
    itr=SYM.begin();
    for(;itr!=SYM.end();itr++)
    {
        if(Term.find(itr->first)!=Term.end())
            continue;
        if(vis[itr->second]==2)
            continue;
        else
            follow(itr->first);
    }
    for(p=0;p<nonTerminal.size();p++)
    {
        i=SYM[nonTerminal[p]];
        cout<<nonTerminal[p]<<": { ";
        Follow[i].erase('@');
        set<char>::iterator it2=Follow[i].begin();
        for(;it2!=Follow[i].end();it2++)
            cout<<*it2<<",";
        cout<<" }"<<endl;
    }
}
string remove_dot(string str)
{
    string temp="";
    for(int i=0;i<str.length();i++)
    {
        if(str[i]=='.')
            continue;
        temp+=str[i];
    }
    return temp;
}
int main()
{
    char sym;
    int n,i,j;
    char ch;
    string str;
    cout<<"Enter the string of symbols used: ";
    cin>>str;
    for(i=0;i<str.length();i++){
        Sym.pb(str[i]);
        SYM.insert(mp(str[i],i));
        IM.insert(mp(str[i],ch));
    }
    SYM.insert(mp('$',i));
    SYM.insert(mp('@',i+1));
    IM.insert(mp(i,'$'));
    IM.insert(mp(i+1,'@'));
    cout<<"Enter the string of terminals: ";
    First[SYM['@']].insert('@');
    Term.insert('@');
    cin>>str;
    for(i=0;i<str.length();i++){
        First[SYM[str[i]]].insert(str[i]);
        Term.insert(str[i]);
    }
    cout<<"Enter the start symbol: ";
    cin>>start;
    cout<<"Enter number of productions: ";
    cin>>n;
    cout<<"Enter productions: \n";
    for(i=0; i<n; i++){
        cin>>sym;
        cin>>str;
        Prod.insert(mp(mp(sym,str),i));
         Iprod.insert(mp(i,mp(sym,str)));
        V[SYM[sym]].pb(str);
        if(str=="@")
            null.insert(sym);
    }
    item();
    First_follow();
    set<set_item >::iterator it=C.begin();
    int no_state=0;
    set_item T;
    cout<<"Item sets: \n";
    for(;it!=C.end();it++)
    {
       T=*it;
       State.insert(mp(T,no_state));
       set_item::iterator itr=T.begin();
        cout<<"Item "<<no_state+1<<": {";
        for(;itr!=T.end();itr++)
        {
            cout<<itr->first<<"->"<<itr->second<<"; ";
        }
        no_state++;
        cout<<" }\n";
    }
    for(i=0;i<no_state;i++)
    {
    	map<int,char>::iterator it3=IM.begin();
    	for(;it3!=IM.end();it3++){
    		Table[i][it3->first].action=-1;
    	}
    }
    cout<<"Table initialised"<<endl;
     it=C.begin();
    set_item res;
    i=0;
    string zod="";
    zod+=start;
    zod=zod+".";
    char a;
    for(;it!=C.end();it++,i++)
    {
    	T=*it;
    	set_item::iterator itr=T.begin();
        for(;itr!=T.end();itr++)
        {
        	if(itr->first=='Z'&&itr->second==zod){
                    if(Table[i][SYM['$']].action>0)
                    {
                        cout<<"Error Not a SLR gRammar";
                        return 0;
                    }
        		Table[i][SYM['$']].action=3;
        		continue;
        	}
            a=find_dot(itr->second);
            if(a=='\0')
            {
                    set<char>::iterator it5=Follow[SYM[itr->first]].begin();
            	for(;it5!=Follow[SYM[itr->first]].end();it5++)
            	{
            	    if(Table[i][SYM[*it5]].action>0)
                    {
                        cout<<"Error Not a SLR gRammar";
                        return 0;
                    }
            		Table[i][SYM[(*it5)]].action=2;
            		Table[i][SYM[(*it5)]].state=Prod[mp(itr->first,remove_dot(itr->second))];
            	}
            	continue;
            }
            j=State[gto[mp(T,a)]];
            if(Table[i][SYM[a]].action>0)
                    {
                        cout<<"Error Not a SLR gRammar";
                        return 0;
                    }
            Table[i][SYM[a]].action=1;
            Table[i][SYM[a]].state=j;
        }
    }
    cout<<"Enter the string to be parsed: ";
    cin>>str;
    str=str+"$";
    stack<int>S;
    cout<<"Pushed "<<State[start_state]<<endl;
    S.push(State[start_state]);  
    int stop,z;
    i=0;
    while(true)
    {
    	stop=S.top();
    	ch=str[i];
    	if(Table[stop][SYM[ch]].action==1)
    	{
    	    cout<<"Shift "<<ch<<" "<<Table[stop][SYM[ch]].state<<endl;
    		S.push(SYM[ch]);
    		S.push(Table[stop][SYM[ch]].state);
    		i++;
    	}
    	else if(Table[stop][SYM[ch]].action==2)
    	{
    		z=Table[stop][SYM[ch]].state;
    		cout<<"Reduce "<<Iprod[z].first<<" -> "<<Iprod[z].second<<endl;;
    		int len=2*(Iprod[z].second.length());
    		while(len>0)
    		{
    			S.pop();
    			len--;
    		}
    		stop=S.top();
    		S.push(SYM[Iprod[z].first]);
    		S.push(Table[stop][SYM[Iprod[z].first]].state);
    	}
    	else if(Table[stop][SYM[ch]].action==3)
    	{
    		cout<<"String is accepted! \n";
    		return 0;
    	}
    	else
    		{
    			cout<<"String is not accepted\n";
    			return 0;
    		}
    }
}
/*
 * 8
 * E T * + ( ) i F
 * 5 + * i ( )
 * E 6
 * E E+T
 * E  T
 * T T*F
 * T F
 * F (E)
 * F i
 *
 * 6
 * S L R = * i
 * 3 = * i
 * S 5
 * S L=R
 * S R
 * L *R
 * L i
 * R L
 * */

