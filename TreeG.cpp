#include <bits/stdc++.h>
#include "TreeSize.cpp"
using namespace std;

//木の重心を得る: O(V + E)
class TreeG{
public:
  int V;
  vector<vector<int> > G;
  vector<int> par;
  TreeG():V(-1){};
  TreeG(int V):V(V),G(V),par(V){}
  
  void add_edge(int a,int b){
    assert(a < V && b < V);
    assert(a >= 0 && b >= 0);
    G[a].push_back(b);
    G[b].push_back(a);
  }

  int dfs(int pos,int pre){
    par[pos] = pre;
    int res = 1;
    for(int to: G[pos]) if(to != pre) res += dfs(to, pos); 
    return res;
  }
  
  //rootから連結するグラフの重心を求める
  vector<int> get(int root = 0){ 
    TreeSize sz(G);
    sz.build(root);
    par.resize(V,-2);
    int size = dfs(root,-1);
    
    vector<int> res;
    for(int i=0;i<V;i++){
      if(par[i] == -2) continue;
      int flag = (size - sz.size(i)) <= size/2;
      for(int to:G[i]) if(to != par[i]) flag &= (sz.size(to) <= size/2);
      if(flag) res.push_back(i);  
    }
    assert(!res.empty() && res.size() < 3);
    return res;
  }

  //fromからtoへのエッジ及び、fromを親とした時のtoを根とする部分木を削除
  void erase(int from,int to){
    G[from].erase(find(G[from].begin(),G[from].end(), to));
    function<void(int,int)> dfs=[&](int pos,int pre){
      for(int to:G[pos]) if(to != pre) dfs(to, pos);
      G[pos].clear();
    };
    dfs(to, from);
  }
  
};
