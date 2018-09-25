#include <bits/stdc++.h>
using namespace std;

class EulerTour{
public:
  int V;                     //ノード数
  int root;                  //根の頂点番号
  vector<vector<int> > G;    //Grapth
  vector<int> L,R;           //[L,R]
  bool ok;
  EulerTour():V(-1),ok(0){};
  EulerTour(int V,int root = 0):V(V),root(root),G(V),L(V),R(V),ok(0){}

  void add_edge(int a,int b){
    assert(a >= 0 && b >= 0);
    assert(a < V && b < V);
    G[a].push_back(b);
    G[b].push_back(a);
  }

  void build(){
    ok = 1;
    int cnt = 0;
    function<void(int,int)> dfs = [&](int pos,int pre){
      L[pos] = cnt;
      for(int to:G[pos]) if(to != pre) cnt++, dfs(to, pos);
      R[pos] = cnt;
    };
    dfs(root,-1);
  }

  
  typedef pair<int,int> P;
  P get(int v){assert(ok && v < V); return P(L[v],R[v]);} //[l, r]
};

