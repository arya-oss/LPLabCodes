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

typedef pair< pair<char,string>,char> LR;
#define lhs first.first
#define rhs first.second
#define lhd second
#define mp make_pair
#define pb push_back
#define itemSet set< LR >
#define item_it set< LR >::iterator

vector<string> V[1001];
vector<char> Sym, NONT;
map<itemSet, int> State, Cstate;
map<int, itemSet> Istate;
int vis[100], no_state;
map<char,int> SYM;
map<int,char> IM;
itemSet start_state;
map<set<pair<char,string> >,vector<int> > LALR;
map<pair<itemSet,char>,itemSet > gto;
map<pair<char,string>, int> Prod;
map<int, pair<char,string> > Iprod;
set<char> follow[100], first[100], null, terminals;
set< itemSet > C;
map<int, int> IU, U;


char start;

struct entry{
	int action,state;
}Table[100][100];

void print(itemSet R)
{
	cout<<"\n{"<<endl;
	itemSet::iterator it=R.begin();
	for(;it!=R.end();it++)
		cout<<it->lhs<<"->"<<it->rhs<<","<<it->lhd<<"; ";
	cout<<"}\n"<<endl;
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
                first[a].insert('@');
                continue;
            }
            if(terminals.find(V[a][i][j])!=terminals.end()){
                first[a].insert(V[a][i][j]);
                break;
            }
            else{
                ch=V[a][i][j];
                if(vis[SYM[ch]]==0)
                {
                    compute(SYM[ch]);
                }
                temp.clear();
                temp.insert(first[SYM[ch]].begin(),first[SYM[ch]].end());
                temp.erase('@');
                    first[a].insert(temp.begin(),temp.end());
                    if(null.find(ch)!=null.end())
                        continue;
                    else
                        break;
            }
        }
    }
}
set<char> Find_first(string str)
{
    set<char>T;
    if(str=="")
        T.insert('@');
    if(str=="$")
        T.insert('$');
    else
    {
        T.insert(first[SYM[str[0]]].begin(),first[SYM[str[0]]].end());
    }
    return T;
}
void make_LR(LR & item,char lhs1,string rhs1,char lhd1)
{
    item.lhs=lhs1;
    item.rhs=rhs1;
    item.lhd=lhd1;
}
itemSet Closure(itemSet I)
{
    
    itemSet S;
    LR item;
    queue<LR>Q;
    set<char>F;
    set<char>::iterator it2;
    item_it itr=I.begin();
    for(;itr!=I.end();itr++)
    {
        S.insert(*itr);
        Q.push(*itr);
    }
    int a,i;
    string t;
    LR t3;
    int t2;
    while(!(Q.empty()))
    {
        item=Q.front();
        Q.pop();
        a=1+item.rhs.find('.');
     
        if(a==item.rhs.length())
            continue;
        else if(terminals.find(item.rhs[a])!=terminals.end())
            continue;
        else{
            t=item.rhs.substr(a+1,item.rhs.length()-a-1);
            t+=item.lhd;
            
            F=Find_first(t);
            t2=SYM[item.rhs[a]];
            it2=F.begin();
            for(i=0;i<V[t2].size();i++)
            {
                it2=F.begin();
                for(;it2!=F.end();it2++)
                {
                    make_LR(t3,item.rhs[a],"."+V[t2][i],*it2);
                    if(S.find(t3)==S.end())
                    {
                        S.insert(t3);
                        Q.push(t3);
                    }
                }
            }
        }
    }
   
    return S;
}
string shift_Dot(string rhs1)
{
    int p=rhs1.find('.')+1;
    if(p==rhs1.length())
        return rhs1;
    string temp;
    temp=rhs1.substr(0,p-1);
    temp+=rhs1[p];
    temp+=".";
    temp+=rhs1.substr(p+1,rhs1.length()-p-1);
    return temp;
}
itemSet Goto(itemSet I,char ch)
{
    int a;
    itemSet S;
    item_it it=I.begin();
    LR t3;
    for(;it!=I.end();it++)
    {
        a=(*it).rhs.find('.')+1;
        if((*it).rhs[a]==ch){
        make_LR(t3,(*it).lhs,shift_Dot((*it).rhs),(*it).lhd);
        S.insert(t3);
        }
    }
    
    S=Closure(S);
    gto.insert(mp(mp(I,ch),S));
    return S;
}
void item()
{
    itemSet T;
    queue<itemSet>Q;
    itemSet item;
    LR t3;
    string t1=".";
    t1+=start;
    make_LR(t3,'Z',t1,'$');
    T.insert(t3);
    T=Closure(T);
    print(T);
    start_state=T;
    C.insert(T);
    int i;
    Q.push(T);
    while(!(Q.empty()))
    {
        item=Q.front();
        Q.pop();
        for(i=0;i<Sym.size();i++)
        {
            T=Goto(item,Sym[i]);
            if((!(T.empty()))&&C.find(T)==C.end())
            {
                C.insert(T);
                Q.push(T);
            }
        }
    }
}
void first_com()
{
    int i,j,p;
    for(i=0;i<Sym.size();i++)
    {
        if(terminals.find(Sym[i])==terminals.end())
            NONT.pb(Sym[i]);
    }
    for(i=0;i<NONT.size();i++)
    {
        for(j=0;j<V[SYM[NONT[i]]].size();j++)
        {
            if(terminals.find(V[SYM[NONT[i]]][ j][0])!=terminals.end())
            {
                first[SYM[NONT[i]]].insert(V[SYM[NONT[i]]][j][0]);
            }
        }
    }
    memset(vis,0,sizeof(vis));
    for(i=0;i<NONT.size();i++)
    {
        if(vis[SYM[NONT[i]]]==0)
        {
            compute(SYM[NONT[i]]);
        }
    }
    map<char,int>::iterator itr=SYM.begin();
    cout<<"First set: \n";
    for(;itr!=SYM.end();itr++)
    {
        cout<<itr->first<<" { ";
        set<char>::iterator it=first[itr->second].begin();
        for(;it!=first[itr->second].end();it++)
            cout<<*it<<",";
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
    cout<<"Enter the string of symbols: ";
    cin>>str;
    for(i=0;i<str.length();i++){
        Sym.pb(str[i]);
        SYM.insert(mp(str[i],i));
        IM.insert(mp(i,str[i]));
    }
    SYM.insert(mp('$',i));
    SYM.insert(mp('@',i+1));
    IM.insert(mp(i,'$'));
    IM.insert(mp(i+1,'@'));
    
    cout<<"Enter the string of terminals: ";
    cin>>str;
    first[SYM['@']].insert('@');
    terminals.insert('@');
    for(i=0;i<str.length();i++)
    {
        first[SYM[str[i]]].insert(str[i]);
        terminals.insert(str[i]);
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
    first_com();
    item();
    itemSet T;
    set<itemSet>::iterator it=C.begin();
    item_it it2;
    set<pair<char,string> >L;
    i=0;
    cout<<"Items are: ";
    for(;it!=C.end();it++)
    {
        T=*it;
        cout<<"\nItem "<<no_state<<": ";
        it2=T.begin();
        L.clear();
        cout<<"{ ";
        for(;it2!=T.end();it2++)
        {
            cout<<(*it2).lhs<<"->"<<(*it2).rhs<<","<<(*it2).lhd<<"; ";
            L.insert(mp((*it2).lhs,(*it2).rhs));
        }
        cout<<"}";
        if(LALR.find(L)==LALR.end())
        {
            vector<int>lalr;
            lalr.pb(no_state);
            LALR.insert(mp(L,lalr));
        }
        else
            {
               
              LALR[L].pb(no_state);
            }
        i++;
        Cstate.insert(mp(T,no_state));
        Istate.insert(mp(no_state,T));
        no_state++;
    }
    vector<int>::iterator vit;
    no_state=0;
    State.clear();
    map<set<pair<char,string> >,vector<int> >::iterator IT=LALR.begin();
    for(;IT!=LALR.end();IT++)
    {
        vit=IT->second.begin();
        T.clear();
       
        for(;vit!=IT->second.end();vit++)
        {
           
            it2=Istate[*vit].begin();
            for(;it2!=Istate[*vit].end();it2++)
            {
                T.insert(*it2);
            }
            U.insert(mp(no_state,*vit));
            IU.insert(mp(*vit,no_state));
        }
       
        State.insert(mp(T,no_state));
        no_state++;
    }
    for(i=0;i<no_state;i++)
    {
    	map<int,char>::iterator it3=IM.begin();
    	for(;it3!=IM.end();it3++){
    		Table[i][it3->first].action=-1;
    	 }
    }
    cout<<"\nTable initialised"<<endl;
     it=C.begin();
    itemSet res;
    i=0;
    string zod="";
    zod+=start;
    zod=zod+".";
   
    int a;i=0;
    map< itemSet ,int>::iterator mit=State.begin();
    for(;mit!=State.end();mit++)
    {
    	T=mit->first;;
    	it2=T.begin();
    	i=mit->second;
    
    	string prev;
        for(;it2!=T.end();it2++)
        {
            if(it2->lhs=='Z'&&it2->rhs==zod&&it2->lhd=='$')
            {
                    if(Table[i][SYM['$']].action>0)
                        {
                            cout<<"Not a LALR1 grammar";
                            return 0;
                        }
                    Table[i][SYM['$']].action=3;
                    continue;
            }
                a=it2->rhs.find('.')+1;
                if(a==it2->rhs.length()&&it2->lhs!='Z')
                {
                        if(Table[i][SYM[it2->lhd]].action>0)
                        {
                            cout<<"Not a SLR grammar";
                            return 0;
                        }
                        Table[i][SYM[it2->lhd]].action=2;
                        Table[i][SYM[it2->lhd]].state=Prod[mp(it2->lhs,remove_dot(it2->rhs))];
                    continue;
                }
                j=IU[Cstate[gto[mp(Istate[U[i]],it2->rhs[a])]]];
                    if(prev!=it2->rhs&&Table[i][SYM[it2->rhs[a]]].action>0)
                        {
                            cout<<"Not a SLR grammar"<<it2->rhs;
                            print(T);
                            return 0;
                        }
                        else{
                                
                Table[i][SYM[it2->rhs[a]]].action=1;
                Table[i][SYM[it2->rhs[a]]].state=j;
                prev=it2->rhs;
                        }
        }
        prev="";
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
    			cout<<"String is NOT accepted!\n";
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
 * 4
 * S C c d
 * 2 c d
 * S 3
 * S CC
 * C cC
 * C d
 *
 * */

