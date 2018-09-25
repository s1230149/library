#include <bits/stdc++.h>
using namespace std;

class Dinic{
public:
  
  struct edge{
    int to,cap,rev;
    edge(){};
    edge(int to,int cap,int rev):to(to),cap(cap),rev(rev){};
  };

  int V;
  vector<vector<edge> > G; //グラフの隣接リスト表現
  vector<int> level;       //sからの距離
  vector<int> iter;        //どこまで調べ終わったか
  int INF;
  
  Dinic():V(-1){};
  Dinic(int V,int INF=1e9):V(V),G(V),level(V),iter(V),INF(INF){}

  //fromからtoへ向かう容量capの辺をグラフに追加。
  void add_edge(int from,int to,int cap){ //有向
    assert(from < V && to < V);
    G[from].push_back(edge(to,cap,G[to].size()));
    G[to].push_back(edge(from,0,G[from].size()-1));
  }
  
  void add_edge2(int from,int to,int cap){ //双方向
    assert(from < V && to < V);
    G[from].push_back(edge(to,cap,G[to].size()));
    G[to].push_back(edge(from,cap,G[from].size()-1));
  }

  //sからの最短距離をBFSで計算する
  void bfs(int s){
    level.clear(); level.resize(V,-1);
    queue<int> que;
    level[s] = 0;
    que.push(s);
    while(!que.empty()){
      int v = que.front(); que.pop();
      for(edge &e : G[v])
        if(e.cap > 0 && level[e.to] < 0){
          level[e.to] = level[v] + 1;
          que.push(e.to);
        }
    }
  }

  //増加パスをDFSで探す。
  int dfs(int v,int t,int f){
    if(v==t) return f;
    for(int &i= iter[v]; i<(int)G[v].size(); i++){
      edge &e = G[v][i];
      if(e.cap > 0 && level[v] < level[e.to]){
        int d = dfs(e.to, t, min(f, e.cap));
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
  int max_flow(int s,int t){
    assert(V >= 0);
    int flow=0;
    for(;;){
      bfs(s);
      if(level[t] < 0) return flow;
      iter.clear();iter.resize(V,0);
      int f;
      while((f=dfs(s ,t ,INF)) > 0 ) flow += f;
    }
  }
};

