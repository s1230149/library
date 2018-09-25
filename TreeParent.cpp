#include <bits/stdc++.h>
using namespace std;

class TreeParent{
public:
  int V;                        //ノード数
  int root;                     //根
  vector<vector<int> > G;       //Graph
  vector<int> parent;           //親
  int ok;
  TreeParent():V(-1){};
  TreeParent(int V,int root = 0):V(V),root(root),G(V),parent(V),ok(0){}
  TreeParent(vector<vector<int> > G,int root = 0):V(G.size()),root(root),G(G),parent(V),ok(0){}
  void resize(int n){*this = TreeParent(n);}
  void add_edge(int a,int b){
    ok = false;
    assert(a < V && b < V);
    assert(a >= 0 && b >= 0);
    G[a].push_back(b);
    G[b].push_back(a);
  }
  void build(int root = -1){
    ok = 1;
    if(root != -1) this->root = root;
    function<void(int,int)> dfs = [&](int pos,int pre){
      parent[pos] = pre;
      for(int to:G[pos]) if(to != pre) dfs(to, pos);
    };
    dfs(this->root, -1);
  }
  int get(int u){assert(ok); assert(0 <= u && u < V); return parent[u];}
  
};

