#include <bits/stdc++.h>
using namespace std;

class MinCostFlow{
public:
  //辺を表す構造体(行き先、容量、コスト、逆辺)
  typedef long long ctype;
  ctype INF = 1LL<<55;
  
  struct edge{
    int to,cap;
    ctype cost;
    int rev;
    edge();
    edge(int to,int cap,ctype cost,int rev):to(to),cap(cap),cost(cost),rev(rev){}
  };
  
  int V;                          //頂点数
  vector<vector<edge> > G;        //グラフの隣接リスト表現
  vector<ctype> dist;             //最短距離
  vector<int> prevv,preve;        //直前の頂点と辺

  MinCostFlow():V(-1){}
  MinCostFlow(int V):V(V), G(V), dist(V), prevv(V), preve(V){};
  
  // fromからtoへ向かう容量cap、コストcostの辺をグラフに追加する。
  void add_edge(int from,int to,int cap ,ctype cost){
    assert(from>=0 && to >= 0);
    assert(from<V && to<V);
    G[from].push_back((edge){to,cap,cost,(int)G[to].size()});
    G[to].push_back((edge){from,0,-cost,(int)G[from].size()-1});
  }
  
  //sからtへの流量fの最小費用流を求める
  //流せない場合-1を返す
  ctype flow(int s, int t, int f){
    ctype res = 0;

    while(f>0){
      //ベルマンフォード法により,s-t間最短路を求める
      fill(dist.begin(),dist.end(),INF);
      dist[s] = 0;
      bool update = true;
      while(update){
        update = false;
        for(int v=0; v<V ;v++){
          if(dist[v]==INF) continue;
          for(int i=0; i<(int)G[v].size(); i++){
            edge &e = G[v][i];
            if(e.cap > 0 && dist[e.to] > dist[v] + e.cost) {
              if(abs(dist[e.to] - dist[v] - e.cost) < 1e-8) continue; //double演算用
              dist[e.to] = dist[v] + e.cost;
              prevv[e.to] = v;
              preve[e.to] = i;
              update = true;
            }
          }
        }
      }

      if(dist[t]==INF) return -1; //これ以上流せない。
    
      //s−t間短路に沿って目一杯流す
      int d = f;
      for(int v=t; v!=s; v=prevv[v]) d = min(d, G[prevv[v]][preve[v]].cap);
      f -= d;
      res += d * dist[t];
      for(int v=t; v!=s; v=prevv[v]){
        edge &e = G[prevv[v]][preve[v]];
        e.cap -= d;
        G[v][e.rev].cap += d;
      }
    }
    return res;
  }
};
