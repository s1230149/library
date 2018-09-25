#include <bits/stdc++.h>
using namespace std;
/*
 *  QuickFind
 *  UnionFindの亜種、各グループのノード集合を高速に管理する。
 */

class QF{
public:
  int V;
  vector<int> par;
  vector<vector<int> > grp; //grp[i] := 頂点iと同じunorderノード集合(i != find(i)のときは空)
  QF(){}
  QF(int V):V(V),par(V),grp(V){
    iota(par.begin(), par.end(), 0);
    for(int i=0;i<V;i++) grp[i].push_back(i);
  }
  
  int find(int x){
    assert(x < V);
    if(par[x]==x)return x;
    return par[x]=find(par[x]);
  }

  void unite(int x,int y){
    x=find(x), y=find(y);
    if(x==y)return;
    if(grp[x].size() < grp[y].size()) swap(x, y);
    par[y] = x;
    for(int a:grp[y]) grp[x].push_back(a);
    grp[y].clear();
  }
  bool same(int x,int y){return find(x)==find(y);}
  int size(int x){return grp[find(x)].size();}
};


signed main(){
  
  int n, q;
  cin>>n>>q;

  QF A(n);
  while(q--){
    int com, x, y;
    cin>>com>>x>>y;
    if(com == 0) A.unite(x, y);
    else cout<<A.same(x, y)<<endl;
  }
  
  return 0;
}
