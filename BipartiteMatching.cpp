#include <bits/stdc++.h>
using namespace std;

class BipartiteMatching{
public:
  int V;                 //頂点数
  vector<vector<int> >G; //グラフの隣接リスト表現
  vector<int> match;     //マッチングのペア
  vector<int> used;      //DFSですでに調べたかのフラグ

  BipartiteMatching(){}
  BipartiteMatching(int V):V(V), G(V){}

  //uとvを結ぶ辺をグラフに追加する
  void add_edge(int a,int b){
    assert(0 <= a && a < V);
    assert(0 <= b && b < V);
    G[a].push_back(b);
    G[b].push_back(a);
  }

  //増加パスをDFSで探す
  int dfs(int v, const int num){
    used[v] = num;
    for(int i=0; i<(int)G[v].size(); i++){
      int u = G[v][i], w = match[u];
      if(w<0 || (used[w] != num && dfs(w, num))){
        match[v] = u;
        match[u] = v;
        return 1;
      }
    }
    return 0;
  }

  //二部グラフの最大マッチングを求める
  int solve(){
    int res=0;
    match.clear(); match.resize(V, -1);
    used.clear(); used.resize(V, 0);
    for(int v=0; v<V; v++)
      if(match[v] < 0 && dfs(v, res)) res++;
    return res;
  }
};
