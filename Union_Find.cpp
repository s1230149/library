#include <bits/stdc++.h>
using namespace std;

class UF{
public:
  int V;
  vector<int> par,rnk,sz;
  UF(){}
  UF(int V):V(V),par(V),rnk(V,0),sz(V,1){for(int i=0;i<V;i++)par[i]=i;}
  
  int find(int x){
    assert(x < V);
    if(par[x]==x)return x;
    return par[x]=find(par[x]);
  }
  
  void unite(int x,int y){
    x=find(x), y=find(y);
    if(x==y)return;
    if(rnk[x]<rnk[y])par[x]=y, sz[y] += sz[x];
    else{
      par[y]=x;
      sz[x] += sz[y];
      if(rnk[x]==rnk[y])rnk[x]++;
    }
  }

  bool same(int x,int y){return find(x)==find(y);}

  int size(int x){return sz[find(x)];}
};

int main(){

}
