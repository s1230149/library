#include <bits/stdc++.h>
#include "SparseTable.cpp"
using namespace std;


class LCA{
public:
  int V;                     //ノード数
  int root;                  //根の頂点番号
  vector<vector<int> > G;    //Grapth
  vector<int> L,R;           //[L,R]
  SparseTable tbl;
  bool ok;
  LCA():V(-1),ok(0){};
  LCA(int V,int root = 0):V(V),root(root),G(V),L(V),R(V),tbl(V,1),ok(0){}

  void add_edge(int a,int b){
    assert(a >= 0 && b >= 0);
    assert(a < V && b < V);
    G[a].push_back(b);
    G[b].push_back(a);
  }

  void build(){
    ok = 1;
    int cnt = 0;
    vector<int> his;    
    function<void(int,int)> dfs = [&](int pos,int pre){
      his.push_back(pos);
      for(int to:G[pos]){
	if(to == pre) continue;
	  cnt++;
	  dfs(to, pos);
	  his.push_back(pos);
      }
    };
    
    dfs(root,-1);
    L.clear(); L.resize(V, his.size());
    R.clear(); R.resize(V, -1);
    for(int i=0;i<(int)his.size();i++){
      int u = his[i];
      L[u] = min(L[u], i);
      R[u] = max(R[u], i);
      tbl.update(i, u);
    }
  }

  int lca(int u, int v){assert(ok);return tbl.get(min(L[u], L[v]), max(R[u],R[v])+1);}
};

