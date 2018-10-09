#include <bits/stdc++.h>
#include "Lowlink.cpp"
using namespace std;
/*二重辺連結成分分解 O(V + E)*/

class BCC{
public:
  int V;                     // 頂点数
  int K;                     // 分解後の頂点数
  Lowlink B;                 // 橋の列挙用
  vector<vector<int> > G;    // 元のグラフ
  vector<vector<int> > T;    // 分解後のグラフ(木)
  vector<int> par;           // 分解後のグラフの頂点0を根としたときの親
  vector<int> cmp;           // 元のグラフの分解後の頂点番号
  vector<int> used;          // dfs用
  
  BCC():V(-1){}
  BCC(int V):V(V),B(V),G(V){};
  
  void add_edge(int a,int b){
    B.add_edge(a,b);
    G[a].push_back(b);
    G[b].push_back(a);
  }
  
  void dfs(int pos){
    if(used[pos]++) return;
    cmp[pos] = K;
    for(int nx:G[pos]) if(!B.isBridge(pos,nx)) dfs(nx);
  }
  
  int build(bool makeT = 0){
    B.build();
    used.clear();used.resize(V,0);
    cmp.clear();cmp.resize(V,0);
    K = 0;
    for(int i=0;i<V;i++) if(used[i]==0) dfs(i),K++;
    if( makeT ) makeTree();
    return K;
  }
  
  void makeTree(){
    
    function<void(int,int)> dfs = [&](int pos, int pre){
      par[pos] = pre;
      for(int nx:T[pos]) if(nx!=pre) dfs(nx,pos);
    };
    
    T.clear(); T.resize(K);
    par.clear();par.resize(V,-1);
    for(int i=0;i<V;i++){
      set<int> used;
      for(int nx:G[i]){
	int a = cmp[i], b = cmp[nx];
	if(a != b && !used.count(b)) T[a].push_back(cmp[nx]), used.insert(b);
      }
    }
    
    for(int i=0;i<K;i++) if(par[i] == -1) dfs(i,-1);
  }

  bool same(int u,int v){return cmp[u] == cmp[v];}
};
