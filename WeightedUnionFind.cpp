#include <bits/stdc++.h>
using namespace std;

class WeightedUnionFind{
public:
  int V;
  vector<int> par, rnk, diff, sz;
  WeightedUnionFind():V(-1){}
  WeightedUnionFind(int V):V(V),par(V),rnk(V,0),diff(V,0),sz(V,1){for(int i=0;i<V;i++)par[i]=i;}
  
  int find(int x){
    assert(x < V);
    if(par[x] == x) return x;
    int p = find(par[x]);
    diff[x] = diff[x] + diff[ par[x] ];
    return par[x] = p;
  }

  //頂点xは頂点yよりもz大きい
  void relate(int x,int y,int z){
    int sx = x, sy = y;
    x = find(x), y = find(y);
    if(x == y) assert(getDiff(sx,sy) == z);
    if(x == y)return;
    
    if(rnk[x] < rnk[y]) {
      par[x] = y;
      sz[y] += sz[x];
      diff[x] = z + (-diff[sx] + diff[sy]);
    }
    else{
      par[y] = x;
      sz[x] += sz[y];
      diff[y] = -z + (diff[sx] - diff[sy]);
      if(rnk[x]==rnk[y])rnk[x]++;
    }
  }

  int getDiff(int u,int v){
    assert(same(u,v));
    return diff[u] - diff[v];
  }
  
  bool same(int x,int y){return find(x)==find(y);}
  int size(int x){return sz[find(x)];}
  
};

signed main(){
  int n;
  cin>>n;
  WeightedUnionFind wuf(n);
  
  int q;
  cin>>q;
  while(q--){
    int cmd, x, y, z;
    cin>>cmd >> y >> x;
    if(cmd == 0){
      cin>>z;
      wuf.relate(x,y,z);
    }
    if(cmd == 1){
      if(!wuf.same(x, y)) cout<<"?"<<endl;
      else cout<<wuf.getDiff(x, y)<<endl;
    }
  }
  return 0;
}
