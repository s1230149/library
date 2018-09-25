#include <bits/stdc++.h>
using namespace std;

//rootを根とする木の部分木のサイズを求める
class TreeSize{
public:
  int V;                        //ノード数
  int root;                     //根
  vector<vector<int> > G;       //Graph
  vector<int> w;                //ノードのに重みが有る場合デフォルトでは1
  vector<int> sz;               //部分木のサイズ
  int ok;
  TreeSize():V(-1){};
  TreeSize(int V,int root = 0):V(V),root(root),G(V),w(V,1),sz(V,0),ok(0){}
  TreeSize(vector<vector<int> > G,int root = 0):V(G.size()),root(root),G(G),w(V,1),sz(V,0),ok(0){}
  void resize(int n){*this = TreeSize(n);}
  int& operator [](int i){return w[i];}
  
  void add_edge(int a,int b){
    ok = false;
    assert(a < V && b < V);
    assert(a >= 0 && b >= 0);
    G[a].push_back(b);
    G[b].push_back(a);
  }
  
  void build(int root=-1){
    ok = 1;
    if(root != -1) this->root = root;
    dfs(this->root,-1);
  }
  
  int dfs(int pos,int pre = -1){
    sz[pos] = w[pos];
    for(int to:G[pos]) if(to != pre) sz[pos] += dfs(to, pos);
    return sz[pos];
  }
  int size(int i){assert(ok);return sz[i];}
};


