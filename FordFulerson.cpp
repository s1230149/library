#include <bits/stdc++.h>
using namespace std;

/*最大流アルゴリズム(Ford_Fulerson法使用)　O(F|E|)*/
template<typename D, D INF>
class FordFulerson{
public:
  struct edge{
    int to;
    D cap;
    int rev;
    edge(){};
    edge(int to,D cap,int rev):to(to), cap(cap), rev(rev){};
  };

  int V;                      //ノード数
  vector<vector<edge> > G;    //グラフの隣接リスト
  vector<int> used;           //DFSですでに調べたかのフラグ

  FordFulerson():V(-1){}
  FordFulerson(int V):V(V),G(V){}

  //fromからtoへ向かう容量capの辺をグラフに追加する
  void add_edge(int from, int to, D cap){ //有向
    assert(0 <= from && from < V);
    assert(0 <= to && to < V);
    G[from].push_back(edge(to, cap, G[to].size()));
    G[to].push_back(edge(from, 0, G[from].size()-1));
  }

  void add_edge2(int a, int b, D cap){ //双方向
    assert(0 <= a && a < V);
    assert(0 <= b && b < V);
    G[a].push_back(edge(b, cap, G[b].size()));
    G[b].push_back(edge(a, cap, G[a].size()-1));
  }

  //増加パスをDFSで探す
  D dfs(int v, int t, D f, const int num){
    if(v == t) return f;
    used[v] = num;
    for(auto &e:G[v]){
      if(used[e.to] != num && e.cap > 0){
        D d = dfs(e.to ,t , min(f, e.cap), num);
        if(d > 0){
          e.cap -= d;
          G[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }

  //sからtへの最大流を求める
  D max_flow(int s, int t){
    used.clear(); used.resize(V, -1);
    int num = 0;
    D res = 0;
    for(;;){
      D f = dfs(s, t, INF, num++);
      if(f == 0) return res;
      res += f;
    }
  }
};
